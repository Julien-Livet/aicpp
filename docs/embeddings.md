---
layout: default
title: Program Embeddings
---

## Objective

aicpp contains a learned program transformer.

We investigate whether the resulting embedding space exhibits
structured organization beyond superficial syntactic similarity.

## Experimental setup

- 9,998 programs
- model trained on more 100 target programs
- embedding dimension: 256
- t-SNE
- UMAP

## t-SNE

![2D t-SNE](assets/embeddings_program_tsne_10k.png)

[3D t-SNE](assets/embeddings_program_tsne_10k.html)

## UMAP

![2D UMAP](assets/embeddings_program_umap_10k.png)

[3D UMAP](assets/embeddings_program_umap_10k.html)

## Preliminary observation

Both projections reveal multiple structured regions in the learned
program representation.

Programs sharing the same root primitive do not necessarily form
isolated clusters, suggesting that the representation may capture
structure beyond the root operation.

## Limitations

These visualizations alone do not establish semantic organization.

Future experiments will measure:

- syntax distance
- behavioral distance
- embedding distance
- clustering stability
- representation evolution during training
