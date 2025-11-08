#include <algorithm>

#include "aicpp/Brain.h"

using namespace aicpp;

std::map<size_t, AnyNeuron> const& Brain::neurons() const
{
    return neurons_;
}

std::map<std::string, bool> const& Brain::modules() const
{
    return modules_;
}

auto const& Brain::connections() const
{
    return connections_;
}

size_t Brain::addNeuron(AnyNeuron const& neuron)
{
    size_t id{0};

    if (neurons_.size())
        id = neurons_.rbegin()->first + 1;

    neurons_.emplace(id, neuron);

    auto const module{std::visit([] (auto const& neuron) { return neuron.module(); }, neuron)};

    if (modules_.find(module) == modules_.end())
        modules_[module] = true;

    return id;
}

void Brain::activateAllModules()
{
    for (auto const& p : modules_)
        activateModule(p.first);
}

void Brain::deactivateAllModules()
{
    for (auto const& p : modules_)
        deactivateModule(p.first);
}

void Brain::deactivateModules(std::vector<std::string> const& modules)
{
    for (auto const& module : modules)
        deactivateModule(module);
}

void Brain::deactivateModule(std::string const& module)
{
    modules_[module] = false;

    for (auto& p : neurons_)
    {
        std::visit(
            [module]
            (auto& neuron)
            {
                if (neuron.module() == module)
                    neuron.activated = false;
            },
            p.second);
    }
}

void Brain::activateModule(std::string const& module)
{
    modules_[module] = true;

    for (auto& p : neurons_)
    {
        std::visit(
            [module]
            (auto& neuron)
            {
                if (neuron.module() == module)
                    neuron.activated = true;
            },
            p.second);
    }
}

void Brain::activateModules(std::vector<std::string> const& modules)
{
    for (auto const& module : modules)
        activateModule(module);
}

std::any Brain::connectionOutput(Connection const& connection) const
{
    std::vector<std::any> inputs;
	inputs.reserve(connection.inputs().size());

	for (auto const& input : connection.inputs())
    {
        if (auto const* p = std::get_if<std::reference_wrapper<AnyNeuron> >(&input))
			inputs.emplace_back(
                std::visit(
                    []
                    (auto const& neuron)
                    {
                        if constexpr (requires { neuron.output(); })
                            return std::any{neuron.output()};
                        else
                            return std::any();
                    },
                    p->get()));
        else if (auto const* p = std::get_if<Connection>(&input))
            inputs.emplace_back(connectionOutput(*p));
        else
            inputs.emplace_back(variantToAny(input));
	}

    return std::visit([inputs] (auto const& neuron) { return std::any{neuron.output(inputs)}; }, neurons_.at(connection.neuronId()));
}

bool Brain::activatedNeuron(size_t id) const
{
    return std::visit([] (auto const& neuron) { return neuron.activated; }, neurons_.at(id));
}

void Brain::deactivateNeuron(size_t id)
{
    std::visit([](auto& neuron) { neuron.activated = false; }, neurons_[id]);
}

void Brain::activateNeuron(size_t id)
{
    std::visit([](auto& neuron) { neuron.activated = true; }, neurons_[id]);
}

void Brain::activateAllOriginNeurons()
{
    for (auto& p : neurons_)
    {
        std::visit(
            [&]
            (auto const& neuron)
            {
                if constexpr (requires { neuron.output(); })
                    activateNeuron(p.first);
            },
            p.second);
    }
}

void Brain::deactivateAllOriginNeurons()
{
    for (auto& p : neurons_)
    {
        std::visit(
            [&]
            (auto const& neuron)
            {
                if constexpr (requires { neuron.output(); })
                    deactivateNeuron(p.first);
            },
            p.second);
    }
}

void Brain::activateString(std::string const& s)
{
    for (auto& p : neurons_)
    {
        std::visit(
            [&]
            (auto const& neuron)
            {
                if constexpr (requires { neuron.output(); })
                {
                    auto const value{neuron.output()};

                    if constexpr (is_string_convertible_v<decltype(value)>)
                    {
                        auto s1{toString(value)};
                        auto s2{s};

                        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
                        std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

                        if (s2.find(s1) != std::string::npos)
                            activateNeuron(p.first);
                    }
                }
            },
            p.second);
    }
}

void Brain::deactivateString(std::string const& s)
{
    for (auto& p : neurons_)
    {
        std::visit(
            [&]
            (auto const& neuron)
            {
                if constexpr (requires { neuron.output(); })
                {
                    auto const value{neuron.output()};

                    if constexpr (is_string_convertible_v<decltype(value)>)
                    {
                        auto s1{toString(value)};
                        auto s2{s};

                        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
                        std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

                        if (s2.find(s1) != std::string::npos)
                            deactivateNeuron(p.first);
                    }
                }
            },
            p.second);
    }
}

AnyNeuron const& Brain::neuron(size_t id) const
{
    return neurons_.at(id);
}

AnyNeuron& Brain::neuron(size_t id)
{
    return neurons_.at(id);
}

void Brain::addConnection(Connection const& connection)
{
    connections_.emplace_back(connection);
}

std::string Brain::neuronName(size_t id) const
{
    auto const n{neuron(id)};

    std::string const module{std::visit(
        [] (auto const& neuron)
        {
            return neuron.module();
        },
        n)};
    std::string name{std::visit(
        [] (auto const& neuron)
        {
            return neuron.name();
        },
        n)};

    if (name.empty())
        name = "#" + std::to_string(id);

    return module + "." + name;
}

void Brain::clearConnections()
{
    connections_.clear();
}
