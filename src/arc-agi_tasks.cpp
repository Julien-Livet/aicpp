#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>

#include <boost/json.hpp>

#include "aicpp/Brain.h"

using namespace aicpp;
using namespace boost::json;

using Matrix = std::vector<std::vector<int>>;

std::string const path{"../../ARC-AGI-2-main/data"};

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

void updateMapping(std::map<int, int>& mapping, Brain const& brain, Connection const& connection)
{
    if (brain.neuronName(connection.neuronId()).find("replace") != std::string::npos)
    {
        std::visit(
            [brain, &mapping, connection] (auto const& value)
            {
                if constexpr (typeid(decltype(value)) == typeid(Connection))
                    updateMapping(mapping, brain, value);
            }, connection.inputs()[0]);

        mapping[std::any_cast<int>(brain.connectionOutput(std::get<Connection>(connection.inputs()[1])))] = std::any_cast<int>(brain.connectionOutput(std::get<Connection>(connection.inputs()[2])));
    }
}

void process(std::string const& folder, std::string const& task)
{
    std::ifstream ifs{path + "/" + folder + "/" + task + ".json"};

    std::string content;

    while (ifs)
    {
        std::string line;

        std::getline(ifs, line);

        content += line + '\n';
    }

    value const jv = parse(content);

    auto const train = jv.at("train").as_array();
    std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > trainPairs;

    for (std::size_t i = 0; i < train.size(); ++i)
    {
        auto const& sample = train[i].as_object();

        trainPairs.emplace_back(std::make_pair(boostJsonToEigenMatrix(sample.at("input").as_array()),
                                               boostJsonToEigenMatrix(sample.at("output").as_array())));
    }

    auto const test = jv.at("test").as_array();
    std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > testPairs;

    for (std::size_t i = 0; i < test.size(); ++i)
    {
        auto const& sample = test[i].as_object();

        testPairs.emplace_back(std::make_pair(boostJsonToEigenMatrix(sample.at("input").as_array()),
                                               boostJsonToEigenMatrix(sample.at("output").as_array())));
    }

    Brain brain;

    std::map<std::string, size_t> neuronIds;

    auto const m{brain.addMatrices<Eigen::MatrixXi>()};
    neuronIds.insert(m.begin(), m.end());

    brain.deactivateAllModules();

    std::vector<std::string> const activatedNeurons{
        "zero",
        "tile",
        "fliplr",
        "flipud",
        "place_region",
        "hline",
        "vline",
        "hlineleft",
        "hlineright",
        "vlineup",
        "vlinedown",
        "fill_region_at",
        "fill_region2_at",
        "replace",
        "map",
        "put_matrix",
        "put_value",
        "fill_region",
        "or",
        "and",
        "xor",
        "invert",
        "dotsegment",
        "rot90",
        "matrix_region"
    };

    for (auto const& p : brain.neurons())
    {
        for (auto const& s : activatedNeurons)
        {
            if (brain.neuronName(p.first).starts_with("matrices." + s))
                brain.activateNeuron(p.first);
        }
    }

    std::map<int, int> mapping;

    neuronIds["input"] = brain.addNeuron(Neuron<Eigen::MatrixXi>{[] () { return Eigen::MatrixXi{}; }, "input"});
    neuronIds["mapping"] = brain.addNeuron(Neuron<std::map<int, int> >{[&mapping] () { return mapping; }, "mapping"});

    std::set<int> values;

    for (int i{0}; i < 10; ++i)
        values.emplace(i);

    std::map<std::string, size_t> ids;

    for (auto const& v : values)
    {
        auto const name{std::to_string(v)};
        ids[name] = brain.addNeuron(Neuron<int>{[v] () { return v; }, name, "ints.variables"});
    }

    int const timeout{10 * 60 * 1000};
    auto const time{std::chrono::system_clock::now()};
    int learnTimeout{2 * 1000};
    std::vector<Connection> connections;
    std::vector<Eigen::MatrixXi> outputs(trainPairs.size());
    double cost{1.0};

    constexpr double eps = 1.0e-6;

    while (cost >= eps)
    {
        if ((int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() > timeout)
            break;

        brain.neuronTimeout = learnTimeout / 8;

        for (size_t i{0}; i < trainPairs.size(); ++i)
        {
            auto const& p{trainPairs[i]};

            std::get<Neuron<Eigen::MatrixXi> >(brain.neuron(neuronIds["input"])).function = [&p] () -> Eigen::MatrixXi { return p.first; };

            connections = brain.learn(p.second, 1, -1, learnTimeout);

            brain.setConnections(connections);
        }

        cost = 0;

        auto const& connection{connections.front()};

        updateMapping(mapping, brain, connection);

        for (size_t i{0}; i < trainPairs.size(); ++i)
        {
            auto const& p{trainPairs[i]};

            std::get<Neuron<Eigen::MatrixXi> >(brain.neuron(neuronIds["input"])).function = [&p] () -> Eigen::MatrixXi { return p.first; };

            try
            {
                auto const newOutput{std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connection))};

                cost += heuristic(p.second, newOutput);

                if (heuristic(outputs[i], newOutput) < eps)
                    learnTimeout *= 2;
                else if (learnTimeout > 1000)
                    learnTimeout /= 2;

                outputs[i] = newOutput;
            }
            catch (std::exception const&)
            {
                learnTimeout *= 2;
            }
        }
    }

    cost = 0;

    for (auto const& p : testPairs)
    {
        std::get<Neuron<Eigen::MatrixXi> >(brain.neuron(neuronIds["input"])).function = [&p] () -> Eigen::MatrixXi { return p.first; };

        auto const newOutput{std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connections.front()))};

        cost += heuristic(p.second, newOutput);
    }

    std::cout << "Task #" << task;

    if (cost < eps)
        std::cout << ": task passed";
    else
        std::cout << ": task failed";

    std::cout << std::endl;
}

int main()
{
    //Training
    {
        process("training", "0d3d703e");
        return 0;
        auto const time{std::chrono::system_clock::now()};

        std::filesystem::path const p{path + "/training"};
        std::vector<std::future<void> > futures;

        for (auto const& dir_entry : std::filesystem::directory_iterator{p})
        {
            auto const pp{dir_entry.path()};

            if (std::filesystem::is_regular_file(pp))
            {
                //process("training", pp.stem().string());
                futures.emplace_back(std::async(std::launch::async, [pp] {
                    process("training", pp.stem().string());
                }));
            }
        }

        for (auto& f : futures)
            f.get();

        std::cout << "Process in " << (int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() << "ms" << std::endl;
    }

    //Evaluation
    {
        process("evaluation", "1ae2feb7");
        return 0;
        auto const time{std::chrono::system_clock::now()};

        std::filesystem::path const p{path + "/evaluation"};
        std::vector<std::future<void> > futures;

        for (auto const& dir_entry : std::filesystem::directory_iterator{p})
        {
            auto const pp{dir_entry.path()};

            if (std::filesystem::is_regular_file(pp))
            {
                //process("evaluation", pp.stem().string());
                futures.emplace_back(std::async(std::launch::async, [pp] {
                    process("evaluation", pp.stem().string());
                }));
            }
        }

        for (auto& f : futures)
            f.get();

        std::cout << "Process in " << (int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() << "ms" << std::endl;
    }

    return 0;
}
