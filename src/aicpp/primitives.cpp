#include <map>

#include "aicpp/primitives.h"
#include "aicpp/utility.h"

using namespace aicpp;

std::any primitives::inferColorMapping(std::vector<std::any> const& args)
{
    auto const pairs{std::any_cast<std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > >(args[0])};
    std::map<int, int> mapping;

    for (auto const& pair : pairs)
    {
        for (int i{0}; i < pair.first.rows(); ++i)
        {
            for (int j{0}; j < pair.first.cols(); ++j)
            {
                auto const a{pair.first(i, j)};
                auto const b{pair.second(i, j)};

                if (mapping.find(a) != mapping.end())
                {
                    if (mapping[a] != b)
                        return mapping;
                }
                else
                    mapping[a] = b;
            }
        }
    }

    return mapping;
}

std::any primitives::fliplr(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
        r.emplace_back(utility::fliplr(x));

    return r;
}

std::any primitives::flipud(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
        r.emplace_back(utility::flipud(x));

    return r;
}

std::any primitives::map(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const m{std::any_cast<std::map<int, int> >(args[1])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        auto y{x};

        for (int i{0}; i < y.rows(); ++i)
        {
            for (int j{0}; j < y.cols(); ++j)
            {
                auto const it{m.find(y(i, j))};

                if (it != m.end())
                    y(i, j) = it->second;
            }
        }

        r.emplace_back(y);
    }

    return r;
}

std::any primitives::sameElement(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > >(args[0])};
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > result;
    result.reserve(v.size());

    for (auto const& x : v)
        result.emplace_back(utility::sameElement(x, std::any_cast<bool>(args[1])));

    return result;
}

std::any primitives::regionPairs(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<std::vector<std::vector<std::pair<int, int> > > > >(args[0])};
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > result;
    result.reserve(v.size());

    for (auto const& x : v)
        result.emplace_back(utility::regionPairs(x));

    return result;
}

std::any primitives::segments(std::vector<std::any> const& args)
{
    auto const v1{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const v2{std::any_cast<std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > >(args[1])};

    std::vector<Eigen::MatrixXi> result;

    if (v1.size() != v2.size())
        return result;

    result.reserve(v1.size());

    for (size_t i{0}; i < v1.size(); ++i)
        result.emplace_back(utility::segments(v1[i], v2[i], std::any_cast<int>(args[2]), std::any_cast<bool>(args[3]), std::any_cast<bool>(args[4])));

    return result;
}
