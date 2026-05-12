#include <algorithm>
#include <ranges>
#include <unordered_set>

#include "aicpp/Hodel.h"

template<typename T>
static std::any repeat(std::any const& item, hdl::UnsignedInteger const& n)
{
    if (item.type() == typeid(T))
        return std::vector<T>(n, std::any_cast<T>(item));

    return std::any{};
}

template<typename T>
static std::any equality(std::any const& a, std::any const& b)
{
    if (a.type() == typeid(T) && b.type() == typeid(T))
        return hdl::Boolean{std::any_cast<T>(a) == std::any_cast<T>(b)};

    return std::any{};
}

template<typename T>
static std::any size_set(std::any const& value)
{
    if (value.type() == typeid(T))
        return static_cast<hdl::UnsignedInteger>(std::any_cast<T>(value).size());

    return std::any{};
}

template<typename T>
static std::any init_set(std::any const& value)
{
    if (value.type() == typeid(typename T::value_type))
        return T{std::any_cast<typename T::value_type>(value)};

    return std::any{};
}

template<typename T>
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

template<typename T>
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

template<typename T>
static std::any vector_set(std::any const& container)
{
    if (container.type() == typeid(T))
    {
        auto const x{std::any_cast<T>(container)};

        return std::vector<typename T::value_type>{x.begin(), x.end()};
    }

    return std::any{};
}

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

std::any hdl::identity(std::vector<std::any> const& args)
{
    auto const x{args.front()};

    return x;
}

std::any hdl::add(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::plus<Integer>{});
}

std::any hdl::subtract(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::minus<Integer>{});
}

std::any hdl::multiply(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::multiplies<Integer>{});
}

std::any hdl::divide(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::divides<Integer>{});
}

std::any hdl::invert(std::vector<std::any> const& args)
{
    auto const n{args.front()};

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

std::any hdl::even(std::vector<std::any> const& args)
{
    auto const n{args.front()};

    if (n.type() == typeid(hdl::Integer))
        return Boolean{std::any_cast<Integer>(n) % 2 == 0};

    return std::any{};
}

std::any hdl::double_(std::vector<std::any> const& args)
{
    auto const n{args.front()};

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

std::any hdl::halve(std::vector<std::any> const& args)
{
    auto const n{args.front()};

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

std::any hdl::flip(std::vector<std::any> const& args)
{
    auto const b{args.front()};

    if (b.type() == typeid(Boolean))
        return Boolean{!std::any_cast<Boolean>(b)};

    return std::any{};
}

std::any hdl::equality(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = ::equality<Boolean>(a, b); r.has_value()) return r;
    if (auto r = ::equality<Integer>(a, b); r.has_value()) return r;
    if (auto r = ::equality<UnsignedInteger>(a, b); r.has_value()) return r;
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
    if (auto r = ::equality<Size>(a, b); r.has_value()) return r;

    return std::any{};
}

std::any hdl::contained(std::vector<std::any> const& args)
{
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

std::any hdl::combine(std::vector<std::any> const& args)
{
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

    return std::any{};
}

std::any hdl::intersection(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = intersection_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Indices>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<IndicesSet>(a, b); r.has_value()) return r;

    return std::any{};
}

std::any hdl::difference(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = difference_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = difference_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Indices>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<IndicesSet>(a, b); r.has_value()) return r;

    return std::any{};
}

std::any hdl::dedupe(std::vector<std::any> const& args)
{
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
    }

    return std::any{};
}

std::any hdl::order(std::vector<std::any> const& args)
{
    auto const container{args[0]};
    auto const compfunc{args[1]};

    //...

    return std::any{};
}

std::any hdl::repeat(std::vector<std::any> const& args)
{
    auto const item{args[0]};
    auto const num{args[1]};

    if (num.type() == typeid(UnsignedInteger))
    {
        auto const n{std::any_cast<UnsignedInteger>(num)};
       
        if (auto r = ::repeat<Integer>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<UnsignedInteger>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<IntegerTuple>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Boolean>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Numerical>(item, n); r.has_value()) return r;
    }

    return std::any{};
}

std::any hdl::greater(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Integer) && b.type() == typeid(Integer))
        return Boolean{std::any_cast<Integer>(a) > std::any_cast<Integer>(b)};

    return std::any{};
}

std::any hdl::size(std::vector<std::any> const& args)
{
    auto const container{args.front()};

    if (auto r = size_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = size_set<Object>    (container); r.has_value()) return r;
    if (auto r = size_set<Objects>   (container); r.has_value()) return r;
    if (auto r = size_set<Indices>   (container); r.has_value()) return r;
    if (auto r = size_set<IndicesSet>(container); r.has_value()) return r;

    if (container.type() == typeid(Grid))
    {
        auto const x{std::any_cast<Grid>(container)};
        
        return static_cast<UnsignedInteger>(x.size());
    }

    return std::any{};
}

std::any hdl::maximum(std::vector<std::any> const& args)
{
    auto const container{args.front()};

    if (container.type() == typeid(IntegerSet))
    {
        auto const set{std::any_cast<IntegerSet>(container)};

        if (set.empty())
            return Integer{0};
        
        return *std::max_element(set.begin(), set.end());
    }

    return std::any{};
}

std::any hdl::minimum(std::vector<std::any> const& args)
{
    auto const container{args.front()};

    if (container.type() == typeid(IntegerSet))
    {
        auto const set{std::any_cast<IntegerSet>(container)};

        if (set.empty())
            return Integer{0};
        
        return *std::min_element(set.begin(), set.end());
    }

    return std::any{};
}

std::any hdl::initset(std::vector<std::any> const& args)
{
    auto const value{args.front()};

    if (auto r = init_set<IntegerSet>(value); r.has_value()) return r;
    if (auto r = init_set<Object>    (value); r.has_value()) return r;
    if (auto r = init_set<Objects>   (value); r.has_value()) return r;
    if (auto r = init_set<Indices>   (value); r.has_value()) return r;
    if (auto r = init_set<IndicesSet>(value); r.has_value()) return r;

    return std::any{};
}

std::any hdl::both(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Boolean) && b.type() == typeid(Boolean))
        return Boolean{std::any_cast<Boolean>(a) && std::any_cast<Boolean>(b)};

    return std::any{};
}

std::any hdl::either(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Boolean) && b.type() == typeid(Boolean))
        return Boolean{std::any_cast<Boolean>(a) || std::any_cast<Boolean>(b)};

    return std::any{};
}

std::any hdl::increment(std::vector<std::any> const& args)
{
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

    return std::any{};
}

std::any hdl::decrement(std::vector<std::any> const& args)
{
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

    return std::any{};
}

std::any hdl::crement(std::vector<std::any> const& args)
{
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

    return std::any{};
}

std::any hdl::sign(std::vector<std::any> const& args)
{
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

    return std::any{};
}

std::any hdl::positive(std::vector<std::any> const& args)
{
    auto const x{args.front()};

    if (x.type() == typeid(Integer))
        return Boolean{std::any_cast<Integer>(x) > 0};

    return std::any{};
}

std::any hdl::toivec(std::vector<std::any> const& args)
{
    auto const i{args.front()};

    if (i.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(std::any_cast<Integer>(i), 0)};

    return std::any{};
}

std::any hdl::tojvec(std::vector<std::any> const& args)
{
    auto const j{args.front()};

    if (j.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(0, std::any_cast<Integer>(j))};

    return std::any{};
}

std::any hdl::totuple(std::vector<std::any> const& args)
{
    auto const container{args.front()};

    if (auto r = vector_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = vector_set<Object>    (container); r.has_value()) return r;
    if (auto r = vector_set<Objects>   (container); r.has_value()) return r;
    if (auto r = vector_set<Indices>   (container); r.has_value()) return r;
    if (auto r = vector_set<IndicesSet>(container); r.has_value()) return r;

    return std::any{};
}

std::any hdl::first(std::vector<std::any> const& args)
{
    auto const container{args.front()};

    if (auto r = first_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = first_set<Object>    (container); r.has_value()) return r;
    if (auto r = first_set<Objects>   (container); r.has_value()) return r;
    if (auto r = first_set<Indices>   (container); r.has_value()) return r;
    if (auto r = first_set<IndicesSet>(container); r.has_value()) return r;

    if (container.type() == typeid(Grid))
    {
        auto const x{std::any_cast<Grid>(container)};
        
        return x.front();
    }

    return std::any{};
}

std::any hdl::last(std::vector<std::any> const& args)
{
    auto const container{args.front()};

    if (auto r = last_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = last_set<Object>    (container); r.has_value()) return r;
    if (auto r = last_set<Objects>   (container); r.has_value()) return r;
    if (auto r = last_set<Indices>   (container); r.has_value()) return r;
    if (auto r = last_set<IndicesSet>(container); r.has_value()) return r;

    if (container.type() == typeid(Grid))
    {
        auto const x{std::any_cast<Grid>(container)};
        
        return x.front();
    }

    return std::any{};
}

std::any hdl::interval(std::vector<std::any> const& args)
{
    auto const start{args[0]};
    auto const stop{args[1]};
    auto const step{args[2]};

    if (start.type() == typeid(Integer) && stop.type() == typeid(Integer) && step.type() == typeid(Integer))
    {
        auto start_{std::any_cast<Integer>(start)};
        auto const stop_{std::any_cast<Integer>(stop)};
        auto const step_{std::any_cast<Integer>(step)};
        std::vector<Integer> result;

        for (; start_ != stop_; start_ += step_)
            result.emplace_back(start_);

        return result;
    }

    return std::any{};
}

std::any hdl::astuple(std::vector<std::any> const& args)
{
    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Integer) && b.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(std::any_cast<Integer>(a), std::any_cast<Integer>(b))};

    return std::any{};
}

std::any hdl::crop(std::vector<std::any> const& args)
{
    auto const grid{args[0]};
    auto const start{args[1]};
    auto const dims{args[2]};

    if (grid.type() == typeid(Grid) && start.type() == typeid(IntegerTuple) && dims.type() == typeid(Size))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const start_{std::any_cast<IntegerTuple>(start)};
        auto const dims_{std::any_cast<Size>(dims)};

        Grid result;

        for (size_t i{0}; i < dims_.first; ++i)
        {
            std::vector<Integer> row;

            for (size_t j{0}; j < dims_.second; ++j)
                row.emplace_back(grid_[start_.first + i][start_.second + j]); 

            result.emplace_back(row);
        }

        return result;
    }
    
    return std::any{};
}

std::any hdl::rot90(std::vector<std::any> const& args)
{
    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        if (grid_.empty())
            return std::any{};

        auto const rows{static_cast<int>(grid_.size())};
        auto const cols{static_cast<int>(grid_[0].size())};

        Grid result(cols, std::vector<int>(rows));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
                result[j][rows - 1 - i] = grid_[i][j];
        }

        return result;
    }

    return std::any{};
}

std::any hdl::rot180(std::vector<std::any> const& args)
{
    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        if (grid_.empty())
            return std::any{};

        auto const rows{static_cast<int>(grid_.size())};
        auto const cols{static_cast<int>(grid_[0].size())};

        Grid result(cols, std::vector<int>(rows));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
                result[rows - 1 - i][cols - 1 - j] = grid_[i][j];
        }

        return result;
    }

    return std::any{};
}

std::any hdl::rot270(std::vector<std::any> const& args)
{
    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        if (grid_.empty())
            return std::any{};

        auto const rows{static_cast<int>(grid_.size())};
        auto const cols{static_cast<int>(grid_[0].size())};

        Grid result(cols, std::vector<int>(rows));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
                result[cols - 1 - j][i] = grid_[i][j];
        }

        return result;
    }

    return std::any{};
}
