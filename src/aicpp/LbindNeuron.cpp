#include "aicpp/LbindNeuron.h"
#include "aicpp/FunctionValue.h"

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

        if (!function.isFunction() || function.inputs().empty())
        {
            throw std::invalid_argument(
                "lbind requires a function with at least one argument");
        }

        if (!fixed.isFunction() || !fixed.inputs().empty())
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

        DslType::Inputs remainingInputs(
            function.inputs().begin() + 1,
            function.inputs().end());

        if (remainingInputs.size() != 1)
        {
            throw std::invalid_argument(
                "lbind currently supports only unary resulting functions");
        }

        return DslType::function(
            remainingInputs,
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

    DslType LbindNeuron::inferConnectionSignature(
        std::vector<Connection> const& arguments) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "lbind requires exactly two arguments");
        }

        auto const& functionExpression = arguments[0];
        auto const& fixedExpression = arguments[1];

        auto const functionValueType = functionExpression.valueType();

        if (!functionValueType.isFunction()
            && functionValueType.nativeType() == typeid(FunctionValue))
        {
            auto const fixedSignature = fixedExpression.signature();

            if (!fixedSignature.isFunction()
                || !fixedSignature.inputs().empty())
            {
                throw std::invalid_argument(
                    "lbind requires a value-producing expression");
            }

            return fixedSignature.output();
        }

        return inferSignature({
            functionExpression.signature(),
            fixedExpression.signature()
        });
    }

    bool LbindNeuron::evaluatesToValue(
        std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2
            || arguments[0].type() != typeid(Connection))
        {
            return false;
        }

        auto const& functionExpression =
            std::any_cast<Connection const&>(arguments[0]);

        auto const functionValueType = functionExpression.valueType();

        return !functionValueType.isFunction()
            && functionValueType.nativeType() == typeid(FunctionValue);
    }

    std::any LbindNeuron::evaluate(
        std::vector<std::any> const& arguments) const
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

        auto const& functionExpression =
            std::any_cast<Connection const&>(arguments[0]);

        auto const& fixedExpression =
            std::any_cast<Connection const&>(arguments[1]);

        auto const functionResult = functionExpression.output();

        if (functionResult.type() != typeid(FunctionValue))
        {
            throw std::invalid_argument(
                "lbind first argument did not produce a FunctionValue");
        }

        auto const& functionValue =
            std::any_cast<FunctionValue const&>(functionResult);

        auto const fixedValue = fixedExpression.output();

        return functionValue.connection.apply(fixedValue);
    }
}
