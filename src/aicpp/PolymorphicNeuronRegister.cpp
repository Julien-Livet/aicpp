// Automatically generated file. Do not modify.

#include "aicpp/HodelRegister.h"
#include "aicpp/ApplyNeuron.h"
#include "aicpp/ChainNeuron.h"
#include "aicpp/ComposeNeuron.h"
#include "aicpp/ExtractNeuron.h"
#include "aicpp/ForkNeuron.h"

namespace aicpp
{

NeuronRegistry makePolymorphicNeuronRegistry()
{
    static ApplyNeuron polymorphic_ApplyNeuron;
    static ChainNeuron polymorphic_ChainNeuron;
    static ComposeNeuron polymorphic_ComposeNeuron;
    static ExtractNeuron polymorphic_ExtractNeuron;
    static ForkNeuron polymorphic_ForkNeuron;

    NeuronRegistry registry;
    registry.emplace(polymorphic_ApplyNeuron.name(), &polymorphic_ApplyNeuron);
    registry.emplace(polymorphic_ChainNeuron.name(), &polymorphic_ChainNeuron);
    registry.emplace(polymorphic_ComposeNeuron.name(), &polymorphic_ComposeNeuron);
    registry.emplace(polymorphic_ExtractNeuron.name(), &polymorphic_ExtractNeuron);
    registry.emplace(polymorphic_ForkNeuron.name(), &polymorphic_ForkNeuron);

    return registry;
}

} // namespace aicpp
