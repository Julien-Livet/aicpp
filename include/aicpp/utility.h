#ifndef AICPP_UTILITY_H
#define AICPP_UTILITY_H

#include <any>
#include <generator>
#include <map>
#include <set>
#include <typeindex>
#include <vector>

#include <Eigen/Core>

#include <boost/algorithm/string.hpp>

namespace aicpp
{
    namespace utility
    {
        template <typename T>
        std::generator<std::vector<T> > cartesianProduct(std::vector<std::vector<T> > lists)
        {
            if (lists.empty())
                co_return;

            size_t const n{lists.size()};
            std::vector<std::size_t> indices(n, 0);
            std::vector<T> current(n);

            while (true)
            {
                for (size_t i{0}; i < n; ++i)
                    current[i] = lists[i][indices[i]];

                co_yield current;

                std::size_t i{n};

                while (i > 0)
                {
                    --i;

                    if (++indices[i] < lists[i].size())
                        break;

                    indices[i] = 0;
                }

                if (i == 0 && indices[0] == 0)
                    break;
            }
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

        template <typename S, typename T>
        double cost(double initCost, S const& val, T const& target)
        {
            return std::abs(initCost + std::abs(val - target));
        }

        template <typename S, typename T>
        double heuristic(S const& val, T const& target)
        {
            if constexpr (std::is_same_v<S, std::any> && std::is_same_v<T, std::any>)
            {
                if (val.type() == typeid(bool) && target.type() == typeid(bool))
                    return heuristic(std::any_cast<bool>(val), std::any_cast<bool>(target));
                else if (val.type() == typeid(char) && target.type() == typeid(char))
                    return heuristic(std::any_cast<char>(val), std::any_cast<char>(target));
                else if (val.type() == typeid(double) && target.type() == typeid(double))
                    return heuristic(std::any_cast<double>(val), std::any_cast<double>(target));
                else if (val.type() == typeid(Eigen::MatrixXd) && target.type() == typeid(Eigen::MatrixXd))
                    return heuristic(std::any_cast<Eigen::MatrixXd>(val), std::any_cast<Eigen::MatrixXd>(target));
                else if (val.type() == typeid(Eigen::MatrixXf) && target.type() == typeid(Eigen::MatrixXf))
                    return heuristic(std::any_cast<Eigen::MatrixXf>(val), std::any_cast<Eigen::MatrixXf>(target));
                else if (val.type() == typeid(Eigen::MatrixXi) && target.type() == typeid(Eigen::MatrixXi))
                    return heuristic(std::any_cast<Eigen::MatrixXi>(val), std::any_cast<Eigen::MatrixXi>(target));
                else if (val.type() == typeid(float) && target.type() == typeid(float))
                    return heuristic(std::any_cast<float>(val), std::any_cast<float>(target));
                else if (val.type() == typeid(int) && target.type() == typeid(int))
                    return heuristic(std::any_cast<int>(val), std::any_cast<int>(target));
                else if (val.type() == typeid(long) && target.type() == typeid(long))
                    return heuristic(std::any_cast<long>(val), std::any_cast<long>(target));
                else if (val.type() == typeid(std::string) && target.type() == typeid(std::string))
                    return heuristic(std::any_cast<std::string>(val), std::any_cast<std::string>(target));
                else if (val.type() == typeid(std::vector<Eigen::MatrixXd>) && target.type() == typeid(std::vector<Eigen::MatrixXd>))
                    return heuristic(std::any_cast<std::vector<Eigen::MatrixXd> >(val), std::any_cast<std::vector<Eigen::MatrixXd> >(target));
                else if (val.type() == typeid(std::vector<Eigen::MatrixXf>) && target.type() == typeid(std::vector<Eigen::MatrixXf>))
                    return heuristic(std::any_cast<std::vector<Eigen::MatrixXf> >(val), std::any_cast<std::vector<Eigen::MatrixXf> >(target));
                else if (val.type() == typeid(std::vector<Eigen::MatrixXi>) && target.type() == typeid(std::vector<Eigen::MatrixXi>))
                    return heuristic(std::any_cast<std::vector<Eigen::MatrixXi> >(val), std::any_cast<std::vector<Eigen::MatrixXi> >(target));
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                if constexpr (std::is_same_v<S, std::any>)
                {
                    if (val.type() == typeid(std::string))
                        return heuristic(std::any_cast<std::string>(val), target);
                }
                else if constexpr (is_string_convertible_v<S>)
                {
                    double cost{std::is_same_v<S, std::string> ? 0.0 : 1.0};

                    auto const s{toString(val)};
                    auto a{s}, b{target};

                    if (a.find(b) != std::string::npos)
                        std::swap(a, b);

                    if (!a.empty() && b.find(a) != std::string::npos)
                    {
                        std::vector<std::string> matches;

                        return cost + 1.0 - 1.0 / boost::algorithm::find_all(matches, b, a).size() + 1.0 / (1.0 + a.size()) - 1 / (1.0 + b.size());
                    }

                    return cost + 1.0 / (1.0 + a.size()) - 1.0 / (1.0 + b.size()) + levenshtein(a, b);
                }
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                if constexpr (std::is_same_v<S, double>)
                    return cost(0.0, val, target);
                else if constexpr (std::is_same_v<S, float>)
                    return cost(1.0, val, target);
                else if constexpr (std::is_same_v<S, int>)
                    return cost(2.0, val, target);
                else if constexpr (std::is_same_v<S, long>)
                    return cost(2.0, val, target);
            }
            else if constexpr (std::is_same_v<T, float>)
            {
                if constexpr (std::is_same_v<S, float>)
                    return cost(0.0, val, target);
                else if constexpr (std::is_same_v<S, double>)
                    return cost(1.0, val, target);
                else if constexpr (std::is_same_v<S, int>)
                    return cost(2.0, val, target);
                else if constexpr (std::is_same_v<S, long>)
                    return cost(2.0, val, target);
            }
            else if constexpr (std::is_same_v<T, int>)
            {
                if constexpr (std::is_same_v<S, int>)
                    return cost(0.0, val, target);
                else if constexpr (std::is_same_v<S, long>)
                    return cost(1.0, val, target);
                else if constexpr (std::is_same_v<S, double>)
                    return cost(2.0, val, target);
                else if constexpr (std::is_same_v<S, float>)
                    return cost(2.0, val, target);
            }
            else if constexpr (std::is_same_v<T, long>)
            {
                if constexpr (std::is_same_v<S, long>)
                    return cost(0.0, val, target);
                else if constexpr (std::is_same_v<S, int>)
                    return cost(1.0, val, target);
                else if constexpr (std::is_same_v<S, double>)
                    return cost(2.0, val, target);
                else if constexpr (std::is_same_v<S, float>)
                    return cost(2.0, val, target);
            }
            else if constexpr (std::is_same_v<T, Eigen::MatrixXd>)
            {
                if constexpr (std::is_same_v<S, Eigen::MatrixXd>)
                {
                    if (!(val.rows() == target.rows() && val.cols() == target.cols()))
                        return 100.0 + std::abs(val.sum() - target.sum());

                    return std::abs((val - target).norm());
                }
            }
            else if constexpr (std::is_same_v<T, Eigen::MatrixXf>)
            {
                if constexpr (std::is_same_v<S, Eigen::MatrixXf>)
                {
                    if (!(val.rows() == target.rows() && val.cols() == target.cols()))
                        return 100.0 + std::abs(val.sum() - target.sum());

                    return std::abs((val - target).norm());
                }
            }
            else if constexpr (std::is_same_v<T, Eigen::MatrixXi>)
            {
                if constexpr (std::is_same_v<S, Eigen::MatrixXi>)
                {
                    if (!(val.rows() == target.rows() && val.cols() == target.cols()))
                        return 100.0 + std::abs(val.sum() - target.sum());

                    return std::abs((val.template cast<double>() - target.template cast<double>()).norm());
                }
            }
            else if constexpr (std::is_same_v<T, std::vector<Eigen::MatrixXd> >)
            {
                if constexpr (std::is_same_v<S, std::any>)
                {
                    if (val.type() == typeid(std::vector<Eigen::MatrixXd>))
                        return heuristic(std::any_cast<std::vector<Eigen::MatrixXd> >(val), target);
                }
                else if constexpr (std::is_same_v<S, std::vector<Eigen::MatrixXd> >)
                {
                    if (val.size() == target.size())
                    {
                        double h{0};

                        for (size_t i{0}; i < std::min(val.size(), target.size()); ++i)
                            h += heuristic(val[i], target[i]);

                        return h;
                    }
                }
            }
            else if constexpr (std::is_same_v<T, std::vector<Eigen::MatrixXf> >)
            {
                if constexpr (std::is_same_v<S, std::any>)
                {
                    if (val.type() == typeid(std::vector<Eigen::MatrixXf>))
                        return heuristic(std::any_cast<std::vector<Eigen::MatrixXf> >(val), target);
                }
                else if constexpr (std::is_same_v<S, std::vector<Eigen::MatrixXf> >)
                {
                    if (val.size() == target.size())
                    {
                        double h{0};

                        for (size_t i{0}; i < std::min(val.size(), target.size()); ++i)
                            h += heuristic(val[i], target[i]);

                        return h;
                    }
                }
            }
            else if constexpr (std::is_same_v<T, std::vector<Eigen::MatrixXi> >)
            {
                if constexpr (std::is_same_v<S, std::any>)
                {
                    if (val.type() == typeid(std::vector<Eigen::MatrixXi>))
                        return heuristic(std::any_cast<std::vector<Eigen::MatrixXi> >(val), target);
                }
                else if constexpr (std::is_same_v<S, std::vector<Eigen::MatrixXi> >)
                {
                    if (val.size() == target.size())
                    {
                        double h{0};

                        for (size_t i{0}; i < std::min(val.size(), target.size()); ++i)
                            h += heuristic(val[i], target[i]);

                        return h;
                    }
                }
            }

            return 1000.0; //return std::abs(std::hash<S>() - std::hash<T>());
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

        inline std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > sameElement(std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > const& pairs, bool first)
        {
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > result;

            for (auto const& p : pairs)
            {
                if (first)
                {
                    if (p.first.first == p.second.first)
                        result.emplace_back(p);
                }
                else
                {
                    if (p.first.second == p.second.second)
                        result.emplace_back(p);
                }
            }

            return result;
        }

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

                    auto const r{region(b, regions[i].front(), true)};

                    if (r.size() == regions[i].size() + regions[j].size())
                    {
                        std::vector<std::pair<size_t, size_t> > pairs{regions[i].begin(), regions[i].end()};

                        pairs.insert(pairs.end(), regions[j].begin(), regions[j].end());

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
        std::set<std::vector<std::pair<int, int> > > regionSet(Matrix const& m, bool diagonals)
        {
            std::set<std::vector<std::pair<int, int> > > s;

            for (int i{0}; i < m.rows(); ++i)
            {
                for (int j{0}; j < m.cols(); ++j)
                {
                    auto r{region(m, std::make_pair(i, j), diagonals)};

                    std::sort(r.begin(), r.end(),
                              [] (auto const& x, auto const& y) -> bool
                              {
                                  if (x.first == y.first)
                                      return x.second < y.second;

                                  return x.first < y.first;
                              });

                    if (s.find(r) == s.end())
                        s.emplace(r);
                }
            }

            return s;
        }

        inline Eigen::MatrixXi matrix(std::initializer_list<std::initializer_list<int>> values)
        {
            int rows = values.size();
            int cols = values.begin()->size();

            Eigen::MatrixXi m(rows, cols);

            int i = 0;
            for (auto const& row : values)
            {
                int j = 0;
                for (int v : row)
                {
                    m(i, j++) = v;
                }
                ++i;
            }

            return m;
        }

        inline std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > matrixPairs(std::initializer_list<std::initializer_list<std::initializer_list<int> > > const& values)
        {
            return std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >{std::make_pair(matrix(*values.begin()), matrix(*(values.begin() + 1)))};
        }

        inline std::vector<Eigen::MatrixXi> matrices(std::initializer_list<std::initializer_list<std::initializer_list<int> > > const& values)
        {
            std::vector<Eigen::MatrixXi> result;
            result.reserve(values.size());

            for (auto const& v : values)
                result.emplace_back(matrix(v));

            return result;
        }
    }

    inline std::string anyToString(std::any const& v)
    {
        if (v.type() == typeid(char))
            return std::string{std::any_cast<char>(v)};
        else if (v.type() == typeid(double))
            return std::to_string(std::any_cast<double>(v));
        else if (v.type() == typeid(float))
            return std::to_string(std::any_cast<float>(v));
        else if (v.type() == typeid(int))
            return std::to_string(std::any_cast<int>(v));
        else if (v.type() == typeid(long))
            return std::to_string(std::any_cast<long>(v));
        else if (v.type() == typeid(std::string))
            return std::any_cast<std::string>(v);
        else if (v.type() == typeid(std::type_index))
            return std::any_cast<std::type_index>(v).name();

        return std::string{};
    }

    inline std::any stringToAny(std::string const& type, std::string const& value)
    {
        if (type == typeid(char).name())
            return value[0];
        else if (type == typeid(double).name())
            return std::stod(value);
        else if (type == typeid(float).name())
            return std::stof(value);
        else if (type == typeid(int).name())
            return std::stoi(value);
        else if (type == typeid(long).name())
            return std::stol(value);
        else if (type == typeid(std::string).name())
            return value;
        else if (type == typeid(std::type_index).name())
        {
            if (value == typeid(bool).name())
                return std::type_index{typeid(bool)};
            else if (value == typeid(double).name())
                return std::type_index{typeid(double)};
            else if (value == typeid(Eigen::MatrixXd).name())
                return std::type_index{typeid(Eigen::MatrixXd)};
            else if (value == typeid(Eigen::MatrixXf).name())
                return std::type_index{typeid(Eigen::MatrixXf)};
            else if (value == typeid(Eigen::MatrixXi).name())
                return std::type_index{typeid(Eigen::MatrixXi)};
            else if (value == typeid(float).name())
                return std::type_index{typeid(float)};
            else if (value == typeid(int).name())
                return std::type_index{typeid(int)};
            else if (value == typeid(long).name())
                return std::type_index{typeid(long)};
            else if (value == typeid(std::map<int, int>).name())
                return std::type_index{typeid(std::map<int, int>)};
            else if (value == typeid(std::pair<int, int>).name())
                return std::type_index{typeid(std::pair<int, int>)};
            else if (value == typeid(std::string).name())
                return std::type_index{typeid(std::string)};
        }

        return std::any{};
    }
}

#endif // AICPP_UTILITY_H
