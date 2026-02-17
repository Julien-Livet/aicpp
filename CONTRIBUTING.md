# Contributing to aicpp

Thank you for your interest in contributing to **aicpp**.

aicpp is a deterministic native C++ symbolic synthesis engine guided by LLM-generated structural reductions.  
The project focuses on:

- Symbolic program synthesis
- Structural search space reduction
- Deterministic exhaustive exploration
- Native C++ compilation
- Reproducibility and explicability

Before contributing, please read this document carefully.

---

## Project Philosophy

aicpp is **not**:

- A deep learning framework
- A stochastic generative solver
- A black-box ARC solver

aicpp is:

- A deterministic symbolic engine
- Guided externally by LLM-based structural parameterization
- Fully reproducible
- Fully inspectable

Maintaining this architectural clarity is essential.

---

## Types of Contributions Welcome

### 1. New Primitives (C++)

You may propose:

- New ARC-relevant primitives
- Typed, composable transformations
- Efficient implementations

Requirements:
- Must preserve deterministic behavior
- Must include documentation
- Must compile without additional heavy dependencies
- Must include example ARC usage if applicable

---

### 2. Search Space Reduction Strategies

Improvements to:

- Heuristics
- Pruning strategies
- Structural deduplication
- Isomorphism detection
- Canonical form normalization

Contributions that reduce combinatorial explosion are particularly valuable.

---

### 3. Partial Structural Parameterization Improvements

Improvements to:

- Prompt design
- LLM output robustness
- Code generation reliability
- Reduction of verbosity

The goal is to reduce structural search space, not to replace symbolic reasoning.

---

### 4. Performance Optimizations

Improvements in:

- Compilation performance
- Memory usage
- Connection reuse
- Incremental rebuild
- Serialization efficiency

All optimizations must preserve correctness and determinism.

---

### 5. Benchmarking & Evaluation

You may contribute:

- Automated ARC benchmarking scripts
- Comparative evaluation setups
- Profiling tools
- Measurement of combinatorial reduction

---

## Contributions That Are Out of Scope

The following are generally not aligned with the project direction:

- Replacing the symbolic engine with neural inference
- Introducing non-deterministic search mechanisms
- Adding heavy ML frameworks
- Refactoring without architectural justification
- Introducing unnecessary dependencies

---

## Coding Standards

- C++17 minimum
- Use CMake
- Keep dependencies minimal
- Write clear, readable code
- Document new primitives
- Maintain type safety

---

## Development Workflow

1. Fork the repository
2. Create a feature branch
3. Implement your change
4. Ensure compilation via Docker
5. Provide a clear Pull Request description

If your contribution affects search behavior, please include:

- ARC task tested
- Performance comparison
- Before/after results

---

## Reproducibility

All contributions must:

- Build using the provided Docker setup
- Preserve deterministic behavior
- Not break existing test tasks

---

## Research & Collaboration

If you are interested in academic collaboration or deeper architectural changes:

Please open a Discussion before submitting a major Pull Request.

aicpp is evolving as a research-oriented symbolic synthesis framework, and architectural coherence is critical.

---

## Final Note

aicpp aims to explore a hybrid approach:

LLM-guided structural reduction  
+  
Deterministic symbolic native exploration  

Your contributions should strengthen this balance.

Thank you for helping improve aicpp.
