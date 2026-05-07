#ifndef AICPP_DSLSYSTEM_H
#define AICPP_DSLSYSTEM_H

#include <map>
#include <string>

#include "aicpp/Neuron.h"

namespace aicpp
{
    std::map<std::string, Neuron> dslVariableNeurons();
    std::map<std::string, Neuron> dslPrimitiveNeurons();
}

#endif // AICPP_DSLSYSTEM_H
