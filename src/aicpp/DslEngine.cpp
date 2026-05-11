#include "aicpp/DslEngine.h"
#include "aicpp/DslSystem.h"
#include "aicpp/Hodel.h"

using namespace aicpp;

DslEngine::DslEngine(std::function<double(std::any, std::any)> const heuristic,
                     size_t bo_n_init, size_t bo_top_k, size_t bo_count_max) : heuristic_{heuristic}, bo_n_init_{bo_n_init}, bo_top_k_{bo_top_k}, bo_count_max_{bo_count_max}
{
    variableNeurons_ = dslVariableNeurons();
    primitiveNeurons_ = dslPrimitiveNeurons();

    for (const auto& [name, neuron] : primitiveNeurons_)
    {
        //TODO: see if there is a way to do it more generic
        if (typeid(neuron.outputType()) == typeid(hdl::Numerical)
            || typeid(neuron.outputType()) == typeid(hdl::Cell))
        {
            typedPrimitiveNeurons_[typeid(hdl::Integer)].emplace_back(neuron);
            typedPrimitiveNeurons_[typeid(hdl::IntegerTuple)].emplace_back(neuron);
        }
        else if (typeid(neuron.outputType()) == typeid(hdl::Patch))
        {
            typedPrimitiveNeurons_[typeid(hdl::Object)].emplace_back(neuron);
            typedPrimitiveNeurons_[typeid(hdl::Indices)].emplace_back(neuron);
        }
        else if (typeid(neuron.outputType()) == typeid(hdl::Element))
        {
            typedPrimitiveNeurons_[typeid(hdl::Object)].emplace_back(neuron);
            typedPrimitiveNeurons_[typeid(hdl::Grid)].emplace_back(neuron);
        }
        else if (typeid(neuron.outputType()) == typeid(hdl::Piece))
        {
            typedPrimitiveNeurons_[typeid(hdl::Grid)].emplace_back(neuron);
            typedPrimitiveNeurons_[typeid(hdl::Patch)].emplace_back(neuron);
        }
        else
            typedPrimitiveNeurons_[neuron.outputType()].emplace_back(neuron);

        //TODO: add primitive as variable neurons
    }

    for (const auto& [name, neuron] : variableNeurons_)
        typedVariableNeurons_[neuron.outputType()].emplace_back(neuron);
}

void DslEngine::clearVariableNeurons()
{
    variableNeurons_.clear();
    typedVariableNeurons_.clear();
}

void DslEngine::clearPrimitiveNeurons()
{
    primitiveNeurons_.clear();
    typedPrimitiveNeurons_.clear();
}

void DslEngine::addVariableNeuron(Neuron const& neuron, std::string name)
{
    if (name.empty())
        name = neuron.name();

    variableNeurons_.emplace(name, neuron);
    typedVariableNeurons_[neuron.outputType()].emplace_back(neuron);
}

void DslEngine::addPrimitiveNeuron(Neuron const& neuron, std::string name)
{
    if (name.empty())
        name = neuron.name();

    primitiveNeurons_.emplace(name, neuron);
    typedPrimitiveNeurons_[neuron.outputType()].emplace_back(neuron);
}

std::map<std::string, Neuron> const& DslEngine::variableNeurons() const
{
    return variableNeurons_;
}

Neuron& DslEngine::variableNeuron(std::string const& name)
{
    return variableNeurons_.at(name);
}

std::map<std::string, Neuron> const& DslEngine::primitiveNeurons() const
{
    return primitiveNeurons_;
}

std::function<double(std::any, std::any)> const& DslEngine::heuristic() const
{
    return heuristic_;
}
