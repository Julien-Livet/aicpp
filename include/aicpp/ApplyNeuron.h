#ifndef AICPP_APPLY_NEURON_H
#define AICPP_APPLY_NEURON_H

#include "PolymorphicNeuron.h"

#include <any>
#include <stdexcept>
#include <vector>

namespace aicpp
{
    class ApplyNeuron : public PolymorphicNeuron
    {
        public:
            std::string const& name() const override
            {
                static std::string const name{"apply"};
                return name;
            }

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;

            std::any evaluate(
                std::vector<std::any> const& arguments) const override;

            bool evaluatesToValue() const override
            {
                return true;
            }
    };
}

#endif // AICPP_APPLY_NEURON_H
