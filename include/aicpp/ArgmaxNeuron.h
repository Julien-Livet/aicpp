#ifndef AICPP_ARGMAX_NEURON_H
#define AICPP_ARGMAX_NEURON_H

#include "PolymorphicNeuron.h"

#include <any>
#include <vector>

namespace aicpp
{
    class ArgmaxNeuron : public PolymorphicNeuron
    {
        public:
            std::string const& name() const override
            {
                static std::string const name{"argmax"};
                return name;
            }

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;

            DslType inferConnectionSignature(
                std::vector<Connection> const& arguments) const override;

            bool evaluatesToValue() const override
            {
                return true;
            }

            std::any evaluate(
                std::vector<std::any> const& arguments) const override;

        private:
            DslType elementTypeFor(DslType const& container) const;
            Connection resolveFunction(
                Connection const& function,
                DslType const& elementType) const;
    };
}

#endif // AICPP_ARGMAX_NEURON_H
