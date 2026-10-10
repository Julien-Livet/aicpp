#ifndef AICPP_CHAIN_NEURON_H
#define AICPP_CHAIN_NEURON_H

#include "PolymorphicNeuron.h"

#include <any>
#include <stdexcept>
#include <vector>

namespace aicpp
{
    class ChainNeuron : public PolymorphicNeuron
    {
        public:
            std::string const& name() const override
            {
                static std::string const name{"chain"};
                return name;
            }

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;
    };
}

#endif // AICPP_CHAIN_NEURON_H
