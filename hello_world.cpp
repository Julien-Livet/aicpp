#include <iostream>

#include "Brain.h"

int main()
{
    Brain brain;

    std::map<std::string, size_t> neuronIds;

    auto const m{brain.addStrings<std::string>()};
    neuronIds.insert(m.begin(), m.end());

    std::string x{"Hello "};
    std::string name{"world"};
    std::string z{"! How are you?"};

    neuronIds["x"] = brain.addNeuron(Neuron<std::string>([&x] () { return x; }, "x"));
    neuronIds["name"] = brain.addNeuron(Neuron<std::string>([&name] () { return name; }, "name"));
    neuronIds["z"] = brain.addNeuron(Neuron<std::string>([&z] () { return z; }, "z"));

    auto const connections{brain.learn(x + name + z)};

    std::cout << std::any_cast<std::string>(brain.connectionOutput(connections.front())) << std::endl;

    bool nameProvided{false};

    std::get<Neuron<std::string> >(brain.neuron(neuronIds["name"])).function =
        [&name, &nameProvided] () -> std::string
        {
            if (nameProvided)
                return name;

            std::cout << "What is your name? ";
            std::cin >> name;
            nameProvided = true;

            return name;
        };

    std::cout << std::any_cast<std::string>(brain.connectionOutput(connections.front())) << std::endl;

    return 0;
}
