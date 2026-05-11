#ifndef AICPP_UTILITY_H
#define AICPP_UTILITY_H

#include <algorithm>
#include <any>
#include <cmath>
#include <functional>
#include <generator>
#include <limits>
#include <numeric>
#include <map>
#include <random>
#include <set>
#include <typeindex>
#include <vector>

#include <Eigen/Core>

#include <boost/algorithm/string.hpp>

#include <dlib/matrix.h>
#include <dlib/statistics.h>
#include <dlib/svm.h>
#include <dlib/global_optimization.h>

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

            n = std::min(n, static_cast<size_t>(std::max(0, static_cast<int>(size) - static_cast<int>(exclude.size()))));

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
        template <typename T>
        class CartesianProductIterator
        {
            public:
                using iterator_category = std::input_iterator_tag;
                using value_type        = std::vector<T>;
                using difference_type   = std::ptrdiff_t;
                using pointer           = value_type const*;
                using reference         = value_type const&;

                CartesianProductIterator() : done{true} {}

                explicit CartesianProductIterator(std::vector<std::vector<T>> const& dims)
                    : pools{dims}, indices(dims.size(), 0), done{dims.empty()}
                {
                    if (!done)
                        build_current();
                }

                reference operator*()  const { return current; }
                pointer   operator->() const { return &current; }

                CartesianProductIterator& operator++()
                {
                    for (int i{static_cast<int>(indices.size()) - 1}; i >= 0; --i)
                    {
                        if (++indices[i] < pools[i].size())
                        {
                            build_current();
                            return *this;
                        }
                        indices[i] = 0;
                    }

                    done = true;
                    
                    return *this;
                }

                bool operator==(CartesianProductIterator const& o) const
                {
                    if (done && o.done) 
                        return true;
                    if (done != o.done)
                        return false;
                    
                        return indices == o.indices;
                }

                bool operator!=(CartesianProductIterator const& o) const { return !(*this == o); }

            private:
                void build_current()
                {
                    current.resize(pools.size());
                    
                    for (size_t i{0}; i < pools.size(); ++i)
                        current[i] = pools[i][indices[i]];
                }

                std::vector<std::vector<T>> pools;
                std::vector<size_t>         indices;
                value_type                  current;
                bool                        done;
        };

        template <typename T>
        class CartesianProductRange
        {
            public:
                explicit CartesianProductRange(std::vector<std::vector<T>> dims)
                    : pools{std::move(dims)} {}

                CartesianProductIterator<T> begin() const { return CartesianProductIterator<T>{pools}; }
                CartesianProductIterator<T> end()   const { return CartesianProductIterator<T>{}; }

            private:
                std::vector<std::vector<T>> pools;
        };

        template <typename T>
        CartesianProductRange<T> iter_space(
            std::vector<std::vector<T>> combinations,
            bool                        shuffle = true)
        {
            std::random_device rd;

            if (shuffle)
            {
                for (auto& c : combinations)
                    std::shuffle(c.begin(), c.end(), rd);
            }

            return CartesianProductRange<T>{std::move(combinations)};
        }

        template <typename T>
        std::vector<std::vector<T> > sampled_neighbors(
            std::vector<T> const&            point,
            size_t                           dim,
            std::vector<std::vector<T>> const& combinations,
            size_t                           k)
        {
            std::random_device rd;

            auto const& dim_vals{combinations[dim]};
            auto const& cur{point[dim]};

            std::vector<T> other_vals;
            other_vals.reserve(dim_vals.size());

            for (auto const& v : dim_vals)
                if (v != cur)
                    other_vals.push_back(v);

            if (other_vals.empty())
                return {};

            size_t const n_chosen{std::min(k, other_vals.size())};

            for (size_t i{0}; i < n_chosen; ++i)
            {
                size_t j{std::uniform_int_distribution<size_t>{i, other_vals.size() - 1}(rd)};
                std::swap(other_vals[i], other_vals[j]);
            }

            std::vector<std::vector<T>> result;
            result.reserve(n_chosen);

            for (size_t i{0}; i < n_chosen; ++i)
            {
                auto nb{point};
                nb[dim] = other_vals[i];
                result.emplace_back(std::move(nb));
            }

            return result;
        }

        using sample_type = dlib::matrix<double, 0, 1>;
        using kernel_type = dlib::radial_basis_kernel<sample_type>;

        struct StandardScaler
        {
            dlib::matrix<double, 1, 0> mean, std_dev;

            void fit(std::vector<sample_type> const& X)
            {
                long const n{static_cast<long>(X.size())};
                long const d{X[0].size()};

                mean    = dlib::zeros_matrix<double>(1, d);
                std_dev = dlib::zeros_matrix<double>(1, d);

                for (auto const& x : X)
                    mean += dlib::trans(x);
                mean /= n;

                for (auto const& x : X)
                {
                    dlib::matrix<double, 1, 0> diff = dlib::trans(x) - mean;
                    std_dev += dlib::pointwise_multiply(diff, diff);
                }
                std_dev /= n;

                for (long j{0}; j < d; ++j)
                {
                    std_dev(j) = std::sqrt(std_dev(j));
                    if (std_dev(j) < 1e-8) std_dev(j) = 1.0;
                }
            }

            sample_type transform(sample_type const& x) const
            {
                long const d{x.size()};
                sample_type out(d);

                for (long j{0}; j < d; ++j)
                    out(j) = (x(j) - mean(j)) / std_dev(j);

                return out;
            }

            std::vector<sample_type> transform(std::vector<sample_type> const& X) const
            {
                std::vector<sample_type> out;
                out.reserve(X.size());

                for (auto const& x : X)
                    out.emplace_back(transform(x));

                return out;
            }
        };

        inline double standard_normal_pdf(double z)
        {
            return std::exp(-0.5 * z * z) / std::sqrt(2.0 * M_PI);
        }

        inline double standard_normal_cdf(double z)
        {
            return 0.5 * std::erfc(-z / std::sqrt(2.0));
        }

        inline std::vector<double> expected_improvement(
            std::vector<double> const& mu,
            std::vector<double> const& sigma,
            double                     best_y,
            double                     xi = 0.01)
        {
            std::vector<double> ei(mu.size());

            for (size_t i{0}; i < mu.size(); ++i)
            {
                double s{sigma[i]};

                if (s < 1e-9) { ei[i] = 0.0; continue; }

                double Z{(best_y - mu[i] - xi) / s};
                ei[i] = (best_y - mu[i] - xi) * standard_normal_cdf(Z)
                        + s * standard_normal_pdf(Z);

                if (ei[i] < 0.0) ei[i] = 0.0;
            }

            return ei;
        }

        template <typename T>
        std::vector<sample_type> encode_output_space_discrete(
            std::vector<std::vector<std::string> > const&               points,
            std::function<std::any(std::vector<std::string> const&)>    op,
            std::vector<std::vector<std::string> > const&               combinations,
            T const&                                                    target,
            std::function<double(std::any const&, std::any const&)>     heuristicFunction,
            size_t                                                      k_neighbors = 8)
        {
            size_t const D{combinations.size()};
            size_t const n_features{1 + D * 5};

            std::vector<sample_type> result;
            result.reserve(points.size());

            for (auto const& point : points)
            {
                double v{heuristicFunction(op(point), target)};
                sample_type row(static_cast<long>(n_features));
                row = 0.0;
                row(0) = v;

                for (size_t dim{0}; dim < D; ++dim)
                {
                    auto nbs = sampled_neighbors(point, dim, combinations, k_neighbors);

                    std::vector<double> scores;
                    scores.reserve(nbs.empty() ? 1 : nbs.size());

                    if (nbs.empty())
                        scores.emplace_back(v);
                    else
                    {
                        for (auto const& nb : nbs)
                            scores.emplace_back(heuristicFunction(op(nb), target));
                    }

                    double mean_s{std::accumulate(scores.begin(), scores.end(), 0.0)
                                / static_cast<double>(scores.size())};
                    double std_s{0.0};

                    if (scores.size() > 1)
                    {
                        double sq{0.0};

                        for (double s : scores)
                            sq += (s - mean_s) * (s - mean_s);

                        std_s = std::sqrt(sq / static_cast<double>(scores.size()));
                    }

                    double min_s{*std::min_element(scores.begin(), scores.end())};
                    double max_s{*std::max_element(scores.begin(), scores.end())};

                    long base{static_cast<long>(1 + dim * 5)};
                    row(base + 0) = mean_s;
                    row(base + 1) = std_s;
                    row(base + 2) = min_s;
                    row(base + 3) = max_s;
                    row(base + 4) = v - mean_s;
                }

                result.emplace_back(std::move(row));
            }

            return result;
        }

        template <typename T>
        std::pair<std::vector<std::string>, double> bayesian_optimization_discrete(
            std::function<std::any(std::vector<std::string> const&)>    op,
            T const&                                                    target,
            std::vector<std::vector<std::string> > const&               combinations,
            std::function<double(std::any const&, std::any const&)>     heuristicFunction,
            size_t   n_init      = 5,
            size_t   top_k       = 3,
            size_t   count_max   = 10,
            double   xi          = 0.01,
            size_t   n_sample    = 200,
            size_t   k_neighbors = 8,
            double   threshold   = 0.0)
        {
            size_t const size{space_size(combinations)};
            auto init_pts = sample_space(combinations, n_init, "mixed");

            std::vector<std::vector<std::string> > obs_x;
            std::vector<double>         obs_y;

            for (auto const& x : init_pts)
            {
                try
                {
                    double y{heuristicFunction(op(x), target)};
                    obs_x.emplace_back(x);
                    obs_y.emplace_back(y);

                    if (y <= threshold)
                        return {x, y};
                }
                catch (...)
                {
                }
            }

            if (obs_x.empty())
            {
                auto range = iter_space(combinations, false);
                auto it    = range.begin();

                if (it != range.end())
                    return {*it, 999.0};

                return {{}, 999.0};
            }

            size_t best_idx{static_cast<size_t>(std::min_element(obs_y.begin(), obs_y.end()) - obs_y.begin())};
            auto   best_x{obs_x[best_idx]};
            double best_y{obs_y[best_idx]};
            double prev_best{std::numeric_limits<double>::infinity()};
            size_t count{0};

            // dlib GP (krls = kernel recursive least squares — used as GP surrogate)
            // gamma = 1 / (2 * length_scale²)  →  length_scale=1  →  gamma=0.5
            kernel_type                  kernel{0.5};
            dlib::krls<kernel_type>      gp{kernel, 1e-2};  // 1e-2 = tolerance (alpha jitter)
            std::vector<sample_type>     C_enc;
            std::vector<std::vector<std::string> > candidates;

            while (true)
            {
                std::set<std::vector<std::string> > obs_set(obs_x.begin(), obs_x.end());

                auto X_raw = encode_output_space_discrete(
                    obs_x, op, combinations, target, heuristicFunction, k_neighbors);

                if (static_cast<long>(X_raw.size()) < 2)
                    break;

                // StandardScaler on training data
                StandardScaler scaler;

                try
                {
                    scaler.fit(X_raw);
                }
                catch (...)
                {
                    break;
                }

                auto X_sc = scaler.transform(X_raw);

                // Fit dlib GP (krls trains online; re-init each iteration for clean fit)
                gp = dlib::krls<kernel_type>{kernel, 1e-2};

                try
                {
                    for (size_t i{0}; i < X_sc.size(); ++i)
                        gp.train(X_sc[i], obs_y[i]);
                }
                catch (...)
                {
                    break;
                }

                candidates = sample_space(combinations, n_sample, "mixed", obs_set);

                if (candidates.empty())
                    break;

                auto C_raw = encode_output_space_discrete(
                    candidates, op, combinations, target, heuristicFunction, k_neighbors);

                if (C_raw.empty())
                    break;

                // Align columns
                long n_cols{std::min(X_raw[0].size(), C_raw[0].size())};

                // Scale candidates with a fresh scaler fitted on (aligned) training data
                std::vector<sample_type> X_aligned;
                X_aligned.reserve(X_raw.size());

                for (auto const& x : X_raw)
                {
                    sample_type s(n_cols);

                    for (long j{0}; j < n_cols; ++j)
                        s(j) = x(j);

                    X_aligned.push_back(s);
                }

                StandardScaler scaler2;
                try
                {
                    scaler2.fit(X_aligned);
                }
                catch (...)
                {
                    break;
                }

                // Predict: dlib krls has no built-in std; approximate via leave-one-out
                // variance estimate using the kernel diagonal (common GP surrogate trick).
                // k(x*,x*) - k_vec^T K^{-1} k_vec  is unavailable directly in krls,
                // so we use the squared residual on training data as a local proxy,
                // then interpolate for candidates (conservative but functional).
                //
                // For a production use, replace krls with dlib::gaussian_process directly
                // (available in dlib ≥ 19.24 as dlib::gp_regression) or with mlpack's GP.

                double train_rss{0.0};

                for (size_t i{0}; i < X_sc.size(); ++i)
                {
                    double r{obs_y[i] - gp(X_sc[i])};
                    train_rss += r * r;
                }

                double global_sigma{std::sqrt(train_rss / std::max<size_t>(1, X_sc.size()))};

                std::vector<double> mu_vec, sigma_vec;
                mu_vec.reserve(C_raw.size());
                sigma_vec.reserve(C_raw.size());

                C_enc.clear();
                C_enc.reserve(C_raw.size());

                for (auto const& c : C_raw)
                {
                    sample_type aligned(n_cols);

                    for (long j{0}; j < n_cols; ++j)
                        aligned(j) = c(j);

                    sample_type c_sc = scaler2.transform(aligned);
                    C_enc.emplace_back(c_sc);

                    mu_vec.emplace_back(gp(c_sc));
                    sigma_vec.emplace_back(global_sigma);  // homoscedastic proxy
                }

                double best_obs{*std::min_element(obs_y.begin(), obs_y.end())};
                auto   ei = expected_improvement(mu_vec, sigma_vec, best_obs, xi);

                // top_k by descending EI
                std::vector<size_t> idx(ei.size());
                std::iota(idx.begin(), idx.end(), 0);
                size_t k{std::min(top_k, ei.size())};
                std::partial_sort(idx.begin(), idx.begin() + k, idx.end(),
                    [&ei](size_t a, size_t b){ return ei[a] > ei[b]; });

                bool improved{false};

                for (size_t i{0}; i < k; ++i)
                {
                    auto const& x{candidates[idx[i]]};

                    try
                    {
                        double y{heuristicFunction(op(x), target)};
                        obs_x.emplace_back(x);
                        obs_y.emplace_back(y);

                        if (y <= threshold)
                            return {x, y};

                        if (y < best_y)
                        {
                            best_x   = x;
                            best_y   = y;
                            improved = true;
                        }
                    }
                    catch (...)
                    {
                    }
                }

                if (best_y < prev_best)
                {
                    prev_best = best_y;
                    count     = 0;
                }
                else if (!improved)
                    ++count;

                if (count >= count_max)
                    break;

                if (obs_x.size() >= size)
                    break;
            }

            return {best_x, best_y};
        }
    }
}

#endif // AICPP_UTILITY_H
