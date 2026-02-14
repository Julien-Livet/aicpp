#include "aicpp/Neuron.h"

using namespace aicpp;

Neuron::Neuron(std::string const& name, std::function<std::any(std::vector<std::any>)> const& function,
               std::vector<std::type_index> const& inputTypes, std::type_index const& outputType) : name_{name}, function_{function}, inputTypes_{inputTypes}, outputType_{outputType}
{
}

std::string const& Neuron::name() const
{
    return name_;
}

std::function<std::any(std::vector<std::any>)>& Neuron::function()
{
    return function_;
}

std::function<std::any(std::vector<std::any>)> const& Neuron::function() const
{
    return function_;
}

std::vector<std::type_index> const& Neuron::inputTypes() const
{
    return inputTypes_;
}

std::type_index const& Neuron::outputType() const
{
    return outputType_;
}

std::pair<std::string, size_t> Neuron::dot(size_t index) const
{
    std::string s;
    size_t const startIndex{index};

    for (size_t i{0}; i < inputTypes_.size(); ++i)
    {
        s += "n" + std::to_string(index) + " [label=\"" + inputTypes_[i].name() + "\", shape=circle, style=fill];\n";
        s += "n" + std::to_string(index) + " -> n" + std::to_string(startIndex + inputTypes_.size()) + ";\n";
        ++index;
    }

    s += "n" + std::to_string(index) + " [label=\"" + name_ + "\", shape=circle, style=fill];\n";
    ++index;

    s += "n" + std::to_string(index) + " [label=\"" + outputType_.name() + "\", shape=circle, style=fill];\n";
    s += "n" + std::to_string(startIndex + inputTypes_.size()) + " -> n" + std::to_string(index) + ";\n";
    ++index;

    return std::make_pair(s, index);
}

boost::json::value Neuron::toJson() const
{
    using namespace boost::json;

    object obj;

    obj["name"] = name_;

    array inputs;

    for (const auto& t : inputTypes_)
        inputs.emplace_back(std::string(t.name()));

    obj["inputTypes"] = std::move(inputs);

    obj["outputType"] = std::string(outputType_.name());

    return obj;
}
