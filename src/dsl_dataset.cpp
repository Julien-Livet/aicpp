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
        {"replace", "I", "ONE", "subtract", "NINE", "FOUR"},
        {"replace", "I", "ONE", "multiply", "TWO", "THREE"},
        {"compress", "rot90", "righthalf", "vmirror", "vconcat", "switch", "I", "divide", "ONE", "NEG_ONE", "NEG_ONE", "I"},
        {"replace", "I", "ONE", "multiply", "NEG_ONE", "invert", "TWO"},
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
        {"replace", "I", "ONE", "divide", "size", "I", "SIX"},
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
        {"replace", "I", "TWO", "first", "sfilter", "interval", "invert", "SIX", "SIX", "ONE", "positive"},
        //{"mfilter"}, //cf. below
        //{"extract"},
        {"paint", "vmirror", "I", "first", "totuple", "objects", "I", "F", "F", "T"},
        //{"insert"},
        //{"remove"},
        //{"other"},
        {"crop", "I", "astuple", "FOUR", "FIVE", "astuple", "SIX", "SEVEN"},
        //{"product"},
        //{"pair"},
        //{"chain"},
        //{"matcher"},
        //{"lbind"}, //cf. below
        //{"power"},
        //{"fork"},
        {"apply", "first", "combine", "hmirror", "I", "vmirror", "I"},
        //{"rapply"},
        //{"mapply"},
        //{"papply"},
        //{"mpapply"},
        //{"prapply"},
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
    };

    std::vector<Connection> connections;

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
        Connection const mfilter{primitives.at("mfilter58"), {objects, compose}};
        Connection const hmirror{primitives.at("hmirror0"), {I}};
        Connection const paint{primitives.at("paint"), {hmirror, mfilter}};

        connections.emplace_back(paint);
    }

    {
        Connection const width{variables.at("width"), {}};
        Connection const greater{variables.at("greater"), {}};
        Connection const ONE{variables.at("ONE"), {}};
        Connection const lbind{primitives.at("lbind5"), {greater, ONE}};
        Connection const compose{primitives.at("compose"), {lbind, width}};
        Connection const I{iNeuron, {}};
        Connection const F{variables.at("F"), {}};
        Connection const T{variables.at("T"), {}};
        Connection const objects{primitives.at("objects"), {I, F, F, T}};
        Connection const mfilter{primitives.at("mfilter58"), {objects, compose}};
        Connection const hmirror{primitives.at("hmirror0"), {I}};
        Connection const paint{primitives.at("paint"), {hmirror, mfilter}};

        connections.emplace_back(paint);
    }

    for (auto names : allNames)
    {
        std::reverse(names.begin(), names.end());

        try
        {
            connections.emplace_back(buildNamedConnection(variableNeuronsByOutputType, neuronsByOutputType, typeid(hodel::Grid), names));
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

        auto const program{connection.string()};

        if (!program.contains("(I)") && !program.contains("(I, ") && !program.contains(", I,") && !program.contains(", I)"))
        {
            std::cout << "Failed to add: " << connection.string() << std::endl;

            continue;
        }

        std::any output;
        bool add{true};

        for (size_t i{0}; i < gridTrials; ++i)
        {
            auto const input{generateStructuredGrid({30, 30}, {30, 30})};

            iNeuron.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };
/*
            try
            {*/
                output = connection.output();

                if (output.has_value())
                {
                    auto const grid{std::any_cast<hodel::Grid>(output)};
                    add = true;

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

                    if (add)
                        break;
                }/*
            }
            catch (std::exception const&)
            {
                std::cout << "Failed connection: " << connection.string() << std::endl;
            }*/
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
