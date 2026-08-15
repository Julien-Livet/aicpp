#ifndef AICPP_CONNECTION_H
#define AICPP_CONNECTION_H

#include <memory>

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
            size_t nextLeafDepth(size_t d, bool& finish) const;
            std::string string() const;
            std::vector<std::type_index> inputTypes() const;
            void applyInputs(std::vector<std::any> const& inputs, bool checkTypes = true);
            bool applyNextLeaf(std::any const& input);
            std::pair<std::string, size_t> dot(size_t index = 0) const;
            std::any output() const;
            size_t hash() const;
            bool operator==(Connection const& other) const;
            boost::json::value toJson() const;
            Connection const& source() const;
            void setSource(Connection const& connection);
            std::string name() const;
            void setName(std::string const& name);
            std::string expression() const;
            std::vector<std::any> leafInputs() const;
            bool replace(Neuron const& neuron);

        private:
            size_t computeHash_() const;

            std::string name_;
            std::reference_wrapper<Neuron const> neuron_;
            std::vector<std::any> inputs_;
            size_t hash_;
            std::shared_ptr<Connection> source_;
    };
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
