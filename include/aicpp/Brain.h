#ifndef AICPP_BRAIN_H
#define AICPP_BRAIN_H

#include <map>
#include <unordered_set>

#include "aicpp/Connection.h"

namespace aicpp
{
    class Brain
    {
        public:
            Brain(std::vector<std::reference_wrapper<Neuron const> > const& neurons);
            std::vector<Connection> learn(std::vector<std::any> const& targets, size_t level = 3, double eps = 1e-6) const;
            std::vector<std::reference_wrapper<Neuron const> > const& neurons() const;
            std::unordered_set<Connection> const& connections() const;
            void addConnection(Connection const& connection);
            void removeConnection(Connection const& connection);
            void clearConnections();
            bool fromJson(boost::json::value const& value);
            boost::json::value toJson() const;

        private:
            std::vector<std::reference_wrapper<Neuron const> > neurons_;
            std::unordered_set<Connection> connections_;

            Connection buildConnection_(std::map<std::string, std::reference_wrapper<Neuron const> > const& map, boost::json::value const& value) const;
    };
}

#endif // AICPP_BRAIN_H
