#ifndef AICPP_EXTRACT_NEURON_H
#define AICPP_EXTRACT_NEURON_H

#include "PolymorphicNeuron.h"

#include <any>
#include <vector>

namespace aicpp
{
    class ExtractNeuron : public PolymorphicNeuron
    {
        public:
            std::string const& name() const override
            {
                static std::string const name{"extract"};
                return name;
            }

            DslType inferSignature(
                std::vector<DslType> const& arguments) const override;

            std::any apply(
                std::vector<std::any> const& arguments,
                std::any const& input) const override;

            DslType inferConnectionSignature(
                std::vector<Connection> const& arguments) const override;

            bool evaluatesToValue(
                std::vector<std::any> const& arguments) const override;

            std::any evaluate(
                std::vector<std::any> const& arguments) const override;

        private:
            static std::pair<DslType, DslType> inferElementTypes(
                DslType const& containerType);
    };
}

#endif // AICPP_EXTRACT_NEURON_H
