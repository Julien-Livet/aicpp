#ifndef AICPP_UTILITY_H
#define AICPP_UTILITY_H

#include <any>
#include <generator>
#include <map>
#include <random>
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

        template <typename T>
        size_t space_size(std::vector<std::vector<T> > const& combinations)
        {
            size_t s{1};

            for (auto const& c : combinations)
                s *= c.size();

            return s;
        }

        template <typename T>
        std::vector<std::vector<T> > sample_space(
            std::vector<std::vector<T> > const& combinations,
            size_t n,
            std::string const& strategy = "mixed",
            std::set<std::vector<T> > const& exclude = std::set<std::vector<T> >{})
        {
            auto const size{space_size(combinations)};

            n = std::min(n, std::max(0, size - exclude.size()));

            if (n <= 0)
                return std::vector<std::vector<T> >{};

            std::set<std::vector<T> > samples;
            std::random_device rd;

            // Latin hypercube approximate
            if (std::set<std::string>{"grid", "mixed"}.contains(strategy))
            {
                size_t const n_grid{strategy == "grid" ? n : std::max(size_t{1}, n / 2)};
                std::vector<std::vector<size_t> > indices;
            
                for (auto const& dim_vals : combinations)
                {
                    size_t const k{dim_vals.size()};
                    size_t const step{std::max(size_t{1}, k / n_grid)};

                    std::vector<size_t> idx;

                    for (size_t i{0}; i < k && idx.size() < n_grid; i += step)
                        idx.emplace_back(i);

                    while (idx.size() < n_grid)
                        idx.emplace_back(std::uniform_int_distribution<size_t>{0, k - 1}(rd));

                    std::shuffle(idx.begin(), idx.end(), rd);
                    indices.emplace_back(std::move(idx));
                }

                for (size_t row{0}; row < n_grid; ++row)
                {
                    std::vector<T> pt;
                    pt.reserve(combinations.size());

                    for (size_t d{0}; d < combinations.size(); ++d)
                        pt.emplace_back(combinations[d][indices[d][row]]);

                    if (!exclude.contains(pt))
                        samples.insert(std::move(pt));
                }
            }

            // Complete with random draw
            size_t attempts{0};
            size_t const max_attempts{n * 30};
            
            while (samples.size() < n && attempts < max_attempts)
            {
                std::vector<T> pt;
                pt.reserve(combinations.size());

                for (auto const& dim_vals : combinations)
                    pt.emplace_back(dim_vals[std::uniform_int_distribution<size_t>{0, dim_vals.size() - 1}(rd)]);

                if (!exclude.contains(pt))
                    samples.insert(std::move(pt));

                ++attempts;
            }

            return std::vector<std::vector<T> >{samples.begin(), samples.end()};
        }
    }
}

#endif // AICPP_UTILITY_H
