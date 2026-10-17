#ifndef AICPP_POLYMORPHIC_NEURON_H
#define AICPP_POLYMORPHIC_NEURON_H

#include <stdexcept>
#include <vector>

#include "aicpp/Connection.h"
#include "aicpp/Neuron.h"

namespace aicpp
{
    class PolymorphicNeuron : public NeuronBase
    {
        public:
            bool isPolymorphic() const override
            {
                return true;
            }

            std::type_index returnType() const override
            {
                throw std::logic_error("A polymorphic neuron has no fixed native return type");
            }

            std::vector<std::type_index> inputTypes() const override
            {
                throw std::logic_error("A polymorphic neuron has no fixed native input types");
            }

            virtual DslType inferSignature(std::vector<DslType> const& arguments) const = 0;

            DslType signature() const override
            {
                throw std::logic_error("A polymorphic neuron has no fixed signature");
            }

            std::any invoke(std::vector<std::any> const&) const override
            {
                throw std::logic_error("Direct invocation of a polymorphic neuron is not supported");
            }

            boost::json::value toJson() const override
            {
                throw std::logic_error("Serialization of a polymorphic neuron is not supported");
            }

            virtual std::any apply(std::vector<std::any> const& arguments, std::any const& input) const = 0;

            virtual bool evaluatesToValue() const
            {
                return false;
            }

            virtual std::any evaluate(std::vector<std::any> const&) const
            {
                throw std::logic_error("Value evaluation is not supported by this polymorphic neuron");
            }

            virtual DslType inferConnectionSignature(std::vector<Connection> const& arguments) const
            {
                DslType::Inputs signatures;
                signatures.reserve(arguments.size());

                for (auto const& argument : arguments)
                    signatures.emplace_back(argument.signature());

                return inferSignature(signatures);
            }

            virtual bool evaluatesToValue(std::vector<std::any> const& arguments) const
            {
                return evaluatesToValue();
            }

            virtual DslType inferConnectionSignature(std::vector<Connection> const& arguments, DslType const& expectedResultType) const
            {
                auto const inferred = inferConnectionSignature(arguments);

                if (inferred.output() != expectedResultType)
                    throw std::invalid_argument("Inferred result type does not match expected result type");

                return inferred;
            }
    };
}

#endif // AICPP_POLYMORPHIC_NEURON_H
