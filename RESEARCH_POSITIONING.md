# Research Positioning of aicpp

This document clarifies the scientific positioning of aicpp within the broader landscape of symbolic AI, program synthesis, and neuro-symbolic systems.

aicpp is not intended as a production ARC solver.  
It is a research-oriented exploration of hybrid symbolic architectures guided by large language models.

---

# 1. Core Thesis

aicpp explores the hypothesis that:

> Large Language Models are most effective not as solvers,
> but as structural search space reducers.

Instead of generating final solutions directly,
LLMs are used to:

- Restrict the primitive space
- Suggest structural parameterizations
- Reduce combinatorial explosion

The actual solving process remains:

- Deterministic
- Symbolic
- Fully inspectable
- Native compiled C++

---

# 2. Relationship to Existing Paradigms

## Deep Learning Systems

Deep learning-based approaches:

- Learn latent representations
- Optimize parameters via gradients
- Provide limited interpretability
- Do not guarantee completeness

aicpp differs by:

- Operating on explicit symbolic structures
- Preserving determinism
- Providing explicit execution traces
- Guaranteeing exploration within bounded depth

---

## Program Synthesis (e.g., library learning systems)

Some systems learn reusable abstractions or DSL extensions.

aicpp shares similarities in:

- Compositional symbolic construction
- Potential library compression

However, it differs in that:

- The core engine is native compiled C++
- No DSL interpreter is used
- Structural guidance can be external (LLM)

---

## Neuro-Symbolic Systems

Many neuro-symbolic systems integrate neural and symbolic components jointly.

aicpp instead adopts a modular separation:

- LLM → structural prior
- Symbolic engine → deterministic solver

This separation maintains:

- Reproducibility
- Control
- Interpretability

---

# 3. Key Architectural Principles

aicpp is built upon:

- Strong typing
- Explicit compositional graphs
- Deterministic cost-based exploration
- Native compilation
- Structural reusability
- JSON-serializable reasoning artifacts

The system is designed to avoid:

- Black-box latent representations
- Opaque internal states
- Stochastic exploration

---

# 4. Scientific Contributions (Conceptual)

The primary research contributions explored by aicpp are:

1. Structural Partial Parameterization
   LLM-driven reduction of primitive space before search.

2. Deterministic Symbolic Completion
   Exhaustive bounded-depth exploration.

3. Native Compilation in Synthesis Loops
   Dynamic C++ generation + compilation.

4. Reusable Structural Memory
   Serialization and reuse of discovered connections.

5. Separation of Guidance and Reasoning
   LLM suggests; symbolic engine guarantees.

---

# 5. Research Questions Addressed

aicpp enables investigation of:

- How much can LLM structural priors reduce combinatorial explosion?
- Can deterministic engines scale with proper structural pruning?
- What is the trade-off between probabilistic guidance and symbolic guarantees?
- How does structural reuse impact synthesis scalability?
- Can hybrid systems preserve explicability without sacrificing performance?

---

# 6. Limitations

aicpp currently faces:

- Combinatorial explosion beyond depth 3 without pruning
- Heavy reliance on correct primitive design
- LLM output formatting instability
- No automated abstraction learning yet

These limitations are active research areas.

---

# 7. Long-Term Vision

The long-term vision of aicpp is to:

- Explore scalable hybrid symbolic architectures
- Combine probabilistic structural priors with deterministic solvers
- Maintain explicability and reproducibility
- Provide a research platform for structured reasoning tasks

---

# 8. Intended Audience

aicpp is intended for:

- Researchers in symbolic AI
- Program synthesis researchers
- Neuro-symbolic system designers
- ARC and abstraction benchmark researchers
- Engineers exploring deterministic reasoning systems

---

# 9. Disclaimer

aicpp is an experimental research framework.

It is not:

- A finished ARC benchmark competitor
- A deep learning replacement
- A black-box solver

Its purpose is to explore architectural hypotheses.

