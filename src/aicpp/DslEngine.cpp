#include "aicpp/DslEngine.h"
#include "aicpp/DslSystem.h"
#include "aicpp/Hodel.h"

using namespace aicpp;

template <typename T>
void get_variant_types(std::vector<std::type_index>& out) {
    [&out]<typename... Ts>(std::variant<Ts...>*) {
        (out.emplace_back(typeid(Ts)), ...);
    }((T*)nullptr);
}

template <typename T>
void addRule(std::unordered_map<std::type_index, std::vector<std::type_index> >& map)
{
    std::vector<std::type_index> types;
    get_variant_types<T>(types);

    map[typeid(T)] = std::move(types);
}

DslEngine::DslEngine(std::function<double(std::any, std::any)> const heuristic,
                     size_t bo_n_init, size_t bo_top_k, size_t bo_count_max) : heuristic_{heuristic}, bo_n_init_{bo_n_init}, bo_top_k_{bo_top_k}, bo_count_max_{bo_count_max}
{
    variableNeurons_ = dslVariableNeurons();
    primitiveNeurons_ = dslPrimitiveNeurons();

    //TODO: see if there is a way to do it more generic
    std::unordered_map<std::type_index, std::vector<std::type_index> > conversionRules;
    addRule<hdl::Numerical>(conversionRules);
    addRule<hdl::Patch>(conversionRules);
    addRule<hdl::Element>(conversionRules);
    addRule<hdl::Piece>(conversionRules);

    for (const auto& [name, neuron] : primitiveNeurons_)
    {
        auto const outputType{neuron.outputType()};
        auto const it{conversionRules.find(outputType)};

        if (it != conversionRules.end())
        {
            for (const auto& targetType : it->second)
                typedPrimitiveNeurons_[targetType].emplace_back(neuron);
        }
        else
            typedPrimitiveNeurons_[outputType].emplace_back(neuron);

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
