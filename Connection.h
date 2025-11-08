#ifndef CONNECTION_H
#define CONNECTION_H

#include <chrono>

#include "Neuron.h"

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

	private:
        std::vector<ConnectionInput> inputs_;
        size_t neuronId_;
};

#endif // CONNECTION_H
