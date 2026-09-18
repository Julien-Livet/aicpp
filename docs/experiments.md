---
layout: default
title: Experiments
---

## Motivation

aicpp is not only intended to learn mappings from tasks to programs.

A central hypothesis is that training may also modify how efficiently
the model explores the program space.

## Sequential learning

Tasks are presented sequentially.

After solving one task, the model retains the learned parameters
and continues with the next task.

This makes it possible to study whether previous experience reduces
the cost of subsequent program synthesis.

## Search cost

We measure ...

- synthesis time
- number of explored programs
- number of iterations
- cost of the best candidate
- number of programs discovered
- memory usage

## Preliminary observations

...