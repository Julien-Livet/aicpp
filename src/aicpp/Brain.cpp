#include <future>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "aicpp/Brain.h"
#include "aicpp/utility.h"

using namespace aicpp;

class Pair
{
    public:
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

        bool operator==(Pair const& other) const
        {
            return connection == other.connection;
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

    for (auto const& c : connections_)
    {
        if (c.inputTypes().empty())
            parameters[c.neuron().outputType()].emplace_back(c);
        else
            connections.emplace(c);
    }

    std::map<std::type_index, std::unordered_set<Connection> > connectionMapping;

    for (size_t l{0}; l < level; ++l)
    {
        auto mapping{connectionMapping};

        for (auto const& connection : connections)
        {
            auto& s{mapping[connection.neuron().outputType()]};

            std::vector<std::vector<std::any> > args;
            auto const connectionInputTypes{connection.inputTypes()};

            for (auto const& inputType : connectionInputTypes)
                args.emplace_back(std::vector<std::any>{inputType});

            for (size_t i{0}; i < args.size(); ++i)
            {
                auto const it{connectionMapping.find(connectionInputTypes[i])};

                if (it != connectionMapping.end())
                {
                    for (auto const& v : it->second)
                        args[i].emplace_back(v);
                }
            }

            for (auto const& p : utility::cartesianProduct(args))
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

        connectionParameters.emplace(std::make_pair(connection, utility::cartesianProduct(args)));
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
        c.setName("");
        c.setSource(connection);
        c.applyInputs(*iterator);
        ++iterator;
        auto const value{c.output()};

        for (size_t j{0}; j < targets.size(); ++j)
            sets[j].emplace(Pair{utility::heuristic(value, targets[j]), connection.cost(), i, c});
    }

    std::vector<std::multiset<Pair>::iterator> its;
    its.reserve(sets.size());

    for (auto const& set : sets)
        its.emplace_back(set.begin());

    std::vector<bool> finishedSets(sets.size(), false);
    std::vector<std::vector<std::future<Pair> > > futures;
    futures.resize(its.size());
    std::vector<char> processes(its.size(), 1);

    while (std::any_of(finishedSets.begin(), finishedSets.end(), [] (auto const& x) { return !x; }))
    {
        for (size_t i{0}; i < its.size(); ++i)
        {
            futures[i].clear();
            processes[i] = 1;

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

            while (its[i] != sets[i].end())
            {
                auto const connectionId{its[i]->connectionId};
                auto const& connection{conns[connectionId]};
                auto const connectionParametersIt{connectionParameters.find(connection)};

                if (connectionParametersIt == connectionParameters.end())
                    continue;

                auto const iteratorsIt{iterators.find(connection)};
                auto& iterator{iteratorsIt->second};

                futures[i].emplace_back(
                    std::async(std::launch::async,
                               [eps, connection, bestPair = *its[i], connectionParametersIt = connectionParametersIt, target = targets[i], &iterator, connectionId, &process = processes[i]] ()
                               -> Pair
                               {
                                   while (process && iterator != connectionParametersIt->second.cend())
                                   {
                                       auto c{connection};
                                       c.setName("");
                                       c.setSource(connection);
                                       c.applyInputs(*iterator);
                                       ++iterator;
                                       auto const value{c.output()};
                                       auto const cost{utility::heuristic(value, target)};

                                       if (cost < bestPair.cost + eps)
                                       {
                                           process = 0;

                                           return Pair{cost, connection.cost(), connectionId, c};
                                       }
                                   }

                                   return bestPair;
                               }));

                ++its[i];
            }
        }

        for (size_t i{0}; i < its.size(); ++i)
        {
            std::multiset<Pair> pairs;

            if (futures[i].size())
            {
                for (auto& f : futures[i])
                    pairs.emplace(f.get());

                if (sets[i] == pairs)
                    finishedSets[i] = true;
                else
                {
                    sets[i] = pairs;
                    its[i] = sets[i].begin();
                }
            }
        }
    }

    std::vector<Connection> learnedConnections;
    learnedConnections.reserve(targets.size());

    for (auto const& set : sets)
    {
        if (set.empty())
            return std::vector<Connection>{};

        auto it{set.begin()};
        std::vector<Connection> solutions{it->connection};
        ++it;

        for (; it != set.end(); ++it)
        {
            if (it->cost < set.begin()->cost + eps)
                solutions.emplace_back(it->connection);
            else
                break;
        }

        std::sort(solutions.begin(), solutions.end(), [] (auto const& x, auto const& y) { return x.cost() < y.cost(); });

        learnedConnections.emplace_back(solutions.front());
    }

    return learnedConnections;
}

std::vector<std::reference_wrapper<Neuron const> > const& Brain::neurons() const
{
    return neurons_;
}

std::unordered_set<Connection> const& Brain::connections() const
{
    return connections_;
}

void Brain::addConnection(Connection const& connection)
{
    connections_.emplace(connection);
}

void Brain::removeConnection(Connection const& connection)
{
    auto const it{connections_.find(connection)};

    if (it != connections_.end())
        connections_.erase(it);
}

void Brain::clearConnections()
{
    connections_.clear();
}


bool Brain::fromJson(boost::json::value const& value)
{
    std::map<std::string, std::reference_wrapper<Neuron const> > map;
    std::unordered_set<boost::json::value> neuronValues;

    for (auto const& neuron : neurons_)
    {
        auto const v{neuron.get().toJson()};

        neuronValues.emplace(v);
        map.emplace(std::make_pair(boost::json::serialize(v), neuron));
    }

    boost::json::array neurons;

    if (value.is_object())
        neurons = value.at("neurons").as_array();
    else if (value.is_array())
        neurons = value.as_array()[0].at("neurons").as_array();

    for (size_t i{0}; i < neurons.size(); ++i)
    {
        if (neuronValues.find(neurons[i]) == neuronValues.end())
            break;
    }

    boost::json::array connections;

    if (value.is_object())
        connections = value.at("connections").as_array();
    else if (value.is_array())
        connections = value.as_array()[0].at("connections").as_array();

    connections_.clear();

    for (size_t i{0}; i < connections.size(); ++i)
    {
        try
        {
            connections_.emplace(buildConnection_(map, connections[i]));
        }
        catch (std::runtime_error const&)
        {
            return false;
        }
    }

    return true;
}

Connection Brain::buildConnection_(std::map<std::string, std::reference_wrapper<Neuron const> > const& map, boost::json::value const& value) const
{
    auto const name{value.at("name").as_string()};
    auto const neuron{value.at("neuron")};
    auto const it{map.find(boost::json::serialize(neuron))};

    if (it == map.end())
        throw std::runtime_error{"Neuron not found"};

    boost::json::array types;

    if (value.is_object())
        types = value.at("types").as_array();
    else if (value.is_array())
        types = value.as_array()[0].at("types").as_array();

    boost::json::array inputs;

    if (value.is_object())
        inputs = value.at("inputs").as_array();
    else if (value.is_array())
        inputs = value.as_array()[0].at("inputs").as_array();

    assert(types.size() == inputs.size());

    std::vector<std::any> connectionInputs;
    connectionInputs.reserve(types.size());

    for (size_t j{0}; j < types.size(); ++j)
    {
        if (types[j].as_string() == typeid(Connection).name())
            connectionInputs.emplace_back(buildConnection_(map, inputs[j]));
        else
            connectionInputs.emplace_back(stringToAny(types[j].as_string().c_str(), inputs[j].as_string().c_str()));
    }

    assert(connectionInputs.size() == types.size());

    Connection connection{it->second, connectionInputs};
    connection.setName(name.c_str());

    return connection;
}

boost::json::value Brain::toJson() const
{
    using namespace boost::json;

    object obj;

    array neurons;

    for (const auto& neuron : neurons_)
        neurons.emplace_back(neuron.get().toJson());

    obj["neurons"] = std::move(neurons);

    array connections;

    for (const auto& connection : connections_)
        connections.emplace_back(connection.toJson());

    obj["connections"] = std::move(connections);

    return obj;
}
