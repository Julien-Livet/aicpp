#include <stdexcept>
#include <utility>

#include "aicpp/Connection.h"
#include "aicpp/ExtractNeuron.h"
#include "aicpp/Hodel.h"

namespace aicpp
{
    DslType ExtractNeuron::inferSignature(
        std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "extract expects exactly two arguments");
        }

        auto const& container = arguments[0];
        auto const& condition = arguments[1];

        auto const [containerType, elementType] =
            inferElementTypes(container);

        if (!condition.isFunction())
        {
            throw std::invalid_argument(
                "extract expects a function as its condition");
        }

        if (condition.inputs().size() != 1)
        {
            throw std::invalid_argument(
                "extract condition must be unary");
        }

        if (condition.inputs()[0] != elementType)
        {
            throw std::invalid_argument(
                "extract condition input type does not match "
                "the container element type");
        }

        if (condition.output() != makeDslType<hodel::Boolean>())
        {
            throw std::invalid_argument(
                "extract condition must return a Boolean");
        }

        return DslType::function(
            {containerType},
            elementType);
    }

    std::any ExtractNeuron::apply(
        std::vector<std::any> const& arguments,
        std::any const& input) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "extract expects exactly two arguments");
        }

        if (arguments[1].type() != typeid(Connection))
        {
            throw std::invalid_argument(
                "extract expects a Connection as its condition");
        }

        auto const& condition =
            std::any_cast<Connection const&>(arguments[1]);

        if (input.type() == typeid(hodel::GridVector))
        {
            auto const& grids =
                std::any_cast<hodel::GridVector const&>(input);

            for (auto const& grid : grids)
            {
                auto const result = condition.apply(std::any{grid});

                if (result.type() != typeid(hodel::Boolean))
                {
                    throw std::invalid_argument(
                        "extract condition must return a Boolean");
                }

                if (std::any_cast<hodel::Boolean>(result))
                {
                    return std::any{grid};
                }
            }

            return std::any{};
        }

        if (input.type() == typeid(hodel::Objects))
        {
            auto const& objects =
                std::any_cast<hodel::Objects const&>(input);

            for (auto const& object : objects)
            {
                auto const result = condition.apply(std::any{object});

                if (result.type() != typeid(hodel::Boolean))
                {
                    throw std::invalid_argument(
                        "extract condition must return a Boolean");
                }

                if (std::any_cast<hodel::Boolean>(result))
                {
                    return std::any{object};
                }
            }

            return std::any{};
        }

        throw std::invalid_argument(
            "extract expects a GridVector or Objects input");
    }

    DslType ExtractNeuron::inferConnectionSignature(
        std::vector<Connection> const& arguments) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "extract expects exactly two arguments");
        }

        auto const& container = arguments[0];
        auto const& condition = arguments[1];

        auto const containerSignature = container.signature();

        auto const containerType = containerSignature.isFunction()
            ? containerSignature.output()
            : containerSignature;

        auto const [expectedContainerType, elementType] =
            inferElementTypes(containerType);

        auto const conditionSignature = condition.signature();

        if (!conditionSignature.isFunction())
        {
            throw std::invalid_argument(
                "extract expects a function as its condition");
        }

        if (conditionSignature.inputs().size() != 1)
        {
            throw std::invalid_argument(
                "extract condition must be unary");
        }

        if (conditionSignature.inputs()[0] != elementType)
        {
            throw std::invalid_argument(
                "extract condition input type does not match "
                "the container element type");
        }

        if (conditionSignature.output() != makeDslType<hodel::Boolean>())
        {
            throw std::invalid_argument(
                "extract condition must return a Boolean");
        }

        return DslType::function(
            {expectedContainerType},
            elementType);
    }

    bool ExtractNeuron::evaluatesToValue(
        std::vector<std::any> const& arguments) const
    {
        return arguments.size() == 2
            && arguments[0].type() == typeid(Connection)
            && arguments[1].type() == typeid(Connection);
    }

    std::any ExtractNeuron::evaluate(
        std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2)
        {
            throw std::invalid_argument(
                "extract expects exactly two arguments");
        }

        if (arguments[0].type() != typeid(Connection))
        {
            throw std::invalid_argument(
                "extract expects a Connection as its first argument");
        }

        auto const& container =
            std::any_cast<Connection const&>(arguments[0]);

        return apply(arguments, container.output());
    }

    std::pair<DslType, DslType> ExtractNeuron::inferElementTypes(
        DslType const& containerType)
    {
        if (containerType == makeDslType<hodel::GridVector>())
        {
            return {
                makeDslType<hodel::GridVector>(),
                makeDslType<hodel::Grid>()
            };
        }

        if (containerType == makeDslType<hodel::Objects>())
        {
            return {
                makeDslType<hodel::Objects>(),
                makeDslType<hodel::Object>()
            };
        }

        throw std::invalid_argument(
            "extract expects a GridVector or Objects container");
    }
}
