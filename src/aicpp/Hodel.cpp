#include <algorithm>
#include <map>
#include <numeric>
#include <ranges>
#include <unordered_set>

#include "aicpp/Hodel.h"

constexpr hodel::IntegerType MAX_SIZE = 30;
constexpr size_t SHOOT_DISTANCE = 42;

using IntegerCountMap = std::map<hodel::IntegerType, hodel::IntegerType>;

hodel::IndicesType rectangleOutline(hodel::IntegerType si, hodel::IntegerType sj, hodel::IntegerType ei, hodel::IntegerType ej)
{
    hodel::IndicesType result;

    for (hodel::IntegerType i = si; i <= ei; ++i)
    {
        result.emplace(i, sj);
        result.emplace(i, ej);
    }

    for (hodel::IntegerType j = sj; j <= ej; ++j)
    {
        result.emplace(si, j);
        result.emplace(ei, j);
    }

    return result;
}

IntegerCountMap colorCounts(hodel::Element const& element)
{
    IntegerCountMap counts;

    std::visit(
        [&] (auto const& value)
        {
            using T = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<T, hodel::GridType>)
            {
                for (auto const& row : value)
                {
                    for (auto const& color : row)
                        ++counts[color];
                }
            }
            else
            {
                for (auto const& [color, position] : value)
                    ++counts[color];
            }
        },
        element);

    return counts;
}

template <typename T>
static std::vector<std::any> toVector(T const& container)
{
    std::vector<std::any> values;
    values.reserve(container.size());

    for (auto const& v : container)
        values.emplace_back(v);

    return values;
}

template <typename T>
static std::vector<typename T::value_type> toVector(std::any const& container)
{
    if (container.type() != typeid(T))
        return std::vector<typename T::value_type>{};

    auto const container_{std::any_cast<T>(container)};

    return std::vector<typename T::value_type>{container_.begin(), container_.end()};
}

template <typename T>
static std::any order(std::any const& container, std::function<std::any(std::vector<std::any> const&)> const& function)
{
    if (container.type() != typeid(T))
        return std::any{};

    auto values = toVector<T>(container);

    try
    {
        std::sort(values.begin(), values.end(),
                  [function] (auto const& x, auto const& y) -> auto
                  {
                      return std::any_cast<hodel::Boolean>(hodel::greater({function({y}), function({x})}));
                  });
    }
    catch (std::exception const&)
    {
        return std::any{};
    }

    return values;
}

template <typename T>
static std::any repeat(std::any const& item, hodel::IntegerType const& n)
{
    if (n <= 0)
        return std::any{};

    if (item.type() == typeid(T))
        return std::vector<T>(n, std::any_cast<T>(item));

    return std::any{};
}

template <typename T>
static std::any equality(std::any const& a, std::any const& b)
{
    if (a.type() == typeid(T) && b.type() == typeid(T))
        return hodel::Boolean{std::any_cast<T>(a) == std::any_cast<T>(b)};

    return std::any{};
}

template <typename T>
static std::any size_set(std::any const& value)
{
    if (value.type() == typeid(T))
        return static_cast<hodel::IntegerType>(std::any_cast<T>(value).size());

    return std::any{};
}

template <typename T>
static std::any difference_sets(std::any const& a, std::any const& b)
{
    if (a.type() == typeid(T) && b.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(a)};
        auto const y{std::any_cast<T>(b)};
        std::vector<typename T::value_type> v;

        std::set_difference(x.begin(), x.end(), y.begin(), y.end(), std::back_inserter(v));

        return T{v.begin(), v.end()};
    }

    return std::any{};
}

template <typename T>
static std::any intersection_sets(std::any const& a, std::any const& b)
{
    if (a.type() == typeid(T) && b.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(a)};
        auto const y{std::any_cast<T>(b)};
        std::vector<typename T::value_type> v;

        std::set_intersection(x.begin(), x.end(), y.begin(), y.end(), std::back_inserter(v));

        return T{v.begin(), v.end()};
    }

    return std::any{};
}

std::any do_op(std::any const& a, std::any const& b, std::function<hodel::IntegerType(hodel::IntegerType, hodel::IntegerType)> const& op)
{
    if (a.type() == typeid(hodel::Numerical) && b.type() == typeid(hodel::Numerical))
    {
        auto const x{std::any_cast<hodel::Numerical>(a)};
        auto const y{std::any_cast<hodel::Numerical>(b)};

        if (std::holds_alternative<hodel::IntegerType>(x) && std::holds_alternative<hodel::IntegerType>(y))
            return op(std::get<hodel::IntegerType>(x), std::get<hodel::IntegerType>(y));
        else if (std::holds_alternative<hodel::IntegerTuple>(x) && std::holds_alternative<hodel::IntegerTuple>(y))
        {
            auto const& c{std::get<hodel::IntegerTuple>(x)};
            auto const& d{std::get<hodel::IntegerTuple>(y)};

            return hodel::IntegerTuple{op(c.first, d.first), op(c.second, d.second)};
        }
        else if (std::holds_alternative<hodel::IntegerType>(x) && std::holds_alternative<hodel::IntegerTuple>(y))
        {
            auto const& c{std::get<hodel::IntegerType>(x)};
            auto const& d{std::get<hodel::IntegerTuple>(y)};

            return hodel::IntegerTuple{op(c, d.first), op(c, d.second)};
        }
        else if (std::holds_alternative<hodel::IntegerTuple>(x) && std::holds_alternative<hodel::IntegerType>(y))
        {
            auto const& c{std::get<hodel::IntegerTuple>(x)};
            auto const& d{std::get<hodel::IntegerType>(y)};

            return hodel::IntegerTuple{op(c.first, d), op(c.second, d)};
        }
    }
    else if (a.type() == typeid(hodel::IntegerType))
    {
        auto const x{std::any_cast<hodel::IntegerType>(a)};

        if (b.type() == typeid(hodel::IntegerType))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::IntegerType>(b)}, op);
        else if (b.type() == typeid(hodel::IntegerTuple))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::IntegerTuple>(b)}, op);
    }
    else if (a.type() == typeid(hodel::IntegerTuple))
    {
        auto const x{std::any_cast<hodel::IntegerTuple>(a)};

        if (b.type() == typeid(hodel::IntegerType))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::IntegerType>(b)}, op);
        else if (b.type() == typeid(hodel::IntegerTuple))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::IntegerTuple>(b)}, op);
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::identity(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    return x;
}

std::any hodel::add(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::plus<IntegerType>{});
}

std::any hodel::subtract(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::minus<IntegerType>{});
}

std::any hodel::multiply(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::multiplies<IntegerType>{});
}

std::any hodel::divide(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (b.type() == typeid(hodel::Numerical))
    {
        auto const y{std::any_cast<hodel::Numerical>(b)};

        if (std::holds_alternative<hodel::IntegerType>(y))
        {
            if (!std::get<hodel::IntegerType>(y))
                throw std::runtime_error{"Wrong value"};
        }
        else if (std::holds_alternative<hodel::IntegerTuple>(y))
        {
            auto const& d{std::get<hodel::IntegerTuple>(y)};

            if (!d.first || !d.second)
                throw std::runtime_error{"Wrong value"};
        }
    }
    else if (b.type() == typeid(hodel::IntegerType))
    {
        auto const y{std::any_cast<hodel::IntegerType>(b)};

        if (!y)
            throw std::runtime_error{"Wrong value"};
    }
    else if (b.type() == typeid(hodel::IntegerTuple))
    {
        auto const y{std::any_cast<hodel::IntegerTuple>(b)};

        if (!y.first || !y.second)
            throw std::runtime_error{"Wrong value"};
    }

    return do_op(a, b, std::divides<IntegerType>{});
}

std::any hodel::invert(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const n{args.front()};

    if (n.type() == typeid(Numerical))
    {
        auto const x{std::any_cast<Numerical>(n)};

        if (std::holds_alternative<IntegerType>(x))
        {
            auto const& y{std::get<IntegerType>(x)};

            return IntegerType{-y};
        }
        else if (std::holds_alternative<IntegerTuple>(x))
        {
            auto const& y{std::get<IntegerTuple>(x)};

            return Numerical{std::make_pair<IntegerType, IntegerType>(-y.first, -y.second)};
        }
    }
    else if (n.type() == typeid(IntegerType))
        return invert({Numerical{std::any_cast<IntegerType>(n)}});
    else if (n.type() == typeid(IntegerTuple))
        return invert({Numerical{std::any_cast<IntegerTuple>(n)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::even(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const n{args.front()};

    if (n.type() == typeid(hodel::IntegerType))
        return Boolean{std::any_cast<IntegerType>(n) % 2 == 0};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::double_(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const n{args.front()};

    if (n.type() == typeid(hodel::Numerical))
    {
        auto const x{std::any_cast<hodel::Numerical>(n)};

        if (std::holds_alternative<IntegerType>(x))
        {
            auto const& y{std::get<IntegerType>(x)};

            return IntegerType{y * 2};
        }
        else if (std::holds_alternative<IntegerTuple>(x))
        {
            auto const& y{std::get<IntegerTuple>(x)};

            return Numerical{std::make_pair<IntegerType, IntegerType>(y.first * 2, y.second * 2)};
        }
    }
    else if (n.type() == typeid(IntegerType))
        return double_({Numerical{std::any_cast<IntegerType>(n)}});
    else if (n.type() == typeid(IntegerTuple))
        return double_({Numerical{std::any_cast<IntegerTuple>(n)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::halve(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const n{args.front()};

    if (n.type() == typeid(hodel::Numerical))
    {
        auto const x{std::any_cast<hodel::Numerical>(n)};

        if (std::holds_alternative<IntegerType>(x))
        {
            auto const& y{std::get<IntegerType>(x)};

            return IntegerType{y / 2};
        }
        else if (std::holds_alternative<IntegerTuple>(x))
        {
            auto const& y{std::get<IntegerTuple>(x)};

            return Numerical{std::make_pair<IntegerType, IntegerType>(y.first / 2, y.second / 2)};
        }
    }
    else if (n.type() == typeid(IntegerType))
        return halve({Numerical{std::any_cast<IntegerType>(n)}});
    else if (n.type() == typeid(IntegerTuple))
        return halve({Numerical{std::any_cast<IntegerTuple>(n)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::flip(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const b{args.front()};

    if (b.type() == typeid(Boolean))
        return Boolean{!std::any_cast<Boolean>(b)};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::equality(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = ::equality<Boolean>(a, b); r.has_value()) return r;
    if (auto r = ::equality<IntegerType>(a, b); r.has_value()) return r;
    if (auto r = ::equality<IntegerTuple>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Numerical>(a, b); r.has_value()) return r;
    if (auto r = ::equality<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = ::equality<GridType>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Cell>(a, b); r.has_value()) return r;
    if (auto r = ::equality<ObjectType>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Objects>(a, b); r.has_value()) return r;
    if (auto r = ::equality<IndicesType>(a, b); r.has_value()) return r;
    if (auto r = ::equality<IndicesSet>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Patch>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Element>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Piece>(a, b); r.has_value()) return r;
    if (auto r = ::equality<std::vector<IntegerType> >(a, b); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::contained(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const value{args[0]};
    auto const container{args[1]};

    if (value.type()     == typeid(IntegerType)    &&
        container.type() == typeid(IntegerSet))
    {
        auto const v{std::any_cast<IntegerType>(value)};
        auto const c{std::any_cast<IntegerSet>(container)};

        return static_cast<Boolean>(c.contains(v));
    }
    if (value.type()     == typeid(IntegerType)    &&
        container.type() == typeid(std::vector<IntegerType>))
    {
        auto const v{std::any_cast<IntegerType>(value)};
        auto const c{std::any_cast<std::vector<IntegerType> >(container)};

        return static_cast<Boolean>(std::find(c.begin(), c.end(), v) != c.end());
    }
    else if (container.type() == typeid(ObjectType))
    {
        auto const c{std::any_cast<ObjectType>(container)};

        if (value.type() == typeid(Cell))
        {
            auto const v{std::any_cast<Cell>(value)};

            return static_cast<Boolean>(c.contains(v));
        }
    }
    else if (value.type()     == typeid(ObjectType)  &&
             container.type() == typeid(Objects))
    {
        auto const v{std::any_cast<ObjectType>(value)};
        auto const c{std::any_cast<Objects>(container)};

        return static_cast<Boolean>(c.contains(v));
    }
    else if (value.type()     == typeid(IntegerTuple) &&
             container.type() == typeid(IndicesType))
    {
        auto const v{std::any_cast<IntegerTuple>(value)};
        auto const c{std::any_cast<IndicesType>(container)};

        return static_cast<Boolean>(c.contains(v));
    }
    else if (value.type()     == typeid(IndicesType)    &&
             container.type() == typeid(IndicesSet))
    {
        auto const v{std::any_cast<IndicesType>(value)};
        auto const c{std::any_cast<IndicesSet>(container)};

        return static_cast<Boolean>(c.contains(v));
    }
    else if (value.type()     == typeid(Patch)   &&
             container.type() == typeid(Objects))
    {
        auto const p{std::any_cast<Patch>(value)};
        auto const c{std::any_cast<Objects>(container)};

        if (std::holds_alternative<ObjectType>(p))
            return static_cast<Boolean>(c.contains(std::get<ObjectType>(p)));
    }

    throw std::runtime_error{"Wrong value"};
}

template <typename T, typename S>
static std::any combine_sets(std::any const& a, std::any const& b)
{
    if (a.type() == typeid(T) && b.type() == typeid(S))
    {
        auto const x{std::any_cast<T>(a)};
        auto const y{std::any_cast<S>(b)};

        std::vector<typename T::value_type> v{x.begin(), x.end()};
        v.insert(v.end(), y.begin(), y.end());

        return T{v.begin(), v.end()};
    }

    return std::any{};
}

std::any hodel::combine(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};

    bool recall{false};

    if (a.type() == typeid(IntegerTuple))
    {
        auto const a_{std::any_cast<IntegerTuple>(a)};
        std::vector<IntegerType> const v{a_.first, a_.second};
        a = v;
        recall = true;
    }

    if (b.type() == typeid(IntegerTuple))
    {
        auto const b_{std::any_cast<IntegerTuple>(b)};
        std::vector<IntegerType> const v{b_.first, b_.second};
        b = v;
        recall = true;
    }

    if (recall)
    {
        auto const result{std::any_cast<std::vector<IntegerType> >(combine({a, b}))};

        return IntegerTuple{result.at(0), result.at(1)};
    }

    if (auto r = combine_sets<IntegerSet, IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<IntegerSet, std::vector<IntegerType> >(a, b); r.has_value()) return r;
    if (auto r = combine_sets<std::vector<IntegerType>, IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<ObjectType, ObjectType>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<Objects, Objects>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<IndicesType, IndicesType>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<IndicesType, std::vector<IntegerTuple> >(a, b); r.has_value()) return r;
    if (auto r = combine_sets<std::vector<IntegerTuple>, IndicesType>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<IndicesSet, IndicesSet>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<std::vector<IntegerTuple>, std::vector<IntegerTuple> >(a, b); r.has_value()) return r;
    if (auto r = combine_sets<std::vector<IntegerType>, std::vector<IntegerType> >(a, b); r.has_value()) return r;
    if (auto r = combine_sets<GridType, GridType>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<std::vector<GridType>, std::vector<GridType> >(a, b); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::intersection(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = intersection_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = intersection_sets<ObjectType>    (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<IndicesType>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<IndicesSet>(a, b); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::difference(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = difference_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = difference_sets<ObjectType>    (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<IndicesType>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<IndicesSet>(a, b); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::dedupe(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const tup{args.front()};

    if (tup.type() == typeid(Element))
    {
        auto const x{std::any_cast<Element>(tup)};

        if (std::holds_alternative<GridType>(x))
            return dedupe({std::get<GridType>(x)});
    }
    else if (tup.type() == typeid(Piece))
    {
        auto const x{std::any_cast<Piece>(tup)};

        if (std::holds_alternative<GridType>(x))
            return dedupe({std::get<GridType>(x)});
    }
    else if (tup.type() == typeid(GridType))
    {
        auto const x{std::any_cast<GridType>(tup)};
        GridType y;
        y.reserve(x.size());

        for (size_t i{0}; i < x.size(); ++i)
        {
            auto const result{std::ranges::find_end(x, std::views::single(x[i]))};

            if (result.begin() != x.end() && std::distance(x.begin(), result.begin()) == i)
                y.emplace_back(x[i]);
        }

        return y;
    }
    else if (tup.type() == typeid(std::vector<GridType>))
    {
        auto const x{std::any_cast<std::vector<GridType> >(tup)};
        std::vector<GridType> y;
        y.reserve(x.size());

        for (size_t i{0}; i < x.size(); ++i)
        {
            auto const result{std::ranges::find_end(x, std::views::single(x[i]))};

            if (result.begin() != x.end() && std::distance(x.begin(), result.begin()) == i)
                y.emplace_back(x[i]);
        }

        return y;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::order(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const compfunc{args[1]};

    if (compfunc.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    if (container.type() == typeid(IntegerTuple))
    {
        auto const container_{std::any_cast<IntegerTuple>(container)};
        std::vector<IntegerType> const v{container_.first, container_.second};

        return order({v, compfunc});
    }

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    if (auto r = ::order<IntegerSet>(container, f); r.has_value()) return r;
    if (auto r = ::order<std::vector<IntegerType> >(container, f); r.has_value()) return r;
    if (auto r = ::order<std::vector<GridType> >(container, f); r.has_value()) return r;
    if (auto r = ::order<Objects>(container, f); r.has_value()) return r;
    if (auto r = ::order<IndicesSet>(container, f); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::repeat(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const item{args[0]};
    auto const num{args[1]};

    if (num.type() == typeid(IntegerType))
    {
        auto const n{std::any_cast<IntegerType>(num)};

        if (n <= 0 || n > 100)
            throw std::runtime_error{"Wrong value"};

        if (auto r = ::repeat<IntegerType>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<IntegerTuple>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Boolean>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Numerical>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<GridType>(item, n); r.has_value()) return r;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::greater(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(IntegerType) && b.type() == typeid(IntegerType))
        return Boolean{std::any_cast<IntegerType>(a) > std::any_cast<IntegerType>(b)};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::size(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (container.type() == typeid(IntegerTuple))
        return IntegerType{2};

    if (auto r = size_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = size_set<ObjectType>    (container); r.has_value()) return r;
    if (auto r = size_set<Objects>   (container); r.has_value()) return r;
    if (auto r = size_set<IndicesType>   (container); r.has_value()) return r;
    if (auto r = size_set<IndicesSet>(container); r.has_value()) return r;
    if (auto r = size_set<std::vector<IntegerType> >(container); r.has_value()) return r;

    if (container.type() == typeid(GridType))
    {
        auto const x{std::any_cast<GridType>(container)};

        return static_cast<IntegerType>(x.size());
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::merge(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const containers{args.front()};

    if (containers.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(containers)};

        if (std::holds_alternative<GridType>(piece))
            return merge({std::get<GridType>(piece)});
    }

    if (containers.type() == typeid(Objects))
    {
        auto const containers_{std::any_cast<Objects>(containers)};

        ObjectType result;

        for (auto const& container : containers_)
            result.insert(container.begin(), container.end());

        return result;
    }
    else if (containers.type() == typeid(IndicesSet))
    {
        auto const containers_{std::any_cast<IndicesSet>(containers)};

        IndicesType result;

        for (auto const& container : containers_)
            result.insert(container.begin(), container.end());

        return result;
    }
    else if (containers.type() == typeid(GridType))
    {
        auto const containers_{std::any_cast<GridType>(containers)};

        std::vector<IntegerType> result;

        for (auto const& container : containers_)
            result.insert(result.end(), container.begin(), container.end());

        return result;
    }
    else if (containers.type() == typeid(std::vector<GridType>))
    {
        auto const containers_{std::any_cast<std::vector<GridType> >(containers)};

        GridType result;

        for (auto const& container : containers_)
            result.insert(result.end(), container.begin(), container.end());

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::maximum(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (container.type() == typeid(IntegerSet))
    {
        auto const set{std::any_cast<IntegerSet>(container)};

        if (set.empty())
            throw std::runtime_error{"Wrong value"};

        return *std::max_element(set.begin(), set.end());
    }
    else if (container.type() == typeid(std::vector<IntegerType>))
    {
        auto const v{std::any_cast<std::vector<IntegerType>>(container)};

        if (v.empty())
            throw std::runtime_error{"Wrong value"};

        return *std::max_element(v.begin(), v.end());
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::minimum(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (container.type() == typeid(IntegerSet))
    {
        auto const set{std::any_cast<IntegerSet>(container)};

        if (set.empty())
            throw std::runtime_error{"Wrong value"};

        return *std::min_element(set.begin(), set.end());
    }
    else if (container.type() == typeid(std::vector<IntegerType>))
    {
        auto const v{std::any_cast<std::vector<IntegerType>>(container)};

        if (v.empty())
            throw std::runtime_error{"Wrong value"};

        return *std::min_element(v.begin(), v.end());
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::valmax(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const compfunc{args[1]};

    if (compfunc.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    if (container.type() == typeid(IntegerTuple))
    {
        auto const container_{std::any_cast<IntegerTuple>(container)};
        std::vector<IntegerType> const v{container_.first, container_.second};

        return valmax({v, compfunc});
    }

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    std::vector<std::any> values;

    if (container.type() == typeid(IntegerSet))
        values = toVector(std::any_cast<IntegerSet>(container));
    else if (container.type() == typeid(std::vector<IntegerType>))
        values = toVector(std::any_cast<std::vector<IntegerType> >(container));
    else if (container.type() == typeid(std::vector<GridType>))
        values = toVector(std::any_cast<std::vector<GridType> >(container));
    else if (container.type() == typeid(Objects))
        values = toVector(std::any_cast<Objects>(container));
    else if (container.type() == typeid(IndicesType))
        values = toVector(std::any_cast<IndicesType>(container));

    try
    {
        for (auto& v : values)
            v = f({v});

        auto const it{std::max_element(values.begin(), values.end(), [] (auto const& x, auto const& y) -> auto { return std::any_cast<Boolean>(greater({y, x})); } )};

        if (it != values.end())
            return *it;
    }
    catch (std::exception const&)
    {
        throw std::runtime_error{"Wrong value"};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::valmin(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const compfunc{args[1]};

    if (compfunc.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    if (container.type() == typeid(IntegerTuple))
    {
        auto const container_{std::any_cast<IntegerTuple>(container)};
        std::vector<IntegerType> const v{container_.first, container_.second};

        return valmin({v, compfunc});
    }

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    std::vector<std::any> values;

    if (container.type() == typeid(IntegerSet))
        values = toVector(std::any_cast<IntegerSet>(container));
    else if (container.type() == typeid(std::vector<IntegerType>))
        values = toVector(std::any_cast<std::vector<IntegerType> >(container));
    else if (container.type() == typeid(std::vector<GridType>))
        values = toVector(std::any_cast<std::vector<GridType> >(container));
    else if (container.type() == typeid(Objects))
        values = toVector(std::any_cast<Objects>(container));
    else if (container.type() == typeid(IndicesType))
        values = toVector(std::any_cast<IndicesType>(container));

    try
    {
        for (auto& v : values)
            v = f({v});

        auto const it{std::min_element(values.begin(), values.end(), [] (auto const& x, auto const& y) -> auto { return std::any_cast<Boolean>(greater({y, x})); } )};

        if (it != values.end())
            return *it;
    }
    catch (std::exception const&)
    {
        throw std::runtime_error{"Wrong value"};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::argmax(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const compfunc{args[1]};

    if (compfunc.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    if (container.type() == typeid(IntegerTuple))
    {
        auto const container_{std::any_cast<IntegerTuple>(container)};
        std::vector<IntegerType> const v{container_.first, container_.second};

        return argmax({v, compfunc});
    }

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    std::vector<std::any> values;

    if (container.type() == typeid(IntegerSet))
        values = toVector(std::any_cast<IntegerSet>(container));
    else if (container.type() == typeid(std::vector<IntegerType>))
        values = toVector(std::any_cast<std::vector<IntegerType> >(container));
    else if (container.type() == typeid(std::vector<GridType>))
        values = toVector(std::any_cast<std::vector<GridType> >(container));
    else if (container.type() == typeid(Objects))
        values = toVector(std::any_cast<Objects>(container));
    else if (container.type() == typeid(IndicesType))
        values = toVector(std::any_cast<IndicesType>(container));

    try
    {
        if (values.size() == 1)
            f({*values.begin()});

        auto const it{std::max_element(values.begin(), values.end(), [f] (auto const& x, auto const& y) -> auto { return std::any_cast<Boolean>(greater({f({y}), f({x})})); } )};

        if (it != values.end())
            return *it;
    }
    catch (std::exception const&)
    {
        throw std::runtime_error{"Wrong value"};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::argmin(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const compfunc{args[1]};

    if (compfunc.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    if (container.type() == typeid(IntegerTuple))
    {
        auto const container_{std::any_cast<IntegerTuple>(container)};
        std::vector<IntegerType> const v{container_.first, container_.second};

        return argmin({v, compfunc});
    }

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    std::vector<std::any> values;

    if (container.type() == typeid(IntegerSet))
        values = toVector(std::any_cast<IntegerSet>(container));
    else if (container.type() == typeid(std::vector<IntegerType>))
        values = toVector(std::any_cast<std::vector<IntegerType> >(container));
    else if (container.type() == typeid(std::vector<GridType>))
        values = toVector(std::any_cast<std::vector<GridType> >(container));
    else if (container.type() == typeid(Objects))
        values = toVector(std::any_cast<Objects>(container));
    else if (container.type() == typeid(IndicesType))
        values = toVector(std::any_cast<IndicesType>(container));

    try
    {
        if (values.size() == 1)
            f({*values.begin()});

        auto const it{std::min_element(values.begin(), values.end(), [f] (auto const& x, auto const& y) -> auto { return std::any_cast<Boolean>(greater({f({y}), f({x})})); } )};

        if (it != values.end())
            return *it;
    }
    catch (std::exception const&)
    {
        throw std::runtime_error{"Wrong value"};
    }

    throw std::runtime_error{"Wrong value"};
}

template <typename T>
struct VectorHash
{
    std::size_t operator()(std::vector<T> const& v) const
    {
        std::size_t seed = 0;

        for (auto const& x : v)
        {
            seed ^= std::hash<T>{}(x)
                  + 0x9e3779b9
                  + (seed << 6)
                  + (seed >> 2);
        }

        return seed;
    }
};

template <typename T>
struct std::hash<std::vector<T> >
{
    std::size_t operator()(std::vector<T> const& v) const
    {
        return VectorHash<T>{}(v);
    }
};

template <typename T>
std::any mostcommon(std::any const& container)
{
    if (container.type() != typeid(T))
        return std::any{};

    auto const container_{std::any_cast<T>(container)};

    if (container_.empty())
        throw std::runtime_error{"Wrong value"};

    std::unordered_map<typename T::value_type, size_t> counts;

    for (auto const& value : container_)
        ++counts[value];

    auto result{container_.front()};
    auto maxCount{counts[result]};

    for (auto const& value : container_)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

std::any hodel::mostcommon(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};

    if (container.type() == typeid(IntegerTuple))
    {
        auto const container_{std::any_cast<IntegerTuple>(container)};
        std::vector<IntegerType> const v{container_.first, container_.second};

        return mostcommon({v});
    }

    if (auto r = ::mostcommon<std::vector<IntegerType> >(container); r.has_value()) return r;
    if (auto r = ::mostcommon<std::vector<GridType> >(container); r.has_value()) return r;
    if (auto r = ::mostcommon<GridType>(container); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

template <typename T>
std::any leastcommon(std::any const& container)
{
    if (container.type() != typeid(T))
        return std::any{};

    auto const container_{std::any_cast<T>(container)};

    if (container_.empty())
        throw std::runtime_error{"Wrong value"};

    std::unordered_map<typename T::value_type, size_t> counts;

    for (auto const& value : container_)
        ++counts[value];

    auto result{container_.front()};
    auto minCount{counts[result]};

    for (auto const& value : container_)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

std::any hodel::leastcommon(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};

    if (container.type() == typeid(IntegerTuple))
    {
        auto const container_{std::any_cast<IntegerTuple>(container)};
        std::vector<IntegerType> const v{container_.first, container_.second};

        return leastcommon({v});
    }

    if (auto r = ::leastcommon<std::vector<IntegerType> >(container); r.has_value()) return r;
    if (auto r = ::leastcommon<std::vector<GridType> >(container); r.has_value()) return r;
    if (auto r = ::leastcommon<GridType>(container); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

template <typename T>
static std::any init_set(std::any const& value)
{
    if (value.type() == typeid(typename T::value_type))
        return T{std::any_cast<typename T::value_type>(value)};

    return std::any{};
}

std::any hodel::initset(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const value{args.front()};

    if (auto r = init_set<IntegerSet>(value); r.has_value()) return r;
    if (auto r = init_set<ObjectType>    (value); r.has_value()) return r;
    if (auto r = init_set<Objects>   (value); r.has_value()) return r;
    if (auto r = init_set<IndicesType>   (value); r.has_value()) return r;
    if (auto r = init_set<IndicesSet>(value); r.has_value()) return r;
    if (auto r = init_set<std::vector<IntegerType> >(value); r.has_value()) return r;
    if (auto r = init_set<std::vector<GridType> >(value); r.has_value()) return r;
    if (auto r = init_set<std::vector<std::function<std::any(std::vector<std::any> const&)> > >(value); r.has_value()) return r;
    if (auto r = init_set<std::vector<Boolean> >(value); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::both(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Boolean) && b.type() == typeid(Boolean))
        return Boolean{std::any_cast<Boolean>(a) && std::any_cast<Boolean>(b)};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::either(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Boolean) && b.type() == typeid(Boolean))
        return Boolean{std::any_cast<Boolean>(a) || std::any_cast<Boolean>(b)};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::increment(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    if (x.type() == typeid(IntegerTuple))
        return increment({Numerical{std::any_cast<IntegerTuple>(x)}});
    else if (x.type() == typeid(IntegerType))
        return increment({Numerical{std::any_cast<IntegerType>(x)}});
    else if (x.type() == typeid(Numerical))
    {
        auto const y{std::any_cast<Numerical>(x)};

        if (std::holds_alternative<IntegerType>(y))
            return IntegerType{std::get<IntegerType>(y) + 1};
        else if (std::holds_alternative<IntegerTuple>(y))
        {
            auto const z{std::get<IntegerTuple>(y)};

            return IntegerTuple{z.first + 1, z.second + 1};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::decrement(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    if (x.type() == typeid(IntegerTuple))
        return decrement({Numerical{std::any_cast<IntegerTuple>(x)}});
    else if (x.type() == typeid(IntegerType))
        return decrement({Numerical{std::any_cast<IntegerType>(x)}});
    else if (x.type() == typeid(Numerical))
    {
        auto const y{std::any_cast<Numerical>(x)};

        if (std::holds_alternative<IntegerType>(y))
            return IntegerType{std::get<IntegerType>(y) - 1};
        else if (std::holds_alternative<IntegerTuple>(y))
        {
            auto const z{std::get<IntegerTuple>(y)};

            return IntegerTuple{z.first - 1, z.second - 1};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::crement(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    if (x.type() == typeid(IntegerTuple))
        return decrement({Numerical{std::any_cast<IntegerTuple>(x)}});
    else if (x.type() == typeid(IntegerType))
        return decrement({Numerical{std::any_cast<IntegerType>(x)}});
    else if (x.type() == typeid(Numerical))
    {
        auto const y{std::any_cast<Numerical>(x)};

        if (std::holds_alternative<IntegerType>(y))
        {
            auto const z{std::get<IntegerType>(y)};

            if (!z)
                return z;
            else if (z > 0)
                return increment(args);
            else
                return decrement(args);
        }
        else if (std::holds_alternative<IntegerTuple>(y))
        {
            auto const z{std::get<IntegerTuple>(y)};
            IntegerTuple result{std::make_pair<IntegerType, IntegerType>(0, 0)};

            if (!z.first)
                result.first = z.first;
            else if (z.first > 0)
                ++result.first;
            else
                --result.first;

            if (!z.second)
                result.second = z.second;
            else if (z.second > 0)
                ++result.second;
            else
                --result.second;

            return result;
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::sign(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    if (x.type() == typeid(Numerical))
    {
        auto const y{std::any_cast<Numerical>(x)};

        if (std::holds_alternative<IntegerType>(y))
        {
            auto const z{std::get<IntegerType>(y)};

            if (!z)
                return IntegerType{0};
            else if (z > 0)
                return IntegerType{1};
            else
                return IntegerType{-1};
        }
        else if (std::holds_alternative<IntegerTuple>(y))
        {
            auto const z{std::get<IntegerTuple>(y)};
            IntegerTuple result{std::make_pair<IntegerType, IntegerType>(0, 0)};

            if (!z.first)
                result.first = 0;
            else if (z.first > 0)
                result.first = 1;
            else
                result.first = -1;

            if (!z.second)
                result.second = 0;
            else if (z.second > 0)
                result.second = 1;
            else
                result.second = -1;

            return result;
        }
    }
    else if (x.type() == typeid(IntegerType))
        return sign({Numerical{std::any_cast<IntegerType>(x)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::positive(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    if (x.type() == typeid(IntegerType))
        return Boolean{std::any_cast<IntegerType>(x) > 0};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::toivec(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const i{args.front()};

    if (i.type() == typeid(IntegerType))
        return IntegerTuple{std::make_pair<IntegerType, IntegerType>(std::any_cast<IntegerType>(i), 0)};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::tojvec(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const j{args.front()};

    if (j.type() == typeid(IntegerType))
        return IntegerTuple{std::make_pair<IntegerType, IntegerType>(0, std::any_cast<IntegerType>(j))};

    throw std::runtime_error{"Wrong value"};
}

template <typename Container>
std::any sfilter(std::any const& container, std::function<std::any(std::vector<std::any> const&)> const& condition)
{
    if (container.type() != typeid(Container))
        return std::any{};

    auto const container_{std::any_cast<Container>(container)};
    Container result;

    try
    {
        for (const auto& element : container_)
        {
            if (std::any_cast<hodel::Boolean>(condition({element})))
                result.insert(result.end(), element);
        }

        return result;
    }
    catch (std::exception const&)
    {
        return std::any{};
    }

    return std::any{};
}

std::any hodel::sfilter(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const condition{args[1]};

    if (condition.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
       throw std::runtime_error{"Wrong value"};

    auto const condition_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(condition)};
    auto const container{args[0]};

    if (container.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(container)};

        if (std::holds_alternative<GridType>(piece))
            return sfilter({std::get<GridType>(piece), condition});
    }

    if (auto r = ::sfilter<IntegerSet>(container, condition_); r.has_value()) return r;
    if (auto r = ::sfilter<ObjectType>(container, condition_); r.has_value()) return r;
    if (auto r = ::sfilter<Objects>(container, condition_); r.has_value()) return r;
    if (auto r = ::sfilter<IndicesType>(container, condition_); r.has_value()) return r;
    if (auto r = ::sfilter<IndicesSet>(container, condition_); r.has_value()) return r;
    if (auto r = ::sfilter<GridType>(container, condition_); r.has_value()) return r;
    if (auto r = ::sfilter<std::vector<IntegerType> >(container, condition_); r.has_value()) return r;
    if (auto r = ::sfilter<std::vector<GridType> >(container, condition_); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::mfilter(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const condition{args[1]};

    return merge({sfilter({container, condition})});
}

template <typename Container>
std::any extract(std::any const& container, std::function<std::any(std::vector<std::any> const)> const& condition)
{
    if (container.type() != typeid(Container))
        return std::any{};

    auto const container_{std::any_cast<Container>(container)};

    if (container_.empty())
        throw std::runtime_error{"Wrong value"};

    for (auto it{container_.begin()}; it != container_.end(); ++it)
    {
        if (std::any_cast<hodel::Boolean>(condition({*it})))
            return *it;
    }

    return std::any{};
}

std::any hodel::extract(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const condition{args[1]};

    if (condition.type() != typeid(std::function<std::any(std::vector<std::any> const)>))
        throw std::runtime_error{"Wrong value"}; 

    auto const condition_{std::any_cast<std::function<std::any(std::vector<std::any> const)> >(condition)};

    if (auto r = ::extract<IntegerSet>(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<std::vector<IntegerType> >(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<ObjectType>(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<std::vector<Cell> >(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<Objects>(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<std::vector<ObjectType> >(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<IndicesType>(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<std::vector<IntegerTuple> >(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<IndicesSet>(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<std::vector<IndicesType> >(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<std::vector<IntegerType> >(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<std::vector<GridType> >(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<GridType>(container, condition_); r.has_value()) return r;
    if (auto r = ::extract<std::vector<std::function<std::any(std::vector<std::any> const&)> > >(container, condition_); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

template <typename T>
static std::any vector_set(std::any const& container)
{
    if (container.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(container)};

        return std::vector<typename T::value_type>{x.begin(), x.end()};
    }

    return std::any{};
}

std::any hodel::totuple(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (auto r = vector_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = vector_set<ObjectType>    (container); r.has_value()) return r;
    if (auto r = vector_set<Objects>   (container); r.has_value()) return r;
    if (auto r = vector_set<IndicesType>   (container); r.has_value()) return r;
    if (auto r = vector_set<IndicesSet>(container); r.has_value()) return r;
    if (auto r = vector_set<std::vector<IntegerType> >(container); r.has_value()) return r;
    if (auto r = vector_set<std::vector<GridType> >(container); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

template <typename T>
static std::any first_set(std::any const& container)
{
    if (container.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(container)};

        if (x.empty())
            return std::any{};

        return *x.begin();
    }

    return std::any{};
}

std::any hodel::first(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (container.type() == typeid(IntegerTuple))
        return std::any_cast<IntegerTuple>(container).first;

    if (auto r = first_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<IntegerType> >(container); r.has_value()) return r;
    if (auto r = first_set<ObjectType>(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<Cell> >(container); r.has_value()) return r;
    if (auto r = first_set<Objects>(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<ObjectType> >(container); r.has_value()) return r;
    if (auto r = first_set<IndicesType>(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<IntegerTuple> >(container); r.has_value()) return r;
    if (auto r = first_set<IndicesSet>(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<IndicesType> >(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<IntegerType> >(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<GridType> >(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<std::function<std::any(std::vector<std::any> const&)> > >(container); r.has_value()) return r;

    if (container.type() == typeid(GridType))
    {
        auto const x{std::any_cast<GridType>(container)};

        if (x.empty())
            throw std::runtime_error{"Wrong value"};

        return x.front();
    }

    throw std::runtime_error{"Wrong value"};
}

template <typename T>
static std::any last_set(std::any const& container)
{
    if (container.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(container)};

        if (x.empty())
            return std::any{};

        return *x.rbegin();
    }

    return std::any{};
}

std::any hodel::last(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (container.type() == typeid(IntegerTuple))
        return std::any_cast<IntegerTuple>(container).second;

    if (auto r = last_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<IntegerType> >(container); r.has_value()) return r;
    if (auto r = last_set<ObjectType>(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<Cell> >(container); r.has_value()) return r;
    if (auto r = last_set<Objects>(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<ObjectType> >(container); r.has_value()) return r;
    if (auto r = last_set<IndicesType>(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<IntegerTuple> >(container); r.has_value()) return r;
    if (auto r = last_set<IndicesSet>(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<IndicesType> >(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<IntegerType> >(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<GridType> >(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<std::function<std::any(std::vector<std::any> const&)> > >(container); r.has_value()) return r;

    if (container.type() == typeid(GridType))
    {
        auto const x{std::any_cast<GridType>(container)};

        if (x.empty())
            throw std::runtime_error{"Wrong value"};

        return x.back();
    }

    throw std::runtime_error{"Wrong value"};
}

template <typename Container>
std::any insert(std::any const& value, std::any const& container)
{
    if (!(value.type() == typeid(typename Container::value_type) && container.type() == typeid(Container)))
        return std::any{};

    auto const value_{std::any_cast<typename Container::value_type>(value)};
    auto container_{std::any_cast<Container>(container)};

    container_.insert(container_.end(), value_);

    return container_;
}

std::any hodel::insert(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const value{args[0]};
    auto const container{args[1]};

    if (auto r = ::insert<IntegerSet>(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<IntegerType> >(value, container); r.has_value()) return r;
    if (auto r = ::insert<ObjectType>(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<Cell> >(value, container); r.has_value()) return r;
    if (auto r = ::insert<Objects>(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<ObjectType> >(value, container); r.has_value()) return r;
    if (auto r = ::insert<IndicesType>(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<IntegerTuple> >(value, container); r.has_value()) return r;
    if (auto r = ::insert<IndicesSet>(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<IndicesType> >(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<IntegerType> >(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<GridType> >(value, container); r.has_value()) return r;
    if (auto r = ::insert<GridType>(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<std::function<std::any(std::vector<std::any> const&)> > >(value, container); r.has_value()) return r;
    if (auto r = ::insert<std::vector<Boolean> >(value, container); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

template <typename Container>
std::any remove(std::any const& value, std::any const& container)
{
    if (!(value.type() == typeid(typename Container::value_type) && container.type() == typeid(Container)))
        return std::any{};

    auto const value_{std::any_cast<typename Container::value_type>(value)};
    auto container_{std::any_cast<Container>(container)};
    auto const it{std::find(container_.begin(), container_.end(), value_)};

    if (it != container_.end())
        container_.erase(it);

    return container_;
}

std::any hodel::remove(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const value{args[0]};
    auto const container{args[1]};

    if (auto r = ::remove<IntegerSet>(value, container); r.has_value()) return r;
    if (auto r = ::remove<std::vector<IntegerType> >(value, container); r.has_value()) return r;
    if (auto r = ::remove<ObjectType>(value, container); r.has_value()) return r;
    if (auto r = ::remove<std::vector<Cell> >(value, container); r.has_value()) return r;
    if (auto r = ::remove<Objects>(value, container); r.has_value()) return r;
    if (auto r = ::remove<std::vector<ObjectType> >(value, container); r.has_value()) return r;
    if (auto r = ::remove<IndicesType>(value, container); r.has_value()) return r;
    if (auto r = ::remove<std::vector<IntegerTuple> >(value, container); r.has_value()) return r;
    if (auto r = ::remove<IndicesSet>(value, container); r.has_value()) return r;
    if (auto r = ::remove<std::vector<IndicesType> >(value, container); r.has_value()) return r;
    if (auto r = ::remove<std::vector<IntegerType> >(value, container); r.has_value()) return r;
    if (auto r = ::remove<std::vector<GridType> >(value, container); r.has_value()) return r;
    if (auto r = ::remove<GridType>(value, container); r.has_value()) return r;
    if (auto r = ::remove<std::vector<Boolean> >(value, container); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::other(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const value{args[1]};

    return first({remove({value, container})});
}

std::any hodel::interval(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const start{args[0]};
    auto const stop{args[1]};
    auto const step{args[2]};

    if (start.type() == typeid(IntegerType) && stop.type() == typeid(IntegerType) && step.type() == typeid(IntegerType))
    {
        auto start_{std::any_cast<IntegerType>(start)};
        auto const stop_{std::any_cast<IntegerType>(stop)};
        auto const step_{std::any_cast<IntegerType>(step)};
        std::vector<IntegerType> result;

        if ((step_ >= 0 && stop_ < start_) || (step_ <= 0 && stop_ > start_))
            throw std::runtime_error{"Wrong value"};

        if (std::abs(start_ - stop_) > 100)
            throw std::runtime_error{"Wrong value"};

        for (; step_ >= 0 ? start_ < stop_ : start_ > stop_; start_ += step_)
            result.emplace_back(start_);

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::astuple(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(IntegerType) && b.type() == typeid(IntegerType))
        return IntegerTuple{std::make_pair<IntegerType, IntegerType>(std::any_cast<IntegerType>(a), std::any_cast<IntegerType>(b))};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::product(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(std::vector<IntegerType>) && b.type() == typeid(std::vector<IntegerTuple>))
    {
        auto const a_{std::any_cast<std::vector<IntegerType> >(a)};
        auto const b_{std::any_cast<std::vector<IntegerTuple> >(b)};

        ObjectType result;

        for (auto const& i : a_)
        {
            for (auto const& j : b_)
                result.emplace(i, j);
        }

        return result;
    }
    else if (a.type() == typeid(std::vector<IntegerType>) && b.type() == typeid(std::vector<IntegerType>))
    {
        auto const a_{std::any_cast<std::vector<IntegerType> >(a)};
        auto const b_{std::any_cast<std::vector<IntegerType> >(b)};

        IndicesType result;

        for (auto const& i : a_)
        {
            for (auto const& j : b_)
                result.emplace(i, j);
        }

        return result;
    }
    //TODO: add other cases

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::pair(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(IntegerType) && b.type() == typeid(IntegerType))
        return IntegerTuple{std::any_cast<IntegerType>(a), std::any_cast<IntegerType>(b)};
    else if (a.type() == typeid(IntegerType) && b.type() == typeid(IntegerTuple))
        return Cell{std::any_cast<IntegerType>(a), std::any_cast<IntegerTuple>(b)};
    else if (a.type() == typeid(std::vector<IntegerType>) && b.type() == typeid(std::vector<IntegerType>))
        return GridType{std::any_cast<std::vector<IntegerType> >(a), std::any_cast<std::vector<IntegerType> >(b)};
    else if (a.type() == typeid(IntegerTuple) && b.type() == typeid(IntegerTuple))
        return std::vector<IntegerTuple>{std::any_cast<IntegerTuple>(a), std::any_cast<IntegerTuple>(b)};
    else if (a.type() == typeid(GridType) && b.type() == typeid(GridType))
        return std::vector<GridType>{std::any_cast<GridType>(a), std::any_cast<GridType>(b)};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::branch(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const condition{args[0]};
    auto const a{args[1]};
    auto const b{args[2]};

    if (condition.type() == typeid(Boolean))
    {
        auto const condition_{std::any_cast<Boolean>(condition)};

        return condition_ ? a : b;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::compose(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const outer{args[0]};
    auto const inner{args[1]};

    if (outer.type() == typeid(std::function<std::any(std::vector<std::any> const&)>)
        && inner.type() == typeid(std::function<std::any(std::vector<std::any> const&)>))
    {
        auto const outer_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(outer)};
        auto const inner_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(inner)};

        return std::function<std::any(std::vector<std::any> const&)>{[outer_, inner_] (std::vector<std::any> const& args) -> std::any
        {
            return outer_({inner_(args)});
        }};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::chain(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const h{args[0]};
    auto const g{args[1]};
    auto const f{args[2]};

    if (h.type() == typeid(std::function<std::any(std::vector<std::any> const&)>)
        && g.type() == typeid(std::function<std::any(std::vector<std::any> const&)>)
        && f.type() == typeid(std::function<std::any(std::vector<std::any> const&)>))
    {
        auto const h_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(h)};
        auto const g_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(g)};
        auto const f_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(f)};

        return std::function<std::any(std::vector<std::any> const&)>{[h_, g_, f_] (std::vector<std::any> const& args) -> std::any
        {
            return h_({g_({f_(args)})});
        }};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::matcher(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const target{args[1]};

    if (function.type() == typeid(std::function<std::any(std::vector<std::any> const&)>))
    {
        auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(function)};

        return std::function<std::any(std::vector<std::any> const&)>{[f, target] (std::vector<std::any> const& args) -> std::any
        {
            return equality({f(args), target});
        }};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::rbind(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const fixed{args[1]};

    if (function.type() == typeid(std::function<std::any(std::vector<std::any> const&)>))
    {
        auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(function)};

        return std::function<std::any(std::vector<std::any> const&)>{[f, fixed] (std::vector<std::any> const& args) -> std::any
        {
            auto new_args = args;
            new_args.emplace_back(fixed);

            return f(new_args);
        }};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::lbind(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const fixed{args[1]};

    if (function.type() == typeid(std::function<std::any(std::vector<std::any> const&)>))
    {
        auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(function)};

        return std::function<std::any(std::vector<std::any> const&)>{[f, fixed] (std::vector<std::any> const& args) -> std::any
        {
            std::vector<std::any> new_args{fixed};
            new_args.insert(new_args.end(), args.begin(), args.end());

            return f(new_args);
        }};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::power(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const n{args[1]};

    if (function.type() == typeid(std::function<std::any(std::vector<std::any> const&)>) && n.type() == typeid(IntegerType))
    {
        auto const n_{std::any_cast<IntegerType>(n)};

        if (n_ <= 0 || n_ > 10)
            throw std::runtime_error{"Wrong value"};

        if (n_ == 1)
            return function;

        return compose({function, power({function, n_ - 1})});
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::fork(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const outer{args[0]};
    auto const a{args[1]};
    auto const b{args[1]};

    if (outer.type() == typeid(std::function<std::any(std::vector<std::any> const&)>)
        && a.type() == typeid(std::function<std::any(std::vector<std::any> const&)>)
        && b.type() == typeid(std::function<std::any(std::vector<std::any> const&)>))
    {
        auto const outer_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(outer)};
        auto const a_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(a)};
        auto const b_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(b)};

        return std::function<std::any(std::vector<std::any> const&)>{[outer_, a_, b_] (std::vector<std::any> const& args) -> std::any
        {
            return outer_({a_(args), b_(args)});
        }};
    }

    throw std::runtime_error{"Wrong value"};
}

template <typename T, typename S = typename T::value_type>
static std::any apply(std::function<std::any(std::vector<std::any> const&)> const& function, std::any const& container)
{
    if (container.type() != typeid(T))
        return std::any{};

    auto const container_{std::any_cast<T>(container)};

    std::vector<S> values;
    values.reserve(container_.size());

    try
    {
        for (auto const& v : container_)
            values.emplace_back(std::any_cast<S>(function({v})));
    }
    catch (std::exception const&)
    {
        return std::any{};
    }

    return values;
}

std::any hodel::apply(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const container{args[1]};

    if (function.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    if (container.type() == typeid(IntegerTuple))
    {
        auto const container_{std::any_cast<IntegerTuple>(container)};
        std::vector<IntegerType> const v{container_.first, container_.second};

        return apply({function, v});
    }

    auto const function_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(function)};

    if (auto r = ::apply<std::vector<Boolean> >(function_, container); r.has_value()) return r;
    if (auto r = ::apply<std::vector<GridType>, Boolean>(function_, container); r.has_value()) return r;
    if (auto r = ::apply<std::vector<IntegerType>, IntegerType>(function_, container); r.has_value()) return r;
    if (auto r = ::apply<std::vector<GridType>, IntegerType>(function_, container); r.has_value()) return r;
    if (auto r = ::apply<Objects, IntegerType>(function_, container); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

template <typename T>
std::any rapply(std::vector<std::function<std::any(std::vector<std::any> const&)> > const& functions, std::any const& value)
{
    if (value.type() != typeid(T))
        return std::any{};

    std::vector<T> result;

    try
    {
        for (auto const& function : functions)
            result.emplace_back(std::any_cast<T>(function({value})));
    }
    catch (std::exception const&)
    {
        return std::any{};
    }

    return result;
}

std::any hodel::rapply(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const functions{args[0]};
    auto const value{args[1]};

    if (functions.type() != typeid(std::vector<std::function<std::any(std::vector<std::any> const&)> >))
        throw std::runtime_error{"Wrong value"};

    auto const functions_{std::any_cast<std::vector<std::function<std::any(std::vector<std::any> const&)> > >(functions)};

    if (auto r = ::rapply<Boolean>(functions_, value); r.has_value()) return r;
    if (auto r = ::rapply<IntegerType>(functions_, value); r.has_value()) return r;
    if (auto r = ::rapply<IntegerTuple>(functions_, value); r.has_value()) return r;
    if (auto r = ::rapply<GridType>(functions_, value); r.has_value()) return r;
    if (auto r = ::rapply<IndicesSet>(functions_, value); r.has_value()) return r;
    if (auto r = ::rapply<ObjectType>(functions_, value); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::mapply(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const container{args[1]};

    return merge({apply({function, container})});
}

std::any hodel::papply(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const a{args[1]};
    auto const b{args[2]};

    if (function.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    auto const function_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(function)};

    if (a.type() == typeid(std::vector<IntegerType>) && b.type() == typeid(std::vector<IntegerTuple>))
    {
        auto const a_{std::any_cast<std::vector<IntegerType> >(a)};
        auto const b_{std::any_cast<std::vector<IntegerTuple> >(b)};

        if (a_.size() != b_.size() || a_.empty())
            throw std::runtime_error{"Wrong value"};

        ObjectType result;

        for (size_t i{0}; i < a_.size(); ++i)
            result.emplace(a_[i], b_[i]);

        return result;
    }
    else if (a.type() == typeid(std::vector<IntegerType>) && b.type() == typeid(std::vector<IntegerType>))
    {
        auto const a_{std::any_cast<std::vector<IntegerType> >(a)};
        auto const b_{std::any_cast<std::vector<IntegerType> >(b)};

        if (a_.size() != b_.size() || a_.empty())
            throw std::runtime_error{"Wrong value"};

        IndicesType result;

        for (size_t i{0}; i < a_.size(); ++i)
            result.emplace(a_[i], b_[i]);

        return result;
    }
    //TODO: add other cases?

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::mpapply(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const a{args[1]};
    auto const b{args[2]};

    return merge({papply({function, a, b})});
}

template <typename T, typename S, typename U>
std::any prapply(std::function<std::any(std::vector<std::any> const&)> const& function, std::any const& a, std::any const& b)
{
    if (!(a.type() == typeid(T) && b.type() == typeid(S)))
        return std::any{};

    auto const a_{std::any_cast<T>(a)};
    auto const b_{std::any_cast<S>(b)};

    if (a_.size() != b_.size())
        return std::any{};

    std::vector<U> result;
    result.reserve(a_.size());

    auto itA{a_.begin()};
    auto itB{b_.begin()};

    try
    {
        for (; itA != a_.end() && itB != b_.end(); ++itA, ++itB)
            result.emplace_back(std::any_cast<U>(function({*itA, *itB})));
    }
    catch (std::exception const&)
    {
        return std::any{};
    }
    
    return result;
}

std::any hodel::prapply(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const a{args[1]};
    auto const b{args[2]};

    if (function.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    auto const function_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(function)};

    if (auto r = ::prapply<std::vector<IndicesType>, std::vector<IndicesType>, Boolean>(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<IndicesType>, std::vector<IndicesType>, IntegerType>(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<ObjectType>, std::vector<ObjectType>, Boolean>(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<ObjectType>, std::vector<ObjectType>, IntegerType>(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&)> >, std::vector<Boolean>,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&) > >, std::vector<IntegerType>,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&) > >, std::vector<IntegerTuple>,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&) > >, GridType,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&) > >, std::vector<GridType>,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&) > >, ObjectType,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&) > >, Objects,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&) > >, IndicesType,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    if (auto r = ::prapply<std::vector<std::function<std::any(std::vector<std::any> const&) > >, IndicesSet,
                           std::function<std::any(std::vector<std::any> const&)> >(function_, a, b); r.has_value()) return r;
    //TODO: add other cases?

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::mostcolor(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const element{args[0]};

    if (element.type() == typeid(ObjectType))
        return mostcolor({Element{std::any_cast<ObjectType>(element)}});
    else if (element.type() == typeid(GridType))
        return mostcolor({Element{std::any_cast<GridType>(element)}});
    else if (element.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(element)};

        if (std::holds_alternative<GridType>(piece))
            return leastcolor({Element{std::get<GridType>(piece)}});
    }

    if (element.type() == typeid(Element))
    {
        auto const element_{std::any_cast<Element>(element)};

        auto const counts{colorCounts(element_)};

        auto const it = std::max_element(
            counts.begin(),
            counts.end(),
            [] (auto const& a, auto const& b)
            {
                return a.second < b.second;
            });

        if (it == counts.end())
            throw std::runtime_error{"Wrong value"};

        return it->first;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::leastcolor(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const element{args[0]};

    if (element.type() == typeid(ObjectType))
        return leastcolor({Element{std::any_cast<ObjectType>(element)}});
    else if (element.type() == typeid(GridType))
        return leastcolor({Element{std::any_cast<GridType>(element)}});
    else if (element.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(element)};

        if (std::holds_alternative<GridType>(piece))
            return leastcolor({Element{std::get<GridType>(piece)}});
    }

    if (element.type() == typeid(Element))
    {
        auto const element_{std::any_cast<Element>(element)};

        auto const counts{colorCounts(element_)};

        auto const it = std::min_element(
            counts.begin(),
            counts.end(),
            [] (auto const& a, auto const& b)
            {
                return a.second < b.second;
            });

        if (it == counts.end())
            throw std::runtime_error{"Wrong value"};

        return it->first;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::height(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
    {
        auto const piece_{std::any_cast<Piece>(piece)};

        if (std::holds_alternative<GridType>(piece_))
        {
            auto const grid{std::get<GridType>(piece_)};

            if (grid.size() == 0)
                return IntegerType{0};

            return static_cast<IntegerType>(grid.size());
        }
        else if (std::holds_alternative<Patch>(piece_))
        {
            auto const lm{std::any_cast<IntegerType>(lowermost({std::get<Patch>(piece_)}))};
            auto const um{std::any_cast<IntegerType>(uppermost({std::get<Patch>(piece_)}))};

            return IntegerType{lm - um + 1};
        }
    }
    else if (piece.type() == typeid(GridType))
        return height({Piece{std::any_cast<GridType>(piece)}});
    else if (piece.type() == typeid(Patch))
        return height({Piece{std::any_cast<Patch>(piece)}});
    else if (piece.type() == typeid(ObjectType))
    {
        auto const object{std::any_cast<ObjectType>(piece)};

        auto const lm{std::any_cast<IntegerType>(rightmost({object}))};
        auto const um{std::any_cast<IntegerType>(leftmost({object}))};

        return IntegerType{lm - um + 1};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::width(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
    {
        auto const piece_{std::any_cast<Piece>(piece)};

        if (std::holds_alternative<GridType>(piece_))
        {
            auto const grid{std::get<GridType>(piece_)};

            if (grid.size() == 0)
                return IntegerType{0};

            return static_cast<IntegerType>(grid.at(0).size());
        }
        else if (std::holds_alternative<Patch>(piece_))
        {
            auto const rm{std::any_cast<IntegerType>(rightmost({std::get<Patch>(piece_)}))};
            auto const lm{std::any_cast<IntegerType>(leftmost({std::get<Patch>(piece_)}))};

            return IntegerType{rm - lm + 1};
        }
    }
    else if (piece.type() == typeid(GridType))
        return width({Piece{std::any_cast<GridType>(piece)}});
    else if (piece.type() == typeid(Patch))
        return width({Piece{std::any_cast<Patch>(piece)}});
    else if (piece.type() == typeid(ObjectType))
    {
        auto const object{std::any_cast<ObjectType>(piece)};

        auto const rm{std::any_cast<IntegerType>(rightmost({object}))};
        auto const lm{std::any_cast<IntegerType>(leftmost({object}))};

        return IntegerType{rm - lm + 1};
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::shape(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(GridType))
        return shape({Piece(std::any_cast<GridType>(piece))});
    else if (piece.type() == typeid(Patch))
        return shape({Piece(std::any_cast<Patch>(piece))});

    if (piece.type() == typeid(Piece) || piece.type() == typeid(ObjectType))
        return IntegerTuple{std::any_cast<IntegerType>(height(args)), std::any_cast<IntegerType>(width(args))};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::portrait(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(GridType))
        return portrait({Piece(std::any_cast<GridType>(piece))});
    else if (piece.type() == typeid(Patch))
        return portrait({Piece(std::any_cast<Patch>(piece))});

    if (piece.type() == typeid(Piece) || piece.type() == typeid(ObjectType))
    {
        auto const h{std::any_cast<IntegerType>(height(args))};
        auto const w{std::any_cast<IntegerType>(width(args))};

        return static_cast<Boolean>(h > w);
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::colorcount(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const element{args[0]};
    auto const value{args[1]};

    if (element.type() == typeid(GridType))
        return colorcount({Element(std::any_cast<GridType>(element)), value});
    else if (element.type() == typeid(ObjectType))
        return colorcount({Element(std::any_cast<ObjectType>(element)), value});

    if (element.type() == typeid(Element) && value.type() == typeid(IntegerType))
    {
        auto const element_{std::any_cast<Element>(element)};
        auto const value_{std::any_cast<IntegerType>(value)};

        IntegerType count = 0;

        if (std::holds_alternative<GridType>(element_))
        {
            auto const grid{std::get<GridType>(element_)};

            for (auto const& row : grid)
                count += static_cast<IntegerType>(std::count(row.begin(), row.end(), value_));
        }
        else
        {
            auto const& object{std::get<ObjectType>(element_)};

            for (auto const& [color, position] : object)
            {
                if (color == value_)
                    ++count;
            }
        }

        return count;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::colorfilter(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const objs{args[0]};
    auto const value{args[1]};

    if (objs.type() == typeid(Objects) && value.type() == typeid(IntegerType))
    {
        auto const objs_{std::any_cast<Objects>(objs)};
        auto const value_{std::any_cast<IntegerType>(value)};

        Objects result;

        for (auto const& obj : objs_)
        {
            if (!obj.empty() && obj.begin()->first == value_)
                result.emplace(obj);
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

template <typename ContainerContainer>
std::any sizefilter(std::any const& container, hodel::IntegerType n)
{
    if (container.type() != typeid(ContainerContainer))
        return std::any{};

    auto const container_{std::any_cast<ContainerContainer>(container)};

    ContainerContainer result;

    for (auto const& v : container_)
    {
        if (v.size() == n)
            result.insert(result.end(), v);
    }

    return result;
}

std::any hodel::sizefilter(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};
    auto const n{args[1]};

    if (n.type() != typeid(IntegerType))
        throw std::runtime_error{"Wrong value"};

    auto const n_{std::any_cast<IntegerType>(n)};

    if (n_ < 0)
        throw std::runtime_error{"Wrong value"};

    if (container.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(container)};

        if (std::holds_alternative<GridType>(piece))
            return sizefilter({std::get<GridType>(piece), n});
    }

    if (auto r = ::sizefilter<Objects>(container, n_); r.has_value()) return r;
    if (auto r = ::sizefilter<IndicesSet>(container, n_); r.has_value()) return r;
    if (auto r = ::sizefilter<GridType>(container, n_); r.has_value()) return r;
    if (auto r = ::sizefilter<std::vector<GridType> >(container, n_); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::asindices(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return asindices({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        IndicesType indices;

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        for (IntegerType i{0}; i < static_cast<IntegerType>(grid_.size()); ++i)
        {
            for (IntegerType j{0}; j < static_cast<IntegerType>(grid_.at(0).size()); ++j)
                indices.emplace(i, j);
        }

        return indices;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::ofcolor(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const value{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return ofcolor({std::get<GridType>(piece), value});
    }

    if (grid.type() == typeid(GridType) && value.type() == typeid(IntegerType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const value_{std::any_cast<IntegerType>(value)};

        IndicesType indices;

        for (IntegerType i{0}; i < static_cast<IntegerType>(grid_.size()); ++i)
        {
            for (IntegerType j{0}; j < static_cast<IntegerType>(grid_[i].size()); ++j)
            {
                if (grid_[i][j] == value_)
                    indices.emplace(i, j);
            }
        }

        return indices;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::ulcorner(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        if (std::holds_alternative<ObjectType>(patch_))
            return ulcorner({Patch{std::any_cast<IndicesType>(toindices(args))}});
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};
            auto min_y = std::numeric_limits<IntegerType>::max();
            auto min_x = std::numeric_limits<IntegerType>::max();

            for (auto const& [y, x] : indices)
            {
                min_y = std::min(min_y, y);
                min_x = std::min(min_x, x);
            }

            return IntegerTuple{min_y, min_x};
        }
    }
    else if (patch.type() == typeid(ObjectType))
        return ulcorner({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return ulcorner({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::urcorner(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        if (std::holds_alternative<ObjectType>(patch_))
            return urcorner({Patch{std::any_cast<IndicesType>(toindices(args))}});
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};
            auto min_y = std::numeric_limits<IntegerType>::max();
            auto max_x = std::numeric_limits<IntegerType>::lowest();

            for (auto const& [y, x] : indices)
            {

                min_y = std::min(min_y, y);
                max_x = std::max(max_x, x);
            }

            return IntegerTuple{min_y, max_x};
        }
    }
    else if (patch.type() == typeid(ObjectType))
        return urcorner({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return urcorner({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::llcorner(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        if (std::holds_alternative<ObjectType>(patch_))
            return llcorner({Patch{std::any_cast<IndicesType>(toindices(args))}});
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};
            auto max_y = std::numeric_limits<IntegerType>::lowest();
            auto min_x = std::numeric_limits<IntegerType>::max();

            for (auto const& [y, x] : indices)
            {
                max_y = std::max(max_y, y);
                min_x = std::min(min_x, x);
            }

            return IntegerTuple{max_y, min_x};
        }
    }
    else if (patch.type() == typeid(ObjectType))
        return llcorner({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return llcorner({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::lrcorner(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        if (std::holds_alternative<ObjectType>(patch_))
            return lrcorner({Patch{std::any_cast<IndicesType>(toindices(args))}});
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};
            auto max_y = std::numeric_limits<IntegerType>::lowest();
            auto max_x = std::numeric_limits<IntegerType>::lowest();

            for (auto const& [y, x] : indices)
            {
                max_y = std::max(max_y, y);
                max_x = std::max(max_x, x);
            }

            return IntegerTuple{max_y, max_x};
        }
    }
    else if (patch.type() == typeid(ObjectType))
        return lrcorner({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return lrcorner({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::crop(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const start{args[1]};
    auto const dims{args[2]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return crop({std::get<GridType>(piece), start, dims});
    }

    if (grid.type() == typeid(GridType) && start.type() == typeid(IntegerTuple) && dims.type() == typeid(IntegerTuple))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const start_{std::any_cast<IntegerTuple>(start)};
        auto const dims_{std::any_cast<IntegerTuple>(dims)};

        if (dims_.first < 0 || dims_.second < 0 || start_.first < 0 || start_.second < 0 || start_.first + dims_.first > grid_.size() || start_.second + dims_.second > grid_.at(0).size())
            throw std::runtime_error{"Wrong value"};

        GridType result;

        try
        {
            for (size_t i{0}; i < dims_.first; ++i)
            {
                std::vector<IntegerType> row;

                for (size_t j{0}; j < dims_.second; ++j)
                    row.emplace_back(grid_.at(start_.first + i).at(start_.second + j));

                result.emplace_back(row);
            }
        }
        catch (const std::exception&)
        {
            throw std::runtime_error{"Wrong value"};
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::toindices(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        if (std::holds_alternative<IndicesType>(patch_))
            return std::get<IndicesType>(patch_);

        auto const& obj = std::get<ObjectType>(patch_);

        if (obj.empty())
            throw std::runtime_error{"Wrong value"};

        IndicesType result;

        for (auto const& cell : obj)
            result.insert(cell.second);

        return result;
    }
    else if (patch.type() == typeid(ObjectType))
        return toindices({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return toindices({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::recolor(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const value{args[0]};
    auto const patch{args[1]};

    if (patch.type() == typeid(ObjectType))
        return recolor({value, Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return recolor({value, Patch{std::any_cast<IndicesType>(patch)}});

    if (value.type() == typeid(IntegerType) && patch.type() == typeid(Patch))
    {
        auto const value_{std::any_cast<IntegerType>(value)};

        try
        {
            ObjectType ObjectType;

            for (auto const& index : std::any_cast<IndicesType>(toindices({patch})))
                ObjectType.emplace(value_, index);

            return ObjectType;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::shift(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};
    auto const directions{args[1]};

    if (patch.type() == typeid(Patch) && directions.type() == typeid(IntegerTuple))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
        auto const directions_{std::any_cast<IntegerTuple>(directions)};

        if (std::holds_alternative<ObjectType>(patch_) && std::get<ObjectType>(patch_).empty())
            return patch;

        if (std::holds_alternative<IndicesType>(patch_) && std::get<IndicesType>(patch_).empty())
            return patch;

        auto const& [di, dj] = directions_;

        if (std::holds_alternative<ObjectType>(patch_))
        {
            auto const& obj = std::get<ObjectType>(patch_);
            ObjectType result;

            for (auto const& [value, pos] : obj)
            {
                auto const& [i, j] = pos;

                result.insert({value, {i + di, j + dj}});
            }

            return result;
        }

        auto const& indices = std::get<IndicesType>(patch_);
        IndicesType result;

        for (auto const& [i, j] : indices)
            result.insert({i + di, j + dj});

        return result;
    }
    else if (patch.type() == typeid(ObjectType))
        return shift({Patch{std::any_cast<ObjectType>(patch)}, directions});
    else if (patch.type() == typeid(IndicesType))
        return shift({Patch{std::any_cast<IndicesType>(patch)}, directions});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::normalize(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        if (std::holds_alternative<ObjectType>(patch_))
        {
            auto const& obj = std::get<ObjectType>(patch_);

            if (obj.empty())
                return obj;

            try
            {
                return shift({obj, IntegerTuple{-std::any_cast<IntegerType>(uppermost({obj})), -std::any_cast<IntegerType>(leftmost({obj}))}});
        
            }
            catch (std::exception const&)
            {
                throw std::runtime_error{"Wrong value"};
            }
        }
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};

            if (indices.empty())
                throw std::runtime_error{"Wrong value"};

            try
            {
                return shift({indices, IntegerTuple{-std::any_cast<IntegerType>(uppermost({indices})), -std::any_cast<IntegerType>(leftmost({indices}))}});
        
            }
            catch (std::exception const&)
            {
                throw std::runtime_error{"Wrong value"};
            }
        }
    }
    else if (patch.type() == typeid(ObjectType))
        return normalize({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return normalize({Patch{std::any_cast<IndicesType>(patch)}});
    
    throw std::runtime_error{"Wrong value"};
}

std::any hodel::dneighbors(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const loc{args[0]};

    if (loc.type() == typeid(IntegerTuple))
    {
        auto const loc_{std::any_cast<IntegerTuple>(loc)};

        return IndicesType{
            {loc_.first - 1, loc_.second},
            {loc_.first + 1, loc_.second},
            {loc_.first,     loc_.second - 1},
            {loc_.first,     loc_.second + 1}
        };
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::ineighbors(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const loc{args[0]};

    if (loc.type() == typeid(IntegerTuple))
    {
        auto const loc_{std::any_cast<IntegerTuple>(loc)};

        return IndicesType{
            {loc_.first - 1, loc_.second - 1},
            {loc_.first - 1, loc_.second + 1},
            {loc_.first + 1, loc_.second - 1},
            {loc_.first + 1, loc_.second + 1}
        };
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::neighbors(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const loc{args[0]};

    if (loc.type() == typeid(IntegerTuple))
    {
        try
        {
            auto result{std::any_cast<IndicesType>(dneighbors({loc}))};
            auto const diagonal{std::any_cast<IndicesType>(ineighbors({loc}))};

            result.insert(diagonal.begin(), diagonal.end());

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::objects(std::vector<std::any> const& args)
{
    if (args.size() != 4)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const univalued{args[1]};
    auto const diagonal{args[2]};
    auto const without_bg{args[3]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return objects({std::get<GridType>(piece), univalued, diagonal, without_bg});
    }

    if (univalued.type() == typeid(Boolean) && diagonal.type() == typeid(Boolean) && without_bg.type() == typeid(Boolean))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const univalued_{std::any_cast<Boolean>(univalued)};
        auto const diagonal_{std::any_cast<Boolean>(diagonal)};
        auto const without_bg_{std::any_cast<Boolean>(without_bg)};

        Objects objs;

        if (grid_.empty())
            return objs;

        try
        {
            auto const h = grid_.size();
            auto const w = grid_.at(0).size();

            auto const bg = without_bg_ ? std::any_cast<IntegerType>(mostcolor({grid})) : IntegerType{-1};

            IndicesType occupied;
            IndicesType unvisited = std::any_cast<IndicesType>(asindices({grid}));

            for (auto const& loc : unvisited)
            {
                if (occupied.count(loc))
                    continue;

                auto const val = grid_.at(loc.first).at(loc.second);

                if (without_bg_ && val == bg)
                    continue;

                ObjectType obj;
                IndicesType candidates{loc};

                while (!candidates.empty())
                {
                    IndicesType neighborhood;

                    for (auto const& cand : candidates)
                    {
                        if (occupied.count(cand))
                            continue;

                        auto const v = grid_.at(cand.first).at(cand.second);

                        if ((univalued_ && v == val) ||
                            (!univalued_ && (!without_bg_ || v != bg)))
                        {
                            obj.emplace(v, cand);
                            occupied.insert(cand);

                            auto const neigh = std::any_cast<IndicesType>(diagonal_ ? neighbors({cand}) : dneighbors({cand}));

                            for (auto const& p : neigh)
                            {
                                auto const i = p.first;
                                auto const j = p.second;

                                if (0 <= i && i < h && 0 <= j && j < w)
                                    neighborhood.insert(p);
                            }
                        }
                    }

                    candidates.clear();

                    for (const auto& p : neighborhood)
                    {
                        if (!occupied.count(p))
                            candidates.insert(p);
                    }
                }

                objs.insert(std::move(obj));
            }

            return objs;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::partition(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return partition({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        std::map<IntegerType, ObjectType> objectsByColor;

        try
        {
            for (size_t i = 0; i < grid_.size(); ++i)
            {
                for (size_t j = 0; j < grid_.at(i).size(); ++j)
                {
                    auto const color = grid_.at(i).at(j);
                    objectsByColor[color].emplace(color, IntegerTuple{i, j});
                }
            }

            Objects result;

            for (auto& [color, ObjectType] : objectsByColor)
            {
                result.insert(std::move(ObjectType));
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::fgpartition(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return partition({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        std::map<IntegerType, ObjectType> objectsByColor;

        try
        {
            for (size_t i = 0; i < grid_.size(); ++i)
            {
                for (size_t j = 0; j < grid_.at(i).size(); ++j)
                {
                    auto const color = grid_.at(i).at(j);
                    objectsByColor[color].emplace(color, IntegerTuple{i, j});
                }
            }

            Objects result;
            auto const bg{std::any_cast<IntegerType>(mostcolor({grid_}))};

            for (auto& [color, ObjectType] : objectsByColor)
            {
                if (color != bg)
                    result.insert(std::move(ObjectType));
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::uppermost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
        auto const indices = std::any_cast<IndicesType>(toindices(args));
        auto result = std::numeric_limits<IntegerType>::max();

        for (auto const& [i, j] : indices)
            result = std::min(result, i);

        return result;
    }
    else if (patch.type() == typeid(ObjectType))
        return uppermost({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return uppermost({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::lowermost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
        auto const indices = std::any_cast<IndicesType>(toindices(args));
        auto result = std::numeric_limits<IntegerType>::min();

        for (auto const& [i, j] : indices)
            result = std::max(result, i);

        return result;
    }
    else if (patch.type() == typeid(ObjectType))
        return lowermost({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return lowermost({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::leftmost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
        auto const indices = std::any_cast<IndicesType>(toindices(args));
        auto result = std::numeric_limits<IntegerType>::max();

        for (auto const& [i, j] : indices)
            result = std::min(result, j);

        return result;
    }
    else if (patch.type() == typeid(ObjectType))
        return leftmost({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return leftmost({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::rightmost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
        auto const indices = std::any_cast<IndicesType>(toindices(args));
        auto result = std::numeric_limits<IntegerType>::min();

        for (auto const& [i, j] : indices)
            result = std::max(result, j);

        return result;
    }
    else if (patch.type() == typeid(ObjectType))
        return rightmost({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return rightmost({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::square(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
    {
        try
        {
            auto const piece_{std::any_cast<Piece>(piece)};

            if (std::holds_alternative<GridType>(piece_))
            {
                auto const grid{std::get<GridType>(piece_)};

                try
                {
                    return Boolean{grid.size() == grid.at(0).size()};
                }
                catch (std::exception const&)
                {
                    throw std::runtime_error{"Wrong value"};
                }
            }
            else
            {
                auto const h{std::any_cast<IntegerType>(height(args))};
                auto const w{std::any_cast<IntegerType>(width(args))};
                auto const patch{std::get<Patch>(piece_)};
                auto const l{static_cast<IntegerType>(std::holds_alternative<ObjectType>(patch) ? std::get<ObjectType>(patch).size() : std::get<IndicesType>(patch).size())};

                return Boolean{h * w == l and h == w};
            }
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }
    else if (piece.type() == typeid(GridType))
        return square({Piece{std::any_cast<GridType>(piece)}});
    else if (piece.type() == typeid(Patch))
        return square({Piece{std::any_cast<Patch>(piece)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::vline(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        try
        {
            auto const h{std::any_cast<IntegerType>(height(args))};
            auto const w{std::any_cast<IntegerType>(width(args))};
            auto const patch_{std::any_cast<Patch>(patch)};
            auto const l{static_cast<IntegerType>(std::holds_alternative<ObjectType>(patch_) ? std::get<ObjectType>(patch_).size() : std::get<IndicesType>(patch_).size())};

            return Boolean{h == l && w == 1};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }
    else if (patch.type() == typeid(ObjectType))
        return vline({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return vline({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hline(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        try
        {
            auto const h{std::any_cast<IntegerType>(height(args))};
            auto const w{std::any_cast<IntegerType>(width(args))};
            auto const patch_{std::any_cast<Patch>(patch)};
            auto const l{static_cast<IntegerType>(std::holds_alternative<ObjectType>(patch_) ? std::get<ObjectType>(patch_).size() : std::get<IndicesType>(patch_).size())};

            return Boolean{w == l && h == 1};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }
    else if (patch.type() == typeid(ObjectType))
        return hline({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return hline({Patch{std::any_cast<IndicesType>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hmatching(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};

    bool recall{false};

    if (a.type() == typeid(ObjectType))
    {
        a = Patch{std::any_cast<ObjectType>(a)};
        recall = true;
    }
    else if (a.type() == typeid(IndicesType))
    {
        a = Patch{std::any_cast<IndicesType>(a)};
        recall = true;
    }

    if (b.type() == typeid(ObjectType))
    {
        b = Patch{std::any_cast<ObjectType>(b)};
        recall = true;
    }
    else if (b.type() == typeid(IndicesType))
    {
        b = Patch{std::any_cast<IndicesType>(b)};
        recall = true;
    }

    if (recall)
        return hmatching({a, b});

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        try
        {
            std::set<IntegerType> rows;

            for (auto const& [i, j] : std::any_cast<IndicesType>(toindices({a})))
                rows.insert(i);

            for (auto const& [i, j] : std::any_cast<IndicesType>(toindices({b})))
            {
                if (rows.count(i))
                    return Boolean{true};
            }

            return Boolean{false};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::vmatching(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};

    bool recall{false};

    if (a.type() == typeid(ObjectType))
    {
        a = Patch{std::any_cast<ObjectType>(a)};
        recall = true;
    }
    else if (a.type() == typeid(IndicesType))
    {
        a = Patch{std::any_cast<IndicesType>(a)};
        recall = true;
    }

    if (b.type() == typeid(ObjectType))
    {
        b = Patch{std::any_cast<ObjectType>(b)};
        recall = true;
    }
    else if (b.type() == typeid(IndicesType))
    {
        b = Patch{std::any_cast<IndicesType>(b)};
        recall = true;
    }

    if (recall)
        return vmatching({a, b});

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        try
        {
            std::set<IntegerType> cols;

            for (auto const& [i, j] : std::any_cast<IndicesType>(toindices({a})))
                cols.insert(j);

            for (auto const& [i, j] : std::any_cast<IndicesType>(toindices({b})))
            {
                if (cols.count(j))
                    return Boolean{true};
            }

            return Boolean{false};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::manhattan(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};

    bool recall{false};

    if (a.type() == typeid(ObjectType))
    {
        a = Patch{std::any_cast<ObjectType>(a)};
        recall = true;
    }
    else if (a.type() == typeid(IndicesType))
    {
        a = Patch{std::any_cast<IndicesType>(a)};
        recall = true;
    }

    if (b.type() == typeid(ObjectType))
    {
        b = Patch{std::any_cast<ObjectType>(b)};
        recall = true;
    }
    else if (b.type() == typeid(IndicesType))
    {
        b = Patch{std::any_cast<IndicesType>(b)};
        recall = true;
    }

    if (recall)
        return manhattan({a, b});

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        try
        {
            auto dmin{std::numeric_limits<IntegerType>::max()};

            for (auto const& [ai, aj] : std::any_cast<IndicesType>(toindices({a})))
            {
                for (auto const& [bi, bj] : std::any_cast<IndicesType>(toindices({b})))
                {
                    IntegerType const d{std::abs(ai - bi) + std::abs(aj - bj)};
                    dmin = std::min(dmin, d);
                }
            }

            return dmin;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::adjacent(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};

    bool recall{false};

    if (a.type() == typeid(ObjectType))
    {
        a = Patch{std::any_cast<ObjectType>(a)};
        recall = true;
    }
    else if (a.type() == typeid(IndicesType))
    {
        a = Patch{std::any_cast<IndicesType>(a)};
        recall = true;
    }

    if (b.type() == typeid(ObjectType))
    {
        b = Patch{std::any_cast<ObjectType>(b)};
        recall = true;
    }
    else if (b.type() == typeid(IndicesType))
    {
        b = Patch{std::any_cast<IndicesType>(b)};
        recall = true;
    }

    if (recall)
        return adjacent({a, b});

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        try
        {
            return Boolean{std::any_cast<IntegerType>(manhattan(args)) == 1};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::bordering(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};
    auto const grid{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return bordering({patch, std::get<GridType>(piece)});
    }

    if (patch.type() == typeid(ObjectType))
        return bordering({Patch{std::any_cast<ObjectType>(patch)}, grid});
    else if (patch.type() == typeid(IndicesType))
        return bordering({Patch{std::any_cast<IndicesType>(patch)}, grid});

    if (patch.type() == typeid(Patch) && grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        try
        {
            auto const urm{std::any_cast<IntegerType>(uppermost({patch}))};
            auto const ltm{std::any_cast<IntegerType>(leftmost({patch}))};
            auto const lrm{std::any_cast<IntegerType>(lowermost({patch}))};
            auto const rtm{std::any_cast<IntegerType>(rightmost({patch}))};

            return Boolean{urm == 0 || ltm == 0 || lrm == static_cast<IntegerType>(grid_.size()) - 1 || rtm == static_cast<IntegerType>(grid_.at(0).size()) - 1};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::centerofmass(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(ObjectType))
        return centerofmass({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return centerofmass({Patch{std::any_cast<IndicesType>(patch)}});

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
        auto const l{static_cast<IntegerType>(std::holds_alternative<ObjectType>(patch_) ? std::get<ObjectType>(patch_).size() : std::get<IndicesType>(patch_).size())};

        if (!l)
            throw std::runtime_error{"Wrong value"};

        try
        {
            IntegerType sumRow{0};
            IntegerType sumCol{0};

            for (auto const& [i, j] : std::any_cast<IndicesType>(toindices(args)))
            {
                sumRow += i;
                sumCol += j;
            }

            return IntegerTuple{sumRow / l, sumCol / l};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::palette(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const element{args[0]};

    if (element.type() == typeid(ObjectType))
        return palette({Element{std::any_cast<ObjectType>(element)}});
    else if (element.type() == typeid(GridType))
        return palette({Element{std::any_cast<GridType>(element)}});

    if (element.type() == typeid(Element))
    {
        auto const element_{std::any_cast<Element>(element)};

        IntegerSet colors;

        if (std::holds_alternative<GridType>(element_))
        {
            auto const& grid{std::get<GridType>(element_)};

            for (auto const& row : grid)
                colors.insert(row.begin(), row.end());
        }
        else if (std::holds_alternative<ObjectType>(element_))
        {
            auto const& objectType{std::get<ObjectType>(element_)};

            for (auto const& [color, position] : objectType)
                colors.insert(color);
        }

        return colors;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::numcolors(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const element{args[0]};

    if (element.type() == typeid(ObjectType))
        return numcolors({Element{std::any_cast<ObjectType>(element)}});
    else if (element.type() == typeid(GridType))
        return numcolors({Element{std::any_cast<GridType>(element)}});

    if (element.type() == typeid(Element))
    {
        try
        {
            return static_cast<IntegerType>(std::any_cast<IntegerSet>(palette(args)).size());
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::color(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const object{args[0]};

    if (object.type() == typeid(ObjectType))
    {
        auto const& object_{std::any_cast<ObjectType>(object)};

        if (object_.empty())
            throw std::runtime_error{"Wrong value"};

        return object_.begin()->first;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::toobject(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};
    auto const grid{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return toobject({patch, std::get<GridType>(piece)});
    }

    if (patch.type() == typeid(ObjectType))
        return toobject({Patch{std::any_cast<ObjectType>(patch)}, grid});
    else if (patch.type() == typeid(IndicesType))
        return toobject({Patch{std::any_cast<IndicesType>(patch)}, grid});

    if (patch.type() == typeid(Patch) && grid.type() == typeid(GridType))
    {
        auto const& patch_{std::any_cast<Patch>(patch)};
        auto const& grid_{std::any_cast<GridType>(grid)};

        try
        {
            auto const h{grid_.size()};
            auto const w{grid_.at(0).size()};

            ObjectType ObjectType;

            if (grid_.empty())
                throw std::runtime_error{"Wrong value"};

            for (auto const& [i, j] : std::any_cast<IndicesType>(toindices({patch})))
            {
                if (0 <= i && i < h && 0 <= j && j < w)
                    ObjectType.emplace(grid_.at(i).at(j), IntegerTuple{i, j});
            }

            return ObjectType;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::asobject(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return asobject({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const& grid_{std::any_cast<GridType>(grid)};

        try
        {
            ObjectType ObjectType;

            for (IntegerType i = 0; i < static_cast<IntegerType>(grid_.size()); ++i)
            {
                for (IntegerType j = 0; j < static_cast<IntegerType>(grid_.at(i).size()); ++j)
                    ObjectType.emplace(grid_.at(i).at(j), IntegerTuple{i, j});
            }

            return ObjectType;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::rot90(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return rot90({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        auto const rows{grid_.size()};
        auto const cols{grid_.at(0).size()};

        GridType result(cols, std::vector<IntegerType>(rows));

        try
        {
            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < cols; ++j)
                    result.at(j).at(rows - 1 - i) = grid_.at(i).at(j);
            }
        }
        catch (const std::exception&)
        {
            throw std::runtime_error{"Wrong value"};
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::rot180(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return rot180({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        auto const rows{grid_.size()};
        auto const cols{grid_.at(0).size()};

        GridType result(rows, std::vector<IntegerType>(cols));

        try
        {
            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < cols; ++j)
                    result.at(rows - 1 - i).at(cols - 1 - j) = grid_.at(i).at(j);
            }
        }
        catch (const std::exception&)
        {
            throw std::runtime_error{"Wrong value"};
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::rot270(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return rot270({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        auto const rows{grid_.size()};
        auto const cols{grid_.at(0).size()};

        GridType result(cols, std::vector<IntegerType>(rows));

        try
        {
            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < cols; ++j)
                    result.at(cols - 1 - j).at(i) = grid_.at(i).at(j);
            }
        }
        catch (const std::exception&)
        {
            throw std::runtime_error{"Wrong value"};
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hmirror(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
    {
        auto const piece_{std::any_cast<Piece>(piece)};

        if (std::holds_alternative<GridType>(piece_))
        {
            auto grid = std::get<GridType>(piece_);

            std::reverse(grid.begin(), grid.end());

            return grid;
        }

        auto patch = std::get<Patch>(piece_);
        auto const ulc = std::any_cast<IntegerTuple>(ulcorner({patch}));
        auto const lrc = std::any_cast<IntegerTuple>(lrcorner({patch}));

        auto const d = ulc.first + lrc.first;

        if (std::holds_alternative<ObjectType>(patch))
        {
            auto const& obj = std::get<ObjectType>(patch);

            ObjectType result;

            for (auto const& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {d - i, j}});
            }

            return result;
        }

        auto const& indices = std::get<IndicesType>(patch);

        IndicesType result;

        for (auto const& [i, j] : indices)
            result.insert({d - i, j});

        return result;
    }
    else if (piece.type() == typeid(GridType))
        return hmirror({Piece{std::any_cast<GridType>(piece)}});
    else if (piece.type() == typeid(Patch))
        return hmirror({Piece{std::any_cast<Patch>(piece)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::vmirror(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
    {
        auto const piece_{std::any_cast<Piece>(piece)};

        if (std::holds_alternative<GridType>(piece_))
        {
            auto grid = std::get<GridType>(piece_);

            for (auto& row : grid)
                std::reverse(row.begin(), row.end());

            return grid;
        }

        auto patch = std::get<Patch>(piece_);
        auto const ulc = std::any_cast<IntegerTuple>(ulcorner({patch}));
        auto const lrc = std::any_cast<IntegerTuple>(lrcorner({patch}));

        auto const d = ulc.second + lrc.second;

        if (std::holds_alternative<ObjectType>(patch))
        {
            auto const& obj = std::get<ObjectType>(patch);

            ObjectType result;

            for (auto const& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {i, d - j}});
            }

            return result;
        }

        auto const& indices = std::get<IndicesType>(patch);

        IndicesType result;

        for (auto const& [i, j] : indices)
            result.insert({i, d - j});

        return result;
    }
    else if (piece.type() == typeid(GridType))
        return vmirror({Piece{std::any_cast<GridType>(piece)}});
    else if (piece.type() == typeid(Patch))
        return vmirror({Piece{std::any_cast<Patch>(piece)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::dmirror(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
    {
        auto const piece_{std::any_cast<Piece>(piece)};

        if (std::holds_alternative<GridType>(piece_))
        {
            auto const& grid = std::get<GridType>(piece_);

            if (grid.empty())
                return GridType{};

            auto const rows = static_cast<IntegerType>(grid.size());
            auto const cols = static_cast<IntegerType>(grid.at(0).size());

            GridType result(cols, std::vector<IntegerType>(rows));

            try
            {
                for (IntegerType i = 0; i < rows; ++i)
                {
                    for (IntegerType j = 0; j < cols; ++j)
                        result.at(j).at(i) = grid.at(i).at(j);
                }
            }
            catch (std::exception const&)
            {
                throw std::runtime_error{"Wrong value"};
            }

            return result;
        }

        Patch patch = std::get<Patch>(piece_);

        auto [a, b] = std::any_cast<IntegerTuple>(ulcorner({patch}));

        if (std::holds_alternative<ObjectType>(patch))
        {
            auto const& obj = std::get<ObjectType>(patch);

            ObjectType result;

            for (auto const& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {j - b + a, i - a + b}});
            }

            return result;
        }

        auto const& indices = std::get<IndicesType>(patch);

        IndicesType result;

        for (auto const& [i, j] : indices)
            result.insert({j - b + a, i - a + b});

        return result;
    }
    else if (piece.type() == typeid(GridType))
        return dmirror({Piece{std::any_cast<GridType>(piece)}});
    else if (piece.type() == typeid(Patch))
        return dmirror({Piece{std::any_cast<Patch>(piece)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::cmirror(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
    {
        auto const piece_{std::any_cast<Piece>(piece)};

        if (std::holds_alternative<GridType>(piece_))
        {
            auto grid = std::get<GridType>(piece_);

            std::reverse(grid.begin(), grid.end());

            for (auto& row : grid)
                std::reverse(row.begin(), row.end());

            return dmirror({Piece{grid}});
        }

        return vmirror({dmirror({vmirror(args)})});
    }
    else if (piece.type() == typeid(GridType))
        return cmirror({Piece{std::any_cast<GridType>(piece)}});
    else if (piece.type() == typeid(Patch))
        return cmirror({Piece{std::any_cast<Patch>(piece)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::fill(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const value{args[1]};
    auto const patch{args[2]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return fill({std::get<GridType>(piece), value, patch});
    }

    if (patch.type() == typeid(ObjectType))
        return fill({grid, value, Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return fill({grid, value, Patch{std::any_cast<IndicesType>(patch)}});

    if (grid.type() == typeid(GridType) && value.type() == typeid(IntegerType) && patch.type() == typeid(Patch))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const value_{std::any_cast<IntegerType>(value)};
        auto const patch_{std::any_cast<Patch>(patch)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h = grid_.size();
            auto const w = grid_.at(0).size();

            GridType result = grid_;

            for (auto const& [i, j] : std::any_cast<IndicesType>(toindices({patch})))
            {
                if (0 <= i && i < h && 0 <= j && j < w)
                    result.at(i).at(j) = value_;
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }
    
    throw std::runtime_error{"Wrong value"};
}

std::any hodel::paint(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const obj{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return paint({std::get<GridType>(piece), obj});
    }

    if (grid.type() == typeid(GridType) && obj.type() == typeid(ObjectType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const obj_{std::any_cast<ObjectType>(obj)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h = grid_.size();
            auto const w = grid_.at(0).size();

            GridType result = grid_;

            for (auto const& [value, location] : obj_)
            {
                auto const& [i, j] = location;

                if (0 <= i && i < h && 0 <= j && j < w)
                    result.at(i).at(j) = value;
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }
    
    throw std::runtime_error{"Wrong value"};
}

std::any hodel::underfill(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const value{args[1]};
    auto const patch{args[2]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return underfill({std::get<GridType>(piece), value, patch});
    }

    if (patch.type() == typeid(ObjectType))
        return underfill({grid, value, Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return underfill({grid, value, Patch{std::any_cast<IndicesType>(patch)}});

    if (grid.type() == typeid(GridType) && value.type() == typeid(IntegerType) && patch.type() == typeid(Patch))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const value_{std::any_cast<IntegerType>(value)};
        auto const patch_{std::any_cast<Patch>(patch)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h = grid_.size();
            auto const w = grid_.at(0).size();
            auto const bg = std::any_cast<IntegerType>(mostcolor({grid_}));

            GridType result = grid_;

            for (auto const& [i, j] : std::any_cast<IndicesType>(toindices({patch})))
            {
                if (0 <= i && i < h && 0 <= j && j < w && result.at(i).at(j) == bg)
                    result.at(i).at(j) = value_;
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }
    
    throw std::runtime_error{"Wrong value"};
}

std::any hodel::underpaint(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const obj{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return underpaint({std::get<GridType>(piece), obj});
    }

    if (grid.type() == typeid(GridType) && obj.type() == typeid(ObjectType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const obj_{std::any_cast<ObjectType>(obj)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h = grid_.size();
            auto const w = grid_.at(0).size();
            auto const bg = std::any_cast<IntegerType>(mostcolor({grid_}));

            GridType result = grid_;

            for (auto const& [value, location] : obj_)
            {
                auto const& [i, j] = location;

                if (0 <= i && i < h && 0 <= j && j < w && result.at(i).at(j) == bg)
                    result.at(i).at(j) = value;
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }
    
    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hupscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const factor{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return hupscale({std::get<GridType>(piece), factor});
    }

    if (grid.type() == typeid(GridType) && factor.type() == typeid(IntegerType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const factor_{std::any_cast<IntegerType>(factor)};

        if (factor_ <= 1 || factor_ > 10)
            throw std::runtime_error{"Wrong value"};

        GridType result;

        for (auto const& row : grid_)
        {
            std::vector<IntegerType> new_row;
            new_row.reserve(row.size() * factor_);

            for (auto const& cell : row)
            {
                for (IntegerType i{0}; i < factor_; ++i)
                    new_row.emplace_back(cell);
            }

            result.emplace_back(new_row);
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::vupscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const factor{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return vupscale({std::get<GridType>(piece), factor});
    }

    if (grid.type() == typeid(GridType) && factor.type() == typeid(IntegerType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const factor_{std::any_cast<IntegerType>(factor)};

        if (factor_ <= 1 || factor_ > 10)
            throw std::runtime_error{"Wrong value"};

        GridType result;
        result.reserve(grid_.size() * factor_);

        for (auto const& row : grid_)
        {
            for (IntegerType k = 0; k < factor_; ++k)
                result.emplace_back(row);
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::upscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const element{args[0]};
    auto const factor{args[1]};

    if (element.type() == typeid(Element) && factor.type() == typeid(IntegerType))
    {
        auto const element_{std::any_cast<Element>(element)};
        auto const factor_{std::any_cast<IntegerType>(factor)};

        if (factor_ <= 1 || factor_ > 10)
            throw std::runtime_error{"Wrong value"};

        if (std::holds_alternative<GridType>(element_))
        {
            auto const& grid = std::get<GridType>(element_);

            GridType result;

            for (auto const& row : grid)
            {
                std::vector<IntegerType> upscaled_row;

                upscaled_row.reserve(row.size() * factor_);

                for (auto const& value : row)
                {
                    for (IntegerType k = 0; k < factor_; ++k)
                        upscaled_row.emplace_back(value);
                }

                for (IntegerType k = 0; k < factor_; ++k)
                    result.emplace_back(upscaled_row);
            }

            return result;
        }

        auto const& obj = std::get<ObjectType>(element_);

        if (obj.empty())
            return ObjectType{};

        auto const [di_inv, dj_inv] = std::any_cast<IntegerTuple>(ulcorner({element}));
        IntegerType const di = -di_inv;
        IntegerType const dj = -dj_inv;

        Patch const p = std::any_cast<Patch>(shift({Patch{obj}, IntegerTuple{di, dj}}));
        ObjectType normed_obj = std::get<ObjectType>(p);
        ObjectType result;

        for (auto const& [value, pos] : normed_obj)
        {
            auto const& [i, j] = pos;

            for (IntegerType io = 0; io < factor_; ++io)
            {
                for (IntegerType jo = 0; jo < factor_; ++jo)
                    result.insert({value, {i * factor_ + io, j * factor_ + jo}});
            }
        }

        return shift({Patch{result}, IntegerTuple{di_inv, dj_inv}});
    }
    else if (element.type() == typeid(GridType))
        return upscale({Element{std::any_cast<GridType>(element)}, factor});
    else if (element.type() == typeid(ObjectType))
        return upscale({Element{std::any_cast<ObjectType>(element)}, factor});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::downscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const factor{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return downscale({std::get<GridType>(piece), factor});
    }

    if (grid.type() == typeid(GridType) && factor.type() == typeid(IntegerType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const factor_{std::any_cast<IntegerType>(factor)};

        if (factor_ <= 1)
            throw std::runtime_error{"Wrong value"};

        if (grid_.empty())
            return grid_;

        try
        {
            auto const h = static_cast<IntegerType>(grid_.size());
            auto const w = static_cast<IntegerType>(grid_.at(0).size());

            GridType temp;

            for (IntegerType i = 0; i < h; ++i)
            {
                std::vector<IntegerType> row;

                for (IntegerType j = 0; j < w; ++j)
                {
                    if (j % factor_ == 0)
                        row.emplace_back(grid_.at(i).at(j));
                }

                temp.emplace_back(row);
            }

            GridType result;

            for (IntegerType i = 0; i < static_cast<IntegerType>(temp.size()); ++i)
            {
                if (i % factor_ == 0)
                    result.emplace_back(temp.at(i));
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hconcat(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};

    bool recall{false};

    if (a.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(a)};

        if (std::holds_alternative<GridType>(piece))
            a = std::get<GridType>(piece);
    }

    if (b.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(b)};

        if (std::holds_alternative<GridType>(piece))
            b = std::get<GridType>(piece);
    }

    if (recall)
        return hconcat({a, b});

    if (a.type() == typeid(GridType) && b.type() == typeid(GridType))
    {
        auto const a_{std::any_cast<GridType>(a)};
        auto const b_{std::any_cast<GridType>(b)};

        GridType result;
        auto const rows = std::min(a_.size(), b_.size());
        result.reserve(rows);

        for (size_t i = 0; i < rows; ++i)
        {
            std::vector<IntegerType> row;
            row.reserve(a_[i].size() + b_[i].size());

            row.insert(row.end(), a_[i].begin(), a_[i].end());
            row.insert(row.end(), b_[i].begin(), b_[i].end());
            result.emplace_back(std::move(row));
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::vconcat(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};

    bool recall{false};

    if (a.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(a)};

        if (std::holds_alternative<GridType>(piece))
            a = std::get<GridType>(piece);
    }

    if (b.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(b)};

        if (std::holds_alternative<GridType>(piece))
            b = std::get<GridType>(piece);
    }

    if (recall)
        return hconcat({a, b});

    if (a.type() == typeid(GridType) && b.type() == typeid(GridType))
    {
        auto const a_{std::any_cast<GridType>(a)};
        auto const b_{std::any_cast<GridType>(b)};

        GridType result;
        result.reserve(a_.size() + b_.size());

        result.insert(result.end(), a_.begin(), a_.end());
        result.insert(result.end(), b_.begin(), b_.end());

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::subgrid(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};
    auto const grid{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return subgrid({patch, std::get<GridType>(piece)});
    }

    if (patch.type() == typeid(IndicesType))
        return subgrid({Patch(std::any_cast<IndicesType>(patch)), grid});
    else if (patch.type() == typeid(ObjectType))
        return subgrid({Patch(std::any_cast<ObjectType>(patch)), grid});

    if (patch.type() == typeid(Patch) && grid.type() == typeid(GridType))
        return crop({grid, ulcorner({patch}), shape({patch})});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hsplit(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const n{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return hsplit({std::get<GridType>(piece), n});
    }

    if (grid.type() == typeid(GridType) && n.type() == typeid(IntegerType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const n_{std::any_cast<IntegerType>(n)};

        if (grid_.empty() || n_ <= 0)
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h{static_cast<IntegerType>(grid_.size())};
            auto const w{static_cast<IntegerType>(grid_.at(0).size()) / n_};
            IntegerType const offset{(grid_.at(0).size() % n_ != 0)};

            std::vector<GridType> result;
            result.reserve(n_);

            for (IntegerType i = 0; i < n_; ++i)
                result.emplace_back(std::any_cast<GridType>(crop({grid_, IntegerTuple{0, w * i + i * offset}, IntegerTuple{h, w}})));

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::vsplit(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const n{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return vsplit({std::get<GridType>(piece), n});
    }

    if (grid.type() == typeid(GridType) && n.type() == typeid(IntegerType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const n_{std::any_cast<IntegerType>(n)};

        if (grid_.empty() || n_ <= 0)
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h{static_cast<IntegerType>(grid_.size()) / n_};
            auto const w{static_cast<IntegerType>(grid_.at(0).size())};
            IntegerType const offset{(grid_.size() % n_ != 0)};

            std::vector<GridType> result;
            result.reserve(n_);

            for (IntegerType i = 0; i < n_; ++i)
                result.emplace_back(std::any_cast<GridType>(crop({grid_, IntegerTuple{h * i + i * offset, 0}, IntegerTuple{h, w}})));

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::cellwise(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};
    auto const fallback{args[2]};

    bool recall{false};

    if (a.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(a)};

        if (std::holds_alternative<GridType>(piece))
            a = std::get<GridType>(piece);
    }

    if (b.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(b)};

        if (std::holds_alternative<GridType>(piece))
            b = std::get<GridType>(piece);
    }

    if (recall)
        return cellwise({a, b, fallback});

    if (a.type() == typeid(GridType) && b.type() == typeid(GridType) && fallback.type() == typeid(IntegerType))
    {
        auto const a_{std::any_cast<GridType>(a)};
        auto const b_{std::any_cast<GridType>(b)};
        auto const fallback_{std::any_cast<IntegerType>(fallback)};

        try
        {
            auto const h{static_cast<IntegerType>(a_.size())};
            auto const w{static_cast<IntegerType>(a_.at(0).size())};

            GridType result(h, std::vector<IntegerType>(w));

            for (IntegerType i{0}; i < h; ++i)
            {
                for (IntegerType j{0}; j < w; ++j)
                    result.at(i).at(j) = (a_.at(i).at(j) == b_.at(i).at(j)) ? a_.at(i).at(j) : fallback_;
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::replace(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const replacee{args[1]};
    auto const replacer{args[2]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return replace({std::get<GridType>(piece), replacee, replacer});
    }

    if (grid.type() == typeid(GridType) && replacee.type() == typeid(IntegerType) && replacer.type() == typeid(IntegerType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const replacee_{std::any_cast<IntegerType>(replacee)};
        auto const replacer_{std::any_cast<IntegerType>(replacer)};

        GridType result = grid_;

        for (auto& row : result)
        {
            for (auto& v : row)
            {
                if (v == replacee_)
                    v = replacer_;
            }
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::switch_(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const a{args[1]};
    auto const b{args[2]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return switch_({std::get<GridType>(piece), a, b});
    }

    if (grid.type() == typeid(GridType) && a.type() == typeid(IntegerType) && b.type() == typeid(IntegerType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const a_{std::any_cast<IntegerType>(a)};
        auto const b_{std::any_cast<IntegerType>(b)};

        GridType result = grid_;

        for (auto& row : result)
        {
            for (auto& v : row)
            {
                if (v == a_)
                    v = b_;
                else if (v == b_)
                    v = a_;
            }
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::center(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(ObjectType))
        return center({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return center({Patch{std::any_cast<IndicesType>(patch)}});

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        try
        {
            auto const um{std::any_cast<IntegerType>(uppermost(args))};
            auto const h{std::any_cast<IntegerType>(height(args))};
            auto const lm{std::any_cast<IntegerType>(leftmost(args))};
            auto const w{std::any_cast<IntegerType>(width(args))};

            return IntegerTuple{um + h / 2, lm + w / 2};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::position(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto a{args[0]};
    auto b{args[1]};

    bool recall{false};

    if (a.type() == typeid(ObjectType))
    {
        a = Patch{std::any_cast<ObjectType>(a)};
        recall = true;
    }
    else if (a.type() == typeid(IndicesType))
    {
        a = Patch{std::any_cast<IndicesType>(a)};
        recall = true;
    }

    if (b.type() == typeid(ObjectType))
    {
        b = Patch{std::any_cast<ObjectType>(b)};
        recall = true;
    }
    else if (b.type() == typeid(IndicesType))
    {
        b = Patch{std::any_cast<IndicesType>(b)};
        recall = true;
    }

    if (recall)
        return position({a, b});

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        auto const a_{std::any_cast<Patch>(a)};
        auto const b_{std::any_cast<Patch>(b)};

        try
        {
            auto const [ia, ib] = std::any_cast<IntegerTuple>(center({toindices({a_})}));
            auto const [ja, jb] = std::any_cast<IntegerTuple>(center({toindices({b_})}));

            if (ia == ib)
                return IntegerTuple{0, ja < jb ? 1 : -1};
            else if (ja == jb)
                return IntegerTuple{ia < ib ? 1: -1, 0};
            else if (ia < ib)
                return IntegerTuple{1, ja < jb ? 1 : -1};
            else if (ia > ib)
                return IntegerTuple{-1, ja < jb ? 1 : -1};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::index(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const loc{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return index({std::get<GridType>(piece), loc});
    }

    if (grid.type() == typeid(GridType) && loc.type() == typeid(IntegerTuple))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const loc_{std::any_cast<IntegerTuple>(loc)};

        if (grid_.empty() || grid_.at(0).empty())
            throw std::runtime_error{"Wrong value"};

        auto const& [i, j] = loc_;
        auto const h{static_cast<IntegerType>(grid_.size())};
        auto const w{static_cast<IntegerType>(grid_.at(0).size())};

        if (!(0 <= i && i < h && 0 <= j && j < w))
            throw std::runtime_error{"Wrong value"};

        try
        {
            return grid_.at(i).at(j);
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::canvas(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const value{args[0]};
    auto const dimensions{args[1]};

    if (value.type() == typeid(IntegerType) && dimensions.type() == typeid(IntegerTuple))
    {
        auto const value_{std::any_cast<IntegerType>(value)};
        auto const dimensions_{std::any_cast<IntegerTuple>(dimensions)};

        if (dimensions_.first < 0 || dimensions_.second < 0)
            throw std::runtime_error{"Wrong value"};

        return GridType(dimensions_.first, std::vector<IntegerType>(dimensions_.second, value_));
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::corners(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(ObjectType))
        return corners({Patch{std::any_cast<ObjectType>(patch)}});
    else if (patch.type() == typeid(IndicesType))
        return corners({Patch{std::any_cast<IndicesType>(patch)}});

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        try
        {
            auto const ulc{std::any_cast<IntegerTuple>(ulcorner(args))};
            auto const urc{std::any_cast<IntegerTuple>(urcorner(args))};
            auto const llc{std::any_cast<IntegerTuple>(llcorner(args))};
            auto const lrc{std::any_cast<IntegerTuple>(lrcorner(args))};

            return IndicesType{ulc, urc, llc, lrc};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::connect(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(IntegerTuple) && b.type() == typeid(IntegerTuple))
    {
        auto const a_{std::any_cast<IntegerTuple>(a)};
        auto const b_{std::any_cast<IntegerTuple>(b)};

        auto const& [ai, aj] = a_;
        auto const& [bi, bj] = b_;

        IntegerType di{0};
        IntegerType dj{0};

        if (std::abs(bi - ai) > SHOOT_DISTANCE * MAX_SIZE || std::abs(bj - aj) > SHOOT_DISTANCE * MAX_SIZE)
            throw std::runtime_error{"Wrong value"};

        if (ai == bi)
            dj = (bj > aj ? 1 : -1);
        else if (aj == bj)
            di = (bi > ai ? 1 : -1);
        else if (std::abs(bi - ai) == std::abs(bj - aj))
        {
            di = (bi > ai ? 1 : -1);
            dj = (bj > aj ? 1 : -1);
        }
        else
            throw std::runtime_error{"Wrong value"};

        IndicesType result;

        auto i{ai};
        auto j{aj};

        while (true)
        {
            result.emplace(i, j);

            if (i == bi && j == bj)
                break;

            i += di;
            j += dj;
        }

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::cover(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const patch{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return cover({std::get<GridType>(piece), patch});
    }

    if (patch.type() == typeid(IndicesType))
        return cover({grid, Patch(std::any_cast<IndicesType>(patch))});
    else if (patch.type() == typeid(ObjectType))
        return cover({grid, Patch(std::any_cast<ObjectType>(patch))});

    if (grid.type() == typeid(GridType) && patch.type() == typeid(Patch))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const patch_{std::any_cast<Patch>(patch)};

        return fill({grid, mostcolor({grid}), toindices({patch})});
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::trim(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return trim({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        GridType result;

        if (grid_.size() <= 2 || grid_.front().size() <= 2)
            return result;

        for (size_t i{1}; i + 1 < grid_.size(); ++i)
            result.emplace_back(grid_[i].begin() + 1, grid_[i].end() - 1);

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::move(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const obj{args[1]};
    auto const offset{args[2]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return move({std::get<GridType>(piece), obj, offset});
    }

    if (grid.type() == typeid(GridType) && obj.type() == typeid(ObjectType) && offset.type() == typeid(IntegerTuple))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const obj_{std::any_cast<ObjectType>(obj)};
        auto const offset_{std::any_cast<IntegerTuple>(offset)};

        return paint({cover({grid, obj}), shift({obj, offset})});
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::tophalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return tophalf({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const mid = grid_.size() / 2;

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        return GridType(grid_.begin(), grid_.begin() + mid);
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::bottomhalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return bottomhalf({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const mid = grid_.size() / 2 + grid_.size() % 2;

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        return GridType(grid_.begin() + mid, grid_.end());
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::lefthalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return lefthalf({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
        return rot270({tophalf({rot90(args)})});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::righthalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return righthalf({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
        return rot270({bottomhalf({rot90(args)})});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::vfrontier(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const location{args[0]};

    if (location.type() == typeid(IntegerTuple))
    {
        auto const location_{std::any_cast<IntegerTuple>(location)};

        IndicesType result;

        for (IntegerType i{0}; i < MAX_SIZE; ++i)
            result.emplace(i, location_.second);

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hfrontier(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const location{args[0]};

    if (location.type() == typeid(IntegerTuple))
    {
        auto const location_{std::any_cast<IntegerTuple>(location)};

        IndicesType result;

        for (IntegerType j{0}; j < MAX_SIZE; ++j)
            result.emplace(location_.first, j);

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::backdrop(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(IndicesType))
        return backdrop({Patch(std::any_cast<IndicesType>(patch))});
    else if (patch.type() == typeid(ObjectType))
        return backdrop({Patch(std::any_cast<ObjectType>(patch))});

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        if (std::holds_alternative<ObjectType>(patch_))
        {
            auto const obj{std::get<ObjectType>(patch_)};

            if (obj.empty())
                throw std::runtime_error{"Wrong value"};
        }
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};

            if (indices.empty())
                throw std::runtime_error{"Wrong value"};
        }

        try
        {
            auto const ulc{std::any_cast<IntegerTuple>(ulcorner({patch_}))};
            auto const lrc{std::any_cast<IntegerTuple>(lrcorner({patch_}))};

            IndicesType result;

            for (IntegerType i = ulc.first; i <= lrc.first; ++i)
            {
                for (IntegerType j = ulc.second; j <= lrc.second; ++j)
                    result.emplace(i, j);
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::delta(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(IndicesType))
        return delta({Patch(std::any_cast<IndicesType>(patch))});
    else if (patch.type() == typeid(ObjectType))
        return delta({Patch(std::any_cast<ObjectType>(patch))});

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
    
        if (std::holds_alternative<ObjectType>(patch_))
        {
            auto const obj{std::get<ObjectType>(patch_)};

            if (obj.empty())
                throw std::runtime_error{"Wrong value"};
        }
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};

            if (indices.empty())
                throw std::runtime_error{"Wrong value"};
        }

        try
        {
            auto result = std::any_cast<IndicesType>(backdrop({patch_}));

            for (const auto& p : std::any_cast<IndicesType>(toindices({patch_})))
                result.erase(p);

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::gravitate(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto source{args[0]};
    auto destination{args[1]};

    bool recall{false};

    if (source.type() == typeid(ObjectType))
    {
        source = Patch{std::any_cast<ObjectType>(source)};
        recall = true;
    }
    else if (source.type() == typeid(IndicesType))
    {
        source = Patch{std::any_cast<IndicesType>(source)};
        recall = true;
    }

    if (destination.type() == typeid(ObjectType))
    {
        destination = Patch{std::any_cast<ObjectType>(destination)};
        recall = true;
    }
    else if (destination.type() == typeid(IndicesType))
    {
        destination = Patch{std::any_cast<IndicesType>(destination)};
        recall = true;
    }

    if (recall)
        return gravitate({source, destination});

    if (source.type() == typeid(Patch) && destination.type() == typeid(Patch))
    {
        auto const source_{std::any_cast<Patch>(source)};
        auto const destination_{std::any_cast<Patch>(destination)};

        Patch current = source_;

        try
        {
            auto const [si, sj] = std::any_cast<IntegerTuple>(center({current}));
            auto const [di, dj] = std::any_cast<IntegerTuple>(center({destination_}));

            IntegerType stepI = 0;
            IntegerType stepJ = 0;

            if (std::any_cast<Boolean>(vmatching({current, destination})))
                stepI = (si < di) ? 1 : -1;
            else
                stepJ = (sj < dj) ? 1 : -1;

            auto moveI = stepI;
            auto moveJ = stepJ;
            IntegerType count = 0;

            while (!std::any_cast<Boolean>(adjacent({current, destination})) && count < 42)
            {
                ++count;

                moveI += stepI;
                moveJ += stepJ;

                auto const v = shift({current, IntegerTuple{stepI, stepJ}});

                if (v.type() == typeid(ObjectType))
                    current = Patch{std::any_cast<ObjectType>(v)};
                else
                    current = Patch{std::any_cast<IndicesType>(v)};
            }

            return IntegerTuple{moveI - stepI, moveJ - stepJ};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::inbox(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(IndicesType))
        return inbox({Patch(std::any_cast<IndicesType>(patch))});
    else if (patch.type() == typeid(ObjectType))
        return inbox({Patch(std::any_cast<ObjectType>(patch))});

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
    
        if (std::holds_alternative<ObjectType>(patch_))
        {
            auto const obj{std::get<ObjectType>(patch_)};

            if (obj.empty())
                throw std::runtime_error{"Wrong value"};
        }
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};

            if (indices.empty())
                throw std::runtime_error{"Wrong value"};
        }

        try
        {
            auto const ai = std::any_cast<IntegerType>(uppermost({patch})) + 1;
            auto const aj = std::any_cast<IntegerType>(leftmost({patch})) + 1;
            auto const bi = std::any_cast<IntegerType>(lowermost({patch})) - 1;
            auto const bj = std::any_cast<IntegerType>(rightmost({patch})) - 1;

            return rectangleOutline(
                std::min(ai, bi),
                std::min(aj, bj),
                std::max(ai, bi),
                std::max(aj, bj));
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::outbox(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(IndicesType))
        return outbox({Patch(std::any_cast<IndicesType>(patch))});
    else if (patch.type() == typeid(ObjectType))
        return outbox({Patch(std::any_cast<ObjectType>(patch))});

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
    
        if (std::holds_alternative<ObjectType>(patch_))
        {
            auto const obj{std::get<ObjectType>(patch_)};

            if (obj.empty())
                throw std::runtime_error{"Wrong value"};
        }
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};

            if (indices.empty())
                throw std::runtime_error{"Wrong value"};
        }

        try
        {
            auto const ai = std::any_cast<IntegerType>(uppermost({patch})) + 1;
            auto const aj = std::any_cast<IntegerType>(leftmost({patch})) + 1;
            auto const bi = std::any_cast<IntegerType>(lowermost({patch})) - 1;
            auto const bj = std::any_cast<IntegerType>(rightmost({patch})) - 1;

            return rectangleOutline(
                std::min(ai, bi),
                std::min(aj, bj),
                std::max(ai, bi),
                std::max(aj, bj));
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::box(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(IndicesType))
        return box({Patch(std::any_cast<IndicesType>(patch))});
    else if (patch.type() == typeid(ObjectType))
        return box({Patch(std::any_cast<ObjectType>(patch))});

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
    
        if (std::holds_alternative<ObjectType>(patch_))
        {
            auto const obj{std::get<ObjectType>(patch_)};

            if (obj.empty())
                throw std::runtime_error{"Wrong value"};
        }
        else if (std::holds_alternative<IndicesType>(patch_))
        {
            auto const indices{std::get<IndicesType>(patch_)};

            if (indices.empty())
                throw std::runtime_error{"Wrong value"};
        }

        try
        {
            auto const [ai, aj] = std::any_cast<IntegerTuple>(ulcorner({patch}));
            auto const [bi, bj] = std::any_cast<IntegerTuple>(lrcorner({patch}));

            return rectangleOutline(
                std::min(ai, bi),
                std::min(aj, bj),
                std::max(ai, bi),
                std::max(aj, bj));
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::shoot(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const start{args[0]};
    auto const direction{args[1]};

    if (start.type() == typeid(IntegerTuple) && direction.type() == typeid(IntegerTuple))
    {
        auto const start_{std::any_cast<IntegerTuple>(start)};
        auto const direction_{std::any_cast<IntegerTuple>(direction)};

        if (std::abs(start_.first) > 100 || std::abs(start_.second) > 100)
            throw std::runtime_error{"Wrong value"};

        auto const fd{static_cast<size_t>(direction_.first)};
        auto const sd{static_cast<size_t>(direction_.second)};

        if (fd * fd + sd * sd > 2 * MAX_SIZE * MAX_SIZE)
            throw std::runtime_error{"Wrong value"};

        return connect({start_, IntegerTuple{start_.first + SHOOT_DISTANCE * direction_.first, start_.second + SHOOT_DISTANCE * direction_.second}});
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::occurrences(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const obj{args[1]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return occurrences({std::get<GridType>(piece), obj});
    }

    if (grid.type() == typeid(GridType) && obj.type() == typeid(ObjectType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};
        auto const obj_{std::any_cast<ObjectType>(obj)};

        if (grid_.empty() || obj_.empty())
            throw std::runtime_error{"Wrong value"};

        try
        {
            IndicesType occs;
            auto const normed = std::any_cast<ObjectType>(normalize({obj_}));

            auto const h = grid_.size();
            auto const w = grid_.at(0).size();

            auto const [oh, ow] = std::any_cast<IntegerTuple>(shape({obj_}));

            for (size_t i = 0; i <= h - oh; ++i)
            {
                for (size_t j = 0; j <= w - ow; ++j)
                {
                    bool ok = true;

                    for (auto const& [value, pos] : normed)
                    {
                        size_t const a = pos.first + i;
                        size_t const b = pos.second + j;

                        if (grid_.at(a).at(b) != value)
                        {
                            ok = false;
                            break;
                        }
                    }

                    if (ok)
                        occs.emplace(i, j);
                }
            }

            return occs;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::frontiers(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return frontiers({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        try
        {
            Objects result;

            auto const h = grid_.size();
            auto const w = grid_.at(0).size();

            for (size_t i = 0; i < h; ++i)
            {
                auto const color = grid_.at(i).at(0);
                bool uniform = true;

                for (size_t j = 1; j < w; ++j)
                {
                    if (grid_.at(i).at(j) != color)
                    {
                        uniform = false;
                        break;
                    }
                }

                if (uniform)
                {
                    ObjectType ObjectType;

                    for (size_t j = 0; j < w; ++j)
                        ObjectType.emplace(grid_.at(i).at(j), IntegerTuple{i, j});

                    result.insert(std::move(ObjectType));
                }
            }

            for (size_t j = 0; j < w; ++j)
            {
                auto const color = grid_.at(0).at(j);
                bool uniform = true;

                for (size_t i = 1; i < h; ++i)
                {
                    if (grid_.at(i).at(j) != color)
                    {
                        uniform = false;
                        break;
                    }
                }

                if (uniform)
                {
                    ObjectType ObjectType;

                    for (size_t i = 0; i < h; ++i)
                        ObjectType.emplace(grid_.at(i).at(j), IntegerTuple{i, j});

                    result.insert(std::move(ObjectType));
                }
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::compress(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Piece))
    {
        auto const piece{std::any_cast<Piece>(grid)};

        if (std::holds_alternative<GridType>(piece))
            return compress({std::get<GridType>(piece)});
    }

    if (grid.type() == typeid(GridType))
    {
        auto const grid_{std::any_cast<GridType>(grid)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h{static_cast<IntegerType>(grid_.size())};
            auto const w{static_cast<IntegerType>(grid_.at(0).size())};

            std::vector<bool> removeRow(h, false);

            for (IntegerType i = 0; i < h; ++i)
            {
                bool uniform{true};

                for (IntegerType j = 1; j < w; ++j)
                {
                    if (grid_.at(i).at(j) != grid_.at(i).at(0))
                    {
                        uniform = false;
                        break;
                    }
                }

                removeRow[i] = uniform;
            }

            std::vector<bool> removeCol(w, false);

            for (IntegerType j = 0; j < w; ++j)
            {
                bool uniform{true};

                for (IntegerType i = 1; i < h; ++i)
                {
                    if (grid_.at(i).at(j) != grid_.at(0).at(j))
                    {
                        uniform = false;
                        break;
                    }
                }

                removeCol[j] = uniform;
            }

            GridType result;

            for (IntegerType i = 0; i < h; ++i)
            {
                if (removeRow[i])
                    continue;

                std::vector<IntegerType> row;

                for (IntegerType j = 0; j < w; ++j)
                {
                    if (!removeCol[j])
                        row.emplace_back(grid_.at(i).at(j));
                }

                result.emplace_back(std::move(row));
            }

            return result;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hperiod(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const obj{args[0]};

    if (obj.type() == typeid(ObjectType))
    {
        try
        {
            auto const normalized = std::any_cast<ObjectType>(normalize({obj}));
            auto const w = std::any_cast<IntegerType>(width({normalized}));

            for (IntegerType p = 1; p < w; ++p)
            {
                auto const offsetted = std::any_cast<ObjectType>(shift({normalized, IntegerTuple{0, -p}}));

                ObjectType pruned;

                for (const auto& [color, pos] : offsetted)
                {
                    if (pos.second >= 0)
                    {
                        pruned.emplace(color, pos);
                    }
                }

                if (std::includes(
                        normalized.begin(), normalized.end(),
                        pruned.begin(), pruned.end()))
                {
                    return p;
                }
            }

            return w;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::vperiod(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const obj{args[0]};

    if (obj.type() == typeid(ObjectType))
    {
        try
        {
            auto const normalized = std::any_cast<ObjectType>(normalize({obj}));
            auto const h = std::any_cast<IntegerType>(height({normalized}));

            for (IntegerType p = 1; p < h; ++p)
            {
                auto const offsetted = std::any_cast<ObjectType>(shift({normalized, IntegerTuple{-p, 0}}));

                ObjectType pruned;

                for (const auto& [color, pos] : offsetted)
                {
                    if (pos.first >= 0)
                    {
                        pruned.emplace(color, pos);
                    }
                }

                if (std::includes(
                        normalized.begin(), normalized.end(),
                        pruned.begin(), pruned.end()))
                {
                    return p;
                }
            }

            return h;
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}
