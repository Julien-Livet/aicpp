#ifndef AICPP_CHESSDSLSYSTEM_H
#define AICPP_CHESSDSLSYSTEM_H

#include <map>
#include <string>

#include "aicpp/Neuron.h"

namespace aicpp
{
    std::map<std::string, Neuron> chessDslVariableNeurons();
    std::map<std::string, Neuron> chessDslPrimitiveNeurons();
}

#endif // AICPP_CHESSDSLSYSTEM_H
