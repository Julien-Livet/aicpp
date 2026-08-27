#include <cassert>
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <print>
#include <random>
#include <set>
#include <thread>

#include "aicpp/Brain.h"
#include "aicpp/Connection.h"
#include "aicpp/Chess.h"
#include "aicpp/Neuron.h"
#include "aicpp/ChessDslSystem.h"

using namespace aicpp;

using Pair = std::pair<chess::Board, Connection>;

struct PairLess
{
    bool operator()(Pair const& x, Pair const& y) const
    {
        return x.second.hash() < y.second.hash();
    }
};

Connection buildConnection(std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& variableNeuronsByOutputType,
                           std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& neuronsByOutputType,
                           size_t depth, std::type_index const& type)
{
    std::random_device rd;

    if (!depth)
    {
        std::uniform_int_distribution<size_t> dist(0, variableNeuronsByOutputType.at(type).size() - 1);
        Neuron const& neuron{variableNeuronsByOutputType.at(type).at(dist(rd))};

        assert(neuron.inputTypes().empty());

        return Connection{neuron, {}};
    }

    std::map<std::string, std::vector<std::reference_wrapper<Neuron const> > > namedNeurons;

    for (auto const& neuron : neuronsByOutputType.at(type))
        namedNeurons[neuron.get().name()].emplace_back(neuron);

    std::vector<std::vector<std::reference_wrapper<Neuron const> > > nn;
    nn.reserve(namedNeurons.size());

    for (auto const& [n, v] : namedNeurons)
        nn.emplace_back(v);

    std::shuffle(nn.begin(), nn.end(), rd);
    
    while (nn.size())
    {
        auto neurons{nn.back()};
        nn.pop_back();

        std::shuffle(neurons.begin(), neurons.end(), rd);

        while (neurons.size())
        {
            auto const neuron{neurons.back()};
            neurons.pop_back();

            try
            {
                std::vector<std::any> inputs;

                for (auto const& inputType : neuron.get().inputTypes())
                {
                    Connection const& inputConnection{buildConnection(variableNeuronsByOutputType, neuronsByOutputType, depth - 1, inputType)};
                    inputs.emplace_back(inputConnection);
                }

                return Connection{neuron.get(), inputs};
            }
            catch (std::exception const&)
            {
                break; //TODO: to remove?
            }
        }

        break; //TODO: to remove?
    }

    throw std::runtime_error{"Wrong connection"};
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <depth> <count>" << std::endl;

        return 1;
    }

    size_t const depth{static_cast<size_t>(std::stoi(argv[1]))};
    size_t const count{static_cast<size_t>(std::stoi(argv[2]))};

    auto const variables{chessDslVariableNeurons()};
    auto const primitives{chessDslPrimitiveNeurons()};

    std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > variableNeuronsByOutputType;

    for (auto const& variable : variables)
        variableNeuronsByOutputType[variable.second.outputType()].emplace_back(variable.second);

    Neuron boardNeuron{"board", chess::initialBoard, std::vector<std::type_index>{}, typeid(chess::Board)};

    variableNeuronsByOutputType[boardNeuron.outputType()].emplace_back(boardNeuron);

    std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > primitiveNeuronsByOutputType;

    for (auto const& primitive : primitives)
        primitiveNeuronsByOutputType[primitive.second.outputType()].emplace_back(primitive.second);

    std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > neuronsByOutputType{variableNeuronsByOutputType};

    for (auto const& [i, v] : primitiveNeuronsByOutputType)
        neuronsByOutputType[i].insert(neuronsByOutputType[i].end(), v.begin(), v.end());

    std::set<Pair, PairLess> pairs;
    std::mutex mutex;

    auto const addConnection = [&mutex, &pairs, &variableNeuronsByOutputType, &neuronsByOutputType, &boardNeuron, depth, count] () {
        if (pairs.size() >= count)
            return;

        try
        {
            auto const connection{buildConnection(variableNeuronsByOutputType, neuronsByOutputType, depth, typeid(chess::Board))};

            assert(connection.neuron().outputType() == typeid(chess::Board));

            auto const program{connection.string()};

            if (!program.contains("(board)") && !program.contains("(board, ") && !program.contains(", I,") && !program.contains(", board)"))
                return;

            auto const output{connection.output()};

            if (output.has_value())
            {
                auto const board{std::any_cast<chess::Board>(output)};
                bool add{true};

                if (board == std::any_cast<chess::Board>(boardNeuron.function()({})))
                    add = false;

                if (add)
                {
                    std::lock_guard<std::mutex> lock(mutex);

                    pairs.emplace(board, std::move(connection));
                }
            }
        }
        catch (std::exception const&)
        {
        }
    };

    std::vector<std::thread> threads;

    while (pairs.size() < count)
    {
        if (threads.size() == std::thread::hardware_concurrency())
        {
            for (auto& thread : threads)
                thread.join();

            threads.clear();
        }

        threads.emplace_back(addConnection);
    }

    for (auto& thread : threads)
        thread.join();

    std::set<std::string> strings;

    for (auto const& pair : pairs)
        strings.emplace(pair.second.string());

    for (auto const& s : strings)
        std::println("{0}", s);

    std::vector<std::reference_wrapper<Neuron const> > neurons;

    for (auto const& [type, v] : variableNeuronsByOutputType)
        neurons.insert(neurons.end(), v.begin(), v.end());

    for (auto const& [type, v] : primitiveNeuronsByOutputType)
        neurons.insert(neurons.end(), v.begin(), v.end());

    Brain brain{neurons};

    for (auto const& pair : pairs)
        brain.addConnection(pair.second);

    {
        auto const value{brain.toJson()};

        std::ofstream ofs{"chess_dsl_dataset_connections.json"};

        ofs << boost::json::serialize(value);
    }

    {
        std::vector<chess::Board> boards;

        for (auto const& connection : brain.connections())
        {
            for (auto const& pair : pairs)
            {
                if (pair.second == connection)
                {
                    boards.emplace_back(pair.first);
                    break;
                }
            }
        }        

        boost::json::object obj;
        boost::json::array json_boards;

        for (auto const& board : boards)
        {
            boost::json::array json_board;
/**
            for (auto const& row : grid)
            {
                boost::json::array json_row;

                for (auto const& val : row)
                    json_row.push_back(val);

                json_grid.push_back(json_row);
            }

            json_grids.push_back(json_grid);**/
        }

        obj["boards"] = json_boards;
        boost::json::value const value = obj;

        std::ofstream ofs{"chess_dsl_dataset_boards.json"};

        ofs << boost::json::serialize(value);
    }

    return 0;
}
