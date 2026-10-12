#ifndef AICPP_VALMIN_NEURON_H
#define AICPP_VALMIN_NEURON_H

#include "PolymorphicNeuron.h"

#include <any>
#include <vector>

namespace aicpp
{
    class ValminNeuron : public PolymorphicNeuron
    {
        public:
            std::string const& name() const override
            {
                static std::string const name{"valmin"};
                return name;
            }

            DslType inferSignature(
                std::vector<DslType> const& valuments) const override;

            std::any apply(
                std::vector<std::any> const& valuments,
                std::any const& input) const override;

            DslType inferConnectionSignature(
                std::vector<Connection> const& valuments) const override;

            bool evaluatesToValue() const override
            {
                return true;
            }

            std::any evaluate(
                std::vector<std::any> const& valuments) const override;

        private:
            DslType elementTypeFor(DslType const& container) const;
            Connection resolveFunction(
                Connection const& function,
                DslType const& elementType) const;
    };
}

#endif // AICPP_VALMIN_NEURON_H
