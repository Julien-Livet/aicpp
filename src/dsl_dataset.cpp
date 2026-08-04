#include <cassert>
#include <fstream>
#include <iostream>
#include <mutex>
#include <print>
#include <random>
#include <set>
#include <thread>

#include "aicpp/Brain.h"
#include "aicpp/Connection.h"
#include "aicpp/Hodel.h"
#include "aicpp/Neuron.h"
#include "aicpp/DslSystem.h"

using namespace aicpp;

Connection buildNamedConnection(std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& variableNeuronsByOutputType,
                                std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& neuronsByOutputType,
                                size_t depth, std::type_index const& type,
                                std::vector<std::string>& names)
{
    assert(names.size());

    std::random_device rd;

    if (!depth)
    {
        std::uniform_int_distribution<size_t> dist(0, variableNeuronsByOutputType.at(type).size() - 1);
        auto const& neurons{variableNeuronsByOutputType.at(type)};

        for (auto const& n : neurons)
        {
            auto const& neuron{n.get()};

            if (neuron.name() == names.back())
            {
                names.pop_back();

                assert(neuron.inputTypes().empty());

                return Connection{neuron, {}};
            }
        }

        assert(0);
    }

    std::uniform_int_distribution<size_t> dist(0, neuronsByOutputType.at(type).size() - 1);
    auto const& neurons{neuronsByOutputType.at(type)};
    auto const originalNames{names};

    for (auto const& n : neurons)
    {
        auto const& neuron{n.get()};

        if (neuron.name() == names.back())
        {
            names.pop_back();

            std::vector<std::any> inputs;

            try
            {
                for (auto const& inputType : neuron.inputTypes())
                {
                    Connection const& inputConnection{buildNamedConnection(variableNeuronsByOutputType, neuronsByOutputType, depth - 1, inputType, names)};
                    inputs.emplace_back(inputConnection);
                }

                return Connection{neuron, inputs};
            }
            catch (std::exception const&)
            {
                names = originalNames;
            }
        }
    }

    throw std::runtime_error{"Wrong connection"};
}

Connection buildConnection(std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& variableNeuronsByOutputType,
                           std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& neuronsByOutputType,
                           size_t depth, std::type_index const& type)
{
    std::random_device rd;

    if (!depth)
    {
        std::uniform_int_distribution<size_t> dist(0, variableNeuronsByOutputType.at(type).size() - 1);
        Neuron const& neuron{variableNeuronsByOutputType.at(type).at(dist(rd))};

        assert(neuron.inputTypes().empty());

        return Connection{neuron, {}};
    }

    std::map<std::string, std::vector<std::reference_wrapper<Neuron const> > > namedNeurons;

    for (auto const& neuron : neuronsByOutputType.at(type))
        namedNeurons[neuron.get().name()].emplace_back(neuron);

    std::vector<std::vector<std::reference_wrapper<Neuron const> > > nn;
    nn.reserve(namedNeurons.size());

    for (auto const& [n, v] : namedNeurons)
        nn.emplace_back(v);

    std::shuffle(nn.begin(), nn.end(), rd);
    
    while (nn.size())
    {
        auto neurons{nn.back()};
        nn.pop_back();

        std::shuffle(neurons.begin(), neurons.end(), rd);

        while (neurons.size())
        {
            auto const neuron{neurons.back()};
            neurons.pop_back();

            try
            {
                std::vector<std::any> inputs;

                for (auto const& inputType : neuron.get().inputTypes())
                {
                    Connection const& inputConnection{buildConnection(variableNeuronsByOutputType, neuronsByOutputType, depth - 1, inputType)};
                    inputs.emplace_back(inputConnection);
                }

                return Connection{neuron.get(), inputs};
            }
            catch (std::exception const&)
            {
            }
        }
    }

    throw std::runtime_error{"Wrong connection"};
}

using Pair = std::pair<hodel::Grid, Connection>;
struct PairLess
{
    bool operator()(Pair const& x, Pair const& y) const
    {
        return x.second.hash() < y.second.hash();
    }
};

 int NUM_COLORS = 10;

hodel::Grid generateStructuredGrid(
    std::pair<size_t, size_t> minSize = {4, 4},
    std::pair<size_t, size_t> maxSize = {30, 30})
{
    std::random_device rd;

    const std::vector<std::string> kinds = {
        "stripes", "blocks", "pattern",
        "gradient", "sparse", "random"
    };

    std::uniform_int_distribution<size_t> kindDist(0, kinds.size() - 1);
    auto const kind = kinds[kindDist(rd)];

    std::uniform_int_distribution<size_t> hDist(minSize.first, maxSize.first);
    std::uniform_int_distribution<size_t> wDist(minSize.second, maxSize.second);

    auto const h = hDist(rd);
    auto const w = wDist(rd);

    hodel::Grid grid(h, std::vector<hodel::Integer>(w, 0));

    std::uniform_int_distribution<hodel::Integer> colorDist(1, NUM_COLORS - 1);
    std::uniform_int_distribution<hodel::Integer> anyColorDist(0, NUM_COLORS - 1);
    std::uniform_real_distribution<double> realDist(0.0, 1.0);

    if (kind == "stripes")
    {
        for (size_t i = 0; i < h; ++i)
        {
            if (realDist(rd) > 0.5)
            {
                auto const color = colorDist(rd);
                std::fill(grid[i].begin(), grid[i].end(), color);
            }
        }
    }
    else if (kind == "blocks")
    {
        std::uniform_int_distribution<size_t> blockCountDist(2, 5);
        auto const blockCount = blockCountDist(rd);

        std::uniform_int_distribution<size_t> rowDist(0, h - 1);
        std::uniform_int_distribution<size_t> colDist(0, w - 1);

        for (int b = 0; b < blockCount; ++b)
        {
            auto r1 = rowDist(rd);
            auto r2 = rowDist(rd);

            if (r1 > r2)
                std::swap(r1, r2);

            auto c1 = colDist(rd);
            auto c2 = colDist(rd);

            if (c1 > c2)
                std::swap(c1, c2);

            auto const color = colorDist(rd);

            for (size_t i = r1; i <= r2; ++i)
                for (size_t j = c1; j <= c2; ++j)
                    grid[i][j] = color;
        }
    }
    else if (kind == "pattern")
    {
        auto const maxBaseH = std::max(3ul, h / 2);
        auto const maxBaseW = std::max(3ul, w / 2);

        std::uniform_int_distribution<size_t> baseHDist(2, maxBaseH - 1);
        std::uniform_int_distribution<size_t> baseWDist(2, maxBaseW - 1);

        auto const baseH = baseHDist(rd);
        auto const baseW = baseWDist(rd);

        std::vector<std::vector<hodel::Integer> > base(baseH, std::vector<hodel::Integer>(baseW));

        for (int i = 0; i < baseH; ++i)
            for (int j = 0; j < baseW; ++j)
                base[i][j] = anyColorDist(rd);

        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
                grid[i][j] = base[i % baseH][j % baseW];
    }
    else if (kind == "gradient")
    {
        for (size_t i = 0; i < h; ++i)
        {
            auto const value = (i * (NUM_COLORS - 1)) / std::max(h - 1, 1ul);
            std::fill(grid[i].begin(), grid[i].end(), value);
        }
    }
    else if (kind == "random")
    {
        for (size_t i = 0; i < h; ++i)
            for (size_t j = 0; j < w; ++j)
                grid[i][j] = anyColorDist(rd);
    }
    else // sparse
    {
        std::uniform_int_distribution<size_t> countDist(3, 9);
        std::uniform_int_distribution<size_t> rowDist(0, h - 1);
        std::uniform_int_distribution<size_t> colDist(0, w - 1);

        auto const count = countDist(rd);

        for (size_t k = 0; k < count; ++k)
        {
            grid[rowDist(rd)][colDist(rd)] = colorDist(rd);
        }
    }

    return grid;
}

void checkConnections(std::map<std::string, Neuron> const& variables, std::map<std::string, Neuron> const& primitives, Neuron& iNeuron,
                      std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& variableNeuronsByOutputType,
                      std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& neuronsByOutputType)
{
    std::vector<std::vector<std::string> > allNames{
        {"apply", "identity", "cmirror", "righthalf", "I"},
        {"rot270", "hconcat", "vconcat", "crop", "canvas", "add", "size", "TWO_BY_ZERO", "FIVE", "astuple", "FIVE", "FIVE", "UP", "ORIGIN", "I", "I"},
        {"lefthalf", "downscale", "rot180", "righthalf", "rot90", "remove", "mostcommon", "subtract", "LEFT", "SIX", "I", "NEG_ONE"},
        {"replace", "I", "ONE", "multiply", "height", "hmirror", "I", "ONE"},
        {"compress", "rot90", "righthalf", "vmirror", "vconcat", "switch", "I", "divide", "ONE", "NEG_ONE", "NEG_ONE", "I"},
        {"replace", "I", "ONE", "invert", "TWO"},
        {"branch", "even", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"replace", "I", "ONE", "double", "TWO"},
        {"replace", "I", "ONE", "halve", "SIX"},
        {"branch", "flip", "even", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"branch", "equality", "TWO", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"branch", "contained", "TWO", "merge", "I", "hmirror", "I", "vmirror", "I"},
        {"tophalf", "combine", "upscale", "I", "THREE", "I"},
        {"paint", "vmirror", "I", "first", "intersection", "objects", "I", "F", "F", "T", "objects", "I", "F", "F", "T"},
        {"paint", "vmirror", "I", "first", "difference", "objects", "I", "F", "F", "T", "partition", "I"},
        {"first", "dedupe", "combine", "hsplit", "trim", "I", "FOUR", "vsplit", "I", "TWO"},
        {"first", "order", "initset", "trim", "I", "mostcommon"},
        {"replace", "I", "ONE", "last", "repeat", "TWO", "THREE"},
        {"branch", "greater", "THREE", "TWO", "hmirror", "I", "vmirror", "I"},
        {"replace", "I", "ONE", "size", "I"},
        {"merge", "combine", "hsplit", "trim", "I", "FOUR", "vsplit", "I", "TWO"},
        {"branch", "equality", "maximum", "interval", "ZERO", "TWO", "ONE", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"branch", "equality", "minimum", "interval", "ZERO", "TWO", "ONE", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"replace", "I", "ONE", "valmax", "objects", "I", "F", "F", "T", "hperiod"},
        {"replace", "I", "ONE", "valmin", "objects", "I", "F", "F", "T", "hperiod"},
        {"argmax", "combine", "hsplit", "trim", "I", "FOUR", "vsplit", "I", "TWO", "size"},
        {"argmin", "combine", "hsplit", "trim", "I", "FOUR", "vsplit", "I", "TWO", "size"},
        {"first", "order", "initset", "trim", "I", "mostcommon"},
        {"first", "order", "initset", "trim", "I", "leastcommon"},
        {"first", "initset", "trim", "I"},
        {"branch", "both", "T", "F", "hmirror", "I", "vmirror", "I"},
        {"branch", "either", "T", "F", "hmirror", "I", "vmirror", "I"},
        {"replace", "I", "ONE", "increment", "THREE"},
        {"replace", "I", "ONE", "decrement", "THREE"},
        {"replace", "I", "ONE", "crement", "THREE"},
        {"replace", "I", "TWO", "multiply", "NEG_ONE", "sign", "NEG_ONE"},
        {"replace", "I", "ONE", "first", "toivec", "THREE"},
        {"replace", "I", "ONE", "last", "tojvec", "FOUR"},
        {"replace", "I", "TWO", "first", "sfilter", "interval", "invert", "SIX", "SIX", "ONE", "positive"},/*
        //{"mfilter"}, //cf. below
        //{"extract"},
        {"trim", "trim", "vconcat", "dmirror", "apply", "last", "canvas", "mostcolor", "I", "UP", "I"},
        {"vupscale", "bottomhalf", "vconcat", "remove", "invert", "RIGHT", "dedupe", "interval", "last", "UNITY", "THREE", "ONE", "I", "NINE"},
        {"righthalf", "subgrid", "dneighbors", "astuple", "first", "TWO_BY_ZERO", "THREE", "I"},
        {"canvas", "divide", "FOUR", "branch", "greater", "index", "replace", "hconcat", "dmirror", "I", "I", "SEVEN", "EIGHT", "TWO_BY_ZERO", "EIGHT", "ONE", "THREE_BY_THREE", "TWO_BY_TWO"},
        {"subgrid", "branch", "F", "compose", "last", "argmin", "lefthalf", "I", "I"},
        {"cmirror", "rot270", "lefthalf", "remove", "chain", "first", "fork", "other", "I"},
        {"upscale", "hmirror", "branch", "T", "lefthalf", "I", "matcher", "leastcommon", "centerofmass", "connect", "UP", "TWO_BY_TWO", "SIX"},
        {"cmirror", "rot180", "remove", "fork", "extract", "first", "rbind", "I"},
        {"move", "tophalf", "I", "prapply", "lbind", "crop", "rot180", "canvas", "width", "I", "ZERO_BY_TWO", "DOWN", "UNITY", "DOWN", "DOWN_LEFT"},
        {"remove", "power", "lbind", "FIVE", "hconcat", "branch", "flip", "branch", "contained", "asobject", "I", "NEG_UNITY", "UP_RIGHT", "RIGHT", "T", "I", "I"},
        {"righthalf", "remove", "fork", "mostcommon", "power", "matcher", "rot90", "I"},
        {"tophalf", "rot270", "vconcat", "switch", "upscale", "apply", "extract", "colorfilter", "fgpartition", "I", "TEN", "NEG_ONE", "ONE", "SEVEN", "I"},
        {"lefthalf", "vupscale", "canvas", "mostcolor", "compress", "I", "TWO_BY_TWO", "EIGHT"},
        {"upscale", "canvas", "other", "other", "normalize", "neighbors", "sign", "NEG_UNITY", "leastcolor", "I", "FOUR", "TWO_BY_TWO", "SEVEN"},
        {"rot270", "upscale", "I", "height", "backdrop", "connect", "NEG_UNITY", "ORIGIN"},
        {"compress", "vupscale", "dmirror", "I", "width", "neighbors", "DOWN"},
        {"canvas", "multiply", "double", "center", "neighbors", "THREE_BY_THREE", "sign", "RIGHT", "shape", "asobject", "I"},
        {"dmirror", "remove", "flip", "portrait", "hmirror", "rot90", "cmirror", "cellwise", "I", "I", "ZERO", "I"},
        {"rot270", "canvas", "colorcount", "prapply", "first", "connect", "astuple", "width", "I", "FOUR", "UP_RIGHT", "UP_RIGHT", "TWO", "TWO_BY_TWO"},
        {"canvas", "width", "asindices", "bottomhalf", "crop", "I", "UP_RIGHT", "UNITY", "TWO_BY_TWO"},
        {"lefthalf", "subgrid", "box", "toindices", "ofcolor", "rot180", "I", "EIGHT", "I"},
        {"switch", "rot90", "bottomhalf", "vconcat", "identity", "ulcorner", "neighbors", "DOWN_LEFT", "I", "FIVE", "SIX"},
        {"trim", "remove", "urcorner", "asindices", "I", "I"},
        {"rot180", "switch", "subgrid", "backdrop", "vfrontier", "llcorner", "asindices", "vconcat", "I", "I", "I", "SEVEN", "NEG_TWO"},
        {"rot270", "rot180", "canvas", "identity", "F", "lrcorner", "hmirror", "I"},
        {"vupscale", "crop", "rot270", "rot180", "hconcat", "vconcat", "downscale", "vmirror", "I", "THREE", "I", "I", "TWO_BY_ZERO", "DOWN_LEFT", "SEVEN"},
        {"dmirror", "toindices", "hmirror", "I"},
        {"subgrid", "recolor", "ZERO", "vfrontier", "increment", "multiply", "TWO", "TWO_BY_TWO", "I"},
        {"subgrid", "shift", "inbox", "outbox", "toobject", "asindices", "cmirror", "I", "I", "ORIGIN", "I"},
        {"upscale", "rot90", "subgrid", "initset", "tojvec", "NEG_TWO", "subgrid", "dneighbors", "TWO_BY_TWO", "I", "EIGHT"},
        {"underfill", "hmirror", "I", "FOUR", "corners", "ineighbors", "DOWN_LEFT"},
        {"trim", "compress", "bottomhalf", "cover", "I", "box", "dneighbors", "ORIGIN"},
        {"canvas", "uppermost", "hfrontier", "combine", "THREE_BY_THREE", "shape", "replace", "I", "FIVE", "SIX", "TWO_BY_TWO"},
        {"vupscale", "identity", "hmirror", "dneighbors", "THREE_BY_THREE", "lowermost", "vfrontier", "shape", "I"},
        {"righthalf", "canvas", "leftmost", "shift", "ofcolor", "I", "TWO", "UP_RIGHT", "TWO_BY_TWO"},
        {"vupscale", "I", "rightmost", "neighbors", "THREE_BY_THREE"},
        {"rot180", "cmirror", "branch", "square", "vfrontier", "combine", "UP_RIGHT", "ZERO_BY_TWO", "RIGHT", "I"},
        {"upscale", "righthalf", "vmirror", "tophalf", "branch", "vline", "other", "hsplit", "I", "EIGHT", "TWO_BY_TWO", "I", "ONE", "SIX"},
        {"replace", "vupscale", "switch", "branch", "hline", "vfrontier", "DOWN", "UP", "I", "FOUR", "FIVE", "NINE", "FOUR", "TEN"},
        {"bottomhalf", "branch", "hmatching", "ineighbors", "DOWN", "toindices", "delta", "delta", "hfrontier", "RIGHT", "SIX", "I"},
        {"tophalf", "branch", "vmatching", "ineighbors", "TWO_BY_TWO", "hfrontier", "DOWN", "lefthalf", "rot270", "downscale", "I", "TWO", "NEG_ONE"},
        {"merge", "canvas", "subtract", "manhattan", "vfrontier", "NEG_UNITY", "dneighbors", "subtract", "index", "I", "THREE_BY_THREE", "TWO_BY_ZERO", "TWO_BY_TWO", "TWO_BY_TWO"},
        {"branch", "adjacent", "hfrontier", "UP", "inbox", "recolor", "EIGHT", "dmirror", "neighbors", "TWO_BY_ZERO", "NEG_ONE", "tophalf", "I"},
        {"rot90", "vconcat", "trim", "branch", "bordering", "connect", "DOWN_LEFT", "DOWN", "I", "DOWN_LEFT", "UP_RIGHT", "I"},
        {"vconcat", "subgrid", "hfrontier", "centerofmass", "hmirror", "rot180", "I", "I", "I"},
        {"rot90", "switch", "combine", "initset", "UNITY", "palette", "upscale", "upscale", "I", "NEG_ONE", "NINE", "ZERO", "NEG_ONE"},
        {"hupscale", "remove", "numcolors", "rot180", "crop", "branch", "F", "SIX", "I", "RIGHT", "LEFT", "I", "TEN"},
        {"replace", "cmirror", "delta", "ofcolor", "I", "SEVEN", "ONE", "EIGHT"},
        {"hconcat", "upscale", "subgrid", "cmirror", "toobject", "vfrontier", "ORIGIN", "cmirror", "I", "I", "FIVE", "I"},
        {"move", "lefthalf", "hupscale", "I", "SIX", "asobject", "compress", "lefthalf", "hmirror", "I", "TWO_BY_ZERO"},
        {"vupscale", "rot90", "rot90", "vconcat", "I", "I", "EIGHT"},
        {"rot180", "switch", "I", "NEG_TWO", "NEG_ONE"},
        {"rot270", "subgrid", "hfrontier", "RIGHT", "I"},
        {"hconcat", "subgrid", "neighbors", "mostcommon", "I", "hmirror", "vupscale", "rot180", "I", "SIX", "I"},
        {"vmirror", "trim", "cellwise", "I", "hupscale", "other", "initset", "righthalf", "branch", "F", "UNITY", "I", "ORIGIN", "NINE", "FOUR"},
        {"dmirror", "hupscale", "downscale", "lefthalf", "vmirror", "I", "EIGHT", "FIVE"},
        {"vmirror", "hconcat", "combine", "cellwise", "hconcat", "hupscale", "cmirror", "bottomhalf", "I", "NEG_TWO", "I", "I", "SEVEN", "ORIGIN", "I"},
        {"rot270", "hupscale", "cmirror", "I", "EIGHT"},
        {"compress", "vupscale", "vconcat", "rot180", "I", "I", "SIX"},
        {"hupscale", "I", "increment", "FIVE"},
        {"downscale", "hconcat", "rot270", "dmirror", "I", "I", "THREE"},
        {"rot90", "hconcat", "replace", "I", "ZERO", "TWO", "I"},
        {"vmirror", "rot180", "replace", "vconcat", "canvas", "NEG_ONE", "RIGHT", "I", "ONE", "NEG_ONE"},
        {"downscale", "subgrid", "hmirror", "identity", "vconcat", "leastcommon", "canvas", "add", "FIVE", "ORIGIN", "THREE_BY_THREE", "I", "I", "SIX"},
        {"leastcommon", "hsplit", "replace", "rot90", "downscale", "I", "TWO", "TEN", "TWO", "THREE"},
        {"crop", "cellwise", "branch", "T", "hupscale", "identity", "vsplit", "downscale", "vconcat", "I", "I", "SIX", "TWO", "THREE", "NINE", "I", "EIGHT", "ZERO_BY_TWO", "THREE_BY_THREE"},
        {"vupscale", "dmirror", "bottomhalf", "dmirror", "cellwise", "compress", "tophalf", "switch", "I", "TWO", "EIGHT", "I", "EIGHT", "SIX"},
        {"replace", "rot270", "downscale", "cmirror", "rot90", "I", "SEVEN", "NEG_ONE", "SEVEN"},
        {"rot90", "last", "vsplit", "switch", "I", "THREE", "NINE", "TWO"},
        {"canvas", "decrement", "TEN", "centerofmass", "identity", "I"},
        {"vconcat", "vmirror", "replace", "I", "halve", "position", "vfrontier", "DOWN_LEFT", "vfrontier", "TWO_BY_ZERO", "ZERO", "I"},
        {"hupscale", "switch", "subgrid", "ofcolor", "sfilter", "dmirror", "rot270", "I", "mostcommon", "index", "I", "RIGHT", "I", "EIGHT", "TWO", "SIX"},
        {"dmirror", "hconcat", "canvas", "increment", "UP_RIGHT", "DOWN_LEFT", "I"},
        {"hconcat", "subgrid", "corners", "box", "ineighbors", "divide", "TEN", "TWO_BY_TWO", "I", "I"},
        {"hconcat", "vmirror", "connect", "ZERO_BY_TWO", "invert", "merge", "switch", "I", "NEG_ONE", "THREE", "I"},
        {"cmirror", "tophalf", "trim", "rot180", "vconcat", "righthalf", "hconcat", "dmirror", "I", "I", "I"},
        {"move", "hmirror", "tophalf", "lefthalf", "I", "upscale", "cmirror", "rot270", "I", "NEG_ONE", "ORIGIN"},
        {"dmirror", "compress", "bottomhalf", "remove", "first", "TWO_BY_ZERO", "switch", "I", "EIGHT", "SIX"},
        {"lefthalf", "hupscale", "righthalf", "I", "ONE"},
        {"cmirror", "cellwise", "righthalf", "I", "I", "EIGHT"},
        {"hupscale", "I", "size", "vfrontier", "DOWN_LEFT"},
        {"rot270", "lefthalf", "replace", "subgrid", "toindices", "hfrontier", "DOWN_LEFT", "I", "SIX", "THREE"},
        {"subgrid", "shoot", "astuple", "minimum", "first", "I", "EIGHT", "THREE_BY_THREE", "I"},
        {"hmirror", "replace", "vupscale", "compress", "trim", "rot270", "vupscale", "I", "SIX", "TWO", "FOUR", "ONE"}*/};

    std::vector<Connection> connections;
/*
    {
        Connection const width{variables.at("width"), {}};
        Connection const greater{variables.at("greater"), {}};
        Connection const ONE{variables.at("ONE"), {}};
        Connection const rbind{primitives.at("rbind5"), {greater, ONE}};
        Connection const compose{primitives.at("compose"), {rbind, width}};
        Connection const I{iNeuron, {}};
        Connection const F{variables.at("F"), {}};
        Connection const T{variables.at("T"), {}};
        Connection const objects{primitives.at("objects"), {I, F, F, T}};
        Connection const mfilter{primitives.at("mfilter42"), {objects, compose}};
        Connection const hmirror{primitives.at("hmirror0"), {I}};
        Connection const paint{primitives.at("paint"), {hmirror, mfilter}};

        auto const input{generateStructuredGrid({30, 30}, {30, 30})}; //TODO: to remove
        iNeuron.function() = [input] (std::vector<std::any> const&) -> std::any { return input; }; //TODO: to remove
        auto const o = mfilter.output(); //TODO: to remove

        connections.emplace_back(paint);
    }
*/
    for (auto names : allNames)
    {
        std::reverse(names.begin(), names.end());

        try
        {
            connections.emplace_back(buildNamedConnection(variableNeuronsByOutputType, neuronsByOutputType, static_cast<size_t>(-1), typeid(hodel::Grid), names));
        }
        catch (std::exception const&)
        {
            std::reverse(names.begin(), names.end());

            std::cout << "Unknown symbol(s): ";

            for (auto const& name : names)
                std::cout << name << ", ";

            std::cout << std::endl;
        }
    }

    for (auto& connection : connections)
    {
        assert(connection.neuron().outputType() == typeid(hodel::Grid));

        std::any output;
        auto const input{generateStructuredGrid({30, 30}, {30, 30})};

        iNeuron.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };
/*
        try
        {*/
            output = connection.output();

            if (output.has_value())
            {
                auto const grid{std::any_cast<hodel::Grid>(output)};
                bool add{true};

                if (grid == input)
                    add = false;

                auto const minReducer = [] (hodel::Integer a, hodel::Integer b) { return std::min(a, b); };
                auto const minTransformer = [] (auto const& row) {
                    return row.empty()
                        ? std::numeric_limits<hodel::Integer>::max()
                        : *std::min_element(row.begin(), row.end());
                };
                auto const maxReducer = [] (hodel::Integer a, hodel::Integer b) { return std::max(a, b); };
                auto const maxTransformer = [] (auto const& row) {
                    return row.empty()
                        ? std::numeric_limits<hodel::Integer>::min()
                        : *std::max_element(row.begin(), row.end());
                };

                auto const min = std::transform_reduce(
                    grid.begin(), grid.end(),
                    std::numeric_limits<hodel::Integer>::max(),
                    minReducer,
                    minTransformer);
                auto const max = std::transform_reduce(
                    grid.begin(), grid.end(),
                    std::numeric_limits<hodel::Integer>::min(),
                    maxReducer,
                    maxTransformer);

                if (min < 0 || max > 9)
                    add = false;

                auto const program{connection.string()};

                if (!program.contains("(I)") && !program.contains("(I, ") && !program.contains(", I,") && !program.contains(", I)"))
                    add = false;

                if (!add)
                    std::cout << "Failed to add: " << connection.string() << std::endl;
            }/*
        }
        catch (std::exception const&)
        {
            std::cout << "Failed connection: " << connection.string() << std::endl;
        }*/
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <depth> <count>" << std::endl;

        return 1;
    }

    size_t const depth{static_cast<size_t>(std::stoi(argv[1]))};
    size_t const count{static_cast<size_t>(std::stoi(argv[2]))};

    auto const variables{dslVariableNeurons()};
    auto const primitives{dslPrimitiveNeurons()};

    std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > variableNeuronsByOutputType;

    for (auto const& variable : variables)
        variableNeuronsByOutputType[variable.second.outputType()].emplace_back(variable.second);

    Neuron iNeuron{"I", [] (std::vector<std::any> const&) -> std::any { return std::any{}; }, std::vector<std::type_index>{}, typeid(hodel::Grid)};

    variableNeuronsByOutputType[iNeuron.outputType()].emplace_back(iNeuron);

    std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > primitiveNeuronsByOutputType;

    for (auto const& primitive : primitives)
        primitiveNeuronsByOutputType[primitive.second.outputType()].emplace_back(primitive.second);

    std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > neuronsByOutputType{variableNeuronsByOutputType};

    for (auto const& [i, v] : primitiveNeuronsByOutputType)
        neuronsByOutputType[i].insert(neuronsByOutputType[i].end(), v.begin(), v.end());
/*
    checkConnections(variables, primitives, iNeuron, variableNeuronsByOutputType, neuronsByOutputType);

    return 0;
*/
    std::set<Pair, PairLess> pairs;
    std::mutex mutex;

    auto const addConnection = [&mutex, &pairs, &variableNeuronsByOutputType, &neuronsByOutputType, &iNeuron, depth, count] () {
        if (pairs.size() >= count)
            return;

        try
        {
            auto const connection{buildConnection(variableNeuronsByOutputType, neuronsByOutputType, depth, typeid(hodel::Grid))};

            assert(connection.neuron().outputType() == typeid(hodel::Grid));

            std::any output;
            auto const input{generateStructuredGrid()};

            {
                std::lock_guard<std::mutex> lock(mutex);

                iNeuron.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };

                output = connection.output();
            }

            if (output.has_value())
            {
                auto const grid{std::any_cast<hodel::Grid>(output)};
                bool add{true};

                if (grid == input)
                    add = false;

                auto const minReducer = [] (hodel::Integer a, hodel::Integer b) { return std::min(a, b); };
                auto const minTransformer = [] (auto const& row) {
                    return row.empty()
                        ? std::numeric_limits<hodel::Integer>::max()
                        : *std::min_element(row.begin(), row.end());
                };
                auto const maxReducer = [] (hodel::Integer a, hodel::Integer b) { return std::max(a, b); };
                auto const maxTransformer = [] (auto const& row) {
                    return row.empty()
                        ? std::numeric_limits<hodel::Integer>::min()
                        : *std::max_element(row.begin(), row.end());
                };

                auto const min = std::transform_reduce(
                    grid.begin(), grid.end(),
                    std::numeric_limits<hodel::Integer>::max(),
                    minReducer,
                    minTransformer);
                auto const max = std::transform_reduce(
                    grid.begin(), grid.end(),
                    std::numeric_limits<hodel::Integer>::min(),
                    maxReducer,
                    maxTransformer);

                if (min < 0 || max > 9)
                    add = false;

                auto const program{connection.string()};

                if (!program.contains("(I)") && !program.contains("(I, ") && !program.contains(", I,") && !program.contains(", I)"))
                    add = false;

                if (add)
                {
                    std::lock_guard<std::mutex> lock(mutex);

                    pairs.emplace(input, std::move(connection));
                }
            }
        }
        catch (std::exception const&)
        {
        }
    };

    std::vector<std::thread> threads;

    while (pairs.size() < count)
    {
        if (threads.size() == std::thread::hardware_concurrency())
        {
            for (auto& thread : threads)
                thread.join();

            threads.clear();
        }

        threads.emplace_back(addConnection);
    }

    for (auto& thread : threads)
        thread.join();

    std::set<std::string> strings;

    for (auto const& pair : pairs)
        strings.emplace(pair.second.string());

    for (auto const& s : strings)
        std::println("{0}", s);

    std::vector<std::reference_wrapper<Neuron const> > neurons;

    for (auto const& [type, v] : variableNeuronsByOutputType)
        neurons.insert(neurons.end(), v.begin(), v.end());

    for (auto const& [type, v] : primitiveNeuronsByOutputType)
        neurons.insert(neurons.end(), v.begin(), v.end());

    Brain brain{neurons};

    for (auto const& pair : pairs)
        brain.addConnection(pair.second);

    {
        auto const value{brain.toJson()};

        std::ofstream ofs{"dsl_dataset_connections.json"};

        ofs << boost::json::serialize(value);
    }

    {
        std::vector<hodel::Grid> grids;

        for (auto const& connection : brain.connections())
        {
            for (auto const& pair : pairs)
            {
                if (pair.second == connection)
                {
                    grids.emplace_back(pair.first);
                    break;
                }
            }
        }        

        boost::json::object obj;
        boost::json::array json_grids;

        for (auto const& grid : grids)
        {
            boost::json::array json_grid;

            for (auto const& row : grid)
            {
                boost::json::array json_row;

                for (auto const& val : row)
                    json_row.push_back(val);

                json_grid.push_back(json_row);
            }

            json_grids.push_back(json_grid);
        }

        obj["grids"] = json_grids;
        boost::json::value const value = obj;

        std::ofstream ofs{"dsl_dataset_grids.json"};

        ofs << boost::json::serialize(value);
    }

    return 0;
}
