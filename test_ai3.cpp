#include <iostream>

#include "Brain.h"

int main()
{
    Brain brain;

    std::map<std::string, size_t> neuronIds;

    auto const m{brain.addInts<int>()};
    neuronIds.insert(m.begin(), m.end());

    int x{16};
    int y{25};
    int z{34};

    neuronIds["x"] = brain.addNeuron(Neuron<int>([&x] () { return x; }, "x"));
    neuronIds["y"] = brain.addNeuron(Neuron<int>([&y] () { return y; }, "y"));
    neuronIds["z"] = brain.addNeuron(Neuron<int>([&z] () { return z; }, "z"));

    //std::cout << "Given output: " << x * y << std::endl;
    std::cout << "Given output: " << x * y + z << std::endl;

    //auto const connections{brain.learn(x * y)};
    auto const connections{brain.learn(x * y + z)};

    std::cout << "Found output: " << std::any_cast<int>(brain.connectionOutput(connections.front())) << std::endl;

    bool xProvided{false};
    bool yProvided{false};
    bool zProvided{false};

    std::get<Neuron<int> >(brain.neuron(neuronIds["x"])).function =
        [&x, &xProvided] () -> int
        {
            if (xProvided)
                return x;

            std::cout << "x? ";
            std::cin >> x;
            xProvided = true;

            return x;
        };
    std::get<Neuron<int> >(brain.neuron(neuronIds["y"])).function =
        [&y, &yProvided] () -> int
        {
            if (yProvided)
                return y;

            std::cout << "y? ";
            std::cin >> y;
            yProvided = true;

            return y;
        };
    std::get<Neuron<int> >(brain.neuron(neuronIds["z"])).function =
        [&z, &zProvided]() -> int
        {
            if (zProvided)
                return z;

            std::cout << "z? ";
            std::cin >> z;
            zProvided = true;

            return z;
        };

    std::cout << "New output: " << std::any_cast<int>(brain.connectionOutput(connections.front())) << std::endl;

    return 0;
}
