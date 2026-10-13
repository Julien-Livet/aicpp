#include "aicpp/LbindNeuron.h"

#include <stdexcept>

namespace aicpp
{
    DslType LbindNeuron::inferSignature(
        std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "lbind requires exactly two arguments");
        }

        auto const& function = arguments[0];
        auto const& fixed = arguments[1];

        if (!function.isFunction()
            || function.inputs().empty())
        {
            throw std::invalid_argument(
                "lbind requires a function with at least one argument");
        }

        if (!fixed.isFunction()
            || !fixed.inputs().empty())
        {
            throw std::invalid_argument(
                "lbind requires a value-producing expression");
        }

        if (fixed.output() != function.inputs()[0])
        {
            throw std::invalid_argument(
                "lbind fixed argument type does not match "
                "the first function input");
        }

        return DslType::function(
            {function.inputs()[1]},
            function.output());
    }

    std::any LbindNeuron::apply(
        std::vector<std::any> const& arguments,
        std::any const& input) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "lbind requires exactly two arguments");
        }

        if (arguments[0].type() != typeid(Connection)
            || arguments[1].type() != typeid(Connection))
        {
            throw std::invalid_argument(
                "lbind arguments must be connections");
        }

        auto const& function =
            std::any_cast<Connection const&>(arguments[0]);

        auto const& fixedConnection =
            std::any_cast<Connection const&>(arguments[1]);

        auto const signature = function.signature();

        if (!signature.isFunction()
            || signature.inputs().size() < 2)
        {
            throw std::invalid_argument(
                "lbind requires a function with at least two arguments");
        }

        if (input.type() != signature.inputs()[1].nativeType())
        {
            throw std::invalid_argument(
                "lbind received an incompatible input");
        }

        if (function.neuron()->isPolymorphic())
        {
            throw std::invalid_argument(
                "lbind currently requires a native function");
        }

        auto const fixed = fixedConnection.output();

        if (fixed.type() != signature.inputs()[0].nativeType())
        {
            throw std::invalid_argument(
                "lbind fixed argument has an incompatible type");
        }

        return function.neuron()->invoke({fixed, input});
    }
}
