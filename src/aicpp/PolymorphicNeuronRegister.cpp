// Automatically generated file. Do not modify.

#include "aicpp/HodelRegister.h"
#include "aicpp/ComposeNeuron.h"
#include "aicpp/ChainNeuron.h"
#include "aicpp/ForkNeuron.h"
#include "aicpp/ExtractNeuron.h"

namespace aicpp
{

NeuronRegistry makePolymorphicNeuronRegistry()
{
    static ComposeNeuron compose;
    static ChainNeuron chain;
    static ForkNeuron fork;
    static ExtractNeuron extract;

    NeuronRegistry registry;
    registry.emplace(compose.name(), &compose);
    registry.emplace(chain.name(), &chain);
    registry.emplace(fork.name(), &fork);
    registry.emplace(extract.name(), &extract);

    return registry;
}

} // namespace aicpp
