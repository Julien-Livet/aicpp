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

        private:
            std::vector<std::reference_wrapper<Neuron const> > neurons_;
    };
}

#endif // AICPP_BRAIN_H
