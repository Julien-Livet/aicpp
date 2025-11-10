#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>

#include <boost/json.hpp>

#include "aicpp/Brain.h"

using namespace aicpp;
using namespace boost::json;

using Matrix = std::vector<std::vector<int>>;

std::string const path{"../../ARC-AGI-2-main/data/training"};

Eigen::MatrixXi boostJsonToEigenMatrix(array const& arr)
{
    std::size_t const rows = arr.size();
    std::size_t const cols = arr.at(0).as_array().size();

    Eigen::MatrixXi mat(rows, cols);

    for (std::size_t i = 0; i < rows; ++i)
    {
        auto const& row = arr[i].as_array();

        for (std::size_t j = 0; j < cols; ++j)
            mat(i, j) = (int)row[j].as_int64();
    }

    return mat;
}

void process(std::string const& task)
{
    std::ifstream ifs{path + "/" + task + ".json"};

	std::string content;

	while (ifs)
	{
		std::string line;

		std::getline(ifs, line);

		content += line + '\n';
	}

    value jv = parse(content);

    auto train = jv.at("train").as_array();
    auto const taskTime{std::chrono::system_clock::now()};
    bool subtaskFailed{false};

    for (std::size_t i = 0; i < train.size(); ++i)
    {
        auto const& sample = train[i].as_object();

        auto const input = boostJsonToEigenMatrix(sample.at("input").as_array());
        auto const output = boostJsonToEigenMatrix(sample.at("output").as_array());
/*
        std::cout << "input" << std::endl;
        std::cout << input << std::endl;
        std::cout << "output" << std::endl;
        std::cout << output << std::endl;
*/
        Brain brain;

        std::map<std::string, size_t> neuronIds;

        auto const m{brain.addMatrices<Eigen::MatrixXi>()};
        neuronIds.insert(m.begin(), m.end());

        brain.deactivateAllModules();

        std::vector<std::string> activatedNeurons{
            "zero_",
            "tile_",
            "fliplr_",
            "flipud_",
            "place_region_",
            "hline_",
            "vline_",
            "hlineleft_",
            "hlineright_",
            "vlineup_",
            "vlinedown_",
            "fill_region_at_",
            "fill_region2_at_",
            "replace_",
            "put_",
            "put_value_",
            "fill_region_",
            "or_",
            "and_",
            "xor_",
            "invert_",
            "dotsegment_",
            "rot90_"
        };

        for (auto const& p : brain.neurons())
        {
            for (auto const& s : activatedNeurons)
                if (brain.neuronName(p.first).find(s) != std::string::npos)
                    brain.activateNeuron(p.first);
        }

        neuronIds["input"] = brain.addNeuron(Neuron<Eigen::MatrixXi>{[&input] () { return input; }, "input"});
        neuronIds["shape_input"] = brain.addNeuron(Neuron<std::pair<int, int> >{[&input] () { return std::make_pair((int)input.rows(), (int)input.cols()); }, "shape_input"});
        neuronIds["shape_output"] = brain.addNeuron(Neuron<std::pair<int, int> >{[&output] () { return std::make_pair((int)output.rows(), (int)output.cols()); }, "shape_output"});

        std::set<int> values;

        for (int i = 0; i < input.rows(); ++i)
            for (int j = 0; j < input.cols(); ++j)
                values.emplace(input(i, j));

        for (int i = 0; i < output.rows(); ++i)
            for (int j = 0; j < output.cols(); ++j)
                values.emplace(output(i, j));

        std::map<std::string, size_t> ids;

        {
            auto const id = brain.addNeuron(Neuron<std::pair<int, int> >{[input, output] () { return std::make_pair((int)output.rows() / (int)input.rows(), (int)output.cols() / (int)input.cols()); }, "", "pairs.variables"});
            ids[std::to_string(id)] = id;
        }

        for (auto const& v : values)
        {
            auto const name{std::to_string(v)};
            ids[name] = brain.addNeuron(Neuron<int>{[v] () { return v; }, name, "ints.variables"});
        }

        std::set<std::vector<std::pair<int, int> > > s;

        for (int i = 0; i < input.rows(); ++i)
        {
            for (int j = 0; j < input.cols(); ++j)
            {
                auto r = region(input, std::make_pair(i, j), false);

                std::sort(r.begin(), r.end(),
                          [] (auto const& x, auto const& y) -> bool
                    {
                        if (x.first == y.first)
                            return x.second < y.second;

                        return x.first < y.first;
                    }
                );

                if (s.find(r) == s.end())
                    s.emplace(r);
            }
        }

        for (auto const& r : s)
        {
            auto const id = brain.addNeuron(Neuron<std::vector<std::pair<int, int> > >{[r] () { return r; }, "", "vectors.variables"});
            ids[std::to_string(id)] = id;
        }

        for (int i = 0; i < output.rows(); ++i)
        {
            for (int j = 0; j < output.cols(); ++j)
            {
                auto const name{"(" + std::to_string(i) + ", " + std::to_string(j) + ")"};
                ids[name] = brain.addNeuron(Neuron<std::pair<int, int> >{[i, j] () { return std::make_pair(i, j); }, name, "pairs.variables"});
            }
        }

        auto const maxRows{std::max(input.rows(), output.rows())};
        auto const maxCols{std::max(input.cols(), output.cols())};

        for (int i = 0; i < std::max(maxRows, maxCols); ++i)
        {
            auto const name{std::to_string(i)};
            ids[name] = brain.addNeuron(Neuron<int>{[i] () { return i; }, name, "ints.variables"});
        }

        int const timeout{10 * 60 * 1000};
        auto const time{std::chrono::system_clock::now()};

        int learnTimeout{2 * 1000};
        Eigen::MatrixXi previousOutput{};
        std::vector<Connection> connections;

        constexpr double eps = 1.0e-6;

        while (heuristic(previousOutput, output) >= eps)
        {
            if ((int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() > timeout)
                break;
/*
            if (connections.size())
            {
                std::cout << "step" << std::endl;
                std::cout << std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connections.front())) << std::endl;
            }
*/
            brain.neuronTimeout = learnTimeout / 8;
            connections = brain.learn(output, 1, -1, learnTimeout);
            brain.setConnections(connections);

            try
            {
                auto const newOutput{std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connections.front()))};

                if (heuristic(previousOutput, newOutput) < eps)
                    learnTimeout *= 2;
                else if (learnTimeout > 1000)
                    learnTimeout /= 2;

                previousOutput = newOutput;
            }
            catch (std::exception const&)
            {
                learnTimeout *= 2;
            }
        }

        //std::cout << "Task #" << task << ": subtask #" << i;

        if (heuristic(previousOutput, output) < eps)
        {
            //std::cout << " passed";
        }
        else
        {
            //std::cout << " failed";
            subtaskFailed = true;
        }

        //std::cout << " in " << (int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() << "ms" << std::endl;

        if (subtaskFailed)
            break;
    }

    std::cout << "Task #" << task;

    if (!subtaskFailed)
        std::cout << ": task passed";
    else
        std::cout << ": task failed";

    std::cout << " in " << (int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(taskTime)).count() << "ms" << std::endl;
}

int main()
{
    //process("00d62c1b");

    auto const time{std::chrono::system_clock::now()};

    std::filesystem::path const p{path};
    std::vector<std::future<void> > futures;

    for (auto const& dir_entry : std::filesystem::directory_iterator{p})
    {
        auto const pp{dir_entry.path()};

        if (std::filesystem::is_regular_file(pp))
        {
            //process(pp.stem().string());
            futures.emplace_back(std::async(std::launch::async, [pp] {
                process(pp.stem().string());
            }));
        }
    }

    for (auto& f : futures)
        f.get();

    std::cout << "Process in " << (int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() << "ms" << std::endl;

    return 0;
}
