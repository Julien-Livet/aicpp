#include <algorithm>
#include <numeric>
#include <ranges>
#include <unordered_set>

#include "aicpp/Hodel.h"

template<typename T>
static std::any repeat(std::any const& item, hodel::UnsignedInteger const& n)
{
    if (item.type() == typeid(T))
        return std::vector<T>(n, std::any_cast<T>(item));

    return std::any{};
}

template<typename T>
static std::any equality(std::any const& a, std::any const& b)
{
    if (a.type() == typeid(T) && b.type() == typeid(T))
        return hodel::Boolean{std::any_cast<T>(a) == std::any_cast<T>(b)};

    return std::any{};
}

template<typename T>
static std::any size_set(std::any const& value)
{
    if (value.type() == typeid(T))
        return static_cast<hodel::UnsignedInteger>(std::any_cast<T>(value).size());

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
        auto const& x{std::any_cast<hodel::IntegerTuple>(a)};

        if (b.type() == typeid(hodel::Integer))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::Integer>(b)}, op);
        else if (b.type() == typeid(hodel::IntegerTuple))
            return do_op(hodel::Numerical{x}, hodel::Numerical{std::any_cast<hodel::IntegerTuple>(b)}, op);
    }

    return std::any{};
}

std::any hodel::identity(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const x{args.front()};

    return x;
}

std::any hodel::add(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::plus<Integer>{});
}

std::any hodel::subtract(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::minus<Integer>{});
}

std::any hodel::multiply(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    return do_op(a, b, std::multiplies<Integer>{});
}

std::any hodel::divide(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    if (b.type() == typeid(hodel::Numerical))
    {
        auto const y{std::any_cast<hodel::Numerical>(b)};

        if (std::holds_alternative<hodel::Integer>(y))
        {
            if (!std::get<hodel::Integer>(y))
                return std::any{};
        }
        else if (std::holds_alternative<hodel::IntegerTuple>(y))
        {
            auto const& d{std::get<hodel::IntegerTuple>(y)};

            if (!d.first || !d.second)
                return std::any{};
        }
    }
    else if (b.type() == typeid(hodel::Integer))
    {
        auto const y{std::any_cast<hodel::Integer>(b)};

        if (!y)
            return std::any{};
    }
    else if (b.type() == typeid(hodel::IntegerTuple))
    {
        auto const& y{std::any_cast<hodel::IntegerTuple>(b)};

        if (!y.first || !y.second)
            return std::any{};
    }

    return do_op(a, b, std::divides<Integer>{});
}

std::any hodel::invert(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::even(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const n{args.front()};

    if (n.type() == typeid(hodel::Integer))
        return Boolean{std::any_cast<Integer>(n) % 2 == 0};

    return std::any{};
}

std::any hodel::double_(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::halve(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::flip(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const b{args.front()};

    if (b.type() == typeid(Boolean))
        return Boolean{!std::any_cast<Boolean>(b)};

    return std::any{};
}

std::any hodel::equality(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

std::any hodel::contained(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

    return std::any{};
}

std::any hodel::combine(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

std::any hodel::intersection(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = intersection_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<Indices>   (a, b); r.has_value()) return r;
    if (auto r = intersection_sets<IndicesSet>(a, b); r.has_value()) return r;

    return std::any{};
}

std::any hodel::difference(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    if (auto r = difference_sets<IntegerSet>(a, b); r.has_value()) return r;
    if (auto r = difference_sets<Object>    (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Objects>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<Indices>   (a, b); r.has_value()) return r;
    if (auto r = difference_sets<IndicesSet>(a, b); r.has_value()) return r;

    return std::any{};
}

std::any hodel::dedupe(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

std::any hodel::order(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const container{args[0]};
    auto const compfunc{args[1]};

    //...

    return std::any{};
}

std::any hodel::repeat(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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
    else if (num.type() == typeid(Integer))
    {
        auto const n{std::any_cast<Integer>(num)};
       
        if (n < 0)
            return std::any{};

        if (auto r = ::repeat<Integer>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<UnsignedInteger>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<IntegerTuple>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Boolean>(item, n); r.has_value()) return r;
        if (auto r = ::repeat<Numerical>(item, n); r.has_value()) return r;
    }

    return std::any{};
}

std::any hodel::greater(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Integer) && b.type() == typeid(Integer))
        return Boolean{std::any_cast<Integer>(a) > std::any_cast<Integer>(b)};

    return std::any{};
}

std::any hodel::size(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

std::any hodel::maximum(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

std::any hodel::minimum(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

std::any hodel::initset(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const value{args.front()};

    if (auto r = init_set<IntegerSet>(value); r.has_value()) return r;
    if (auto r = init_set<Object>    (value); r.has_value()) return r;
    if (auto r = init_set<Objects>   (value); r.has_value()) return r;
    if (auto r = init_set<Indices>   (value); r.has_value()) return r;
    if (auto r = init_set<IndicesSet>(value); r.has_value()) return r;

    return std::any{};
}

std::any hodel::both(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Boolean) && b.type() == typeid(Boolean))
        return Boolean{std::any_cast<Boolean>(a) && std::any_cast<Boolean>(b)};

    return std::any{};
}

std::any hodel::either(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Boolean) && b.type() == typeid(Boolean))
        return Boolean{std::any_cast<Boolean>(a) || std::any_cast<Boolean>(b)};

    return std::any{};
}

std::any hodel::increment(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::decrement(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::crement(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::sign(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::positive(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const x{args.front()};

    if (x.type() == typeid(Integer))
        return Boolean{std::any_cast<Integer>(x) > 0};

    return std::any{};
}

std::any hodel::toivec(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const i{args.front()};

    if (i.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(std::any_cast<Integer>(i), 0)};

    return std::any{};
}

std::any hodel::tojvec(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const j{args.front()};

    if (j.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(0, std::any_cast<Integer>(j))};

    return std::any{};
}

std::any hodel::totuple(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const container{args.front()};

    if (auto r = vector_set<IntegerSet>(container); r.has_value()) return r;
    if (auto r = vector_set<Object>    (container); r.has_value()) return r;
    if (auto r = vector_set<Objects>   (container); r.has_value()) return r;
    if (auto r = vector_set<Indices>   (container); r.has_value()) return r;
    if (auto r = vector_set<IndicesSet>(container); r.has_value()) return r;

    return std::any{};
}

std::any hodel::first(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

std::any hodel::last(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

std::any hodel::interval(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        return std::any{};

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

std::any hodel::astuple(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const a{args[0]};
    auto const b{args[1]};

    if (a.type() == typeid(Integer) && b.type() == typeid(Integer))
        return IntegerTuple{std::make_pair<Integer, Integer>(std::any_cast<Integer>(a), std::any_cast<Integer>(b))};

    return std::any{};
}

std::any hodel::matcher(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

    return std::any{};
}

std::any hodel::rbind(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

    return std::any{};
}

std::any hodel::lbind(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

    return std::any{};
}

std::any hodel::ulcorner(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

            for (const auto& [y, x] : indices)
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

    return std::any{};
}

std::any hodel::urcorner(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

            for (const auto& [y, x] : indices)
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

    return std::any{};
}

std::any hodel::llcorner(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

            for (const auto& [y, x] : indices)
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

    return std::any{};
}

std::any hodel::lrcorner(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

            for (const auto& [y, x] : indices)
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

    return std::any{};
}

std::any hodel::crop(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        return std::any{};

    auto const grid{args[0]};
    auto const start{args[1]};
    auto const dims{args[2]};

    if (grid.type() == typeid(Grid) && start.type() == typeid(IntegerTuple) && dims.type() == typeid(Size))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const start_{std::any_cast<IntegerTuple>(start)};
        auto const dims_{std::any_cast<Size>(dims)};

        if (start_.first < 0 || start_.second < 0 || start_.first + dims_.first > grid_.size() || start_.second + dims_.second > grid_[0].size())
            return std::any{};

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

std::any hodel::toindices(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const patch{args[0]};

    if (patch.type() == typeid(Patch))
    {
        auto const patch_{std::any_cast<Patch>(patch)};

        if (std::holds_alternative<Indices>(patch_))
            return std::get<Indices>(patch_);

        auto const& obj = std::get<Object>(patch_);

        if (obj.empty())
            return std::any{};

        Indices result;

        for (auto const& cell : obj)
            result.insert(cell.second);

        return result;
    }
    else if (patch.type() == typeid(Object))
        return toindices(std::vector<std::any>{Patch{std::any_cast<Object>(patch)}});
    else if (patch.type() == typeid(Indices))
        return toindices(std::vector<std::any>{Patch{std::any_cast<Indices>(patch)}});

    return std::any{};
}

std::any hodel::shift(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

    return std::any{};
}

std::any hodel::uppermost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::lowermost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::leftmost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::rightmost(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::rot90(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

std::any hodel::rot180(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};

        if (grid_.empty())
            return std::any{};

        auto const rows{static_cast<int>(grid_.size())};
        auto const cols{static_cast<int>(grid_[0].size())};

        Grid result(rows, std::vector<int>(cols));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
                result[rows - 1 - i][cols - 1 - j] = grid_[i][j];
        }

        return result;
    }

    return std::any{};
}

std::any hodel::rot270(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

std::any hodel::hmirror(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

            for (const auto& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {d - i, j}});
            }

            return Piece{Patch(result)};
        }

        auto const& indices = std::get<Indices>(patch);

        Indices result;

        for (const auto& [i, j] : indices)
            result.insert({d - i, j});

        return Piece{Patch(result)};
    }
    else if (piece.type() == typeid(Grid))
        return hmirror(std::vector<std::any>{Piece{std::any_cast<Grid>(piece)}});
    else if (piece.type() == typeid(Patch))
        return hmirror(std::vector<std::any>{Piece{std::any_cast<Patch>(piece)}});

    return std::any{};
}

std::any hodel::vmirror(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

            for (const auto& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {i, d - j}});
            }

            return Piece{Patch(result)};
        }

        auto const& indices = std::get<Indices>(patch);

        Indices result;

        for (const auto& [i, j] : indices)
            result.insert({i, d - j});

        return Piece{Patch(result)};
    }
    else if (piece.type() == typeid(Grid))
        return vmirror(std::vector<std::any>{Piece{std::any_cast<Grid>(piece)}});
    else if (piece.type() == typeid(Patch))
        return vmirror(std::vector<std::any>{Piece{std::any_cast<Patch>(piece)}});

    return std::any{};
}

std::any hodel::dmirror(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
                    result[j][i] = grid[i][j];
            }

            return result;
        }

        Patch patch = std::get<Patch>(piece_);

        auto [a, b] = std::any_cast<IntegerTuple>(ulcorner(std::vector<std::any>{patch}));

        if (std::holds_alternative<Object>(patch))
        {
            auto const& obj = std::get<Object>(patch);

            Object result;

            for (const auto& [v, pos] : obj)
            {
                auto [i, j] = pos;

                result.insert({v, {j - b + a, i - a + b}});
            }

            return Piece{Patch(result)};
        }

        auto const& indices = std::get<Indices>(patch);

        Indices result;

        for (const auto& [i, j] : indices)
            result.insert({j - b + a, i - a + b});

        return Piece{Patch(result)};
    }
    else if (piece.type() == typeid(Grid))
        return dmirror(std::vector<std::any>{Piece{std::any_cast<Grid>(piece)}});
    else if (piece.type() == typeid(Patch))
        return dmirror(std::vector<std::any>{Piece{std::any_cast<Patch>(piece)}});

    return std::any{};
}

std::any hodel::cmirror(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

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

    return std::any{};
}

std::any hodel::hupscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const grid{args[0]};
    auto const factor{args[1]};

    if (grid.type() == typeid(Grid) && factor.type() == typeid(UnsignedInteger))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const factor_{std::any_cast<UnsignedInteger>(factor)};

        Grid result;

        for (const auto& row : grid_)
        {
            std::vector<Integer> new_row;
            new_row.reserve(row.size() * factor_);

            for (const auto& cell : row)
            {
                for (UnsignedInteger i{0}; i < factor_; ++i)
                    new_row.emplace_back(cell);
            }

            result.emplace_back(new_row);
        }

        return result;
    }

    return std::any{};
}

std::any hodel::vupscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const grid{args[0]};
    auto const factor{args[1]};

    if (grid.type() == typeid(Grid) && factor.type() == typeid(UnsignedInteger))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const factor_{std::any_cast<UnsignedInteger>(factor)};

        Grid result;
        result.reserve(grid_.size() * factor_);

        for (const auto& row : grid_)
        {
            for (UnsignedInteger k = 0; k < factor_; ++k)
                result.emplace_back(row);
        }

        return result;
    }

    return std::any{};
}

std::any hodel::upscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const element{args[0]};
    auto const factor{args[1]};

    if (element.type() == typeid(Element) && factor.type() == typeid(UnsignedInteger))
    {
        auto const element_{std::any_cast<Element>(element)};
        auto const factor_{std::any_cast<UnsignedInteger>(factor)};

        if (std::holds_alternative<Grid>(element_))
        {
            auto const& grid = std::get<Grid>(element_);

            Grid result;

            for (const auto& row : grid)
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

    return std::any{};
}

std::any hodel::downscale(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const grid{args[0]};
    auto const factor{args[1]};

    if (grid.type() == typeid(Grid) && factor.type() == typeid(UnsignedInteger))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const factor_{std::any_cast<UnsignedInteger>(factor)};

        if (grid_.empty())
            return grid_;

        auto const h = static_cast<Integer>(grid_.size());
        auto const w = static_cast<Integer>(grid_[0].size());

        Grid temp;

        for (Integer i = 0; i < h; ++i)
        {
            std::vector<Integer> row;

            for (Integer j = 0; j < w; ++j)
            {
                if (j % factor_ == 0)
                    row.emplace_back(grid_[i][j]);
            }

            temp.emplace_back(row);
        }

        Grid result;

        for (Integer i = 0; i < static_cast<Integer>(temp.size()); ++i)
        {
            if (i % factor_ == 0)
                result.emplace_back(temp[i]);
        }

        return result;
    }

    return std::any{};
}

std::any hodel::hconcat(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

    return std::any{};
}

std::any hodel::vconcat(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

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

    return std::any{};
}

std::any hodel::replace(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        return std::any{};

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

    return std::any{};
}

std::any hodel::switch_(std::vector<std::any> const& args)
{
    if (args.size() != 3)
        return std::any{};

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

    return std::any{};
}

std::any hodel::tophalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const mid = grid_.size() / 2;

        return Grid(grid_.begin(), grid_.begin() + mid);
    }

    return std::any{};
}

std::any hodel::bottomhalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
    {
        auto const grid_{std::any_cast<Grid>(grid)};
        auto const mid = grid_.size() / 2 + grid_.size() % 2;

        return Grid(grid_.begin() + mid, grid_.end());
    }

    return std::any{};
}

std::any hodel::lefthalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
        return rot270(std::vector<std::any>{tophalf(std::vector<std::any>{rot90(args)})});

    return std::any{};
}

std::any hodel::righthalf(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const grid{args[0]};

    if (grid.type() == typeid(Grid))
        return rot270(std::vector<std::any>{bottomhalf(std::vector<std::any>{rot90(args)})});

    return std::any{};
}
