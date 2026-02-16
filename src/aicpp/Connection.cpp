#include <boost/algorithm/string.hpp>

#include "aicpp/Connection.h"
#include "aicpp/utility.h"

using namespace aicpp;

Connection::Connection(Neuron const& neuron, std::vector<std::any> const& inputs) : neuron_{std::cref(neuron)}, inputs_(inputs)
{
    assert(inputs_.size() == neuron_.get().inputTypes().size());

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        if (inputs_[i].type() == typeid(Connection))
            assert(std::any_cast<Connection>(inputs_[i]).neuron().outputType() == neuron_.get().inputTypes()[i]);
        else if (inputs_[i].type() == typeid(std::type_index))
            assert(std::any_cast<std::type_index>(inputs_[i]) == neuron_.get().inputTypes()[i]);
        else
            assert(inputs_[i].type() == neuron_.get().inputTypes()[i]);
    }

    hash_ = computeHash_();
}

Neuron const& Connection::neuron() const
{
    return neuron_;
}

std::vector<std::any> const& Connection::inputs() const
{
    return inputs_;
}

size_t Connection::cost() const
{
    size_t c{0};

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        ++c;

        if (inputs_[i].type() == typeid(Connection))
            c += std::any_cast<Connection>(inputs_[i]).cost();
    }

    return c;
}

size_t Connection::depth(size_t d) const
{
    size_t de{d};

    for (auto const& input : inputs_)
    {
        if (input.type() == typeid(Connection))
            de = std::max(de, std::any_cast<Connection>(input).depth(d + 1));
    }

    return de;
}

std::string Connection::string() const
{
    if (name_.empty())
        return expression();

    auto const v(leafInputs());
    std::vector<std::string> args;
    args.reserve(v.size());

    for (auto const& x : v)
        args.emplace_back(anyToString(x));

    auto s{name_};

    if (args.size())
        s += "(" + boost::algorithm::join(args, ", ") + ")";

    return s;
}

std::vector<std::type_index> Connection::inputTypes() const
{
    std::vector<std::type_index> types;
    types.reserve(inputs_.size());

    for (auto const& input : inputs_)
    {
        if (input.type() == typeid(Connection))
        {
            auto const connection{std::any_cast<Connection>(input)};
            auto const inputTypes{connection.inputTypes()};

            if (inputTypes.empty())
                types.emplace_back(connection.neuron().outputType());
            else
            {
                auto const v{std::any_cast<Connection>(input).inputTypes()};

                types.insert(types.end(), v.begin(), v.end());
            }
        }
        else if (input.type() == typeid(std::type_index))
            types.emplace_back(std::any_cast<std::type_index>(input));
        else
            types.emplace_back(input.type());
    }

    return types;
}

void Connection::applyInputs(std::vector<std::any> const& inputs)
{
    assert(inputs.size() == inputTypes().size());

    size_t index{0};

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        auto& input{inputs_[i]};

        if (input.type() == typeid(Connection))
        {
            auto connection{std::any_cast<Connection>(input)};
            auto const size{connection.inputTypes().size()};

            if (size)
            {
                connection.applyInputs(std::vector<std::any>(inputs.begin() + index, inputs.begin() + index + size));
                input = connection;
                index += size;
            }
            else
            {
                input = inputs[index];
                ++index;
            }
        }
        else
        {
            if (index < inputs.size())
            {
                if (inputs[index].type() == typeid(std::type_index))
                    assert(neuron_.get().inputTypes()[i] == std::any_cast<std::type_index>(inputs[index]));
                else if (inputs[index].type() != typeid(Connection))
                    assert(neuron_.get().inputTypes()[i] == inputs[index].type());

                input = inputs[index];
                ++index;
            }
        }
    }

    hash_ = computeHash_();
}

std::pair<std::string, size_t> Connection::dot(size_t index) const
{
    std::string s;

    s += "n" + std::to_string(index) + " [label=\"" + neuron_.get().name() + "\", shape=circle, style=fill];\n";
    auto const nodeIndex{index};
    ++index;

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        auto const& input{inputs_[i]};

        if (input.type() == typeid(Connection))
        {
            auto const p{std::any_cast<Connection>(input).dot(index)};
            index = p.second;
            s += "n" + std::to_string(index - 1) + " -> n" + std::to_string(nodeIndex) + ";\n";
            s += p.first;
        }
        else
        {
            std::string value{input.type().name()};

            if (input.type() == typeid(char))
                value = std::string{std::any_cast<char>(input)};
            else if (input.type() == typeid(double))
                value = std::to_string(std::any_cast<double>(input));
            else if (input.type() == typeid(float))
                value = std::to_string(std::any_cast<float>(input));
            else if (input.type() == typeid(int))
                value = std::to_string(std::any_cast<int>(input));
            else if (input.type() == typeid(long))
                value = std::to_string(std::any_cast<long>(input));
            else if (input.type() == typeid(std::string))
                value = std::any_cast<std::string>(input);
            else if (input.type() == typeid(std::type_index))
                value = std::any_cast<std::type_index>(input).name();

            s += "n" + std::to_string(index) + " [label=\"" + value + "\", shape=circle, style=fill];\n";
            s += "n" + std::to_string(index) + " -> n" + std::to_string(nodeIndex) + ";\n";
            ++index;
        }
    }

    std::string value{neuron_.get().outputType().name()};

    try
    {
        value = anyToString(output());
    }
    catch (std::bad_any_cast const&)
    {
    }

    s += "n" + std::to_string(index) + " [label=\"" + value + "\", shape=circle, style=fill];\n";
    s += "n" + std::to_string(nodeIndex) + " -> n" + std::to_string(index) + ";\n";
    ++index;

    return std::make_pair(s, index);
}

std::any Connection::output() const
{
    std::vector<std::any> args;
    args.reserve(inputs_.size());

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        auto const& input{inputs_[i]};

        if (input.type() == typeid(Connection))
            args.emplace_back(std::any_cast<Connection>(input).output());
        else
            args.emplace_back(input);
    }

    return neuron_.get().function()(args);
}

size_t Connection::computeHash_() const
{
    size_t h{std::hash<Neuron>{}(neuron_.get())};

    for (auto const& input : inputs_)
    {
        if (input.type() == typeid(char))
            h += std::hash<char>{}(std::any_cast<char>(input));
        else if (input.type() == typeid(Connection))
            h += std::any_cast<Connection>(input).hash();
        else if (input.type() == typeid(double))
            h += std::hash<double>{}(std::any_cast<double>(input));
        else if (input.type() == typeid(float))
            h += std::hash<float>{}(std::any_cast<float>(input));
        else if (input.type() == typeid(int))
            h += std::hash<int>{}(std::any_cast<int>(input));
        else if (input.type() == typeid(long))
            h += std::hash<long>{}(std::any_cast<long>(input));
        else if (input.type() == typeid(std::string))
            h += std::hash<std::string>{}(std::any_cast<std::string>(input));
        else if (input.type() == typeid(std::type_index))
            h += std::hash<std::type_index>{}(std::any_cast<std::type_index>(input));
    }

    return h;
}

size_t Connection::hash() const
{
    return hash_;
}

bool Connection::operator==(Connection const& other) const
{
    if (&neuron_.get() != &other.neuron_.get())
        return false;

    if (inputs_.size() != other.inputs_.size())
        return false;

    bool equal{true};

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        if (inputs_[i].type() == typeid(char) && other.inputs_[i].type() == typeid(char))
            equal &= (std::any_cast<char>(inputs_[i]) == std::any_cast<char>(other.inputs_[i]));
        else if (inputs_[i].type() == typeid(Connection) && other.inputs_[i].type() == typeid(Connection))
            equal &= (std::any_cast<Connection>(inputs_[i]) == std::any_cast<Connection>(other.inputs_[i]));
        else if (inputs_[i].type() == typeid(double) && other.inputs_[i].type() == typeid(double))
            equal &= (std::any_cast<double>(inputs_[i]) == std::any_cast<double>(other.inputs_[i]));
        else if (inputs_[i].type() == typeid(float) && other.inputs_[i].type() == typeid(float))
            equal &= (std::any_cast<float>(inputs_[i]) == std::any_cast<float>(other.inputs_[i]));
        else if (inputs_[i].type() == typeid(int) && other.inputs_[i].type() == typeid(int))
            equal &= (std::any_cast<int>(inputs_[i]) == std::any_cast<int>(other.inputs_[i]));
        else if (inputs_[i].type() == typeid(long) && other.inputs_[i].type() == typeid(long))
            equal &= (std::any_cast<long>(inputs_[i]) == std::any_cast<long>(other.inputs_[i]));
        else if (inputs_[i].type() == typeid(std::string) && other.inputs_[i].type() == typeid(std::string))
            equal &= (std::any_cast<std::string>(inputs_[i]) == std::any_cast<std::string>(other.inputs_[i]));
        else if (inputs_[i].type() == typeid(std::type_index) && other.inputs_[i].type() == typeid(std::type_index))
            equal &= (std::any_cast<std::type_index>(inputs_[i]) == std::any_cast<std::type_index>(other.inputs_[i]));
        else
            equal = false;

        if (!equal)
            break;
    }

    return equal;
}

boost::json::value Connection::toJson() const
{
    using namespace boost::json;

    object obj;

    obj["name"] = name_;
    obj["neuron"] = neuron_.get().toJson();

    array inputs, types;

    for (const auto& input : inputs_)
    {
        types.emplace_back(input.type().name());

        if (input.type() == typeid(Connection))
            inputs.emplace_back(std::any_cast<Connection>(input).toJson());
        else
            inputs.emplace_back(anyToString(input));
    }

    obj["types"] = std::move(types);
    obj["inputs"] = std::move(inputs);

    return obj;
}

Connection const& Connection::source() const
{
    if (!source_)
        return *this;

    return *source_;
}

void Connection::setSource(Connection const& connection)
{
    source_ = std::make_shared<Connection>(connection);
}

std::string Connection::name() const
{
    return name_;
}

void Connection::setName(std::string const& name)
{
    name_ = name;
}

std::string Connection::expression() const
{
    std::vector<std::string> args;
    args.reserve(inputs_.size());

    for (auto const& input : inputs_)
    {
        if (input.type() == typeid(Connection))
            args.emplace_back(std::any_cast<Connection>(input).expression());
        else
            args.emplace_back(anyToString(input));
    }

    auto s{neuron_.get().name()};

    if (neuron_.get().inputTypes().size())
        s += "(" + boost::algorithm::join(args, ", ") + ")";

    return s;
}

std::vector<std::any> Connection::leafInputs() const
{
    std::vector<std::any> inputs;
    inputs.reserve(inputs_.size());

    for (auto const& input : inputs_)
    {
        if (input.type() == typeid(Connection))
        {
            auto const connection{std::any_cast<Connection>(input)};
            auto const v(connection.leafInputs());

            inputs.insert(inputs.end(), v.begin(), v.end());
        }
        else
            inputs.emplace_back(input);
    }

    return inputs;
}
