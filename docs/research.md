---
layout: default
title: Research
---

## Motivation

Many reasoning problems can be expressed as transformations,
programs, plans or structured sequences of operations.

Neural models are effective at learning representations and
guiding decisions, while symbolic systems provide explicit,
executable and verifiable structures.

aicpp explores the combination of these two approaches.

## Research question

How can neural representations guide the search for executable
symbolic programs efficiently while preserving their structure,
interpretability and verifiability?

## Core hypothesis

Instead of learning to directly predict an answer, a model can
learn to navigate a structured program space.

## Three research axes

### 1. Representation

Learn representations of both:

- problem instances
- symbolic programs

### 2. Search

Use neural predictions to guide a constrained symbolic search.

### 3. Experience reuse

Study whether experience acquired on previous synthesis problems
reduces the cost of solving subsequent problems.

## Why a DSL?

aicpp does not directly predict the output grid. Instead, it searches for
a program that describes the transformation from input to output.

A Domain-Specific Language (DSL) provides the structured space in which
this search takes place.

### Constraining the search space

The space of all possible programs is extremely large. A DSL restricts
this space to a set of operations that are syntactically valid and
meaningful for the target domain.

This constraint makes program synthesis tractable while preserving the
compositional nature of the problem.

### Executable solutions

DSL programs are executable by the aicpp symbolic engine.

This provides a direct connection between program generation and program
verification: a generated program can be executed on the task examples,
its outputs can be inspected, and its cost can be measured.

The model therefore does not need to learn the semantics of every
possible output directly. Instead, it learns to navigate a structured
space of executable transformations.

### Compositionality

Complex transformations can be constructed by composing simpler DSL
operations.

For example:

```text
trim(I)
vmirror(trim(I))
hconcat(rot90(I), rot270(I))
```

This gives the neural model access to a potentially large space of
compositions while keeping the underlying operations explicit.

### Structural constraints

The DSL also provides structural constraints during autoregressive
generation.

At each generation step, the set of valid next tokens depends on the
current program structure. This prevents the model from generating
syntactically invalid programs and reduces the effective search space.

### Interpretability and verification

Unlike a direct neural prediction, a synthesized DSL program provides an
explicit representation of the transformation that can be inspected,
executed, and verified independently of the neural model.

The DSL therefore acts as a contract between the learned component and
the symbolic execution engine:

```text
Neural model
     ↓
program generation
     ↓
DSL
     ↓
symbolic execution
     ↓
verifiable behavior
```

The purpose of the DSL is therefore not simply to restrict the model,
but to provide a structured and executable interface through which
neural guidance can be applied to symbolic program search.
