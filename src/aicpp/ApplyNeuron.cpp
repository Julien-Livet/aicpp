#include <stdexcept>
#include <typeindex>
#include <vector>

#include <boost/algorithm/string/join.hpp>

#include "aicpp/ApplyNeuron.h"
#include "aicpp/Connection.h"
#include "aicpp/FunctionValue.h"
#include "aicpp/Hodel.h"

namespace
{
    using namespace aicpp;

    template<typename Input, typename Output>
    std::vector<Output> applyToCollection(std::vector<Input> const& collection, Connection const& function)
    {
        std::vector<Output> result;
        result.reserve(collection.size());

        for (auto const& value : collection)
            result.emplace_back(std::any_cast<Output>(function.apply(value)));

        return result;
    }

    template<typename Input, typename Output>
    std::set<Output> applyToCollection(std::set<Input> const& collection, Connection const& function)
    {
        std::vector<Output> result;
        result.reserve(collection.size());

        for (auto const& value : collection)
            result.emplace_back(std::any_cast<Output>(function.apply(value)));

        return {result.begin(), result.end()};
    }

    struct ApplyRule
    {
        std::type_index collectionType;
        DslType inputType;
        DslType outputType;
        DslType resultType;

        std::any (*evaluate)(std::any const& collection, Connection const& function);
    };

    template<typename Input, typename Output, typename Collection>
    std::any evaluateCollection(std::any const& collectionValue, Connection const& function)
    {
        auto const& collection = std::any_cast<Collection const&>(collectionValue);

        return applyToCollection<Input, Output>(collection, function);
    }

    template<typename Input, typename Output, typename Collection>
    ApplyRule makeApplyRule(DslType resultType)
    {
        return {
            typeid(Collection),
            makeDslType<Input>(),
            makeDslType<Output>(),
            std::move(resultType),
            &evaluateCollection<Input, Output, Collection>
        };
    }

    std::vector<ApplyRule> const& applyRules()
    {
        static std::vector<ApplyRule> const rules{
            makeApplyRule<
                hodel::Object,
                hodel::Integer,
                hodel::ObjectVector>(
                    makeDslType<hodel::IntegerVector>()),

            makeApplyRule<
                hodel::Object,
                hodel::Integer,
                hodel::Objects>(
                    makeDslType<hodel::IntegerSet>()),

            makeApplyRule<
                hodel::Integer,
                hodel::Integer,
                hodel::IntegerVector>(
                    makeDslType<hodel::IntegerVector>()),

            makeApplyRule<
                hodel::Integer,
                hodel::Integer,
                hodel::IntegerSet>(
                    makeDslType<hodel::IntegerSet>()),

            makeApplyRule<
                hodel::Integer,
                hodel::Boolean,
                hodel::IntegerSet>(
                    makeDslType<hodel::BooleanVector>()),

            makeApplyRule<
                hodel::Integer,
                hodel::Boolean,
                hodel::IntegerVector>(
                    makeDslType<hodel::BooleanVector>()),

            makeApplyRule<
                hodel::Boolean,
                hodel::Boolean,
                hodel::BooleanVector>(
                    makeDslType<hodel::BooleanVector>()),

            makeApplyRule<
                hodel::Grid,
                hodel::Grid,
                hodel::GridVector>(
                    makeDslType<hodel::GridVector>()),

            makeApplyRule<
                hodel::Grid,
                hodel::Boolean,
                hodel::GridVector>(
                    makeDslType<hodel::BooleanVector>()),

            makeApplyRule<
                hodel::Grid,
                hodel::Indices,
                hodel::GridVector>(
                    makeDslType<hodel::Indices>()),

            makeApplyRule<
                hodel::Object,
                hodel::Boolean,
                hodel::Objects>(
                    makeDslType<hodel::BooleanVector>()),

            makeApplyRule<
                hodel::Object,
                hodel::Boolean,
                hodel::ObjectVector>(
                    makeDslType<hodel::BooleanVector>()),

            makeApplyRule<
                hodel::Object,
                hodel::Object,
                hodel::Objects>(
                    makeDslType<hodel::Objects>()),

            makeApplyRule<
                hodel::Object,
                hodel::Object,
                hodel::ObjectVector>(
                    makeDslType<hodel::ObjectVector>()),

            makeApplyRule<
                hodel::Object,
                hodel::Indices,
                hodel::Objects>(
                    makeDslType<hodel::Objects>()),

            makeApplyRule<
                hodel::Object,
                hodel::Indices,
                hodel::Objects>(
                    makeDslType<hodel::IndicesSet>()),

            makeApplyRule<
                hodel::Indices,
                hodel::Indices,
                hodel::IndicesSet>(
                    makeDslType<hodel::IndicesSet>()),

            makeApplyRule<
                hodel::IntegerTuple,
                hodel::Indices,
                hodel::Indices>(
                    makeDslType<hodel::Indices>()),

            makeApplyRule<
                hodel::IntegerTuple,
                hodel::Indices,
                hodel::Indices>(
                    makeDslType<hodel::IndicesSet>()),

            makeApplyRule<
                hodel::IntegerTuple,
                hodel::Object,
                hodel::Indices>(
                    makeDslType<hodel::Object>()),

            makeApplyRule<
                hodel::Integer,
                hodel::IntegerTuple,
                hodel::IntegerSet>(
                    makeDslType<hodel::Indices>()),

            makeApplyRule<
                hodel::Grid,
                hodel::GridVector,
                hodel::GridVector>(
                    makeDslType<hodel::GridVectorVector>()),

            makeApplyRule<
                hodel::Object,
                hodel::Object,
                hodel::Objects>(
                    makeDslType<hodel::Objects>()),
        };

        return rules;
    }
}

namespace aicpp
{
    DslType ApplyNeuron::inferSignature(std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("apply requires exactly two arguments");

        auto const& function = arguments[0];
        auto const& collection = arguments[1];

        if (!function.isFunction())
            throw std::invalid_argument("apply requires a function as its first argument");

        if (function.inputs().size() != 1)
            throw std::invalid_argument("apply requires a unary function");

        if (!collection.isFunction() || !collection.inputs().empty())
            throw std::invalid_argument("apply requires a collection-producing expression with no inputs");

        auto const& collectionType = collection.output();

        if (collectionType.isFunction())
            throw std::invalid_argument("apply requires a native collection type");

        auto const inputType = function.inputs()[0];
        auto const outputType = function.output();
        auto const nativeCollectionType = collectionType.nativeType();
 
        for (auto const& rule : applyRules())
        {
            auto const collectionMatches = rule.collectionType == nativeCollectionType;
            auto const inputMatches = rule.inputType == inputType;
            auto const outputMatches = rule.outputType == outputType;

            if (collectionMatches && inputMatches && outputMatches)
                return rule.resultType;
        }

        std::vector<std::string> v;
        v.reserve(arguments.size());

        for (auto const& arg : arguments)
            v.emplace_back(arg.string());

        throw std::invalid_argument("Unsupported function and collection combination for apply " + boost::algorithm::join(v, ", "));
    }

    std::any ApplyNeuron::evaluate(std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("apply requires exactly two arguments");

        if (arguments[0].type() != typeid(Connection) || arguments[1].type() != typeid(Connection))
            throw std::invalid_argument("apply arguments must be connections");

        auto const& function = std::any_cast<Connection const&>(arguments[0]);
        auto const& collectionConnection = std::any_cast<Connection const&>(arguments[1]);
        auto const collectionValue = collectionConnection.output();
        auto const functionSignature = function.signature();

        if (!functionSignature.isFunction() || functionSignature.inputs().size() != 1)
            throw std::invalid_argument("apply requires a unary function");

        auto const inputType = functionSignature.inputs()[0];
        auto const outputType = functionSignature.output();

        for (auto const& rule : applyRules()) {
            if (rule.collectionType == collectionValue.type() && rule.inputType == inputType && rule.outputType == outputType)
                return rule.evaluate(collectionValue, function);
        }

        throw std::invalid_argument("Unsupported function and collection combination for apply " + aicpp::signature(arguments));
    }

    std::any ApplyNeuron::apply(std::vector<std::any> const&, std::any const&) const
    {
        throw std::logic_error("apply is a value-producing operator, not a function");
    }

    DslType ApplyNeuron::inferConnectionSignature(std::vector<Connection> const& arguments) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("apply requires exactly two arguments");

        auto const& function = arguments[0];
        auto const& collection = arguments[1];
        auto const functionType = function.signature();
        auto const collectionType = collection.valueType();

        if (!functionType.isFunction())
            throw std::invalid_argument("apply requires a function as its first argument");

        if (functionType.inputs().size() != 1)
            throw std::invalid_argument("apply requires a unary function");

        if (collectionType.isFunction())
            throw std::invalid_argument("apply requires a collection-producing expression");

        auto const nativeCollectionType = collectionType.nativeType();
        auto const inputType = functionType.inputs().front();
        auto const outputType = functionType.output();

        for (auto const& rule : applyRules())
        {
            auto const collectionMatches = rule.collectionType == nativeCollectionType;
            auto const inputMatches = rule.inputType == inputType;
            auto const outputMatches = rule.outputType == outputType;

            if (collectionMatches && inputMatches && outputMatches)
                return DslType::function({collectionType}, rule.resultType);
        }

        std::vector<std::string> v;
        v.reserve(arguments.size());

        for (auto const& arg : arguments)
            v.emplace_back(arg.signature().string());

        throw std::invalid_argument("apply does not support this function and collection combination " + boost::algorithm::join(v, ", "));
    }

    DslType ApplyNeuron::inferConnectionSignature(std::vector<Connection> const& arguments, DslType const& expectedResultType) const
    {
        if (arguments.size() != 2)
            throw std::invalid_argument("apply requires exactly two arguments");

        auto const& function = arguments[0];
        auto const& collection = arguments[1];
        auto const functionType = function.signature();
        auto const collectionType = collection.valueType();

        if (!functionType.isFunction() || functionType.inputs().size() != 1)
            throw std::invalid_argument("apply requires a unary function");

        if (collectionType.isFunction())
            throw std::invalid_argument("apply requires a collection-producing expression");

        auto const nativeCollectionType = collectionType.nativeType();
        auto const inputType = functionType.inputs().front();
        auto const outputType = functionType.output();

        for (auto const& rule : applyRules())
        {
            auto const collectionMatches = rule.collectionType == nativeCollectionType;
            auto const inputMatches = rule.inputType == inputType;
            auto const outputMatches = rule.outputType == outputType;
            auto const resultMatches = rule.resultType == expectedResultType;

            if (collectionMatches && inputMatches && outputMatches && resultMatches)
                return DslType::function({collectionType}, rule.resultType);
        }

        throw std::invalid_argument("No apply rule matches the expected result type: " + expectedResultType.string());
    }
}
