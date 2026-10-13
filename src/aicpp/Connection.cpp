#include <algorithm>

#include <boost/algorithm/string.hpp>

#include "aicpp/Connection.h"
#include "aicpp/PolymorphicNeuron.h"
#include "aicpp/utility.h"
#include "aicpp/FunctionValue.h"
#include "aicpp/HodelRegister.h"
#include "aicpp/FunctionAdapterNeuron.h"

using namespace aicpp;

static auto const registry = aicpp::makeNeuronRegistry();

aicpp::NeuronBase const* aicpp::findNeuron(aicpp::DslType const& expected)
{
    auto it = std::find_if(
        registry.begin(),
        registry.end(),
        [&expected](auto const& entry)
        {
            return !entry.second->isPolymorphic()
                && entry.second->signature() == expected;
        });

    if (it == registry.end())
    {
        throw std::runtime_error(
            "Neuron not found for expected signature");
    }

    return it->second;
};

aicpp::Connection aicpp::buildFunctionConnection(
    std::string const& name,
    DslType const& expectedSignature)
{
    if (expectedSignature.isFunction()
        && expectedSignature.inputs().size() == 1)
    {
        for (auto const& [_, neuron] : registry)
        {
            if (neuron->name() != name || !neuron->isPolymorphic())
                continue;

            auto const* adapter =
                dynamic_cast<FunctionAdapterNeuron const*>(neuron);

            if (adapter == nullptr)
                continue;

            try
            {
                if (adapter->inferSignature({}) == expectedSignature)
                    return Connection{neuron, {}};
            }
            catch (std::exception const&)
            {
            }
        }
    }

    for (auto const& [_, neuron] : registry)
    {
        if (neuron->name() != name || neuron->isPolymorphic())
            continue;

        if (neuron->signature() != expectedSignature)
            continue;

        auto const inputTypes{neuron->inputTypes()};
        std::vector<std::any> inputs;
        inputs.reserve(inputTypes.size());

        for (auto const& input : inputTypes)
            inputs.emplace_back(input);

        return Connection{neuron, inputs};
    }

    throw std::runtime_error(
        "No function overload found for neuron: " + name);
}

aicpp::Connection aicpp::buildConnection(
    std::string const& name,
    std::vector<std::any> const& args)
{
    for (auto const& arg : args)
    {
        if (arg.type() != typeid(aicpp::Connection))
        {
            throw std::invalid_argument(
                "Arguments must be connections");
        }
    }

    for (auto const& [_, neuron] : registry)
    {
        if (neuron->name() != name)
            continue;

        if (neuron->isPolymorphic())
        {
            auto const* polymorphic =
                dynamic_cast<aicpp::PolymorphicNeuron const*>(neuron);

            if (polymorphic == nullptr)
                continue;

            std::vector<aicpp::Connection> connections;
            connections.reserve(args.size());

            for (auto const& arg : args)
            {
                connections.push_back(
                    std::any_cast<aicpp::Connection const&>(arg));
            }

            try
            {
                polymorphic->inferConnectionSignature(connections);
                return aicpp::Connection{neuron, args};
            }
            catch (std::exception const& e)
            {
                continue;
            }
        }

        if (neuron->inputTypes().size() != args.size())
            continue;

        bool compatible = true;

        for (size_t i = 0; i < args.size(); ++i)
        {
            auto const& connection =
                std::any_cast<aicpp::Connection const&>(args[i]);

            auto const expectedType = neuron->inputTypes()[i];

            if (expectedType == typeid(aicpp::FunctionValue))
            {
                compatible = connection.signature().isFunction();
            }
            else
            {
                auto const actualType = connection.valueType();

                compatible =
                    !actualType.isFunction()
                    && actualType.nativeType() == expectedType;
            }

            if (!compatible)
                break;
        }
        
        if (compatible)
            return aicpp::Connection{neuron, args};
    }

    throw std::runtime_error{
        "No compatible connection found for neuron: " + name
    };
}

Connection::Connection(
    NeuronBase const* neuron,
    std::vector<std::any> const& inputs)
    : neuron_{neuron}, inputs_(inputs)
{
    if (!neuron_->isPolymorphic())
    {
        assert(inputs_.size() == neuron_->inputTypes().size());

        for (size_t i{0}; i < inputs_.size(); ++i)
        {
            if (inputs_[i].type() == typeid(Connection))
            {
                auto const& connection =
                    std::any_cast<Connection const&>(inputs_[i]);

                auto const expectedType = neuron_->inputTypes()[i];

                if (expectedType == typeid(FunctionValue))
                {
                    assert(connection.signature().isFunction());
                }
                else
                {
                    auto const actualType = connection.valueType();

                    assert(!actualType.isFunction());
                    assert(actualType.nativeType() == expectedType);
                }
            }
            else if (inputs_[i].type() == typeid(std::type_index))
            {
                assert(
                    std::any_cast<std::type_index>(inputs_[i])
                    == neuron_->inputTypes()[i]);
            }
            else
            {
                assert(inputs_[i].type() == neuron_->inputTypes()[i]);
            }
        }
    }
    else
    {
        auto const* polymorphic =
            dynamic_cast<PolymorphicNeuron const*>(neuron_);

        if (polymorphic == nullptr)
        {
            throw std::logic_error(
                "Neuron marked polymorphic does not implement PolymorphicNeuron");
        }

        std::vector<Connection> arguments;
        arguments.reserve(inputs_.size());

        for (auto const& input : inputs_)
        {
            if (input.type() != typeid(Connection))
            {
                throw std::invalid_argument(
                    "Polymorphic neuron '" + neuron_->name()
                    + "' received an argument of type '"
                    + input.type().name() + "' instead of Connection");
            }

            arguments.emplace_back(
                std::any_cast<Connection const&>(input));
        }

        polymorphic->inferConnectionSignature(arguments);
    }

    hash_ = computeHash_();
}

NeuronBase const* Connection::neuron() const
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
        else
            de = std::max(de, d + 1);
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
        args.emplace_back(utility::anyToString(x));

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
                types.emplace_back(connection.neuron()->returnType());
            else
                types.insert(types.end(), inputTypes.begin(), inputTypes.end());
        }
        else if (input.type() == typeid(std::type_index))
            types.emplace_back(std::any_cast<std::type_index>(input));
        else
            types.emplace_back(input.type());
    }

    return types;
}

void Connection::applyInputs(std::vector<std::any> const& inputs, bool checkTypes)
{
    assert(inputs.size() == inputTypes().size());

    auto checkType = [checkTypes] (std::any const& input, std::type_index expectedType)
    {
        if (!checkTypes)
            return;

        if (input.type() == typeid(std::type_index))
            assert(expectedType == std::any_cast<std::type_index>(input));
        else if (input.type() != typeid(Connection))
            assert(expectedType == input.type());
    };

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
                connection.applyInputs(std::vector<std::any>(inputs.begin() + index, inputs.begin() + index + size), checkTypes);

                input = connection;
                index += size;
            }
            else
            {
                checkType(inputs[index], connection.neuron()->returnType());

                input = inputs[index];
                ++index;
            }
        }
        else
        {
            if (index < inputs.size())
            {
                checkType(inputs[index], neuron_->inputTypes()[i]);

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

    s += "n" + std::to_string(index) + " [label=\"" + neuron_->name() + "\", shape=circle, style=fill];\n";
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

    std::string value;

    try
    {
        auto const result = output();

        if (result.type() == typeid(Connection))
            value = std::any_cast<Connection const&>(result).signature().output().nativeType().name();
        else
            value = utility::anyToString(result);
    }
    catch (std::bad_any_cast const&)
    {
        value = neuron_->isPolymorphic()
            ? "polymorphic"
            : neuron_->returnType().name();
    }

    s += "n" + std::to_string(index) + " [label=\"" + value + "\", shape=circle, style=fill];\n";
    s += "n" + std::to_string(nodeIndex) + " -> n" + std::to_string(index) + ";\n";
    ++index;

    return std::make_pair(s, index);
}

std::any Connection::output() const
{
    if (neuron_->isPolymorphic())
    {
        auto const* polymorphic =
            dynamic_cast<PolymorphicNeuron const*>(neuron_);

        if (polymorphic == nullptr)
        {
            throw std::logic_error(
                "Neuron marked polymorphic does not implement PolymorphicNeuron");
        }

        if (polymorphic->evaluatesToValue(inputs_))
            return polymorphic->evaluate(inputs_);

        return *this;
    }

    std::vector<std::any> args;
    args.reserve(inputs_.size());

    auto const expectedTypes = neuron_->inputTypes();

    for (std::size_t i = 0; i < inputs_.size(); ++i)
    {
        auto const& input = inputs_[i];

        if (input.type() == typeid(Connection))
        {
            auto const& connection =
                std::any_cast<Connection const&>(input);

            if (expectedTypes[i] == typeid(aicpp::FunctionValue))
            {
                args.emplace_back(aicpp::FunctionValue{connection});
            }
            else
            {
                args.emplace_back(connection.output());
            }
        }
        else
        {
            args.emplace_back(input);
        }
    }

    return neuron_->invoke(args);
}

size_t Connection::computeHash_() const
{
    size_t h{std::hash<NeuronBase const*>{}(neuron_)};

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
        else if (input.type() == typeid(int16_t))
            h += std::hash<int16_t>{}(std::any_cast<int16_t>(input));
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
    if (neuron_ != other.neuron_)
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
        else if (inputs_[i].type() == typeid(int16_t) && other.inputs_[i].type() == typeid(int16_t))
            equal &= (std::any_cast<int16_t>(inputs_[i]) == std::any_cast<int16_t>(other.inputs_[i]));
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
    obj["neuron"] = neuron_->toJson();

    array inputs, types;

    for (const auto& input : inputs_)
    {
        types.emplace_back(input.type().name());

        if (input.type() == typeid(Connection))
            inputs.emplace_back(std::any_cast<Connection>(input).toJson());
        else
            inputs.emplace_back(utility::anyToString(input));
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

std::string const& Connection::name() const
{
    if (!name_.empty())
        return name_;

    if (neuron_)
        return neuron_->name();

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
            args.emplace_back(
                std::any_cast<Connection const&>(input).expression());
        else
            args.emplace_back(utility::anyToString(input));
    }

    auto s = neuron_->name();

    if (!inputs_.empty())
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

bool Connection::replace(NeuronBase const* neuron)
{
    bool ok = false;

    if (neuron->name() == neuron_->name()) {
        bool compatible = false;

        if (neuron->isPolymorphic() && neuron_->isPolymorphic()) {
            auto const* newPolymorphic =
                dynamic_cast<PolymorphicNeuron const*>(neuron);
            auto const* currentPolymorphic =
                dynamic_cast<PolymorphicNeuron const*>(neuron_);

            if (newPolymorphic == nullptr || currentPolymorphic == nullptr)
                throw std::logic_error(
                    "Neuron marked polymorphic does not implement PolymorphicNeuron"
                );

            compatible = signature() == [&]() {
                DslType::Inputs arguments;
                arguments.reserve(inputs_.size());

                for (auto const& input : inputs_) {
                    if (input.type() != typeid(Connection))
                        throw std::invalid_argument(
                            "Cannot infer polymorphic signature from a non-connection input"
                        );

                    arguments.push_back(
                        std::any_cast<Connection const&>(input).signature()
                    );
                }

                return newPolymorphic->inferSignature(arguments);
            }();
        } else if (!neuron->isPolymorphic() && !neuron_->isPolymorphic()) {
            compatible =
                neuron->inputTypes() == neuron_->inputTypes()
                && neuron->returnType() == neuron_->returnType();
        }

        if (compatible) {
            neuron_ = neuron;
            ok = true;
        }
    }

    for (auto& input : inputs_) {
        if (input.type() == typeid(Connection)) {
            auto connection = std::any_cast<Connection>(input);
            auto const valid = connection.replace(neuron);

            ok |= valid;

            if (valid)
                input = connection;
        }
    }

    if (ok)
        hash_ = computeHash_();

    return ok;
}

std::vector<std::type_index> Connection::expectedInputTypes() const
{
    std::vector<std::type_index> types;
    types.reserve(inputs_.size());

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        auto const& input{inputs_[i]};

        if (input.type() == typeid(Connection))
        {
            auto const connection{std::any_cast<Connection>(input)};
            auto const nestedTypes{connection.expectedInputTypes()};

            if (nestedTypes.empty())
                types.emplace_back(connection.neuron()->returnType());
            else
                types.insert(
                    types.end(),
                    nestedTypes.begin(),
                    nestedTypes.end());
        }
        else
            types.emplace_back(neuron_->inputTypes()[i]);
    }

    return types;
}

DslType Connection::signature() const
{
    if (!neuron_->isPolymorphic())
    {
        return neuron_->signature();
    }

    auto const* polymorphic =
        dynamic_cast<PolymorphicNeuron const*>(neuron_);

    if (polymorphic == nullptr)
    {
        throw std::logic_error(
            "Neuron marked polymorphic does not implement PolymorphicNeuron");
    }

    std::vector<Connection> arguments;
    arguments.reserve(inputs_.size());

    for (auto const& input : inputs_)
    {
        if (input.type() != typeid(Connection))
        {
            throw std::invalid_argument(
                "Cannot infer polymorphic signature from a non-connection input");
        }

        arguments.push_back(
            std::any_cast<Connection const&>(input));
    }

    return polymorphic->inferConnectionSignature(arguments);
}

std::any Connection::apply(std::any const& argument) const
{
    auto const signature = this->signature();

    if (!signature.isFunction() || signature.inputs().size() != 1)
    {
        throw std::invalid_argument(
            "Only unary function connections can be applied");
    }

    auto const expectedType = signature.inputs().front().nativeType();

    if (argument.type() != expectedType)
    {
        throw std::invalid_argument(
            "Argument type does not match function input type");
    }

    if (neuron_->isPolymorphic())
    {
        auto const* polymorphic =
            dynamic_cast<PolymorphicNeuron const*>(neuron_);

        if (polymorphic == nullptr)
        {
            throw std::logic_error(
                "Neuron marked polymorphic does not implement PolymorphicNeuron");
        }

        return polymorphic->apply(inputs_, argument);
    }

    if (inputs_.size() != 1)
    {
        throw std::logic_error(
            "Native function connection must have exactly one input");
    }

    std::vector<std::any> args;
    args.reserve(1);
    args.emplace_back(argument);

    return neuron_->invoke(args);
}

std::vector<std::type_index> Connection::immediateInputTypes() const
{
    std::vector<std::type_index> types;
    types.reserve(inputs_.size());

    for (auto const& input : inputs_) {
        if (input.type() == typeid(Connection)) {
            auto const& connection = std::any_cast<Connection const&>(input);
            auto const signature = connection.signature();

            if (signature.isFunction()) {
                types.emplace_back(signature.output().nativeType());
            } else {
                types.emplace_back(signature.nativeType());
            }
        } else if (input.type() == typeid(std::type_index)) {
            types.emplace_back(std::any_cast<std::type_index>(input));
        } else {
            types.emplace_back(input.type());
        }
    }

    return types;
}

DslType Connection::valueType() const
{
    auto const connectionSignature = signature();

    if (connectionSignature.isFunction())
        return connectionSignature.output();

    return connectionSignature;
}

DslType Connection::remainingSignature() const
{
    if (neuron_->isPolymorphic())
    {
        throw std::logic_error(
            "Cannot compute remaining signature for a polymorphic neuron");
    }

    auto const nativeSignature = neuron_->signature();

    if (!nativeSignature.isFunction())
    {
        throw std::logic_error(
            "Cannot compute remaining signature for a non-function neuron");
    }

    auto const& nativeInputs = nativeSignature.inputs();

    if (inputs_.size() != nativeInputs.size())
    {
        throw std::logic_error(
            "Connection inputs do not match the native function signature");
    }

    DslType::Inputs remainingInputs;

    for (std::size_t i = 0; i < inputs_.size(); ++i)
    {
        if (inputs_[i].type() == typeid(std::type_index))
        {
            auto const missingType =
                std::any_cast<std::type_index>(inputs_[i]);

            if (missingType != nativeInputs[i].nativeType())
            {
                throw std::logic_error(
                    "Missing argument type does not match native signature");
            }

            remainingInputs.emplace_back(nativeInputs[i]);
        }
    }

    return DslType::function(
        remainingInputs,
        nativeSignature.output());
}

aicpp::Connection aicpp::buildFunctionConnection(
    std::string const& name,
    DslType const& expectedSignature,
    std::vector<std::any> const& args)
{
    if (!expectedSignature.isFunction())
    {
        throw std::invalid_argument(
            "Expected signature must be a function");
    }

    for (auto const& [_, neuron] : registry)
    {
        if (neuron->name() != name || neuron->isPolymorphic())
            continue;

        if (neuron->signature() != expectedSignature)
            continue;

        auto const inputTypes = neuron->inputTypes();

        if (args.size() > inputTypes.size())
        {
            throw std::invalid_argument(
                "Too many fixed arguments for function: " + name);
        }

        std::vector<std::any> inputs;
        inputs.reserve(inputTypes.size());

        for (std::size_t i = 0; i < inputTypes.size(); ++i)
        {
            if (i < args.size())
            {
                auto const& argument = args[i];

                if (argument.type() == typeid(Connection))
                {
                    auto const& connection =
                        std::any_cast<Connection const&>(argument);

                    if (inputTypes[i] == typeid(FunctionValue))
                    {
                        if (!connection.signature().isFunction())
                        {
                            throw std::invalid_argument(
                                "Expected a function argument");
                        }
                    }
                    else
                    {
                        auto const actualType = connection.valueType();

                        if (actualType.isFunction()
                            || actualType.nativeType() != inputTypes[i])
                        {
                            throw std::invalid_argument(
                                "Fixed argument type mismatch");
                        }
                    }

                    inputs.emplace_back(connection);
                }
                else
                {
                    if (argument.type() != inputTypes[i])
                    {
                        throw std::invalid_argument(
                            "Fixed argument type mismatch");
                    }

                    inputs.emplace_back(argument);
                }
            }
            else
            {
                inputs.emplace_back(inputTypes[i]);
            }
        }

        return Connection{neuron, inputs};
    }

    throw std::runtime_error(
        "No function overload found for neuron: " + name);
}
