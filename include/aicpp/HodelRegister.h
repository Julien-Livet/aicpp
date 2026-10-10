#ifndef AICPP_HODELREGISTER_H
#define AICPP_HODELREGISTER_H

#include <map>

#include "Neuron.h"

namespace aicpp
{
    using NeuronRegistry =
    std::map<std::string, NeuronBase const*>;

    NeuronRegistry makeNeuronRegistry();
}

#endif // AICPP_HODELREGISTER_H
