#include <map>

#include "aicpp/primitives.h"
#include "aicpp/utility.h"

using namespace aicpp;

std::vector<std::pair<int, int> > toIndices(std::vector<std::pair<int, std::pair<int, int> > > const& patch)
{
    std::vector<std::pair<int, int> > r;
    r.reserve(patch.size());

    for (auto const& v : patch)
        r.emplace_back(v.second);

    return r;
}

Eigen::MatrixXi convertToEigen(const std::vector<std::vector<int>>& vec)
{
    size_t const rows{vec.size()};
    size_t const cols{vec[0].size()};

    std::vector<int> flat;
    flat.reserve(rows * cols);

    for (const auto& row : vec)
        flat.insert(flat.end(), row.begin(), row.end());

    Eigen::Map<Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > mat(flat.data(), rows, cols);

    return mat;
}

std::any primitives::hmirror(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
        r.emplace_back(utility::flipud(x));

    return r;
}

std::any primitives::vmirror(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
        r.emplace_back(utility::fliplr(x));

    return r;
}

std::any primitives::dmirror(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
        r.emplace_back(x.transpose());

    return r;
}

std::any primitives::rot90(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
        r.emplace_back(utility::rot90(x));

    return r;
}

std::any primitives::rot180(std::vector<std::any> const& args)
{
    return hmirror(std::vector<std::any>{vmirror(args)});
}

std::any primitives::rot270(std::vector<std::any> const& args)
{
    return rot90(std::vector<std::any>{rot180(args)});
}

std::any primitives::swap(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const a{std::any_cast<int>(args[1])};
    auto const b{std::any_cast<int>(args[2])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        auto y{x};

        for (int i{0}; i < y.rows(); ++i)
        {
            for (int j{0}; j < y.cols(); ++j)
            {
                if (y(i, j) == a)
                    y(i, j) = b;
                else if (y(i, j) == b)
                    y(i, j) = a;
            }
        }

        r.emplace_back(y);
    }

    return r;
}

std::any primitives::ofcolor(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const a{std::any_cast<int>(args[1])};

    std::vector<std::vector<std::pair<int, int> > > r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        std::vector<std::pair<int, int> > y;

        for (int i{0}; i < x.rows(); ++i)
        {
            for (int j{0}; j < x.cols(); ++j)
            {
                if (x(i, j) == a)
                    y.emplace_back(std::make_pair(i, j));
            }
        }

        r.emplace_back(y);
    }

    return r;
}

std::any primitives::fill(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const a{std::any_cast<int>(args[1])};
    auto const patch{std::any_cast<std::vector<std::pair<int, std::pair<int, int> > > >(args[2])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        auto y{x};

        for (auto const& p : toIndices(patch))
        {
            if (0 <= p.first && p.first < x.rows() && 0 <= p.second && p.second < x.cols())
                y(p.first, p.second) = a;
        }

        r.emplace_back(y);
    }

    return r;
}

std::any primitives::upscale(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const factor{std::any_cast<int>(args[1])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        std::vector<std::vector<int > > g;

        for (int i{0}; i < x.rows(); ++i)
        {
            std::vector<int> upscaled_row;
            upscaled_row.reserve(x.cols());

            for (auto const& value : x.row(i))
            {
                for (int num{0}; num < factor; ++num)
                    upscaled_row.emplace_back(value);
            }
        }

        r.emplace_back(convertToEigen(g));
    }

    return r;
}

std::any primitives::hconcat(std::vector<std::any> const& args)
{
    auto const v1{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const v2{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    if (v1.size() != v2.size())
        return std::vector<Eigen::MatrixXi>{};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v1.size());

    for (size_t i{0}; i < v1.size(); ++i)
    {
        auto const a{v1[i]};
        auto const b{v2[i]};

        if (a.rows() != b.rows())
        {
            r.emplace_back();
            continue;
        }

        Eigen::MatrixXi result(a.rows(), a.cols() + b.cols());
        
        result << a, b;

        r.emplace_back(result);
    }

    return r;
}

std::any primitives::vconcat(std::vector<std::any> const& args)
{
    auto const v1{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const v2{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    if (v1.size() != v2.size())
        return std::vector<Eigen::MatrixXi>{};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v1.size());

    for (size_t i{0}; i < v1.size(); ++i)
    {
        auto const a{v1[i]};
        auto const b{v2[i]};

        if (a.cols() != b.cols())
        {
            r.emplace_back();
            continue;
        }

        Eigen::MatrixXi result(a.rows() + b.rows(), a.cols());
        
        result << a, b;

        r.emplace_back(result);
    }

    return r;
}

std::any primitives::replace(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const a{std::any_cast<int>(args[1])};
    auto const b{std::any_cast<int>(args[2])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        auto y{x};

        for (int i{0}; i < y.rows(); ++i)
        {
            for (int j{0}; j < y.cols(); ++j)
            {
                if (y(i, j) == a)
                    y(i, j) = b;
            }
        }

        r.emplace_back(y);
    }

    return r;
}
