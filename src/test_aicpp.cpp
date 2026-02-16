#include <fstream>

#include <boost/json.hpp>

#include <Eigen/Core>

#include <gtest/gtest.h>

#include "aicpp/Brain.h"
#include "aicpp/Connection.h"
#include "aicpp/primitives.h"
#include "aicpp/utility.h"

using namespace boost::json;

using namespace aicpp;

std::string const path{"../../ARC-AGI-2-main/data"};

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
    std::size_t const rows = arr.size();
    std::size_t const cols = arr.at(0).as_array().size();

    Eigen::MatrixXi mat(rows, cols);

    for (std::size_t i = 0; i < rows; ++i)
    {
        auto const& row = arr[i].as_array();

        for (std::size_t j = 0; j < cols; ++j)
            mat(i, j) = (int)row[j].as_int64();
    }

    return mat;
}

std::pair<std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >,
          std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > > trainTestPairs(std::string const& folder, std::string const& task)
{
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

void updateRegionNeurons(std::map<int, Neuron>& regionNeurons, std::vector<Eigen::MatrixXi> const& pairs)
{
    std::map<int, std::vector<std::vector<std::vector<std::pair<int, int> > > > > regionMap;

    for (auto const& input : pairs)
    {
        auto const s{utility::regionSet(input, false)};

        std::map<int, std::vector<std::vector<std::pair<int, int> > > > regions;

        for (int i{0}; i < 10; ++i)
            regions[i].clear();

        for (auto const& r : s)
            regions[input(r.front().first, r.front().second)].emplace_back(r);

        for (auto const& p : regions)
            regionMap[p.first].emplace_back(p.second);
    }

    for (auto const& p : regionMap)
    {
        auto const function{
            [p] (std::vector<std::any> const& args) -> std::any
            {
                return p.second;
            }};

        size_t emptyCount{0};

        for (auto const& v : p.second)
        {
            if (v.empty())
                ++emptyCount;
        }

        auto const it{regionNeurons.find(p.first)};

        if (it == regionNeurons.end())
        {
            if (emptyCount != p.second.size())
                regionNeurons.emplace(std::make_pair(p.first, Neuron{"region" + std::to_string(p.first),
                                                                     function, std::vector<std::type_index>{}, typeid(std::vector<std::vector<std::vector<std::pair<int, int> > > >)}));
        }
        else
        {
            if (emptyCount != p.second.size())
                it->second.function() = function;
            else
                regionNeurons.erase(it);
        }
    }
}

int processTask(std::string const& folder, std::string const& task, std::vector<std::string> const& activatedNeuronNames = std::vector<std::string>{})
{
    auto const taskPairs{trainTestPairs(folder, task)};
    auto const trainPairs{inputOutputPairs(taskPairs.first)};
    auto const testPairs{inputOutputPairs(taskPairs.second)};

    std::vector<Neuron> digitNeurons;
    digitNeurons.reserve(10);

    for (int i{0}; i < digitNeurons.capacity(); ++i)
        digitNeurons.emplace_back(Neuron{std::to_string(i), [i] (std::vector<std::any> const& args) -> std::any { return i; }, std::vector<std::type_index>{}, typeid(int)});

    Neuron const mapNeuron{"map", primitives::map, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>), typeid(std::map<int, int>)}, typeid(std::vector<Eigen::MatrixXi>)};
    Neuron const mappingNeuron{"mapping", [] (std::vector<std::any> const&) -> std::any { return std::map<int, int>{}; }, std::vector<std::type_index>{}, typeid(std::map<int, int>)};
    Neuron const associateNeuron{"associate",
                                 [] (std::vector<std::any> const& args) -> std::any
                                 {
                                     auto m{std::any_cast<std::map<int, int> >(args[0])};
                                     auto const a{std::any_cast<int>(args[1])};
                                     auto const b{std::any_cast<int>(args[2])};

                                     m[a] = b;

                                     return m;
                                 }, std::vector<std::type_index>{typeid(std::map<int, int>), typeid(int), typeid(int)}, typeid(std::map<int, int>)};
    Neuron const inferColorMappingNeuron{"inferColorMapping", primitives::inferColorMapping, std::vector<std::type_index>{typeid(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >)}, typeid(std::map<int, int>)};
    Neuron const pairsNeuron{"pairs",
                             [taskPairs] (std::vector<std::any> const& args) -> std::any
                             {
                                 auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

                                 if (taskPairs.first.size() != v.size())
                                     return std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >{};

                                 auto pairs{taskPairs.first};

                                 for (size_t i{0}; i < pairs.size(); ++i)
                                     pairs[i].first = v[i];

                                 return pairs;
                             }, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>)}, typeid(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >)};
    Neuron const trainPairsNeuron{"trainPairs",
                                  [taskPairs] (std::vector<std::any> const& args) -> std::any
                                  {
                                      return taskPairs.first;
                                  }, std::vector<std::type_index>{}, typeid(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >)};
    Neuron const fliplrNeuron{"fliplr", primitives::fliplr, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>)}, typeid(std::vector<Eigen::MatrixXi>)};
    Neuron const flipudNeuron{"flipud", primitives::flipud, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>)}, typeid(std::vector<Eigen::MatrixXi>)};
    Neuron const falseNeuron{"false",
                             [] (std::vector<std::any> const& args) -> std::any
                             {
                                 return false;
                             }, std::vector<std::type_index>{}, typeid(bool)};
    Neuron const trueNeuron{"true",
                            [] (std::vector<std::any> const& args) -> std::any
                            {
                                return true;
                            }, std::vector<std::type_index>{}, typeid(bool)};
    Neuron const sameElementNeuron{"sameElement", primitives::sameElement, std::vector<std::type_index>{typeid(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > >), typeid(bool)},
                                   typeid(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > >)};
    Neuron const regionPairsNeuron{"regionPairs", primitives::regionPairs, std::vector<std::type_index>{typeid(std::vector<std::vector<std::vector<std::pair<int, int> > > >)},
                                   typeid(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > >)};
    Neuron const pairedRegionsNeuron{"pairedRegions",
                                     [] (std::vector<std::any> const& args) -> std::any
                                     {
                                         auto const v1{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
                                         auto const v2{std::any_cast<std::vector<std::vector<std::vector<std::pair<int, int> > > > >(args[1])};

                                         std::vector<std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > > result;

                                         if (v1.size() != v2.size())
                                             return result;

                                         result.reserve(v1.size());

                                         for (size_t i{0}; i < v1.size(); ++i)
                                             result.emplace_back(utility::pairedRegions(v1[i], v2[i]));

                                         return result;
                                     }, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>), typeid(std::vector<std::vector<std::vector<std::pair<int, int> > > >)},
                                     typeid(std::vector<std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > >)};
    Neuron const memberPairedRegionsNeuron{"memberPairedRegions",
                                           [] (std::vector<std::any> const& args) -> std::any
                                           {
                                               auto const v{std::any_cast<std::vector<std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > > >(args[0])};
                                               std::vector<std::vector<std::vector<std::pair<int, int> > > > result;
                                               result.reserve(v.size());

                                               for (auto const& x : v)
                                                   result.emplace_back(utility::memberPairedRegions(x, std::any_cast<bool>(args[1])));

                                               return result;
                                           }, std::vector<std::type_index>{typeid(std::vector<std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > > >), typeid(bool)},
                                           typeid(std::vector<std::vector<std::vector<std::pair<int, int> > > >)};
    Neuron const fillRegionsNeuron{"fillRegions",
                                   [] (std::vector<std::any> const& args) -> std::any
                                   {
                                       auto const v1{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};
                                       auto const v2{std::any_cast<std::vector<std::vector<std::vector<std::pair<int, int> > > > >(args[1])};

                                       std::vector<Eigen::MatrixXi> result;

                                       if (v1.size() != v2.size())
                                           return result;

                                       result.reserve(v1.size());

                                       for (size_t i{0}; i < v1.size(); ++i)
                                           result.emplace_back(utility::fillRegions(v1[i], v2[i], std::any_cast<int>(args[2])));

                                       return result;
                                   }, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>), typeid(std::vector<std::vector<std::vector<std::pair<int, int> > > >), typeid(int)},
                                   typeid(std::vector<Eigen::MatrixXi>)};
    Neuron const segmentsNeuron{"segments", primitives::segments, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>), typeid(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > >), typeid(int), typeid(bool), typeid(bool)},
                                typeid(std::vector<Eigen::MatrixXi>)};
    Neuron inputNeuron{"input",
                       [trainPairs] (std::vector<std::any> const&) -> std::any
                       {
                           return trainPairs.first;
                       }, std::vector<std::type_index>{}, typeid(std::vector<Eigen::MatrixXi>)};

    std::map<int, Neuron> regionNeurons;
    updateRegionNeurons(regionNeurons, trainPairs.first);

    std::vector<std::reference_wrapper<Neuron const> > neurons;

    if (activatedNeuronNames.empty() || std::find(activatedNeuronNames.begin(), activatedNeuronNames.end(), "digitNeurons") != activatedNeuronNames.end())
    {
        //neurons.insert(neurons.end(), std::ranges::begin(digitNeurons), std::ranges::end(digitNeurons));

        std::set<int> digits;

        for (auto const& m : trainPairs.first)
        {
            for (auto const& v : m.reshaped())
                digits.emplace(v);
        }

        for (auto const& m : trainPairs.second)
        {
            for (auto const& v : m.reshaped())
                digits.emplace(v);
        }

        std::vector<bool> existingDigits;
        existingDigits.reserve(10);

        for (size_t i{0}; i < 10; ++i)
            existingDigits.emplace_back(digits.find(i) != digits.end());

        for (size_t i{0}; i < digitNeurons.size(); ++i)
        {
            if (existingDigits[i])
                neurons.emplace_back(digitNeurons[i]);
        }
    }

    if (activatedNeuronNames.empty() || std::find(activatedNeuronNames.begin(), activatedNeuronNames.end(), "boolNeurons") != activatedNeuronNames.end())
    {
        neurons.emplace_back(falseNeuron);
        neurons.emplace_back(trueNeuron);
    }

    if (activatedNeuronNames.empty() || std::find(activatedNeuronNames.begin(), activatedNeuronNames.end(), "253bf280") != activatedNeuronNames.end())
    {
        neurons.emplace_back(sameElementNeuron);
        neurons.emplace_back(regionPairsNeuron);
        neurons.emplace_back(segmentsNeuron);
    }

    if (activatedNeuronNames.empty() || std::find(activatedNeuronNames.begin(), activatedNeuronNames.end(), "00d62c1b") != activatedNeuronNames.end())
    {
        neurons.emplace_back(pairedRegionsNeuron);
        neurons.emplace_back(memberPairedRegionsNeuron);
        neurons.emplace_back(fillRegionsNeuron);
    }

    if (activatedNeuronNames.empty() || std::find(activatedNeuronNames.begin(), activatedNeuronNames.end(), "mapNeurons") != activatedNeuronNames.end())
    {
        neurons.emplace_back(mapNeuron);
        //neurons.emplace_back(associateNeuron);
        //neurons.emplace_back(mappingNeuron);
        neurons.emplace_back(inferColorMappingNeuron);
        neurons.emplace_back(pairsNeuron);
        neurons.emplace_back(trainPairsNeuron);
    }

    if (activatedNeuronNames.empty() || std::find(activatedNeuronNames.begin(), activatedNeuronNames.end(), "flipNeurons") != activatedNeuronNames.end())
    {
        neurons.emplace_back(fliplrNeuron);
        neurons.emplace_back(flipudNeuron);
    }

    if (activatedNeuronNames.empty() || std::find(activatedNeuronNames.begin(), activatedNeuronNames.end(), "regionNeurons") != activatedNeuronNames.end())
    {
        for (auto const& p : regionNeurons)
            neurons.emplace_back(p.second);
    }

    neurons.emplace_back(inputNeuron);

    Brain brain{neurons};

    auto const connections{brain.learn(std::vector<std::any>{trainPairs.second})};

    if (connections.empty())
        return -1;

    auto const connection{connections[0]};

    std::cout << connection.string() << std::endl;

    if (utility::heuristic(connection.output(), trainPairs.second))
        return -2;

    updateRegionNeurons(regionNeurons, testPairs.first);

    inputNeuron.function() =
        [testPairs] (std::vector<std::any> const&) -> std::any
    {
        return testPairs.first;
    };

    if (utility::heuristic(connection.output(), testPairs.second))
        return -3;

    return 0;
}

TEST(TestAiCpp, 3c9b0459) //Flip left/right and flip up/down
{
    EXPECT_EQ(processTask("training", "3c9b0459", std::vector<std::string>{"flipNeurons"}), 0);
/*
    auto const taskPairs{trainTestPairs("training", "3c9b0459")};
    auto const trainPairs{inputOutputPairs(taskPairs.first)};
    auto const testPairs{inputOutputPairs(taskPairs.second)};

    Neuron const fliplrNeuron{"fliplr",
                              [] (std::vector<std::any> const& args) -> std::any
                              {
                                  auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

                                  std::vector<Eigen::MatrixXi> r;
                                  r.reserve(v.size());

                                  for (auto const& x : v)
                                      r.emplace_back(fliplr(x));

                                  return r;
                              }, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>)}, typeid(std::vector<Eigen::MatrixXi>)};
    Neuron const flipudNeuron{"flipud",
                              [] (std::vector<std::any> const& args) -> std::any
                              {
                                  auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

                                  std::vector<Eigen::MatrixXi> r;
                                  r.reserve(v.size());

                                  for (auto const& x : v)
                                      r.emplace_back(flipud(x));

                                  return r;
                              }, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>)}, typeid(std::vector<Eigen::MatrixXi>)};
    Neuron inputNeuron{"input",
                       [trainPairs] (std::vector<std::any> const&) -> std::any
                       {
                           return trainPairs.first;
                       }, std::vector<std::type_index>{}, typeid(std::vector<Eigen::MatrixXi>)};

    std::vector<std::reference_wrapper<Neuron const> > neurons;
    neurons.emplace_back(fliplrNeuron);
    neurons.emplace_back(flipudNeuron);
    neurons.emplace_back(inputNeuron);

    Brain brain{neurons};

    auto const connections{brain.learn(std::vector<std::any>{trainPairs.second}, 2)};

    EXPECT_TRUE(connections.size());

    auto const connection{connections[0]};
    auto const s{connection.string()};

    EXPECT_TRUE(s == "fliplr(flipud(input))" || s == "flipud(fliplr(input))");

    EXPECT_TRUE(!heuristic(connection.output(), trainPairs.second));

    inputNeuron.function() =
        [testPairs] (std::vector<std::any> const&) -> std::any
        {
            return testPairs.first;
        };

    EXPECT_TRUE(!heuristic(connection.output(), testPairs.second));*/
}

TEST(TestAiCpp, 0d3d703e) //Color mapping
{
    EXPECT_EQ(processTask("training", "0d3d703e", std::vector<std::string>{"digitNeurons", "mapNeurons"}), 0);
/*
    auto const taskPairs{trainTestPairs("training", "0d3d703e")};
    auto const trainPairs{inputOutputPairs(taskPairs.first)};
    auto const testPairs{inputOutputPairs(taskPairs.second)};

    std::vector<Neuron> digitNeurons;
    digitNeurons.reserve(10);

    for (int i{0}; i < 10; ++i)
        digitNeurons.emplace_back(Neuron{std::to_string(i), [i] (std::vector<std::any> const& args) -> std::any { return i; }, std::vector<std::type_index>{}, typeid(int)});

    Neuron const mapNeuron{"map",
                           [] (std::vector<std::any> const& args) -> std::any
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
                           }, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>), typeid(std::map<int, int>)}, typeid(std::vector<Eigen::MatrixXi>)};
    Neuron const mappingNeuron{"mapping", [] (std::vector<std::any> const&) -> std::any { return std::map<int, int>{}; }, std::vector<std::type_index>{}, typeid(std::map<int, int>)};
    Neuron const associateNeuron{"associate",
                                 [] (std::vector<std::any> const& args) -> std::any
                                 {
                                    auto m{std::any_cast<std::map<int, int> >(args[0])};
                                    auto const a{std::any_cast<int>(args[1])};
                                    auto const b{std::any_cast<int>(args[2])};

                                    m[a] = b;

                                    return m;
                                 }, std::vector<std::type_index>{typeid(std::map<int, int>), typeid(int), typeid(int)}, typeid(std::map<int, int>)};
    Neuron const inferColorMappingNeuron{"inferColorMapping",
                                         [] (std::vector<std::any> const& args) -> std::any
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
                                         }, std::vector<std::type_index>{typeid(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >)}, typeid(std::map<int, int>)};
    Neuron const pairsNeuron{"pairs",
                             [taskPairs] (std::vector<std::any> const& args) -> std::any
                             {
                                 auto const v{std::any_cast<std::vector<Eigen::MatrixXi> >(args[0])};

                                 if (taskPairs.first.size() != v.size())
                                     return std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >{};

                                 auto pairs{taskPairs.first};

                                 for (size_t i{0}; i < pairs.size(); ++i)
                                     pairs[i].first = v[i];

                                 return pairs;
                             }, std::vector<std::type_index>{typeid(std::vector<Eigen::MatrixXi>)}, typeid(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >)};
    Neuron const trainPairsNeuron{"trainPairs",
                                  [taskPairs] (std::vector<std::any> const& args) -> std::any
                                  {
                                      return taskPairs.first;
                                  }, std::vector<std::type_index>{}, typeid(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> >)};
    Neuron inputNeuron{"input",
                       [trainPairs] (std::vector<std::any> const&) -> std::any
                       {
                           return trainPairs.first;
                       }, std::vector<std::type_index>{}, typeid(std::vector<Eigen::MatrixXi>)};

    std::vector<std::reference_wrapper<Neuron const> > neurons;
    neurons.insert(neurons.end(), std::ranges::begin(digitNeurons), std::ranges::end(digitNeurons));
    neurons.emplace_back(mapNeuron);
    neurons.emplace_back(associateNeuron);
    neurons.emplace_back(mappingNeuron);
    neurons.emplace_back(inferColorMappingNeuron);
    neurons.emplace_back(pairsNeuron);
    neurons.emplace_back(trainPairsNeuron);
    neurons.emplace_back(inputNeuron);

    Connection const mappingConnection{mappingNeuron, std::vector<std::any>{}};
    Connection const inputConnection{inputNeuron, std::vector<std::any>{}};

    Connection c{associateNeuron, std::vector<std::any>{mappingConnection, std::type_index(typeid(int)), std::type_index(typeid(int))}};

    for (int i{0}; i < 9; ++i)
        c = Connection{associateNeuron, std::vector<std::any>{c, std::type_index(typeid(int)), std::type_index(typeid(int))}};

    c = Connection{mapNeuron, std::vector<std::any>{inputConnection, c}};

    EXPECT_EQ(c.depth(), 11);

    std::string dot{"digraph ConnectionTree {\n"};
    dot += "node [shape=circle, style=filled, fillcolor=lightgray];\n";

    auto const p{c.dot()};
    dot += p.first;
    dot += "}\n";

    std::map<std::type_index, std::string> nameMap;
    nameMap[typeid(std::vector<Eigen::MatrixXi>)] = "vector<MatrixXi>";
    nameMap[typeid(Eigen::MatrixXi)] = "MatrixXi";
    nameMap[typeid(std::map<int, int>)] = "map<int,int>";

    for (auto const& p : nameMap)
        boost::algorithm::replace_all(dot, p.first.name(), p.second);

    std::ofstream ofs{"mapping_connection.dot"};
    ofs << dot;
    ofs.close();

    Brain brain{neurons};

    auto const connections{brain.learn(std::vector<std::any>{trainPairs.second})};//, 5)};

    EXPECT_TRUE(connections.size());

    auto const connection{connections[0]};

    EXPECT_TRUE(!heuristic(connection.output(), trainPairs.second));
    EXPECT_EQ(connection.string(), "map(input, inferColorMapping(trainPairs))");

    inputNeuron.function() =
        [testPairs] (std::vector<std::any> const&) -> std::any
    {
        return testPairs.first;
    };

    EXPECT_TRUE(!heuristic(connection.output(), testPairs.second));*/
}

TEST(TestAiCpp, 253bf280) //Draw colored segment between pixels that have same x or y coordinates
{
    EXPECT_EQ(processTask("training", "253bf280", std::vector<std::string>{"digitNeurons", "boolNeurons", "regionNeurons", "253bf280"}), 0);
}
