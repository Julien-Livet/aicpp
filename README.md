[![Docker](https://img.shields.io/badge/Docker-ready-blue?logo=docker)](https://hub.docker.com/r/julienlivet/aicpp)
[![License](https://img.shields.io/badge/License-Apache-green)](LICENSE)
[![ARC-AGI](https://img.shields.io/badge/Benchmark-ARC--AGI-orange)](https://arcprize.org)

# About aicpp

`aicpp` is a C++ framework about network of connected neurons.
Each neuron is a function with inputs and an output.
Connections between compatible types can be allowed, i.e., a neuron with an int output can connect to another with an int input.

[Concept of connected neural network.pdf](https://github.com/user-attachments/files/25365047/Concept.of.connected.neural.network.pdf)

```
ollama pull gpt-oss:20b
git clone https://github.com/Julien-Livet/aicpp.git
cd aicpp
git clone https://github.com/arcprize/ARC-AGI-2.git
docker build -t aicpp .
docker run --rm aicpp
cd scripts
python engine.py
```
