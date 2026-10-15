#include "aicpp/LbindNeuron.h"
#include "aicpp/FunctionValue.h"
#include "aicpp/FunctionAdapterNeuron.h"

#include <stdexcept>

namespace aicpp
{
    DslType LbindNeuron::inferSignature(
        std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("lbind requires exactly two arguments");

        auto const& function = arguments[0];
        auto const& fixed = arguments[1];

        if (!function.isFunction() || function.inputs().empty())
            throw std::invalid_argument("lbind requires a function with at least one argument");

        if (!fixed.isFunction() || !fixed.inputs().empty())
            throw std::invalid_argument("lbind requires a value-producing expression");

        auto const inputs{function.inputs()};

        if (fixed.output() != inputs.back())
            throw std::invalid_argument("lbind fixed argument type does not match the first function input");

        DslType::Inputs remainingInputs(
            inputs.begin() + 1,
            inputs.end());

        if (remainingInputs.empty())
            return function.output();

        return DslType::function(
            remainingInputs,
            function.output());
    }

    std::any LbindNeuron::apply(
        std::vector<std::any> const& arguments,
        std::any const& input) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("lbind requires exactly two arguments");

        if (arguments[0].type() != typeid(Connection) || arguments[1].type() != typeid(Connection))
            throw std::invalid_argument("lbind arguments must be connections");

        auto const& function = std::any_cast<Connection const&>(arguments[0]);
        auto const& fixedConnection = std::any_cast<Connection const&>(arguments[1]);
        auto const signature = function.signature();

        if (!signature.isFunction() || signature.inputs().empty())
            throw std::invalid_argument("lbind requires a function with at least one input");

        auto const fixed = fixedConnection.output();

        if (fixed.type() != signature.inputs()[0].nativeType())
            throw std::invalid_argument("lbind fixed argument has an incompatible type");

        if (signature.inputs().size() == 1)
            return function.apply(fixed);

        if (input.has_value())
        {
            auto const expectedInput = signature.inputs().back();

            if (input.type() != expectedInput.nativeType())
                throw std::invalid_argument("lbind received an incompatible input");
        }

        NeuronBase const* nativeNeuron = function.neuron();

        if (nativeNeuron->isPolymorphic())
        {
            auto const* adapter = dynamic_cast<FunctionAdapterNeuron const*>(nativeNeuron);

            if (adapter == nullptr)
                throw std::invalid_argument("lbind requires a native function or FunctionAdapterNeuron");

            nativeNeuron = adapter->adaptedNeuron();
        }

        if (!input.has_value())
            throw std::invalid_argument("lbind requires an input when evaluating a partially applied function");

        return nativeNeuron->invoke({fixed, input});
    }

    DslType LbindNeuron::inferConnectionSignature(
        std::vector<Connection> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("lbind requires exactly two arguments");

        auto const& functionExpression = arguments[0];
        auto const& fixedExpression = arguments[1];

        auto const functionSignature = functionExpression.signature();
        auto const fixedType = fixedExpression.valueType();

        if (!functionSignature.isFunction() || functionSignature.inputs().empty())
            throw std::invalid_argument("lbind requires a function with at least one input");

        if (functionSignature.output().nativeType() == typeid(FunctionValue))
        {
            auto const connection{std::any_cast<FunctionValue>(functionExpression.output()).connection};
            auto const inputs{connection.signature().inputs()};

            if (fixedType.output() != inputs[0])
                throw std::invalid_argument("lbind fixed argument type does not match the first function input");

            DslType::Inputs remainingInputs(
                inputs.begin() + 1,
                inputs.end());

            if (remainingInputs.empty())
                return makeDslType<FunctionValue>();

            return DslType::function(
                remainingInputs,
                makeDslType<FunctionValue>());
        }

        auto const inputs{functionSignature.inputs()};

        if (fixedType != inputs[0])
            throw std::invalid_argument("lbind fixed argument type does not match the first function input");

        DslType::Inputs remainingInputs(
            inputs.begin() + 1,
            inputs.end());

        if (remainingInputs.empty())
            return functionSignature.output();

        return DslType::function(
            remainingInputs,
            functionSignature.output());
    }

    bool LbindNeuron::evaluatesToValue(
        std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2
            || arguments[0].type() != typeid(Connection)
            || arguments[1].type() != typeid(Connection))
        {
            return false;
        }

        auto const& functionExpression =
            std::any_cast<Connection const&>(arguments[0]);

        auto const functionSignature = functionExpression.signature();

        if (functionSignature.isFunction()
            && functionSignature.inputs().size() == 1)
        {
            return true;
        }

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

        if (functionResult.type() == typeid(FunctionValue))
        {
            auto const& functionValue =
                std::any_cast<FunctionValue const&>(functionResult);

            auto const fixedValue = fixedExpression.output();

            return functionValue.connection.apply(fixedValue);
        }

        if (functionResult.type() == typeid(Connection))
        {
            auto const& functionValue =
                std::any_cast<Connection const&>(functionResult);

            auto const fixedValue = fixedExpression.output();

            return functionValue.apply(fixedValue);
        }

        throw std::invalid_argument(
            "lbind expected a FunctionValue or a Connection");
    }
}
