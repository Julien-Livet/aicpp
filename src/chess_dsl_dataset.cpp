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

void printBoard(chess::Board const& board)
{
    std::vector<std::vector<char> > grid(8, std::vector<char>(8, '.'));

    for (auto const& piece : board.first)
    {
        char c{'.'};

        switch (std::get<1>(piece))
        {
            case chess::Pawn:
                c = 'P';
                break;

            case chess::Knight:
                c = 'K';
                break;

            case chess::Bishop:
                c = 'B';
                break;


            case chess::Rook:
                c = 'R';
                break;

            case chess::Queen:
                c = 'Q';
                break;


            case chess::King:
                c = 'X';
                break;
        }

        if (std::get<0>(piece) == chess::Black)
            c = std::tolower(c);

        auto const position{std::get<2>(piece)};

        grid[std::get<1>(position) - 1][std::get<0>(position) - 1] = c;
    }

    std::reverse(grid.begin(), grid.end());

    for (auto const& row : grid)
    {
        for (auto const& c : row)
            std::cout << c;

        std::cout << std::endl;
    }
}

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

            auto const& inputTypes{neuron.get().inputTypes()};

            try
            {
                if (neuron.get().name() == "mv")
                {
                    std::vector<std::any> inputs;

                    Connection const& inputConnection{buildConnection(variableNeuronsByOutputType, neuronsByOutputType, depth - 1, inputTypes[0])};
                    inputs.emplace_back(inputConnection);

                    auto const board{std::any_cast<chess::Board>(inputConnection.output())};
                    chess::Color const color{static_cast<bool>(depth % 2)};

                    auto const positions{chess::movablePieces(board, color)};

                    if (positions.empty() || chess::inCheck(board, chess::Color{!static_cast<bool>(color)}))
                        throw std::runtime_error{"Wrong connection"};

                    std::uniform_int_distribution<size_t> distribution1(0, positions.size() - 1);

                    auto it1{positions.begin()};
                    std::advance(it1, distribution1(rd));

                    auto const from{*it1};
                    auto const moves{std::any_cast<std::set<chess::Position> >(chess::mvs({board, from}))};

                    std::uniform_int_distribution<size_t> distribution2(0, moves.size() - 1);

                    auto it2{moves.begin()};
                    std::advance(it2, distribution2(rd));

                    auto const to{*it2};

                    auto posConnection =
                    [&] (chess::Position const& position) -> Connection
                    {
                        Neuron const* columnNeuron{nullptr};

                        for (auto const& neuron : variableNeuronsByOutputType.at(typeid(chess::Column)))
                        {
                            if (std::any_cast<chess::Column>(neuron.get().function()({})) == std::get<0>(position))
                            {
                                columnNeuron = &neuron.get();
                                break;
                            }
                        }

                        assert(columnNeuron);

                        Neuron const* rowNeuron{nullptr};

                        for (auto const& neuron : variableNeuronsByOutputType.at(typeid(chess::Row)))
                        {
                            if (std::any_cast<chess::Row>(neuron.get().function()({})) == std::get<1>(position))
                            {
                                rowNeuron = &neuron.get();
                                break;
                            }
                        }

                        assert(rowNeuron);

                        Neuron const* positionNeuron{nullptr};

                        for (auto const& neuron : neuronsByOutputType.at(typeid(chess::Position)))
                        {
                            if (neuron.get().name() == "pos")
                            {
                                positionNeuron = &neuron.get();
                                break;
                            }
                        }

                        assert(positionNeuron);

                        return Connection{*positionNeuron,
                                          {Connection{*columnNeuron, {}},
                                           Connection{*rowNeuron, {}}}};
                    };

                    inputs.emplace_back(posConnection(from));
                    inputs.emplace_back(posConnection(to));

                    return Connection{neuron.get(), inputs};
                }
                else
                {
                    std::vector<std::any> inputs;

                    for (auto const& inputType : inputTypes)
                    {
                        Connection const& inputConnection{buildConnection(variableNeuronsByOutputType, neuronsByOutputType, depth - 1, inputType)};
                        inputs.emplace_back(inputConnection);
                    }

                    return Connection{neuron.get(), inputs};
                }
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

    Neuron boardNeuron{"b", chess::initialBoard, std::vector<std::type_index>{}, typeid(chess::Board)};

    //printBoard(std::any_cast<chess::Board>(boardNeuron.function()({})));

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

            if (!program.contains("(b)") && !program.contains("(b, ") && !program.contains(", b,") && !program.contains(", b)"))
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
