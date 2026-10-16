#include <stdexcept>
#include <string>
#include <vector>

#include "aicpp/ArgminNeuron.h"
#include "aicpp/Connection.h"
#include "aicpp/FunctionValue.h"
#include "aicpp/Hodel.h"
#include "aicpp/FunctionOverloadNeuron.h"

namespace
{
    template<typename T>
    std::any findMinimum(std::vector<T> const& values, aicpp::Connection const& function)
    {
        if (values.empty())
            throw std::invalid_argument("argmin cannot process an empty container");

        auto const evaluate = [&function] (T const& value)
        {
            auto const result = function.apply(std::any{value});

            if (result.type() != typeid(hodel::Integer))
                throw std::invalid_argument("argmin function must return an Integer");

            return std::any_cast<hodel::Integer>(result);
        };

        auto best = values.begin();
        auto bestScore = evaluate(*best);

        for (auto it = std::next(best); it != values.end(); ++it)
        {
            auto const score = evaluate(*it);

            if (hodel::greater(bestScore, score))
            {
                best = it;
                bestScore = score;
            }
        }

        return std::any{*best};
    }

    template<typename Container>
    std::vector<typename Container::value_type> asVector(Container const& container)
    {
        return {container.begin(), container.end()};
    }
}

namespace aicpp
{
    DslType ArgminNeuron::inferSignature(std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("argmin expects exactly two arguments");

        auto const& container = arguments[0];
        auto const& function = arguments[1];

        DslType elementType{std::type_index{typeid(hodel::Integer)}};
        DslType resultType{std::type_index{typeid(hodel::Integer)}};

        if (container == makeDslType<hodel::IntegerSet>() || container == makeDslType<hodel::IntegerVector>())
        {
            elementType = makeDslType<hodel::Integer>();
            resultType = elementType;
        }
        else if (container == makeDslType<hodel::GridVector>())
        {
            elementType = makeDslType<hodel::Grid>();
            resultType = elementType;
        }
        else if (container == makeDslType<hodel::Objects>())
        {
            elementType = makeDslType<hodel::Object>();
            resultType = elementType;
        }
        else if (container == makeDslType<hodel::Indices>())
        {
            elementType = makeDslType<hodel::IntegerTuple>();
            resultType = elementType;
        }
        else if (container == makeDslType<hodel::IntegerTuple>())
        {
            elementType = makeDslType<hodel::Integer>();
            resultType = makeDslType<hodel::Integer>();
        }
        else
            throw std::invalid_argument("argmin does not support this container type");

        if (!function.isFunction() || function.inputs().size() != 1
            || function.inputs()[0] != elementType || function.output() != makeDslType<hodel::Integer>())
            throw std::invalid_argument("inferSignature: argmin expects a function from the element type to Integer");

        return DslType::function({container}, resultType);
    }

    std::any ArgminNeuron::apply(std::vector<std::any> const& arguments, std::any const& input) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("argmin expects exactly two arguments");

        if (arguments[1].type() != typeid(Connection))
            throw std::invalid_argument("argmin expects a Connection as its function");

        auto const& function = std::any_cast<Connection const&>(arguments[1]);

        if (input.type() == typeid(hodel::IntegerSet))
        {
            auto const resolvedFunction = resolveFunction(function, makeDslType<hodel::Integer>());

            return findMinimum(asVector(std::any_cast<hodel::IntegerSet const&>(input)), resolvedFunction);
        }

        if (input.type() == typeid(hodel::IntegerVector))
        {
            auto const resolvedFunction = resolveFunction(function, makeDslType<hodel::Integer>());

            return findMinimum(std::any_cast<hodel::IntegerVector const&>(input), resolvedFunction);
        }

        if (input.type() == typeid(hodel::GridVector))
        {
            auto const resolvedFunction = resolveFunction(function, makeDslType<hodel::Grid>());

            return findMinimum(std::any_cast<hodel::GridVector const&>(input), resolvedFunction);
        }

        if (input.type() == typeid(hodel::Objects))
        {
            auto const resolvedFunction = resolveFunction(function, makeDslType<hodel::Object>());

            return findMinimum(asVector(std::any_cast<hodel::Objects const&>(input)), resolvedFunction);
        }

        if (input.type() == typeid(hodel::Object))
        {
            auto const resolvedFunction = resolveFunction(function, makeDslType<hodel::Cell>());

            return findMinimum(asVector(std::any_cast<hodel::Object const&>(input)), resolvedFunction);
        }

        if (input.type() == typeid(hodel::Indices))
        {
            auto const resolvedFunction = resolveFunction(function, makeDslType<hodel::IntegerTuple>());

            return findMinimum(asVector(std::any_cast<hodel::Indices const&>(input)), resolvedFunction);
        }

        if (input.type() == typeid(hodel::IntegerTuple))
        {
            auto const resolvedFunction = resolveFunction(function, makeDslType<hodel::Integer>());
            auto const tuple = std::any_cast<hodel::IntegerTuple const&>(input);

            return findMinimum(hodel::IntegerVector{tuple.first, tuple.second}, resolvedFunction);
        }

        if (input.type() == typeid(hodel::Grid))
        {
            auto const resolvedFunction = resolveFunction(function, makeDslType<hodel::IntegerVector>());

            return findMinimum(std::any_cast<hodel::Grid const&>(input), resolvedFunction);
        }

        throw std::invalid_argument("argmin received an unsupported container type");
    }

    DslType ArgminNeuron::inferConnectionSignature(std::vector<Connection> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("argmin expects exactly two arguments");

        auto const containerSignature = arguments[0].valueType();
        auto const elementType = elementTypeFor(containerSignature);
        auto const* overload = dynamic_cast<FunctionOverloadNeuron const*>(arguments[1].neuron());

        if (overload != nullptr)
        {
            auto const expectedFunction = DslType::function({elementType}, makeDslType<hodel::Integer>());

            overload->resolve(expectedFunction);
        }
        else
        {
            auto const functionSignature = arguments[1].signature();

            if (!functionSignature.isFunction() || functionSignature.inputs().size() != 1
                || functionSignature.inputs().front() != elementType || functionSignature.output() != makeDslType<hodel::Integer>())
                throw std::invalid_argument("inferConnectionSignature: argmin expects a function from the element type to Integer");
        }

        return DslType::function({containerSignature}, elementType);
    }

    DslType ArgminNeuron::elementTypeFor(DslType const& container) const
    {
        if (container.isFunction())
            throw std::invalid_argument("argmin expects a container, not a function");

        auto const nativeType = container.nativeType();

        if (nativeType == typeid(hodel::IntegerSet) || nativeType == typeid(hodel::IntegerVector))
            return makeDslType<hodel::Integer>();

        if (nativeType == typeid(hodel::GridVector))
            return makeDslType<hodel::Grid>();

        if (nativeType == typeid(hodel::Object))
            return makeDslType<hodel::Cell>();

        if (nativeType == typeid(hodel::Objects))
            return makeDslType<hodel::Object>();

        if (nativeType == typeid(hodel::Indices))
            return makeDslType<hodel::IntegerTuple>();

        if (nativeType == typeid(hodel::IntegerTuple))
            return makeDslType<hodel::Integer>();

        if (nativeType == typeid(hodel::Grid))
            return makeDslType<hodel::IntegerVector>();

        throw std::invalid_argument("argmin does not support this container type");
    }

    Connection ArgminNeuron::resolveFunction(Connection const& function, DslType const& elementType) const
    {
        auto const* overload = dynamic_cast<FunctionOverloadNeuron const*>(function.neuron());

        if (overload == nullptr)
        {
            auto const signature = function.signature();

            if (!signature.isFunction() || signature.inputs().size() != 1
                || signature.inputs().front() != elementType || signature.output() != makeDslType<hodel::Integer>())
                throw std::invalid_argument("resolveFunction: argmin expects a function from the element type to Integer");

            return function;
        }

        auto const expectedSignature = DslType::function({elementType}, makeDslType<hodel::Integer>());

        auto const* selected = overload->resolve(expectedSignature);

        return Connection{selected, {}};
    }

    std::any ArgminNeuron::evaluate(std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("argmin expects exactly two arguments");

        if (arguments[0].type() != typeid(Connection) || arguments[1].type() != typeid(Connection))
            throw std::invalid_argument("argmin arguments must be connections");

        auto const& containerConnection = std::any_cast<Connection const&>(arguments[0]);

        auto const container = containerConnection.output();

        return apply(arguments, container);
    }
}
