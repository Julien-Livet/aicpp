#include <iostream> //TODO: to remove
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "aicpp/Brain.h"
#include "aicpp/utility.h"

using namespace aicpp;

class Pair
{
    public:
        std::any value;
        double cost;
        size_t connectionCost;
        size_t connectionId;
        Connection connection;

        bool operator<(Pair const& other) const
        {
            if (cost == other.cost)
                return connectionCost < other.connectionCost;

            return cost < other.cost;
        }
};

Brain::Brain(std::vector<std::reference_wrapper<Neuron const> > const& neurons) : neurons_{neurons}
{
}

std::vector<Connection> Brain::learn(std::vector<std::any> const& targets, size_t level, double eps) const
{
    std::map<std::type_index, std::vector<std::any> > parameters;
    std::unordered_set<Connection> connections;

    for (auto const& neuron : neurons_)
    {
        if (neuron.get().inputTypes().empty())
            parameters[neuron.get().outputType()].emplace_back(Connection{neuron, std::vector<std::any>{}});
        else
        {
            std::vector<std::any> v;

            for (auto const& inputType : neuron.get().inputTypes())
                v.emplace_back(inputType);

            connections.emplace(Connection{neuron, v});
        }
    }

    std::map<std::type_index, std::unordered_set<Connection> > connectionMapping;

    for (size_t l{0}; l < level; ++l)
    {
        auto mapping{connectionMapping};

        for (auto const& connection : connections)
        {
            auto& s{mapping[connection.neuron().outputType()]};

            std::vector<std::vector<std::any> > args;

            for (auto const& inputType : connection.inputTypes())
                args.emplace_back(std::vector<std::any>{inputType});

            for (size_t j{0}; j < args.size(); ++j)
            {
                auto const it{connectionMapping.find(connection.inputTypes()[j])};

                if (it != connectionMapping.end())
                {
                    for (auto const& v : it->second)
                        args[j].emplace_back(v);
                }
            }

            for (auto const& p : cartesianProduct(args))
            {
                auto c{connection};
                c.applyInputs(p);
                s.emplace(c);
            }
        }

        connectionMapping = mapping;

        connections.clear();

        for (auto const& p : connectionMapping)
            connections.insert(p.second.begin(), p.second.end());
    }

    for (auto const& neuron : neurons_)
    {
        if (neuron.get().inputTypes().empty())
            connections.emplace(Connection{neuron, std::vector<std::any>{}});
    }

    std::vector<Connection> conns{connections.begin(), connections.end()};

    std::sort(conns.begin(), conns.end(), [] (auto const& x, auto const& y) { return x.cost() < y.cost(); });
    for (size_t i{0}; i < conns.size(); ++i)
    {
        auto const& connection{conns[i]};
        std::string const vectorMatrixStr{typeid(std::vector<Eigen::MatrixXi>).name()};
        std::string const intStr{typeid(int).name()};
        std::string const boolStr{typeid(bool).name()};
        std::string const vectorRegionsStr{typeid(std::vector<std::vector<std::vector<std::pair<int, int> > > >).name()};
        if (connection.string().starts_with("fillRegions(fillRegions(fillRegions(" + vectorMatrixStr + ", " + vectorRegionsStr + ", " + intStr + "), memberPairedRegions(pairedRegions(" + vectorMatrixStr + ", " + vectorRegionsStr + "), " + boolStr + "), " + intStr + "), memberPairedRegions(pairedRegions(" + vectorMatrixStr + ", " + vectorRegionsStr + "), " + boolStr + "), " + intStr))
            std::cout << "@" << i << " " << conns.size() << " " << connection.string() << std::endl;
    }
    std::unordered_map<Connection, std::generator<std::vector<std::any> > > connectionParameters;

    for (size_t i{0}; i < conns.size(); ++i)
    {
        auto const& connection{conns[i]};
        auto const& connectionInputTypes{connection.inputTypes()};

        std::vector<std::vector<std::any> > args;

        for (auto const& inputType : connectionInputTypes)
        {
            auto const it{parameters.find(inputType)};

            if (it == parameters.end())
                break;

            args.emplace_back(it->second);
        }

        if (args.size() != connectionInputTypes.size())
            continue;

        connectionParameters.emplace(std::make_pair(connection, cartesianProduct(args)));
    }

    if (connectionParameters.empty())
        return std::vector<Connection>{};

    std::vector<std::multiset<Pair> > sets;
    sets.resize(targets.size());
    std::unordered_map<Connection, decltype(connectionParameters.begin()->second.cbegin())> iterators;

    for (size_t i{0}; i < conns.size(); ++i)
    {
        auto const it{connectionParameters.find(conns[i])};

        if (it != connectionParameters.end())
            iterators.emplace(std::make_pair(conns[i], it->second.cbegin()));
    }

    for (size_t i{0}; i < conns.size(); ++i)
    {
        auto const& connection{conns[i]};
        auto const connectionParametersIt{connectionParameters.find(conns[i])};

        if (connectionParametersIt == connectionParameters.end())
            continue;

        auto const iteratorsIt{iterators.find(conns[i])};
        auto& iterator{iteratorsIt->second};

        if (iterator == connectionParametersIt->second.cend())
            continue;

        auto c{connection};
        c.applyInputs(*iterator);
        ++iterator;
        auto const value{c.output()};

        for (size_t j{0}; j < targets.size(); ++j)
            sets[j].emplace(Pair{value, heuristic(value, targets[j]), connection.cost(), i, c});
    }

    std::vector<std::multiset<Pair>::iterator> its;
    its.reserve(sets.size());

    for (auto const& set : sets)
        its.emplace_back(set.begin());

    std::vector<bool> finishedSets(sets.size(), false);

    while (std::any_of(finishedSets.begin(), finishedSets.end(), [] (auto const& x) { return !x; }))
    {
        for (size_t i{0}; i < its.size(); ++i)
        {
            if (its[i] == sets[i].end())
            {
                finishedSets[i] = true;
                continue;
            }

            if (its[i]->cost < eps)
            {
                finishedSets[i] = true;
                continue;
            }

            auto const connectionId{its[i]->connectionId};
            auto const& connection{conns[connectionId]};
            auto const connectionParametersIt{connectionParameters.find(connection)};

            if (connectionParametersIt == connectionParameters.end())
                continue;

            auto const iteratorsIt{iterators.find(connection)};
            auto& iterator{iteratorsIt->second};

            if (iterator == connectionParametersIt->second.cend())
            {
                ++its[i];
                continue;
            }

            auto c{connection};
            c.applyInputs(*iterator);
            ++iterator;
            auto const value{c.output()};
            auto const cost{heuristic(value, targets[i])};

            if (cost < its[i]->cost)
            {
                sets[i].erase(its[i]);
                sets[i].emplace(Pair{value, cost, connection.cost(), connectionId, c});
                its[i] = sets[i].begin();
            }
        }
    }

    std::vector<Connection> learnedConnections;
    learnedConnections.reserve(targets.size());

    for (auto const& set : sets)
    {
        if (set.empty())
            return std::vector<Connection>{};

        learnedConnections.emplace_back(set.begin()->connection);
    }

    return learnedConnections;
}
