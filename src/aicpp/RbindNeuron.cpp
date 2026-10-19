#include "aicpp/RbindNeuron.h"
#include "aicpp/FunctionValue.h"
#include "aicpp/FunctionAdapterNeuron.h"

#include <stdexcept>

namespace aicpp
{
    DslType RbindNeuron::inferSignature(std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("rbind requires exactly two arguments");

        auto const& function = arguments[0];
        auto const& fixed = arguments[1];

        if (!function.isFunction() || function.inputs().empty())
            throw std::invalid_argument("rbind requires a function with at least one argument");

        if (!fixed.isFunction() || !fixed.inputs().empty())
            throw std::invalid_argument("rbind requires a value-producing expression");

        auto const inputs{function.inputs()};

        if (fixed.output() != inputs.back())
            throw std::invalid_argument("rbind fixed argument type does not match the last function input");

        DslType::Inputs remainingInputs(inputs.begin(), inputs.end() - 1);

        if (remainingInputs.empty())
            return function.output();

        return DslType::function(remainingInputs, function.output());
    }

    std::any RbindNeuron::apply(std::vector<std::any> const& arguments, std::any const& input) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("rbind requires exactly two arguments");

        if (arguments[0].type() != typeid(Connection) || arguments[1].type() != typeid(Connection))
            throw std::invalid_argument("rbind arguments must be connections");

        auto const& function = std::any_cast<Connection const&>(arguments[0]);
        auto const& fixedConnection = std::any_cast<Connection const&>(arguments[1]);
        auto const signature = function.signature();

        if (!signature.isFunction() || signature.inputs().empty())
            throw std::invalid_argument("rbind requires a function with at least one input");

        auto const fixed = fixedConnection.output();

        if (fixed.type() != signature.inputs().back().nativeType())
            throw std::invalid_argument("rbind fixed argument has an incompatible type");

        if (signature.inputs().size() == 1)
            return function.apply(fixed);

        if (input.has_value())
        {
            auto const expectedInput = signature.inputs().front();

            if (input.type() != expectedInput.nativeType())
                throw std::invalid_argument("rbind received an incompatible input");
        }

        NeuronBase const* nativeNeuron = function.neuron();

        if (nativeNeuron->isPolymorphic())
        {
            auto const* adapter = dynamic_cast<FunctionAdapterNeuron const*>(nativeNeuron);

            if (adapter == nullptr)
                throw std::invalid_argument("rbind requires a native function or FunctionAdapterNeuron");

            nativeNeuron = adapter->adaptedNeuron();
        }

        if (!input.has_value())
            throw std::invalid_argument("rbind requires an input when evaluating a partially applied function");

        return nativeNeuron->invoke({input, fixed});
    }

    DslType RbindNeuron::inferConnectionSignature(std::vector<Connection> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("rbind requires exactly two arguments");

        auto const& functionExpression = arguments[0];
        auto const& fixedExpression = arguments[1];
        auto const functionSignature = functionExpression.signature();
        auto const fixedType = fixedExpression.valueType();

        if (!functionSignature.isFunction() || functionSignature.inputs().empty())
            throw std::invalid_argument("rbind requires a function with at least one input");

        if (functionSignature.output().nativeType() == typeid(FunctionValue))
        {
            auto const connection{std::any_cast<FunctionValue>(functionExpression.output()).connection};
            auto const inputs{connection.signature().inputs()};

            if (fixedType.output() != inputs.back())
                throw std::invalid_argument("rbind fixed argument type does not match the last function input");

            DslType::Inputs remainingInputs(inputs.begin(), inputs.end() - 1);

            if (remainingInputs.empty())
                return makeDslType<FunctionValue>();

            return DslType::function(remainingInputs, makeDslType<FunctionValue>());
        }

        auto const inputs{functionSignature.inputs()};

        if (inputs.back().isFunction())
        {
            if (fixedExpression.signature() != inputs.back())
                throw std::invalid_argument("rbind fixed argument type does not match the last function input");
        }
        else
        {
            if (fixedType != inputs.back())
                throw std::invalid_argument("rbind fixed argument type does not match the last function input");
        }

        DslType::Inputs remainingInputs(inputs.begin(), inputs.end() - 1);

        if (remainingInputs.empty())
            return functionSignature.output();

        return DslType::function(remainingInputs, functionSignature.output());
    }

    bool RbindNeuron::evaluatesToValue(std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2 || arguments[0].type() != typeid(Connection) || arguments[1].type() != typeid(Connection))
            return false;

        auto const& functionExpression = std::any_cast<Connection const&>(arguments[0]);
        auto const functionSignature = functionExpression.signature();

        if (functionSignature.isFunction() && functionSignature.inputs().size() == 1)
            return true;

        auto const functionValueType = functionExpression.valueType();

        return !functionValueType.isFunction() && functionValueType.nativeType() == typeid(FunctionValue);
    }

    std::any RbindNeuron::evaluate(std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("rbind requires exactly two arguments");

        if (arguments[0].type() != typeid(Connection) || arguments[1].type() != typeid(Connection))
            throw std::invalid_argument("rbind arguments must be connections");

        auto const& functionExpression = std::any_cast<Connection const&>(arguments[0]);
        auto const& fixedExpression = std::any_cast<Connection const&>(arguments[1]);
        auto const functionResult = functionExpression.output();

        if (functionResult.type() == typeid(FunctionValue))
        {
            auto const& functionValue = std::any_cast<FunctionValue const&>(functionResult);
            auto const fixedValue = fixedExpression.output();

            return functionValue.connection.apply(fixedValue);
        }

        if (functionResult.type() == typeid(Connection))
        {
            auto const& functionValue = std::any_cast<Connection const&>(functionResult);
            auto const fixedValue = fixedExpression.output();

            return functionValue.apply(fixedValue);
        }

        throw std::invalid_argument("rbind expected a FunctionValue or a Connection");
    }
}
