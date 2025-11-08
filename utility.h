#ifndef UTILITY_H
#define UTILITY_H

#include <algorithm>
#include <any>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <generator>
#include <set>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

template <typename T, typename = void>
struct is_string_convertible : std::false_type {};

template <typename T>
struct is_string_convertible<
    T,
    std::void_t<
    decltype(static_cast<std::string>(std::declval<T>()))
    >
> : std::true_type
{
};

template <typename T>
constexpr bool is_string_convertible_v =
is_string_convertible<T>::value ||
std::is_arithmetic_v<T>;

template <typename T>
std::string toString(T const& value)
{
	std::ostringstream oss;

	oss << value;

	return oss.str();
}

template <typename... Ts>
std::any variantToAny(std::variant<Ts...> const& var)
{
    return std::visit([] (auto const& v) { return std::make_any<std::decay_t<decltype(v)> >(v); }, var);
}

template <typename... Ts>
std::variant<Ts...> anyToVariant(std::any const& var)
{
    auto tryCast = [&](auto self, auto firstType) -> std::variant<Ts...>
    {
        using T = decltype(firstType);

        if (var.type() == typeid(T))
            return std::variant<Ts...>(std::any_cast<T>(var));

        if constexpr (sizeof...(Ts) > 1) {
            using Rest = std::tuple<Ts...>;

            return std::visit(
                [&](auto&& v) -> std::variant<Ts...> { return v; },
                self(self, std::tuple_element_t<1, Rest>{})
                );
        } else {
            throw std::bad_any_cast();
        }
    };

    std::variant<Ts...> result;
    bool matched{false};

    ([&] {
        if (!matched && var.type() == typeid(Ts)) {
            result = std::variant<Ts...>(std::any_cast<Ts>(var));
            matched = true;
        }
    }(), ...);

    if (!matched)
        throw std::bad_any_cast();

    return result;
}

template <typename... Ts>
size_t variantToHash(std::variant<Ts...> const& v)
{
    std::vector<bool> bits;

    {
        auto const index{static_cast<uint8_t>(v.index())};
        std::bitset<8> const bs{index};

        for (size_t j{0}; j < bs.size(); ++j)
            bits.emplace_back(bs[j]);
    }

    std::visit(
        [&] (auto&& val)
        {
            using T = std::decay_t<decltype(val)>;

            auto const ptr = reinterpret_cast<uint8_t const*>(&val);

            for (size_t i{0}; i < sizeof(T); ++i)
            {
                std::bitset<8> const bs{ptr[i]};

                for (size_t j{0}; j < bs.size(); ++j)
                    bits.emplace_back(bs[j]);
            }
        }, v);

    return std::hash<std::vector<bool> >{}(bits);
}

inline std::size_t levenshtein(std::string const& a, std::string const& b)
{
    std::size_t const n = a.size(), m = b.size();
    std::vector<std::size_t> dp(m+1);

    for (std::size_t j = 0; j <= m; ++j)
        dp[j] = j;

    for (std::size_t i = 1; i <= n; ++i)
    {
        std::size_t prev = dp[0];
        dp[0] = i;

        for (std::size_t j = 1; j <= m; ++j)
        {
            std::size_t const cur = dp[j];

            if (a[i-1] == b[j-1])
                dp[j] = prev;
            else
            {
                std::array<size_t, 3> const arr{
                    dp[j],       // deletion
                    dp[j-1],     // insertion
                    prev         // substitution
                };

                dp[j] = 1 + *std::min_element(arr.begin(), arr.end());
            }

            prev = cur;
        }
    }

    return dp[m];
}

template<typename T>
std::generator<std::vector<T> > cartesianProduct(std::vector<T> const& l, size_t n)
{
    auto const total{(size_t)std::pow(l.size(), n)};
    std::vector<T> combo(n);

    for (size_t i = 0; i < total; ++i)
    {
        size_t index{i};

        for (long j = (long)n - 1; j >= 0; --j)
        {
            combo[j] = l[index % l.size()];
            index /= l.size();
        }

        co_yield combo;
    }
}

template <typename Matrix>
Matrix swapCols(Matrix const& a, int i, int j)
{
    if (!(0 <= i && i < a.cols() && 0 <= j && j < a.cols()))
        return a;

    Matrix b{a};

    auto const tmp{b.col(i).eval()};
    b.col(i) = b.col(j);
    b.col(j) = tmp;

    return b;
}

template <typename Matrix>
Matrix swapRows(Matrix const& a, int i, int j)
{
    if (!(0 <= i && i < a.rows() && 0 <= j && j < a.rows()))
        return a;

    Matrix b{a};

    auto const tmp{b.row(i).eval()};
    b.row(i) = b.row(j);
    b.row(j) = tmp;

    return b;
}

template <typename Matrix>
Matrix fliplr(Matrix const& a)
{
    Matrix b{a};

    for (int j = 0; j < b.cols() / 2; ++j)
        b = swapCols(b, j, (int)b.cols() - 1 - j);

    return b;
}

template <typename Matrix>
Matrix flipud(Matrix const& a)
{
    Matrix b{a};

    for (int i = 0; i < b.rows() / 2; ++i)
        b = swapRows(b, i, (int)b.rows() - 1 - i);

    return b;
}

template <typename Matrix>
Matrix hline(Matrix const& a, int row, typename Matrix::Scalar const& value)
{
    if (!(0 <= row && row < a.rows()))
        return a;

    Matrix b{a};

    b.row(row).fill(value);

    return b;
}

template <typename Matrix>
Matrix vline(Matrix const& a, int col, typename Matrix::Scalar const& value)
{
    if (!(0 <= col && col < a.cols()))
        return a;

    Matrix b{a};

    b.col(col).fill(value);

    return b;
}

template <typename Matrix>
Matrix hlineright(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
{
    if (!(0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols()))
        return a;

    Matrix b{a};

    b.row(at.first).tail(b.cols() - at.second).fill(value);

    return b;
}

template <typename Matrix>
Matrix hlineleft(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
{
    if (!(0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols()))
        return a;

    Matrix b{a};

    b.row(at.first).head(at.second).fill(value);

    return b;
}

template <typename Matrix>
Matrix vlinedown(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
{
    if (!(0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols()))
        return a;

    Matrix b{a};

    b.col(at.second).tail(b.rows() - at.first).fill(value);

    return b;
}

template <typename Matrix>
Matrix vlineup(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
{
    if (!(0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols()))
        return a;

    Matrix b{a};

    b.col(at.second).head(at.first).fill(value);

    return b;
}

template <typename Matrix>
Matrix put(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
{
    if (!(0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols()))
        return a;

    Matrix b{a};

    b(at.first, at.second) = value;

    return b;
}

template <typename Matrix>
typename Matrix::Scalar at(Matrix const& a, std::pair<int, int> const& at)
{
    if (!(0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols()))
        return typename Matrix::Scalar{};

    return a(at.first, at.second);
}

template <typename Matrix>
Matrix zero(std::pair<int, int> const& size)
{
    if (!(0 <= size.first && 0 <= size.second))
        return Matrix{};

    Matrix m;
    m.resize(size.first, size.second);
    m.setZero();

    return m;
}

template <typename Matrix>
Matrix ones(std::pair<int, int> const& size)
{
    if (!(0 <= size.first && 0 <= size.second))
        return Matrix{};

    Matrix m;
    m.resize(size.first, size.second);
    m.setOnes();

    return m;
}

template <typename Matrix>
Matrix identity(std::pair<int, int> const& size)
{
    if (!(0 <= size.first && 0 <= size.second))
        return Matrix{};

    Matrix m;
    m.resize(size.first, size.second);
    m.setIdentity();

    return m;
}

template <typename Matrix>
Matrix modMatrix(Matrix const& a, Matrix const& b)
{
    if (!(a.cols() == b.cols() && a.rows() == b.rows()) || !a.cols() || !a.rows() || !b.cols() || !b.rows())
        return Matrix{};

    Matrix c{a};

    for (int i = 0; i < c.rows(); ++i)
    {
        for (int j = 0; j < c.cols(); ++j)
        {
            if (!b(i, j))
                c(i, j) = 0;
            else
                c(i, j) %= b(i, j);
        }
    }

    return b;
}

template <typename Matrix>
Matrix andMatrix(Matrix const& a, Matrix const& b)
{
    if (!(a.cols() == b.cols() && a.rows() == b.rows()) || !a.cols() || !a.rows() || !b.cols() || !b.rows())
        return Matrix{};

    Matrix c{a};

    for (int i = 0; i < c.rows(); ++i)
    {
        for (int j = 0; j < c.cols(); ++j)
            c(i, j) &= b(i, j);
    }

    return b;
}

template <typename Matrix>
Matrix orMatrix(Matrix const& a, Matrix const& b)
{
    if (!(a.cols() == b.cols() && a.rows() == b.rows()) || !a.cols() || !a.rows() || !b.cols() || !b.rows())
        return Matrix{};

    Matrix c{a};

    for (int i = 0; i < c.rows(); ++i)
    {
        for (int j = 0; j < c.cols(); ++j)
            c(i, j) |= b(i, j);
    }

    return b;
}

template <typename Matrix>
Matrix xorMatrix(Matrix const& a, Matrix const& b)
{
    if (!(a.cols() == b.cols() && a.rows() == b.rows()) || !a.cols() || !a.rows() || !b.cols() || !b.rows())
        return Matrix{};

    Matrix c{a};

    for (int i = 0; i < c.rows(); ++i)
    {
        for (int j = 0; j < c.cols(); ++j)
            c(i, j) ^= b(i, j);
    }

    return b;
}

template <typename Matrix>
Matrix rot90(Matrix const& a)
{
    return flipud(Matrix{a.transpose()});
}

inline std::vector<std::pair<int, int> > neighbors(std::pair<int, int> const& loc, std::pair<int, int> const& size, bool diagonals)
{
    std::vector<std::pair<int, int> > n;

    for (int di = -1; di <= 1; ++di)
    {
        for (int dj = -1; dj <= 1; ++dj)
        {
            if (!di && !dj)
                continue;

            auto const i{loc.first + di};
            auto const j{loc.second + dj};

            if (!(0 <= i && i < size.first && 0 <= j && j < size.second))
                continue;

            if (!diagonals && std::abs(di) == std::abs(dj))
                continue;

            n.emplace_back(std::make_pair(i, j));
        }
    }

    return n;
}

template <typename Matrix>
Matrix fillRegionAt(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& x, bool diagonals)
{
    if (!(0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols()))
        return a;

    auto b{a};

    std::set<std::pair<int, int> > s;
    std::set<std::pair<int, int> > stack;
    stack.emplace(at);
    auto const v{a(at.first, at.second)};

    while (stack.size())
    {
        auto const loc{*stack.begin()};
        stack.erase(stack.begin());

        if (s.find(loc) == s.end())
        {
            s.emplace(loc);

            if (std::abs(b(loc.first, loc.second) - v) < 1.0e-6)
            {
                b(loc.first, loc.second) = x;

                for (auto const& n : neighbors(loc, std::make_pair((int)b.rows(), (int)b.cols()), diagonals))
                    stack.emplace(n);
            }
        }
    }

    return b;
}

template <typename Matrix>
std::vector<std::pair<int, int> > region(Matrix const& a, std::pair<int, int> const& at, bool diagonals)
{
    if (!(0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols()))
        return std::vector<std::pair<int, int> >{};

    std::set<std::pair<int, int> > s;
    std::set<std::pair<int, int> > stack;
    stack.emplace(at);
    auto const v{a(at.first, at.second)};
    std::vector<std::pair<int, int> > indices;

    while (stack.size())
    {
        auto const loc{*stack.begin()};
        stack.erase(stack.begin());

        if (s.find(loc) == s.end())
        {
            s.emplace(loc);

            if (std::abs(a(loc.first, loc.second) - v) < 1.0e-6)
            {
                indices.emplace_back(loc);

                for (auto const& n : neighbors(loc, std::make_pair((int)a.rows(), (int)a.cols()), diagonals))
                    stack.emplace(n);
            }
        }
    }

    return indices;
}

template <typename Matrix>
Matrix fillRegion(Matrix const& a, std::vector<std::pair<int, int> > const& region, typename Matrix::Scalar const& x)
{
    Matrix b{a};

    for (auto const& p : region)
    {
        if (0 <= p.first && p.first < b.rows() && 0 <= p.second && p.second < b.cols())
            b(p.first, p.second) = x;
    }

    return b;
}

template <typename Matrix>
Matrix matrixRegion(Matrix const& a, std::vector<std::pair<int, int> > const& region)
{
    int iMin{a.rows()};
    int iMax{0};
    int jMin{a.cols()};
    int jMax{0};

    for (auto const& p : region)
    {
        iMin = std::min(iMin, p.first);
        iMax = std::max(iMax, p.first);
        jMin = std::min(jMin, p.second);
        jMax = std::max(jMax, p.second);
    }

    return a.block(iMin, iMax, jMin, jMax);
}

#endif // UTILITY_H
