#include <stdexcept>

#include "aicpp/Connection.h"
#include "aicpp/ForkNeuron.h"

namespace aicpp
{
    DslType ForkNeuron::inferSignature(std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 3)
            throw std::invalid_argument("fork expects exactly three arguments");

        auto const& outer = arguments[0];
        auto const& a = arguments[1];
        auto const& b = arguments[2];

        if (!outer.isFunction() || !a.isFunction() || !b.isFunction())
            throw std::invalid_argument("fork expects function signatures");

        if (outer.inputs().size() != 2 || a.inputs().size() != 1 || b.inputs().size() != 1)
            throw std::invalid_argument("fork expects a binary outer function and two unary branches");

        if (a.inputs()[0] != b.inputs()[0])
            throw std::invalid_argument("fork branches must have the same input type " + a.inputs()[0].string() + " " + b.inputs()[0].string());

        if (outer.inputs()[0] != a.output() || outer.inputs()[1] != b.output())
            throw std::invalid_argument("fork: outer input types must match branch output types");

        return DslType::function(a.inputs(), outer.output());
    }

    std::any ForkNeuron::apply(std::vector<std::any> const& arguments, std::any const& input) const
    {
        if (arguments.size() != 3)
            throw std::invalid_argument("fork expects exactly three arguments");

        for (auto const& argument : arguments)
        {
            if (argument.type() != typeid(Connection))
                throw std::invalid_argument("fork expects Connection arguments");
        }

        auto const& outer = std::any_cast<Connection const&>(arguments[0]);
        auto const& a = std::any_cast<Connection const&>(arguments[1]);
        auto const& b = std::any_cast<Connection const&>(arguments[2]);
        auto resultA = a.apply(input);
        auto resultB = b.apply(input);
        auto const* neuron = outer.neuron();

        if (neuron->isPolymorphic())
            throw std::invalid_argument("fork outer must be a native binary function");

        if (outer.inputs().size() != 2)
            throw std::invalid_argument("fork outer must have exactly two inputs");

        return neuron->invoke({resultA, resultB});
    }
}
