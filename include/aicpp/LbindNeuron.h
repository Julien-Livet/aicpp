#ifndef AICPP_LBIND_NEURON_H
#define AICPP_LBIND_NEURON_H

#include "aicpp/PolymorphicNeuron.h"

namespace aicpp
{
    class LbindNeuron : public PolymorphicNeuron
    {
        public:
            std::string const& name() const override
            {
                static std::string const name{"lbind"};
                return name;
            }

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;
    };
}

#endif // AICPP_LBIND_NEURON_H
