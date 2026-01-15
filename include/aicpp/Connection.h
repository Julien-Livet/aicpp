#ifndef AICPP_CONNECTION_H
#define AICPP_CONNECTION_H

#include "aicpp/Neuron.h"

namespace aicpp
{
    class Connection
    {
        public:
            Connection(Neuron const& neuron, std::vector<std::any> const& inputs_);
            Neuron const& neuron() const;
            std::vector<std::any> const& inputs() const;
            size_t cost() const;
            size_t depth(size_t d = 0) const;
            std::string string() const;
            std::vector<std::type_index> inputTypes() const;
            void applyInputs(std::vector<std::any> const& inputs);
            std::pair<std::string, size_t> dot(size_t index = 0) const;
            std::any output() const;
            size_t hash() const;
            bool operator==(Connection const& other) const;

        private:
            size_t computeHash_() const;

            std::reference_wrapper<Neuron const> neuron_;
            std::vector<std::any> inputs_;
            size_t hash_;
    };
}

template<>
struct std::hash<aicpp::Connection>
{
    std::size_t operator()(const aicpp::Connection& c) const noexcept
    {
        return c.hash();
    }
};

#endif // AICPP_CONNECTION_H
