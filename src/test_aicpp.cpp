#include <cassert>
#include <chrono>
#include <fstream>
#include <print>

#include <boost/json.hpp>

#include <Eigen/Core>

#include <gtest/gtest.h>

#include "aicpp/Brain.h"
#include "aicpp/Connection.h"
#include "aicpp/DslEngine.h"
#include "aicpp/Hodel.h"
#include "aicpp/utility.h"

using namespace boost::json;

using namespace aicpp;

using Matrix = std::vector<std::vector<int> >;
using BoundingBox = std::tuple<int, int, int, int>;

Eigen::MatrixXi to_eigen(Matrix const& v)
{
    if (v.empty())
        return Eigen::MatrixXi{};

    auto const rows = static_cast<int>(v.size());
    auto const cols = static_cast<int>(v[0].size());

    Eigen::MatrixXi mat(rows, cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            mat(i, j) = v[i][j];
    }

    return mat;
}

Matrix to_std_vector(Eigen::MatrixXi const& mat)
{
    std::vector<std::vector<int> > result(mat.rows(), std::vector<int>(mat.cols()));

    for (int i = 0; i < mat.rows(); ++i)
    {
        for (int j = 0; j < mat.cols(); ++j)
            result[i][j] = mat(i, j);
    }

    return result;
}

std::string const path{"../ARC-AGI-2/data"};

TEST(TestAiCpp, ValidConnections)
{
    std::vector<Neuron> digitNeurons;
    digitNeurons.reserve(10);

    for (int i{0}; i < 10; ++i)
        digitNeurons.emplace_back(Neuron{std::to_string(i),
                                         [i] (std::vector<std::any> const& args) -> std::any
                                         {
                                             return i;
                                         }, std::vector<std::type_index>{}, typeid(int)});

    Neuron const addNeuron{"add",
                           [] (std::vector<std::any> const& args) -> std::any
                           {
                               return std::any_cast<int>(args[0]) + std::any_cast<int>(args[1]);
                           }, std::vector<std::type_index>{typeid(int), typeid(int)}, typeid(int)};
    Neuron const subNeuron{"sub",
                           [] (std::vector<std::any> const& args) -> std::any
                           {
                               return std::any_cast<int>(args[0]) - std::any_cast<int>(args[1]);
                           }, std::vector<std::type_index>{typeid(int), typeid(int)}, typeid(int)};
    Neuron const mulNeuron{"mul",
                           [] (std::vector<std::any> const& args) -> std::any
                           {
                               return std::any_cast<int>(args[0]) * std::any_cast<int>(args[1]);
                           }, std::vector<std::type_index>{typeid(int), typeid(int)}, typeid(int)};

    std::string dot{"digraph ConnectionTree {\n"};
    dot += "node [shape=circle, style=filled, fillcolor=lightgray];\n";

    std::pair<std::string, size_t> p;

    p = addNeuron.dot(p.second);
    dot += p.first;
    p = subNeuron.dot(p.second);
    dot += p.first;
    p = mulNeuron.dot(p.second);
    dot += p.first;

    Connection const conn0{digitNeurons[0], std::vector<std::any>{}};

    p = conn0.dot(p.second);
    dot += p.first;

    EXPECT_EQ(conn0.string(), "0");
    EXPECT_EQ(std::any_cast<int>(conn0.output()), 0);
    EXPECT_EQ(conn0.depth(), 0);
    EXPECT_EQ(conn0.cost(), 0);

    Connection const conn1{addNeuron, std::vector<std::any>{2, 3}};

    p = conn1.dot(p.second);
    dot += p.first;

    EXPECT_EQ(conn1.string(), "add(2, 3)");
    EXPECT_EQ(std::any_cast<int>(conn1.output()), 5);
    EXPECT_EQ(conn1.depth(), 0);
    EXPECT_EQ(conn1.cost(), 2);

    Connection conn2{mulNeuron, std::vector<std::any>{conn1, 4}};

    p = conn2.dot(p.second);
    dot += p.first;

    EXPECT_EQ(conn2.string(), "mul(add(2, 3), 4)");
    EXPECT_EQ(std::any_cast<int>(conn2.output()), 20);
    EXPECT_EQ(conn2.depth(), 1);
    EXPECT_EQ(conn2.cost(), 4);

    std::vector<std::type_index> const inputTypes{typeid(int), typeid(int), typeid(int)};
    EXPECT_EQ(conn2.inputTypes(), inputTypes);

    conn2.applyInputs(std::vector<std::any>{3, 5, 4});
    EXPECT_EQ(std::any_cast<int>(conn2.output()), 32);

    p = conn2.dot(p.second);
    dot += p.first;

    Connection conn3{subNeuron, std::vector<std::any>{std::type_index{typeid(int)}, std::type_index{typeid(int)}}};

    p = conn3.dot(p.second);
    dot += p.first;

    std::string const intStr{typeid(int).name()};

    EXPECT_EQ(conn3.string(), "sub(" + intStr + ", " + intStr + ")");
    EXPECT_EQ(conn3.depth(), 0);
    EXPECT_EQ(conn3.cost(), 2);

    Connection conn4{mulNeuron, std::vector<std::any>{conn3, std::type_index{typeid(int)}}};

    p = conn4.dot(p.second);
    dot += p.first;

    EXPECT_EQ(conn4.string(), "mul(sub(" + intStr + ", " + intStr + "), " + intStr + ")");

    Connection conn5{addNeuron, std::vector<std::any>{std::type_index{typeid(int)}, std::type_index{typeid(int)}}};

    p = conn5.dot(p.second);
    dot += p.first;

    conn5.applyInputs(std::vector<std::any>{std::type_index{typeid(int)}, conn3});

    EXPECT_EQ(conn5.string(), "add(" + intStr + ", sub(" + intStr + ", " + intStr + "))");
    EXPECT_EQ(conn5.depth(), 1);
    EXPECT_EQ(conn5.cost(), 4);

    p = conn5.dot(p.second);
    dot += p.first;

    dot += "}\n";

    std::ofstream ofs{"validConnections.dot"};
    ofs << dot;
    ofs.close();

    Neuron intNeuron{"intNeuron",
                     [] (std::vector<std::any> const& args) -> std::any { return 0; },
                     std::vector<std::type_index>{}, typeid(int)};
    Connection const conn6{intNeuron, std::vector<std::any>{}};

    EXPECT_EQ(std::any_cast<int>(conn6.output()), 0);

    intNeuron.function() = [] (std::vector<std::any> const& args) -> std::any { return 1; };

    EXPECT_EQ(std::any_cast<int>(conn6.output()), 1);

    EXPECT_EQ(&conn6.neuron(), &intNeuron);

    {
        Connection const c1{addNeuron, std::vector<std::any>{1, 2}};
        Connection const c2{addNeuron, std::vector<std::any>{3, 4}};
        Connection const c3{mulNeuron, std::vector<std::any>{c1, c2}};
        Connection c4{addNeuron, std::vector<std::any>{c3, c3}};

        EXPECT_EQ(std::any_cast<int>(c4.output()), (1 + 2) * (3 + 4) + (1 + 2) * (3 + 4));

        std::string dot{"digraph ConnectionTree {\n"};
        dot += "node [shape=circle, style=filled, fillcolor=lightgray];\n";

        std::pair<std::string, size_t> p;

        p = c4.dot(p.second);
        dot += p.first;
        dot += "}\n";

        {
            std::ofstream ofs{"typedValidConnection.dot"};
            ofs << dot;
        }

        c4.applyInputs(std::vector<std::any>{4, 5, 6, 7, 8, 9, 10, 11});

        dot = "digraph ConnectionTree {\n";
        dot += "node [shape=circle, style=filled, fillcolor=lightgray];\n";

        p = c4.dot(p.second);
        dot += p.first;
        dot += "}\n";

        {
            std::ofstream ofs{"valuedValidConnection.dot"};
            ofs << dot;
        }

        EXPECT_EQ(std::any_cast<int>(c4.output()), (4 + 5) * (6 + 7) + (8 + 9) * (10 + 11));
    }
}

TEST(TestAiCpp, Str)
{
    std::vector<Neuron> digitNeurons;

    for (int i{0}; i < 10; ++i)
        digitNeurons.emplace_back(Neuron{std::to_string(i),
                                         [i] (std::vector<std::any> const& args) -> std::any
                                         {
                                             return i;
                                         }, std::vector<std::type_index>{}, typeid(int)});

    Neuron const addNeuron{"add",
                           [] (std::vector<std::any> const& args) -> std::any
                           {
                               return std::any_cast<int>(args[0]) + std::any_cast<int>(args[1]);
                           }, std::vector<std::type_index>{typeid(int), typeid(int)}, typeid(int)};
    Neuron const mulNeuron{"mul",
                           [] (std::vector<std::any> const& args) -> std::any
                           {
                               return std::any_cast<int>(args[0]) * std::any_cast<int>(args[1]);
                           }, std::vector<std::type_index>{typeid(int), typeid(int)}, typeid(int)};
    Neuron const intToStrNeuron{"intToStr",
                                [] (std::vector<std::any> const& args) -> std::any
                                {
                                    return std::to_string(std::any_cast<int>(args[0]));
                                }, std::vector<std::type_index>{typeid(int)}, typeid(std::string)};

    std::vector<std::reference_wrapper<Neuron const> > neurons;

    for (auto const& neuron : digitNeurons)
        neurons.emplace_back(neuron);

    neurons.emplace_back(addNeuron);
    neurons.emplace_back(mulNeuron);
    neurons.emplace_back(intToStrNeuron);

    Brain brain{neurons};

    auto const connections{brain.learn(std::vector<std::any>{std::string{"11"}}, 2)};

    EXPECT_TRUE(connections.size());

    auto const connection{connections[0]};

    std::cout << connection.string() << std::endl;

    EXPECT_FALSE(utility::heuristic(connection.output(), std::string{"11"}));

    auto addAndStr{connection.source()};
    addAndStr.setName("addAndStr");

    EXPECT_EQ(addAndStr.string(), std::string{"addAndStr("} + typeid(int).name() + ", " + typeid(int).name() + ")");

    brain.addConnection(addAndStr);

    {
        auto const connections{brain.learn(std::vector<std::any>{std::string{"11"}}, 1)};

        EXPECT_TRUE(connections.size());

        auto const connection{connections[0]};

        std::cout << connection.string() << std::endl;
    }

    auto const value{brain.toJson()};

    std::ofstream ofs{"strBrain.json"};

    ofs << boost::json::serialize(value);

    brain.clearConnections();

    EXPECT_TRUE(brain.fromJson(value));

    EXPECT_EQ(brain.connections().size(), 1);

    auto const c{*brain.connections().begin()};

    EXPECT_EQ(c.string(), std::string{"addAndStr("} + typeid(int).name() + ", " + typeid(int).name() + ")");

    {
        auto const connections{brain.learn(std::vector<std::any>{std::string{"11"}}, 1)};

        EXPECT_TRUE(connections.size());

        auto const connection{connections[0]};

        std::cout << connection.string() << std::endl;
    }
}

Eigen::MatrixXi boostJsonToEigenMatrix(array const& arr)
{
    auto const rows = arr.size();
    auto const cols = arr.at(0).as_array().size();

    Eigen::MatrixXi mat(rows, cols);

    for (size_t i = 0; i < rows; ++i)
    {
        auto const& row = arr[i].as_array();

        for (size_t j = 0; j < cols; ++j)
            mat(i, j) = (int)row[j].as_int64();
    }

    return mat;
}

std::pair<std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >,
          std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > > trainTestPairs(std::string const& folder, std::string const& task)
{
    std::set<std::string> const s{"training", "evaluation"};

    assert(s.contains(folder));

    std::ifstream ifs{path + "/" + folder + "/" + task + ".json"};

    std::string content;

    while (ifs)
    {
        std::string line;

        std::getline(ifs, line);

        content += line + '\n';
    }

    value const jv{parse(content)};
    boost::json::array train;

    if (jv.is_object())
        train = jv.at("train").as_array();
    else if (jv.is_array())
        train = jv.as_array()[0].at("train").as_array();

    std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > trainPairs;

    for (size_t i{0}; i < train.size(); ++i)
    {
        auto const& sample{train[i].as_object()};

        trainPairs.emplace_back(std::make_pair(boostJsonToEigenMatrix(sample.at("input").as_array()),
                                               boostJsonToEigenMatrix(sample.at("output").as_array())));
    }

    boost::json::array test;

    if (jv.is_object())
        test = jv.at("test").as_array();
    else if (jv.is_array())
        test = jv.as_array()[0].at("test").as_array();

    std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > testPairs;

    for (size_t i{0}; i < test.size(); ++i)
    {
        auto const& sample{test[i].as_object()};

        testPairs.emplace_back(std::make_pair(boostJsonToEigenMatrix(sample.at("input").as_array()),
                                              boostJsonToEigenMatrix(sample.at("output").as_array())));
    }

    return std::make_pair(trainPairs, testPairs);
}

std::pair<std::vector<Eigen::MatrixXi>, std::vector<Eigen::MatrixXi> > inputOutputPairs(
    std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > const& taskPairs)
{
    std::vector<Eigen::MatrixXi> inputs, outputs;
    inputs.reserve(taskPairs.size());
    outputs.reserve(taskPairs.size());

    for (size_t i{0}; i < taskPairs.size(); ++i)
    {
        inputs.emplace_back(taskPairs[i].first);
        outputs.emplace_back(taskPairs[i].second);
    }

    return std::make_pair(inputs, outputs);
}

DslEngine buildSimplifiedEngine(std::set<std::string> const& ops = std::set<std::string>{"add", "sub", "mul"})
{
    DslEngine engine;

    engine.clearVariableNeurons();

    for (int i{0}; i < 10; ++i)
        engine.addVariableNeuron(Neuron(std::to_string(i), [i] (std::vector<std::any> const&) -> std::any { return i; }, std::vector<std::type_index>{}, typeid(int)));

    engine.clearPrimitiveNeurons();

    if (ops.contains("add"))
        engine.addPrimitiveNeuron(Neuron("add", [] (std::vector<std::any> const& args) -> std::any { return std::any_cast<int>(args[0]) + std::any_cast<int>(args[1]); }, std::vector<std::type_index>{typeid(int), typeid(int)}, typeid(int)));

    if (ops.contains("sub"))
        engine.addPrimitiveNeuron(Neuron("sub", [] (std::vector<std::any> const& args) -> std::any { return std::any_cast<int>(args[0]) - std::any_cast<int>(args[1]); }, std::vector<std::type_index>{typeid(int), typeid(int)}, typeid(int)));

    if (ops.contains("mul"))
        engine.addPrimitiveNeuron(Neuron("mul", [] (std::vector<std::any> const& args) -> std::any { return std::any_cast<int>(args[0]) * std::any_cast<int>(args[1]); }, std::vector<std::type_index>{typeid(int), typeid(int)}, typeid(int)));

    return engine;
}

void learnInt(DslEngine& engine, std::string const& expression, int target)
{
    auto const t{std::chrono::high_resolution_clock::now()};

    std::println("Target expression: {0} = {1}", expression, target);

    auto const [c, args, cost] = engine.learn(target);

    std::println("Found connection: {0}", c.string());

    auto connnection{c};
    std::vector<std::any> inputs;
    inputs.reserve(args.size());

    for (auto const& n : args)
        inputs.emplace_back(engine.variableNeurons().at(n).function()(std::vector<std::any>{}));

    connnection.applyInputs(inputs);

    std::println("Applied connection: {0}", connnection.string());
    std::println("Args: {0}, output: {1}, cost: {2}", args, std::any_cast<int>(connnection.output()), cost);
    std::println("Duration: {0} s", std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - t).count());

    EXPECT_FALSE(cost);
}

TEST(TestAiCpp, LearnDigit)
{
    DslEngine engine{buildSimplifiedEngine()};

    learnInt(engine, "5", 5);
}

TEST(TestAiCpp, LearnOneAddition)
{
    DslEngine engine{buildSimplifiedEngine()};

    learnInt(engine, "7 + 8", 7 + 8);
}

TEST(TestAiCpp, LearnThreeAdditions)
{
    DslEngine engine{buildSimplifiedEngine(std::set<std::string>{"add"})};

    learnInt(engine, "5 + 7 + 8", 5 + 7 + 8);
}

TEST(TestAiCpp, LearnSimpleOperation)
{
    DslEngine engine{buildSimplifiedEngine(std::set<std::string>{"add", "mul"})};

    learnInt(engine, "5 + 7 * 8", 5 + 7 * 8);
}

TEST(TestAiCpp, LearnOperations)
{
    DslEngine engine{buildSimplifiedEngine(std::set<std::string>{"add", "mul"})};

    learnInt(engine, "5", 5);
    learnInt(engine, "7 + 8", 7 + 8);
    learnInt(engine, "5 + 7 + 8", 5 + 7 + 8);
    learnInt(engine, "5 + 7 * 8", 5 + 7 * 8);
}

TEST(TestAiCpp, LearnThreeLevels)
{
    DslEngine engine{buildSimplifiedEngine(std::set<std::string>{"add", "mul", "sub"})};

    learnInt(engine, "(3 + 4) * (8 - 2)", (3 + 4) * (8 - 2));
}

double size_cost(Matrix const& x, Matrix const& y)
{
    Eigen::Vector2d const xs{static_cast<double>(x.size()), x.empty() ? 0 : static_cast<double>(x[0].size())};
    Eigen::Vector2d const ys{static_cast<double>(y.size()), y.empty() ? 0 : static_cast<double>(y[0].size())};

    return (xs - ys).norm();
}

int total_sum(Matrix const& v)
{
    int s{0};

    for (const auto& row : v)
        s += std::accumulate(row.begin(), row.end(), 0);

    return s;
}

double value_cost(Matrix const& x, Matrix const& y)
{
    Eigen::Vector2d const xs{static_cast<double>(x.size()), x.empty() ? 0 : static_cast<double>(x[0].size())};
    Eigen::Vector2d const ys{static_cast<double>(y.size()), y.empty() ? 0 : static_cast<double>(y[0].size())};

    if (xs == ys)
    {
        auto const x_{to_eigen(x)};
        auto const y_{to_eigen(y)};

        return (x_ - y_).norm();
    }

    return static_cast<double>(std::abs(total_sum(x) - total_sum(y)));
}

double pixel_overlap_cost(Matrix const& x, Matrix const& y)
{
     if (x.size() != y.size())
     {
        size_t sx = 0;
        size_t sy = 0;

        for (auto const& row : x)
            sx += row.size();

        for (auto const& row : y)
            sy += row.size();

        return static_cast<double>(sx + sy);
    }

    if (!x.empty())
    {
        for (size_t i = 0; i < x.size(); ++i)
        {
            if (x[i].size() != y[i].size())
            {
                size_t sx = 0;
                size_t sy = 0;

                for (auto const& row : x)
                    sx += row.size();

                for (auto const& row : y)
                    sy += row.size();

                return static_cast<double>(sx + sy);
            }
        }
    }

    int total   = 0;
    int matches = 0;

    for (size_t i = 0; i < x.size(); ++i)
    {
        for (size_t j = 0; j < x[i].size(); ++j)
        {
            ++total;

            if (x[i][j] == y[i][j])
                ++matches;
        }
    }

    return 1.0 - (static_cast<double>(matches) / total);
}

std::optional<BoundingBox> bounding_box(const Matrix& arr)
{
    bool found = false;
    int y_min = 0;
    int x_min = 0;
    int y_max = 0;
    int x_max = 0;

    for (int y = 0; y < static_cast<int>(arr.size()); ++y)
    {
        for (int x = 0; x < static_cast<int>(arr[y].size()); ++x)
        {
            if (arr[y][x] != 0)
            {
                if (!found)
                {
                    y_min = y_max = y;
                    x_min = x_max = x;
                    found = true;
                }
                else
                {
                    y_min = std::min(y_min, y);
                    x_min = std::min(x_min, x);
                    y_max = std::max(y_max, y);
                    x_max = std::max(x_max, x);
                }
            }
        }
    }

    if (!found)
        return std::nullopt;

    return BoundingBox{y_min, x_min, y_max, x_max};
}

double bounding_box_cost(const Matrix& x, const Matrix& y)
{
    auto box_x = bounding_box(x);
    auto box_y = bounding_box(y);

    if (!box_x.has_value() && !box_y.has_value())
        return 0.0;

    if (!box_x.has_value() || !box_y.has_value())
        return 1.0;

    auto [y1a, x1a, y2a, x2a] = *box_x;
    auto [y1b, x1b, y2b, x2b] = *box_y;

    double const diff =
        std::sqrt(
            std::pow(y1a - y1b, 2) +
            std::pow(x1a - x1b, 2) +
            std::pow(y2a - y2b, 2) +
            std::pow(x2a - x2b, 2)
        );

    auto const x_rows = static_cast<int>(x.size());
    auto const x_cols = x.empty() ? 0 : static_cast<int>(x[0].size());
    auto const y_rows = static_cast<int>(y.size());
    auto const y_cols = y.empty() ? 0 : static_cast<int>(y[0].size());

    double const norm =
        std::sqrt(
            std::pow(x_rows + y_rows, 2) +
            std::pow(x_cols + y_cols, 2)
        );

    return diff / (norm + 1e-8);
}

double arcHeuristic(std::any const& x, std::any const& y)
{
    std::vector<std::vector<int> > x_;
    std::vector<std::vector<int> > y_;

    if (x.type() == typeid(hodel::Grid))
        x_ = std::any_cast<hodel::Grid>(x);
    else if (x.type() == typeid(hodel::Piece))
    {
        auto const& piece = std::any_cast<hodel::Piece>(x);
        
        if (std::holds_alternative<hodel::Grid>(piece))
            x_ = std::get<hodel::Grid>(piece);
    }
    else if (x.type() == typeid(hodel::Element))
    {
        auto const& element = std::any_cast<hodel::Element>(x);
        
        if (std::holds_alternative<hodel::Grid>(element))
            x_ = std::get<hodel::Grid>(element);
    }

    if (y.type() == typeid(hodel::Grid))
        y_ = std::any_cast<hodel::Grid>(y);
    else if (y.type() == typeid(hodel::Piece))
    {
        auto const& piece = std::any_cast<hodel::Piece>(y);
        
        if (std::holds_alternative<hodel::Grid>(piece))
            y_ = std::get<hodel::Grid>(piece);
    }
    else if (y.type() == typeid(hodel::Element))
    {
        auto const& element = std::any_cast<hodel::Element>(y);
        
        if (std::holds_alternative<hodel::Grid>(element))
            y_ = std::get<hodel::Grid>(element);
    }

    return size_cost(x_, y_) + bounding_box_cost(x_, y_) + pixel_overlap_cost(x_, y_) + value_cost(x_, y_);
}

DslEngine dslEngine(arcHeuristic);

TEST(TestAiCpp, InitDslEngine)
{
    dslEngine.addVariableNeuron(Neuron{"I", [] (std::vector<std::any> const&) { return std::any{}; }, std::vector<std::type_index>{}, typeid(hodel::Grid)});
}

std::tuple<double, double, std::string> processTask(std::string const& folder, std::string const& task)
{
    auto const taskPairs{trainTestPairs(folder, task)};
    std::vector<std::tuple<Connection, std::vector<std::string>, double> > results;
    std::unique_ptr<Connection> connection;
    std::unique_ptr<std::tuple<Connection, std::vector<std::string>, double> > result;
    std::vector<std::string> args;

    for (auto const& [inp, out] : taskPairs.first)
    {
        dslEngine.variableNeuron("I").function() = [inp] (std::vector<std::any> const&) -> std::any { return to_std_vector(inp); };
        bool process{true};

        if (connection)
        {
            auto connectionTmp{*connection};
            std::vector<std::any> inputs;
            inputs.reserve(args.size());

            for (auto const& n : args)
                inputs.emplace_back(dslEngine.variableNeuron(n).function()(std::vector<std::any>{}));

            connectionTmp.applyInputs(inputs);

            auto const output{connectionTmp.output()};
            auto const cost{dslEngine.heuristic()(output, to_std_vector(out))};
            process = cost;
        }

        if (process)
        {
            result = std::make_unique<std::tuple<Connection, std::vector<std::string>, double> >(std::move(dslEngine.learn(to_std_vector(out))));
            auto const& [c, a, cost] = *result;
            args = a;
            connection = std::make_unique<Connection>(std::move(c));
        }
        
        results.emplace_back(*result);
    }

    std::vector<std::pair<double, std::reference_wrapper<const std::tuple<Connection, std::vector<std::string>, double> > > > sortedResults;
    sortedResults.reserve(results.size());

    for (auto const& r : results)
    {
        double totalCost{0};

        for (auto const& [inp, out] : taskPairs.first)
        {
            dslEngine.variableNeuron("I").function() = [inp] (std::vector<std::any> const&) -> std::any { return to_std_vector(inp); };
            auto const& [c, arguments, cost] = r;
            auto connectionTmp{c};
            std::vector<std::any> inputs;
            inputs.reserve(arguments.size());

            for (auto const& n : arguments)
                inputs.emplace_back(dslEngine.variableNeuron(n).function()(std::vector<std::any>{}));

            connectionTmp.applyInputs(inputs);
            auto const output{connectionTmp.output()};
            totalCost += dslEngine.heuristic()(output, to_std_vector(out));
        }

        sortedResults.emplace_back(totalCost, std::cref(r));
    }

    std::sort(sortedResults.begin(), sortedResults.end(), [] (auto const& a, auto const& b) { return a.first < b.first; });
    double testCost{0};
    auto const& [trainCost, resultTmp] = sortedResults.front();

    for (auto const& [inp, out] : taskPairs.second)
    {
        dslEngine.variableNeuron("I").function() = [inp] (std::vector<std::any> const&) -> std::any { return to_std_vector(inp); };
        auto const& [c, arguments, cost] = resultTmp.get();
        auto connectionTmp{c};
        std::vector<std::any> inputs;
        inputs.reserve(arguments.size());

        for (auto const& n : arguments)
            inputs.emplace_back(dslEngine.variableNeuron(n).function()(std::vector<std::any>{}));

        connectionTmp.applyInputs(inputs);
        auto const output{connectionTmp.output()};
        testCost += dslEngine.heuristic()(output, to_std_vector(out));
    }

    auto const& [c, arguments, cost] = resultTmp.get();
    auto connectionTmp{c};

    std::vector<std::any> inputs;
    inputs.reserve(arguments.size());

    for (auto const& arg : arguments)
        inputs.emplace_back(arg);

    connectionTmp.applyInputs(inputs, false);

    return std::make_tuple(trainCost, testCost, connectionTmp.string());
}

void passTask(std::string const& folder, std::string const& task, bool debug = false)
{
    auto const [trainCost, testCost, dsl] = processTask(folder, task);

    if (debug)
        std::println("Train cost: {0}, test cost: {1}, dsl: {2}", trainCost, testCost, dsl);

    EXPECT_FALSE(trainCost + testCost);
}

std::vector<std::string> read_lines(std::string const& filename)
{
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line))
        lines.emplace_back(line);

    return lines;
}

std::string trim(const std::string& s)
{
    auto const begin = s.find_first_not_of(" \t\r\n");

    if (begin == std::string::npos)
        return "";

    auto const end = s.find_last_not_of(" \t\r\n");

    return s.substr(begin, end - begin + 1);
}

TEST(TestAiCpp, TestHodelTasks)
{
    std::vector<std::string> const lines{read_lines("../scripts/arc-dsl/solvers.py")};
    std::vector<std::string> tasks;

    for (auto const& line : lines)
    {
        if (line.starts_with("def solve_"))
        {
            auto const start{line.find('_') + 1};
            auto const end{line.find('(')};

            tasks.emplace_back(line.substr(start, end - start));
        }
    }

    std::map<int, std::vector<std::string> > tasksByStep;

    for (auto const& task : tasks)
    {
        std::string const signature{"def solve_" + task + "(I):"};

        auto const it{std::find(lines.begin(), lines.end(), signature)};

        if (it == lines.end())
            continue;

        int i{static_cast<int>(std::distance(lines.begin(), it)) + 1};
        int count{0};

        while (i < static_cast<int>(lines.size()) && !lines[i].starts_with("def solve_"))
        {
            auto const t{trim(lines[i])};

            if (!t.empty() && !t.starts_with("return"))
                ++count;

            ++i;
        }

        tasksByStep[count].emplace_back(task);
    }

    for (auto const& [k, v] : tasksByStep)
    {
        if (k != 1)
            continue;

        auto const t1{std::chrono::high_resolution_clock::now()};

        for (auto const& task : v)
        {
            std::println("training {0}", task);

            auto const t2{std::chrono::high_resolution_clock::now()};

            passTask("training", task, true);

            auto const duration{std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t2).count()};

            std::println("Duration: {0} s", duration);
        }

        auto const total_duration{std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t1).count()};

        std::println("Duration for {0} step{1} of DSL ({2} tasks): {3} s", k, (k > 1 ? "s" : ""), v.size(), total_duration);
    }
}
/*
TEST(TestAicpp, TestTask0d3d703e) //Color mapping
{
    passTask("training", "0d3d703e", true);
}
*/