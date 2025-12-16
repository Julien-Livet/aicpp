#include <sstream>

#include "aicpp/Brain.h"
#include "aicpp/Connection.h"

using namespace aicpp;

void aicpp::freeDot(Node* node)
{
    for (auto const& c: node->children)
    {
        freeDot(c);
        delete c;
    }

    node->children.clear();
}

void aicpp::writeDot(Node* node, std::ostream& out, size_t& counter, std::string const& parent)
{
    std::string current = "n" + std::to_string(counter++);

    out << "    " << current << " [label=\"" << node->label << "\", shape=circle, style=filled, tooltip=\"" << node->tooltip << "\"];\n";

    if (!parent.empty())
        out << "    " << parent << " -> " << current << ";\n";

    for (auto* child: node->children)
        writeDot(child, out, counter, current);
}

Connection::Connection(std::vector<ConnectionInput> const& inputs, size_t neuronId, double weight) : weight{weight}, inputs_{inputs}, neuronId_{neuronId}
{
}

std::vector<ConnectionInput> const& Connection::inputs() const
{
    return inputs_;
}

size_t Connection::neuronId() const
{
    return neuronId_;
}

bool Connection::similar(Connection const& other) const
{
    if (neuronId_ != other.neuronId_
        || inputs_.size() != other.inputs_.size())
        return false;

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        if (inputs_[i].index() != other.inputs_[i].index())
            return false;

        auto const* v1 = std::get_if<Connection>(&inputs_[i]);
        auto const* v2 = std::get_if<Connection>(&other.inputs_[i]);

        if (v1 && v2)
        {
            if (!v1->similar(*v2))
                return false;
        }
    }

    return true;
}

std::string Connection::string(Brain const& brain) const
{
    std::string s{brain.neuronName(neuronId_) + "("};

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        std::visit(
            [brain, &s] (auto const& value)
            {
                if constexpr (typeid(decltype(value)) == typeid(Connection))
                    s += value.string(brain);
                else if constexpr (typeid(decltype(value)) == typeid(std::reference_wrapper<AnyNeuron>))
                    std::visit([brain, &s] (auto const& neuron) { s += brain.neuronName(neuron.id); }, value.get());
                else if constexpr (typeid(decltype(value)) == typeid(std::map<double, double>))
                {
                    s += "{";

                    for (auto const& p : value)
                        s += std::to_string(p.first) + ": " + std::to_string(p.second) + ", ";

                    if (s.ends_with(", "))
                        s.resize(s.size() - 2);

                    s += "}";
                }
                else if constexpr (typeid(decltype(value)) == typeid(std::map<float, float>))
                {
                    s += "{";

                    for (auto const& p : value)
                        s += std::to_string(p.first) + ": " + std::to_string(p.second) + ", ";

                    if (s.ends_with(", "))
                        s.resize(s.size() - 2);

                    s += "}";
                }
                else if constexpr (typeid(decltype(value)) == typeid(std::map<int, int>))
                {
                    s += "{";

                    for (auto const& p : value)
                        s += std::to_string(p.first) + ": " + std::to_string(p.second) + ", ";

                    if (s.ends_with(", "))
                        s.resize(s.size() - 2);

                    s += "}";
                }
                else if constexpr (typeid(decltype(value)) == typeid(std::pair<int, int>))
                    s += "(" + std::to_string(value.first) +  ", " + std::to_string(value.second) + ")";
                else if constexpr (typeid(decltype(value)) == typeid(std::pair<size_t, size_t>))
                    s += "(" + std::to_string(value.first) +  ", " + std::to_string(value.second) + ")";
                else if constexpr (typeid(decltype(value)) == typeid(std::vector<std::pair<int, int> >))
                {
                    s += "(";

                    if (value.size())
                        s += "(" + std::to_string(value.front().first) +  ", " + std::to_string(value.front().second) + ")";

                    for (size_t i{1}; i < value.size(); ++i)
                        s += ", (" + std::to_string(value[i].first) +  ", " + std::to_string(value[i].second) + ")";

                    s += ")";
                }
                else if constexpr (typeid(decltype(value)) == typeid(std::vector<std::vector<std::pair<int, int> > >))
                {
                }
                else
                {
                    std::ostringstream oss;

                    oss << value;

                    s += oss.str();
                }
            }, inputs_[i]);

        if (i + 1 < inputs_.size())
            s += ", ";
    }

    return s + ")";
}

void Connection::updateNode_(Brain const& brain, Node* node) const
{
    //node->label = brain.neuronName(neuronId_);

    auto const n{brain.neuron(neuronId_)};

    std::string name{std::visit(
        [] (auto const& neuron)
        {
            return neuron.name();
        },
        n)};

    auto const pos{name.find("_")};

    if (pos != std::string::npos)
        name = name.substr(0, pos);

    node->label =   name;

    for (size_t i{0}; i < inputs_.size(); ++i)
    {
        std::visit(
            [brain, &node] (auto const& value)
            {
                if constexpr (typeid(decltype(value)) == typeid(Connection))
                {
                    Node* n = new Node;
                    value.updateNode_(brain, n);
                    node->children.emplace_back(n);
                }
            }, inputs_[i]);
    }
}

std::string Connection::dot(Brain const& brain) const
{
	std::ostringstream oss;

    oss << "digraph ConnectionTree {\n"
		<< "    node [shape=circle, style=filled, fillcolor=lightgray];\n"
		<< "\n";

	Node root;
    updateNode_(brain, &root);

	root.tooltip = string(brain);

	size_t counter{0};
	writeDot(&root, oss, counter);
	freeDot(&root);

	oss << "}\n";

    return oss.str();
}
