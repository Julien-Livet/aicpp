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
    namespace typed
    {
        inline void addType(boost::json::array& inputs)
        {
        }

        template <typename T, typename... Args>
        void addType(boost::json::array& inputs)
        {
            inputs.emplace_back(std::string(typeid(T).name()));
            addType<Args...>(inputs);
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
        class Neuron
        {
            public:
                Neuron(std::string const& name, std::function<T(Args...)> const& function) : name_{name}, function_{function}
                {
                }

                std::string const& name() const
                {
                    return name_;
                }

                std::function<T(Args...)>& function()
                {
                    return function_;
                }

                std::function<T(Args...)> const& function() const
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

            private:
                std::string name_;
                std::function<T(Args...)> function_;
        };
    }

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
