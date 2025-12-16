#ifndef AICPP_CONNECTION_H
#define AICPP_CONNECTION_H

#include <chrono>

#include "aicpp/Neuron.h"

namespace aicpp
{
    struct Node
    {
        std::string label;
        std::string tooltip;
        std::vector<Node*> children;

        Node(std::string const& label = std::string{},
             std::string const& tooltip = std::string{},
             std::vector<Node*> const& children = std::vector<Node*>{}) : label{label}, tooltip{tooltip}, children{children}
        {
        }
    };

    void freeDot(Node* node);
    void writeDot(Node* node, std::ostream& out, size_t& counter, std::string const& parent = "");

    class Brain;

    class Connection
    {
        public:
            bool activated{true};
            std::chrono::time_point<std::chrono::system_clock> timeStamp{std::chrono::system_clock::now()};
            double weight{1.0};

            Connection() = default;
            Connection(std::vector<ConnectionInput> const& inputs, size_t neuronId, double weight = 1.0);
            std::vector<ConnectionInput> const& inputs() const;
            size_t neuronId() const;
            bool similar(Connection const& other) const;
            std::string string(Brain const& brain) const;
            std::string dot(Brain const& brain) const;

        private:
            void updateNode_(Brain const& brain, Node* node) const;

            std::vector<ConnectionInput> inputs_;
            size_t neuronId_;
    };
}

#endif // AICPP_CONNECTION_H
