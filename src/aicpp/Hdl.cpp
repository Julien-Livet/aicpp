#include <algorithm>
#include <numeric>
#include <ranges>
#include <unordered_set>

#include "aicpp/Hdl.h"

namespace hdl
{
    namespace typed
    {
        Integer add(Integer const& a, Integer const& b)
        {
            return a + b;
        }

        IntegerTuple add(IntegerTuple const& a, Integer const& b)
        {
            return IntegerTuple{a} += b;
        }

        IntegerTuple add(Integer const& a, IntegerTuple const& b)
        {
            return IntegerTuple{b} += a;
        }

        IntegerTuple add(IntegerTuple const& a, IntegerTuple const& b)
        {
            return IntegerTuple{a} += b;
        }
        
        Integer subtract(Integer const& a, Integer const& b)
        {
            return a - b;
        }

        IntegerTuple subtract(IntegerTuple const& a, Integer const& b)
        {
            return IntegerTuple{a} -= b;
        }

        IntegerTuple subtract(Integer const& a, IntegerTuple const& b)
        {
            return IntegerTuple{b} -= a;
        }

        IntegerTuple subtract(IntegerTuple const& a, IntegerTuple const& b)
        {
            return IntegerTuple{a} -= b;
        }
        
        Integer multiply(Integer const& a, Integer const& b)
        {
            return a * b;
        }

        IntegerTuple multiply(IntegerTuple const& a, Integer const& b)
        {
            return IntegerTuple{a} *= b;
        }

        IntegerTuple multiply(Integer const& a, IntegerTuple const& b)
        {
            return IntegerTuple{b} *= a;
        }

        IntegerTuple multiply(IntegerTuple const& a, IntegerTuple const& b)
        {
            return IntegerTuple{a} *= b;
        }
        
        Integer divide(Integer const& a, Integer const& b)
        {
            return a / b;
        }

        IntegerTuple divide(IntegerTuple const& a, Integer const& b)
        {
            return IntegerTuple{a} /= b;
        }

        IntegerTuple divide(Integer const& a, IntegerTuple const& b)
        {
            return IntegerTuple{a, a} /= b;
        }

        IntegerTuple divide(IntegerTuple const& a, IntegerTuple const& b)
        {
            return IntegerTuple{a} /= b;
        }
    }
}

/*
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
*/
hdl::Numerical do_op(hdl::Numerical const& a, hdl::Numerical const& b, std::function<hdl::Integer(hdl::Integer, hdl::Integer)> const& op)
{
    if (std::holds_alternative<hdl::Integer>(a) && std::holds_alternative<hdl::Integer>(b))
        return hdl::Numerical{op(std::get<hdl::Integer>(a), std::get<hdl::Integer>(b))};
    else if (std::holds_alternative<hdl::IntegerTuple>(a) && std::holds_alternative<hdl::IntegerTuple>(b))
    {
        auto const& c{std::get<hdl::IntegerTuple>(a)};
        auto const& d{std::get<hdl::IntegerTuple>(b)};

        return hdl::Numerical{std::make_pair<hdl::Integer, hdl::Integer>(op(c.first, d.first), op(c.second, d.second))};
    }
    else if (std::holds_alternative<hdl::Integer>(a) && std::holds_alternative<hdl::IntegerTuple>(b))
    {
        auto const& c{std::get<hdl::Integer>(a)};
        auto const& d{std::get<hdl::IntegerTuple>(b)};

        return hdl::Numerical{std::make_pair<hdl::Integer, hdl::Integer>(op(c, d.first), op(c, d.second))};
    }
    //else if (std::holds_alternative<hdl::IntegerTuple>(a) && std::holds_alternative<hdl::Integer>(b))
    {
        auto const& c{std::get<hdl::IntegerTuple>(a)};
        auto const& d{std::get<hdl::Integer>(b)};

        return hdl::Numerical{std::make_pair<hdl::Integer, hdl::Integer>(op(c.first, d), op(c.second, d))};
    }
}
/*
std::any hdl::identity(std::vector<std::any> const& args)
{
    if (args.size() != 1)
        return std::any{};

    auto const x{args.front()};

    return x;
}
*/
hdl::Numerical hdl::add(Numerical const& a, Numerical const& b)
{
    return do_op(a, b, std::plus<Integer>{});
}

hdl::Numerical hdl::subtract(Numerical const& a, Numerical const& b)
{
    return do_op(a, b, std::minus<Integer>{});
}

hdl::Numerical hdl::multiply(Numerical const& a, Numerical const& b)
{
    return do_op(a, b, std::multiplies<Integer>{});
}

hdl::Numerical hdl::divide(Numerical const& a, Numerical const& b)
{
    return do_op(a, b, std::divides<Integer>{});
}

hdl::Numerical hdl::invert(Numerical const& n)
{
    if (std::holds_alternative<Integer>(n))
    {
        auto const& y{std::get<Integer>(n)};

        return Integer{-y};
    }
    //else if (std::holds_alternative<IntegerTuple>(n))
    {
        auto const& y{std::get<IntegerTuple>(n)};

        return Numerical{std::make_pair<Integer, Integer>(-y.first, -y.second)};
    }
}

hdl::Boolean hdl::even(Integer const& n)
{
    return Boolean{n % 2 == 0};
}

hdl::Numerical hdl::double_(Numerical const& n)
{
    if (std::holds_alternative<Integer>(n))
    {
        auto const& y{std::get<Integer>(n)};

        return Integer{y * 2};
    }
    //else if (std::holds_alternative<IntegerTuple>(n))
    {
        auto const& y{std::get<IntegerTuple>(n)};

        return Numerical{std::make_pair<Integer, Integer>(y.first * 2, y.second * 2)};
    }
}

hdl::Numerical hdl::halve(Numerical const& n)
{
    if (std::holds_alternative<Integer>(n))
    {
        auto const& y{std::get<Integer>(n)};

        return Integer{y / 2};
    }
    //else if (std::holds_alternative<IntegerTuple>(n))
    {
        auto const& y{std::get<IntegerTuple>(n)};

        return Numerical{std::make_pair<Integer, Integer>(y.first / 2, y.second / 2)};
    }
}

hdl::Boolean hdl::flip(Boolean const& b)
{
    return Boolean{!b};
}
/*
std::any hdl::equality(std::vector<std::any> const& args)
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

std::any hdl::contained(std::vector<std::any> const& args)
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

std::any hdl::combine(std::vector<std::any> const& args)
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

std::any hdl::intersection(std::vector<std::any> const& args)
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

std::any hdl::difference(std::vector<std::any> const& args)
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

std::any hdl::dedupe(std::vector<std::any> const& args)
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

std::any hdl::order(std::vector<std::any> const& args)
{
    if (args.size() != 2)
        return std::any{};

    auto const container{args[0]};
    auto const compfunc{args[1]};

    //...

    return std::any{};
}

std::any hdl::repeat(std::vector<std::any> const& args)
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

    return std::any{};
}
*/
hdl::Boolean hdl::greater(Integer const& a, Integer const& b)
{
    return Boolean{a > b};
}
/*
std::any hdl::size(std::vector<std::any> const& args)
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
*/
hdl::Integer hdl::maximum(IntegerSet const& container)
{
    if (container.empty())
        return Integer{0};
    
    return *std::max_element(container.begin(), container.end());
}

hdl::Integer hdl::minimum(IntegerSet const& container)
{
    if (container.empty())
        return Integer{0};
    
    return *std::min_element(container.begin(), container.end());
}
/*
std::any hdl::initset(std::vector<std::any> const& args)
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
*/
hdl::Boolean hdl::both(Boolean const& a, Boolean const& b)
{
    return Boolean{a && b};
}

hdl::Boolean hdl::either(Boolean const& a, Boolean const& b)
{
    return Boolean{a || b};
}

hdl::Numerical hdl::increment(Numerical const& x)
{
    if (std::holds_alternative<Integer>(x))
        return Numerical{std::get<Integer>(x) + 1};
    //else if (std::holds_alternative<IntegerTuple>(x))
    {
        auto const z{std::get<IntegerTuple>(x)};

        return Numerical{std::make_pair<Integer, Integer>(z.first + 1, z.second + 1)};
    }
}

hdl::Numerical hdl::decrement(Numerical const& x)
{
    if (std::holds_alternative<Integer>(x))
        return Numerical{std::get<Integer>(x) - 1};
    //else if (std::holds_alternative<IntegerTuple>(x))
    {
        auto const z{std::get<IntegerTuple>(x)};

        return Numerical{std::make_pair<Integer, Integer>(z.first - 1, z.second - 1)};
    }
}

hdl::Numerical hdl::crement(Numerical const& x)
{
    if (std::holds_alternative<Integer>(x))
    {
        auto const z{std::get<Integer>(x)};

        if (!z)
            return Numerical{z};
        else if (z > 0)
            return increment(x);
        else
            return decrement(x);
    }
    //else if (std::holds_alternative<IntegerTuple>(x))
    {
        auto const z{std::get<IntegerTuple>(x)};
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

hdl::Numerical hdl::sign(Numerical const& x)
{
    if (std::holds_alternative<Integer>(x))
    {
        auto const z{std::get<Integer>(x)};

        if (!z)
            return Numerical{0};
        else if (z > 0)
            return Numerical{1};
        else
            return Numerical{-1};
    }
    //else if (std::holds_alternative<IntegerTuple>(x))
    {
        auto const z{std::get<IntegerTuple>(x)};
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

hdl::Boolean hdl::positive(Integer const& x)
{
    return Boolean{x > 0};
}

hdl::IntegerTuple hdl::toivec(Integer const& i)
{
    return IntegerTuple{i, 0};
}

hdl::IntegerTuple hdl::tojvec(Integer const& j)
{
    return IntegerTuple{0, j};
}
/*
std::any hdl::totuple(std::vector<std::any> const& args)
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

std::any hdl::first(std::vector<std::any> const& args)
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

std::any hdl::last(std::vector<std::any> const& args)
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
*/
std::vector<hdl::Integer> hdl::interval(Integer start, Integer const& stop, Integer const& step)
{
    std::vector<Integer> result;

    for (; start != stop; start += step)
        result.emplace_back(start);

    return result;
}

hdl::IntegerTuple hdl::astuple(Integer const& a, Integer const& b)
{
    return IntegerTuple{a, b};
}

hdl::IntegerTuple hdl::ulcorner(Patch const& patch)
{
    if (std::holds_alternative<Object>(patch))
        return ulcorner(toindices(patch));
    //else if (std::holds_alternative<Indices>(patch))
    {
        auto const indices{std::get<Indices>(patch)};
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

hdl::IntegerTuple hdl::urcorner(Patch const& patch)
{
    if (std::holds_alternative<Object>(patch))
        return urcorner(toindices(patch));
    //else if (std::holds_alternative<Indices>(patch))
    {
        auto const indices{std::get<Indices>(patch)};
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

hdl::IntegerTuple hdl::llcorner(Patch const& patch)
{
    if (std::holds_alternative<Object>(patch))
        return llcorner(toindices(patch));
    //else if (std::holds_alternative<Indices>(patch))
    {
        auto const indices{std::get<Indices>(patch)};
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

hdl::IntegerTuple hdl::lrcorner(Patch const& patch)
{
    if (std::holds_alternative<Object>(patch))
        return lrcorner(toindices(patch));
    //else if (std::holds_alternative<Indices>(patch))
    {
        auto const indices{std::get<Indices>(patch)};
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

hdl::Grid hdl::crop(Grid const& grid, IntegerTuple const& start, Size const& dims)
{
    Grid result;

    if (start.first < 0 || start.second < 0 || start.first + dims.first > grid.size() || start.second + dims.second > grid[0].size())
        return result;

    for (size_t i{0}; i < dims.first; ++i)
    {
        std::vector<Integer> row;

        for (size_t j{0}; j < dims.second; ++j)
            row.emplace_back(grid[start.first + i][start.second + j]); 

        result.emplace_back(row);
    }

    return result;
}

hdl::Indices hdl::toindices(Patch const& patch)
{
    if (std::holds_alternative<Indices>(patch))
        return std::get<Indices>(patch);

    auto const& obj = std::get<Object>(patch);

    if (obj.empty())
        return Indices{};

    Indices result;

    for (auto const& cell : obj)
        result.insert(cell.second);

    return result;
}

hdl::Patch hdl::shift(Patch const& patch, IntegerTuple const& directions)
{
    if (std::holds_alternative<Object>(patch) && std::get<Object>(patch).empty())
        return patch;

    if (std::holds_alternative<Indices>(patch) && std::get<Indices>(patch).empty())
        return patch;

    auto const& [di, dj] = directions;

    if (std::holds_alternative<Object>(patch))
    {
        auto const& obj = std::get<Object>(patch);
        Object result;

        for (auto const& [value, pos] : obj)
        {
            auto const& [i, j] = pos;

            result.insert({value, {i + di, j + dj}});
        }

        return Patch{result};
    }

    auto const& indices = std::get<Indices>(patch);
    Indices result;

    for (auto const& [i, j] : indices)
        result.insert({i + di, j + dj});

    return Patch{result};
}

hdl::Integer hdl::uppermost(Patch const& patch)
{
    auto const indices = toindices(patch);
    auto result = std::numeric_limits<Integer>::max();

    for (auto const& [i, j] : indices)
        result = std::min(result, i);

    return result;
}

hdl::Integer hdl::lowermost(Patch const& patch)
{
    auto const indices = toindices(patch);
    auto result = std::numeric_limits<Integer>::max();

    for (auto const& [i, j] : indices)
        result = std::max(result, i);

    return result;
}

hdl::Integer hdl::leftmost(Patch const& patch)
{
    auto const indices = toindices(patch);
    auto result = std::numeric_limits<Integer>::max();

    for (auto const& [i, j] : indices)
        result = std::min(result, j);

    return result;
}

hdl::Integer hdl::rightmost(Patch const& patch)
{
    auto const indices = toindices(patch);
    auto result = std::numeric_limits<Integer>::min();

    for (auto const& [i, j] : indices)
        result = std::max(result, j);

    return result;
}

hdl::Grid hdl::rot90(hdl::Grid const& grid)
{
    if (grid.empty())
        return grid;

    auto const rows{static_cast<int>(grid.size())};
    auto const cols{static_cast<int>(grid[0].size())};

    Grid result(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            result[j][rows - 1 - i] = grid[i][j];
    }

    return result;
}

hdl::Grid hdl::rot180(hdl::Grid const& grid)
{
    if (grid.empty())
        return grid;

    auto const rows{static_cast<int>(grid.size())};
    auto const cols{static_cast<int>(grid[0].size())};

    Grid result(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            result[rows - 1 - i][cols - 1 - j] = grid[i][j];
    }

    return result;
}

hdl::Grid hdl::rot270(hdl::Grid const& grid)
{
    if (grid.empty())
        return grid;

    auto const rows{static_cast<int>(grid.size())};
    auto const cols{static_cast<int>(grid[0].size())};

    Grid result(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            result[cols - 1 - j][i] = grid[i][j];
    }

    return result;
}

hdl::Piece hdl::hmirror(hdl::Piece const& piece)
{
    if (std::holds_alternative<Grid>(piece))
    {
        auto grid = std::get<Grid>(piece);

        std::reverse(grid.begin(), grid.end());

        return Piece{grid};
    }

    auto patch = std::get<Patch>(piece);
    auto const ulc = ulcorner(patch);
    auto const lrc = lrcorner(patch);

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

hdl::Piece hdl::vmirror(hdl::Piece const& piece)
{
    if (std::holds_alternative<Grid>(piece))
    {
        auto grid = std::get<Grid>(piece);

        for (auto& row : grid)
            std::reverse(row.begin(), row.end());

        return Piece{grid};
    }

    auto patch = std::get<Patch>(piece);
    auto const ulc = ulcorner(patch);
    auto const lrc = lrcorner(patch);

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

hdl::Piece hdl::dmirror(hdl::Piece const& piece)
{
    if (std::holds_alternative<Grid>(piece))
    {
        auto const& grid = std::get<Grid>(piece);

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

    Patch patch = std::get<Patch>(piece);

    auto [a, b] = ulcorner(patch);

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

hdl::Piece hdl::cmirror(hdl::Piece const& piece)
{
    if (std::holds_alternative<Grid>(piece))
    {
        auto grid = std::get<Grid>(piece);

        std::reverse(grid.begin(), grid.end());

        for (auto& row : grid)
            std::reverse(row.begin(), row.end());

        return dmirror(grid);
    }

    return vmirror(dmirror(vmirror(piece)));
}

hdl::Grid hdl::hupscale(Grid const& grid, UnsignedInteger const& factor)
{
    Grid result;

    for (const auto& row : grid)
    {
        std::vector<Integer> new_row;
        new_row.reserve(row.size() * factor);

        for (const auto& cell : row)
        {
            for (UnsignedInteger i{0}; i < factor; ++i)
                new_row.emplace_back(cell);
        }

        result.emplace_back(new_row);
    }

    return result;
}

hdl::Grid hdl::vupscale(Grid const& grid, UnsignedInteger const& factor)
{
    Grid result;
    result.reserve(grid.size() * factor);

    for (const auto& row : grid)
    {
        for (UnsignedInteger k = 0; k < factor; ++k)
            result.emplace_back(row);
    }

    return result;
}

hdl::Element hdl::upscale(Element const& element, UnsignedInteger const& factor)
{
    if (std::holds_alternative<Grid>(element))
    {
        auto const& grid = std::get<Grid>(element);

        Grid result;

        for (const auto& row : grid)
        {
            std::vector<Integer> upscaled_row;

            upscaled_row.reserve(row.size() * factor);

            for (auto const& value : row)
            {
                for (Integer k = 0; k < factor; ++k)
                    upscaled_row.emplace_back(value);
            }

            for (Integer k = 0; k < factor; ++k)
                result.emplace_back(upscaled_row);
        }

        return Element{result};
    }

    auto const& obj = std::get<Object>(element);

    if (obj.empty())
        return Element{Object{}};

    auto const [di_inv, dj_inv] = ulcorner(obj);
    Integer const di = -di_inv;
    Integer const dj = -dj_inv;

    auto const p = shift(Patch{obj}, IntegerTuple{di, dj});
    Object normed_obj = std::get<Object>(p);
    Object result;

    for (auto const& [value, pos] : normed_obj)
    {
        auto const& [i, j] = pos;

        for (Integer io = 0; io < factor; ++io)
        {
            for (Integer jo = 0; jo < factor; ++jo)
                result.insert({value, {i * factor + io, j * factor + jo}});
        }
    }

    return std::get<Object>(shift(result, IntegerTuple{di_inv, dj_inv}));
}

hdl::Grid hdl::downscale(Grid const& grid, UnsignedInteger const& factor)
{
    if (grid.empty())
        return grid;

    auto const h = static_cast<Integer>(grid.size());
    auto const w = static_cast<Integer>(grid[0].size());

    Grid temp;

    for (Integer i = 0; i < h; ++i)
    {
        std::vector<Integer> row;

        for (Integer j = 0; j < w; ++j)
        {
            if (j % factor == 0)
                row.emplace_back(grid[i][j]);
        }

        temp.emplace_back(row);
    }

    Grid result;

    for (Integer i = 0; i < static_cast<Integer>(temp.size()); ++i)
    {
        if (i % factor == 0)
            result.emplace_back(temp[i]);
    }

    return result;
}

hdl::Grid hdl::hconcat(Grid const& a, Grid const& b)
{
    Grid result;
    auto const rows = std::min(a.size(), b.size());
    result.reserve(rows);

    for (size_t i = 0; i < rows; ++i)
    {
        std::vector<Integer> row;
        row.reserve(a[i].size() + b[i].size());

        row.insert(row.end(), a[i].begin(), a[i].end());
        row.insert(row.end(), b[i].begin(), b[i].end());
        result.emplace_back(std::move(row));
    }

    return result;
}

hdl::Grid hdl::vconcat(Grid const& a, Grid const& b)
{
    Grid result;
    result.reserve(a.size() + b.size());

    result.insert(result.end(), a.begin(), a.end());
    result.insert(result.end(), b.begin(), b.end());

    return result;
}

hdl::Grid hdl::replace(Grid const& grid, Integer const& replacee, Integer const& replacer)
{
    Grid result = grid;

    for (auto& row : result)
    {
        for (auto& v : row)
        {
            if (v == replacee)
                v = replacer;
        }
    }

    return result;
}

hdl::Grid hdl::switch_(Grid const& grid, Integer const& a, Integer const& b)
{
    Grid result = grid;

    for (auto& row : result)
    {
        for (auto& v : row)
        {
            if (v == a)
                v = b;
            else if (v == b)
                v = a;
        }
    }

    return result;
}

hdl::Grid hdl::tophalf(Grid const& grid)
{
    auto const mid = grid.size() / 2;

    return Grid(grid.begin(), grid.begin() + mid);
}

hdl::Grid hdl::bottomhalf(Grid const& grid)
{
    auto const mid = grid.size() / 2 + grid.size() % 2;

    return Grid(grid.begin() + mid, grid.end());
}

hdl::Grid hdl::lefthalf(Grid const& grid)
{
    return rot270(tophalf(rot90(grid)));
}

hdl::Grid hdl::righthalf(Grid const& grid)
{
    return rot270(bottomhalf(rot90(grid)));
}
