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
            if (val.type() == typeid(bool))
                return heuristic(std::any_cast<bool>(val), target);
            else if (val.type() == typeid(char))
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
                        return variantToHash(anyToVariant<bool, char, double, Eigen::MatrixXd, Eigen::MatrixXf, Eigen::MatrixXi, float, int, long, std::map<double, double>,
                                                          std::map<float, float>, std::map<int, int>, std::pair<int, int>, std::pair<size_t, size_t>, std::string, std::vector<std::pair<int, int> >,
                                                          std::vector<std::vector<std::pair<int, int> > >, std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >,
                                                          std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > >(x));
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

                auto const suffix{std::string{"_"} + typeid(String).name()};

                {
                    auto const n{std::string{"add"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<String, String, String>{[] (String const& x, String const& y) { return x + y; }, n, "strings"});
                }
                {
                    auto const n{std::string{"size"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<int, String>{[] (String const& x) { return (int)x.size(); }, n, "strings"});
                }
                {
                    auto const n{std::string{"lower"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<String, String>{[] (String const& x) { auto s{x}; std::transform(s.begin(), s.end(), s.begin(), ::tolower); return s; },
                                                                    n, "strings"});
                }
                {
                    auto const n{std::string{"upper"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<String, String>{[] (String const& x) { auto s{x}; std::transform(s.begin(), s.end(), s.begin(), ::toupper); return s; },
                                                                    n, "strings"});}
                {
                    auto const n{std::string{"pop_back"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<String, String>{[] (String const& x) { return x.substr(0, x.size() - 1); }, n, "strings"});
                }
                {
                    auto const n{std::string{"pop_front"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<String, String>{[] (String const& x) { return x.substr(1); }, n, "strings"});
                }

                return neuronIds;
            }

            std::map<std::string, size_t> addBools()
            {
                std::map<std::string, size_t> neuronIds;

                auto const suffix{std::string{"_"} + typeid(bool).name()};

                {
                    auto const n{std::string{"and"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x & y; }, n, "bools"});
                }
                {
                    auto const n{std::string{"or"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x | y; }, n, "bools"});
                }
                {
                    auto const n{std::string{"xor"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x ^ y; }, n, "bools"});
                }
                {
                    auto const n{std::string{"not"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, bool>{[] (bool const& x) { return !x; }, n, "bools"});
                }
                {
                    auto const n{std::string{typeid(bool).name()} + "_to_" + typeid(std::string).name()};
                    neuronIds[n] = addNeuron(Neuron<std::string, bool>{[] (bool const& x) { std::ostringstream oss; oss << x; return oss.str(); }, n, "bools"});
                }
                {
                    auto const n{std::string{typeid(std::string).name()} + "_to" + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, std::string>{[] (std::string const& s) { std::istringstream iss{s}; bool x; iss >> x; return x; }, n, "bools"});
                }
                {
                    auto const n{std::string{"eq"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x == y; }, n, "bools"});
                }
                {
                    auto const n{std::string{"ne"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, bool, bool>{[] (bool const& x, bool const& y) { return x != y; }, n, "bools"});
                }

                return neuronIds;
            }

            template <typename Int>
            std::map<std::string, size_t> addInts()
            {
                std::map<std::string, size_t> neuronIds;

                auto const suffix{std::string{"_"} + typeid(Int).name()};

                {
                    auto const n{std::string{"add"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x + y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"sub"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x - y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"mul"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x * y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"div"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) -> Int { if (!y) return Int{}; return x / y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"mod"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) -> Int { if (!y) return Int{}; return x % y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"pow"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<double, Int, Int>{[] (Int const& x, Int const& y) { return std::pow(x, y); }, n, "ints"});
                }
                {
                    auto const n{std::string{"and"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x & y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"or"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x | y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"xor"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { return x ^ y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"left_shift"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { if (y < 0) return Int{}; return Int{x << y}; }, n, "ints"});
                }
                {
                    auto const n{std::string{"right_shift"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int, Int>{[] (Int const& x, Int const& y) { if (y < 0) return Int{}; return Int{x >> y}; }, n, "ints"});
                }
                {
                    auto const n{std::string{"complement"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int>{[] (Int const& x) { return ~x; }, n, "ints"});
                }
                {
                    auto const n{std::string{"abs"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int>{[] (Int const& x) { return std::abs(x); }, n, "ints"});
                }
                {
                    auto const n{std::string{"neg"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, Int>{[] (Int const& x) { return -x; }, n, "ints"});
                }
                {
                    auto const n{std::string{typeid(Int).name()} + "_to_" + typeid(std::string).name()};
                    neuronIds[n] = addNeuron(Neuron<std::string, Int>{[] (Int const& x) { std::ostringstream oss; oss << x; return oss.str(); }, n, "ints"});
                }
                {
                    auto const n{std::string{typeid(std::string).name()} + "_to" + suffix};
                    neuronIds[n] = addNeuron(Neuron<Int, std::string>{[] (std::string const& s) { std::istringstream iss{s}; Int x; iss >> x; return x; }, n, "ints"});
                }
                {
                    auto const n{std::string{"eq"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x == y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"ne"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x != y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"gt"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x > y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"lt"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x < y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"ge"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x >= y; }, n, "ints"});
                }
                {
                    auto const n{std::string{"le"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Int, Int>{[] (Int const& x, Int const& y) { return x <= y; }, n, "ints"});
                }

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

                auto const suffix{std::string{"_"} + typeid(Real).name()};

                {
                    auto const n{std::string{"add"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { return x + y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"sub"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { return x - y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"mul"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { return x * y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"div"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { if (!y) return Real{}; return x / y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"pow"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real, Real>{[] (Real const& x, Real const& y) { return std::pow(x, y); }, n, "reals"});
                }
                {
                    auto const n{std::string{"abs"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::abs(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"neg"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return -x; }, n, "reals"});
                }
                {
                    auto const n{std::string{typeid(Real).name()} + "_to_" + typeid(std::string).name()};
                    neuronIds[n] = addNeuron(Neuron<std::string, Real>{[] (Real const& x) { std::ostringstream oss; oss << x; return oss.str(); }, n, "reals"});
                }
                {
                    auto const n{std::string{typeid(std::string).name()} + "_to_" + typeid(Real).name()};
                    neuronIds[n] = addNeuron(Neuron<Real, std::string>{[] (std::string const& s) { std::istringstream iss{s}; Real x; iss >> x; return x; }, n, "reals"});
                }
                {
                    auto const n{std::string{"eq"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x == y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"ne"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x != y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"gt"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x > y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"lt"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x < y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"ge"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x >= y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"le"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<bool, Real, Real>{[] (Real const& x, Real const& y) { return x <= y; }, n, "reals"});
                }
                {
                    auto const n{std::string{"sqrt"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::sqrt(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"log"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::log(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"exp"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::exp(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"cos"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::cos(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"sin"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::sin(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"tan"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::tan(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"acos"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::acos(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"asin"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::asin(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"atan"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::atan(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"cosh"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::cosh(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"sinh"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::sinh(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"tanh"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::tanh(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"acosh"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::acosh(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"asinh"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::asinh(x); }, n, "reals"});
                }
                {
                    auto const n{std::string{"atanh"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Real, Real>{[] (Real const& x) { return std::atanh(x); }, n, "reals"});
                }

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

                auto const suffix{std::string{"_"} + typeid(Matrix).name()};

                {
                    auto const n{std::string{"add"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (!(x.rows() == y.rows() && x.cols() == y.cols()) || !x.rows() || !x.cols() || !y.rows() || !y.cols()) return Matrix{}; return Matrix{x + y}; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"add2"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a + y; }); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"sub"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (!(x.rows() == y.rows() && x.cols() == y.cols()) || !x.rows() || !x.cols() || !y.rows() || !y.cols()) return Matrix{}; return Matrix{x - y}; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"sub2"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a - y; }); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"mul"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (!(x.rows() == y.rows() && x.cols() == y.cols()) || !x.rows() || !x.cols() || !y.rows() || !y.cols()) return Matrix{}; return Matrix{x.cwiseProduct(y)}; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"mul2"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a * y; }); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"div"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (!(x.rows() == y.rows() && x.cols() == y.cols()) || !x.rows() || !x.cols() || !y.rows() || !y.cols() || !y.cwiseAbs().minCoeff()) return Matrix{}; return Matrix{x.cwiseQuotient(y)}; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"div2"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { if (!y) return Matrix{}; return Matrix{x.unaryExpr([y] (auto const& a) { return a / y; })}; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"mulmat"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { if (x.cols() != y.rows() || !x.rows() || !x.cols() || !y.rows() || !y.cols()) return Matrix{}; return Matrix{x * y}; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"abs"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::abs(a); }); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"neg"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return -x; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"transpose"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { if (!x.rows() || !x.cols()) return Matrix{}; return Matrix{x.transpose()}; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"swapcols"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, int, int>{[] (Matrix const& x, int i, int j) { return swapCols(x, i, j); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"swaprows"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, int, int>{[] (Matrix const& x, int i, int j) { return swapRows(x, i, j); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"fliplr"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return fliplr(x); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"flipud"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return flipud(x); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"replace"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar, typename Matrix::Scalar>{[] (Matrix const& a, auto const& x, auto const& y) { return a.unaryExpr([x, y] (auto const& b) { return std::abs(b - x) < 1.0e-6 ? y : b; }); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"map"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::map<typename Matrix::Scalar, typename Matrix::Scalar> >{[] (Matrix const& a, auto const& mapping) { return map(a, mapping); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"fill_region"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::vector<std::pair<int, int> >, typename Matrix::Scalar>{[] (Matrix const& a, auto  const& region, auto const& x) { return fillRegion(a, region, x); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"fill_regions"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::vector<std::vector<std::pair<int, int> > >, typename Matrix::Scalar>{[] (Matrix const& a, auto const& regions, auto const& x) { return fillRegions(a, regions, x); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"fill_region_at"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& a, auto const& at, auto const& x) { return fillRegionAt(a, at, x, true); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"fill_region2_at"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& a, auto const& at, auto const& x) { return fillRegionAt(a, at, x, false); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"hline"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, int, typename Matrix::Scalar>{[] (Matrix const& x, int row, auto const& value) { return hline(x, row, value); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"vline"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, int, typename Matrix::Scalar>{[] (Matrix const& x, int col, auto const& value) { return vline(x, col, value); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"hlineright"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, auto const& at, auto const& value) { return hlineright(x, at, value); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"hlineleft"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, auto const& at, auto const& value) { return hlineleft(x, at, value); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"vlineup"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, auto const& at, auto const& value) { return vlineup(x, at, value); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"vlinedown"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, auto const& at, auto const& value) { return vlinedown(x, at, value); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"zero"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, std::pair<size_t, size_t> >{[] (std::pair<size_t, size_t> const& size) { return zero<Matrix>(size); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"ones"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, std::pair<size_t, size_t> >{[] (std::pair<size_t, size_t> const& size) { return ones<Matrix>(size); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"identity"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, std::pair<size_t, size_t> >{[] (std::pair<size_t, size_t> const& size) { return identity<Matrix>(size); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"put_value"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& x, std::pair<int, int> const& at, auto const& value) { return put(x, at, value); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"at"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<typename Matrix::Scalar, Matrix, std::pair<int, int> >{[] (Matrix const& x, std::pair<int, int> const& pos) { return at(x, pos); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"fill"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& value) { Matrix y{x}; y.fill(value); return y; }, n, "matrices"});
                }
                {
                    auto const n{std::string{"rot90"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return rot90(x); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"trace"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<typename Matrix::Scalar, Matrix>{[] (Matrix const& x) { return x.trace(); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"dot_segment"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<int, int>, std::pair<int, int>, typename Matrix::Scalar, int>{[] (Matrix const& x, std::pair<int, int> const& b, std::pair<int, int> const& e, auto const& v, int d) { return dotSegment(x, b, e, v, d); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"tile"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::pair<size_t, size_t> >{[] (Matrix const& x, std::pair<size_t, size_t> const& r) { return tile(x, r); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"put_matrix"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix, std::pair<int, int> >{[] (Matrix const& dst, Matrix const& src, std::pair<int, int> const& at) { return put(dst, src, at); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"place_region"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::vector<std::pair<int, int> >, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& a, std::vector<std::pair<int, int> > const& region, std::pair<int, int> const& at, auto const& x) { return placeRegion(a, region, at, x); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"place_region"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::vector<std::pair<int, int> >, std::pair<int, int>, typename Matrix::Scalar>{[] (Matrix const& a, std::vector<std::pair<int, int> > const& region, std::pair<int, int> const& at, auto const& x) { return placeRegion(a, region, at, x); }, n, "matrices"});
                }
                {
                    auto const n{std::string{"matrix_region"} + suffix};
                    neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::vector<std::pair<int, int> > >{[] (Matrix const& a, std::vector<std::pair<int, int> > const& region) { return matrixRegion(a, region); }, n, "matrices"});
                }

                if constexpr (std::is_same_v<Matrix, Eigen::MatrixXi>)
                {
                    {
                        auto const n{std::string{"segments"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >, int, bool, bool>{[] (auto const& dst, auto const& pairs, auto const& value, auto start, auto finish) { return segments(dst, pairs, value, start, finish); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"mod"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { return modMatrix(x, y); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"mod2"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { if (!y) return Matrix{}; return Matrix{x.unaryExpr([y] (auto const& a) { return a % y; })}; }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"and"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { return andMatrix(x, y); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"and2"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a & y; }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"or"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { return orMatrix(x, y); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"or2"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a | y; }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"xor"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, Matrix>{[] (Matrix const& x, Matrix const& y) { return xorMatrix(x, y); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"xor2"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix, typename Matrix::Scalar>{[] (Matrix const& x, typename Matrix::Scalar const& y) { return x.unaryExpr([y] (auto const& a) { return a ^ y; }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"invert"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return ~a; }); }, n, "matrices"});
                    }
                }
                else
                {
                    {
                        auto const n{std::string{"sqrt"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::sqrt(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"log_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::log(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"exp_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::exp(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"cos_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::cos(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"sin_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::sin(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"tan_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::tan(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"acos_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::acos(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"asin_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::asin(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"atan_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::atan(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"cosh_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::cosh(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"sinh_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::sinh(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"tanh_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::tanh(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"acosh_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::acosh(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"asinh_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::asinh(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"atanh_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.unaryExpr([] (auto const& a) { return std::atanh(a); }); }, n, "matrices"});
                    }
                    {
                        auto const n{std::string{"inverse_"} + suffix};
                        neuronIds[n] = addNeuron(Neuron<Matrix, Matrix>{[] (Matrix const& x) { return x.inverse(); }, n, "matrices"});
                    }
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
