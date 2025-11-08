#include "aicpp/Connection.h"

using namespace aicpp;

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
