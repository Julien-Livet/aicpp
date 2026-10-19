#include <algorithm>
#include <map>
#include <numeric>
#include <ranges>
#include <type_traits>

#include "aicpp/Hodel.h"
#include "aicpp/Neuron.h"

constexpr hodel::Integer MAX_SIZE = 30;
constexpr size_t SHOOT_DISTANCE = 42;

using IntegerCountMap = std::map<hodel::Integer, hodel::Integer>;

hodel::Indices rectangleOutline(hodel::Integer si, hodel::Integer sj, hodel::Integer ei, hodel::Integer ej)
{
    hodel::Indices result;

    for (hodel::Integer i = si; i <= ei; ++i)
    {
        result.emplace(i, sj);
        result.emplace(i, ej);
    }

    for (hodel::Integer j = sj; j <= ej; ++j)
    {
        result.emplace(si, j);
        result.emplace(ei, j);
    }

    return result;
}

IntegerCountMap colorCounts(hodel::Grid const& element)
{
    IntegerCountMap counts;

    for (auto const& row : element)
    {
        for (auto const& color : row)
            ++counts[color];
    }

    return counts;
}

IntegerCountMap colorCounts(hodel::Object const& element)
{
    IntegerCountMap counts;

    for (auto const& [color, position] : element)
        ++counts[color];

    return counts;
}

hodel::Integer hodel::add(Integer const& a, Integer const& b)
{
    return a + b;
}

hodel::IntegerTuple hodel::add(IntegerTuple const& a, Integer const& b)
{
    auto r{a};
    r += b;

    return r;
}

hodel::IntegerTuple hodel::add(Integer const& a, IntegerTuple const& b)
{
    auto r{b};
    r += 1;

    return r;
}

hodel::IntegerTuple hodel::add(IntegerTuple const& a, IntegerTuple const& b)
{
    auto r{a};
    r += b;

    return r;
}

hodel::Integer hodel::subtract(Integer const& a, Integer const& b)
{
    return a - b;
}

hodel::IntegerTuple hodel::subtract(IntegerTuple const& a, Integer const& b)
{
    auto r{a};
    r -= b;

    return r;
}

hodel::IntegerTuple hodel::subtract(Integer const& a, IntegerTuple const& b)
{
    auto r{b};
    r *= -1;
    r += a;

    return r;
}

hodel::IntegerTuple hodel::subtract(IntegerTuple const& a, IntegerTuple const& b)
{
    auto r{a};
    r -= b;

    return r;
}

hodel::Integer hodel::multiply(Integer const& a, Integer const& b)
{
    return a * b;
}

hodel::IntegerTuple hodel::multiply(IntegerTuple const& a, Integer const& b)
{
    auto r{a};
    r *= b;

    return r;
}

hodel::IntegerTuple hodel::multiply(Integer const& a, IntegerTuple const& b)
{
    auto r{b};
    r *= a;

    return r;
}

hodel::IntegerTuple hodel::multiply(IntegerTuple const& a, IntegerTuple const& b)
{
    auto r{a};
    r *= b;

    return r;
}

hodel::Integer hodel::divide(Integer const& a, Integer const& b)
{
    if (!b)
        throw InvalidInteger{"divide"};

    return a / b;
}

hodel::IntegerTuple hodel::divide(IntegerTuple const& a, Integer const& b)
{
    if (!b)
        throw InvalidInteger{"divide"};

    auto r{a};
    r /= b;

    return r;
}

hodel::IntegerTuple hodel::divide(IntegerTuple const& a, IntegerTuple const& b)
{
    if (!b.first || b.second)
        throw InvalidIntegerTuple{"divide"};

    auto r{a};
    r /= b;

    return r;
}

hodel::Integer hodel::invert(Integer const& n)
{
    auto const r{-n};

    return r;
}

hodel::IntegerTuple hodel::invert(IntegerTuple const& n)
{
    auto r{n};
    r *= -1;

    return r;
}

hodel::Boolean hodel::even(Integer const& n)
{
    return n % 2 == 0;
}

hodel::Integer hodel::double_(Integer const& n)
{
    return n * 2;
}

hodel::IntegerTuple hodel::double_(IntegerTuple const& n)
{
    auto r{n};
    r *= 2;

    return r;
}

hodel::Integer hodel::halve(Integer const& n)
{
    return n / 2;
}

hodel::IntegerTuple hodel::halve(IntegerTuple const& n)
{
    auto r{n};
    r /= 2;

    return r;
}

hodel::Boolean hodel::flip(Boolean const& b)
{
    return !b;
}

hodel::Boolean hodel::greater(Integer const& a, Integer const& b)
{
    return a > b;
}

hodel::Boolean hodel::greater(IntegerTuple const& a, IntegerTuple const& b)
{
    return a > b;
}

hodel::Integer hodel::maximum(IntegerSet const& container)
{
    if (container.empty())
        throw EmptyContainer{"maximum"};
    
    return *std::max_element(container.begin(), container.end());
}

hodel::Integer hodel::maximum(IntegerVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"maximum"};
    
    return *std::max_element(container.begin(), container.end());
}

hodel::IntegerTuple hodel::maximum(Indices const& container)
{
    if (container.empty())
        throw EmptyContainer{"maximum"};
    
    return *std::max_element(container.begin(), container.end());
}

hodel::Integer hodel::maximum(IntegerTuple const& container)
{
    return std::max(container.first, container.second);
}

hodel::Integer hodel::minimum(IntegerSet const& container)
{
    if (container.empty())
        throw EmptyContainer{"maximum"};
    
    return *std::min_element(container.begin(), container.end());
}

hodel::Integer hodel::minimum(IntegerVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"maximum"};
    
    return *std::min_element(container.begin(), container.end());
}

hodel::IntegerTuple hodel::minimum(Indices const& container)
{
    if (container.empty())
        throw EmptyContainer{"maximum"};
    
    return *std::min_element(container.begin(), container.end());
}

hodel::Integer hodel::minimum(IntegerTuple const& container)
{
    return std::min(container.first, container.second);
}

hodel::Boolean hodel::both(Boolean const& a, Boolean const& b)
{
    return a && b;
}

hodel::Boolean hodel::either(Boolean const& a, Boolean const& b)
{
    return Boolean{a || b};
}

hodel::Integer hodel::increment(Integer const& x)
{
    return x + 1;
}

hodel::IntegerTuple hodel::increment(IntegerTuple const& x)
{
    auto y{x};

    y += 1;

    return y;
}

hodel::Integer hodel::decrement(Integer const& x)
{
    return x - 1;
}

hodel::IntegerTuple hodel::decrement(IntegerTuple const& x)
{
    auto y{x};

    y -= 1;

    return y;
}

hodel::Integer hodel::crement(Integer const& x)
{
    if (!x)
        return x;
    else if (x > 0)
        return increment(x);
    else
        return decrement(x);
}

hodel::IntegerTuple hodel::crement(IntegerTuple const& x)
{
    return {crement(x.first), crement(x.second)};
}

hodel::Integer hodel::sign(Integer const& x)
{
    if (!x)
        return 0;
    else if (x > 0)
        return 1;
    else
        return -1;
}

hodel::IntegerTuple hodel::sign(IntegerTuple const& x)
{
    return {sign(x.first), sign(x.second)};
}

hodel::Boolean hodel::positive(Integer const& x)
{
    return x > 0;
}

hodel::IntegerTuple hodel::toivec(Integer const& i)
{
    return {i, 0};
}

hodel::IntegerTuple hodel::tojvec(Integer const& j)
{
    return {0, j};
}

hodel::IntegerSet hodel::interval(Integer start, Integer const& stop, Integer const& step)
{
    IntegerSet result;

    if ((step >= 0 && stop < start) || (step <= 0 && stop > start))
        throw InvalidInteger{"interval"};

    if (std::abs(start - stop) > 100)
        throw InvalidInteger{"interval"};

    for (; step >= 0 ? start < stop : start > stop; start += step)
        result.emplace(start);

    return result;
}

hodel::IntegerTuple hodel::astuple(Integer const& a, Integer const& b)
{
    return {a, b};
}

hodel::FunctionIntegerPair hodel::astuple(aicpp::FunctionValue const& a, Integer const& b)
{
    return {a, b};
}

hodel::Cell hodel::astuple(Integer const& a, IntegerTuple const& b)
{
    return {a, b};
}

hodel::GridVector hodel::astuple(Grid const& a, Grid const& b)
{
    return {a, b};
}

hodel::IntegerTuple hodel::ulcorner(Object const& patch)
{
    return ulcorner(toindices(patch));
}

hodel::IntegerTuple hodel::ulcorner(Indices const& patch)
{
    auto min_y = std::numeric_limits<Integer>::max();
    auto min_x = std::numeric_limits<Integer>::max();

    for (const auto& [y, x] : patch)
    {
        min_y = std::min(min_y, y);
        min_x = std::min(min_x, x);
    }

    return {min_y, min_x};
}

hodel::IntegerTuple hodel::urcorner(Object const& patch)
{
    return urcorner(toindices(patch));
}

hodel::IntegerTuple hodel::urcorner(Indices const& patch)
{
    auto min_y = std::numeric_limits<Integer>::max();
    auto max_x = std::numeric_limits<Integer>::lowest();

    for (const auto& [y, x] : patch)
    {

        min_y = std::min(min_y, y);
        max_x = std::max(max_x, x);
    }

    return {min_y, max_x};
}

hodel::IntegerTuple hodel::llcorner(Object const& patch)
{
    return llcorner(toindices(patch));
}

hodel::IntegerTuple hodel::llcorner(Indices const& patch)
{
    auto max_y = std::numeric_limits<Integer>::lowest();
    auto min_x = std::numeric_limits<Integer>::max();

    for (const auto& [y, x] : patch)
    {
        max_y = std::max(max_y, y);
        min_x = std::min(min_x, x);
    }

    return {max_y, min_x};
}

hodel::IntegerTuple hodel::lrcorner(Object const& patch)
{
    return lrcorner(toindices(patch));
}

hodel::IntegerTuple hodel::lrcorner(Indices const& patch)
{
    auto max_y = std::numeric_limits<Integer>::lowest();
    auto max_x = std::numeric_limits<Integer>::lowest();

    for (const auto& [y, x] : patch)
    {
        max_y = std::max(max_y, y);
        max_x = std::max(max_x, x);
    }

    return {max_y, max_x};
}

hodel::Grid hodel::crop(Grid const& grid, IntegerTuple const& start, IntegerTuple const& dims)
{
    Grid result;

    if (start.first < 0 || start.second < 0 || start.first + dims.first > grid.size() || start.second + dims.second > grid[0].size())
        throw InvalidInteger{"crop"};

    for (size_t i{0}; i < dims.first; ++i)
    {
        std::vector<Integer> row;

        for (size_t j{0}; j < dims.second; ++j)
            row.emplace_back(grid[start.first + i][start.second + j]); 

        result.emplace_back(row);
    }

    return result;
}

hodel::Indices hodel::toindices(Object const& patch)
{
    Indices result;

    for (auto const& cell : patch)
        result.insert(cell.second);

    return result;
}

hodel::Object hodel::shift(Object const& patch, IntegerTuple const& directions)
{
    if (patch.empty())
        throw EmptyObject{"shift"};

    auto const& [di, dj] = directions;

    Object result;

    for (auto const& [value, pos] : patch)
    {
        auto const& [i, j] = pos;

        result.insert({value, {static_cast<Integer>(i + di), static_cast<Integer>(j + dj)}});
    }

    return result;
}

hodel::Indices hodel::shift(Indices const& patch, IntegerTuple const& directions)
{
    if (patch.empty())
        throw EmptyIndices{"shift"};

    auto const& [di, dj] = directions;

    Indices result;

    for (auto const& [i, j] : patch)
        result.insert({static_cast<Integer>(i + di), static_cast<Integer>(j + dj)});

    return result;
}

hodel::Integer hodel::uppermost(Object const& patch)
{
    return uppermost(toindices(patch));
}

hodel::Integer hodel::uppermost(Indices const& patch)
{
    auto result = std::numeric_limits<Integer>::max();

    for (auto const& [i, j] : patch)
        result = std::min(result, i);

    return result;
}

hodel::Integer hodel::lowermost(Object const& patch)
{
    return lowermost(toindices(patch));
}

hodel::Integer hodel::lowermost(Indices const& patch)
{
    auto result = std::numeric_limits<Integer>::min();

    for (auto const& [i, j] : patch)
        result = std::max(result, i);

    return result;
}

hodel::Integer hodel::leftmost(Object const& patch)
{
    return leftmost(toindices(patch));
}

hodel::Integer hodel::leftmost(Indices const& patch)
{
    auto result = std::numeric_limits<Integer>::max();

    for (auto const& [i, j] : patch)
        result = std::min(result, j);

    return result;
}

hodel::Integer hodel::rightmost(Object const& patch)
{
    return rightmost(toindices(patch));
}

hodel::Integer hodel::rightmost(Indices const& patch)
{
    auto result = std::numeric_limits<Integer>::min();

    for (auto const& [i, j] : patch)
        result = std::max(result, j);

    return result;
}

hodel::Grid hodel::rot90(Grid const& grid)
{
    if (grid.empty())
        throw EmptyGrid{"rot90"};

    Grid result;

    try
    {
        auto const rows{grid.size()};
        auto const cols{grid.at(0).size()};

        result = Grid(cols, std::vector<Integer>(rows));

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
                result.at(j).at(rows - 1 - i) = grid.at(i).at(j);
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"rot90"};
    }

    return result;
}

hodel::Grid hodel::rot180(hodel::Grid const& grid)
{
    if (grid.empty())
        throw EmptyGrid{"rot180"};

    Grid result;

    try
    {
        auto const rows{grid.size()};
        auto const cols{grid.at(0).size()};

        result = Grid(cols, std::vector<Integer>(rows));

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
                result.at(rows - 1 - i).at(cols - 1 - j) = grid.at(i).at(j);
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"rot180"};
    }

    return result;
}

hodel::Grid hodel::rot270(hodel::Grid const& grid)
{
    if (grid.empty())
        throw EmptyGrid{"rot270"};

    Grid result;

    try
    {
        auto const rows{grid.size()};
        auto const cols{grid.at(0).size()};

        result = Grid(cols, std::vector<Integer>(rows));

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
                result.at(cols - 1 - j).at(i) = grid.at(i).at(j);
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"rot270"};
    }

    return result;
}

hodel::Grid hodel::hmirror(Grid const& piece)
{
    auto grid = piece;

    std::reverse(grid.begin(), grid.end());

    return grid;
}

hodel::Object hodel::hmirror(Object const& piece)
{
    auto const ulc = ulcorner(piece);
    auto const lrc = lrcorner(piece);
    auto const d = ulc.first + lrc.first;

    Object result;

    for (const auto& [v, pos] : piece)
    {
        auto [i, j] = pos;

        result.insert({v, {static_cast<Integer>(d - i), j}});
    }

    return result;
}

hodel::Indices hodel::hmirror(Indices const& piece)
{
    auto const ulc = ulcorner(piece);
    auto const lrc = lrcorner(piece);
    auto const d = ulc.first + lrc.first;

    Indices result;

    for (const auto& [i, j] : piece)
        result.insert({static_cast<Integer>(d - i), j});

    return result;
}

hodel::Grid hodel::vmirror(Grid const& piece)
{
    auto grid = piece;

    for (auto& row : grid)
        std::reverse(row.begin(), row.end());

    return grid;
}

hodel::Object hodel::vmirror(Object const& piece)
{
    auto const ulc = ulcorner(piece);
    auto const lrc = lrcorner(piece);
    auto const d = ulc.second + lrc.second;

    Object result;

    for (const auto& [v, pos] : piece)
    {
        auto [i, j] = pos;

        result.insert({v, {i, static_cast<Integer>(d - j)}});
    }

    return result;
}

hodel::Indices hodel::vmirror(Indices const& piece)
{
    auto const ulc = ulcorner(piece);
    auto const lrc = lrcorner(piece);
    auto const d = ulc.second + lrc.second;

    Indices result;

    for (const auto& [i, j] : piece)
        result.insert({i, static_cast<Integer>(d - j)});

    return result;
}

hodel::Grid hodel::dmirror(Grid const& piece)
{
    Grid result;

    try
    {
        auto const rows = static_cast<int>(piece.size());
        auto const cols = static_cast<int>(piece.at(0).size());

        result = Grid(cols, std::vector<Integer>(rows));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
                result.at(j).at(i) = piece.at(i).at(j);
        }

    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"dmirror"};
    }

    return result;
}

hodel::Object hodel::dmirror(Object const& piece)
{
    auto [a, b] = ulcorner(piece);

    Object result;

    for (const auto& [v, pos] : piece)
    {
        auto [i, j] = pos;

        result.insert({v, {static_cast<Integer>(j - b + a), static_cast<Integer>(i - a + b)}});
    }

    return result;
}

hodel::Indices hodel::dmirror(Indices const& piece)
{
    auto [a, b] = ulcorner(piece);

    Indices result;

    for (const auto& [i, j] : piece)
        result.insert({static_cast<Integer>(j - b + a), static_cast<Integer>(i - a + b)});

    return result;
}

hodel::Grid hodel::cmirror(Grid const& piece)
{
    return vmirror(dmirror(vmirror(piece)));
}

hodel::Object hodel::cmirror(Object const& piece)
{
    return vmirror(dmirror(vmirror(piece)));
}

hodel::Indices hodel::cmirror(Indices const& piece)
{
    return vmirror(dmirror(vmirror(piece)));
}

hodel::Grid hodel::hupscale(Grid const& grid, Integer const& factor)
{
    try
    {
        if (grid.size() > MAX_SIZE || grid.at(0).size() > MAX_SIZE)
            throw InvalidGrid{"hupscale"};
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"hupscale"};
    }

    if (factor <= 0 || factor > 20)
        throw InvalidInteger{"hupscale"};

    Grid result;

    for (const auto& row : grid)
    {
        std::vector<Integer> new_row;
        new_row.reserve(row.size() * factor);

        for (const auto& cell : row)
        {
            for (Integer i{0}; i < factor; ++i)
                new_row.emplace_back(cell);
        }

        result.emplace_back(new_row);
    }

    return result;
}

hodel::Grid hodel::vupscale(Grid const& grid, Integer const& factor)
{
    try
    {
        if (grid.size() > MAX_SIZE || grid.at(0).size() > MAX_SIZE)
            throw InvalidGrid{"vupscale"};
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"vupscale"};
    }

    if (factor <= 0 || factor > 20)
        throw InvalidInteger{"vupscale"};

    Grid result;
    result.reserve(grid.size() * factor);

    for (const auto& row : grid)
    {
        for (Integer k = 0; k < factor; ++k)
            result.emplace_back(row);
    }

    return result;
}

hodel::Grid hodel::upscale(Grid const& element, Integer const& factor)
{
    try
    {
        if (element.size() > MAX_SIZE || element.at(0).size() > MAX_SIZE)
            throw InvalidGrid{"upscale"};
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"upscale"};
    }

    if (factor <= 0 || factor > 20)
        throw InvalidInteger{"upscale"};

    Grid result;

    for (const auto& row : element)
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

    return result;
}

hodel::Object hodel::upscale(Object const& element, Integer const& factor)
{
    if (element.empty())
        throw EmptyObject{"upscale"};

    if (factor <= 0 || factor > 20)
        throw InvalidInteger{"upscale"};

    auto const [di_inv, dj_inv] = ulcorner(element);
    Integer const di = -di_inv;
    Integer const dj = -dj_inv;

    auto const normed_obj = shift(element, IntegerTuple{di, dj});
    Object result;

    for (auto const& [value, pos] : normed_obj)
    {
        auto const& [i, j] = pos;

        for (Integer io = 0; io < factor; ++io)
        {
            for (Integer jo = 0; jo < factor; ++jo)
                result.insert({value, {static_cast<Integer>(i * factor + io), static_cast<Integer>(j * factor + jo)}});
        }
    }

    result = shift(result, IntegerTuple{di_inv, dj_inv});

    return result;
}

hodel::Grid hodel::downscale(Grid const& grid, Integer const& factor)
{
    if (factor <= 1)
        throw InvalidInteger{"downscale"};

    Grid result;

    try
    {
        auto const h = static_cast<Integer>(grid.size());
        auto const w = static_cast<Integer>(grid.at(0).size());

        Grid temp;

        for (Integer i = 0; i < h; ++i)
        {
            std::vector<Integer> row;

            for (Integer j = 0; j < w; ++j)
            {
                if (j % factor == 0)
                    row.emplace_back(grid.at(i).at(j));
            }

            temp.emplace_back(row);
        }

        for (size_t i = 0; i < temp.size(); ++i)
        {
            if (i % factor == 0)
                result.emplace_back(temp[i]);
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"downscale"};
    }

    return result;
}

hodel::Grid hodel::hconcat(Grid const& a, Grid const& b)
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

hodel::Grid hodel::vconcat(Grid const& a, Grid const& b)
{
    Grid result;
    result.reserve(a.size() + b.size());

    result.insert(result.end(), a.begin(), a.end());
    result.insert(result.end(), b.begin(), b.end());

    return result;
}

hodel::Grid hodel::replace(Grid const& grid, Integer const& replacee, Integer const& replacer)
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

hodel::Grid hodel::switch_(Grid const& grid, Integer const& a, Integer const& b)
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

hodel::Grid hodel::tophalf(Grid const& grid)
{
    auto const mid = grid.size() / 2;

    return Grid(grid.begin(), grid.begin() + mid);
}

hodel::Grid hodel::bottomhalf(Grid const& grid)
{
    auto const mid = grid.size() / 2 + grid.size() % 2;

    return Grid(grid.begin() + mid, grid.end());
}

hodel::Grid hodel::lefthalf(Grid const& grid)
{
    return rot270(tophalf(rot90(grid)));
}

hodel::Grid hodel::righthalf(Grid const& grid)
{
    return rot270(bottomhalf(rot90(grid)));
}

hodel::Grid hodel::trim(hodel::Grid const &grid)
{
    Grid result;

    try
    {
        for (size_t i{1}; i + 1 < grid.size(); ++i)
            result.emplace_back(grid.at(i).begin() + 1, grid.at(i).end() - 1);
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"trim"};
    }

    return result;
}

hodel::Grid hodel::compress(Grid const& grid)
{
    Grid result;

    try
    {
        auto const h{grid.size()};
        auto const w{grid.at(0).size()};

        std::vector<bool> removeRow(h, false);

        for (size_t i = 0; i < h; ++i)
        {
            bool uniform{true};

            for (size_t j = 1; j < w; ++j)
            {
                if (grid.at(i).at(j) != grid.at(i).at(0))
                {
                    uniform = false;
                    break;
                }
            }

            removeRow[i] = uniform;
        }

        std::vector<bool> removeCol(w, false);

        for (Integer j = 0; j < w; ++j)
        {
            bool uniform{true};

            for (size_t i = 1; i < h; ++i)
            {
                if (grid.at(i).at(j) != grid.at(0).at(j))
                {
                    uniform = false;
                    break;
                }
            }

            removeCol[j] = uniform;
        }

        for (size_t i = 0; i < h; ++i)
        {
            if (removeRow[i])
                continue;

            std::vector<Integer> row;

            for (size_t j = 0; j < w; ++j)
            {
                if (!removeCol[j])
                    row.emplace_back(grid.at(i).at(j));
            }

            result.emplace_back(std::move(row));
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"compress"};
    }

    return result;
}

hodel::Object hodel::normalize(Object const& patch)
{
    if (patch.empty())
        throw EmptyObject{"normalize"};

    return shift(patch, IntegerTuple{static_cast<Integer>(-uppermost(patch)), static_cast<Integer>(-leftmost(patch))});
}

hodel::Indices hodel::normalize(Indices const& patch)
{
    if (patch.empty())
        throw EmptyIndices{"normalize"};

    return shift(patch, IntegerTuple{static_cast<Integer>(-uppermost(patch)), static_cast<Integer>(-leftmost(patch))});
}

hodel::Indices hodel::dneighbors(IntegerTuple const& loc)
{
    return {
        {static_cast<Integer>(loc.first - 1), loc.second},
        {static_cast<Integer>(loc.first + 1), loc.second},
        {loc.first, static_cast<Integer>(loc.second - 1)},
        {loc.first, static_cast<Integer>(loc.second + 1)}
    };
}

hodel::Indices hodel::ineighbors(IntegerTuple const& loc)
{
    return {
        {static_cast<Integer>(loc.first - 1), static_cast<Integer>(loc.second - 1)},
        {static_cast<Integer>(loc.first - 1), static_cast<Integer>(loc.second + 1)},
        {static_cast<Integer>(loc.first + 1), static_cast<Integer>(loc.second - 1)},
        {static_cast<Integer>(loc.first + 1), static_cast<Integer>(loc.second + 1)}
    };
}

hodel::Indices hodel::neighbors(IntegerTuple const& loc)
{
    auto result{dneighbors(loc)};
    auto const diagonal{ineighbors(loc)};

    result.insert(diagonal.begin(), diagonal.end());

    return result;
}

hodel::Object hodel::recolor(Integer const& value, Object const& patch)
{
    return recolor(value, toindices(patch));
}

hodel::Object hodel::recolor(Integer const& value, Indices const& patch)
{
    Object object;

    for (auto const& index : patch)
        object.emplace(value, index);

    return object;
}

hodel::Boolean hodel::square(Grid const& piece)
{
    try
    {
        return piece.size() == piece.at(0).size();
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"square"};
    }
}

hodel::Boolean hodel::square(Object const& piece)
{
    auto const h{height(piece)};
    auto const w{width(piece)};
    auto const l{static_cast<Integer>(piece.size())};

    return h * w == l && h == w;
}

hodel::Boolean hodel::square(Indices const& piece)
{
    auto const h{height(piece)};
    auto const w{width(piece)};
    auto const l{static_cast<Integer>(piece.size())};

    return h * w == l && h == w;
}

hodel::Boolean hodel::vline(Object const& patch)
{
    return vline(toindices(patch));
}

hodel::Boolean hodel::vline(Indices const& patch)
{
    auto const h{height(patch)};
    auto const w{width(patch)};
    auto const l{patch.size()};

    return h == l && w == 1;
}

hodel::Boolean hodel::hline(Object const& patch)
{
    return hline(toindices(patch));
}

hodel::Boolean hodel::hline(Indices const& patch)
{
    auto const h{height(patch)};
    auto const w{width(patch)};
    auto const l{patch.size()};

    return w == l && h == 1;
}

hodel::Integer hodel::height(Grid const& piece)
{
    if (piece.size() == 0)
        throw InvalidGrid{"height"};

    return static_cast<Integer>(piece.size());
}

hodel::Integer hodel::height(Object const& piece)
{
    return static_cast<Integer>(lowermost(piece) - uppermost(piece) + 1);
}

hodel::Integer hodel::height(Indices const& piece)
{
    return static_cast<Integer>(lowermost(piece) - uppermost(piece) + 1);
}

hodel::Integer hodel::width(Grid const& piece)
{
    try
    {
        return static_cast<Integer>(piece.at(0).size());
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"width"};
    }
}

hodel::Integer hodel::width(Object const& piece)
{
    return static_cast<Integer>(rightmost(piece) - leftmost(piece) + 1);
}

hodel::Integer hodel::width(Indices const& piece)
{
    return static_cast<Integer>(rightmost(piece) - leftmost(piece) + 1);
}

hodel::IntegerTuple hodel::shape(Grid const& piece)
{
    return {height(piece), width(piece)};
}

hodel::IntegerTuple hodel::shape(Object const& piece)
{
    return {height(piece), width(piece)};
}

hodel::IntegerTuple hodel::shape(Indices const& piece)
{
    return {height(piece), width(piece)};
}

hodel::Boolean hodel::portrait(Grid const& piece)
{
    auto const h{height(piece)};
    auto const w{width(piece)};

    return h > w;
}

hodel::Boolean hodel::portrait(Object const& piece)
{
    auto const h{height(piece)};
    auto const w{width(piece)};

    return h > w;
}

hodel::Boolean hodel::portrait(Indices const& piece)
{
    auto const h{height(piece)};
    auto const w{width(piece)};

    return h > w;
}

hodel::Boolean hodel::branch(Boolean const& condition, Boolean const& a, Boolean const& b)
{
    return condition ? a : b;
}

hodel::Integer hodel::branch(Boolean const& condition, Integer const& a, Integer const& b)
{
    return condition ? a : b;
}

hodel::IntegerTuple hodel::branch(Boolean const& condition, IntegerTuple const& a, IntegerTuple const& b)
{
    return condition ? a : b;
}

hodel::Indices hodel::branch(Boolean const& condition, Indices const& a, Indices const& b)
{
    return condition ? a : b;
}

hodel::Object hodel::branch(Boolean const& condition, Object const& a, Object const& b)
{
    return condition ? a : b;
}

hodel::Grid hodel::branch(Boolean const& condition, Grid const& a, Grid const& b)
{
    return condition ? a : b;
}

hodel::GridVector hodel::branch(Boolean const& condition, GridVector const& a, GridVector const& b)
{
    return condition ? a : b;
}

hodel::IntegerVector hodel::branch(Boolean const& condition, IntegerVector const& a, IntegerVector const& b)
{
    return condition ? a : b;
}

hodel::IndicesSet hodel::branch(Boolean const& condition, IndicesSet const& a, IndicesSet const& b)
{
    return condition ? a : b;
}

hodel::IntegerSet hodel::branch(Boolean const& condition, IntegerSet const& a, IntegerSet const& b)
{
    return condition ? a : b;
}

hodel::Objects hodel::branch(Boolean const& condition, Objects const& a, Objects const& b)
{
    return condition ? a : b;
}

hodel::ObjectVector hodel::branch(Boolean const& condition, ObjectVector const& a, ObjectVector const& b)
{
    return condition ? a : b;
}

hodel::ObjectsVector hodel::branch(Boolean const& condition, ObjectsVector const& a, ObjectsVector const& b)
{
    return condition ? a : b;
}

hodel::IndicesVector hodel::branch(Boolean const& condition, IndicesVector const& a, IndicesVector const& b)
{
    return condition ? a : b;
}

hodel::BooleanVector hodel::branch(Boolean const& condition, BooleanVector const& a, BooleanVector const& b)
{
    return condition ? a : b;
}

aicpp::FunctionValue hodel::branch(Boolean const& condition, aicpp::FunctionValue const& a, aicpp::FunctionValue const& b)
{
    if (a.connection.signature() != b.connection.signature())
        throw std::logic_error{"branch"};

    return condition ? a : b;
}

hodel::Integer hodel::color(Object const& object)
{
    if (object.empty())
        throw EmptyObject{"color"};

    return object.begin()->first;
}

hodel::Object hodel::toobject(Object const& patch, Grid const& grid)
{
    return toobject(toindices(patch), grid);
}

hodel::Object hodel::toobject(Indices const& patch, Grid const& grid)
{
    try
    {
        auto const h{grid.size()};
        auto const w{grid.at(0).size()};

        Object object;

        for (auto const& [i, j] : patch)
        {
            if (0 <= i && i < h && 0 <= j && j < w)
                object.emplace(grid.at(i).at(j), IntegerTuple{i, j});
        }

        return object;
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"toobject"};
    }
}

hodel::Object hodel::asobject(Grid const &grid)
{
    try
    {
        Object object;

        for (size_t i = 0; i < grid.size(); ++i)
        {
            for (size_t j = 0; j < grid.at(i).size(); ++j)
                object.emplace(grid.at(i).at(j), IntegerTuple{static_cast<Integer>(i), static_cast<Integer>(j)});
        }

        return object;
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"asobject"};
    }
}

hodel::Integer hodel::mostcolor(Grid const& element)
{
    auto const counts{colorCounts(element)};

    auto const it = std::max_element(
        counts.begin(),
        counts.end(),
        [] (auto const& a, auto const& b)
        {
            return a.second < b.second;
        });

    if (it == counts.end())
        return 0;

    return it->first;
}

hodel::Integer hodel::mostcolor(Object const& element)
{
    auto const counts{colorCounts(element)};

    auto const it = std::max_element(
        counts.begin(),
        counts.end(),
        [] (auto const& a, auto const& b)
        {
            return a.second < b.second;
        });

    if (it == counts.end())
        return 0;

    return it->first;
}

hodel::Integer hodel::leastcolor(Grid const& element)
{
    auto const counts{colorCounts(element)};

    auto const it = std::min_element(
        counts.begin(),
        counts.end(),
        [] (auto const& a, auto const& b)
        {
            return a.second < b.second;
        });

    if (it == counts.end())
        return 0;

    return it->first;
}

hodel::Integer hodel::leastcolor(Object const& element)
{
    auto const counts{colorCounts(element)};

    auto const it = std::min_element(
        counts.begin(),
        counts.end(),
        [] (auto const& a, auto const& b)
        {
            return a.second < b.second;
        });

    if (it == counts.end())
        return 0;

    return it->first;
}

hodel::Indices hodel::ofcolor(Grid const& grid, Integer const& value)
{
    Indices indices;

    try
    {
        for (size_t i{0}; i < grid.size(); ++i)
        {
            for (size_t j{0}; j < grid.at(i).size(); ++j)
            {
                if (grid.at(i).at(j) == value)
                    indices.emplace(i, j);
            }
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"ofcolor"};
    }

    return indices;
}

hodel::Integer hodel::colorcount(Grid const& element, Integer const& value)
{
    Integer count = 0;

    for (auto const& row : element)
        count += std::count(row.begin(), row.end(), value);

    return count;
}

hodel::Integer hodel::colorcount(Object const& element, Integer const& value)
{
    Integer count = 0;

    for (auto const& [color, position] : element)
    {
        if (color == value)
            ++count;
    }

    return count;
}

hodel::Objects hodel::colorfilter(Objects const& objs, Integer const& value)
{
    Objects result;

    for (auto const& obj : objs)
    {
        if (!obj.empty() && obj.begin()->first == value)
            result.emplace(obj);
    }

    return result;
}

hodel::Objects hodel::objects(Grid const& grid, Boolean const& univalued, Boolean const& diagonal, Boolean const& without_bg)
{
    Objects objs;

    try
    {
        auto const h = grid.size();
        auto const w = grid.at(0).size();
        auto const bg = without_bg ? mostcolor(grid) : Integer{-1};

        Indices occupied;
        auto unvisited = asindices(grid);

        for (auto const& loc : unvisited)
        {
            if (occupied.count(loc))
                continue;

            auto const val = grid.at(loc.first).at(loc.second);

            if (without_bg && val == bg)
                continue;

            Object obj;
            Indices candidates{loc};

            while (!candidates.empty())
            {
                Indices neighborhood;

                for (auto const& cand : candidates)
                {
                    if (occupied.count(cand))
                        continue;

                    auto const v = grid.at(cand.first).at(cand.second);

                    if ((univalued && v == val) ||
                        (!univalued && (!without_bg || v != bg)))
                    {
                        obj.emplace(v, cand);
                        occupied.insert(cand);

                        auto const neigh = diagonal ? neighbors(cand) : dneighbors(cand);

                        for (auto const& p : neigh)
                        {
                            auto const i = p.first;
                            auto const j = p.second;

                            if (0 <= i && i < h && 0 <= j && j < w)
                                neighborhood.insert(p);
                        }
                    }
                }

                candidates.clear();

                for (const auto& p : neighborhood)
                {
                    if (!occupied.count(p))
                        candidates.insert(p);
                }
            }

            objs.insert(std::move(obj));
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"objects"};
    }

    return objs;
}

hodel::Objects hodel::partition(Grid const& grid)
{
    std::map<Integer, Object> objectsByColor;
    Objects result;

    try
    {
        for (size_t i = 0; i < grid.size(); ++i)
        {
            for (size_t j = 0; j < grid.at(i).size(); ++j)
            {
                auto const color = grid.at(i).at(j);
                objectsByColor[color].emplace(color, IntegerTuple{static_cast<Integer>(i), static_cast<Integer>(j)});
            }
        }

        for (auto& [color, object] : objectsByColor)
            result.insert(std::move(object));

    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"partition"};
    }

    return result;
}

hodel::Objects hodel::fgpartition(Grid const& grid)
{
    std::map<Integer, Object> objectsByColor;
    Objects result;

    try
    {
        for (size_t i = 0; i < grid.size(); ++i)
        {
            for (size_t j = 0; j < grid.at(i).size(); ++j)
            {
                auto const color = grid.at(i).at(j);
                objectsByColor[color].emplace(color, IntegerTuple{static_cast<Integer>(i), static_cast<Integer>(j)});
            }
        }

        auto const bg{mostcolor(grid)};

        for (auto& [color, object] : objectsByColor)
        {
            if (color != bg)
                result.insert(std::move(object));
        }
    }
    catch (std::exception const&)
    {
        throw std::runtime_error{"Wrong value"};
    }

    return result;
}

hodel::Indices hodel::asindices(Grid const& grid)
{
    Indices indices;

    try
    {
        for (size_t i{0}; i < grid.size(); ++i)
        {
            for (size_t j{0}; j < grid.at(0).size(); ++j)
                indices.emplace(i, j);
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"asindices"};
    }

    return indices;
}

hodel::Boolean hodel::equality(Boolean const& a, Boolean const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(Integer const& a, Integer const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(IntegerTuple const& a, IntegerTuple const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(Indices const& a, Indices const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(Object const& a, Object const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(Grid const& a, Grid const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(GridVector const& a, GridVector const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(IntegerVector const& a, IntegerVector const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(IndicesSet const& a, IndicesSet const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(IntegerSet const& a, IntegerSet const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(Objects const& a, Objects const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(ObjectVector const& a, ObjectVector const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(ObjectsVector const& a, ObjectsVector const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(IndicesVector const& a, IndicesVector const& b)
{
    return a == b;
}

hodel::Boolean hodel::equality(BooleanVector const& a, BooleanVector const& b)
{
    return a == b;
}

hodel::Boolean hodel::hmatching(Object const& a, Indices const& b)
{
    return hmatching(toindices(a), b);
}

hodel::Boolean hodel::hmatching(Indices const& a, Object const& b)
{
    return hmatching(a, toindices(b));
}

hodel::Boolean hodel::hmatching(Object const& a, Object const& b)
{
    return hmatching(toindices(a), toindices(b));
}

hodel::Boolean hodel::hmatching(Indices const& a, Indices const& b)
{
    std::set<Integer> rows;

    for (auto const& [i, j] : a)
        rows.insert(i);

    for (auto const& [i, j] : b)
    {
        if (rows.count(i))
            return true;
    }

    return false;
}

hodel::Boolean hodel::vmatching(Object const& a, Indices const& b)
{
    return vmatching(toindices(a), b);
}

hodel::Boolean hodel::vmatching(Indices const& a, Object const& b)
{
    return vmatching(a, toindices(b));
}

hodel::Boolean hodel::vmatching(Object const& a, Object const& b)
{
    return vmatching(toindices(a), toindices(b));
}

hodel::Boolean hodel::vmatching(Indices const& a, Indices const& b)
{
    std::set<Integer> cols;

    for (auto const& [i, j] : a)
        cols.insert(j);

    for (auto const& [i, j] : b)
    {
        if (cols.count(j))
            return true;
    }

    return false;
}

hodel::Integer hodel::manhattan(Object const& a, Indices const& b)
{
    return manhattan(toindices(a), b);
}

hodel::Integer hodel::manhattan(Indices const& a, Object const& b)
{
    return manhattan(a, toindices(b));
}

hodel::Integer hodel::manhattan(Object const& a, Object const& b)
{
    return manhattan(toindices(a), toindices(b));
}

hodel::Integer hodel::manhattan(Indices const& a, Indices const& b)
{
    auto dmin{std::numeric_limits<Integer>::max()};

    for (auto const& [ai, aj] : a)
    {
        for (auto const& [bi, bj] : b)
        {
            auto const d{std::abs(static_cast<int>(ai) - static_cast<int>(bi)) + std::abs(static_cast<int>(aj) - static_cast<int>(bj))};
            dmin = static_cast<Integer>(std::min(static_cast<int>(dmin), d));
        }
    }

    return dmin;
}

hodel::Boolean hodel::adjacent(Object const& a, Indices const& b)
{
    return adjacent(toindices(a), b);
}

hodel::Boolean hodel::adjacent(Indices const& a, Object const& b)
{
    return adjacent(a, toindices(b));
}

hodel::Boolean hodel::adjacent(Object const& a, Object const& b)
{
    return adjacent(toindices(a), toindices(b));
}

hodel::Boolean hodel::adjacent(Indices const& a, Indices const& b)
{
    return manhattan(a, b) == 1;
}

hodel::Boolean hodel::bordering(Object const& patch, Grid const grid)
{
    return bordering(toindices(patch), grid);
}

hodel::Boolean hodel::bordering(Indices const& patch, Grid const grid)
{
    try
    {
        auto const urm{uppermost(patch)};
        auto const ltm{leftmost(patch)};
        auto const lrm{lowermost(patch)};
        auto const rtm{rightmost(patch)};

        return urm == 0 || ltm == 0 || lrm == grid.size() - 1 || rtm == grid.at(0).size() - 1;
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"bordering"};
    }
}

hodel::IntegerTuple hodel::centerofmass(Object const &patch)
{
    return centerofmass(toindices(patch));
}

hodel::IntegerTuple hodel::centerofmass(Indices const &patch)
{
    auto const l{patch.size()};

    if (!l)
        throw InvalidInteger{"centerofmass"};

    Integer sumRow{0};
    Integer sumCol{0};

    for (auto const& [i, j] : patch)
    {
        sumRow += i;
        sumCol += j;
    }

    return {static_cast<Integer>(sumRow / l), static_cast<Integer>(sumCol / l)};
}

hodel::IntegerSet hodel::palette(Grid const& element)
{
    IntegerSet colors;

    for (auto const& row : element)
        colors.insert(row.begin(), row.end());

    return colors;
}

hodel::IntegerSet hodel::palette(Object const& element)
{
    IntegerSet colors;

    for (auto const& [color, position] : element)
        colors.insert(color);

    return colors;
}

hodel::Integer hodel::numcolors(Grid const& element)
{
    return palette(element).size();
}

hodel::Integer hodel::numcolors(Object const& element)
{
    return palette(element).size();
}

hodel::Grid hodel::fill(Grid const& grid, Integer const& value, Object const& patch)
{
    return fill(grid, value, toindices(patch));
}

hodel::Grid hodel::fill(Grid const& grid, Integer const& value, Indices const& patch)
{
    Grid result = grid;

    try
    {
        auto const h{grid.size()};
        auto const w{grid.at(0).size()};

        for (auto const& [i, j] : patch)
        {
            if (0 <= i && i < h && 0 <= j && j < w)
                result.at(i).at(j) = value;
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"fill"};
    }

    return result;
}

hodel::Grid hodel::paint(Grid const& grid, Object const& obj)
{

    Grid result{grid};

    try
    {
        auto const h{grid.size()};
        auto const w{grid.at(0).size()};

        for (auto const& [value, location] : obj)
        {
            auto const& [i, j] = location;

            if (0 <= i && i < h && 0 <= j && j < w)
                result.at(i).at(j) = value;
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"paint"};
    }

    return result;
}

hodel::Grid hodel::underfill(Grid const& grid, Integer const& value, Object const& patch)
{
    return underfill(grid, value, toindices(patch));
}

hodel::Grid hodel::underfill(Grid const& grid, Integer const& value, Indices const& patch)
{
    Grid result{grid};

    try
    {
        auto const h{grid.size()};
        auto const w{grid.at(0).size()};
        auto const bg{mostcolor(grid)};

        for (auto const& [i, j] : patch)
        {
            if (0 <= i && i < h && 0 <= j && j < w && result.at(i).at(j) == bg)
                result.at(i).at(j) = value;
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"underfill"};
    }

    return result;
}

hodel::Grid hodel::underpaint(Grid const& grid, Object const& obj)
{
    Grid result{grid};

    try
    {
        auto const h{grid.size()};
        auto const w{grid.at(0).size()};
        auto const bg{mostcolor(grid)};

        for (auto const& [value, location] : obj)
        {
            auto const& [i, j] = location;

            if (0 <= i && i < h && 0 <= j && j < w && result.at(i).at(j) == bg)
                result.at(i).at(j) = value;
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"underpaint"};
    }

    return result;
}

hodel::IntegerTuple hodel::center(Object const& patch)
{
    return center(toindices(patch));
}

hodel::IntegerTuple hodel::center(Indices const& patch)
{
    auto const um{uppermost(patch)};
    auto const h{height(patch)};
    auto const lm{leftmost(patch)};
    auto const w{width(patch)};

    return {static_cast<Integer>(um + h / 2), static_cast<Integer>(lm + w / 2)};
}

hodel::IntegerTuple hodel::position(Indices const& a, Indices const& b)
{
    auto const [ia, ja] = center(a);
    auto const [ib, jb] = center(b);

    if (ia == ib)
        return {0, static_cast<Integer>(ja < jb ? 1 : -1)};
    else if (ja == jb)
        return {static_cast<Integer>(ia < ib ? 1: -1), 0};
    else if (ia < ib)
        return {1, static_cast<Integer>(ja < jb ? 1 : -1)};
    else if (ia > ib)
        return {-1, static_cast<Integer>(ja < jb ? 1 : -1)};

    return {0, 0};
}

hodel::IntegerTuple hodel::position(Object const& a, Indices const& b)
{
    return position(toindices(a), b);
}

hodel::IntegerTuple hodel::position(Indices const& a, Object const& b)
{
    return position(a, toindices(b));
}

hodel::IntegerTuple hodel::position(Object const& a, Object const& b)
{
    return position(toindices(a), toindices(b));
}

hodel::Integer hodel::index(Grid const& grid, IntegerTuple const& loc)
{
    try
    {
        auto const& [i, j] = loc;
        auto const h{grid.size()};
        auto const w{grid.at(0).size()};

        if (!(0 <= i && i < h && 0 <= j && j < w))
            throw InvalidIntegerTuple{"index"};

        return grid.at(i).at(j);
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"index"};
    }
}

hodel::Grid hodel::canvas(Integer const& value, IntegerTuple const& dimensions)
{
    if (dimensions.first <= 0 || dimensions.second <= 0)
        throw InvalidIntegerTuple{"canvas"};

    return Grid(dimensions.first, std::vector<Integer>(dimensions.second, value));
}

hodel::Indices hodel::corners(Object const& patch)
{
    return corners(toindices(patch));
}

hodel::Indices hodel::corners(Indices const& patch)
{
    auto const ulc{ulcorner(patch)};
    auto const urc{urcorner(patch)};
    auto const llc{llcorner(patch)};
    auto const lrc{lrcorner(patch)};

    return {ulc, urc, llc, lrc};
}

hodel::Indices hodel::connect(IntegerTuple const& a, IntegerTuple const& b)
{
    auto const& [ai, aj] = a;
    auto const& [bi, bj] = b;

    Integer di{0};
    Integer dj{0};

    if (std::abs(bi - ai) > SHOOT_DISTANCE * MAX_SIZE || std::abs(bj - aj) > SHOOT_DISTANCE * MAX_SIZE)
        throw InvalidIntegerTuple{"connect"};

    if (ai == bi)
        dj = (bj > aj ? 1 : -1);
    else if (aj == bj)
        di = (bi > ai ? 1 : -1);
    else if (std::abs(bi - ai) == std::abs(bj - aj))
    {
        di = (bi > ai ? 1 : -1);
        dj = (bj > aj ? 1 : -1);
    }
    else
        throw InvalidIntegerTuple{"connect"};

    Indices result;

    auto i{ai};
    auto j{aj};

    while (true)
    {
        result.emplace(i, j);

        if (i == bi && j == bj)
            break;

        i += di;
        j += dj;
    }

    return result;
}

hodel::Grid hodel::cover(Grid const& grid, Object const& patch)
{
    return cover(grid, toindices(patch));
}

hodel::Grid hodel::cover(Grid const& grid, Indices const& patch)
{
    return fill(grid, mostcolor(grid), patch);
}

hodel::Indices hodel::vfrontier(IntegerTuple const& location)
{
    Indices result;

    for (Integer i{0}; i < MAX_SIZE; ++i)
        result.emplace(i, location.second);

    return result;
}

hodel::Indices hodel::hfrontier(IntegerTuple const& location)
{
    Indices result;

    for (Integer j{0}; j < MAX_SIZE; ++j)
        result.emplace(location.first, j);

    return result;
}

hodel::Indices hodel::backdrop(Object const& patch)
{
    return backdrop(toindices(patch));
}

hodel::Indices hodel::backdrop(Indices const& patch)
{
    auto const ulc{ulcorner(patch)};
    auto const lrc{lrcorner(patch)};

    Indices result;

    for (Integer i = ulc.first; i <= lrc.first; ++i)
    {
        for (Integer j = ulc.second; j <= lrc.second; ++j)
            result.emplace(i, j);
    }

    return result;
}

hodel::Indices hodel::delta(Object const& patch)
{
    return delta(toindices(patch));
}

hodel::Indices hodel::delta(Indices const& patch)
{
    auto result = backdrop(patch);

    for (const auto& p : patch)
        result.erase(p);

    return result;
}

hodel::IntegerTuple hodel::gravitate(Indices const& source, Indices const& destination)
{
    auto current = source;
    auto const [si, sj] = center(current);
    auto const [di, dj] = center(destination);

    Integer stepI = 0;
    Integer stepJ = 0;

    if (vmatching(current, destination))
        stepI = (si < di) ? 1 : -1;
    else
        stepJ = (sj < dj) ? 1 : -1;

    auto moveI = stepI;
    auto moveJ = stepJ;
    Integer count = 0;

    while (!adjacent(current, destination) && count < 42)
    {
        ++count;

        moveI += stepI;
        moveJ += stepJ;

        current = shift(current, IntegerTuple{stepI, stepJ});
    }

    return IntegerTuple{static_cast<Integer>(moveI - stepI), static_cast<Integer>(moveJ - stepJ)};
}

hodel::IntegerTuple hodel::gravitate(Object const& source, Indices const& destination)
{
    return gravitate(toindices(source), destination);
}

hodel::IntegerTuple hodel::gravitate(Indices const& source, Object const& destination)
{
    return gravitate(source, toindices(destination));
}

hodel::IntegerTuple hodel::gravitate(Object const& source, Object const& destination)
{
    return gravitate(toindices(source), toindices(destination));
}

hodel::Indices hodel::inbox(Object const& patch)
{
    return inbox(toindices(patch));
}

hodel::Indices hodel::inbox(Indices const& patch)
{
    auto const ai = uppermost(patch) + 1;
    auto const aj = leftmost(patch) + 1;
    auto const bi = lowermost(patch) - 1;
    auto const bj = rightmost(patch) - 1;

    return rectangleOutline(
        std::min(ai, bi),
        std::min(aj, bj),
        std::max(ai, bi),
        std::max(aj, bj));
}

hodel::Indices hodel::outbox(Object const& patch)
{
    return outbox(toindices(patch));
}

hodel::Indices hodel::outbox(Indices const& patch)
{
    auto const ai = uppermost(patch) - 1;
    auto const aj = leftmost(patch) - 1;
    auto const bi = lowermost(patch) + 1;
    auto const bj = rightmost(patch) + 1;

    return rectangleOutline(
        std::min(ai, bi),
        std::min(aj, bj),
        std::max(ai, bi),
        std::max(aj, bj));
}

hodel::Indices hodel::box(Object const& patch)
{
    return box(toindices(patch));
}

hodel::Indices hodel::box(Indices const& patch)
{
    auto const [ai, aj] = ulcorner(patch);
    auto const [bi, bj] = lrcorner(patch);

    return rectangleOutline(
        std::min(ai, bi),
        std::min(aj, bj),
        std::max(ai, bi),
        std::max(aj, bj));
}

hodel::Indices hodel::shoot(IntegerTuple const& start, IntegerTuple const& direction)
{
    if (std::abs(start.first) > 100 || std::abs(start.second) > 100)
        throw InvalidIntegerTuple{"shoot"};

    auto const fd{static_cast<size_t>(direction.first)};
    auto const sd{static_cast<size_t>(direction.second)};

    if (fd * fd + sd * sd > 2 * MAX_SIZE * MAX_SIZE)
        throw InvalidIntegerTuple{"shoot"};

    return connect(start,
        IntegerTuple{static_cast<Integer>(start.first + SHOOT_DISTANCE * direction.first),
                     static_cast<Integer>(start.second + SHOOT_DISTANCE * direction.second)});
}

hodel::Indices hodel::occurrences(Grid const& grid, Object const& obj)
{
    if (grid.empty())
        throw EmptyGrid{"occurrences"};

    if (obj.empty())
        throw EmptyObject{"occurrences"};

    Indices occs;

    try
    {
        auto const normed = normalize(obj);
        auto const h{grid.size()};
        auto const w{grid.at(0).size()};
        auto const [oh, ow] = shape(obj);

        for (size_t i = 0; i <= h - oh; ++i)
        {
            for (size_t j = 0; j <= w - ow; ++j)
            {
                bool ok = true;

                for (auto const& [value, pos] : normed)
                {
                    size_t const a = pos.first + i;
                    size_t const b = pos.second + j;

                    if (grid.at(a).at(b) != value)
                    {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                    occs.emplace(static_cast<Integer>(i), static_cast<Integer>(j));
            }
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"occurrences"};
    }

    return occs;
}

hodel::Objects hodel::frontiers(Grid const& grid)
{
    Objects result;
    
    try
    {

        auto const h = grid.size();
        auto const w = grid.at(0).size();

        for (size_t i = 0; i < h; ++i)
        {
            auto const color = grid.at(i).at(0);
            bool uniform = true;

            for (size_t j = 1; j < w; ++j)
            {
                if (grid.at(i).at(j) != color)
                {
                    uniform = false;
                    break;
                }
            }

            if (uniform)
            {
                Object object;

                for (size_t j = 0; j < w; ++j)
                    object.emplace(grid.at(i).at(j), IntegerTuple{static_cast<Integer>(i), static_cast<Integer>(j)});

                result.insert(std::move(object));
            }
        }

        for (size_t j = 0; j < w; ++j)
        {
            auto const color = grid.at(0).at(j);
            bool uniform = true;

            for (size_t i = 1; i < h; ++i)
            {
                if (grid.at(i).at(j) != color)
                {
                    uniform = false;
                    break;
                }
            }

            if (uniform)
            {
                Object object;

                for (size_t i = 0; i < h; ++i)
                    object.emplace(grid.at(i).at(j), IntegerTuple{static_cast<Integer>(i), static_cast<Integer>(j)});

                result.insert(std::move(object));
            }
        }
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"frontiers"};
    }

    return result;
}

hodel::Integer hodel::hperiod(Object const &obj)
{
    auto const normalized = normalize(obj);
    auto const w = width(normalized);

    for (Integer p = 1; p < w; ++p)
    {
        auto const offsetted = shift(normalized, IntegerTuple{0, static_cast<Integer>(-p)});

        Object pruned;

        for (auto const& [color, pos] : offsetted)
        {
            if (pos.second >= 0)
                pruned.emplace(color, pos);
        }

        if (std::includes(normalized.begin(), normalized.end(), pruned.begin(), pruned.end()))
            return p;
    }

    return w;
}

hodel::Integer hodel::vperiod(Object const &obj)
{
    auto const normalized = normalize(obj);
    auto const h = height(normalized);

    for (Integer p = 1; p < h; ++p)
    {
        auto const offsetted = shift(normalized, IntegerTuple{static_cast<Integer>(-p), 0});

        Object pruned;

        for (auto const& [color, pos] : offsetted)
        {
            if (pos.first >= 0)
                pruned.emplace(color, pos);
        }

        if (std::includes(normalized.begin(), normalized.end(), pruned.begin(), pruned.end()))
            return p;
    }

    return h;
}

hodel::Grid hodel::pair(IntegerVector const& a, IntegerVector const &b)
{
    if (a.size() != b.size())
        throw InvalidIntegerVector{"pair"};

    Grid result;
    result.reserve(a.size());

    try
    {
        for (size_t i = 0; i < a.size(); ++i)
            result.emplace_back(a.at(i), b.at(i));
    }
    catch (std::exception const&)
    {
        throw InvalidIntegerVector{"pair"};
    }

    return result;
}

hodel::Integer hodel::size(Object const& container)
{
    return container.size();
}

hodel::Integer hodel::size(Objects const& container)
{
    return container.size();
}

hodel::Integer hodel::size(ObjectVector const& container)
{
    return container.size();
}

hodel::Integer hodel::size(ObjectsVector const& container)
{
    return container.size();
}

hodel::Integer hodel::size(Indices const& container)
{
    return container.size();
}

hodel::Integer hodel::size(IndicesSet const& container)
{
    return container.size();
}

hodel::Integer hodel::size(IntegerSet const& container)
{
    return container.size();
}

hodel::Integer hodel::size(Grid const& container)
{
    return container.size();
}

hodel::Integer hodel::size(GridVector const& container)
{
    return container.size();
}

hodel::Integer hodel::size(IntegerTuple const& container)
{
    return 2;
}

hodel::Integer hodel::size(IndicesVector const& container)
{
    return container.size();
}

hodel::Integer hodel::size(BooleanVector const& container)
{
    return container.size();
}

hodel::Integer hodel::size(FunctionIntegerPair const& container)
{
    return 2;
}

hodel::Integer hodel::size(FunctionIntegerPairVector const& container)
{
    return container.size();
}

hodel::Integer hodel::size(Cell const& container)
{
    return 2;
}

hodel::Boolean  hodel::identity(Boolean const& x)
{
    return x;
}

hodel::Integer  hodel::identity(Integer const& x)
{
    return x;
}

hodel::IntegerTuple hodel::identity(IntegerTuple const& x)
{
    return x;
}

hodel::Indices hodel::identity(Indices const& x)
{
    return x;
}

hodel::Object hodel::identity(Object const& x)
{
    return x;
}

hodel::Grid hodel::identity(Grid const& x)
{
    return x;
}

hodel::GridVector hodel::identity(GridVector const& x)
{
    return x;
}

hodel::IntegerVector hodel::identity(IntegerVector const& x)
{
    return x;
}

hodel::IndicesSet hodel::identity(IndicesSet const& x)
{
    return x;
}

hodel::IntegerSet hodel::identity(IntegerSet const& x)
{
    return x;
}

hodel::Objects hodel::identity(Objects const& x)
{
    return x;
}

hodel::ObjectVector hodel::identity(ObjectVector const& x)
{
    return x;
}

hodel::ObjectsVector hodel::identity(ObjectsVector const& x)
{
    return x;
}

hodel::IndicesVector hodel::identity(IndicesVector const& x)
{
    return x;
}

hodel::BooleanVector hodel::identity(BooleanVector const& x)
{
    return x;
}

hodel::Integer hodel::first(IntegerTuple const& x)
{
    return x.first;
}

hodel::IntegerTuple hodel::first(Indices const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Cell hodel::first(Object const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::IntegerVector hodel::first(Grid const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Grid hodel::first(GridVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Integer hodel::first(IntegerVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Indices hodel::first(IndicesSet const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Integer hodel::first(IntegerSet const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Object hodel::first(Objects const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Object hodel::first(ObjectVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Objects hodel::first(ObjectsVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Indices hodel::first(IndicesVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::Boolean hodel::first(BooleanVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

aicpp::FunctionValue hodel::first(FunctionSet const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

hodel::FunctionIntegerPair hodel::first(FunctionIntegerPairVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"first"};

    return *x.begin();
}

aicpp::FunctionValue hodel::first(FunctionIntegerPair const& x)
{
    return x.first;
}

hodel::Integer hodel::first(Cell const& x)
{
    return x.first;
}

hodel::Integer hodel::last(IntegerTuple const& x)
{
    return x.second;
}

hodel::IntegerTuple hodel::last(Indices const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Cell hodel::last(Object const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::IntegerVector hodel::last(Grid const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Grid hodel::last(GridVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Integer hodel::last(IntegerVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Indices hodel::last(IndicesSet const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Integer hodel::last(IntegerSet const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Object hodel::last(Objects const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Object hodel::last(ObjectVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Objects hodel::last(ObjectsVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Indices hodel::last(IndicesVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Boolean hodel::last(BooleanVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

aicpp::FunctionValue hodel::last(FunctionSet const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::FunctionIntegerPair hodel::last(FunctionIntegerPairVector const& x)
{
    if (x.empty())
        throw EmptyContainer{"last"};

    return *x.rbegin();
}

hodel::Integer hodel::last(FunctionIntegerPair const& x)
{
    return x.second;
}

hodel::IntegerTuple hodel::last(Cell const& x)
{
    return x.second;
}

hodel::Indices hodel::insert(IntegerTuple const& value, Indices const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::Object hodel::insert(Cell const& value, Object const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::Grid hodel::insert(IntegerVector const& value, Grid const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::GridVector hodel::insert(Grid const& value, GridVector const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::IntegerVector hodel::insert(Integer const& value, IntegerVector const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::IndicesSet hodel::insert(Indices const& value, IndicesSet const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::IntegerSet hodel::insert(Integer const& value, IntegerSet const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::Objects hodel::insert(Object const& value, Objects const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::ObjectVector hodel::insert(Object const& value, ObjectVector const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::ObjectsVector hodel::insert(Objects const& value, ObjectsVector const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::IndicesVector hodel::insert(Indices const& value, IndicesVector const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::BooleanVector hodel::insert(Boolean const& value, BooleanVector const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::FunctionSet hodel::insert(aicpp::FunctionValue const& value, hodel::FunctionSet const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::FunctionIntegerPairVector hodel::insert(FunctionIntegerPair const& value, FunctionIntegerPairVector const& container)
{
    auto result{container};

    result.insert(result.end(), value);

    return result;
}

hodel::Indices hodel::remove(IntegerTuple const& value, Indices const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::Object hodel::remove(Cell const& value, Object const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::Grid hodel::remove(IntegerVector const& value, Grid const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::GridVector hodel::remove(Grid const& value, GridVector const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::IntegerVector hodel::remove(Integer const& value, IntegerVector const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::IndicesSet hodel::remove(Indices const& value, IndicesSet const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::IntegerSet hodel::remove(Integer const& value, IntegerSet const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::Objects hodel::remove(Object const& value, Objects const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::ObjectVector hodel::remove(Object const& value, ObjectVector const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::ObjectsVector hodel::remove(Objects const& value, ObjectsVector const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::IndicesVector hodel::remove(Indices const& value, IndicesVector const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::BooleanVector hodel::remove(Boolean const& value, BooleanVector const& container)
{
    auto result{container};
    auto const it{std::find(result.begin(), result.end(), value)};

    if (it == result.end())
        throw InvalidContainer{"remove"};

    result.erase(it);

    return result;
}

hodel::IntegerTuple hodel::other(Indices const& container, IntegerTuple const& value)
{
    return first(remove(value, container));
}

hodel::Cell hodel::other(Object const& container, Cell const& value)
{
    return first(remove(value, container));
}

hodel::IntegerVector hodel::other(Grid const& container, IntegerVector const& value)
{
    return first(remove(value, container));
}

hodel::Grid hodel::other(GridVector const& container, Grid const& value)
{
    return first(remove(value, container));
}

hodel::Integer hodel::other(IntegerVector const& container, Integer const& value)
{
    return first(remove(value, container));
}

hodel::Indices hodel::other(IndicesSet const& container, Indices const& value)
{
    return first(remove(value, container));
}

hodel::Integer hodel::other(IntegerSet const& container, Integer const& value)
{
    return first(remove(value, container));
}

hodel::Object hodel::other(Objects const& container, Object const& value)
{
    return first(remove(value, container));
}

hodel::Object hodel::other(ObjectVector const& container, Object const& value)
{
    return first(remove(value, container));
}

hodel::Objects hodel::other(ObjectsVector const& container, Objects const& value)
{
    return first(remove(value, container));
}

hodel::Indices hodel::other(IndicesVector const& container, Indices const& value)
{
    return first(remove(value, container));
}

hodel::Boolean hodel::other(BooleanVector const& container, Boolean const& value)
{
    return first(remove(value, container));
}

hodel::Indices hodel::initset(IntegerTuple const& value)
{
    return {value};
}

hodel::Object hodel::initset(Cell const& value)
{
    return {value};
}

hodel::Grid hodel::initset(IntegerVector const& value)
{
    return {value};
}

hodel::GridVector hodel::initset(Grid const& value)
{
    return {value};
}

hodel::IndicesSet hodel::initset(Indices const& value)
{
    return {value};
}

hodel::IntegerSet hodel::initset(Integer const& value)
{
    return {value};
}

hodel::Objects hodel::initset(Object const& value)
{
    return {value};
}

hodel::ObjectsVector hodel::initset(Objects const& value)
{
    return {value};
}

hodel::BooleanVector hodel::initset(Boolean const& value)
{
    return {value};
}
hodel::FunctionSet hodel::initset(aicpp::FunctionValue const& value)
{
    return {value};
}

hodel::FunctionIntegerPairVector hodel::initset(FunctionIntegerPair const& value)
{
    return {value};
}

hodel::IntegerVector hodel::totuple(IntegerTuple const& container)
{
    return {container.first, container.second};
}

hodel::IntegerVector hodel::totuple(IntegerSet const& container)
{
    return {container.begin(), container.end()};
}

hodel::IndicesVector hodel::totuple(IndicesSet const& container)
{
    return {container.begin(), container.end()};
}

hodel::ObjectVector hodel::totuple(Objects const& container)
{
    return {container.begin(), container.end()};
}

hodel::Grid hodel::subgrid(Object const& patch, Grid const& grid)
{
    return subgrid(toindices(patch), grid);
}

hodel::Grid hodel::subgrid(Indices const& patch, Grid const& grid)
{
    return crop(grid, ulcorner(patch), shape(patch));
}

hodel::GridVector hodel::hsplit(Grid const& grid, Integer const& n)
{
    if (n <= 0)
        throw InvalidInteger{"hsplit"};

    std::vector<Grid> result;
    result.reserve(n);

    try
    {
        auto const h{grid.size()};
        auto const w{grid.at(0).size() / n};
        Integer const offset{(grid.at(0).size() % n != 0)};

        for (Integer i = 0; i < n; ++i)
            result.emplace_back(crop(grid,
                                     IntegerTuple{0, static_cast<Integer>(w * i + i * offset)},
                                     IntegerTuple{static_cast<Integer>(h), static_cast<Integer>(w)}));
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"hsplit"};
    }

    return result;
}

hodel::GridVector hodel::vsplit(Grid const& grid, Integer const& n)
{
    if (n <= 0)
        throw InvalidInteger{"vsplit"};

    std::vector<Grid> result;
    result.reserve(n);

    try
    {
        auto const h{grid.size() / n};
        auto const w{grid.at(0).size()};
        Integer const offset{(grid.size() % n != 0)};

        for (Integer i = 0; i < n; ++i)
            result.emplace_back(crop(grid,
                                     IntegerTuple{static_cast<Integer>(h * i + i * offset), 0},
                                     IntegerTuple{static_cast<Integer>(h), static_cast<Integer>(w)}));
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"vsplit"};
    }

    return result;
}

hodel::BooleanVector hodel::repeat(Boolean const& item, Integer const& num)
{
    if (num <= 0 || num > 100)
        throw InvalidInteger{"repeat"};

    return hodel::BooleanVector(static_cast<size_t>(num), item);
}

hodel::IntegerVector hodel::repeat(Integer const& item, Integer const& num)
{
    if (num <= 0 || num > 100)
        throw InvalidInteger{"repeat"};

    return hodel::IntegerVector(static_cast<size_t>(num), item);
}

hodel::Grid hodel::repeat(IntegerVector const& item, Integer const& num)
{
    if (num <= 0 || num > 100)
        throw InvalidInteger{"repeat"};

    return {static_cast<size_t>(num), item};
}

hodel::GridVector hodel::repeat(Grid const& item, Integer const& num)
{
    if (num <= 0 || num > 100)
        throw InvalidInteger{"repeat"};

    return {static_cast<size_t>(num), item};
}

hodel::ObjectVector hodel::repeat(Object const& item, Integer const& num)
{
    if (num <= 0 || num > 100)
        throw InvalidInteger{"repeat"};

    return {static_cast<size_t>(num), item};
}

hodel::ObjectsVector hodel::repeat(Objects const& item, Integer const& num)
{
    if (num <= 0 || num > 100)
        throw InvalidInteger{"repeat"};

    return {static_cast<size_t>(num), item};
}

hodel::IndicesVector hodel::repeat(Indices const& item, Integer const& num)
{
    if (num <= 0 || num > 100)
        throw InvalidInteger{"repeat"};

    return {static_cast<size_t>(num), item};
}

hodel::GridVector hodel::dedupe(GridVector const& tup)
{
    std::remove_cvref_t<decltype(tup)> r;
    r.reserve(tup.size());

    for (size_t i{0}; i < tup.size(); ++i)
    {
        auto const result{std::ranges::find_end(tup, std::views::single(tup.at(i)))};

        if (result.begin() != tup.end() && std::distance(tup.begin(), result.begin()) == i)
            r.emplace_back(tup.at(i));
    }

    return r;
}

hodel::BooleanVector hodel::dedupe(BooleanVector const& tup)
{
    std::remove_cvref_t<decltype(tup)> r;
    r.reserve(tup.size());

    for (size_t i{0}; i < tup.size(); ++i)
    {
        auto const result{std::ranges::find_end(tup, std::views::single(tup.at(i)))};

        if (result.begin() != tup.end() && std::distance(tup.begin(), result.begin()) == i)
            r.emplace_back(tup.at(i));
    }

    return r;
}

hodel::IntegerVector hodel::dedupe(IntegerVector const& tup)
{
    std::remove_cvref_t<decltype(tup)> r;
    r.reserve(tup.size());

    for (size_t i{0}; i < tup.size(); ++i)
    {
        auto const result{std::ranges::find_end(tup, std::views::single(tup.at(i)))};

        if (result.begin() != tup.end() && std::distance(tup.begin(), result.begin()) == i)
            r.emplace_back(tup.at(i));
    }

    return r;
}

hodel::ObjectVector hodel::dedupe(ObjectVector const& tup)
{
    std::remove_cvref_t<decltype(tup)> r;
    r.reserve(tup.size());

    for (size_t i{0}; i < tup.size(); ++i)
    {
        auto const result{std::ranges::find_end(tup, std::views::single(tup.at(i)))};

        if (result.begin() != tup.end() && std::distance(tup.begin(), result.begin()) == i)
            r.emplace_back(tup.at(i));
    }

    return r;
}

hodel::ObjectsVector hodel::dedupe(ObjectsVector const& tup)
{
    std::remove_cvref_t<decltype(tup)> r;
    r.reserve(tup.size());

    for (size_t i{0}; i < tup.size(); ++i)
    {
        auto const result{std::ranges::find_end(tup, std::views::single(tup.at(i)))};

        if (result.begin() != tup.end() && std::distance(tup.begin(), result.begin()) == i)
            r.emplace_back(tup.at(i));
    }

    return r;
}

hodel::IndicesVector hodel::dedupe(IndicesVector const& tup)
{
    std::remove_cvref_t<decltype(tup)> r;
    r.reserve(tup.size());

    for (size_t i{0}; i < tup.size(); ++i)
    {
        auto const result{std::ranges::find_end(tup, std::views::single(tup.at(i)))};

        if (result.begin() != tup.end() && std::distance(tup.begin(), result.begin()) == i)
            r.emplace_back(tup.at(i));
    }

    return r;
}

hodel::Grid hodel::dedupe(Grid const& tup)
{
    std::remove_cvref_t<decltype(tup)> r;
    r.reserve(tup.size());

    for (size_t i{0}; i < tup.size(); ++i)
    {
        auto const result{std::ranges::find_end(tup, std::views::single(tup.at(i)))};

        if (result.begin() != tup.end() && std::distance(tup.begin(), result.begin()) == i)
            r.emplace_back(tup.at(i));
    }

    return r;
}

hodel::Object hodel::merge(Objects const& containers)
{
    std::remove_cvref_t<decltype(containers)>::value_type result;

    for (auto const& container : containers)
        result.insert(container.begin(), container.end());

    return result;
}

hodel::Object hodel::merge(ObjectVector const& containers)
{
    std::remove_cvref_t<decltype(containers)>::value_type result;

    for (auto const& container : containers)
        result.insert(container.begin(), container.end());

    return result;
}

hodel::Indices hodel::merge(IndicesSet const& containers)
{
    std::remove_cvref_t<decltype(containers)>::value_type result;

    for (auto const& container : containers)
        result.insert(container.begin(), container.end());

    return result;
}

hodel::IntegerTupleVector hodel::merge(IndicesVector const& containers)
{
    std::remove_cvref_t<decltype(containers)>::value_type result;

    for (auto const& container : containers)
        result.insert(container.begin(), container.end());

    return {result.begin(), result.end()};
}

hodel::IntegerVector hodel::merge(Grid const& containers)
{
    std::remove_cvref_t<decltype(containers)>::value_type result;

    for (auto const& container : containers)
        result.insert(result.end(), container.begin(), container.end());

    return result;
}

hodel::Grid hodel::merge(GridVector const& containers)
{
    std::remove_cvref_t<decltype(containers)>::value_type result;

    for (auto const& container : containers)
        result.insert(result.end(), container.begin(), container.end());

    return result;
}

hodel::GridVector hodel::merge(GridVectorVector const& containers)
{
    std::remove_cvref_t<decltype(containers)>::value_type result;

    for (auto const& container : containers)
        result.insert(result.end(), container.begin(), container.end());

    return result;
}

hodel::Objects hodel::merge(ObjectsVector const& containers)
{
    std::remove_cvref_t<decltype(containers)>::value_type result;

    for (auto const& container : containers)
        result.insert(container.begin(), container.end());

    return result;
}

hodel::Boolean hodel::contained(Boolean const& value, BooleanVector const& container)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

hodel::Boolean hodel::contained(Integer const& value, IntegerVector const& container)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

hodel::Boolean hodel::contained(Integer const& value, IntegerSet const& container)
{
    return container.contains(value);
}

hodel::Boolean hodel::contained(IntegerTuple const& value, Indices const& container)
{
    return container.contains(value);
}

hodel::Boolean hodel::contained(IntegerVector const& value, Grid const& container)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

hodel::Boolean hodel::contained(Grid const& value, GridVector const& container)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

hodel::Boolean hodel::contained(Object const& value, Objects const& container)
{
    return container.contains(value);
}

hodel::Boolean hodel::contained(Object const& value, ObjectVector const& container)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

hodel::Boolean hodel::contained(Objects const& value, ObjectsVector const& container)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

hodel::Boolean hodel::contained(Indices const& value, IndicesVector const& container)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

hodel::Boolean hodel::contained(Indices const& value, IndicesSet const& container)
{
    return container.contains(value);
}

hodel::Object hodel::product(IntegerSet const& a, Indices const& b)
{
    Object result;

    for (auto const& i : a)
    {
        for (auto const& j : b)
            result.emplace(i, j);
    }

    return result;
}

hodel::Indices hodel::product(IntegerSet const& a, IntegerSet const& b)
{
    Indices result;

    for (auto const& i : a)
    {
        for (auto const& j : b)
            result.emplace(i, j);
    }

    return result;
}

hodel::FunctionIntegerPairVector hodel::product(FunctionSet const& a, IntegerSet const& b)
{
    FunctionIntegerPairVector result;

    for (auto const& i : a)
    {
        for (auto const& j : b)
            result.emplace_back(i, j);
    }

    return result;
}

hodel::Grid hodel::move(Grid const& grid, Object const& obj, IntegerTuple const& offset)
{
    return paint(cover(grid, obj), shift(obj, offset));
}

hodel::BooleanVector hodel::intersection(BooleanVector const& a, BooleanVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::IntegerVector hodel::intersection(IntegerVector const& a, IntegerVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::Grid hodel::intersection(Grid const& a, Grid const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::GridVector hodel::intersection(GridVector const& a, GridVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::ObjectVector hodel::intersection(ObjectVector const& a, ObjectVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::ObjectsVector hodel::intersection(ObjectsVector const& a, ObjectsVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::IndicesVector hodel::intersection(IndicesVector const& a, IndicesVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::Indices hodel::intersection(Indices const& a, Indices const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::Object hodel::intersection(Object const& a, Object const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::Objects hodel::intersection(Objects const& a, Objects const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::IndicesSet hodel::intersection(IndicesSet const& a, IndicesSet const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::BooleanVector hodel::difference(BooleanVector const& a, BooleanVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::IntegerVector hodel::difference(IntegerVector const& a, IntegerVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::Grid hodel::difference(Grid const& a, Grid const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::GridVector hodel::difference(GridVector const& a, GridVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::ObjectVector hodel::difference(ObjectVector const& a, ObjectVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::ObjectsVector hodel::difference(ObjectsVector const& a, ObjectsVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::IndicesVector hodel::difference(IndicesVector const& a, IndicesVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::Indices hodel::difference(Indices const& a, Indices const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::Object hodel::difference(Object const& a, Object const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::Objects hodel::difference(Objects const& a, Objects const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::IndicesSet hodel::difference(IndicesSet const& a, IndicesSet const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v;

    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(v));

    return {v.begin(), v.end()};
}

hodel::BooleanVector hodel::combine(BooleanVector const& a, BooleanVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::IntegerVector hodel::combine(IntegerVector const& a, IntegerVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::Grid hodel::combine(Grid const& a, Grid const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::GridVector hodel::combine(GridVector const& a, GridVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::ObjectVector hodel::combine(ObjectVector const& a, ObjectVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::ObjectsVector hodel::combine(ObjectsVector const& a, ObjectsVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::IndicesVector hodel::combine(IndicesVector const& a, IndicesVector const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::Indices hodel::combine(Indices const& a, Indices const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::Object hodel::combine(Object const& a, Object const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::Objects hodel::combine(Objects const& a, Objects const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::IndicesSet hodel::combine(IndicesSet const& a, IndicesSet const& b)
{
    std::vector<std::remove_cvref_t<decltype(a)>::value_type > v{a.begin(), a.end()};

    v.insert(v.end(), b.begin(), b.end());

    return {v.begin(), v.end()};
}

hodel::GridVector hodel::mapply(aicpp::FunctionValue const& function, GridVector const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<GridVectorVector>(apply.output()));
}

hodel::IntegerTupleVector hodel::mapply_(aicpp::FunctionValue const& function, GridVector const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<IndicesVector>(apply.output()));
}

hodel::IntegerVector hodel::mapply(aicpp::FunctionValue const& function, Grid const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<std::remove_cvref_t<decltype(container)> >(apply.output()));
}

hodel::Indices hodel::mapply(aicpp::FunctionValue const& function, Objects const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<IndicesSet>(apply.output()));
}

hodel::Object hodel::mapply_(aicpp::FunctionValue const& function, Objects const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<Objects>(apply.output()));
}

hodel::Object hodel::mapply(aicpp::FunctionValue const& function, ObjectVector const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<std::remove_cvref_t<decltype(container)> >(apply.output()));
}

hodel::Objects hodel::mapply(aicpp::FunctionValue const& function, ObjectsVector const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<std::remove_cvref_t<decltype(container)> >(apply.output()));
}

hodel::IntegerTupleVector hodel::mapply(aicpp::FunctionValue const& function, IndicesVector const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<std::remove_cvref_t<decltype(container)> >(apply.output()));
}

hodel::Indices hodel::mapply(aicpp::FunctionValue const& function, IndicesSet const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<IndicesSet>(apply.output()));
}

hodel::Indices hodel::mapply(aicpp::FunctionValue const& function, Indices const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<IndicesSet>(apply.output()));
}

hodel::Object hodel::mapply_(aicpp::FunctionValue const& function, Indices const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<Objects>(apply.output()));
}

hodel::Object hodel::mapply(aicpp::FunctionValue const& function, IntegerSet const& container)
{
    aicpp::Neuron<std::remove_cvref_t<decltype(container)> > const neuron{"container", [&container] () -> std::remove_cvref_t<decltype(container)> { return container; }};
    aicpp::Connection const containerConnection{&neuron, {}};
    auto const apply{aicpp::buildConnection("apply", {function.connection, containerConnection})};

    return merge(std::any_cast<Objects>(apply.output()));
}

hodel::Grid hodel::cellwise(Grid const& a, Grid const& b, Integer const& fallback)
{
    Grid result;

    try
    {
        auto const h{a.size()};
        auto const w{a.at(0).size()};

        result = Grid(h, std::vector<Integer>(w));

        for (size_t i{0}; i < h; ++i)
        {
            for (size_t j{0}; j < w; ++j)
                result.at(i).at(j) = (a.at(i).at(j) == b.at(i).at(j)) ? a.at(i).at(j) : fallback;
        }

        return result;
    }
    catch (std::exception const&)
    {
        throw InvalidGrid{"cellwise"};
    }

    return result;
}


hodel::Boolean hodel::mostcommon(BooleanVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"mostcommon"};

    std::unordered_map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto maxCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Integer hodel::mostcommon(IntegerVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"mostcommon"};

    std::unordered_map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto maxCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Integer hodel::mostcommon(IntegerSet const& container)
{
    if (container.empty())
        throw EmptyContainer{"mostcommon"};

    std::unordered_map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto maxCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

hodel::IntegerTuple hodel::mostcommon(Indices const& container)
{
    if (container.empty())
        throw EmptyContainer{"mostcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto maxCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Object hodel::mostcommon(Objects const& container)
{
    if (container.empty())
        throw EmptyContainer{"mostcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto maxCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Object hodel::mostcommon(ObjectVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"mostcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto maxCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

hodel::IntegerVector hodel::mostcommon(Grid const& container)
{
    if (container.empty())
        throw EmptyContainer{"mostcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto maxCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Grid hodel::mostcommon(GridVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"mostcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto maxCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count > maxCount)
        {
            maxCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Boolean hodel::leastcommon(BooleanVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"leastcommon"};

    std::unordered_map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto minCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Integer hodel::leastcommon(IntegerVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"leastcommon"};

    std::unordered_map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto minCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Integer hodel::leastcommon(IntegerSet const& container)
{
    if (container.empty())
        throw EmptyContainer{"leastcommon"};

    std::unordered_map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto minCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

hodel::IntegerTuple hodel::leastcommon(Indices const& container)
{
    if (container.empty())
        throw EmptyContainer{"leastcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto minCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Object hodel::leastcommon(Objects const& container)
{
    if (container.empty())
        throw EmptyContainer{"leastcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto minCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Object hodel::leastcommon(ObjectVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"leastcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto minCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

hodel::IntegerVector hodel::leastcommon(Grid const& container)
{
    if (container.empty())
        throw EmptyContainer{"leastcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto minCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Grid hodel::leastcommon(GridVector const& container)
{
    if (container.empty())
        throw EmptyContainer{"leastcommon"};

    std::map<std::remove_cvref_t<decltype(container)>::value_type, size_t> counts;

    for (auto const& value : container)
        ++counts[value];

    auto result{*container.begin()};
    auto minCount{counts[result]};

    for (auto const& value : container)
    {
        auto const& count{counts[value]};

        if (count < minCount)
        {
            minCount = count;
            result = value;
        }
    }

    return result;
}

hodel::Grid hodel::sizefilter(Grid const& container, Integer const& n)
{
    std::remove_cvref_t<decltype(container)> result;

    for (auto const& v : container)
    {
        if (v.size() == n)
            result.insert(result.end(), v);
    }

    return result;
}

hodel::GridVector hodel::sizefilter(GridVector const& container, Integer const& n)
{
    std::remove_cvref_t<decltype(container)> result;

    for (auto const& v : container)
    {
        if (v.size() == n)
            result.insert(result.end(), v);
    }

    return result;
}

hodel::ObjectVector hodel::sizefilter(ObjectVector const& container, Integer const& n)
{
    std::remove_cvref_t<decltype(container)> result;

    for (auto const& v : container)
    {
        if (v.size() == n)
            result.insert(result.end(), v);
    }

    return result;
}

hodel::Objects hodel::sizefilter(Objects const& container, Integer const& n)
{
    std::remove_cvref_t<decltype(container)> result;

    for (auto const& v : container)
    {
        if (v.size() == n)
            result.insert(result.end(), v);
    }

    return result;
}

hodel::IndicesSet hodel::sizefilter(IndicesSet const& container, Integer const& n)
{
    std::remove_cvref_t<decltype(container)> result;

    for (auto const& v : container)
    {
        if (v.size() == n)
            result.insert(result.end(), v);
    }

    return result;
}

hodel::Indices hodel::asset(IntegerTuple const& a, IntegerTuple const& b)
{
    return {a, b};
}

hodel::IntegerSet hodel::toset(IntegerVector const& container)
{
    return {container.begin(), container.end()};
}

hodel::IndicesSet hodel::toset(IndicesVector const& container)
{
    return {container.begin(), container.end()};
}

hodel::Objects hodel::toset(ObjectVector const& container)
{
    return {container.begin(), container.end()};
}

hodel::Indices hodel::toset(IntegerTupleVector const& container)
{
    return {container.begin(), container.end()};
}
