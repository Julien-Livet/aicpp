#ifndef AICPP_HODELDSLSYSTEM_H
#define AICPP_HODELDSLSYSTEM_H

#include <map>
#include <string>

#include "aicpp/Neuron.h"

namespace aicpp
{
    std::map<std::string, Neuron> hodelDslVariableNeurons();
    std::map<std::string, Neuron> hodelDslPrimitiveNeurons();
}

#endif // AICPP_HODELDSLSYSTEM_H
