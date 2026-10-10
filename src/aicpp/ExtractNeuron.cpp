#include <stdexcept>

#include "aicpp/Connection.h"
#include "aicpp/ExtractNeuron.h"
#include "aicpp/Hodel.h"

namespace aicpp
{
    DslType ExtractNeuron::inferSignature(
        std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument(
                "extract expects exactly two arguments");

        auto const& container = arguments[0];
        auto const& condition = arguments[1];

        if (container != makeDslType<hodel::GridVector>())
            throw std::invalid_argument(
                "extract expects a GridVector container");

        if (!condition.isFunction())
            throw std::invalid_argument(
                "extract expects a function as its condition");

        if (condition.inputs().size() != 1)
            throw std::invalid_argument(
                "extract condition must be unary");

        if (condition.inputs()[0] != makeDslType<hodel::Grid>())
            throw std::invalid_argument(
                "extract condition must accept a Grid");

        if (condition.output() != makeDslType<hodel::Boolean>())
            throw std::invalid_argument(
                "extract condition must return a Boolean");

        return DslType::function(
            {makeDslType<hodel::GridVector>()},
            makeDslType<hodel::Grid>());
    }

    std::any ExtractNeuron::apply(
        std::vector<std::any> const& arguments,
        std::any const& input) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument(
                "extract expects exactly two arguments");

        if (input.type() != typeid(hodel::GridVector))
            throw std::invalid_argument(
                "extract expects a GridVector input");

        if (arguments[1].type() != typeid(Connection))
            throw std::invalid_argument(
                "extract expects a Connection as its condition");

        auto const& condition =
            std::any_cast<Connection const&>(arguments[1]);

        auto const& grids =
            std::any_cast<hodel::GridVector const&>(input);

        for (auto const& grid : grids)
        {
            auto const result = condition.apply(std::any{grid});

            if (result.type() != typeid(hodel::Boolean))
                throw std::invalid_argument(
                    "extract condition must return a Boolean");

            if (std::any_cast<hodel::Boolean>(result))
                return grid;
        }

        return std::any{};
    }
}
