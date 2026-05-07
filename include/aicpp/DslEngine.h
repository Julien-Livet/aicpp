#ifndef AICPP_DSLENGINE_H
#define AICPP_DSLENGINE_H

#include <functional>
#include <map>
#include <optional>
#include <queue>
#include <string>
#include <tuple>

#include "aicpp/Connection.h"
#include "aicpp/Neuron.h"
#include "aicpp/utility.h"

namespace aicpp
{
    class DslEngine
    {
        public:
            DslEngine(std::function<double(std::any, std::any)> const heuristic = [] (auto const& x, auto const& y) { return utility::heuristic(x, y); },
                      size_t bo_n_init = 1000, size_t bo_top_k = 100, size_t bo_count_max = 20);

            template <typename T> std::tuple<Connection, std::vector<std::string>, double> learn(T const& target)
            {
                struct CustomLess
                {
                    bool operator()(std::tuple<double, size_t, std::string> const& lhs, std::tuple<double, size_t, std::string> const& rhs) const
                    {
                        if (std::get<0>(lhs) == std::get<0>(rhs))
                        {
                            if (std::get<1>(lhs) == std::get<1>(rhs))
                                return std::lexicographical_compare(std::get<2>(lhs).begin(), std::get<2>(lhs).end(), std::get<2>(rhs).begin(), std::get<2>(rhs).end());

                            return std::get<1>(lhs) > std::get<1>(rhs);
                        }

                        return std::get<0>(lhs) > std::get<0>(rhs);
                    }
                };
                
                std::priority_queue<std::tuple<double, size_t, std::string>,
                                    std::vector<std::tuple<double, size_t, std::string> >,
                                    CustomLess> frontier;
                std::map<std::string, Connection> addedConnections;

                auto const explore{[&, this] () -> std::optional<Connection>
                    {
                        for (auto const& [k, n] : primitiveNeurons_)
                        {
                            if (typeid(target) != n.outputType())
                                continue;

                            std::vector<std::vector<std::any> > combinations;

                            for (auto const& inputType : n.inputTypes())
                            {
                                std::vector<std::any> combination{inputType};

                                for (auto const& v : typedConnections_[inputType])
                                    combination.emplace_back(v);
                                
                                combinations.emplace_back(combination);
                            }

                            if (combinations.empty())
                                continue;

                            auto product{utility::cartesianProduct(combinations)};

                            for (auto const& value : product)
                            {
                                Connection connection{n, n.inputTypes()};
                                connection.applyInputs(value);

                                std::vector<std::vector<std::string> > combos;

                                for (auto const& inputType : connection.inputTypes())
                                {
                                    std::vector<std::string> combo;

                                    for (auto const& n : typedVariableNeurons_[inputType])
                                        combo.emplace_back(n.name());
                                    
                                    combos.emplace_back(combo);
                                }

                                if (combinations.empty())
                                    continue;

                                auto const op{[this, connection] (auto const& x) -> std::any
                                    {
                                        auto c{connection};
                                        std::vector<std::any> inputs;
                                        inputs.reserve(x.size());

                                        for (auto const& n : x)
                                            inputs.emplace_back(variableNeurons_[n].function()(std::vector<std::any>{}));

                                        c.applyInputs(inputs);

                                        return c.output();
                                    }
                                };

                                try
                                {/*
                                    auto const result{bayesian_optimization_discrete(op, target, combinations, heuristic_, bo_n_init_, bo_top_k_, bo_count_max_)};
                                    auto const s{connection.toStr()};

                                    connections_[s] = std::make_tuple(connection, result.first, result.second);
                                    addedConnections[s] = connection;

                                    if (!result.second)
                                        return connections_[s];

                                    frontier.push(std::make_tuple(result.second, s.size(), s));*/
                                }
                                catch (std::exception const&)
                                {
                                }
                            }
                        }

                        return {};
                    }
                };

                auto result{explore()};

                if (result.has_value())
                    return result.value();

                double cost{0.0};
                size_t length{0};
                std::string name;

                while (!frontier.empty())
                {
                    auto const t{frontier.pop()};
                    cost = std::get<0>(t);
                    length = std::get<1>(t);
                    name = std::get<2>(t);

                    if (!cost)
                        break;

                    auto const it{addedConnections.find(name)};
                    auto const connection{it->second};
                    addedConnections.erase(it);

                    typedConnections_[connection.neuron().outputType()].emplace_back(connection);

                    result = explore();

                    if (result.has_value())
                        return result.value();
                }

                return connections_.at(name);
            }

            void clearVariableNeurons();
            void clearPrimitiveNeurons();
            void addVariableNeuron(Neuron const& neuron, std::string name = std::string{});
            void addPrimitiveNeuron(Neuron const& neuron, std::string name = std::string{});
        
        private:
            std::function<double(std::any, std::any)> heuristic_;
            size_t bo_n_init_{1000};
            size_t bo_top_k_{100};
            size_t bo_count_max_{20};
            std::map<std::string, Neuron> variableNeurons_;
            std::map<std::type_index, std::vector<Neuron> > typedVariableNeurons_;
            std::map<std::string, Neuron> primitiveNeurons_;
            std::map<std::type_index, std::vector<Neuron> > typedPrimitiveNeurons_;
            std::map<std::string, std::tuple<Connection, std::vector<std::string>, double> > connections_;
            std::map<std::type_index, std::vector<Connection> > typedConnections_;
    };
}

#endif // AICPP_DSLENGINE_H
