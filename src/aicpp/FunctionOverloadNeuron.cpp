#include "aicpp/FunctionOverloadNeuron.h"

#include <stdexcept>

namespace aicpp
{
    FunctionOverloadNeuron::FunctionOverloadNeuron(
        std::string name,
        std::vector<NeuronBase const*> candidates)
        : name_{std::move(name)},
          candidates_{std::move(candidates)}
    {
        if (candidates_.empty())
        {
            throw std::invalid_argument(
                "FunctionOverloadNeuron requires at least one candidate");
        }

        for (auto const* candidate : candidates_)
        {
            if (candidate == nullptr)
            {
                throw std::invalid_argument(
                    "FunctionOverloadNeuron candidate cannot be null");
            }

            if (candidate->isPolymorphic())
            {
                throw std::invalid_argument(
                    "FunctionOverloadNeuron candidates must be native neurons");
            }

            if (candidate->inputTypes().size() != 1)
            {
                throw std::invalid_argument(
                    "FunctionOverloadNeuron candidates must be unary");
            }
        }
    }

    std::string const& FunctionOverloadNeuron::name() const
    {
        return name_;
    }

    NeuronBase const* FunctionOverloadNeuron::resolve(
        DslType const& expectedSignature) const
    {
        if (!expectedSignature.isFunction()
            || expectedSignature.inputs().size() != 1)
        {
            throw std::invalid_argument(
                "Expected signature must be a unary function");
        }

        NeuronBase const* match = nullptr;

        for (auto const* candidate : candidates_)
        {
            if (candidate->signature() != expectedSignature)
                continue;

            if (match != nullptr)
            {
                throw std::invalid_argument(
                    "Ambiguous function overload: " + name_);
            }

            match = candidate;
        }

        if (match == nullptr)
        {
            throw std::invalid_argument(
                "No compatible function overload: " + name_);
        }

        return match;
    }

    DslType FunctionOverloadNeuron::inferSignature(
        std::vector<DslType> const&) const
    {
        throw std::invalid_argument(
            "Function overload requires an expected signature: " + name_);
    }

    DslType FunctionOverloadNeuron::inferConnectionSignature(
        std::vector<Connection> const&) const
    {
        throw std::invalid_argument(
            "Function overload requires an expected signature: " + name_);
    }

    std::any FunctionOverloadNeuron::apply(
        std::vector<std::any> const&,
        std::any const&) const
    {
        throw std::logic_error(
            "Function overload must be resolved before application: " + name_);
    }
}