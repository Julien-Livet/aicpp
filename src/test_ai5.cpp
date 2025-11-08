#include <iostream>

#include "aicpp/Brain.h"

using namespace aicpp;

int main()
{
    Brain brain;

    std::map<std::string, size_t> neuronIds;

    auto const m{brain.addMatrices<Eigen::MatrixXi>()};
    neuronIds.insert(m.begin(), m.end());

    Eigen::Vector3i w{-2, 0, -1};
    Eigen::Vector3i x{-1, 2, 3};
    Eigen::Vector3i y{4, -6, 5};
    Eigen::Vector3i z{9, 8, -7};

    neuronIds["w"] = brain.addNeuron(Neuron<Eigen::MatrixXi>([&w] () { return w; }, "w"));
    neuronIds["x"] = brain.addNeuron(Neuron<Eigen::MatrixXi>([&x] () { return x; }, "x"));
    neuronIds["y"] = brain.addNeuron(Neuron<Eigen::MatrixXi>([&y] () { return y; }, "y"));
    neuronIds["z"] = brain.addNeuron(Neuron<Eigen::MatrixXi>([&z] () { return z; }, "z"));

    //Eigen::MatrixXi const output{x + y};
    //Eigen::MatrixXi const output{x + y.cwiseProduct(z)};
    Eigen::MatrixXi const output{w.cwiseProduct(x) + y.cwiseProduct(z)};

    std::cout << "Given output: " << output.transpose() << std::endl;

    auto const connections{brain.learn(output)};

    std::cout << "Found output: " << std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connections.front())).transpose() << std::endl;

    return 0;
}
