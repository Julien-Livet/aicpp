#include <cassert>
#include <mutex>
#include <random>
#include <thread>

#include "aicpp/Connection.h"
#include "aicpp/DslSystem.h"

using namespace aicpp;

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <depth> <count>" << std::endl;

        return 1;
    }

    size_t const depth{static_cast<size_t>(std::stoi(argv[1]))};
    size_t const count{static_cast<size_t>(std::stoi(argv[2]))};

    auto const variables{dslVariableNeurons()};
    auto const primitives{dslPrimitiveNeurons()};

    std::map<std::type_index, std::vector<Neuron> > variableNeuronsByOutputType;

    for (auto const& variable : variables)
        variableNeuronsByOutputType[variable.second.outputType()].emplace_back(variable.second);

    std::map<std::type_index, std::vector<Neuron> > primitiveNeuronsByOutputType;

    for (auto const& primitive : primitives)
        primitiveNeuronsByOutputType[primitive.second.outputType()].emplace_back(primitive.second);

    std::set<Connection> connections;

    auto const buildConnection = [variableNeuronsByOutputType, primitiveNeuronsByOutputType] (size_t depth, std::type_index const& type) -> Connection {
        std::random_device rd;

        if (!depth)
        {
            std::uniform_int_distribution<size_t> dist(0, variableNeuronsByOutputType.at(type).size() - 1);
            Neuron const& neuron{variableNeuronsByOutputType.at(type).at(dist(rd))};

            assert(neuron.inputTypes().empty());

            return Connection{neuron, {}};
        }

        std::map<std::type_index, std::vector<Connection> > neuronsByOutputType{variableNeuronsByOutputType};
        neuronsByOutputType.insert(primitiveNeuronsByOutputType.begin(), primitiveNeuronsByOutputType.end());

        std::uniform_int_distribution<size_t> dist(0, neuronsByOutputType.at(type).size() - 1);
        Neuron const& neuron{neuronsByOutputType.at(type).at(dist(rd))};

        std::vector<std::any> inputs;

        for (auto const& inputType : neuron.inputTypes())
        {
            Connection const& inputConnection{buildConnection(depth - 1, inputType)};
            inputs.emplace_back(inputConnection);
        }

        return Connection{neuron, inputs};
    };

    std::mutex mutex;

    auto const addConnection = [&mutex, &connections, depth, count] () {
        if (connections.size() >= count)
            return;

        try
        {
            auto const connection{buildConnection(depth, typeid(Hodel::Grid))};

            //...Check connection result

            std::lock_guard<std::mutex> lock(mutex);
            connections.emplace(connection);
        }
        catch (std::exception const&)
        {
        }
    };

    std::vector<std::thread> threads;

    while (connections.size() < count)
    {
        if (threads.size() < std::thread::hardware_concurrency())
            threads.emplace_back(addConnection);
    }

    return 0;
}
