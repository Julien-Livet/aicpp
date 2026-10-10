#ifndef AICPP_FORK_NEURON_H
#define AICPP_FORK_NEURON_H

#include "PolymorphicNeuron.h"

#include <any>
#include <stdexcept>
#include <vector>

namespace aicpp
{
    class ForkNeuron : public PolymorphicNeuron
    {
        public:
            std::string const& name() const override
            {
                static std::string const name{"fork"};
                return name;
            }

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;
        };
}

#endif //AICPP_FORK_NEURON_H
