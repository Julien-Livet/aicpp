#ifndef AICPP_CONNECTION_H
#define AICPP_CONNECTION_H

#include <memory>

#include "aicpp/Neuron.h"
#include "aicpp/DslType.h"

namespace aicpp
{
    class Connection
    {
        public:
            Connection(NeuronBase const* neuron, std::vector<std::any> const& inputs);
            NeuronBase const* neuron() const;
            std::vector<std::any> const& inputs() const;
            size_t cost() const;
            size_t depth(size_t d = 0) const;
            std::string string() const;
            std::vector<std::type_index> inputTypes() const;
            void applyInputs(std::vector<std::any> const& inputs, bool checkTypes = true);
            std::pair<std::string, size_t> dot(size_t index = 0) const;
            std::any output() const;
            size_t hash() const;
            bool operator==(Connection const& other) const;
            boost::json::value toJson() const;
            Connection const& source() const;
            void setSource(Connection const& connection);
            std::string const& name() const;
            void setName(std::string const& name);
            std::string expression() const;
            std::vector<std::any> leafInputs() const;
            bool replace(NeuronBase const* neuron);
            std::vector<std::type_index> expectedInputTypes() const;
            DslType signature() const;
            std::any apply(std::any const& argument) const;
            std::vector<std::type_index> immediateInputTypes() const;
            DslType valueType() const;
            DslType remainingSignature() const;

        private:
            size_t computeHash_() const;

            std::string name_;
            NeuronBase const* neuron_;
            std::vector<std::any> inputs_;
            size_t hash_;
            std::shared_ptr<Connection> source_;
    };

    NeuronBase const* findNeuron(DslType const& expected);
    Connection buildConnection(std::string const& name, std::vector<std::any> const& args);
    Connection buildFunctionConnection(std::string const& name, DslType const& expectedSignature);
    Connection buildFunctionConnection(std::string const& name, DslType const& expectedSignature, std::vector<std::any> const& args);
}

template<>
struct std::hash<aicpp::Connection>
{
    std::size_t operator()(aicpp::Connection const& c) const noexcept
    {
        return c.hash();
    }
};

#endif // AICPP_CONNECTION_H
