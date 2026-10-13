#include <stdexcept>
#include <typeindex>
#include <vector>

#include "aicpp/ApplyNeuron.h"
#include "aicpp/Connection.h"
#include "aicpp/FunctionValue.h"
#include "aicpp/Hodel.h"

namespace
{
    template<typename Input, typename Output>
    std::vector<Output> applyToCollection(
        std::vector<Input> const& collection,
        aicpp::Connection const& function)
    {
        std::vector<Output> result;
        result.reserve(collection.size());

        for (auto const& value : collection)
        {
            result.emplace_back(
                std::any_cast<Output>(function.apply(value)));
        }

        return result;
    }

    template<typename Input, typename Output>
    std::vector<Output> applyToCollection(
        std::set<Input> const& collection,
        aicpp::Connection const& function)
    {
        std::vector<Output> result;
        result.reserve(collection.size());

        for (auto const& value : collection)
        {
            result.emplace_back(
                std::any_cast<Output>(function.apply(value)));
        }

        return result;
    }

    using namespace aicpp;

    struct ApplyRule
    {
        std::type_index collectionType;
        DslType inputType;
        DslType outputType;
        DslType resultType;

        std::any (*evaluate)(
            std::any const& collection,
            Connection const& function);
    };

    template<typename Input, typename Output, typename Collection>
    std::any evaluateCollection(
        std::any const& collectionValue,
        Connection const& function)
    {
        auto const& collection =
            std::any_cast<Collection const&>(collectionValue);

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
                hodel::Integer,
                hodel::Integer,
                hodel::IntegerVector>(
                    makeDslType<hodel::IntegerVector>()),

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
                hodel::Object,
                hodel::Boolean,
                hodel::ObjectVector>(
                    makeDslType<hodel::BooleanVector>()),

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
                hodel::Indices,
                hodel::Indices,
                hodel::IndicesVector>(
                    makeDslType<hodel::IndicesVector>()),

            makeApplyRule<
                hodel::Indices,
                hodel::Indices,
                hodel::IndicesSet>(
                    makeDslType<hodel::IndicesSet>())
        };

        return rules;
    }
}

namespace aicpp
{
    DslType ApplyNeuron::inferSignature(
        std::vector<DslType> const& arguments) const
    {
        if (arguments.size() != 2) {
            throw std::invalid_argument(
                "apply requires exactly two arguments");
        }

        auto const& function = arguments[0];
        auto const& collection = arguments[1];

        if (!function.isFunction()) {
            throw std::invalid_argument(
                "apply requires a function as its first argument");
        }

        if (function.inputs().size() != 1) {
            throw std::invalid_argument(
                "apply requires a unary function");
        }

        if (!collection.isFunction() ||
            !collection.inputs().empty()) {
            throw std::invalid_argument(
                "apply requires a collection-producing expression "
                "with no inputs");
        }

        auto const& collectionType = collection.output();

        if (collectionType.isFunction()) {
            throw std::invalid_argument(
                "apply requires a native collection type");
        }

        auto const& inputType = function.inputs()[0];
        auto const& outputType = function.output();
        auto const& nativeCollectionType = collectionType.nativeType();
 
        for (auto const& rule : applyRules())
        {
            auto const collectionMatches =
                rule.collectionType == nativeCollectionType;

            auto const inputMatches =
                rule.inputType == inputType;

            auto const outputMatches =
                rule.outputType == outputType;

            if (collectionMatches && inputMatches && outputMatches)
                return rule.resultType;
        }

        throw std::invalid_argument(
            "apply does not support this function and collection combination");
    }

    std::any ApplyNeuron::evaluate(
        std::vector<std::any> const& arguments) const
    {
        if (arguments.size() != 2) {
            throw std::invalid_argument(
                "apply requires exactly two arguments");
        }

        if (arguments[0].type() != typeid(Connection) ||
            arguments[1].type() != typeid(Connection)) {
            throw std::invalid_argument(
                "apply arguments must be connections");
        }

        auto const& function =
            std::any_cast<Connection const&>(arguments[0]);

        auto const& collectionConnection =
            std::any_cast<Connection const&>(arguments[1]);

        auto const collectionValue = collectionConnection.output();
        auto const functionSignature = function.signature();

        if (!functionSignature.isFunction() ||
            functionSignature.inputs().size() != 1) {
            throw std::invalid_argument(
                "apply requires a unary function");
        }

        auto const& inputType = functionSignature.inputs()[0];
        auto const& outputType = functionSignature.output();

        for (auto const& rule : applyRules()) {
            if (rule.collectionType == collectionValue.type() &&
                rule.inputType == inputType &&
                rule.outputType == outputType) {
                return rule.evaluate(collectionValue, function);
            }
        }

        throw std::invalid_argument(
            "Unsupported function and collection combination for apply");
    }

    std::any ApplyNeuron::apply(
        std::vector<std::any> const&,
        std::any const&) const
    {
        throw std::logic_error(
            "apply is a value-producing operator, not a function");
    }
}
