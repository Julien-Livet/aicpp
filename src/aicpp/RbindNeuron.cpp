#include "aicpp/RbindNeuron.h"
#include "aicpp/FunctionValue.h"

#include <stdexcept>

namespace aicpp
{
    DslType RbindNeuron::inferSignature(
        std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "rbind requires exactly two arguments");
        }

        auto const& function = arguments[0];
        auto const& fixed = arguments[1];

        if (!function.isFunction()
            || function.inputs().size() < 2)
        {
            throw std::invalid_argument(
                "rbind requires a function with at least two arguments");
        }

        if (!fixed.isFunction()
            || !fixed.inputs().empty())
        {
            throw std::invalid_argument(
                "rbind requires a value-producing expression");
        }

        if (fixed.output() != function.inputs()[1])
        {
            throw std::invalid_argument(
                "rbind fixed argument type does not match "
                "the second function input");
        }

        DslType::Inputs remainingInputs(
            function.inputs().begin(),
            function.inputs().end() - 1);

        if (remainingInputs.size() != 1)
        {
            throw std::invalid_argument(
                "rbind currently supports only binary functions");
        }

        return DslType::function(
            remainingInputs,
            function.output());
    }

    DslType RbindNeuron::inferConnectionSignature(
        std::vector<Connection> const& arguments) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "rbind requires exactly two arguments");
        }

        auto const& functionExpression = arguments[0];
        auto const& fixedExpression = arguments[1];

        auto const functionValueType =
            functionExpression.valueType();

        if (!functionValueType.isFunction()
            && functionValueType.nativeType() == typeid(FunctionValue))
        {
            auto const fixedSignature = fixedExpression.signature();

            if (!fixedSignature.isFunction()
                || !fixedSignature.inputs().empty())
            {
                throw std::invalid_argument(
                    "rbind requires a value-producing expression");
            }

            return fixedSignature.output();
        }

        return inferSignature({
            functionExpression.signature(),
            fixedExpression.signature()
        });
    }

    bool RbindNeuron::evaluatesToValue(
        std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2
            || arguments[0].type() != typeid(Connection))
        {
            return false;
        }

        auto const& functionExpression =
            std::any_cast<Connection const&>(arguments[0]);

        auto const functionValueType =
            functionExpression.valueType();

        return !functionValueType.isFunction()
            && functionValueType.nativeType() == typeid(FunctionValue);
    }

    std::any RbindNeuron::evaluate(
        std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "rbind requires exactly two arguments");
        }

        if (arguments[0].type() != typeid(Connection)
            || arguments[1].type() != typeid(Connection))
        {
            throw std::invalid_argument(
                "rbind arguments must be connections");
        }

        auto const& functionExpression =
            std::any_cast<Connection const&>(arguments[0]);

        auto const& fixedExpression =
            std::any_cast<Connection const&>(arguments[1]);

        auto const functionResult = functionExpression.output();

        if (functionResult.type() != typeid(FunctionValue))
        {
            throw std::invalid_argument(
                "rbind expected a FunctionValue");
        }

        auto const& functionValue =
            std::any_cast<FunctionValue const&>(functionResult);

        auto const fixedValue = fixedExpression.output();

        return functionValue.connection.apply(fixedValue);
    }

    std::any RbindNeuron::apply(
        std::vector<std::any> const& arguments,
        std::any const& input) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "rbind requires exactly two arguments");
        }

        if (arguments[0].type() != typeid(Connection)
            || arguments[1].type() != typeid(Connection))
        {
            throw std::invalid_argument(
                "rbind arguments must be connections");
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
                "rbind requires a function with at least two arguments");
        }

        if (input.type() != signature.inputs()[0].nativeType())
        {
            throw std::invalid_argument(
                "rbind received an incompatible input");
        }

        if (function.neuron()->isPolymorphic())
        {
            throw std::invalid_argument(
                "rbind currently requires a native function");
        }

        auto const fixed = fixedConnection.output();

        if (fixed.type() != signature.inputs()[1].nativeType())
        {
            throw std::invalid_argument(
                "rbind fixed argument has an incompatible type");
        }

        return function.neuron()->invoke({input, fixed});
    }
}