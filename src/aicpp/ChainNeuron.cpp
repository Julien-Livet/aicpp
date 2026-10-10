#include <stdexcept>

#include "aicpp/ChainNeuron.h"
#include "aicpp/Connection.h"

namespace aicpp
{
    DslType ChainNeuron::inferSignature(
        std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 3)
            throw std::invalid_argument(
                "chain expects exactly three arguments");

        auto const& h = arguments[0];
        auto const& g = arguments[1];
        auto const& f = arguments[2];

        if (!h.isFunction() || !g.isFunction() || !f.isFunction())
            throw std::invalid_argument(
                "chain expects function signatures");

        if (h.inputs().size() != 1
            || g.inputs().size() != 1
            || f.inputs().size() != 1)
            throw std::invalid_argument(
                "chain expects unary functions");

        if (g.inputs()[0] != f.output())
            throw std::invalid_argument(
                "chain: incompatible types between f and g");

        if (h.inputs()[0] != g.output())
            throw std::invalid_argument(
                "chain: incompatible types between g and h");

        return DslType::function(
            f.inputs(),
            h.output());
    }

    std::any ChainNeuron::apply(
        std::vector<std::any> const& arguments,
        std::any const& input) const
    {
        if (arguments.size() != 3)
            throw std::invalid_argument(
                "chain expects exactly three arguments");

        for (auto const& argument : arguments)
        {
            if (argument.type() != typeid(Connection))
                throw std::invalid_argument(
                    "chain expects Connection arguments");
        }

        auto const& h =
            std::any_cast<Connection const&>(arguments[0]);
        auto const& g =
            std::any_cast<Connection const&>(arguments[1]);
        auto const& f =
            std::any_cast<Connection const&>(arguments[2]);

        auto intermediate = f.apply(input);
        intermediate = g.apply(intermediate);
        return h.apply(intermediate);
    }
}
