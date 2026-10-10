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
    };
}

#endif // AICPP_EXTRACT_NEURON_H
