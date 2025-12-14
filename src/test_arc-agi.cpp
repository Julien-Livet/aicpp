#include <fstream>
#include <iostream>

#include <boost/json.hpp>

#include <gtest/gtest.h>

#include "aicpp/Brain.h"

using namespace aicpp;
using namespace boost::json;

using Matrix = std::vector<std::vector<int>>;

std::string const path{"../../ARC-AGI-2-main/data"};

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

void updateMapping(std::map<int, int>& mapping, Brain const& brain, Connection const& connection)
{
    if (brain.neuronName(connection.neuronId()).find("replace") != std::string::npos)
    {
        std::visit(
            [brain, &mapping, connection] (auto const& value)
            {
                if constexpr (typeid(decltype(value)) == typeid(Connection))
                    updateMapping(mapping, brain, value);
            }, connection.inputs()[0]);

        mapping[std::any_cast<int>(brain.connectionOutput(std::get<Connection>(connection.inputs()[1])))] = std::any_cast<int>(brain.connectionOutput(std::get<Connection>(connection.inputs()[2])));
    }
}

void applyInput(Brain& brain, std::map<std::string, size_t> const& neuronIds, Eigen::MatrixXi const& input)
{
    std::get<Neuron<Eigen::MatrixXi> >(brain.neuron(neuronIds.at("input"))).function = [&input] () -> Eigen::MatrixXi { return input; };

    auto regionSet{
        [] (auto const& m, bool diagonals)
        {
            std::set<std::vector<std::pair<int, int> > > s;

            for (int i = 0; i < m.rows(); ++i)
            {
                for (int j = 0; j < m.cols(); ++j)
                {
                    auto r = region(m, std::make_pair(i, j), diagonals);

                    std::sort(r.begin(), r.end(),
                              [] (auto const& x, auto const& y) -> bool
                              {
                                  if (x.first == y.first)
                                      return x.second < y.second;

                                  return x.first < y.first;
                              }
                              );

                    if (s.find(r) == s.end())
                        s.emplace(r);
                }
            }

            return s;
        }
    };

    //Grid regions
    {
        auto const s{regionSet(input, false)};

        std::get<Neuron<std::vector<std::vector<std::pair<int, int> > > > >(brain.neuron(neuronIds.at("regions"))).function = [s] () { return std::vector<std::vector<std::pair<int, int> > >{s.begin(), s.end()}; };

        std::map<int, std::vector<std::vector<std::pair<int, int> > > > regions;

        for (int i{0}; i < 10; ++i)
            regions[i].clear();

        for (auto const& r : s)
            regions[input(r.front().first, r.front().second)].emplace_back(r);

        for (auto const& p : regions)
            std::get<Neuron<std::vector<std::vector<std::pair<int, int> > > > >(brain.neuron(neuronIds.at("r" + std::to_string(p.first)))).function = [p] () { return p.second; };
    }

    {
        auto const s{regionSet(input, true)};

        std::get<Neuron<std::vector<std::vector<std::pair<int, int> > > > >(brain.neuron(neuronIds.at("regions_"))).function = [s] () { return std::vector<std::vector<std::pair<int, int> > >{s.begin(), s.end()}; };

        std::map<int, std::vector<std::vector<std::pair<int, int> > > > regions;

        for (int i{0}; i < 10; ++i)
            regions[i].clear();

        for (auto const& r : s)
            regions[input(r.front().first, r.front().second)].emplace_back(r);

        for (auto const& p : regions)
            std::get<Neuron<std::vector<std::vector<std::pair<int, int> > > > >(brain.neuron(neuronIds.at("r_" + std::to_string(p.first)))).function = [p] () { return p.second; };
    }

    {
        auto const s1{regionSet(input, false)};
        auto const s2{regionSet(input, true)};

        std::get<Neuron<std::vector<std::vector<std::pair<int, int> > > > >(brain.neuron(neuronIds.at("allRegions"))).function = [s1, s2] ()
        {
            std::set<std::vector<std::pair<int, int> > > s{s1};

            for (auto const& v : s2)
                s.emplace(v);

            return std::vector<std::vector<std::pair<int, int> > >{s.begin(), s.end()};
        };
    }
}

bool process(std::string const& folder, std::string const& task)
{
    std::ifstream ifs{path + "/" + folder + "/" + task + ".json"};

    std::string content;

    while (ifs)
    {
        std::string line;

        std::getline(ifs, line);

        content += line + '\n';
    }

    value const jv = parse(content);

    auto const train = jv.at("train").as_array();
    std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > trainPairs;

    for (std::size_t i = 0; i < train.size(); ++i)
    {
        auto const& sample = train[i].as_object();

        trainPairs.emplace_back(std::make_pair(boostJsonToEigenMatrix(sample.at("input").as_array()),
                                               boostJsonToEigenMatrix(sample.at("output").as_array())));
    }

    auto const test = jv.at("test").as_array();
    std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > testPairs;

    for (std::size_t i = 0; i < test.size(); ++i)
    {
        auto const& sample = test[i].as_object();

        testPairs.emplace_back(std::make_pair(boostJsonToEigenMatrix(sample.at("input").as_array()),
                                               boostJsonToEigenMatrix(sample.at("output").as_array())));
    }

    Brain brain;

    std::map<std::string, size_t> neuronIds;

    auto const m{brain.addMatrices<Eigen::MatrixXi>()};
    neuronIds.insert(m.begin(), m.end());

    brain.deactivateAllModules();

    std::vector<std::string> const activatedNeurons{
        //"zero",
        //"tile",
        ///"fliplr",
        ///"flipud",
        //"place_region",
        //"hline",
        //"vline",
        //"hlineleft",
        //"hlineright",
        //"vlineup",
        //"vlinedown",
        //"fill_region_at",
        //"fill_region2_at",
        ///"replace",
        ///"map",
        //"put_matrix",
        //"put_value",
        //"fill_region",
        "fill_regions",
        //"or",
        //"and",
        //"xor",
        //"invert",
        //"dotsegment",
        ///"rot90",
        //"matrix_region",
        ///"segments"
    };

    for (auto const& p : brain.neurons())
    {
        for (auto const& s : activatedNeurons)
        {
            if (brain.neuronName(p.first).starts_with("matrices." + s))
                brain.activateNeuron(p.first);
        }
    }

    {
        ///brain.addNeuron(Neuron<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >, std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > >{[] (auto const& x) { return sameFirst(x); }, "sameFirst", "arc"});
        ///brain.addNeuron(Neuron<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >, std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > >{[] (auto const& x) { return sameSecond(x); }, "sameSecond", "arc"});
        ///brain.addNeuron(Neuron<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >, std::vector<std::vector<std::pair<int, int> > > >{[] (auto const& x) { return regionPairs(x); }, "regionPairs", "arc"});
        brain.addNeuron(Neuron<std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > >, Eigen::MatrixXi, std::vector<std::vector<std::pair<int, int> > > >{[] (auto const& a, auto const& regions) { return pairedRegions(a, regions); }, "pairedRegions", "arc"});
        brain.addNeuron(Neuron<std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > >, Eigen::MatrixXi, std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > >, int, bool>{[] (auto const& a, auto const& pairedRegions, auto const& value, bool first) { return filterValuePairedRegions(a, pairedRegions, value, first); }, "filterValuePairedRegions", "arc"});
        brain.addNeuron(Neuron<std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > >, Eigen::MatrixXi, std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > >, bool >{[] (auto const& a, auto const& pairedRegions, bool closed) { return filterClosedPairedRegions(a, pairedRegions, closed); }, "filterClosedPairedRegions", "arc"});
        brain.addNeuron(Neuron<std::vector<std::vector<std::pair<int, int> > >, std::vector<std::pair<std::vector<std::pair<int, int> >, std::vector<std::pair<int, int> > > >, bool>{[] (auto const& pairedRegions, bool first) { return memberPairedRegions(pairedRegions, first); }, "memberPairedRegions", "arc"});
    }

    std::map<int, int> mapping;

    neuronIds["input"] = brain.addNeuron(Neuron<Eigen::MatrixXi>{[] () { return Eigen::MatrixXi{}; }, "input"});
    neuronIds["mapping"] = brain.addNeuron(Neuron<std::map<int, int> >{[&mapping] () { return mapping; }, "mapping"});
    neuronIds["false"] = brain.addNeuron(Neuron<bool>{[] () { return false; }, "false", "bools.variables"});
    neuronIds["true"] = brain.addNeuron(Neuron<bool>{[] () { return true; }, "true", "bools.variables"});
    neuronIds["regions"] = brain.addNeuron(Neuron<std::vector<std::vector<std::pair<int, int> > > >{[] () { return std::vector<std::vector<std::pair<int, int> > >{}; }, "regions", "regions"});
    neuronIds["regions_"] = brain.addNeuron(Neuron<std::vector<std::vector<std::pair<int, int> > > >{[] () { return std::vector<std::vector<std::pair<int, int> > >{}; }, "regions", "regions"});
    neuronIds["allRegions"] = brain.addNeuron(Neuron<std::vector<std::vector<std::pair<int, int> > > >{[] () { return std::vector<std::vector<std::pair<int, int> > >{}; }, "regions", "regions"});

    //Grid values
    {
        std::set<int> values;

        for (int i{0}; i < 10; ++i)
            values.emplace(i);

        for (auto const& v : values)
        {
            auto const name{std::to_string(v)};
            neuronIds[name] = brain.addNeuron(Neuron<int>{[v] () { return v; }, name, "ints.variables"});
        }
    }

    //Grid regions
    {
        for (size_t i{0}; i < 10; ++i)
        {
            {
                auto const name{"r" + std::to_string(i)};
                neuronIds[name] = brain.addNeuron(Neuron<std::vector<std::vector<std::pair<int, int> > > >{[] () { return std::vector<std::vector<std::pair<int, int> > >{}; }, name, "regions"});
            }

            {
                auto const name{"r_" + std::to_string(i)};
                neuronIds[name] = brain.addNeuron(Neuron<std::vector<std::vector<std::pair<int, int> > > >{[] () { return std::vector<std::vector<std::pair<int, int> > >{}; }, name, "regions"});
            }
        }
    }

    int const timeout{10 * 60 * 1000};
    auto const time{std::chrono::system_clock::now()};
    int learnTimeout{2 * 1000};
    std::vector<Connection> connections;
    std::vector<Eigen::MatrixXi> outputs(trainPairs.size());
    double cost{1.0};

    constexpr double eps = 1.0e-6;
    constexpr size_t answerNumber{1};//{static_cast<size_t>(-1)};

    while (cost >= eps)
    {
        if ((int)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()) - std::chrono::time_point_cast<std::chrono::milliseconds>(time)).count() > timeout)
            break;

        brain.neuronTimeout = learnTimeout / 8;

        for (size_t i{0}; i < trainPairs.size(); ++i)
        {
            auto const& p{trainPairs[i]};

            applyInput(brain, neuronIds, p.first);

            auto const regions{pairedRegions(p.first, std::get<Neuron<std::vector<std::vector<std::pair<int, int> > > > >(brain.neuron(neuronIds.at("allRegions"))).function())};

            connections = brain.learn(p.second, answerNumber, -1, learnTimeout);

            brain.setConnections(connections);
        }

        auto const previousCost{cost};
        cost = 0;

        for (auto const& connection : connections)
            updateMapping(mapping, brain, connection);

        auto const& connection{connections.front()};

        for (size_t i{0}; i < trainPairs.size(); ++i)
        {
            auto const& p{trainPairs[i]};

            applyInput(brain, neuronIds, p.first);

            try
            {
                auto const newOutput{std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connection))};

                cost += heuristic(p.second, newOutput);

                outputs[i] = newOutput;
            }
            catch (std::exception const&)
            {
            }
        }

        if (std::abs(cost - previousCost) < eps)
            learnTimeout *= 2;
        else if (learnTimeout > 1000)
            learnTimeout /= 2;
    }

    cost = 0;

    for (auto const& p : testPairs)
    {
        applyInput(brain, neuronIds, p.first);

        auto const newOutput{std::any_cast<Eigen::MatrixXi>(brain.connectionOutput(connections.front()))};

        cost += heuristic(p.second, newOutput);
    }

    if (cost < eps)
        std::cout << connections.front().string(brain) << std::endl;

    return (cost < eps);
}

TEST(TestArcAgi, 00d62c1b)
{
    EXPECT_TRUE(process("training", "00d62c1b"));
}

TEST(TestArcAgi, 253bf280)
{
    EXPECT_TRUE(process("training", "253bf280"));
}

TEST(TestArcAgi, 3c9b0459)
{
    EXPECT_TRUE(process("training", "3c9b0459"));
}

TEST(TestArcAgi, 0d3d703e)
{
    EXPECT_TRUE(process("training", "0d3d703e"));
}
