#ifndef AICPP_FUNCTION_ADAPTER_NEURON_H
#define AICPP_FUNCTION_ADAPTER_NEURON_H

#include "aicpp/Neuron.h"
#include "aicpp/PolymorphicNeuron.h"

namespace aicpp
{
    class FunctionAdapterNeuron : public PolymorphicNeuron
    {
        public:
            explicit FunctionAdapterNeuron(NeuronBase const* neuron);

            std::string const& name() const override;

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;

        private:
            NeuronBase const* neuron_;
    };
}

#endif // AICPP_FUNCTION_ADAPTER_NEURON_H