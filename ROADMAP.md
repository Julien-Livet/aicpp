# aicpp Roadmap

This roadmap describes the current state and future directions of the aicpp project.

aicpp is a deterministic symbolic synthesis engine guided by LLM-driven structural reduction.
Its objective is to explore a scalable hybrid architecture combining:

- Native C++ symbolic exploration
- Structural partial parameterization
- Deterministic exhaustive search
- Reusable learned structural patterns

---

# Current State (v1)

## Core Engine
- Deterministic symbolic search engine
- Typed neuron-based architecture
- Connection composition with cost-based ordering
- Heuristic-guided exploration
- Early stopping at best solution

## Structural Parameterization
- LLM-driven primitive selection
- Automatic C++ partial generation
- Dynamic compilation via CMake
- Engine re-execution loop

## Memory
- Brain serialization to JSON
- Connection source tracking
- Reusable connection structures

## Infrastructure
- Docker reproducibility
- Python pipeline orchestration
- ARC task integration

---

# Short-Term Goals

## 1. Advanced Combinatorial Reduction

- Canonical structural normalization
- Algebraic equivalence detection
- Commutativity pruning
- Structural hash deduplication
- Early semantic pruning (partial evaluation rejection)

Objective:
Reduce exponential growth at depth ≥ 3.

---

## 2. Heuristic Improvements

- Progressive structural scoring
- Partial output alignment scoring
- Constraint propagation during expansion
- A*-like admissible heuristics

Objective:
Improve search prioritization while preserving determinism.

---

## 3. Incremental Compilation Optimization

- Reduce rebuild overhead
- Separate stable core from generated partials
- Optional dynamic module loading

Objective:
Lower iteration time in LLM ↔ engine loop.

---

# Mid-Term Goals

## 4. Library Learning

- Automatic detection of reusable substructures
- Promotion of frequent subtrees to primitives
- Structural compression
- Learned structural abstraction

Objective:
Transition from memorization to structural abstraction.

---

## 5. Grammar-Guided Search

- Explicit typed production grammar
- Depth-controlled generation
- Grammar-level pruning

Objective:
Move from combinatorial enumeration to grammar-constrained synthesis.

---

## 6. Probabilistic Guidance Layer

- LLM-generated primitive priors
- Probability-weighted search ordering
- Deterministic weighted scheduling

Objective:
Hybrid symbolic + probabilistic exploration without losing explicability.

---

# Long-Term Research Directions

## 7. Hierarchical Task Decomposition

- Automatic detection of segmentation vs transformation tasks
- Multi-phase solving strategy
- Structured task classification

Objective:
Reduce search space via structural task recognition.

---

## 8. Meta-Structural Learning

- Learn which partial parameterizations are effective
- Store structural success patterns
- Task similarity detection
- Cross-task transfer

Objective:
Evolve from task solving to structural meta-learning.

---

## 9. Theoretical Formalization

- Formal combinatorial complexity analysis
- Guarantees on determinism and completeness
- Expressivity boundaries
- Comparative positioning vs DreamCoder / neuro-symbolic systems

Objective:
Position aicpp as a research framework.

---

# Evaluation Goals

- Full ARC benchmark automation
- Comparative analysis with and without LLM reduction
- Measurement of search space reduction factor
- Runtime scaling analysis

---

# Guiding Principles

- Determinism over stochasticity
- Explicit structures over latent representations
- Native compilation over interpreted DSL
- Reproducibility first
- Minimal dependencies
- Strong typing

---

# Vision

aicpp explores a hybrid path:

LLM as structural reducer  
+  
Symbolic engine as guaranteed solver  

The long-term goal is to build a scalable, reproducible, explicable synthesis framework capable of tackling abstraction-heavy reasoning tasks.

