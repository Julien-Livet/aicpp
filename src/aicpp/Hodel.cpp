#include <algorithm>
#include <map>
#include <numeric>
#include <ranges>
#include <unordered_set>

#include "aicpp/Hodel.h"

constexpr hodel::Integer MAX_SIZE = 30;
using IntegerCountMap = std::map<hodel::Integer, hodel::Integer>;

IntegerCountMap colorCounts(hodel::Element const& element)
{
    IntegerCountMap counts;

    std::visit(
        [&] (auto const& value)
        {
            using T = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<T, hodel::Grid>)
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
    std::vector<typename T::value_type> values;

    if (container.type() == typeid(hodel::IntegerSet))
        values = toVector<hodel::IntegerSet>(container);
    else if (container.type() == typeid(std::vector<hodel::Integer>))
        values = toVector<std::vector<hodel::Integer> >(container);

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
static std::any apply(std::function<std::any(std::vector<std::any> const&)> const& function, std::any const& container)
{
    if (container.type() != typeid(T))
        return std::any{};

    auto const container_{std::any_cast<T>(container)};

    std::vector<typename T::value_type> values;
    values.reserve(container_.size());

    for (auto const& v : container_)
    {
        auto const o{function({v})};

        if (o.type() == typeid(typename T::value_type))
            values.emplace_back(std::any_cast<typename T::value_type>(o));
    }

    return T{values.begin(), values.end()};
}

template <typename T>
static std::any repeat(std::any const& item, hodel::Integer const& n)
{
    if (n < 0)
        throw std::runtime_error{"Wrong value"};

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
        return static_cast<hodel::Integer>(std::any_cast<T>(value).size());

    return std::any{};
}

template <typename T>
static std::any init_set(std::any const& value)
{
    if (value.type() == typeid(typename T::value_type))
        return T{std::any_cast<typename T::value_type>(value)};

    return std::any{};
}

template <typename T>
static std::any first_set(std::any const& container)
{
    if (container.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(container)};

        if (x.size())
            return *x.begin();
    }

    return std::any{};
}

template <typename T>
static std::any last_set(std::any const& container)
{
    if (container.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(container)};

        if (x.size())
            return *x.rbegin();
    }

    return std::any{};
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

template <typename T>
static std::any combine_sets(std::any const& a, std::any const& b)
{
    if (a.type() == typeid(T) && b.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(a)};
        auto const y{std::any_cast<T>(b)};
        T result{x};

        result.insert(y.begin(), y.end());

        return result;
    }

    return std::any{};
}

std::any do_op(std::any const& a, std::any const& b, std::function<hodel::Integer(hodel::Integer, hodel::Integer)> const& op)
{
    if (a.type() == typeid(hodel::Numerical) && b.type() == typeid(hodel::Numerical))
    {
        auto const x{std::any_cast<hodel::Numerical>(a)};
        auto const y{std::any_cast<hodel::Numerical>(b)};

        if (std::holds_alternative<hodel::Integer>(x) && std::holds_alternative<hodel::Integer>(y))
            return hodel::Numerical{op(std::get<hodel::Integer>(x), std::get<hodel::Integer>(y))};
        else if (std::holds_alternative<hodel::IntegerTuple>(x) && std::holds_alternative<hodel::IntegerTuple>(y))
        {
            auto const& c{std::get<hodel::IntegerTuple>(x)};
            auto const& d{std::get<hodel::IntegerTuple>(y)};

            return hodel::Numerical{std::make_pair<hodel::Integer, hodel::Integer>(op(c.first, d.first), op(c.second, d.second))};
        }
        else if (std::holds_alternative<hodel::Integer>(x) && std::holds_alternative<hodel::IntegerTuple>(y))
        {
            auto const& c{std::get<hodel::Integer>(x)};
            auto const& d{std::get<hodel::IntegerTuple>(y)};

            return hodel::Numerical{std::make_pair<hodel::Integer, hodel::Integer>(op(c, d.first), op(c, d.second))};
        }
        else if (std::holds_alternative<hodel::IntegerTuple>(x) && std::holds_alternative<hodel::Integer>(y))
        {
            auto const& c{std::get<hodel::IntegerTuple>(x)};
            auto const& d{std::get<hodel::Integer>(y)};

            return hodel::Numerical{std::make_pair<hodel::Integer, hodel::Integer>(op(c.first, d), op(c.second, d))};
        }
    }
    else if (a.type() == typeid(hodel::Integer))
    {
        auto const x{std::any_cast<hodel::Integer>(a)};

        if (b.type() == typeid(hodel::Integer))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::Integer>(b)}, op);
        else if (b.type() == typeid(hodel::IntegerTuple))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::IntegerTuple>(b)}, op);
    }
    else if (a.type() == typeid(hodel::IntegerTuple))
    {
        auto const x{std::any_cast<hodel::IntegerTuple>(a)};

        if (b.type() == typeid(hodel::Integer))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::Integer>(b)}, op);
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

    return do_op(a, b, std::plus<Integer>{});
}

std::any hodel::subtract(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::minus<Integer>{});
}

std::any hodel::multiply(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::multiplies<Integer>{});
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

        if (std::holds_alternative<hodel::Integer>(y))
        {
            if (!std::get<hodel::Integer>(y))
                throw std::runtime_error{"Wrong value"};
        }
        else if (std::holds_alternative<hodel::IntegerTuple>(y))
        {
            auto const& d{std::get<hodel::IntegerTuple>(y)};

            if (!d.first || !d.second)
                throw std::runtime_error{"Wrong value"};
        }
    }
    else if (b.type() == typeid(hodel::Integer))
    {
        auto const y{std::any_cast<hodel::Integer>(b)};

        if (!y)
            throw std::runtime_error{"Wrong value"};
    }
    else if (b.type() == typeid(hodel::IntegerTuple))
    {
        auto const y{std::any_cast<hodel::IntegerTuple>(b)};

        if (!y.first || !y.second)
            throw std::runtime_error{"Wrong value"};
    }

    return do_op(a, b, std::divides<Integer>{});
}

std::any hodel::invert(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const n{args.front()};

    if (n.type() == typeid(Numerical))
    {
        auto const x{std::any_cast<Numerical>(n)};

        if (std::holds_alternative<Integer>(x))
        {
            auto const& y{std::get<Integer>(x)};

            return Integer{-y};
        }
        else if (std::holds_alternative<IntegerTuple>(x))
        {
            auto const& y{std::get<IntegerTuple>(x)};

            return Numerical{std::make_pair<Integer, Integer>(-y.first, -y.second)};
        }
    }
    else if (n.type() == typeid(Integer))
        return invert(std::vector<std::any>{Numerical{std::any_cast<Integer>(n)}});
    else if (n.type() == typeid(IntegerTuple))
        return invert(std::vector<std::any>{Numerical{std::any_cast<IntegerTuple>(n)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::even(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const n{args.front()};

    if (n.type() == typeid(hodel::Integer))
        return Boolean{std::any_cast<Integer>(n) % 2 == 0};

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

        if (std::holds_alternative<Integer>(x))
        {
            auto const& y{std::get<Integer>(x)};

            return Integer{y * 2};
        }
        else if (std::holds_alternative<IntegerTuple>(x))
        {
            auto const& y{std::get<IntegerTuple>(x)};

            return Numerical{std::make_pair<Integer, Integer>(y.first * 2, y.second * 2)};
        }
    }
    else if (n.type() == typeid(Integer))
        return double_(std::vector<std::any>{Numerical{std::any_cast<Integer>(n)}});
    else if (n.type() == typeid(IntegerTuple))
        return double_(std::vector<std::any>{Numerical{std::any_cast<IntegerTuple>(n)}});

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

        if (std::holds_alternative<Integer>(x))
        {
            auto const& y{std::get<Integer>(x)};

            return Integer{y / 2};
        }
        else if (std::holds_alternative<IntegerTuple>(x))
        {
            auto const& y{std::get<IntegerTuple>(x)};

            return Numerical{std::make_pair<Integer, Integer>(y.first / 2, y.second / 2)};
        }
    }
    else if (n.type() == typeid(Integer))
        return halve(std::vector<std::any>{Numerical{std::any_cast<Integer>(n)}});
    else if (n.type() == typeid(IntegerTuple))
        return halve(std::vector<std::any>{Numerical{std::any_cast<IntegerTuple>(n)}});

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
    if (auto r = ::equality<Integer>(a, b); r.has_value()) return r;
    if (auto r = ::equality<IntegerTuple>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Numerical>(a, b); r.has_value()) return r;
    if (auto r = ::equality<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Grid>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Cell>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Object>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Objects>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Indices>(a, b); r.has_value()) return r;
    if (auto r = ::equality<IndicesSet>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Patch>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Element>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Piece>(a, b); r.has_value()) return r;
    if (auto r = ::equality<std::vector<Integer> >(a, b); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::contained(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const value{args[0]};
    auto const container{args[1]};

    if (value.type()     == typeid(Integer)    &&
        container.type() == typeid(IntegerSet))
    {
        auto const v{std::any_cast<Integer>(value)};
        auto const c{std::any_cast<IntegerSet>(container)};

        return static_cast<Boolean>(c.count(v) > 0);
    }
    else if (container.type() == typeid(Object))
    {
        auto const c{std::any_cast<Object>(container)};

        if (value.type() == typeid(Cell))
        {
            auto const v{std::any_cast<Cell>(value)};

            return static_cast<Boolean>(c.count(v) > 0);
        }
    }
    else if (value.type()     == typeid(Object)  &&
             container.type() == typeid(Objects))
    {
        auto const v{std::any_cast<Object>(value)};
        auto const c{std::any_cast<Objects>(container)};

        return static_cast<Boolean>(c.count(v) > 0);
    }
    else if (value.type()     == typeid(IntegerTuple) &&
             container.type() == typeid(Indices))
    {
        auto const v{std::any_cast<IntegerTuple>(value)};
        auto const c{std::any_cast<Indices>(container)};

        return static_cast<Boolean>(c.count(v) > 0);
    }
    else if (value.type()     == typeid(Indices)    &&
             container.type() == typeid(IndicesSet))
    {
        auto const v{std::any_cast<Indices>(value)};
        auto const c{std::any_cast<IndicesSet>(container)};

        return static_cast<Boolean>(c.count(v) > 0);
    }
    else if (value.type()     == typeid(Patch)   &&
             container.type() == typeid(Objects))
    {
        auto const p{std::any_cast<Patch>(value)};
        auto const c{std::any_cast<Objects>(container)};

        if (std::holds_alternative<Object>(p))
            return static_cast<Boolean>(c.count(std::get<Object>(p)) > 0);
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::combine(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = combine_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = combine_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = combine_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = combine_sets<Indices>   (a, b); r.has_value()) return r;
    if (auto r = combine_sets<IndicesSet>(a, b); r.has_value()) return r;

    if (a.type() == typeid(Grid) && b.type() == typeid(Grid))
    {
        auto const x{std::any_cast<Grid>(a)};
        auto const y{std::any_cast<Grid>(b)};
        Grid result{x};

        result.insert(result.end(), y.begin(), y.end());

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::intersection(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = intersection_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Indices>   (a, b); r.has_value()) return r;
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
    if (auto r = difference_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Indices>   (a, b); r.has_value()) return r;
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

        if (std::holds_alternative<Grid>(x))
            return dedupe(std::vector<std::any>{std::get<Grid>(x)});
    }
    else if (tup.type() == typeid(Piece))
    {
        auto const x{std::any_cast<Piece>(tup)};

        if (std::holds_alternative<Grid>(x))
            return dedupe(std::vector<std::any>{std::get<Grid>(x)});
    }
    else if (tup.type() == typeid(Grid))
    {
        auto const x{std::any_cast<Grid>(tup)};
        Grid y;
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

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    if (auto r = ::order<IntegerSet>(container, f); r.has_value()) return r;
    if (auto r = ::order<std::vector<Integer> >(container, f); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::repeat(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const item{args[0]};
    auto const num{args[1]};

    if (num.type() == typeid(Integer))
    {
        auto const n{std::any_cast<Integer>(num)};
       
        if (n < 0)
            throw std::runtime_error{"Wrong value"};

        if (auto r = ::repeat<Integer>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<IntegerTuple>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Boolean>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Numerical>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Grid>(item, n); r.has_value()) return r;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::greater(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Integer) && b.type() == typeid(Integer))
        return Boolean{std::any_cast<Integer>(a) > std::any_cast<Integer>(b)};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::size(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (auto r = size_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = size_set<Object>    (container); r.has_value()) return r;
    if (auto r = size_set<Objects>   (container); r.has_value()) return r;
    if (auto r = size_set<Indices>   (container); r.has_value()) return r;
    if (auto r = size_set<IndicesSet>(container); r.has_value()) return r;
    if (auto r = size_set<std::vector<Integer> >(container); r.has_value()) return r;

    if (container.type() == typeid(Grid))
    {
        auto const x{std::any_cast<Grid>(container)};
        
        return static_cast<Integer>(x.size());
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
            return Integer{0};
        
        return *std::max_element(set.begin(), set.end());
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
            return Integer{0};
        
        return *std::min_element(set.begin(), set.end());
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

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    std::vector<std::any> values;

    if (container.type() == typeid(IntegerSet))
        values = toVector(std::any_cast<IntegerSet>(container));
    else if (container.type() == typeid(std::vector<Integer>))
        values = toVector(std::any_cast<std::vector<Integer> >(container));

    try
    {
        for (auto& v : values)
            v = f({v});

        auto const it{std::max_element(values.begin(), values.end(), [f] (auto const& x, auto const& y) -> auto { return std::any_cast<Boolean>(greater({y, x})); } )};

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

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    std::vector<std::any> values;

    if (container.type() == typeid(IntegerSet))
        values = toVector(std::any_cast<IntegerSet>(container));
    else if (container.type() == typeid(std::vector<Integer>))
        values = toVector(std::any_cast<std::vector<Integer> >(container));

    try
    {
        for (auto& v : values)
            v = f({v});

        auto const it{std::min_element(values.begin(), values.end(), [f] (auto const& x, auto const& y) -> auto { return std::any_cast<Boolean>(greater({y, x})); } )};

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

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    std::vector<std::any> values;

    if (container.type() == typeid(IntegerSet))
        values = toVector(std::any_cast<IntegerSet>(container));
    else if (container.type() == typeid(std::vector<Integer>))
        values = toVector(std::any_cast<std::vector<Integer> >(container));

    try
    {
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

    auto const f{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(compfunc)};

    std::vector<std::any> values;

    if (container.type() == typeid(IntegerSet))
        values = toVector(std::any_cast<IntegerSet>(container));
    else if (container.type() == typeid(std::vector<Integer>))
        values = toVector(std::any_cast<std::vector<Integer> >(container));

    try
    {
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

std::any hodel::mostcommon(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};

    if (container.type() == typeid(std::vector<Integer>))
    {
        auto const container_{std::any_cast<std::vector<Integer> >(container)};

        if (container_.empty())
            throw std::runtime_error{"Wrong value"};

        std::unordered_map<Integer, Integer> counts;

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

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::leastcommon(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args[0]};

    if (container.type() == typeid(std::vector<Integer>))
    {
        auto const container_{std::any_cast<std::vector<Integer> >(container)};

        if (container_.empty())
            throw std::runtime_error{"Wrong value"};

        std::unordered_map<Integer, Integer> counts;

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

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::initset(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const value{args.front()};

    if (auto r = init_set<IntegerSet>(value); r.has_value()) return r;
    if (auto r = init_set<Object>    (value); r.has_value()) return r;
    if (auto r = init_set<Objects>   (value); r.has_value()) return r;
    if (auto r = init_set<Indices>   (value); r.has_value()) return r;
    if (auto r = init_set<IndicesSet>(value); r.has_value()) return r;
    if (auto r = init_set<std::vector<Integer> >(value); r.has_value()) return r;

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

    if (x.type() == typeid(Numerical))
    {
        auto const y{std::any_cast<Numerical>(x)};

        if (std::holds_alternative<Integer>(y))
            return Numerical{std::get<Integer>(y) + 1};
        else if (std::holds_alternative<IntegerTuple>(y))
        {
            auto const z{std::get<IntegerTuple>(y)};

            return Numerical{std::make_pair<Integer, Integer>(z.first + 1, z.second + 1)};
        }
    }
    else if (x.type() == typeid(Integer))
        return increment(std::vector<std::any>{Numerical{std::any_cast<Integer>(x)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::decrement(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    if (x.type() == typeid(Numerical))
    {
        auto const y{std::any_cast<Numerical>(x)};

        if (std::holds_alternative<Integer>(y))
            return Numerical{std::get<Integer>(y) - 1};
        else if (std::holds_alternative<IntegerTuple>(y))
        {
            auto const z{std::get<IntegerTuple>(y)};

            return Numerical{std::make_pair<Integer, Integer>(z.first - 1, z.second - 1)};
        }
    }
    else if (x.type() == typeid(Integer))
        return decrement(std::vector<std::any>{Numerical{std::any_cast<Integer>(x)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::crement(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    if (x.type() == typeid(Numerical))
    {
        auto const y{std::any_cast<Numerical>(x)};

        if (std::holds_alternative<Integer>(y))
        {
            auto const z{std::get<Integer>(y)};

            if (!z)
                return Numerical{z};
            else if (z > 0)
                return increment(args);
            else
                return decrement(args);
        }
        else if (std::holds_alternative<IntegerTuple>(y))
        {
            auto const z{std::get<IntegerTuple>(y)};
            IntegerTuple result{std::make_pair<Integer, Integer>(0, 0)};

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

            return Numerical{result};
        }
    }
    else if (x.type() == typeid(Integer))
        return crement(std::vector<std::any>{Numerical{std::any_cast<Integer>(x)}});

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

        if (std::holds_alternative<Integer>(y))
        {
            auto const z{std::get<Integer>(y)};

            if (!z)
                return Numerical{0};
            else if (z > 0)
                return Numerical{1};
            else
                return Numerical{-1};
        }
        else if (std::holds_alternative<IntegerTuple>(y))
        {
            auto const z{std::get<IntegerTuple>(y)};
            IntegerTuple result{std::make_pair<Integer, Integer>(0, 0)};

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

            return Numerical{result};
        }
    }
    else if (x.type() == typeid(Integer))
        return sign(std::vector<std::any>{Numerical{std::any_cast<Integer>(x)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::positive(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const x{args.front()};

    if (x.type() == typeid(Integer))
        return Boolean{std::any_cast<Integer>(x) > 0};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::toivec(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const i{args.front()};

    if (i.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(std::any_cast<Integer>(i), 0)};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::tojvec(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const j{args.front()};

    if (j.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(0, std::any_cast<Integer>(j))};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::totuple(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (auto r = vector_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = vector_set<Object>    (container); r.has_value()) return r;
    if (auto r = vector_set<Objects>   (container); r.has_value()) return r;
    if (auto r = vector_set<Indices>   (container); r.has_value()) return r;
    if (auto r = vector_set<IndicesSet>(container); r.has_value()) return r;
    if (auto r = vector_set<std::vector<Integer> >(container); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::first(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (auto r = first_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = first_set<Object>    (container); r.has_value()) return r;
    if (auto r = first_set<Objects>   (container); r.has_value()) return r;
    if (auto r = first_set<Indices>   (container); r.has_value()) return r;
    if (auto r = first_set<IndicesSet>(container); r.has_value()) return r;
    if (auto r = first_set<std::vector<Integer> >(container); r.has_value()) return r;

    if (container.type() == typeid(Grid))
    {
        auto const x{std::any_cast<Grid>(container)};
        
        if (x.empty())
            throw std::runtime_error{"Wrong value"};

        return x.front();
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::last(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const container{args.front()};

    if (auto r = last_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = last_set<Object>    (container); r.has_value()) return r;
    if (auto r = last_set<Objects>   (container); r.has_value()) return r;
    if (auto r = last_set<Indices>   (container); r.has_value()) return r;
    if (auto r = last_set<IndicesSet>(container); r.has_value()) return r;
    if (auto r = last_set<std::vector<Integer> >(container); r.has_value()) return r;

    if (container.type() == typeid(Grid))
    {
        auto const x{std::any_cast<Grid>(container)};

        if (x.empty())
            throw std::runtime_error{"Wrong value"};

        return x.back();
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::interval(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const start{args[0]};
    auto const stop{args[1]};
    auto const step{args[2]};

    if (start.type() == typeid(Integer) && stop.type() == typeid(Integer) && step.type() == typeid(Integer))
    {
        auto start_{std::any_cast<Integer>(start)};
        auto const stop_{std::any_cast<Integer>(stop)};
        auto const step_{std::any_cast<Integer>(step)};
        std::vector<Integer> result;

        if ((step_ >= 0 && stop_ < start_) || (step_ <= 0 && stop_ > start_))
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

    if (a.type() == typeid(Integer) && b.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(std::any_cast<Integer>(a), std::any_cast<Integer>(b))};

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
            return equality(std::vector<std::any>{f(args), target});
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
            std::vector<std::any> new_args{args};
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

    if (function.type() == typeid(std::function<std::any(std::vector<std::any> const&)>) && n.type() == typeid(Integer))
    {
        auto const n_{std::any_cast<Integer>(n)};

        if (n_ <= 0)
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

std::any hodel::apply(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const function{args[0]};
    auto const container{args[1]};

    if (function.type() != typeid(std::function<std::any(std::vector<std::any> const&)>))
        throw std::runtime_error{"Wrong value"};

    auto const function_{std::any_cast<std::function<std::any(std::vector<std::any> const&)> >(function)};

    if (auto r = ::apply<IntegerSet>(function_, container); r.has_value()) return r;
    if (auto r = ::apply<Object>    (function_, container); r.has_value()) return r;
    if (auto r = ::apply<Objects>   (function_, container); r.has_value()) return r;
    if (auto r = ::apply<Indices>   (function_, container); r.has_value()) return r;
    if (auto r = ::apply<IndicesSet>(function_, container); r.has_value()) return r;
    if (auto r = ::apply<std::vector<Integer> >(function_, container); r.has_value()) return r;
    if (auto r = ::apply<Grid>(function_, container); r.has_value()) return r;

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::mostcolor(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const element{args[0]};

    if (element.type() != typeid(Element))
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

    if (element.type() != typeid(Element))
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

        if (std::holds_alternative<Grid>(piece_))
        {
            auto const grid{std::get<Grid>(piece_)};

            if (grid.size() == 0)
                return 0;

            return grid.size();
        }
        else if (std::holds_alternative<Patch>(piece_))
        {
            auto const lm{std::any_cast<Integer>(lowermost(args))};
            auto const um{std::any_cast<Integer>(uppermost(args))};

            return lm - um + 1;
        }
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

        if (std::holds_alternative<Grid>(piece_))
        {
            auto const grid{std::get<Grid>(piece_)};

            if (grid.size() == 0)
                return 0;

            return grid[0].size();
        }
        else if (std::holds_alternative<Patch>(piece_))
        {
            auto const rm{std::any_cast<Integer>(rightmost(args))};
            auto const lm{std::any_cast<Integer>(leftmost(args))};

            return rm - lm + 1;
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::shape(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
        return IntegerTuple{std::any_cast<Integer>(height(args)), std::any_cast<Integer>(width(args))};

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::portrait(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const piece{args[0]};

    if (piece.type() == typeid(Piece))
    {
        auto const h{std::any_cast<Integer>(height(args))};
        auto const w{std::any_cast<Integer>(width(args))};

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

    if (element.type() == typeid(Element) && value.type() == typeid(Integer))
    {
        auto const element_{std::any_cast<Element>(element)};
        auto const value_{std::any_cast<Integer>(value)};

        Integer count = 0;

        if (std::holds_alternative<Grid>(element_))
        {
            auto const grid{std::get<Grid>(element_)};

            for (auto const& row : grid)
                count += static_cast<Integer>(std::count(row.begin(), row.end(), value_));
        }
        else
        {
            auto const& object{std::get<Object>(element_)};

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

std::any hodel::asindices(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        Indices indices;

        if (grid_.empty())
            return indices;

        for (Integer i{0}; i < static_cast<Integer>(grid_.size()); ++i)
        {
            for (Integer j{0}; j < static_cast<Integer>(grid_[0].size()); ++j)
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

    if (grid.type() == typeid(Grid) && value.type() == typeid(Integer))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const value_{std::any_cast<Integer>(value)};

        Indices indices;

        for (Integer i{0}; i < static_cast<Integer>(grid_.size()); ++i)
        {
            for (Integer j{0}; j < static_cast<Integer>(grid_[i].size()); ++j)
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

        if (std::holds_alternative<Object>(patch_))
            return ulcorner(std::vector<std::any>{Patch{std::any_cast<Indices>(toindices(args))}});
        else if (std::holds_alternative<Indices>(patch_))
        {
            auto const indices{std::get<Indices>(patch_)};
            auto min_y = std::numeric_limits<Integer>::max();
            auto min_x = std::numeric_limits<Integer>::max();

            for (auto const& [y, x] : indices)
            {
                min_y = std::min(min_y, y);
                min_x = std::min(min_x, x);
            }

            return IntegerTuple{min_y, min_x};
        }
    }
    else if (patch.type() == typeid(Object))
        return ulcorner(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return ulcorner(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

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

        if (std::holds_alternative<Object>(patch_))
            return urcorner(std::vector<std::any>{Patch{std::any_cast<Indices>(toindices(args))}});
        else if (std::holds_alternative<Indices>(patch_))
        {
            auto const indices{std::get<Indices>(patch_)};
            auto min_y = std::numeric_limits<Integer>::max();
            auto max_x = std::numeric_limits<Integer>::lowest();

            for (auto const& [y, x] : indices)
            {

                min_y = std::min(min_y, y);
                max_x = std::max(max_x, x);
            }

            return IntegerTuple{min_y, max_x};
        }
    }
    else if (patch.type() == typeid(Object))
        return urcorner(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return urcorner(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

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

        if (std::holds_alternative<Object>(patch_))
            return llcorner(std::vector<std::any>{Patch{std::any_cast<Indices>(toindices(args))}});
        else if (std::holds_alternative<Indices>(patch_))
        {
            auto const indices{std::get<Indices>(patch_)};
            auto max_y = std::numeric_limits<Integer>::lowest();
            auto min_x = std::numeric_limits<Integer>::max();

            for (auto const& [y, x] : indices)
            {
                max_y = std::max(max_y, y);
                min_x = std::min(min_x, x);
            }

            return IntegerTuple{max_y, min_x};
        }
    }
    else if (patch.type() == typeid(Object))
        return llcorner(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return llcorner(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

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

        if (std::holds_alternative<Object>(patch_))
            return lrcorner(std::vector<std::any>{Patch{std::any_cast<Indices>(toindices(args))}});
        else if (std::holds_alternative<Indices>(patch_))
        {
            auto const indices{std::get<Indices>(patch_)};
            auto max_y = std::numeric_limits<Integer>::lowest();
            auto max_x = std::numeric_limits<Integer>::lowest();

            for (auto const& [y, x] : indices)
            {
                max_y = std::max(max_y, y);
                max_x = std::max(max_x, x);
            }

            return IntegerTuple{max_y, max_x};
        }
    }
    else if (patch.type() == typeid(Object))
        return lrcorner(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return lrcorner(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::crop(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const start{args[1]};
    auto const dims{args[2]};

    if (grid.type() == typeid(Grid) && start.type() == typeid(IntegerTuple) && dims.type() == typeid(IntegerTuple))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const start_{std::any_cast<IntegerTuple>(start)};
        auto const dims_{std::any_cast<IntegerTuple>(dims)};

        if (dims_.first < 0 || dims_.second < 0 || start_.first < 0 || start_.second < 0 || start_.first + dims_.first > grid_.size() || start_.second + dims_.second > grid_[0].size())
            throw std::runtime_error{"Wrong value"};

        Grid result;

        try
        {
            for (size_t i{0}; i < dims_.first; ++i)
            {
                std::vector<Integer> row;

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

        if (std::holds_alternative<Indices>(patch_))
            return std::get<Indices>(patch_);

        auto const& obj = std::get<Object>(patch_);

        if (obj.empty())
            throw std::runtime_error{"Wrong value"};

        Indices result;

        for (auto const& cell : obj)
            result.insert(cell.second);

        return result;
    }
    else if (patch.type() == typeid(Object))
        return toindices(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return toindices(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::recolor(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const value{args[0]};
    auto const patch{args[1]};

    if (value.type() == typeid(Integer) && patch.type() == typeid(Patch))
    {
        auto const value_{std::any_cast<Integer>(value)};

        try
        {
            Object object;

            for (auto const& index : std::any_cast<Indices>(toindices({patch})))
                object.emplace(value_, index);

            return object;
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

        if (std::holds_alternative<Object>(patch_) && std::get<Object>(patch_).empty())
            return patch;

        if (std::holds_alternative<Indices>(patch_) && std::get<Indices>(patch_).empty())
            return patch;

        auto const& [di, dj] = directions_;

        if (std::holds_alternative<Object>(patch_))
        {
            auto const& obj = std::get<Object>(patch_);
            Object result;

            for (auto const& [value, pos] : obj)
            {
                auto const& [i, j] = pos;

                result.insert({value, {i + di, j + dj}});
            }

            return Patch{result};
        }

        auto const& indices = std::get<Indices>(patch_);
        Indices result;

        for (auto const& [i, j] : indices)
            result.insert({i + di, j + dj});

        return Patch{result};
    }
    else if (patch.type() == typeid(Object))
        return shift(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}, directions});
    else if (patch.type() == typeid(Indices))
        return shift(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}, directions});

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

        return Indices{
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

        return Indices{
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
            auto result{std::any_cast<Indices>(dneighbors({loc}))};
            auto const diagonal{std::any_cast<Indices>(ineighbors({loc}))};

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

std::any hodel::uppermost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
        auto const indices = std::any_cast<Indices>(toindices(args));
        auto result = std::numeric_limits<Integer>::max();

        for (auto const& [i, j] : indices)
            result = std::min(result, i);

        return result;
    }
    else if (patch.type() == typeid(Object))
        return shift(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return shift(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

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
        auto const indices = std::any_cast<Indices>(toindices(args));
        auto result = std::numeric_limits<Integer>::max();

        for (auto const& [i, j] : indices)
            result = std::max(result, i);

        return result;
    }
    else if (patch.type() == typeid(Object))
        return shift(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return shift(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

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
        auto const indices = std::any_cast<Indices>(toindices(args));
        auto result = std::numeric_limits<Integer>::max();

        for (auto const& [i, j] : indices)
            result = std::min(result, j);

        return result;
    }
    else if (patch.type() == typeid(Object))
        return shift(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return shift(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

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
        auto const indices = std::any_cast<Indices>(toindices(args));
        auto result = std::numeric_limits<Integer>::min();

        for (auto const& [i, j] : indices)
            result = std::max(result, j);

        return result;
    }
    else if (patch.type() == typeid(Object))
        return shift(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return shift(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

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
            
            if (std::holds_alternative<Grid>(piece_))
            {
                auto const grid{std::get<Grid>(piece_)};

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
                auto const h{std::any_cast<Integer>(height(args))};
                auto const w{std::any_cast<Integer>(width(args))};
                auto const patch{std::get<Patch>(piece_)};
                auto const l{static_cast<Integer>(std::holds_alternative<Object>(patch) ? std::get<Object>(patch).size() : std::get<Indices>(patch).size())};

                return Boolean{h * w == l and h == w};
            }
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

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
            auto const h{std::any_cast<Integer>(height(args))};
            auto const w{std::any_cast<Integer>(width(args))};
            auto const patch_{std::any_cast<Patch>(patch)};
            auto const l{static_cast<Integer>(std::holds_alternative<Object>(patch_) ? std::get<Object>(patch_).size() : std::get<Indices>(patch_).size())};

            return Boolean{h == l && w == 1};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

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
            auto const h{std::any_cast<Integer>(height(args))};
            auto const w{std::any_cast<Integer>(width(args))};
            auto const patch_{std::any_cast<Patch>(patch)};
            auto const l{static_cast<Integer>(std::holds_alternative<Object>(patch_) ? std::get<Object>(patch_).size() : std::get<Indices>(patch_).size())};

            return Boolean{w == l && h == 1};
        }
        catch (std::exception const&)
        {
            throw std::runtime_error{"Wrong value"};
        }
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hmatching(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        try
        {
            std::set<Integer> rows;

            for (auto const& [i, j] : std::any_cast<Indices>(toindices({a})))
                rows.insert(i);

            for (auto const& [i, j] : std::any_cast<Indices>(toindices({b})))
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

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        try
        {
            std::set<Integer> cols;

            for (auto const& [i, j] : std::any_cast<Indices>(toindices({a})))
                cols.insert(j);

            for (auto const& [i, j] : std::any_cast<Indices>(toindices({b})))
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

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        try
        {
            auto dmin{std::numeric_limits<Integer>::max()};

            for (auto const& [ai, aj] : std::any_cast<Indices>(toindices({a})))
            {
                for (auto const& [bi, bj] : std::any_cast<Indices>(toindices({b})))
                {
                    Integer const d{std::abs(ai - bi) + std::abs(aj - bj)};
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

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Patch) && b.type() == typeid(Patch))
    {
        try
        {
            return Boolean{std::any_cast<Integer>(manhattan(args)) == 1};
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

    if (patch.type() == typeid(Patch) && grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        try
        {
            auto const urm{std::any_cast<Integer>(uppermost({patch}))};
            auto const ltm{std::any_cast<Integer>(leftmost({patch}))};
            auto const lrm{std::any_cast<Integer>(lowermost({patch}))};
            auto const rtm{std::any_cast<Integer>(rightmost({patch}))};

            return Boolean{urm == 0 || ltm == 0 || lrm == static_cast<Integer>(grid_.size()) - 1 || rtm == static_cast<Integer>(grid_.at(0).size()) - 1};
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

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};
        auto const l{static_cast<Integer>(std::holds_alternative<Object>(patch_) ? std::get<Object>(patch_).size() : std::get<Indices>(patch_).size())};

        try
        {
            Integer sumRow{0};
            Integer sumCol{0};

            for (auto const& [i, j] : std::any_cast<Indices>(toindices(args)))
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

    if (element.type() == typeid(Element))
    {
        auto const element_{std::any_cast<Element>(element)};

        IntegerSet colors;

        if (std::holds_alternative<Grid>(element_))
        {
            auto const& grid{std::get<Grid>(element_)};

            for (auto const& row : grid)
                colors.insert(row.begin(), row.end());
        }
        else if (std::holds_alternative<Object>(element_))
        {
            auto const& object{std::get<Object>(element_)};

            for (auto const& [color, position] : object)
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

    if (element.type() == typeid(Element))
    {
        try
        {
            return static_cast<Integer>(std::any_cast<IntegerSet>(palette(args)).size());
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

    if (object.type() == typeid(Object))
    {
        auto const& object_{std::any_cast<Object>(object)};

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

    if (patch.type() == typeid(Patch) && grid.type() == typeid(Grid))
    {
        auto const& patch_{std::any_cast<Patch>(patch)};
        auto const& grid_{std::any_cast<Grid>(grid)};

        try
        {
            auto const h{std::any_cast<Integer>(grid_.size())};
            auto const w{std::any_cast<Integer>(grid_.at(0).size())};

            Object object;

            if (grid_.empty())
                return object;

            for (auto const& [i, j] : std::any_cast<Indices>(toindices({patch})))
            {
                if (0 <= i && i < h && 0 <= j && j < w)
                    object.emplace(grid_.at(i).at(j), IntegerTuple{i, j});
            }

            return object;
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

    if (grid.type() == typeid(Grid))
    {
        auto const& grid_{std::any_cast<Grid>(grid)};

        try
        {
            Object object;

            for (Integer i = 0; i < static_cast<Integer>(grid_.size()); ++i)
            {
                for (Integer j = 0; j < static_cast<Integer>(grid_.at(i).size()); ++j)
                    object.emplace(grid_.at(i).at(j), IntegerTuple{i, j});
            }

            return object;
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

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        auto const rows{static_cast<int>(grid_.size())};
        auto const cols{static_cast<int>(grid_[0].size())};

        Grid result(cols, std::vector<int>(rows));

        try
        {
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
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

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        auto const rows{static_cast<int>(grid_.size())};
        auto const cols{static_cast<int>(grid_[0].size())};

        Grid result(rows, std::vector<int>(cols));

        try
        {
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
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

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        if (grid_.empty())
            throw std::runtime_error{"Wrong value"};

        auto const rows{static_cast<int>(grid_.size())};
        auto const cols{static_cast<int>(grid_[0].size())};

        Grid result(cols, std::vector<int>(rows));

        try
        {
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
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

        if (std::holds_alternative<Grid>(piece_))
        {
            auto grid = std::get<Grid>(piece_);

            std::reverse(grid.begin(), grid.end());

            return Piece{grid};
        }

        auto patch = std::get<Patch>(piece_);
        auto const ulc = std::any_cast<IntegerTuple>(ulcorner(std::vector<std::any>{patch}));
        auto const lrc = std::any_cast<IntegerTuple>(lrcorner(std::vector<std::any>{patch}));

        auto const d = ulc.first + lrc.first;

        if (std::holds_alternative<Object>(patch))
        {
            auto const& obj = std::get<Object>(patch);

            Object result;

            for (auto const& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {d - i, j}});
            }

            return Piece{Patch(result)};
        }

        auto const& indices = std::get<Indices>(patch);

        Indices result;

        for (auto const& [i, j] : indices)
            result.insert({d - i, j});

        return Piece{Patch(result)};
    }
    else if (piece.type() == typeid(Grid))
        return hmirror(std::vector<std::any>{Piece{std::any_cast<Grid>(piece)}});
    else if (piece.type() == typeid(Patch))
        return hmirror(std::vector<std::any>{Piece{std::any_cast<Patch>(piece)}});

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

        if (std::holds_alternative<Grid>(piece_))
        {
            auto grid = std::get<Grid>(piece_);

            for (auto& row : grid)
                std::reverse(row.begin(), row.end());

            return Piece{grid};
        }

        auto patch = std::get<Patch>(piece_);
        auto const ulc = std::any_cast<IntegerTuple>(ulcorner(std::vector<std::any>{patch}));
        auto const lrc = std::any_cast<IntegerTuple>(lrcorner(std::vector<std::any>{patch}));

        auto const d = ulc.second + lrc.second;

        if (std::holds_alternative<Object>(patch))
        {
            auto const& obj = std::get<Object>(patch);

            Object result;

            for (auto const& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {i, d - j}});
            }

            return Piece{Patch(result)};
        }

        auto const& indices = std::get<Indices>(patch);

        Indices result;

        for (auto const& [i, j] : indices)
            result.insert({i, d - j});

        return Piece{Patch(result)};
    }
    else if (piece.type() == typeid(Grid))
        return vmirror(std::vector<std::any>{Piece{std::any_cast<Grid>(piece)}});
    else if (piece.type() == typeid(Patch))
        return vmirror(std::vector<std::any>{Piece{std::any_cast<Patch>(piece)}});

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

        if (std::holds_alternative<Grid>(piece_))
        {
            auto const& grid = std::get<Grid>(piece_);

            if (grid.empty())
                return Piece{Grid{}};

            auto const rows = static_cast<int>(grid.size());
            auto const cols = static_cast<int>(grid[0].size());

            Grid result(cols, std::vector<int>(rows));

            try
            {
                for (int i = 0; i < rows; ++i)
                {
                    for (int j = 0; j < cols; ++j)
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

        auto [a, b] = std::any_cast<IntegerTuple>(ulcorner(std::vector<std::any>{patch}));

        if (std::holds_alternative<Object>(patch))
        {
            auto const& obj = std::get<Object>(patch);

            Object result;

            for (auto const& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {j - b + a, i - a + b}});
            }

            return Piece{Patch(result)};
        }

        auto const& indices = std::get<Indices>(patch);

        Indices result;

        for (auto const& [i, j] : indices)
            result.insert({j - b + a, i - a + b});

        return Piece{Patch(result)};
    }
    else if (piece.type() == typeid(Grid))
        return dmirror(std::vector<std::any>{Piece{std::any_cast<Grid>(piece)}});
    else if (piece.type() == typeid(Patch))
        return dmirror(std::vector<std::any>{Piece{std::any_cast<Patch>(piece)}});

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

        if (std::holds_alternative<Grid>(piece_))
        {
            auto grid = std::get<Grid>(piece_);

            std::reverse(grid.begin(), grid.end());

            for (auto& row : grid)
                std::reverse(row.begin(), row.end());

            return dmirror(std::vector<std::any>{Piece{grid}});
        }

        return vmirror(std::vector<std::any>{dmirror(std::vector<std::any>{vmirror(args)})});
    }
    else if (piece.type() == typeid(Grid))
        return cmirror(std::vector<std::any>{Piece{std::any_cast<Grid>(piece)}});
    else if (piece.type() == typeid(Patch))
        return cmirror(std::vector<std::any>{Piece{std::any_cast<Patch>(piece)}});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hupscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const factor{args[1]};

    if (grid.type() == typeid(Grid) && factor.type() == typeid(Integer))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const factor_{std::any_cast<Integer>(factor)};

        if (factor_ < 0)
            throw std::runtime_error{"Wrong value"};

        Grid result;

        for (auto const& row : grid_)
        {
            std::vector<Integer> new_row;
            new_row.reserve(row.size() * factor_);

            for (auto const& cell : row)
            {
                for (Integer i{0}; i < factor_; ++i)
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

    if (grid.type() == typeid(Grid) && factor.type() == typeid(Integer))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const factor_{std::any_cast<Integer>(factor)};

        if (factor_ < 0)
            throw std::runtime_error{"Wrong value"};

        Grid result;
        result.reserve(grid_.size() * factor_);

        for (auto const& row : grid_)
        {
            for (Integer k = 0; k < factor_; ++k)
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

    if (element.type() == typeid(Element) && factor.type() == typeid(Integer))
    {
        auto const element_{std::any_cast<Element>(element)};
        auto const factor_{std::any_cast<Integer>(factor)};

        if (factor_ < 0)
            throw std::runtime_error{"Wrong value"};

        if (std::holds_alternative<Grid>(element_))
        {
            auto const& grid = std::get<Grid>(element_);

            Grid result;

            for (auto const& row : grid)
            {
                std::vector<Integer> upscaled_row;

                upscaled_row.reserve(row.size() * factor_);

                for (auto const& value : row)
                {
                    for (Integer k = 0; k < factor_; ++k)
                        upscaled_row.emplace_back(value);
                }

                for (Integer k = 0; k < factor_; ++k)
                    result.emplace_back(upscaled_row);
            }

            return Element{result};
        }

        auto const& obj = std::get<Object>(element_);

        if (obj.empty())
            return Element{Object{}};

        auto const [di_inv, dj_inv] = std::any_cast<IntegerTuple>(ulcorner(std::vector<std::any>{element}));
        Integer const di = -di_inv;
        Integer const dj = -dj_inv;

        Patch const p = std::any_cast<Patch>(shift(std::vector<std::any>{Patch{obj}, IntegerTuple{di, dj}}));
        Object normed_obj = std::get<Object>(p);
        Object result;

        for (auto const& [value, pos] : normed_obj)
        {
            auto const& [i, j] = pos;

            for (Integer io = 0; io < factor_; ++io)
            {
                for (Integer jo = 0; jo < factor_; ++jo)
                    result.insert({value, {i * factor_ + io, j * factor_ + jo}});
            }
        }

        return shift(std::vector<std::any>{Patch{result}, IntegerTuple{di_inv, dj_inv}});
    }
    else if (element.type() == typeid(Grid))
        return upscale(std::vector<std::any>{Element{std::any_cast<Grid>(element)}, factor});
    else if (element.type() == typeid(Object))
        return upscale(std::vector<std::any>{Element{std::any_cast<Object>(element)}, factor});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::downscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const factor{args[1]};

    if (grid.type() == typeid(Grid) && factor.type() == typeid(Integer))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const factor_{std::any_cast<Integer>(factor)};

        if (factor_ <= 0)
            throw std::runtime_error{"Wrong value"};

        if (grid_.empty())
            return grid_;

        try
        {
            auto const h = static_cast<Integer>(grid_.size());
            auto const w = static_cast<Integer>(grid_.at(0).size());

            Grid temp;

            for (Integer i = 0; i < h; ++i)
            {
                std::vector<Integer> row;

                for (Integer j = 0; j < w; ++j)
                {
                    if (j % factor_ == 0)
                        row.emplace_back(grid_.at(i).at(j));
                }

                temp.emplace_back(row);
            }

            Grid result;

            for (Integer i = 0; i < static_cast<Integer>(temp.size()); ++i)
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

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Grid) && b.type() == typeid(Grid))
    {
        auto const a_{std::any_cast<Grid>(a)};
        auto const b_{std::any_cast<Grid>(b)};

        Grid result;
        auto const rows = std::min(a_.size(), b_.size());
        result.reserve(rows);

        for (size_t i = 0; i < rows; ++i)
        {
            std::vector<Integer> row;
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

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Grid) && b.type() == typeid(Grid))
    {
        auto const a_{std::any_cast<Grid>(a)};
        auto const b_{std::any_cast<Grid>(b)};

        Grid result;
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

    if (patch.type() == typeid(Patch) && grid.type() == typeid(Grid))
        return crop({grid, ulcorner({patch}), shape({patch})});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::hsplit(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};
    auto const n{args[1]};

    if (grid.type() == typeid(Grid) && n.type() == typeid(Integer))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const n_{std::any_cast<Integer>(n)};

        if (grid_.empty() || n_ <= 0)
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h{static_cast<Integer>(grid_.size())};
            auto const w{static_cast<Integer>(grid_.at(0).size()) / n_};
            Integer const offset{(grid_.at(0).size() % n_ != 0)};

            std::vector<Grid> result;
            result.reserve(n_);

            for (Integer i = 0; i < n_; ++i)
                result.emplace_back(std::any_cast<Grid>(crop({grid_, IntegerTuple{0, w * i + i * offset}, IntegerTuple{h, w}})));

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

    if (grid.type() == typeid(Grid) && n.type() == typeid(Integer))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const n_{std::any_cast<Integer>(n)};

        if (grid_.empty() || n_ <= 0)
            throw std::runtime_error{"Wrong value"};

        try
        {
            auto const h{static_cast<Integer>(grid_.size()) / n_};
            auto const w{static_cast<Integer>(grid_.at(0).size())};
            Integer const offset{(grid_.size() % n_ != 0)};

            std::vector<Grid> result;
            result.reserve(n_);

            for (Integer i = 0; i < n_; ++i)
                result.emplace_back(std::any_cast<Grid>(crop({grid_, IntegerTuple{h * i + i * offset, 0}, IntegerTuple{h, w}})));

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

    auto const a{args[0]};
    auto const b{args[1]};
    auto const fallback{args[2]};

    if (a.type() == typeid(Grid) && b.type() == typeid(Grid) && fallback.type() == typeid(Integer))
    {
        auto const a_{std::any_cast<Grid>(a)};
        auto const b_{std::any_cast<Grid>(b)};
        auto const fallback_{std::any_cast<Integer>(fallback)};

        try
        {
            auto const h{static_cast<Integer>(a_.size())};
            auto const w{static_cast<Integer>(a_.at(0).size())};

            Grid result(h, std::vector<Integer>(w));

            for (Integer i{0}; i < h; ++i)
            {
                for (Integer j{0}; j < w; ++j)
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

    if (grid.type() == typeid(Grid) && replacee.type() == typeid(Integer) && replacer.type() == typeid(Integer))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const replacee_{std::any_cast<Integer>(replacee)};
        auto const replacer_{std::any_cast<Integer>(replacer)};

        Grid result = grid_;

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

    if (grid.type() == typeid(Grid) && a.type() == typeid(Integer) && b.type() == typeid(Integer))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const a_{std::any_cast<Integer>(a)};
        auto const b_{std::any_cast<Integer>(b)};

        Grid result = grid_;

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

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        try
        {
            auto const um{std::any_cast<Integer>(uppermost(args))};
            auto const h{std::any_cast<Integer>(height(args))};
            auto const lm{std::any_cast<Integer>(leftmost(args))};
            auto const w{std::any_cast<Integer>(width(args))};

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

    auto const a{args[0]};
    auto const b{args[1]};

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

    if (grid.type() == typeid(Grid) && loc.type() == typeid(IntegerTuple))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const loc_{std::any_cast<IntegerTuple>(loc)};

        if (grid_.empty() || grid_[0].empty())
            throw std::runtime_error{"Wrong value"};

        auto const& [i, j] = loc_;
        auto const h{static_cast<Integer>(grid_.size())};
        auto const w{static_cast<Integer>(grid_[0].size())};

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

    if (value.type() == typeid(Integer) && dimensions.type() == typeid(IntegerTuple))
    {
        auto const value_{std::any_cast<Integer>(value)};
        auto const dimensions_{std::any_cast<IntegerTuple>(dimensions)};

        if (dimensions_.first < 0 || dimensions_.second < 0)
            throw std::runtime_error{"Wrong value"};

        return Grid(dimensions_.first, std::vector<Integer>(dimensions_.second, value_));
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::corners(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        try
        {
            auto const ulc{std::any_cast<IntegerTuple>(ulcorner(args))};
            auto const urc{std::any_cast<IntegerTuple>(urcorner(args))};
            auto const llc{std::any_cast<IntegerTuple>(llcorner(args))};
            auto const lrc{std::any_cast<IntegerTuple>(lrcorner(args))};

            return Indices{ulc, urc, llc, lrc};
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

        Integer di{0};
        Integer dj{0};

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
            return Indices{};

        Indices result;

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

std::any hodel::trim(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        Grid result;

        if (grid_.size() <= 2 || grid_.front().size() <= 2)
            return result;

        for (size_t i{1}; i + 1 < grid_.size(); ++i)
            result.emplace_back(grid_[i].begin() + 1, grid_[i].end() - 1);

        return result;
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::tophalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const mid = grid_.size() / 2;

        return Grid(grid_.begin(), grid_.begin() + mid);
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::bottomhalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const mid = grid_.size() / 2 + grid_.size() % 2;

        return Grid(grid_.begin() + mid, grid_.end());
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::lefthalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
        return rot270(std::vector<std::any>{tophalf(std::vector<std::any>{rot90(args)})});

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::righthalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
        return rot270(std::vector<std::any>{bottomhalf(std::vector<std::any>{rot90(args)})});

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

        Indices result;

        for (Integer i{0}; i < MAX_SIZE; ++i)
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

        Indices result;

        for (Integer j{0}; j < MAX_SIZE; ++j)
            result.emplace(location_.first, j);

        return result;
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

        return connect({start_, IntegerTuple{start_.first + 42 * direction_.first, start_.second + 42 * direction_.second}});
    }

    throw std::runtime_error{"Wrong value"};
}

std::any hodel::compress(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        throw std::runtime_error{"Wrong value"};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        if (grid_.empty())
            return {};

        try
        {
            auto const h{static_cast<Integer>(grid_.size())};
            auto const w{static_cast<Integer>(grid_.at(0).size())};

            std::vector<bool> removeRow(h, false);

            for (Integer i = 0; i < h; ++i)
            {
                bool uniform{true};

                for (Integer j = 1; j < w; ++j)
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

            for (Integer j = 0; j < w; ++j)
            {
                bool uniform{true};

                for (Integer i = 1; i < h; ++i)
                {
                    if (grid_.at(i).at(j) != grid_.at(0).at(j))
                    {
                        uniform = false;
                        break;
                    }
                }

                removeCol[j] = uniform;
            }

            Grid result;

            for (Integer i = 0; i < h; ++i)
            {
                if (removeRow[i])
                    continue;

                std::vector<Integer> row;

                for (Integer j = 0; j < w; ++j)
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
