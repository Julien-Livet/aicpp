#ifndef AICPP_DSLTYPE_H
#define AICPP_DSLTYPE_H

#include <memory>
#include <stdexcept>
#include <typeindex>
#include <type_traits>
#include <utility>
#include <vector>

namespace aicpp
{
    class DslType
    {
        public:
            using Inputs = std::vector<DslType>;

            explicit DslType(std::type_index type)
                : type_{type}
            {
            }

            static DslType function(Inputs inputs, DslType output)
            {
                DslType result{typeid(void)};
                result.inputs_ = std::move(inputs);
                result.output_ = std::make_shared<DslType>(
                    std::move(output));
                return result;
            }

            bool isFunction() const
            {
                return static_cast<bool>(output_);
            }

            std::type_index nativeType() const
            {
                if (isFunction())
                    throw std::logic_error(
                        "A function type has no native type");

                return type_;
            }

            Inputs const& inputs() const
            {
                if (!isFunction())
                    throw std::logic_error(
                        "A native type has no function inputs");

                return inputs_;
            }

            DslType const& output() const
            {
                if (!isFunction())
                    throw std::logic_error(
                        "A native type has no function output");

                return *output_;
            }

            friend bool operator==(
                DslType const& lhs,
                DslType const& rhs)
            {
                if (lhs.isFunction() != rhs.isFunction())
                    return false;

                if (!lhs.isFunction())
                    return lhs.type_ == rhs.type_;

                return lhs.inputs_ == rhs.inputs_
                    && lhs.output() == rhs.output();
            }

            friend bool operator!=(
                DslType const& lhs,
                DslType const& rhs)
            {
                return !(lhs == rhs);
            }

        private:
            std::type_index type_;
            Inputs inputs_;
            std::shared_ptr<DslType> output_;
    };

    template <typename T>
    DslType makeDslType()
    {
        using NativeType = std::remove_cvref_t<T>;
        return DslType{typeid(NativeType)};
    }

    inline DslType inferComposeSignature(
        DslType const& outer,
        DslType const& inner)
    {
        if (!outer.isFunction() || !inner.isFunction())
            throw std::invalid_argument(
                "compose requires two function types");

        if (outer.inputs().size() != 1
            || inner.inputs().size() != 1)
            throw std::invalid_argument(
                "compose requires unary functions");

        if (outer.inputs()[0] != inner.output())
            throw std::invalid_argument(
                "compose function types are incompatible");

        return DslType::function(
            {inner.inputs()[0]},
            outer.output());
    }
}

#endif
