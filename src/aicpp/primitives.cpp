#include <map>
#include <unordered_map>
#include <unordered_set>

#include "aicpp/primitives.h"
#include "aicpp/utility.h"

using namespace aicpp;

Indices toIndices(Patch const& patch)
{
    Indices indices;
    indices.reserve(patch.size());
    
    for (auto const& x : v)
        indices.emplace_back(x.second);

    return indices;
}

std::pair<int, int> ulcorner(Patch const& patch)
{
    auto const indices{toIndices(patch)};

    if (indices.empty())
        return std::make_pair(0, 0);

    return *std::min_element(indices.begin(), indices.end());
}

std::pair<int, int> urcorner(Patch const& patch)
{
    auto const indices{toIndices(patch)};

    if (indices.empty())
        return std::make_pair(0, 0);

    return *std::min_element(indices.begin(), indices.end(),
                             [] (auto const& x, auto const& y)
                             {
                                if (x.second == y.second)
                                    return x.first < y.first;
                                    
                                return x.second < y.second;
                            });
}

std::pair<int, int> lrcorner(Patch const& patch)
{
    auto const indices{toIndices(patch)};

    if (indices.empty())
        return std::make_pair(0, 0);

    return *std::max_element(indices.begin(), indices.end());
}

std::pair<int, int> llcorner(Patch const& patch)
{
    auto const indices{toIndices(patch)};

    if (indices.empty())
        return std::make_pair(0, 0);

    return *std::max_element(indices.begin(), indices.end(),
                             [] (auto const& x, auto const& y)
                             {
                                if (x.second == y.second)
                                    return x.first > y.first;
                                    
                                return x.second > y.second;
                            });
}

Indices backdrop(Patch const& patch)
{
    Indices indices;
    indices.reserve(patch.size());
    
    auto const s{ulcorner(patch)};
    auto const e{lrcorner(patch)};

    for (int i{s.first}; i < e.first + 1; ++i)
    {
        for (int j{s.second}; i < e.second + 1; ++i)
            indices.emplace_back(i, j);
    }

    return indices;
}

Eigen::MatrixXi convertToEigen(std::vector<std::vector<int> > const& vec)
{
    size_t const rows{vec.size()};
    size_t const cols{vec.empty() ? 0 : vec[0].size()};

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
    return rot90(std::vector<std::any>{rot180(args)});
}

std::any primitives::rot180(std::vector<std::any> const& args)
{
    return hmirror(std::vector<std::any>{vmirror(args)});
}

std::any primitives::rot270(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
        r.emplace_back(utility::rot90(x));

    return r;
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

std::any primitives::fillPatches(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const a{std::any_cast<int>(args[1])};
    auto const patches{std::any_cast<std::vector<Patch> >(args[2])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    if (v.size() != patches.size())
        return r;

    for (size_t i{0}; i < v.size(); ++i)
    {
        auto const& x{v[i]};
        auto y{x};

        for (auto const& p : toIndices(patches[i]))
        {
            if (0 <= p.first && p.first < x.rows() && 0 <= p.second && p.second < x.cols())
                y(p.first, p.second) = a;
        }

        r.emplace_back(y);
    }

    return r;
}

std::any primitives::fillIndices(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const a{std::any_cast<int>(args[1])};
    auto const indices{std::any_cast<std::vector<Indices> >(args[2])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    if (v.size() != indices.size())
        return r;

    for (size_t i{0}; i < v.size(); ++i)
    {
        auto const& x{v[i]};
        auto y{x};

        for (auto const& p : indices[i])
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
            upscaled_row.reserve(x.cols() * factor);

            for (auto const& value : x.row(i))
            {
                for (int num{0}; num < factor; ++num)
                    upscaled_row.emplace_back(value);
            }

            for (int num{0}; num < factor; ++num)
                g.emplace_back(upscaled_row);
        }

        r.emplace_back(convertToEigen(g));
    }

    return r;
}

std::any primitives::downscale(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const factor{std::any_cast<int>(args[1])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        if (factor <= 0)
            r.emplace_back();
        else
            r.emplace_back(x(Eigen::seq(0, Eigen::last, factor), Eigen::seq(0, Eigen::last, factor)));
    }

    return r;
}

std::any primitives::hconcat(std::vector<std::any> const& args)
{
    auto const v1{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const v2{std::any_cast<std::vector<Eigen::MatrixXi> >(args[1])};

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
    auto const v2{std::any_cast<std::vector<Eigen::MatrixXi> >(args[1])};

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

std::any primitives::crop(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const start{std::any_cast<std::pair<int, int> >(args[1])};
    auto const dims{std::any_cast<std::pair<size_t, size_t> >(args[2])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        if (start.first < 0 || start.second < 0)
            r.emplace_back();
        else
            r.emplace_back(x.block(start.first, start.second, dims.first, dims.second));
    }

    return r;
}

std::any primitives::toivec(std::vector<std::any> const& args)
{
    auto const i{std::any_cast<int>(args[0])};

    return std::make_pair(i, 0);
}

std::any primitives::tojvec(std::vector<std::any> const& args)
{
    auto const j{std::any_cast<int>(args[0])};

    return std::make_pair(0, j);
}

std::any primitives::mostcolor(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

    std::vector<int> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        std::unordered_map<int, int> counts;

        for (int k = 0; k < x.size(); ++k)
            ++counts[x.data()[k]];

        int most_value{x.data()[0]};
        int max_count{0};

        for (auto const& [value, count] : counts)
        {
            if (count > max_count)
                max_count = count, most_value = value;
        }

        r.emplace_back(most_value);
    }

    return r;
}

std::any primitives::canvas(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<int> >(args[0])};
    auto const dims{std::any_cast<std::pair<size_t, size_t> >(args[1])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
        r.emplace_back(Eigen::MatrixXi::Constant(dims.first, dims.second, x));

    return r;
}

std::any primitives::hsplit(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const n{std::any_cast<int>(args[1])};

    std::vector<std::vector<Eigen::MatrixXi> > r;
    r.reserve(v.size());

    if (n <= 0)
        return r;

    for (auto const& grid : v)
    {
        auto const h{grid.rows()};
        auto const total_w{grid.cols()};

        int const base{total_w / n};
        int const remainder{total_w % n};

        std::vector<Eigen::MatrixXi> result;
        result.reserve(n);

        int current_col{0};

        for (int i{0}; i < n; ++i)
        {
            int const width{base + (i < remainder ? 1 : 0)};

            result.emplace_back(grid.block(0, current_col, h, width));
            current_col += width;
        }

        r.emplace_back(result);
    }

    return r;
}

std::any primitives::vsplit(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
    auto const n{std::any_cast<int>(args[1])};

    std::vector<std::vector<Eigen::MatrixXi> > r;
    r.reserve(v.size());

    if (n <= 0)
        return r;

    for (auto const& grid : v)
    {
        auto const total_h{grid.rows()};
        auto const w{grid.cols()};

        int const base{total_h / n};
        int const remainder{total_h % n};

        std::vector<Eigen::MatrixXi> result;
        result.reserve(n);

        int current_row{0};

        for (int i{0}; i < n; ++i)
        {
            int const height{base + (i < remainder ? 1 : 0)};

            result.emplace_back(grid.block(current_row, 0, height, w));
            current_row += height;
        }

        r.emplace_back(result);
    }

    return r;
}

std::any primitives::first(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<std::vector<Eigen::MatrixXi> > >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        if (x.empty())
            r.emplace_back();
        else
            r.emplace_back(x.front());
    }

    return r;
}

std::any primitives::last(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<std::vector<Eigen::MatrixXi> > >(args[0])};

    std::vector<Eigen::MatrixXi> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        if (x.empty())
            r.emplace_back();
        else
            r.emplace_back(x.back());
    }

    return r;
}

std::any primitives::delta(std::vector<std::any> const& args)
{
    auto const v{std::any_cast<std::vector<Patch> >(args[0])};

    std::vector<Indices> r;
    r.reserve(v.size());

    for (auto const& x : v)
    {
        auto const b{backdrop(x)};
        auto const indices{toIndices(x)};

        std::unordered_set<std::pair<int, int> > s1{b.begin(), b.end()};
        std::unordered_set<std::pair<int, int> > s2{indices.begin(), indices.end()};

        std::vector<Indices> result;

        std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(result, result.end())),

        r.emplace_back(result);
    }

    return r;
}
