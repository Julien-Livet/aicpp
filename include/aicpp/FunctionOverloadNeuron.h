#ifndef AICPP_FUNCTION_OVERLOAD_NEURON_H
#define AICPP_FUNCTION_OVERLOAD_NEURON_H

#include "aicpp/PolymorphicNeuron.h"

#include <string>
#include <vector>

namespace aicpp
{
    class FunctionOverloadNeuron : public PolymorphicNeuron
    {
        public:
            FunctionOverloadNeuron(
                std::string name,
                std::vector<NeuronBase const*> candidates);

            std::string const& name() const override;

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            DslType inferConnectionSignature(
                std::vector<Connection> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;

            NeuronBase const* resolve(
                DslType const& expectedSignature) const;

        private:
            std::string name_;
            std::vector<NeuronBase const*> candidates_;
    };
}

#endif
