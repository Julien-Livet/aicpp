#ifndef AICPP_UTILITY_H
#define AICPP_UTILITY_H

#include <algorithm>
#include <any>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <limits>
#include <generator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include <Eigen/Core>

namespace aicpp
{
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

    template <typename Matrix>
    bool validIndex(Matrix const& a, int i, int j)
    {
        return (0 <= i && i < a.rows() && 0 <= j && j < a.cols());
    }

    template <typename Matrix>
    bool validIndex(Matrix const& a, std::pair<int, int> const& at)
    {
        return (0 <= at.first && at.first < a.rows() && 0 <= at.second && at.second < a.cols());
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
        if (!validIndex(a, i, j))
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
        if (!validIndex(a, i, j))
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
        if (!validIndex(a, at))
            return a;

        Matrix b{a};

        b.row(at.first).tail(b.cols() - at.second).fill(value);

        return b;
    }

    template <typename Matrix>
    Matrix hlineleft(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
    {
        if (!validIndex(a, at))
            return a;

        Matrix b{a};

        b.row(at.first).head(at.second).fill(value);

        return b;
    }

    template <typename Matrix>
    Matrix vlinedown(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
    {
        if (!validIndex(a, at))
            return a;

        Matrix b{a};

        b.col(at.second).tail(b.rows() - at.first).fill(value);

        return b;
    }

    template <typename Matrix>
    Matrix vlineup(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
    {
        if (!validIndex(a, at))
            return a;

        Matrix b{a};

        b.col(at.second).head(at.first).fill(value);

        return b;
    }

    template <typename Matrix>
    Matrix put(Matrix const& a, std::pair<int, int> const& at, typename Matrix::Scalar const& value)
    {
        if (!validIndex(a, at))
            return a;

        Matrix b{a};

        b(at.first, at.second) = value;

        return b;
    }

    template <typename Matrix>
    typename Matrix::Scalar at(Matrix const& a, std::pair<int, int> const& at)
    {
        if (!validIndex(a, at))
            return typename Matrix::Scalar{};

        return a(at.first, at.second);
    }

    template <typename Matrix>
    Matrix zero(std::pair<size_t, size_t> const& size)
    {
        Matrix m;
        m.resize(size.first, size.second);
        m.setZero();

        return m;
    }

    template <typename Matrix>
    Matrix ones(std::pair<size_t, size_t> const& size)
    {
        Matrix m;
        m.resize(size.first, size.second);
        m.setOnes();

        return m;
    }

    template <typename Matrix>
    Matrix identity(std::pair<size_t, size_t> const& size)
    {
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
        if (!validIndex(a, at))
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
        if (!validIndex(a, at))
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
            if (validIndex(b, p))
                b(p.first, p.second) = x;
        }

        return b;
    }

    template <typename Matrix>
    Matrix fillRegions(Matrix const& a, std::vector<std::vector<std::pair<int, int> > > const& regions, typename Matrix::Scalar const& x)
    {
        Matrix b{a};

        for (auto const& region : regions)
            b = fillRegion(b, region, x);

        return b;
    }

    template <typename Matrix>
    Matrix matrixRegion(Matrix const& a, std::vector<std::pair<int, int> > const& region)
    {
        if (!a.rows() || !a.cols())
            return Matrix{};

        auto iMin{(int)a.rows()};
        int iMax{0};
        auto jMin{(int)a.cols()};
        int jMax{0};

        for (auto const& p : region)
        {
            iMin = std::min(iMin, p.first);
            iMax = std::max(iMax, p.first);
            jMin = std::min(jMin, p.second);
            jMax = std::max(jMax, p.second);
        }

        if (iMin <= iMax && jMin <= jMax
            && 0 <= iMin && iMin < a.rows()
            && 0 <= iMax && iMax < a.rows()
            && 0 <= jMin && jMin < a.cols()
            && 0 <= jMax && jMax < a.cols())
            return a.block(iMin, jMin, iMax - iMin + 1, jMax - jMin + 1);

        return Matrix{};
    }

    template <typename Matrix>
    Matrix dotSegment(Matrix const& a, std::pair<int, int> const& begin, std::pair<int, int> const& end, typename Matrix::Scalar const& value, int dotStep)
    {
        if (dotStep < 1)
            return a;

        Matrix m{a};

        Eigen::Vector2d const b{begin.first, begin.second};
        Eigen::Vector2d const e{end.first, end.second};
        auto const u{e - b};
        Eigen::Vector2d v{u / u.norm()};

        auto const min{v.minCoeff()};

        if (min > std::numeric_limits<double>::epsilon())
            v *= min;

        auto const step{v.norm() / u.norm()};
        size_t i{0};

        for (double t{0}; t < 1 + 0.1 * step; t += step)
        {
            if (i % dotStep == 0)
                m((int)std::round(b[0] + t * u[0]), (int)std::round(b[1] + t * u[1])) = value;

            ++i;
        }

        return m;
    }

    template <typename Matrix>
    Matrix tile(Matrix const& a, std::pair<size_t, size_t> const& reps)
    {
        if (!reps.first || !reps.second)
            return Matrix{};

        Matrix m;
        m.resize(a.rows() * reps.first, a.cols() * reps.second);

        for (int i{0}; i < reps.first; ++i)
        {
            for (int j{0}; j < reps.second; ++j)
                m.block(i * a.rows(), j * a.cols(), a.rows(), a.cols()) = a;
        }

        return m;
    }

    template <typename Matrix>
    Matrix put(Matrix const& dst, Matrix const& src, std::pair<int, int> const& at)
    {
        Matrix m{dst};

        for (int i{0}; i < src.rows(); ++i)
        {
            for (int j{0}; j < src.cols(); ++j)
            {
                if (0 <= i + at.first && i + at.first < dst.rows() && 0 <= j + at.second && j + at.second < dst.cols())
                    m(i + at.first, j + at.second) = src(i, j);
            }
        }

        return m;
    }

    template <typename Matrix>
    Matrix placeRegion(Matrix const& a, std::vector<std::pair<int, int> > const& region, std::pair<int, int> const& at, typename Matrix::Scalar const& x)
    {
        Matrix b{a};

        if (region.empty())
            return b;

        for (auto const& p : region)
        {
            if (0 <= at.first + p.first - region.front().first && at.first + p.first - region.front().first < b.rows()
                && 0 <= at.second + p.second - region.front().second && at.second + p.second - region.front().second < b.cols())
                b(at.first + p.first - region.front().first, at.second + p.second - region.front().second) = x;
        }

        return b;
    }

    template <typename Matrix>
    Matrix map(Matrix const& dst, std::map<typename Matrix::Scalar, typename Matrix::Scalar> const& mapping)
    {
        Matrix m{dst};

        for (int i{0}; i < m.rows(); ++i)
        {
            for (int j{0}; j < m.cols(); ++j)
            {
                auto const it{mapping.find(m(i, j))};

                if (it != mapping.end())
                    m(i, j) = it->second;
            }
        }

        return m;
    }

    inline std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > sameFirst(std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > const& pairs)
    {
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > result;

        for (auto const& p : pairs)
        {
            if (p.first.first == p.second.first)
                result.emplace_back(p);
        }

        return result;
    }

    inline std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > sameSecond(std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > const& pairs)
    {
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > result;

        for (auto const& p : pairs)
        {
            if (p.first.second == p.second.second)
                result.emplace_back(p);
        }

        return result;
    }
/*
    inline std::vector<std::pair<int, int> > smallestRegion(std::vector<std::vector<std::pair<int, int> > > const& regions)
    {
        std::vector<std::pair<size_t, size_t> > sizes;
        sizes.reserve(regions.size());

        for (size_t i{0}; i < regions.size(); ++i)
            sizes.emplace_back(std::make_pair(i, regions[i].size()));

        std::sort(sizes.begin(), sizes.end(), [] (auto const& x, auto const y) { return x.second < y.second; });

        if (sizes.size())
            return regions[sizes.front().first];

        return std::vector<std::pair<int, int> >{};
    }

    inline std::vector<std::pair<int, int> > biggestRegion(std::vector<std::vector<std::pair<int, int> > > const& regions)
    {
        std::vector<std::pair<size_t, size_t> > sizes;
        sizes.reserve(regions.size());

        for (size_t i{0}; i < regions.size(); ++i)
            sizes.emplace_back(std::make_pair(i, regions[i].size()));

        std::sort(sizes.begin(), sizes.end(), [] (auto const& x, auto const y) { return x.second < y.second; });

        if (sizes.size())
            return regions[sizes.back().first];

        return std::vector<std::pair<int, int> >{};
    }
*/
    inline std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > regionPairs(std::vector<std::vector<std::pair<int, int> > > const& regions)
    {
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > pairs;

        for (size_t i1{0}; i1 < regions.size(); ++i1)
        {
            for (size_t j1{i1 + 1}; j1 < regions.size(); ++j1)
            {
                for (size_t i2{0}; i2 < regions[i1].size(); ++i2)
                {
                    for (size_t j2{0}; j2 < regions[j1].size(); ++j2)
                        pairs.emplace_back(std::make_pair(regions[i1][i2], regions[j1][j2]));
                }
            }
        }

        return pairs;
    }

    template <typename Matrix>
    std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > pairedRegions(Matrix const& a, std::vector<std::vector<std::pair<int, int> > > const& regions)
    {
        std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > result;

        for (size_t i{0}; i < regions.size(); ++i)
        {
            if (regions[i].empty())
                continue;

            for (size_t j{i + 1}; j < regions.size(); ++j)
            {
                if (regions[j].empty())
                    continue;

                Matrix b{a};
                auto const value{a.maxCoeff() + 1};

                b = fillRegion(b, regions[i], value);
                b = fillRegion(b, regions[j], value);

                auto const r{region(b, regions[i].front(), false)};

                if (r.size() == regions[i].size() + regions[j].size())
                {
                    std::vector<std::pair<size_t, size_t> > pairs{regions[i].begin(), regions[i].end()};

                    pairs.append_range(regions[j]);

                    std::sort(pairs.begin(), pairs.end(),
                              [] (auto const& x, auto const& y) -> bool
                              {
                                  if (x.first == y.first)
                                      return x.second < y.second;

                                  return x.first < y.first;
                              }
                              );

                    if (std::find(regions[i].begin(), regions[i].end(), pairs.front()) != regions[i].end())
                        result.emplace_back(std::make_pair(regions[j], regions[i]));
                    else
                        result.emplace_back(std::make_pair(regions[i], regions[j]));
                }
            }
        }

        return result;
    }

    template <typename Matrix>
    std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > filterValuePairedRegions(Matrix const& a, std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > const& pairedRegions, typename Matrix::Scalar const& value, bool first)
    {
        std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > result;

        for (auto const& pairedRegion : pairedRegions)
        {
            auto const& r{first ? pairedRegion.first : pairedRegion.second};

            if (r.empty())
                continue;

            if (a(r.front().first, r.front().second) == value)
                result.emplace_back(pairedRegion);
        }

        return result;
    }

    inline std::vector<std::pair<int, int> > regionContour(std::vector<std::pair<int, int> > const& region)
    {
        std::set<std::pair<int, int> > contour;

        for (auto const& p : region)
        {
            auto const n{neighbors(p, std::make_pair(p.first + 2, p.second + 2), true)};

            for (auto const& q : n)
                contour.emplace(q);
        }

        for (auto const& p : region)
            contour.erase(p);

        return std::vector<std::pair<int, int> >{contour.begin(), contour.end()};
    }

    template <typename Matrix>
    bool closedPairedRegion(Matrix const& a, std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > const& pairedRegion)
    {
        auto const contour{regionContour(pairedRegion.first)};
        std::set<std::pair<int, int> > modifiedContour{contour.begin(), contour.end()};

        for (auto const& p : pairedRegion.second)
            modifiedContour.erase(p);

        for (auto const& p : modifiedContour)
        {
            if (!validIndex(a, p))
                return false;
        }

        return modifiedContour.size() < pairedRegion.second.size();
    }

    template <typename Matrix>
    std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > filterClosedPaireRegions(Matrix const& a, std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > const& pairedRegions, bool closed)
    {
        std::vector<bool> closedRegions;
        closedRegions.reserve(pairedRegions.size());

        for (auto const& r : pairedRegions)
            closedRegions.emplace_back(closedPairedRegion(a, r));

        std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > result;

        for (size_t i{0}; i < pairedRegions.size(); ++i)
        {
            if ((closed && closedRegions[i])
                || (!closed && !closedRegions[i]))
                    result.emplace_back(pairedRegions[i]);
        }

        return result;
    }

    inline std::vector<std::vector<std::pair<int, int> > > memberPairedRegions(std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > const& pairedRegions, bool first)
    {
        std::vector<std::vector<std::pair<int, int> > > result;
        result.reserve(pairedRegions.size());

        for (auto const& r : pairedRegions)
            result.emplace_back(first ? r.first : r.second);

        return result;
    }

    template <typename Matrix>
    Matrix segments(Matrix const& dst, std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > const& pairs, typename Matrix::Scalar const& value, bool start, bool finish)
    {
        Matrix m{dst};

        for (auto const& pair : pairs)
        {
            if (validIndex(m, pair.first) && validIndex(m, pair.second))
            {
                auto const s{m(pair.first.first, pair.first.second)};
                auto const f{m(pair.second.first, pair.second.second)};

                m = dotSegment(m, pair.first, pair.second, value, 1);

                if (start)
                    m(pair.first.first, pair.first.second) = s;
                if (finish)
                    m(pair.second.first, pair.second.second) = f;
            }
        }

        return m;
    }
}

#endif // AICPP_UTILITY_H
