#include <cassert>
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <print>
#include <random>
#include <set>
#include <thread>

#include "aicpp/Brain.h"
#include "aicpp/Connection.h"
#include "aicpp/Hodel.h"
#include "aicpp/Neuron.h"
#include "aicpp/DslSystem.h"

size_t constexpr gridTrials = 100;

using namespace aicpp;

Connection buildNamedConnection(std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& variableNeuronsByOutputType,
                                std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > const& neuronsByOutputType,
                                std::type_index const& type,
                                std::vector<std::string>& names)
{
    assert(names.size());

    std::random_device rd;
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
                    Connection const& inputConnection{buildNamedConnection(variableNeuronsByOutputType, neuronsByOutputType, inputType, names)};
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

    if (type != typeid(hodel::Callable) && namedNeurons.contains("identity"))
        namedNeurons.erase("identity");

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
                break; //TODO: to remove?
            }
        }

        break; //TODO: to remove?
    }

    throw std::runtime_error{"Wrong connection"};
}

using Pair = std::pair<hodel::GridType, Connection>;

struct PairLess
{
    bool operator()(Pair const& x, Pair const& y) const
    {
        return x.second.hash() < y.second.hash();
    }
};

int constexpr NUM_COLORS = 10;

hodel::GridType generateStructuredGrid(
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

    hodel::GridType grid(h, std::vector<hodel::IntegerType>(w, 0));

    std::uniform_int_distribution<hodel::IntegerType> colorDist(1, NUM_COLORS - 1);
    std::uniform_int_distribution<hodel::IntegerType> anyColorDist(0, NUM_COLORS - 1);
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

        std::vector<std::vector<hodel::IntegerType> > base(baseH, std::vector<hodel::IntegerType>(baseW));

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
        {"cmirror", "identity", "vmirror", "I"},
        {"rot270", "hconcat", "vconcat", "crop", "canvas", "add", "size", "TWO_BY_ZERO", "FIVE", "astuple", "FIVE", "FIVE", "UP", "ORIGIN", "I", "I"},
        {"replace", "I", "ONE", "subtract", "NINE", "FOUR"},
        {"replace", "I", "ONE", "multiply", "TWO", "THREE"},
        {"compress", "rot90", "righthalf", "vmirror", "vconcat", "switch", "I", "divide", "ONE", "NEG_ONE", "NEG_ONE", "I"},
        {"replace", "I", "ONE", "multiply", "NEG_ONE", "invert", "TWO"},
        {"branch", "even", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"replace", "I", "ONE", "double", "TWO"},
        {"replace", "I", "ONE", "halve", "SIX"},
        {"branch", "flip", "even", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"branch", "equality", "TWO", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"mostcommon", "order", "initset", "bottomhalf", "I", "contained"},
        {"tophalf", "combine", "upscale", "I", "THREE", "I"},
        {"paint", "vmirror", "I", "first", "intersection", "objects", "I", "F", "F", "T", "objects", "I", "F", "F", "T"},
        {"paint", "vmirror", "I", "first", "difference", "objects", "I", "F", "F", "T", "partition", "I"},
        {"last", "dedupe", "insert", "trim", "I", "insert", "cmirror", "I", "initset", "trim", "I"},
        {"first", "order", "initset", "trim", "I", "mostcommon"},
        {"replace", "I", "ONE", "last", "repeat", "TWO", "THREE"},
        {"branch", "greater", "THREE", "TWO", "hmirror", "I", "vmirror", "I"},
        {"replace", "I", "ONE", "divide", "size", "I", "SIX"},
        {"bottomhalf", "merge", "insert", "cmirror", "I", "initset", "I"},
        {"branch", "equality", "maximum", "interval", "ZERO", "TWO", "ONE", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"branch", "equality", "minimum", "interval", "ZERO", "TWO", "ONE", "ZERO", "hmirror", "I", "vmirror", "I"},
        {"replace", "I", "ONE", "valmax", "objects", "I", "F", "F", "T", "hperiod"},
        {"replace", "I", "ONE", "valmin", "objects", "I", "F", "F", "T", "hperiod"},
        {"paint", "cmirror", "I", "argmax", "objects", "I", "F", "F", "T", "size"},
        {"paint", "cmirror", "I", "argmin", "objects", "I", "F", "F", "T", "size"},
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
        {"replace", "I", "TWO", "first", "sfilter", "interval", "invert", "SIX", "SIX", "ONE", "positive"},
        //{"mfilter"}, //cf. below
        //{"extract"}, //OK
        {"paint", "vmirror", "I", "first", "totuple", "objects", "I", "F", "F", "T"},
        {"first", "remove", "trim", "I", "insert", "trim", "I", "insert", "cmirror", "I", "initset", "trim", "I"},
        {"other", "insert", "trim", "I", "insert", "cmirror", "I", "initset", "cmirror", "I", "trim", "I"},
        {"crop", "I", "astuple", "FOUR", "FIVE", "astuple", "SIX", "SEVEN"},
        //{"product"},
        //{"chain"}, //OK
        //{"matcher"}, //cf. below
        //{"lbind"}, //cf. below
        //{"power"}, //cf. below
        //{"fork"}, //OK
        {"crop", "I", "astuple", "ZERO", "ZERO", "astuple", "halve", "halve", "last", "apply", "size", "objects", "vmirror", "I", "F", "F", "T", "halve", "halve", "first", "apply", "size", "objects", "vmirror", "I", "F", "F", "T"},
        {"first", "rapply", "insert", "trim", "initset", "hmirror", "I"},
        //{"papply"}, //cf. below
        //{"mpapply"}, //cf. below
        //{"prapply"}, //cf. below
        {"righthalf", "subgrid", "dneighbors", "astuple", "first", "TWO_BY_ZERO", "THREE", "I"},
        {"replace", "I", "leastcolor", "I", "mostcolor", "I"},
        {"crop", "I", "astuple", "divide", "height", "I", "TWO", "divide", "width", "I", "TWO", "astuple", "FOUR", "FIVE"},
        {"crop", "I", "divide", "shape", "I", "TWO", "astuple", "FOUR", "FIVE"},
        {"branch", "portrait", "I", "hmirror", "I", "cmirror", "I"},
        {"replace", "I", "mostcolor", "I", "colorcount", "I", "leastcolor", "I"},
        {"underpaint", "cmirror", "I", "first", "colorfilter", "objects", "I", "T", "F", "F", "mostcolor", "I"},
        {"paint", "dmirror", "I", "toobject", "asindices", "cmirror", "I", "cmirror", "I"},
        {"underpaint", "hmirror", "I", "toobject", "ofcolor", "I", "mostcolor", "I", "I"},
        {"paint", "vmirror", "I", "toobject", "toindices", "asobject", "vmirror", "I", "vmirror", "I"},
        {"underpaint", "cmirror", "I", "recolor", "leastcolor", "I", "first", "colorfilter", "objects", "I", "T", "F", "F", "mostcolor", "I"},
        {"paint", "dmirror", "I", "recolor", "leastcolor", "I", "shift", "first", "colorfilter", "objects", "I", "T", "F", "F", "mostcolor", "I", "UNITY"},
        {"underpaint", "hmirror", "I", "toobject", "normalize", "asindices", "trim", "I", "I"},
        {"paint", "vmirror", "I", "toobject", "dneighbors", "center", "asindices", "I", "I"},
        {"underpaint", "cmirror", "I", "toobject", "ineighbors", "center", "asindices", "I", "I"},
        {"paint", "dmirror", "I", "toobject", "neighbors", "center", "asindices", "I", "I"},
        {"underpaint", "hmirror", "I", "first", "fgpartition", "I"},
        {"branch", "square", "I", "hmirror", "I", "cmirror", "I"},
        //{"vline"}, //cf. below
        //{"hline"}, //cf. below
        //{"hmatching"}, //cf. below
        //{"vmatching"}, //cf. below
        //{"manhattan"}, OK
        //{"adjacent"}, //cf. below
        //{"bordering"}, //cf. below
        {"paint", "I", "toobject", "shoot", "centerofmass", "first", "objects", "I", "F", "F", "T", "astuple", "TWO", "TWO", "cmirror", "I"},
        //{"palette"}, OK
        //{"numcolors"}, OK
        {"replace", "I", "color", "first", "objects", "I", "F", "F", "T", "color", "last", "objects", "I", "F", "F", "T"},
        //{"toobject"}, OK
        //{"asobject"}, OK
        {"first", "hsplit", "cmirror", "I", "THREE"},
        {"first", "vsplit", "cmirror", "I", "THREE"},
        {"combine", "I", "canvas", "TWO", "astuple", "FOUR", "FIVE"},
        {"move", "I", "first", "objects", "I", "F", "F", "T", "astuple", "TWO", "THREE"},
        //{"gravitate"}, //cf. below
    };

    std::vector<std::pair<Connection, std::optional<hodel::GridType> > > programs;

    //rbind
    {
        Connection const width{variables.at("width"), {}};
        Connection const greater{variables.at("greater"), {}};
        Connection const ONE{variables.at("ONE"), {}};
        Connection const rbind{primitives.at("rbind8"), {greater, ONE}};
        Connection const compose{primitives.at("compose0"), {rbind, width}};
        Connection const I{iNeuron, {}};
        Connection const F{variables.at("F"), {}};
        Connection const T{variables.at("T"), {}};
        Connection const objects{primitives.at("objects0"), {I, F, F, T}};
        Connection const mfilter{primitives.at("mfilter4"), {objects, compose}};
        Connection const hmirror{primitives.at("hmirror0"), {I}};
        Connection const paint{primitives.at("paint0"), {hmirror, mfilter}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{paint, {}});
    }

    //lbind
    {
        Connection const width{variables.at("width"), {}};
        Connection const greater{variables.at("greater"), {}};
        Connection const ONE{variables.at("ONE"), {}};
        Connection const lbind{primitives.at("lbind8"), {greater, ONE}};
        Connection const compose{primitives.at("compose0"), {lbind, width}};
        Connection const I{iNeuron, {}};
        Connection const F{variables.at("F"), {}};
        Connection const T{variables.at("T"), {}};
        Connection const objects{primitives.at("objects0"), {I, F, F, T}};
        Connection const mfilter{primitives.at("mfilter4"), {objects, compose}};
        Connection const hmirror{primitives.at("hmirror0"), {I}};
        Connection const paint{primitives.at("paint0"), {hmirror, mfilter}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{paint, {}});
    }

    //matcher: 39a8645d
    {
        Connection const I{iNeuron, {}};
        Connection const F{variables.at("F"), {}};
        Connection const T{variables.at("T"), {}};
        Connection const objects{primitives.at("objects0"), {I, T, T, T}};
        Connection const totuple{primitives.at("totuple4"), {objects}};
        Connection const color{variables.at("color"), {}};
        Connection const apply{primitives.at("apply6"), {color, totuple}};
        Connection const mostcommon{primitives.at("mostcommon5"), {apply}};
        Connection const matcher{primitives.at("matcher8"), {color, mostcommon}};
        Connection const extract{primitives.at("extract14"), {objects, matcher}};
        Connection const subgrid{primitives.at("subgrid1"), {extract, I}};

        hodel::GridType const grid{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 0, 8, 0},
                                   {0, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 8, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 8, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 8, 0, 8, 0, 0, 0, 2, 0, 2, 0, 0},
                                   {0, 0, 0, 0, 8, 0, 0, 0, 0, 2, 0, 2, 0, 0},
                                   {0, 0, 0, 8, 0, 8, 0, 0, 0, 0, 2, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
                        
        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{subgrid, grid});
    }

    //power: 1f876c06
    {
        Connection const I{iNeuron, {}};
        Connection const fgpartition{primitives.at("fgpartition0"), {I}};
        Connection const last{variables.at("last"), {}};
        Connection const first{variables.at("first"), {}};
        Connection const compose{primitives.at("compose0"), {last, first}};
        Connection const TWO{variables.at("TWO"), {}};
        Connection const power{primitives.at("power0"), {last, TWO}};
        Connection const connect{variables.at("connect"), {}};
        Connection const fork1{primitives.at("fork0"), {connect, compose, power}};
        Connection const recolor{variables.at("recolor"), {}};
        Connection const color{variables.at("color"), {}};
        Connection const fork2{primitives.at("fork0"), {recolor, color, fork1}};
        Connection const mapply{primitives.at("mapply2"), {fork2, fgpartition}};
        Connection const paint{primitives.at("paint0"), {I, mapply}};

        hodel::GridType const grid{{0, 0, 2, 0, 0, 6, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
                                   {0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 4, 0, 0}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{paint, grid});
    }

    //papply: 73251a56
    {
        Connection const I{iNeuron, {}};
        Connection const dmirror{primitives.at("dmirror0"), {I}};
        Connection const pair{variables.at("pair"), {}};
        Connection const papply{primitives.at("papply28"), {pair, I, dmirror}};
        Connection const maximum{variables.at("maximum"), {}};
        Connection const apply{variables.at("apply"), {}};
        Connection const lbind{primitives.at("lbind1"), {apply, maximum}};
        Connection const apply1{primitives.at("apply9"), {lbind, papply}};
        Connection const mostcolor{primitives.at("mostcolor0"), {apply1}};
        Connection const ZERO{variables.at("ZERO"), {}};
        Connection const replace{primitives.at("replace0"), {apply1, ZERO, mostcolor}};
        Connection const ORIGIN{variables.at("ORIGIN"), {}};
        Connection const UNITY{variables.at("UNITY"), {}};
        Connection const index{primitives.at("index0"), {replace, UNITY}};
        Connection const shoot{primitives.at("shoot0"), {ORIGIN, UNITY}};
        Connection const fill{primitives.at("fill0"), {replace, index, shoot}};

        hodel::GridType const grid{{4, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 1, 1, 2, 2, 3, 3, 4},
                                   {3, 4, 3, 3, 4, 4, 4, 5, 5, 5, 0, 0, 6, 7, 7, 7, 8, 8, 8, 9, 9},
                                   {4, 3, 4, 3, 3, 3, 4, 4, 4, 4, 0, 0, 5, 5, 6, 6, 6, 6, 7, 7, 7},
                                   {4, 3, 3, 4, 3, 3, 3, 3, 4, 4, 0, 0, 4, 5, 5, 5, 5, 5, 6, 6, 6},
                                   {5, 4, 3, 3, 4, 3, 3, 3, 3, 3, 0, 0, 4, 4, 4, 4, 5, 5, 5, 5, 5},
                                   {5, 4, 3, 3, 3, 4, 3, 3, 3, 3, 0, 0, 4, 4, 4, 4, 4, 4, 4, 5, 5},
                                   {6, 4, 4, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4},
                                   {6, 5, 4, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4},
                                   {0, 0, 0, 0, 0, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4},
                                   {0, 0, 0, 0, 0, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4},
                                   {8, 6, 5, 4, 4, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                                   {8, 6, 5, 4, 4, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3},
                                   {9, 6, 5, 4, 4, 4, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3},
                                   {9, 7, 5, 5, 4, 4, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3},
                                   {1, 7, 6, 5, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3},
                                   {1, 7, 6, 5, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3},
                                   {2, 8, 6, 5, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3},
                                   {2, 8, 6, 5, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3},
                                   {3, 8, 7, 6, 5, 4, 4, 4, 4, 3, 3, 3, 0, 0, 0, 0, 0, 3, 4, 3, 3},
                                   {3, 9, 7, 6, 5, 5, 4, 4, 4, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 4, 3},
                                   {4, 9, 7, 6, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{fill, grid});
    }

    //mpapply: 08ed6ac7
    {
        Connection const I{iNeuron, {}};
        Connection const F{variables.at("F"), {}};
        Connection const T{variables.at("T"), {}};
        Connection const objects{primitives.at("objects0"), {I, T, F, T}};
        Connection const totuple{primitives.at("totuple4"), {objects}};
        Connection const height{variables.at("height"), {}};
        Connection const order{primitives.at("order14"), {objects, height}};
        Connection const size{primitives.at("size6"), {totuple}};
        Connection const ZERO{variables.at("ZERO"), {}};
        Connection const NEG_ONE{variables.at("NEG_ONE"), {}};
        Connection const interval{primitives.at("interval0"), {size, ZERO, NEG_ONE}};
        Connection const recolor{variables.at("recolor"), {}};
        Connection const mpapply{primitives.at("mpapply5"), {recolor, interval, order}};
        Connection const paint{primitives.at("paint0"), {I, mpapply}};

        hodel::GridType const grid{{0, 0, 0, 0, 0, 5, 0, 0, 0},
                                   {0, 5, 0, 0, 0, 5, 0, 0, 0},
                                   {0, 5, 0, 0, 0, 5, 0, 0, 0},
                                   {0, 5, 0, 5, 0, 5, 0, 0, 0},
                                   {0, 5, 0, 5, 0, 5, 0, 0, 0},
                                   {0, 5, 0, 5, 0, 5, 0, 0, 0},
                                   {0, 5, 0, 5, 0, 5, 0, 5, 0},
                                   {0, 5, 0, 5, 0, 5, 0, 5, 0},
                                   {0, 5, 0, 5, 0, 5, 0, 5, 0}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{paint, grid});
    }

    //prapply, hline, vline: 253bf280
    {
        Connection const I{iNeuron, {}};
        Connection const EIGHT{variables.at("EIGHT"), {}};
        Connection const ofcolor{primitives.at("ofcolor0"), {I, EIGHT}};
        Connection const connect{variables.at("connect"), {}};
        Connection const prapply{primitives.at("prapply13"), {connect, ofcolor, ofcolor}};
        Connection const ONE{variables.at("ONE"), {}};
        Connection const greater{variables.at("greater"), {}};
        Connection const rbind{primitives.at("rbind8"), {greater, ONE}};
        Connection const size{variables.at("size"), {}};
        Connection const compose{primitives.at("compose0"), {rbind, size}};
        Connection const sfilter{primitives.at("sfilter11"), {prapply, compose}};
        Connection const either{variables.at("either"), {}};
        Connection const vline{variables.at("vline"), {}};
        Connection const hline{variables.at("hline"), {}};
        Connection const fork{primitives.at("fork0"), {either, vline, hline}};
        Connection const mfilter{primitives.at("mfilter3"), {sfilter, fork}};
        Connection const THREE{variables.at("THREE"), {}};
        Connection const fill1{primitives.at("fill0"), {I, THREE, mfilter}};
        Connection const fill2{primitives.at("fill0"), {fill1, EIGHT, ofcolor}};

        hodel::GridType const grid{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 8, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{fill2, grid});
    }

    //hmatching, vmatching, gravitate: d43fd935
    {
        Connection const I{iNeuron, {}};
        Connection const F{variables.at("F"), {}};
        Connection const T{variables.at("T"), {}};
        Connection const objects{primitives.at("objects0"), {I, T, F, T}};
        Connection const THREE{variables.at("THREE"), {}};
        Connection const ofcolor{primitives.at("ofcolor0"), {I, THREE}};
        Connection const ONE{variables.at("ONE"), {}};
        Connection const sizefilter{primitives.at("sizefilter4"), {objects, ONE}};
        Connection const vmatching{variables.at("vmatching"), {}};
        Connection const rbind1{primitives.at("rbind5"), {vmatching, ofcolor}};
        Connection const hmatching{variables.at("hmatching"), {}};
        Connection const rbind2{primitives.at("rbind5"), {hmatching, ofcolor}};
        Connection const either{variables.at("either"), {}};
        Connection const fork1{primitives.at("fork0"), {either, rbind1, rbind2}};
        Connection const sfilter{primitives.at("sfilter14"), {sizefilter, fork1}};
        Connection const gravitate{variables.at("gravitate"), {}};
        Connection const rbind3{primitives.at("rbind5"), {gravitate, ofcolor}};
        Connection const add{variables.at("add"), {}};
        Connection const center{variables.at("center"), {}};
        Connection const fork2{primitives.at("fork0"), {add, center, rbind3}};
        Connection const connect{variables.at("connect"), {}};
        Connection const fork3{primitives.at("fork0"), {connect, center, fork2}};
        Connection const recolor{variables.at("recolor"), {}};
        Connection const color{variables.at("color"), {}};
        Connection const fork4{primitives.at("fork0"), {recolor, color, fork3}};
        Connection const mapply{primitives.at("mapply2"), {fork4, sfilter}};
        Connection const paint{primitives.at("paint0"), {I, mapply}};

        hodel::GridType const grid{{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 6, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 3, 3, 0, 0, 0, 0, 1, 0},
                                   {0, 0, 3, 3, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 6, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 6, 0, 0, 0},
                                   {0, 0, 6, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{paint, grid});
    }

    //adjacent: 48d8fb45
    {
        Connection const I{iNeuron, {}};
        Connection const F{variables.at("F"), {}};
        Connection const T{variables.at("T"), {}};
        Connection const objects{primitives.at("objects0"), {I, T, T, T}};
        Connection const size{variables.at("size"), {}};
        Connection const ONE{variables.at("ONE"), {}};
        Connection const matcher{primitives.at("matcher8"), {size, ONE}};
        Connection const extract1{primitives.at("extract14"), {objects, matcher}};
        Connection const adjacent{variables.at("adjacent"), {}};
        Connection const lbind{primitives.at("lbind9"), {adjacent, extract1}};
        Connection const extract2{primitives.at("extract14"), {objects, lbind}};
        Connection const subgrid{primitives.at("subgrid1"), {extract2, I}};

        hodel::GridType const grid{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                                   {0, 0, 0, 5, 0, 0, 0, 1, 1, 0},
                                   {0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
                                   {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                                   {0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 1, 1, 0, 0}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{subgrid, grid});
    }

    //bordering: 6f8cd79b
    {
        Connection const I{iNeuron, {}};
        Connection const asindices{primitives.at("asindices0"), {I}};
        Connection const initset{variables.at("initset"), {}};
        Connection const apply{primitives.at("apply11"), {initset, asindices}};
        Connection const bordering{variables.at("bordering"), {}};
        Connection const rbind{primitives.at("rbind3"), {bordering, I}};
        Connection const mfilter{primitives.at("mfilter3"), {apply, rbind}};
        Connection const EIGHT{variables.at("EIGHT"), {}};
        Connection const fill{primitives.at("fill0"), {I, EIGHT, mfilter}};

        hodel::GridType const grid{{0, 0, 0, 0},
                                   {0, 0, 0, 0},
                                   {0, 0, 0, 0},
                                   {0, 0, 0, 0},
                                   {0, 0, 0, 0}};

        programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{fill, grid});
    }

    for (auto names : allNames)
    {
        std::reverse(names.begin(), names.end());

        try
        {
            programs.emplace_back(std::pair<Connection, std::optional<hodel::GridType> >{buildNamedConnection(variableNeuronsByOutputType, neuronsByOutputType, typeid(hodel::GridType), names), {}});
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

    for (auto& program : programs)
    {
        auto& connection{program.first};

        assert(connection.neuron().outputType() == typeid(hodel::GridType));

        auto const dslProgram{connection.string()};

        if (!dslProgram.contains("(I)") && !dslProgram.contains("(I, ") && !dslProgram.contains(", I,") && !dslProgram.contains(", I)"))
        {
            std::cout << "Failed to add: " << connection.string() << std::endl;

            continue;
        }

        std::any output;
        bool add{true};

        for (size_t i{0}; i < program.second.has_value() ? 1 : gridTrials; ++i)
        {
            auto const input{program.second.has_value() ? program.second.value() : generateStructuredGrid({30, 30}, {30, 30})};

            iNeuron.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };

            try
            {
                output = connection.output();

                if (output.has_value())
                {
                    auto const grid{std::any_cast<hodel::GridType>(output)};
                    add = true;

                    if (grid == input)
                        add = false;

                    auto const minReducer = [] (hodel::IntegerType a, hodel::IntegerType b) { return std::min(a, b); };
                    auto const minTransformer = [] (auto const& row) {
                        return row.empty()
                            ? std::numeric_limits<hodel::IntegerType>::max()
                            : *std::min_element(row.begin(), row.end());
                    };
                    auto const maxReducer = [] (hodel::IntegerType a, hodel::IntegerType b) { return std::max(a, b); };
                    auto const maxTransformer = [] (auto const& row) {
                        return row.empty()
                            ? std::numeric_limits<hodel::IntegerType>::min()
                            : *std::max_element(row.begin(), row.end());
                    };

                    auto const min = std::transform_reduce(
                        grid.begin(), grid.end(),
                        std::numeric_limits<hodel::IntegerType>::max(),
                        minReducer,
                        minTransformer);
                    auto const max = std::transform_reduce(
                        grid.begin(), grid.end(),
                        std::numeric_limits<hodel::IntegerType>::min(),
                        maxReducer,
                        maxTransformer);

                    if (min < 0 || max > 9)
                        add = false;

                    if (add)
                        break;
                }
            }
            catch (std::exception const&)
            {
            }
        }

        if (!add)
            std::cout << "Failed to add: " << connection.string() << std::endl;
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

    Neuron iNeuron{"I", [] (std::vector<std::any> const&) -> std::any { return std::any{}; }, std::vector<std::type_index>{}, typeid(hodel::GridType)};

    variableNeuronsByOutputType[iNeuron.outputType()].emplace_back(iNeuron);

    std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > primitiveNeuronsByOutputType;

    for (auto const& primitive : primitives)
        primitiveNeuronsByOutputType[primitive.second.outputType()].emplace_back(primitive.second);

    std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > neuronsByOutputType{variableNeuronsByOutputType};

    for (auto const& [i, v] : primitiveNeuronsByOutputType)
        neuronsByOutputType[i].insert(neuronsByOutputType[i].end(), v.begin(), v.end());

    ///checkConnections(variables, primitives, iNeuron, variableNeuronsByOutputType, neuronsByOutputType);

    std::set<Pair, PairLess> pairs;
    std::mutex mutex;

    auto const addConnection = [&mutex, &pairs, &variableNeuronsByOutputType, &neuronsByOutputType, &iNeuron, depth, count] () {
        if (pairs.size() >= count)
            return;

        try
        {
            auto const connection{buildConnection(variableNeuronsByOutputType, neuronsByOutputType, depth, typeid(hodel::GridType))};

            assert(connection.neuron().outputType() == typeid(hodel::GridType));

            auto const program{connection.string()};

            if (!program.contains("(I)") && !program.contains("(I, ") && !program.contains(", I,") && !program.contains(", I)"))
                return;

            std::any output;
            auto const input{generateStructuredGrid()};

            for (size_t i{0}; i < gridTrials; ++i)
            {
                {
                    std::lock_guard<std::mutex> lock(mutex);

                    iNeuron.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };

                    output = connection.output();
                }

                if (output.has_value())
                {
                    auto const grid{std::any_cast<hodel::GridType>(output)};
                    bool add{true};

                    if (grid == input || grid.empty())
                        add = false;

                    auto const minReducer = [] (hodel::IntegerType a, hodel::IntegerType b) { return std::min(a, b); };
                    auto const minTransformer = [] (auto const& row) {
                        return row.empty()
                            ? std::numeric_limits<hodel::IntegerType>::max()
                            : *std::min_element(row.begin(), row.end());
                    };
                    auto const maxReducer = [] (hodel::IntegerType a, hodel::IntegerType b) { return std::max(a, b); };
                    auto const maxTransformer = [] (auto const& row) {
                        return row.empty()
                            ? std::numeric_limits<hodel::IntegerType>::min()
                            : *std::max_element(row.begin(), row.end());
                    };

                    auto const min = std::transform_reduce(
                        grid.begin(), grid.end(),
                        std::numeric_limits<hodel::IntegerType>::max(),
                        minReducer,
                        minTransformer);
                    auto const max = std::transform_reduce(
                        grid.begin(), grid.end(),
                        std::numeric_limits<hodel::IntegerType>::min(),
                        maxReducer,
                        maxTransformer);

                    if (min < 0 || max > 9)
                        add = false;

                    if (add)
                    {
                        std::lock_guard<std::mutex> lock(mutex);

                        pairs.emplace(input, std::move(connection));

                        break;
                    }
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
        std::vector<hodel::GridType> grids;

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
