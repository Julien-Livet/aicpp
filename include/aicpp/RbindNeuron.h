#ifndef AICPP_RBIND_NEURON_H
#define AICPP_RBIND_NEURON_H

#include "aicpp/PolymorphicNeuron.h"

namespace aicpp
{
    class RbindNeuron : public PolymorphicNeuron
    {
        public:
            std::string const& name() const override
            {
                static std::string const name{"rbind"};
                return name;
            }

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            DslType inferConnectionSignature(
                std::vector<Connection> const& arguments) const override;

            bool evaluatesToValue(
                std::vector<std::any> const& arguments) const override;

            std::any evaluate(
                std::vector<std::any> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;
    };
}

#endif // AICPP_RBIND_NEURON_H
