// Automatically generated file. Do not modify.

#include "aicpp/HodelRegister.h"
#include "aicpp/ApplyNeuron.h"
#include "aicpp/ArgmaxNeuron.h"
#include "aicpp/ArgminNeuron.h"
#include "aicpp/ChainNeuron.h"
#include "aicpp/ComposeNeuron.h"
#include "aicpp/ExtractNeuron.h"
#include "aicpp/ForkNeuron.h"
#include "aicpp/LbindNeuron.h"
#include "aicpp/RbindNeuron.h"
#include "aicpp/ValmaxNeuron.h"
#include "aicpp/ValminNeuron.h"

namespace aicpp
{

NeuronRegistry makePolymorphicNeuronRegistry()
{
    static ApplyNeuron polymorphic_ApplyNeuron;
    static ArgmaxNeuron polymorphic_ArgmaxNeuron;
    static ArgminNeuron polymorphic_ArgminNeuron;
    static ChainNeuron polymorphic_ChainNeuron;
    static ComposeNeuron polymorphic_ComposeNeuron;
    static ExtractNeuron polymorphic_ExtractNeuron;
    static ForkNeuron polymorphic_ForkNeuron;
    static LbindNeuron polymorphic_LbindNeuron;
    static RbindNeuron polymorphic_RbindNeuron;
    static ValmaxNeuron polymorphic_ValmaxNeuron;
    static ValminNeuron polymorphic_ValminNeuron;

    NeuronRegistry registry;
    registry.emplace(polymorphic_ApplyNeuron.name(), &polymorphic_ApplyNeuron);
    registry.emplace(polymorphic_ArgmaxNeuron.name(), &polymorphic_ArgmaxNeuron);
    registry.emplace(polymorphic_ArgminNeuron.name(), &polymorphic_ArgminNeuron);
    registry.emplace(polymorphic_ChainNeuron.name(), &polymorphic_ChainNeuron);
    registry.emplace(polymorphic_ComposeNeuron.name(), &polymorphic_ComposeNeuron);
    registry.emplace(polymorphic_ExtractNeuron.name(), &polymorphic_ExtractNeuron);
    registry.emplace(polymorphic_ForkNeuron.name(), &polymorphic_ForkNeuron);
    registry.emplace(polymorphic_LbindNeuron.name(), &polymorphic_LbindNeuron);
    registry.emplace(polymorphic_RbindNeuron.name(), &polymorphic_RbindNeuron);
    registry.emplace(polymorphic_ValmaxNeuron.name(), &polymorphic_ValmaxNeuron);
    registry.emplace(polymorphic_ValminNeuron.name(), &polymorphic_ValminNeuron);

    return registry;
}

} // namespace aicpp
