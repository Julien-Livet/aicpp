# aicpp

## Neuro-symbolic program synthesis for structured reasoning

aicpp is an experimental neuro-symbolic system that learns to search
executable symbolic program spaces.

The project explores how neural representations can guide symbolic
program synthesis while preserving executable, inspectable and
verifiable solutions.

## The idea

Given a task and a domain-specific language (DSL), aicpp learns to
navigate a constrained program space rather than directly predicting
the final output.

```text
Problem
   ↓
Neural representation
   ↓
Program-space guidance
   ↓
Constrained program synthesis
   ↓
Executable symbolic program
   ↓
Verified solution
```

## Current research

The project currently investigates:
- neural guidance of symbolic program search
- joint representations of visual tasks and programs
- constrained autoregressive program generation
- executable DSLs
- program embeddings and latent structure
- experience reuse across sequential synthesis tasks

## ARC-AGI-2

aicpp is currently evaluated on ARC-AGI-2.

[View the ARC-AGI-2 experiments](arc-agi-2.md)

## Research results

[Results](../RESULTS.md)

[Experiments](experiments.md)

[Program embeddings](embeddings.md)

## Architecture

[Explore the architecture](architecture.md)

## Publications

[Publications and research material](publications.md)

## Source code

[GitHub repository](https://github.com/Julien-Livet/aicpp)
