#ifndef AICPP_COMPOSE_NEURON_H
#define AICPP_COMPOSE_NEURON_H

#include <any>
#include <stdexcept>
#include <vector>

#include "aicpp/Connection.h"
#include "aicpp/PolymorphicNeuron.h"

namespace aicpp
{
    class ComposeNeuron : public PolymorphicNeuron
    {
        public:
            DslType inferSignature(std::vector<DslType> const& arguments) const override
            {
                if (arguments.size() != 2)
                    throw std::invalid_argument("compose requires exactly two arguments");

                return inferComposeSignature(arguments[0], arguments[1]);
            }
            
            std::string const& name() const
            {
                static std::string const value{"compose"};

                return value;
            }

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override
            {
                if (arguments.size() != 2)
                {
                    throw std::invalid_argument(
                        "compose requires exactly two arguments");
                }

                if (arguments[0].type() != typeid(Connection) ||
                    arguments[1].type() != typeid(Connection))
                {
                    throw std::invalid_argument(
                        "compose arguments must be connections");
                }

                auto const& f =
                    std::any_cast<Connection const&>(arguments[0]);

                auto const& g =
                    std::any_cast<Connection const&>(arguments[1]);

                auto intermediate = g.apply(input);
                return f.apply(intermediate);
            }

            boost::json::value toJson() const override
            {
                using namespace boost::json;

                object obj;

                obj["name"] = name();
                obj["polymorphic"] = true;

                return obj;
            }
    };
}

#endif // AICPP_COMPOSE_NEURON_H
