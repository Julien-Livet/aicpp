#include "aicpp/FunctionAdapterNeuron.h"

#include <stdexcept>

namespace aicpp
{
    FunctionAdapterNeuron::FunctionAdapterNeuron(
        NeuronBase const* neuron)
        : neuron_{neuron}
    {
        if (neuron_ == nullptr)
        {
            throw std::invalid_argument(
                "FunctionAdapterNeuron requires a neuron");
        }

        if (neuron_->isPolymorphic())
        {
            throw std::invalid_argument(
                "FunctionAdapterNeuron requires a native neuron");
        }
    }

    std::string const& FunctionAdapterNeuron::name() const
    {
        return neuron_->name();
    }

    DslType FunctionAdapterNeuron::inferSignature(
        std::vector<DslType> const& arguments) const
    {
        if (!arguments.empty())
        {
            throw std::invalid_argument(
                "FunctionAdapterNeuron expects no child connections");
        }

        return neuron_->signature();
    }

    std::any FunctionAdapterNeuron::apply(
        std::vector<std::any> const& arguments,
        std::any const& input) const
    {
        if (!arguments.empty())
        {
            throw std::invalid_argument(
                "FunctionAdapterNeuron expects no child connections");
        }

        auto const signature = neuron_->signature();

        if (!signature.isFunction() ||
            signature.inputs().size() != 1)
        {
            throw std::logic_error(
                "Adapted neuron must have a unary function signature");
        }

        if (input.type() != signature.inputs().front().nativeType())
        {
            throw std::invalid_argument(
                "FunctionAdapterNeuron received an incompatible input");
        }

        return neuron_->invoke({input});
    }

    NeuronBase const* FunctionAdapterNeuron::adaptedNeuron() const noexcept
    {
        return neuron_;
    }
}
