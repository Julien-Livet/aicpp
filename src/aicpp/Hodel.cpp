#include <algorithm>
#include <ranges>
#include <unordered_set>

#include "aicpp/Hodel.h"

template<typename T>
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

template<typename T>
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

template<typename T>
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

std::any do_op(std::any const& a, std::any const& b, std::function<hdl::Integer(hdl::Integer, hdl::Integer)> const& op)
{
    if (a.type() == typeid(hdl::Numerical) && b.type() == typeid(hdl::Numerical))
    {
        auto const x{std::any_cast<hdl::Numerical>(a)};
        auto const y{std::any_cast<hdl::Numerical>(b)};

        if (std::holds_alternative<hdl::Integer>(x) && std::holds_alternative<hdl::Integer>(y))
            return hdl::Numerical{op(std::get<hdl::Integer>(x), std::get<hdl::Integer>(y))};
        else if (std::holds_alternative<hdl::IntegerTuple>(x) && std::holds_alternative<hdl::IntegerTuple>(y))
        {
            auto const& c{std::get<hdl::IntegerTuple>(x)};
            auto const& d{std::get<hdl::IntegerTuple>(y)};

            return hdl::Numerical{std::make_pair<hdl::Integer, hdl::Integer>(op(c.first, d.first), op(c.second, d.second))};
        }
        else if (std::holds_alternative<hdl::Integer>(x) && std::holds_alternative<hdl::IntegerTuple>(y))
        {
            auto const& c{std::get<hdl::Integer>(x)};
            auto const& d{std::get<hdl::IntegerTuple>(y)};

            return hdl::Numerical{std::make_pair<hdl::Integer, hdl::Integer>(op(c, d.first), op(c, d.second))};
        }
        else if (std::holds_alternative<hdl::IntegerTuple>(x) && std::holds_alternative<hdl::Integer>(y))
        {
            auto const& c{std::get<hdl::IntegerTuple>(x)};
            auto const& d{std::get<hdl::Integer>(y)};

            return hdl::Numerical{std::make_pair<hdl::Integer, hdl::Integer>(op(c.first, d), op(c.second, d))};
        }
    }

    return std::any{};
}

std::any hdl::identity(std::any const& x)
{
    return x;
}

std::any hdl::add(std::any const& a, std::any const& b)
{
    return do_op(a, b, std::plus<Integer>{});
}

std::any hdl::subtract(std::any const& a, std::any const& b)
{
    return do_op(a, b, std::minus<Integer>{});
}

std::any hdl::multiply(std::any const& a, std::any const& b)
{
    return do_op(a, b, std::multiplies<Integer>{});
}

std::any hdl::divide(std::any const& a, std::any const& b)
{
    return do_op(a, b, std::divides<Integer>{});
}

std::any hdl::invert(std::any const& n)
{
    if (n.type() == typeid(hdl::Numerical))
    {
        auto const x{std::any_cast<hdl::Numerical>(n)};

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

    return std::any{};
}

std::any hdl::even(std::any const& n)
{
    if (n.type() == typeid(hdl::Integer))
        return Boolean{std::any_cast<Integer>(n) % 2 == 0};

    return std::any{};
}

std::any hdl::double_(std::any const& n)
{
    if (n.type() == typeid(hdl::Numerical))
    {
        auto const x{std::any_cast<hdl::Numerical>(n)};

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

    return std::any{};
}

std::any hdl::halve(std::any const& n)
{
    if (n.type() == typeid(hdl::Numerical))
    {
        auto const x{std::any_cast<hdl::Numerical>(n)};

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

    return std::any{};
}

std::any hdl::flip(std::any const& b)
{
    if (b.type() == typeid(Boolean))
        return Boolean{!std::any_cast<Boolean>(b)};

    return std::any{};
}

std::any hdl::contained(std::any const& value, std::any const& container)
{
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

        if (value.type() == typeid(Integer))
        {
            Cell const v{std::any_cast<Integer>(value)};

            return static_cast<Boolean>(c.count(v) > 0);
        }
        else if (value.type() == typeid(IntegerTuple))
        {
            Cell const v{std::any_cast<IntegerTuple>(value)};

            return static_cast<Boolean>(c.count(v) > 0);
        }
        else if (value.type() == typeid(Cell))
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

    return std::any{};
}

std::any hdl::combine(std::any const& a, std::any const& b)
{
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

    return std::any{};
}

std::any hdl::intersection(std::any const& a, std::any const& b)
{
    if (auto r = intersection_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Indices>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<IndicesSet>(a, b); r.has_value()) return r;

    return std::any{};
}

std::any hdl::difference(std::any const& a, std::any const& b)
{
    if (auto r = difference_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = difference_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Indices>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<IndicesSet>(a, b); r.has_value()) return r;

    return std::any{};
}

std::any hdl::dedupe(std::any const& tup)
{
    if (tup.type() == typeid(Element))
    {
        auto const x{std::any_cast<Element>(tup)};

        if (std::holds_alternative<Grid>(x))
            return dedupe(std::get<Grid>(x));
    }
    else if (tup.type() == typeid(Piece))
    {
        auto const x{std::any_cast<Piece>(tup)};

        if (std::holds_alternative<Grid>(x))
            return dedupe(std::get<Grid>(x));
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
    }

    return std::any{};
}

std::any hdl::order(std::any const& container, std::any const& compfunc)
{
    //...

    return std::any{};
}

std::any hdl::repeat(std::any const& item, std::any const& num)
{
    if (num.type() == typeid(UnsignedInteger))
    {
        auto const n{std::any_cast<UnsignedInteger>(num)};
       
        if (item.type() == typeid(Integer))
            return std::vector<Integer>(n, std::any_cast<Integer>(item));
    }

    return std::any{};
}

std::any hdl::greater(std::any const& a, std::any const& b)
{
    if (a.type() == typeid(Integer) && a.type() == typeid(Integer))
        return Boolean{std::any_cast<Integer>(a) > std::any_cast<Integer>(b)};

    return std::any{};
}

std::any hdl::increment(std::any const& x)
{
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

    return std::any{};
}

std::any hdl::decrement(std::any const& x)
{
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

    return std::any{};
}

std::any hdl::crement(std::any const& x)
{
    if (x.type() == typeid(Numerical))
    {
        auto const y{std::any_cast<Numerical>(x)};

        if (std::holds_alternative<Integer>(y))
        {
            auto const z{std::get<Integer>(y)};

            if (!z)
                return Numerical{z};
            else if (z > 0)
                return increment(x);
            else
                return decrement(x);
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

    return std::any{};
}

std::any hdl::positive(std::any const& x)
{
    if (x.type() == typeid(Integer))
        return Boolean{std::any_cast<Integer>(x) > 0};

    return std::any{};
}
