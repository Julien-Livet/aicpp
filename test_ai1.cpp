#include <iostream>

#include "Brain.h"

int main()
{
    Brain brain;

    std::map<std::string, size_t> neuronIds;

    {
        auto const m{brain.addInts<int>()};
        neuronIds.insert(m.begin(), m.end());
    }

    {
        auto const m{brain.addStrings<std::string>()};
        neuronIds.insert(m.begin(), m.end());
    }

    for (int i = 0; i < 10; ++i)
    {
        auto const m{brain.addInt<int>(i)};
        neuronIds.insert(m.begin(), m.end());
    }

    brain.deactivateAllOriginNeurons();
    brain.activateString("103");

    auto const connections{brain.learn(std::string{"103"})};

    std::cout << "Found output: " << std::any_cast<std::string>(brain.connectionOutput(connections.front())) << std::endl;

    return 0;
}
