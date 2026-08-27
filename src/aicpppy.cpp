#include <fstream>
#include <functional>
#include <future>
#include <optional>
#include <random>
#include <thread>

#include <Eigen/Core>

#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "aicpp/Brain.h"
#include "aicpp/Connection.h"
#include "aicpp/HodelDslSystem.h"
#include "aicpp/Hodel.h"

namespace py = pybind11;

using namespace aicpp;

Eigen::MatrixXd to_eigen(hodel::GridType const& v)
{
    if (v.empty())
        return Eigen::MatrixXd{};

    auto const rows = static_cast<int>(v.size());
    auto const cols = static_cast<int>(v[0].size());

    Eigen::MatrixXd mat(rows, cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            mat(i, j) = v[i][j];
    }

    return mat;
}

double size_cost(hodel::GridType const& x, hodel::GridType const& y)
{
    Eigen::Vector2d const xs{static_cast<double>(x.size()), x.empty() ? 0 : static_cast<double>(x[0].size())};
    Eigen::Vector2d const ys{static_cast<double>(y.size()), y.empty() ? 0 : static_cast<double>(y[0].size())};

    return (xs - ys).norm();
}

int total_sum(hodel::GridType const& v)
{
    int s{0};

    for (const auto& row : v)
        s += std::accumulate(row.begin(), row.end(), 0);

    return s;
}

double value_cost(hodel::GridType const& x, hodel::GridType const& y)
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

double pixel_overlap_cost(hodel::GridType const& x, hodel::GridType const& y)
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

    if (!total)
        return 0.0;

    return 1.0 - (static_cast<double>(matches) / total);
}

using BoundingBox = std::tuple<int, int, int, int>;

std::optional<BoundingBox> bounding_box(hodel::GridType const& arr)
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

double bounding_box_cost(hodel::GridType const& x, hodel::GridType const& y)
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
    hodel::GridType x_;
    hodel::GridType y_;

    if (x.type() == typeid(hodel::GridType))
        x_ = std::any_cast<hodel::GridType>(x);
    else if (x.type() == typeid(hodel::Piece))
    {
        auto const& piece = std::any_cast<hodel::Piece>(x);

        if (std::holds_alternative<hodel::GridType>(piece))
            x_ = std::get<hodel::GridType>(piece);
    }
    else if (x.type() == typeid(hodel::Element))
    {
        auto const& element = std::any_cast<hodel::Element>(x);

        if (std::holds_alternative<hodel::GridType>(element))
            x_ = std::get<hodel::GridType>(element);
    }

    if (y.type() == typeid(hodel::GridType))
        y_ = std::any_cast<hodel::GridType>(y);
    else if (y.type() == typeid(hodel::Piece))
    {
        auto const& piece = std::any_cast<hodel::Piece>(y);

        if (std::holds_alternative<hodel::GridType>(piece))
            y_ = std::get<hodel::GridType>(piece);
    }
    else if (y.type() == typeid(hodel::Element))
    {
        auto const& element = std::any_cast<hodel::Element>(y);

        if (std::holds_alternative<hodel::GridType>(element))
            y_ = std::get<hodel::GridType>(element);
    }

    return size_cost(x_, y_) + bounding_box_cost(x_, y_) + pixel_overlap_cost(x_, y_) + value_cost(x_, y_);
}

template <typename T>
struct VectorHash
{
    std::size_t operator()(std::vector<T> const& v) const
    {
        std::size_t seed = 0;

        for (auto const& x : v)
        {
            seed ^= std::hash<T>{}(x)
                  + 0x9e3779b9
                  + (seed << 6)
                  + (seed >> 2);
        }

        return seed;
    }
};

template <typename T>
struct std::hash<std::vector<T> >
{
    std::size_t operator()(std::vector<T> const& v) const
    {
        return VectorHash<T>{}(v);
    }
};

class ConnectionBuilder
{
    public:
        ConnectionBuilder(std::map<std::string, Neuron> const& variableNeurons,
                          std::map<std::string, Neuron> const& primitiveNeurons) : variableNeurons_{variableNeurons}, primitiveNeurons_{primitiveNeurons}
        {
        }

        std::vector<std::string> validNames(std::type_index const& type) const
        {
            std::set<std::string> names;

            if (iNeuron_.outputType() == type)
                names.emplace(iNeuron_.name());

            for (auto const& [name, neuron] : variableNeurons_)
            {
                if (neuron.outputType() == type)
                    names.emplace(neuron.name());
            }

            if (depth_)
            {
                bool finish{false};

                if (!connection_ || connection_->nextLeafDepth(0, finish) < depth_)
                {
                    for (auto const& [name, neuron] : primitiveNeurons_)
                    {
                        if (neuron.outputType() == type)
                            names.emplace(neuron.name());
                    }
                }
            }

            if (type != typeid(hodel::Callable) && names.contains("identity"))
                names.erase("identity");

            return std::vector<std::string>{names.begin(), names.end()};
        }

        std::vector<std::string> availableNames() const
        {
            if (done())
                return {};

            return validNames(nextType().value());
        }

        void reset(size_t depth)
        {
            depth_ = depth;
            connection_.reset();
        }

        std::optional<std::type_index> nextType() const
        {
            if (!connection_)
                return typeid(hodel::GridType);

            auto const inputs(connection_->leafInputs());

            if (inputs.empty())
                return {};

            return std::any_cast<std::type_index>(inputs.front());
        }

        bool done() const
        {
            return !nextType().has_value();
        }

        std::string program() const
        {
            if (!connection_)
                return {};

            return connection_->string();
        }

        bool applyName(std::string const& name)
        {
            if (done())
                return false;

            std::vector<std::reference_wrapper<Neuron const> > neurons;

            if (name == iNeuron_.name())
                neurons.emplace_back(iNeuron_);

            for (auto const& [n, neuron] : variableNeurons_)
            {
                if (name == neuron.name())
                    neurons.emplace_back(neuron);
            }

            if (depth_)
            {
                bool finish{false};

                if (!connection_ || connection_->nextLeafDepth(0, finish) < depth_)
                {
                    for (auto const& [n, neuron] : primitiveNeurons_)
                    {
                        if (name == neuron.name())
                            neurons.emplace_back(neuron);
                    }
                }
            }

            decltype(neurons) result;
            result.reserve(neurons.size());
            auto const type{nextType()};

            for (auto const& neuron : neurons)
            {
                if (type == neuron.get().outputType())
                    result.emplace_back(neuron);
            }

            if (result.empty())
                return false;

            std::random_device rd;

            std::shuffle(result.begin(), result.end(), rd);

            if (!connection_)
            {
                auto const& inputTypes(result.front().get().inputTypes());
                std::vector<std::any> inp;
                inp.reserve(inputTypes.size());

                for (auto const& type : inputTypes)
                    inp.emplace_back(type);
                
                connection_ = std::make_unique<Connection>(result.front().get(), inp);
                    
                return true;
            }

            auto const& inputTypes(result.front().get().inputTypes());
            std::vector<std::any> inp;
            inp.reserve(inputTypes.size());

            for (auto const& type : inputTypes)
                inp.emplace_back(type);

            auto const ok{connection_->applyNextLeaf(Connection{result.front().get(), inp})};

            assert(ok);

            return true;
        }
        
        Connection& connection() const
        {
            if (!connection_)
                throw std::runtime_error{"Invalid connection"};

            return *connection_;
        }

        bool valid() const
        {
            if (!done())
                return false;

            auto const s{connection_->string()};
            
            return s.contains("(I)") || s.contains(", I)") || s.contains(", I,") || s.contains(", I)"); 
        }

    private:
        std::map<std::string, Neuron> const& variableNeurons_;
        std::map<std::string, Neuron> const& primitiveNeurons_;
        std::unique_ptr<Connection> connection_;
        Neuron iNeuron_{"I", [] (std::vector<std::any> const&) -> std::any { return std::any{}; }, std::vector<std::type_index>{}, typeid(hodel::GridType)};
        size_t depth_;
};

class Engine
{
    public:
        Engine(std::string const& dataString)
        {
            std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > variableNeuronsByOutputType;

            for (auto const& variable : variableNeurons_)
                variableNeuronsByOutputType[variable.second.outputType()].emplace_back(variable.second);

            variableNeuronsByOutputType[iNeuron_.outputType()].emplace_back(iNeuron_);

            std::map<std::type_index, std::vector<std::reference_wrapper<Neuron const> > > primitiveNeuronsByOutputType;

            for (auto const& primitive : primitiveNeurons_)
                primitiveNeuronsByOutputType[primitive.second.outputType()].emplace_back(primitive.second);

            std::vector<std::reference_wrapper<Neuron const> > neurons;

            for (auto const& [type, v] : variableNeuronsByOutputType)
                neurons.insert(neurons.end(), v.begin(), v.end());

            for (auto const& [type, v] : primitiveNeuronsByOutputType)
                neurons.insert(neurons.end(), v.begin(), v.end());

            brain_ = std::make_unique<Brain>(neurons);

            {
                std::ifstream ifs{dataString + "_connections.json"};
                std::ostringstream buffer;

                buffer << ifs.rdbuf();

                boost::json::value value = boost::json::parse(buffer.str());

                connections_ = brain_->fromJson(value);
            }

            {
                std::ifstream ifs{dataString + "_grids.json"};
                std::ostringstream buffer;

                buffer << ifs.rdbuf();

                boost::json::value value = boost::json::parse(buffer.str());

                grids_.clear();
                std::set<size_t> indexes;

                {
                    size_t i{0};

                    auto const json_grids = value.is_object() ? value.at("grids").as_array() : value.as_array()[0].at("grids").as_array();

                    for (auto const& json_grid : json_grids)
                    {
                        auto const json_rows = json_grid.as_array();

                        hodel::GridType grid;

                        for (auto const& json_row : json_rows)
                        {
                            std::vector<hodel::IntegerType> row;

                            for (auto const& json_val : json_row.as_array())
                                row.emplace_back(json_val.as_int64());

                            grid.emplace_back(row);
                        }

                        std::unordered_set<hodel::GridType> inputs;
                        std::vector<hodel::GridType> outputs;

                        std::vector<std::function<std::any(std::vector<std::any>)> > const functions{hodel::identity, hodel::rot90, hodel::rot180, hodel::rot270, hodel::hmirror, hodel::vmirror, hodel::cmirror, hodel::dmirror};

                        for (auto const& f1 : functions)
                        {
                            for (auto const& f2 : functions)
                                inputs.emplace(std::any_cast<hodel::GridType>(f1({f2({grid})})));
                        }

                        for (auto const& input : inputs)
                        {
                            try
                            {
                                iNeuron_.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };

                                auto const output{std::any_cast<hodel::GridType>(connections_.at(i).output())};

                                if (output != input && !output.empty())
                                    outputs.emplace_back(input);
                            }
                            catch (std::exception const&)
                            {
                            }
                        }

                        if (outputs.size() < 3)
                            indexes.emplace(i);
                        else
                        {
                            std::random_device rd;

                            std::shuffle(outputs.begin(), outputs.end(), rd);

                            std::uniform_int_distribution<size_t> dist(3, std::min(outputs.size(), decltype(outputs.size())(6)));

                            std::vector<hodel::GridType> selectedOutputs;

                            for (size_t j = 0; j < dist(rd); ++j)
                                selectedOutputs.emplace_back(outputs[j]);

                            grids_.emplace_back(selectedOutputs);
                        }

                        ++i;
                    }
                }

                std::vector<Connection> newConnections;
                newConnections.reserve(connections_.size());
                iNeurons_.reserve(connections_.size());

                for (size_t i = 0; i < connections_.size(); ++i)
                {
                    if (!indexes.contains(i))
                    {
                        iNeurons_.emplace_back("I", [] (std::vector<std::any> const&) -> std::any { return std::any{}; }, std::vector<std::type_index>{}, typeid(hodel::GridType));

                        auto const ok{connections_[i].replace(iNeurons_.back())};
                        
                        assert(ok);

                        newConnections.emplace_back(connections_[i]);
                    }
                }

                connections_ = newConnections;
            }
        }

        ConnectionBuilder& connectionBuilder()
        {
            return connectionBuilder_;
        }

        size_t count() const
        {
            return connections_.size();
        }

        std::vector<std::pair<double, std::string> > trajectory(size_t i)
        {
            assert(i < connections_.size());

            auto const inputs{grids(i)};
            std::vector<hodel::GridType> outputs;
            outputs.reserve(inputs.size());

            for (auto const& input : inputs)
            {
                iNeurons_.at(i).function() = [input] (std::vector<std::any> const&) -> std::any { return input; };
                outputs.emplace_back(std::any_cast<hodel::GridType>(connections_.at(i).output()));
            }

            auto const compute{[inputs, outputs] (std::reference_wrapper<Connection> connection, std::reference_wrapper<Neuron> iNeuron) -> std::optional<std::pair<double, std::string> >
                {
                    double cost{0.0};

                    for (size_t j{0}; j < inputs.size(); ++j)
                    {
                        auto const& input{inputs[j]};
                        auto const& output{outputs[j]};

                        iNeuron.get().function() = [input] (std::vector<std::any> const&) -> std::any { return input; }, std::vector<std::type_index>{}, typeid(hodel::GridType);

                        try
                        {
                            auto const o{std::any_cast<hodel::GridType>(connection.get().output())};

                            cost += arcHeuristic(o, output);
                        }
                        catch (std::exception const&)
                        {
                            cost = -1.0;
                        }
                    }

                    if (cost < 0.0)
                        return {};

                    return std::make_pair(cost, connection.get().string());
                }
            };

            std::vector<std::future<std::optional<std::pair<double, std::string> > > > futures;
            futures.reserve(connections_.size());

            for (size_t i{0}; i < connections_.size(); ++i)
                futures.emplace_back(std::async(std::launch::async, compute, std::ref(connections_.at(i)), std::ref(iNeurons_.at(i))));

            std::vector<std::pair<double, std::string> > result;
            result.reserve(connections_.size());

            for (auto& future : futures)
            {
                auto const o{future.get()};

                if (o.has_value())
                    result.emplace_back(o.value());
            }

            std::sort(result.begin(), result.end(),
                      [] (auto const& a, auto const& b)
                      {
                          if (a.first == b.first)
                              return a.second.size() < b.second.size();

                          return a.first < b.first;
                      });

            auto const df = dfIdentity(i);
            double identityCost{0.0};

            for (auto const& row : df)
                identityCost += row.front();

            auto const it{std::lower_bound(result.begin(), result.end(), identityCost, [] (auto const& a, double val) { return a.first < val; })};;

            result.erase(it, result.end());

            return result;
        }

        std::vector<hodel::GridType> const& grids(size_t i) const
        {
            return grids_.at(i);
        }

        std::string program(size_t i) const
        {
            return connections_.at(i).string();
        }

        std::vector<size_t> orderedIndexes() const
        {
            std::vector<std::future<std::string> > futures;
            futures.reserve(connections_.size());

            auto const compute{[] (Connection const& connection) -> std::string { return connection.string(); }};

            for (auto const& connection : connections_)
                futures.emplace_back(std::async(std::launch::async, compute, connection));

            std::vector<std::pair<size_t, std::string> > v;
            v.reserve(connections_.size());

            for (size_t i{0}; i < futures.size(); ++i)
                v.emplace_back(i, futures.at(i).get());

            std::sort(v.begin(), v.end(),
                      [] (auto const& x, auto const& y) -> bool
                      {
                          if (x.second.size() == y.second.size())
                              return x.second < y.second;

                          return x.second.size() < y.second.size();
                      });

            std::vector<size_t> indexes;
            indexes.reserve(v.size());

            for (auto const& p : v)
                indexes.emplace_back(p.first);

            return indexes;
        }

        std::vector<std::vector<double> > dfConnectionBuilder(size_t i)
        {
            assert(i < connections_.size());

            auto const inputs{grids(i)};
            std::vector<hodel::GridType> outputs;
            outputs.reserve(inputs.size());

            for (auto const& input : inputs)
            {
                iNeurons_.at(i).function() = [input] (std::vector<std::any> const&) -> std::any { return input; };
                outputs.emplace_back(std::any_cast<hodel::GridType>(connections_.at(i).output()));
            }

            auto connection{connectionBuilder_.connection()};

            auto const ok{connection.replace(iNeurons_.at(i))};

            assert(ok);

            std::vector<std::vector<double> > result;

            for (size_t j{0}; j < inputs.size(); ++j)
            {
                auto const& input{inputs[j]};
                auto const& output{outputs[j]};

                iNeurons_.at(i).function() = [input] (std::vector<std::any> const&) -> std::any { return input; };

                auto const o{std::any_cast<hodel::GridType>(connection.output())};

                result.emplace_back(std::vector<double>{arcHeuristic(o, output), size_cost(o, output), bounding_box_cost(o, output), pixel_overlap_cost(o, output), value_cost(o, output)});
            }

            return result;
        }

        std::vector<std::vector<double> > dfConnectionBuilderVsPairs(std::vector<hodel::GridType> const& inputs, std::vector<hodel::GridType> const& outputs)
        {
            assert(inputs.size() == outputs.size());

            auto connection{connectionBuilder_.connection()};

            auto const ok{connection.replace(iNeuron_)};

            assert(ok);

            std::vector<std::vector<double> > result;

            for (size_t j{0}; j < inputs.size(); ++j)
            {
                auto const& input{inputs[j]};
                auto const& output{outputs[j]};

                iNeuron_.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };

                auto const o{std::any_cast<hodel::GridType>(connection.output())};

                result.emplace_back(std::vector<double>{arcHeuristic(o, output), size_cost(o, output), bounding_box_cost(o, output), pixel_overlap_cost(o, output), value_cost(o, output)});
            }

            return result;
        }

        std::vector<std::vector<double> > dfIdentity(size_t i)
        {
            assert(i < connections_.size());

            auto const inputs{grids(i)};
            std::vector<hodel::GridType> outputs;
            outputs.reserve(inputs.size());

            for (auto const& input : inputs)
            {
                iNeurons_.at(i).function() = [input] (std::vector<std::any> const&) -> std::any { return input; };
                outputs.emplace_back(std::any_cast<hodel::GridType>(connections_.at(i).output()));
            }

            std::vector<std::vector<double> > result;
            Connection const identityConnection{iNeuron_, {}};

            for (size_t j{0}; j < inputs.size(); ++j)
            {
                auto const& input{inputs[j]};
                auto const& output{outputs[j]};

                iNeuron_.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };

                auto const o{std::any_cast<hodel::GridType>(identityConnection.output())};

                result.emplace_back(std::vector<double>{arcHeuristic(o, output), size_cost(o, output), bounding_box_cost(o, output), pixel_overlap_cost(o, output), value_cost(o, output)});
            }

            return result;
        }

        std::vector<std::vector<double> > dfIdentityVsPairs(std::vector<hodel::GridType> const& inputs, std::vector<hodel::GridType> const& outputs)
        {
            assert(inputs.size() == outputs.size());

            std::vector<std::vector<double> > result;
            Connection const identityConnection{iNeuron_, {}};

            for (size_t j{0}; j < inputs.size(); ++j)
            {
                auto const& input{inputs[j]};
                auto const& output{outputs[j]};

                iNeuron_.function() = [input] (std::vector<std::any> const&) -> std::any { return input; };

                auto const o{std::any_cast<hodel::GridType>(identityConnection.output())};

                result.emplace_back(std::vector<double>{arcHeuristic(o, output), size_cost(o, output), bounding_box_cost(o, output), pixel_overlap_cost(o, output), value_cost(o, output)});
            }

            return result;
        }

        std::vector<hodel::GridType> outputs(size_t i)
        {
            assert(i < connections_.size());

            auto const inputs{grids(i)};
            std::vector<hodel::GridType> outputs;
            outputs.reserve(inputs.size());

            for (auto const& input : inputs)
            {
                iNeurons_.at(i).function() = [input] (std::vector<std::any> const&) -> std::any { return input; };
                outputs.emplace_back(std::any_cast<hodel::GridType>(connections_.at(i).output()));
            }

            return outputs;
        }

    private:
        std::map<std::string, Neuron> const variableNeurons_{hodelDslVariableNeurons()};
        std::map<std::string, Neuron> const primitiveNeurons_{hodelDslPrimitiveNeurons()};
        Neuron iNeuron_{"I", [] (std::vector<std::any> const&) -> std::any { return std::any{}; }, std::vector<std::type_index>{}, typeid(hodel::GridType)};
        std::vector<Neuron> iNeurons_;
        std::unique_ptr<Brain> brain_;
        std::vector<Connection> connections_;
        std::vector<std::vector<hodel::GridType> > grids_;
        ConnectionBuilder connectionBuilder_{variableNeurons_, primitiveNeurons_};
};

PYBIND11_MODULE(aicpppy, m)
{
    py::class_<Engine>(m, "Engine")
        .def(py::init<std::string const&>())
        .def("count", &Engine::count)
        .def("trajectory", &Engine::trajectory)
        .def("grids", &Engine::grids)
        .def("program", &Engine::program)
        .def("orderedIndexes", &Engine::orderedIndexes)
        .def("connectionBuilder", &Engine::connectionBuilder, py::return_value_policy::reference)
        .def("dfConnectionBuilder", &Engine::dfConnectionBuilder)
        .def("dfConnectionBuilderVsPairs", &Engine::dfConnectionBuilderVsPairs)
        .def("dfIdentity", &Engine::dfIdentity)
        .def("dfIdentityVsPairs", &Engine::dfIdentityVsPairs)
        .def("outputs", &Engine::outputs);

    py::class_<ConnectionBuilder>(m, "ConnectionBuilder")
        .def("validNames", &ConnectionBuilder::validNames)
        .def("availableNames", &ConnectionBuilder::availableNames)
        .def("reset", &ConnectionBuilder::reset)
        .def("nextType", &ConnectionBuilder::nextType)
        .def("done", &ConnectionBuilder::done)
        .def("program", &ConnectionBuilder::program)
        .def("applyName", &ConnectionBuilder::applyName)
        .def("valid", &ConnectionBuilder::valid);
}
