---
layout: default
title: Architecture
---

```text
                    ARC task
                       │
                       ▼
                ┌─────────────┐
                │ CNN encoder │
                └──────┬──────┘
                       │
                       ▼
                Visual embedding
                       │
                       │
        ┌──────────────┴──────────────┐
        │                             │
        ▼                             ▼
 Program AST                    Cost features
        │                             │
        ▼                             ▼
   GNN encoder                  Cost encoder
        │                             │
        └──────────────┬──────────────┘
                       ▼
                Transformer decoder
                       │
                       ▼
             constrained DSL program
                       │
                       ▼
              symbolic execution
                       │
                       ▼
                  cost / score
                       │
                       ▼
                   search
```

Neural components
- CNN encoder
- GNN program encoder
- cost encoder
- Transformer decoder

Symbolic components
- typed DSL
- AST
- grammar constraints
- execution engine
- program validation
- cost evaluation

```text
I
↓
vmirror(I)
↓
trim(vmirror(I))
↓
...
↓
trim(I)
```
