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
    class NeuronBase
    {
        public:
            virtual ~NeuronBase() = default;

            virtual std::string const& name() const = 0;
            virtual std::type_index returnType() const = 0;
            virtual std::vector<std::type_index> inputTypes() const = 0;
            virtual std::any invoke(std::vector<std::any> const& inputs) const = 0;
    };

    template <typename... Args>
    void addTypes(boost::json::array& inputs)
    {
        (inputs.emplace_back(std::string(typeid(Args).name())), ...);
    }

    inline std::string typeDot(size_t startIndex, size_t& index, size_t count)
    {
        return std::string{};
    }

    template <typename T, typename... Args> std::string typeDot(size_t startIndex, size_t& index, size_t count)
    {
        std::string s{"n" + std::to_string(index) + " [label=\"" + typeid(T).name() + "\", shape=circle, style=fill];\n"};
        s += "n" + std::to_string(index) + " -> n" + std::to_string(startIndex + count) + ";\n";
        ++index;

        s += typeDot<Args...>(startIndex, index, count);

        return s;
    }

    template <typename T, typename... Args>
    class Neuron : public NeuronBase
    {
        public:
            using ReturnType = T;
            using Function = T (*)(Args...);

            Neuron(std::string const& name, Function function) : name_{name}, function_{function}
            {
            }

            std::string const& name() const override
            {
                return name_;
            }

            std::type_index returnType() const override
            {
                return typeid(T);
            }

            std::vector<std::type_index> inputTypes() const override
            {
                return {std::type_index(typeid(Args))...};
            }

            Function function() const override
            {
                return function_;
            }

            std::pair<std::string, size_t> dot(size_t index = 0) const
            {
                std::string s;
                size_t const startIndex{index};

                s += typeDot<Args...>(startIndex, index, std::tuple_size<std::tuple<Args...> >::value);
                s += "n" + std::to_string(index) + " [label=\"" + name_ + "\", shape=circle, style=fill];\n";
                ++index;

                s += "n" + std::to_string(index) + " [label=\"" + typeid(T).name() + "\", shape=circle, style=fill];\n";
                s += "n" + std::to_string(startIndex + std::tuple_size<std::tuple<Args...> >::value) + " -> n" + std::to_string(index) + ";\n";
                ++index;

                return std::make_pair(s, index);
            }

            boost::json::value toJson() const
            {
                using namespace boost::json;

                object obj;

                obj["name"] = name_;

                array inputs;

                addType<Args...>(inputs);

                obj["inputTypes"] = std::move(inputs);
                obj["outputType"] = std::string(typeid(T).name());

                return obj;
            }

            std::any invoke(std::vector<std::any> const& inputs) const override
            {
                if (inputs.size() != sizeof...(Args))
                    throw std::invalid_argument("Invalid number of neuron inputs");

                return invokeImpl_(
                    inputs,
                    std::index_sequence_for<Args...>{}
                );
            }

        private:
            std::string name_;
            Function function_;

            template <std::size_t... I>
            std::any invokeImpl_(
                std::vector<std::any> const& inputs,
                std::index_sequence<I...>
            ) const
            {
                return std::any{
                    function_(std::any_cast<Args const&>(inputs[I])...)
                };
            }
    };
}

#endif // AICPP_NEURON_H
