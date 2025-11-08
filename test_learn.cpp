#include <iostream>
#include <random>
#include <set>

#include "Brain.h"

//std::random_device rd;
std::mt19937 rng(0);//(rd());

Eigen::Matrix<int, -1, -1> matrix()
{
    constexpr int M = 10;
    constexpr int N = 10;

    Eigen::Matrix<int, -1, -1> m;
    m.resize(M, N);
    m.setZero();

    std::uniform_int_distribution<std::mt19937::result_type> distM(0, M - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distN(0, N - 1);

    m = hline(m, distM(rng), 1);
    m = vline(m, distN(rng), 2);/*
    m = hlineright(m, std::make_pair(distM(rng), distN(rng)), 3);
    m = vlineup(m, std::make_pair(distM(rng), distN(rng)), 4);
    m = hlineleft(m, std::make_pair(distM(rng), distN(rng)), 5);
    m = vlinedown(m, std::make_pair(distM(rng), distN(rng)), 6);*/

    return m;
}

int main()
{
    Brain brain;

    std::map<std::string, size_t> neuronIds;

    auto const m{brain.addMatrices<Eigen::MatrixXi>()};
    neuronIds.insert(m.begin(), m.end());

    Eigen::MatrixXi input{matrix()};
    Eigen::MatrixXi output{matrix()};

    std::cout << "input" << std::endl;
    std::cout << input << std::endl;
    std::cout << "output" << std::endl;
    std::cout << output << std::endl;

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

    for (auto const& v : values)
    {
        auto const name{std::to_string(v)};
        ids[name] = brain.addNeuron(Neuron<int>{[v] () { return v; }, name, "ints.variables"});
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

    while (heuristic(previousOutput, output) > eps)
    {
        if ((int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() > timeout)
            break;

        if (connections.size())
        {
            std::cout << "step" << std::endl;
            std::cout << std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connections.front())) << std::endl;
        }

        brain.neuronTimeout = learnTimeout / 8;
        connections = brain.learn(output, 1, -1, learnTimeout);
        brain.setConnections(connections);

        auto const newOutput{std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connections.front()))};

        if (heuristic(previousOutput, newOutput) < eps)
            learnTimeout *= 2;
        else if (learnTimeout > 1000)
            learnTimeout /= 2;

        previousOutput = newOutput;
    }

    std::cout << "Passed in " << (int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() << "ms" << std::endl;

    if (connections.size())
    {
        std::cout << "result" << std::endl;
        std::cout << std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connections.front())) << std::endl;
    }

    return 0;
}
