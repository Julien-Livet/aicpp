# About aicpp

`aicpp` is a C++ framework about network of connected neurons.
Each neuron is a function with inputs and an output.
Connections between compatible types can be allowed, i.e., a neuron with an int output can connect to another with an int input.

```
ollama pull gpt-oss:20b
docker build -t aicpp .
docker run --rm aicpp
docker run --rm aicpp -c "python3 scripts/engine.py"
```
