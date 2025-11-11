#ifndef AICPP_BRAIN_H
#define AICPP_BRAIN_H

#include <cctype>
#include <chrono>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <tuple>

#include <boost/algorithm/string.hpp>

#include <Eigen/Dense>

#include "aicpp/Connection.h"
#include "aicpp/Neuron.h"
#include "aicpp/utility.h"

namespace aicpp
{
    template <typename S, typename T>
    double cost(double initCost, S const& val, T const& target)
    {
        return std::abs(initCost + std::abs(val - target));
    }

    template <typename S, typename T>
    double heuristic(S const& val, T const& target)
    {
        if constexpr (std::is_same_v<S, std::any>)
        {
            if (val.type() == typeid(char))
                return heuristic(std::any_cast<char>(val), target);
            else if (val.type() == typeid(double))
                return heuristic(std::any_cast<double>(val), target);
            else if (val.type() == typeid(Eigen::MatrixXd))
                return heuristic(std::any_cast<Eigen::MatrixXd>(val), target);
            else if (val.type() == typeid(Eigen::MatrixXf))
                return heuristic(std::any_cast<Eigen::MatrixXf>(val), target);
            else if (val.type() == typeid(Eigen::MatrixXi))
                return heuristic(std::any_cast<Eigen::MatrixXi>(val), target);
            else if (val.type() == typeid(float))
                return heuristic(std::any_cast<float>(val), target);
            else if (val.type() == typeid(int))
                return heuristic(std::any_cast<int>(val), target);
            else if (val.type() == typeid(long))
                return heuristic(std::any_cast<long>(val), target);
            else if (val.type() == typeid(std::pair<int, int>))
                return heuristic(std::any_cast<std::pair<int, int> >(val), target);
            else if (val.type() == typeid(std::vector<std::pair<int, int> >))
                return heuristic(std::any_cast<std::vector<std::pair<int, int> > >(val), target);
            else if (val.type() == typeid(std::string))
                return heuristic(std::any_cast<std::string>(val), target);
        }
        else if constexpr (std::is_same_v<S, std::variant<bool, char, double, Eigen::MatrixXd, Eigen::MatrixXf, Eigen::MatrixXi, float, int, long, std::pair<int, int>, std::string, std::vector<std::pair<int, int> > > >)
        {
            if (auto const* v = std::get_if<bool>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<char>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<double>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<Eigen::MatrixXd>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<Eigen::MatrixXf>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<Eigen::MatrixXi>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<float>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<int>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<long>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<std::pair<int, int> >(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<std::string>(&val))
                return heuristic(*v, target);
            else if (auto const* v = std::get_if<std::vector<std::pair<int, int> > >(&val))
                return heuristic(*v, target);
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            if constexpr (is_string_convertible_v<S>)
            {
                double cost{std::is_same_v<S, std::string> ? 0.0 : 1.0};

                auto const s{toString(val)};
                auto a{s}, b{target};

                if (a.find(b) != std::string::npos)
                    std::swap(a, b);

                if (!a.empty() && b.find(a) != std::string::npos)
                {
                    std::vector<std::string> matches;

                    return cost + 1.0 - 1.0 / boost::algorithm::find_all(matches, b, a).size() + 1.0 / (1.0 + a.size()) - 1 / (1.0 + b.size());
                }

                return cost + 1.0 / (1.0 + a.size()) - 1.0 / (1.0 + b.size()) + levenshtein(a, b);
            }
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            if constexpr (std::is_same_v<S, double>)
                return cost(0.0, val, target);
            else if constexpr (std::is_same_v<S, float>)
                return cost(1.0, val, target);
            else if constexpr (std::is_same_v<S, int>)
                return cost(2.0, val, target);
            else if constexpr (std::is_same_v<S, long>)
                return cost(2.0, val, target);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            if constexpr (std::is_same_v<S, float>)
                return cost(0.0, val, target);
            else if constexpr (std::is_same_v<S, double>)
                return cost(1.0, val, target);
            else if constexpr (std::is_same_v<S, int>)
                return cost(2.0, val, target);
            else if constexpr (std::is_same_v<S, long>)
                return cost(2.0, val, target);
        }
        else if constexpr (std::is_same_v<T, int>)
        {
            if constexpr (std::is_same_v<S, int>)
                return cost(0.0, val, target);
            else if constexpr (std::is_same_v<S, long>)
                return cost(1.0, val, target);
            else if constexpr (std::is_same_v<S, double>)
                return cost(2.0, val, target);
            else if constexpr (std::is_same_v<S, float>)
                return cost(2.0, val, target);
        }
        else if constexpr (std::is_same_v<T, long>)
        {
            if constexpr (std::is_same_v<S, long>)
                return cost(0.0, val, target);
            else if constexpr (std::is_same_v<S, int>)
                return cost(1.0, val, target);
            else if constexpr (std::is_same_v<S, double>)
                return cost(2.0, val, target);
            else if constexpr (std::is_same_v<S, float>)
                return cost(2.0, val, target);
        }
        else if constexpr (std::is_same_v<T, Eigen::MatrixXd>)
        {
            if constexpr (std::is_same_v<S, Eigen::MatrixXd>)
            {
                if (!(val.rows() == target.rows() && val.cols() == target.cols()))
                    return 100.0 + std::abs(val.sum() - target.sum());

                return std::abs((val - target).norm());
            }
        }
        else if constexpr (std::is_same_v<T, Eigen::MatrixXf>)
        {
            if constexpr (std::is_same_v<S, Eigen::MatrixXf>)
            {
                if (!(val.rows() == target.rows() && val.cols() == target.cols()))
                    return 100.0 + std::abs(val.sum() - target.sum());

                return std::abs((val - target).norm());
            }
        }
        else if constexpr (std::is_same_v<T, Eigen::MatrixXi>)
        {
            if constexpr (std::is_same_v<S, Eigen::MatrixXi>)
            {
                if (!(val.rows() == target.rows() && val.cols() == target.cols()))
                    return 100.0 + std::abs(val.sum() - target.sum());

                return std::abs((val.template cast<double>() - target.template cast<double>()).norm());
            }
        }

        return 1000.0; //return std::abs(std::hash<S>() - std::hash<T>());
    }

    struct LessTupleCost
    {
        bool operator()(std::tuple<ConnectionOutput, double, Connection, size_t> const& x,
                        std::tuple<ConnectionOutput, double, Connection, size_t> const& y) const
        {
            return std::get<1>(x) < std::get<1>(y);
        }
    };

    struct LessTupleHash
    {
        bool operator()(std::tuple<ConnectionOutput, double, Connection, size_t> const& x,
                        std::tuple<ConnectionOutput, double, Connection, size_t> const& y) const
        {
            return std::get<3>(x) < std::get<3>(y);
        }
    };

    class Brain
    {
        public:
            int neuronTimeout = -1;

            Brain() = default;
            std::map<size_t, AnyNeuron> const& neurons() const;
            std::map<std::string, bool> const& modules() const;
            auto const& connections() const;
            size_t addNeuron(AnyNeuron const& neuron);
            void activateAllModules();
            void deactivateAllModules();
            void deactivateModules(std::vector<std::string> const& modules);
            void deactivateModule(std::string const& module);
            void activateModule(std::string const& module);
            void activateModules(std::vector<std::string> const& modules);
            ConnectionOutput connectionOutput(Connection const& connection) const;
            bool activatedNeuron(size_t id) const;
            void deactivateNeuron(size_t id);
            void activateNeuron(size_t id);
            void activateAllOriginNeurons();
            void deactivateAllOriginNeurons();
            void activateString(std::string const& s);
            void deactivateString(std::string const& s);
            AnyNeuron const& neuron(size_t id) const;
            AnyNeuron& neuron(size_t id);
            void addConnection(Connection const& connection);
            std::string neuronName(size_t id) const;
            void clearConnections();

            template <typename Container>
            void addConnections(Container const& connections)
            {
                for (auto const& connection : connections)
                    addConnection(connection);
            }

            template <typename Container>
            void setConnections(Container const& connections)
            {
                connections_.clear();
                addConnections(connections);
            }

            template <typename Value>
            std::vector<Connection> learn(Value const& value, size_t answerNumber = 1, int maxConns = -1, size_t timeout = 20 * 1000)
            {
                auto anyToHash{
                    [] (std::any const& x)
                    {
                        return variantToHash(anyToVariant<bool, char, double, Eigen::MatrixXd, Eigen::MatrixXf, Eigen::MatrixXi, float, int, long, std::pair<int, int>, std::pair<size_t, size_t>, std::string, std::vector<std::pair<int, int> >>(x));
                    }
                };

                std::vector<std::tuple<ConnectionOutput, double, Connection, size_t> > startAvailable;

                std::vector<Connection> activatedConnections;
                activatedConnections.reserve(connections_.size());

                for (auto const& connection : connections_)
                {
                    if (connection.activated)
                    {
                        activatedConnections.emplace_back(connection);

                        auto const x{connectionOutput(connection)};
                        auto const h{anyToHash(x)};
                        startAvailable.emplace_back(std::make_tuple(x, heuristic(x, value), connection, h));
                    }
                }

                std::vector<size_t> originNeuronIds;
                std::vector<size_t> normalNeuronIds;
                std::vector<size_t> activatedNeuronIds;
                activatedNeuronIds.reserve(neurons_.size());

                for (auto const& p : neurons_)
                {
                    if (std::visit([] (auto const& neuron) { return neuron.activated; }, p.second))
                    {
                        activatedNeuronIds.emplace_back(p.first);

                        std::visit(
                            [this, &startAvailable, &originNeuronIds, &normalNeuronIds, p, value, anyToHash]
                            (auto const& neuron)
                            {
                                if constexpr (requires { neuron.output(); })
                                {
                                    originNeuronIds.emplace_back(p.first);

                                    auto const x{neuron.output()};
                                    auto const h{anyToHash(x)};
                                    startAvailable.emplace_back(std::make_tuple(x, heuristic(x, value), Connection(std::vector<ConnectionInput>{}, p.first), h));
                                }
                                else
                                    normalNeuronIds.emplace_back(p.first);
                            },
                            p.second);
                    }
                }

                std::sort(startAvailable.begin(), startAvailable.end(), [] (auto const& x, auto const& y) { return std::get<1>(x) < std::get<1>(y); });

                std::vector<Connection> connections;

                if (startAvailable.empty())
                    return connections;

                constexpr double eps{1.0e-6};

                for (auto const& t : startAvailable)
                {
                    if (std::get<1>(t) < eps)
                        connections.emplace_back(std::get<2>(t));
                    else
                        break;
                }

                double bestCost{std::get<1>(startAvailable.front())};
                Connection bestConnection{std::get<2>(startAvailable.front())};

                std::priority_queue<std::tuple<ConnectionOutput, double, Connection, size_t>,
                                    std::vector<std::tuple<ConnectionOutput, double, Connection, size_t> >,
                                    LessTupleCost> frontier;
                frontier.emplace(startAvailable.front());
                auto time{std::chrono::system_clock::now()};
                std::set<size_t> visited;
                size_t counter{0};

                while (frontier.size() && connections.size() < answerNumber)
                {
                    if ((int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() > timeout)
                        break;

                    auto const top{frontier.top()};
                    frontier.pop();

                    if (visited.find(std::get<3>(top)) != visited.end())
                        continue;

                    visited.emplace(std::get<3>(top));

                    std::set<std::tuple<ConnectionOutput, double, Connection, size_t>, LessTupleHash> av;

                    for (auto const& id : originNeuronIds)
                    {
                        std::visit(
                            [&av, id, value, anyToHash]
                            (auto const& neuron)
                            {
                                if constexpr (requires { neuron.output(); })
                                {
                                    auto const v{neuron.output()};
                                    ConnectionOutput const x{neuron.output()};
                                    auto const h{anyToHash(x)};
                                    av.emplace(std::make_tuple(x, heuristic(x, value), Connection(std::vector<ConnectionInput>{}, id), h));
                                }
                            },
                            neuron(id));
                    }

                    for (auto const& connection : activatedConnections)
                    {
                        auto const x{connectionOutput(connection)};
                        auto const h{anyToHash(x)};
                        av.emplace(std::make_tuple(x, heuristic(x, value), connection, h));
                    }

                    if (maxConns > 0)
                    {
                        auto it{av.begin()};

                        std::advance(it, std::min(maxConns, (int)av.size()));

                        av.erase(it, av.end());
                    }

                    for (auto const& id : normalNeuronIds)
                    {
                        if ((size_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() > timeout)
                            break;

                        auto const n{neuron(id)};

                        if (connections.size() >= answerNumber)
                            break;

                        auto const inputTypes{std::visit(
                            [] (auto const& neuron)
                            {
                               return neuron.inputTypes();
                            },
                            n)};
                        auto const neuronTimeout{std::visit([] (auto const& neuron)
                            {
                                return neuron.limitationTimeout;
                            },
                            n)};
                        std::set<std::type_info const*> const s{inputTypes.begin(), inputTypes.end()};
                        std::vector<std::tuple<ConnectionOutput, double, Connection, size_t> > new_av;
                        new_av.reserve(av.size());

                        for (auto const& t : av)
                        {
                            for (auto const& ti : s)
                            {
                                if (std::get<0>(t).type() == *ti)
                                {
                                    new_av.emplace_back(t);
                                    break;
                                }
                            }
                        }

                        auto const neuronTime{std::chrono::system_clock::now()};

                        for (auto const& combo : cartesianProduct(new_av, inputTypes.size()))
                        {
                            if ((size_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() > timeout)
                                break;

                            if (neuronTimeout > 0)
                            {
                                if ((int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(neuronTime)).count() > neuronTimeout)
                                    break;
                            }
                            else if (this->neuronTimeout > 0)
                            {
                                if ((int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(neuronTime)).count() > this->neuronTimeout)
                                    break;
                            }

                            bool ok{true};
                            std::vector<ConnectionOutput> args;
                            args.reserve(inputTypes.size());
                            std::vector<ConnectionInput> provs;
                            provs.reserve(inputTypes.size());

                            for (size_t i{0}; i < inputTypes.size(); ++i)
                            {
                                if (*inputTypes[i] != std::get<0>(combo[i]).type())
                                {
                                    ok = false;
                                    break;
                                }

                                args.emplace_back(std::get<0>(combo[i]));
                                provs.emplace_back(std::get<2>(combo[i]));
                            }

                            if (!ok)
                                continue;

                            try
                            {
                                auto const newValue{std::visit(
                                    [args] (auto const& neuron)
                                    {
                                        return ConnectionOutput{neuron.output(args)};
                                    },
                                    n)};

                                auto const cost{heuristic(newValue, value)};
                                Connection const newConnection{provs, id};
                                activatedConnections.emplace_back(newConnection);

                                if (cost < bestCost)
                                {
                                    time = std::chrono::system_clock::now();
                                    bestCost = cost;
                                    bestConnection = activatedConnections.back();
                                }

                                if (cost < eps)
                                {
                                    connections.emplace_back(newConnection);

                                    if (connections.size() >= answerNumber)
                                        break;
                                }

                                //auto const h{anyToHash(newValue))};
                                auto const h{counter++};
                                frontier.emplace(std::make_tuple(newValue, std::get<1>(top) + cost, newConnection, h));
                            }
                            catch (std::exception const&)
                            {
                            }
                        }
                    }
                }

                if (connections.empty())
                    connections.emplace_back(bestConnection);

                std::vector<std::pair<size_t, double> > v;

                for (size_t i{0}; i < connections.size(); ++i)
                    v.emplace_back(std::make_pair(i, heuristic(connectionOutput(connections[i]), value)));

                std::sort(v.begin(), v.end(), [] (auto const& x, auto const& y) { return x.second < y.second; });

                auto tmp{connections};

                for (size_t i{0}; i < v.size(); ++i)
                    tmp[i] = connections[v[i].first];

                connections = tmp;

                addConnections(connections);

                return connections;
            }

            template <typename String>
            std::map<std::string, size_t> addStrings()
            {
                std::map<std::string, size_t> neuronIds;

                neuronIds[std::string{"add_"} + typeid(String).name()] = addNeuron(Neuron<String, String, String>{[] (String const& x, String const& y) { return x + y; }, std::string{"add_"} + typeid(String).name(), "strings"});
                neuronIds[std::string{"size_"} + typeid(String).name()] = addNeuron(Neuron<int, String>{[] (String const& x) { return (int)x.size(); }, std::string{"size_"} + typeid(String).name(), "strings"});
                neuronIds[std::string{"lower_"} + typeid(String).name()] = addNeuron(Neuron<String, String>{[] (String const& x) { auto s{x}; std::transform(s.begin(), s.end(), s.begin(), ::tolower); return s; }, std::string{"lower_"} + typeid(String).name(), "strings"});
                neuronIds[std::string{"upper_"} + typeid(String).name()] = addNeuron(Neuron<String, String>{[] (String const& x) { auto s{x}; std::transform(s.begin(), s.end(), s.begin(), ::toupper); return s; }, std::string{"upper_"} + typeid(String).name(), "strings"});
                neuronIds[std::string{"pop_back_"} + typeid(String).name()] = addNeuron(Neuron<String, String>{[] (String const& x) { return x.substr(0, x.size() - 1); }, std::string{"pop_back_"} + typeid(String).name(), "strings"});
                neuronIds[std::string{"pop_front_"} + typeid(String).name()] = addNeuron(Neuron<String, String>{[] (String const& x) { return x.substr(1); }, std::string{"pop_front_"} + typeid(String).name(), "strings"});

                return neuronIds;
            }

            std::map<std::string, size_t> addBools()
            {
                std::map<std::string, size_t> neuronIds;

                neuronIds[std::string{"and_"} + typeid(bool).name()] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x & y; }, std::string{"and_"} + typeid(bool).name(), "bools"});
                neuronIds[std::string{"or_"} + typeid(bool).name()] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x | y; }, std::string{"or_"} + typeid(bool).name(), "bools"});
                neuronIds[std::string{"xor_"} + typeid(bool).name()] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x ^ y; }, std::string{"xor_"} + typeid(bool).name(), "bools"});
                neuronIds[std::string{"not_"} + typeid(bool).name()] = addNeuron(Neuron<bool, bool>{[] (bool const& x) { return !x; }, std::string{"complement_"} + typeid(bool).name(), "bools"});
                neuronIds[std::string{typeid(bool).name()} + "_to_string"] = addNeuron(Neuron<std::string, bool>{[] (bool const& x) { std::ostringstream oss; oss << x; return oss.str(); }, std::string{typeid(bool).name()} + "_to_string", "bools"});
                neuronIds[std::string{"string_to_"} + typeid(bool).name()] = addNeuron(Neuron<bool, std::string>{[] (std::string const& s) { std::istringstream iss{s}; bool x; iss >> x; return x; }, std::string{"string_to_"} + typeid(bool).name(), "bools"});
                neuronIds[std::string{"eq_"} + typeid(bool).name()] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x == y; }, std::string{"eq_"} + typeid(bool).name(), "bools"});
                neuronIds[std::string{"ne_"} + typeid(bool).name()] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x != y; }, std::string{"ne_"} + typeid(bool).name(), "bools"});

                return neuronIds;
            }

            template <typename Int>
            std::map<std::string, size_t> addInts()
            {
                std::map<std::string, size_t> neuronIds;

                neuronIds[std::string{"add_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x + y; }, std::string{"add_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"sub_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x - y; }, std::string{"sub_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"mul_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x * y; }, std::string{"mul_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"div_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) -> Int { if (!y) return Int{}; return x / y; }, std::string{"div_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"mod_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) -> Int { if (!y) return Int{}; return x % y; }, std::string{"mod_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"pow_"} + typeid(Int).name()] = addNeuron(Neuron<double, Int, Int>{[] (Int const& x, Int const& y) { return std::pow(x, y); }, std::string{"pow_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"and_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x & y; }, std::string{"and_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"or_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x | y; }, std::string{"or_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"xor_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x ^ y; }, std::string{"xor_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"left_shift_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { if (y < 0) return Int{}; return Int{x << y}; }, std::string{"left_shift_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"right_shift_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { if (y < 0) return Int{}; return Int{x >> y}; }, std::string{"right_shift_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"complement_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int>{[] (Int const& x) { return ~x; }, std::string{"complement_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"abs_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int>{[] (Int const& x) { return std::abs(x); }, std::string{"abs_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"neg_"} + typeid(Int).name()] = addNeuron(Neuron<Int, Int>{[] (Int const& x) { return -x; }, std::string{"neg_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{typeid(Int).name()} + "_to_string"] = addNeuron(Neuron<std::string, Int>{[] (Int const& x) { std::ostringstream oss; oss << x; return oss.str(); }, std::string{typeid(Int).name()} + "_to_string", "ints"});
                neuronIds[std::string{"string_to_"} + typeid(Int).name()] = addNeuron(Neuron<Int, std::string>{[] (std::string const& s) { std::istringstream iss{s}; Int x; iss >> x; return x; }, std::string{"string_to_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"eq_"} + typeid(Int).name()] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x == y; }, std::string{"eq_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"ne_"} + typeid(Int).name()] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x != y; }, std::string{"ne_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"gt_"} + typeid(Int).name()] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x > y; }, std::string{"gt_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"lt_"} + typeid(Int).name()] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x < y; }, std::string{"lt_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"ge_"} + typeid(Int).name()] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x >= y; }, std::string{"ge_"} + typeid(Int).name(), "ints"});
                neuronIds[std::string{"le_"} + typeid(Int).name()] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x <= y; }, std::string{"le_"} + typeid(Int).name(), "ints"});

                return neuronIds;
            }

            template <typename Int>
            std::map<std::string, size_t> addInt(Int const& x)
            {
                std::map<std::string, size_t> neuronIds;

                neuronIds[std::to_string(x)] = addNeuron(Neuron<Int>{[x] () { return x; }, std::to_string(x), std::string{"ints."} + typeid(Int).name() + ".variables"});

                return neuronIds;
            }

            template <typename Real>
            std::map<std::string, size_t> addReals()
            {
                std::map<std::string, size_t> neuronIds;

                neuronIds[std::string{"add_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { return x + y; }, std::string{"add_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"sub_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { return x - y; }, std::string{"sub_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"mul_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { return x * y; }, std::string{"mul_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"div_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { if (!y) return Real{}; return x / y; }, std::string{"div_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"pow_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { return std::pow(x, y); }, std::string{"pow_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"abs_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::abs(x); }, std::string{"abs_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"neg_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return -x; }, std::string{"neg_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{ typeid(Real).name() } + "_to_string"] = addNeuron(Neuron<std::string, Real>{[] (Real const& x) { std::ostringstream oss; oss << x; return oss.str(); }, std::string{typeid(Real).name()} + "_to_string", "reals"});
                neuronIds[std::string{"string_to_"} + typeid(Real).name()] = addNeuron(Neuron<Real, std::string>{[] (std::string const& s) { std::istringstream iss{s}; Real x; iss >> x; return x; }, std::string{"string_to_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"eq_"} + typeid(Real).name()] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x == y; }, std::string{"eq_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"ne_"} + typeid(Real).name()] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x != y; }, std::string{"ne_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"gt_"} + typeid(Real).name()] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x > y; }, std::string{"gt_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"lt_"} + typeid(Real).name()] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x < y; }, std::string{"lt_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"ge_"} + typeid(Real).name()] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x >= y; }, std::string{"ge_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"le_"} + typeid(Real).name()] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x <= y; }, std::string{"le_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"sqrt_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::sqrt(x); }, std::string{"sqrt_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"log_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::log(x); }, std::string{"log_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"exp_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::exp(x); }, std::string{"exp_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"cos_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::cos(x); }, std::string{"cos_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"sin_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::sin(x); }, std::string{"sin_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"tan_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::tan(x); }, std::string{"tan_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"acos_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::acos(x); }, std::string{"acos_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"asin_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::asin(x); }, std::string{"asin_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"atan_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::atan(x); }, std::string{"atan_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"cosh_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::cosh(x); }, std::string{"cosh_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"sinh_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::sinh(x); }, std::string{"sinh_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"tanh_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::tanh(x); }, std::string{"tanh_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"acosh_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::acosh(x); }, std::string{"acosh_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"asinh_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::asinh(x); }, std::string{"asinh_"} + typeid(Real).name(), "reals"});
                neuronIds[std::string{"atanh_"} + typeid(Real).name()] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::atanh(x); }, std::string{"atanh_"} + typeid(Real).name(), "reals"});

                return neuronIds;
            }

            template <typename Real>
            std::map<std::string, size_t> addReal(Real const& x)
            {
                std::map<std::string, size_t> neuronIds;

                neuronIds[std::to_string(x)] = addNeuron(Neuron<Real>{[x] () { return x; }, std::to_string(x), std::string{"reals."} + typeid(Real).name() + ".variables"});

                return neuronIds;
            }

            template <typename Matrix>
            std::map<std::string, size_t> addMatrices()
            {
                std::map<std::string, size_t> neuronIds;

                neuronIds[std::string{"add_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (!(x.rows() == y.rows() && x.cols() == y.cols()) || !x.rows() || !x.cols() || !y.rows() || !y.cols()) return Matrix{}; return Matrix{x + y}; }, std::string{"add_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"add_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a + y; }); }, std::string{"add_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"sub_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (!(x.rows() == y.rows() && x.cols() == y.cols()) || !x.rows() || !x.cols() || !y.rows() || !y.cols()) return Matrix{}; return Matrix{x - y}; }, std::string{"sub_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"sub_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a - y; }); }, std::string{"sub_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"mul_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (!(x.rows() == y.rows() && x.cols() == y.cols()) || !x.rows() || !x.cols() || !y.rows() || !y.cols()) return Matrix{}; return Matrix{x.cwiseProduct(y)}; }, std::string{"mul_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"mul_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a * y; }); }, std::string{"mul_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"div_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (!(x.rows() == y.rows() && x.cols() == y.cols()) || !x.rows() || !x.cols() || !y.rows() || !y.cols() || !y.cwiseAbs().minCoeff()) return Matrix{}; return Matrix{x.cwiseQuotient(y)}; }, std::string{"div_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"div_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { if (!y) return Matrix{}; return Matrix{x.unaryExpr([y] (auto const& a) { return a / y; })}; }, std::string{"div_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"mulmat_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (x.cols() != y.rows() || !x.rows() || !x.cols() || !y.rows() || !y.cols()) return Matrix{}; return Matrix{x * y}; }, std::string{"mulmat_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"abs_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::abs(a); }); }, std::string{"abs_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"neg_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return -x; }, std::string{"neg_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"transpose_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { if (!x.rows() || !x.cols()) return Matrix{}; return Matrix{x.transpose()}; }, std::string{"transpose_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"swapcols_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, int, int>{[] (Matrix const& x, int i, int j) { return swapCols(x, i, j); }, std::string{"swapcols_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"swaprows_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, int, int>{[] (Matrix const& x, int i, int j) { return swapRows(x, i, j); }, std::string{"swaprows_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"fliplr_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return fliplr(x); }, std::string{"fliplr_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"flipud_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return flipud(x); }, std::string{"flipud_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"replace_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar, typename Matrix::Scalar>{[] (Matrix const& a, auto const& x, auto const& y) { return a.unaryExpr([x, y] (auto const& b) { return std::abs(b - x) < 1.0e-6 ? y : b; }); }, std::string{"replace_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"fill_region_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::vector<std::pair<int, int> >, typename Matrix::Scalar>{[] (Matrix const& a, std::vector<std::pair<int, int> > const& region, typename Matrix::Scalar const& x) { return fillRegion(a, region, x); }, std::string{"fill_region_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"fill_region_at_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& x) { return fillRegionAt(a, at, x, true); }, std::string{"fill_region_at_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"fill_region2_at_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& x) { return fillRegionAt(a, at, x, false); }, std::string{"fill_region2_at_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"hline_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, int, typename Matrix::Scalar>{[] (Matrix const& x, int row, typename Matrix::Scalar const& value) { return hline(x, row, value); }, std::string{"hline_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"vline_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, int, typename Matrix::Scalar>{[] (Matrix const& x, int col, typename Matrix::Scalar const& value) { return vline(x, col, value); }, std::string{"vline_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"hlineright_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, std::pair<int, int> const& at, auto const& value) { return hlineright(x, at, value); }, std::string{"hlineright_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"hlineleft_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, std::pair<int, int> const& at, auto const& value) { return hlineleft(x, at, value); }, std::string{"hlineleft_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"vlineup_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, std::pair<int, int> const& at, auto const& value) { return vlineup(x, at, value); }, std::string{"vlineup_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"vlinedown_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, std::pair<int, int> const& at, auto const& value) { return vlinedown(x, at, value); }, std::string{"vlinedown_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"zero_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, std::pair<size_t, size_t> >{[] (std::pair<size_t, size_t> const& size) { return zero<Matrix>(size); }, std::string{"zero_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"ones_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, std::pair<size_t, size_t> >{[] (std::pair<size_t, size_t> const& size) { return ones<Matrix>(size); }, std::string{"ones_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"identity_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, std::pair<size_t, size_t> >{[] (std::pair<size_t, size_t> const& size) { return identity<Matrix>(size); }, std::string{"identity_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"put_value_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, std::pair<int, int> const& at, auto const& value) { return put(x, at, value); }, std::string{"put_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"at_"} + typeid(Matrix).name()] = addNeuron(Neuron<typename Matrix::Scalar, Matrix, std::pair<int, int> >{[] (Matrix const& x, std::pair<int, int> const& pos) { return at(x, pos); }, std::string{"at_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"fill_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& value) { Matrix y{x}; y.fill(value); return y; }, std::string{"fill_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"rot90_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return rot90(x); }, std::string{"rot90_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"trace_"} + typeid(Matrix).name()] = addNeuron(Neuron<typename Matrix::Scalar, Matrix>{[] (Matrix const& x) { return x.trace(); }, std::string{"trace_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"dot_segment_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, std::pair<int, int>, typename Matrix::Scalar, int>{[] (Matrix const& x, std::pair<int, int> const& b, std::pair<int, int> const& e, auto const& v, int d) { return dotSegment(x, b, e, v, d); }, std::string{"dot_segment_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"tile_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::pair<size_t, size_t> >{[] (Matrix const& x, std::pair<size_t, size_t> const& r) { return tile(x, r); }, std::string{"tile_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"put_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix, std::pair<int, int> >{[] (Matrix const& dst, Matrix const& src, std::pair<int, int> const& at) { return put(dst, src, at); }, std::string{"put_"} + typeid(Matrix).name(), "matrices"});
                neuronIds[std::string{"place_region_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, std::vector<std::pair<int, int> >, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& a, std::vector<std::pair<int, int> > const& region, std::pair<int, int> const& at, auto const& x) { return placeRegion(a, region, at, x); }, std::string{"place_region_"} + typeid(Matrix).name(), "matrices"});

                if constexpr (std::is_same_v<Matrix, Eigen::MatrixXi>)
                {
                    neuronIds[std::string{"mod_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { return modMatrix(x, y); }, std::string{"mod_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"mod_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { if (!y) return Matrix{}; return Matrix{x.unaryExpr([y] (auto const& a) { return a % y; })}; }, std::string{"mod_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"and_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { return andMatrix(x, y); }, std::string{"and_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"and_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a & y; }); }, std::string{"and_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"or_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { return orMatrix(x, y); }, std::string{"or_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"or_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a | y; }); }, std::string{"or_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"xor_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { return xorMatrix(x, y); }, std::string{"xor_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"xor_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a ^ y; }); }, std::string{"xor_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"invert_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return ~a; }); }, std::string{"invert_"} + typeid(Matrix).name(), "matrices"});
                }
                else
                {
                    neuronIds[std::string{"sqrt_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::sqrt(a); }); }, std::string{"sqrt_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"log_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::log(a); }); }, std::string{"log_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"exp_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::exp(a); }); }, std::string{"exp_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"cos_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::cos(a); }); }, std::string{"cos_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"sin_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::sin(a); }); }, std::string{"sin_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"tan_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::tan(a); }); }, std::string{"tan_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"acos_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::acos(a); }); }, std::string{"acos_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"asin_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::asin(a); }); }, std::string{"asin_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"atan_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::atan(a); }); }, std::string{"atan_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"cosh_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::cosh(a); }); }, std::string{"cosh_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"sinh_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::sinh(a); }); }, std::string{"sinh_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"tanh_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::tanh(a); }); }, std::string{"tanh_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"acosh_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::acosh(a); }); }, std::string{"acosh_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"asinh_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::asinh(a); }); }, std::string{"asinh_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"atanh_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::atanh(a); }); }, std::string{"atanh_"} + typeid(Matrix).name(), "matrices"});
                    neuronIds[std::string{"inverse_"} + typeid(Matrix).name()] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.inverse(); }, std::string{"inverse_"} + typeid(Matrix).name(), "matrices"});
                }

                return neuronIds;
            }

            template <typename S, typename T>
            std::map<std::string, size_t> addCast()
            {
                std::map<std::string, size_t> neuronIds;

                neuronIds[std::string{typeid(S).name()} + "_to_" + std::string{typeid(T).name()}] = addNeuron(Neuron<S, T>{[] (T const& x) { return static_cast<S>(x); }, std::string{typeid(S).name()} + "_to_" + std::string{typeid(T).name()}, "casts"});

                return neuronIds;
            }

        private:
            std::map<size_t, AnyNeuron> neurons_;
            std::map<std::string, bool> modules_;
            std::vector<Connection> connections_;
    };
}

#endif // AICPP_BRAIN_H
