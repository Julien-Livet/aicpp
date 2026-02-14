#ifndef AICPP_NEURON_H
#define AICPP_NEURON_H

#include <any>
#include <functional>
#include <string>
#include <typeindex>
#include <vector>

#include <boost/json.hpp>

namespace aicpp
{
    class Neuron
    {
        public:
            Neuron(std::string const& name, std::function<std::any(std::vector<std::any>)> const& function,
                   std::vector<std::type_index> const& inputTypes, std::type_index const& outputType);
            std::string const& name() const;
            std::function<std::any(std::vector<std::any>)>& function();
            std::function<std::any(std::vector<std::any>)> const& function() const;
            std::vector<std::type_index> const& inputTypes() const;
            std::type_index const& outputType() const;
            std::pair<std::string, size_t> dot(size_t index = 0) const;
            boost::json::value toJson() const;

        private:
            std::string name_;
            std::function<std::any(std::vector<std::any>)> function_;
            std::vector<std::type_index> inputTypes_;
            std::type_index outputType_;
    };
}

template<>
struct std::hash<aicpp::Neuron>
{
    size_t operator()(aicpp::Neuron const& n) const noexcept
    {
        auto h{std::hash<std::string>{}(n.name())};

        for (auto const& v : n.inputTypes())
            h += std::hash<std::type_index>{}(v);

        return h + std::hash<std::type_index>{}(n.outputType());
    }
};

#endif // AICPP_NEURON_H
