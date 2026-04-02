# Task 12422b43

train solved, test solved

5 iterations

[Best program](#iteration-5-dsl-diff-1)

## Program 1

### Train scores

|        | Grid size cost          | Value cost                                                           | Pixel overlap cost                                                      | Bounding box cost                                       | Total cost                                                           |
|:-------|:------------------------|:---------------------------------------------------------------------|:------------------------------------------------------------------------|:--------------------------------------------------------|:---------------------------------------------------------------------|
| train1 | 0.0,0.0,NaN,NaN,NaN,0.0 | 18.547236990991408,11.313708498984761,NaN,NaN,NaN,15.937377450509228 | 0.20512820512820518,0.1282051282051282,NaN,NaN,NaN,0.1923076923076923   | 0.2793721182102703,0.0,NaN,NaN,NaN,0.0                  | 19.03173731432988,11.441913627189889,NaN,NaN,NaN,16.12968514281692   |
| train2 | 0.0,0.0,NaN,NaN,NaN,0.0 | 14.45683229480096,0.0,NaN,NaN,NaN,14.45683229480096                  | 0.0892857142857143,0.0,NaN,NaN,NaN,0.0892857142857143                   | 0.1411081301911679,0.0,NaN,NaN,NaN,0.1411081301911679   | 14.687226139277842,0.0,NaN,NaN,NaN,14.687226139277842                |
| train3 | 0.0,0.0,NaN,NaN,NaN,0.0 | 21.166010488516726,13.856406460551018,NaN,NaN,NaN,21.166010488516726 | 0.15873015873015872,0.09523809523809523,NaN,NaN,NaN,0.15873015873015872 | 0.17541160378448276,0.0,NaN,NaN,NaN,0.17541160378448276 | 21.500152251031366,13.951644555789112,NaN,NaN,NaN,21.500152251031366 |
| train4 | 0.0,0.0,NaN,NaN,NaN,0.0 | 22.360679774997898,0.0,NaN,NaN,NaN,14.142135623730951                | 0.23809523809523814,0.0,NaN,NaN,NaN,0.09523809523809523                 | 0.2711630721262614,0.0,NaN,NaN,NaN,0.0                  | 22.869938085219395,0.0,NaN,NaN,NaN,14.237373718969046                |
| train5 | 0.0,0.0,NaN,NaN,NaN,0.0 | 9.16515138991168,0.0,NaN,NaN,NaN,9.16515138991168                    | 0.16000000000000003,0.0,NaN,NaN,NaN,0.16000000000000003                 | 0.1414213561373095,0.0,NaN,NaN,NaN,0.1414213561373095   | 9.466572746048989,0.0,NaN,NaN,NaN,9.466572746048989                  |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |       15.748 |             0.171429 |                   0 |      15.9194 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,17 @@
 def dsl1(I):
-    O = I
+    # Global transformation: crop top (all foreground), then tile the top-5-rows-pattern (with 5->0) to fill the remainder
+    FG = objects(I, T, F, T)
+    FGinds = mapply(toindices, FG)
+    top_h = increment(lowermost(FGinds))
+    H = height(I)
+    W = width(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    bottom_h = subtract(H, top_h)
+    k = divide(bottom_h, m)
+    rep = vupscale(motif0, k)
+    top = crop(I, ORIGIN, astuple(top_h, W))
+    O = vconcat(top, rep)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,15 @@
 def dsl3(I):
-    O = I
+    # Color-based fill: repeat the last non-empty row (with 5->0) to fill all trailing background rows
+    FG = objects(I, T, F, T)
+    FGinds = mapply(toindices, FG)
+    last = lowermost(FGinds)
+    top_h = increment(last)
+    H = height(I)
+    W = width(I)
+    bottom_h = subtract(H, top_h)
+    lastrow = crop(I, astuple(last, ZERO), astuple(ONE, W))
+    lastrow0 = replace(lastrow, FIVE, ZERO)
+    rep = vupscale(lastrow0, bottom_h)
+    top = crop(I, ORIGIN, astuple(top_h, W))
+    O = vconcat(top, rep)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,16 @@
 def dsl5(I):
-    O = I
+    # Relational/structural: build a background from a vertically repeated (5->0) motif, then repaint all original foreground on top
+    W = width(I)
+    H = height(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    bottom_h = subtract(H, m)
+    k = divide(bottom_h, m)
+    rep = vupscale(motif0, k)
+    base = vconcat(motif0, rep)
+    FG = objects(I, T, F, T)
+    fused = merge(FG)
+    O = paint(base, fused)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,25 @@
 def dsl2(I):
-    # Object extraction: build a single shifted copy of the (5->0) motif placed just below the last foreground row, paint only on background
+    # Object extraction: replicate only non-5 objects from the top m rows downward
     FG = objects(I, T, F, T)
-    FGinds = mapply(toindices, FG)
-    top_h = increment(lowermost(FGinds))
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
     W = width(I)
+    H = height(I)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
-    motif = crop(I, ORIGIN, astuple(m, W))
-    motif0 = replace(motif, FIVE, ZERO)
-    base = canvas(ZERO, shape(I))
-    obj = asobject(motif0)
-    off = astuple(top_h, ZERO)
-    placed = move(base, obj, off)
-    O = underpaint(I, asobject(placed))
+    tile = crop(I, ORIGIN, astuple(m, W))
+    objs = objects(tile, T, F, T)
+    fiveobjs = colorfilter(objs, FIVE)
+    non5 = difference(objs, fiveobjs)
+    fused = merge(non5)
+    bottom_h = subtract(H, top_h)
+    k = divide(bottom_h, m)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(top_h, ZERO)
+    offs = apply(lbind(add, start), scaled)
+    copies = mapply(lbind(shift, fused), offs)
+    repobj = merge(copies)
+    O = underpaint(I, repobj)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,13 +1,22 @@
 def dsl4(I):
-    # Geometric reasoning: keep the initial motif block, append its (5->0) version vertically repeated to fill height
+    # Geometric alignment: build a full-height bottom-aligned periodic background from (5->0), then repaint original FG
     W = width(I)
     H = height(I)
+    FG = objects(I, T, F, T)
+    fusedFG = merge(FG)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
     motif = crop(I, ORIGIN, astuple(m, W))
     motif0 = replace(motif, FIVE, ZERO)
-    bottom_h = subtract(H, m)
-    k = divide(bottom_h, m)
-    rep = vupscale(motif0, k)
-    O = vconcat(motif, rep)
+    obj = asobject(motif0)
+    kfull = divide(H, m)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, kfull, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(subtract(H, multiply(m, kfull)), ZERO)
+    offs = apply(lbind(add, start), scaled)
+    copies = mapply(lbind(shift, obj), offs)
+    baseobj = merge(copies)
+    base = paint(canvas(ZERO, shape(I)), baseobj)
+    O = paint(base, fusedFG)
     return O
```

## Program 2

### Train scores

|        | Grid size cost          | Value cost                                            | Pixel overlap cost                                      | Bounding box cost                                       | Total cost                                            |
|:-------|:------------------------|:------------------------------------------------------|:--------------------------------------------------------|:--------------------------------------------------------|:------------------------------------------------------|
| train1 | 0.0,0.0,NaN,NaN,NaN,0.0 | 18.547236990991408,13.114877048604,NaN,NaN,NaN,0.0    | 0.20512820512820518,0.10256410256410253,NaN,NaN,NaN,0.0 | 0.2793721182102703,0.13968605910513515,NaN,NaN,NaN,0.0  | 19.03173731432988,13.357127210273237,NaN,NaN,NaN,0.0  |
| train2 | 0.0,0.0,NaN,NaN,NaN,0.0 | 14.45683229480096,0.0,NaN,NaN,NaN,0.0                 | 0.0892857142857143,0.0,NaN,NaN,NaN,0.0                  | 0.1411081301911679,0.0,NaN,NaN,NaN,0.0                  | 14.687226139277842,0.0,NaN,NaN,NaN,0.0                |
| train3 | 0.0,0.0,NaN,NaN,NaN,0.0 | 21.166010488516726,14.966629547095765,NaN,NaN,NaN,0.0 | 0.15873015873015872,0.07936507936507942,NaN,NaN,NaN,0.0 | 0.17541160378448276,0.08770580189224138,NaN,NaN,NaN,0.0 | 21.500152251031366,15.133700428353086,NaN,NaN,NaN,0.0 |
| train4 | 0.0,0.0,NaN,NaN,NaN,0.0 | 22.360679774997898,20.0,NaN,NaN,NaN,0.0               | 0.23809523809523814,0.19047619047619047,NaN,NaN,NaN,0.0 | 0.2711630721262614,0.2169304577010091,NaN,NaN,NaN,0.0   | 22.869938085219395,20.407406648177197,NaN,NaN,NaN,0.0 |
| train5 | 0.0,0.0,NaN,NaN,NaN,0.0 | 9.16515138991168,0.0,NaN,NaN,NaN,0.0                  | 0.16000000000000003,0.0,NaN,NaN,NaN,0.0                 | 0.1414213561373095,0.0,NaN,NaN,NaN,0.0                  | 9.466572746048989,0.0,NaN,NaN,NaN,0.0                 |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |            0 |                    0 |                   0 |            0 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,16 @@
 def dsl2(I):
-    O = I
+    # Object extraction: build a single shifted copy of the (5->0) motif placed just below the last foreground row, paint only on background
+    FG = objects(I, T, F, T)
+    FGinds = mapply(toindices, FG)
+    top_h = increment(lowermost(FGinds))
+    W = width(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    base = canvas(ZERO, shape(I))
+    obj = asobject(motif0)
+    off = astuple(top_h, ZERO)
+    placed = move(base, obj, off)
+    O = underpaint(I, asobject(placed))
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,13 @@
 def dsl4(I):
-    O = I
+    # Geometric reasoning: keep the initial motif block, append its (5->0) version vertically repeated to fill height
+    W = width(I)
+    H = height(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    bottom_h = subtract(H, m)
+    k = divide(bottom_h, m)
+    rep = vupscale(motif0, k)
+    O = vconcat(motif, rep)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,17 +1,23 @@
 def dsl1(I):
-    # Global transformation: crop top (all foreground), then tile the top-5-rows-pattern (with 5->0) to fill the remainder
+    # Global tiling of (5->0) top-motif into the background below last foreground row
     FG = objects(I, T, F, T)
-    FGinds = mapply(toindices, FG)
-    top_h = increment(lowermost(FGinds))
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
+    W = width(I)
     H = height(I)
-    W = width(I)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
     motif = crop(I, ORIGIN, astuple(m, W))
     motif0 = replace(motif, FIVE, ZERO)
+    obj = asobject(motif0)
     bottom_h = subtract(H, top_h)
     k = divide(bottom_h, m)
-    rep = vupscale(motif0, k)
-    top = crop(I, ORIGIN, astuple(top_h, W))
-    O = vconcat(top, rep)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(top_h, ZERO)
+    offs = apply(lbind(add, start), scaled)
+    copies = mapply(lbind(shift, obj), offs)
+    repobj = merge(copies)
+    O = underpaint(I, repobj)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,15 +1,25 @@
 def dsl3(I):
-    # Color-based fill: repeat the last non-empty row (with 5->0) to fill all trailing background rows
+    # Color-based fill: build bottom canvas by tiling the (5->0) motif, then append under the unchanged head
     FG = objects(I, T, F, T)
-    FGinds = mapply(toindices, FG)
-    last = lowermost(FGinds)
-    top_h = increment(last)
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
+    W = width(I)
     H = height(I)
-    W = width(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    obj = asobject(motif0)
     bottom_h = subtract(H, top_h)
-    lastrow = crop(I, astuple(last, ZERO), astuple(ONE, W))
-    lastrow0 = replace(lastrow, FIVE, ZERO)
-    rep = vupscale(lastrow0, bottom_h)
-    top = crop(I, ORIGIN, astuple(top_h, W))
-    O = vconcat(top, rep)
+    k = divide(bottom_h, m)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    offs0 = apply(lbind(add, ORIGIN), scaled)
+    copies0 = mapply(lbind(shift, obj), offs0)
+    repobj0 = merge(copies0)
+    head = crop(I, ORIGIN, astuple(top_h, W))
+    bottom_canvas = canvas(ZERO, astuple(bottom_h, W))
+    bottom_filled = paint(bottom_canvas, repobj0)
+    O = vconcat(head, bottom_filled)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,26 @@
 def dsl5(I):
-    # Relational/structural: build a background from a vertically repeated (5->0) motif, then repaint all original foreground on top
+    # Relational/structural: place multiple moved copies of the (5->0) motif onto a zero base and underpaint
+    FG = objects(I, T, F, T)
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
     W = width(I)
     H = height(I)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
     motif = crop(I, ORIGIN, astuple(m, W))
     motif0 = replace(motif, FIVE, ZERO)
-    bottom_h = subtract(H, m)
+    obj = asobject(motif0)
+    bottom_h = subtract(H, top_h)
     k = divide(bottom_h, m)
-    rep = vupscale(motif0, k)
-    base = vconcat(motif0, rep)
-    FG = objects(I, T, F, T)
-    fused = merge(FG)
-    O = paint(base, fused)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(top_h, ZERO)
+    offs = apply(lbind(add, start), scaled)
+    base0 = canvas(ZERO, shape(I))
+    mover = lbind(lbind(move, base0), obj)
+    placed_grids = mapply(mover, offs)
+    placed_objs = mapply(asobject, placed_grids)
+    repobj = merge(placed_objs)
+    O = underpaint(I, repobj)
     return O
```

## Program 3

### Train scores

|        | Grid size cost          | Value cost                                                         | Pixel overlap cost                                                      | Bounding box cost                                       | Total cost                                                           |
|:-------|:------------------------|:-------------------------------------------------------------------|:------------------------------------------------------------------------|:--------------------------------------------------------|:---------------------------------------------------------------------|
| train1 | 0.0,0.0,NaN,NaN,NaN,0.0 | 18.547236990991408,18.547236990991408,NaN,NaN,NaN,17.4928556845359 | 0.20512820512820518,0.15384615384615385,NaN,NaN,NaN,0.17948717948717952 | 0.2793721182102703,0.0,NaN,NaN,NaN,0.03492151477628379  | 19.03173731432988,18.70108314483756,NaN,NaN,NaN,17.707264378799362   |
| train2 | 0.0,0.0,NaN,NaN,NaN,0.0 | 14.45683229480096,12.68857754044952,NaN,NaN,NaN,13.30413469565007  | 0.0892857142857143,0.125,NaN,NaN,NaN,0.1071428571428571                 | 0.1411081301911679,0.0,NaN,NaN,NaN,0.09407208679411193  | 14.687226139277842,12.81357754044952,NaN,NaN,NaN,13.50534963958704   |
| train3 | 0.0,0.0,NaN,NaN,NaN,0.0 | 21.166010488516726,16.0,NaN,NaN,NaN,21.908902300206645             | 0.15873015873015872,0.15873015873015872,NaN,NaN,NaN,0.19047619047619047 | 0.17541160378448276,0.0,NaN,NaN,NaN,0.04385290094612069 | 21.500152251031366,16.158730158730158,NaN,NaN,NaN,22.143231391628955 |
| train4 | 0.0,0.0,NaN,NaN,NaN,0.0 | 22.360679774997898,12.041594578792296,NaN,NaN,NaN,0.0              | 0.23809523809523814,0.23809523809523814,NaN,NaN,NaN,0.0                 | 0.2711630721262614,0.0,NaN,NaN,NaN,0.0                  | 22.869938085219395,12.279689816887533,NaN,NaN,NaN,0.0                |
| train5 | 0.0,0.0,NaN,NaN,NaN,0.0 | 9.16515138991168,6.0,NaN,NaN,NaN,9.16515138991168                  | 0.16000000000000003,0.12,NaN,NaN,NaN,0.24                               | 0.1414213561373095,0.0,NaN,NaN,NaN,0.07071067806865475  | 9.466572746048989,6.12,NaN,NaN,NaN,9.475862067980335                 |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      13.2665 |             0.171429 |           0.0409616 |      13.4789 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,15 @@
 def dsl3(I):
-    O = I
+    # Color-based fill: repeat the last non-empty row (with 5->0) to fill all trailing background rows
+    FG = objects(I, T, F, T)
+    FGinds = mapply(toindices, FG)
+    last = lowermost(FGinds)
+    top_h = increment(last)
+    H = height(I)
+    W = width(I)
+    bottom_h = subtract(H, top_h)
+    lastrow = crop(I, astuple(last, ZERO), astuple(ONE, W))
+    lastrow0 = replace(lastrow, FIVE, ZERO)
+    rep = vupscale(lastrow0, bottom_h)
+    top = crop(I, ORIGIN, astuple(top_h, W))
+    O = vconcat(top, rep)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,16 @@
 def dsl5(I):
-    O = I
+    # Relational/structural: build a background from a vertically repeated (5->0) motif, then repaint all original foreground on top
+    W = width(I)
+    H = height(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    bottom_h = subtract(H, m)
+    k = divide(bottom_h, m)
+    rep = vupscale(motif0, k)
+    base = vconcat(motif0, rep)
+    FG = objects(I, T, F, T)
+    fused = merge(FG)
+    O = paint(base, fused)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,25 @@
 def dsl2(I):
-    # Object extraction: build a single shifted copy of the (5->0) motif placed just below the last foreground row, paint only on background
+    # Object extraction: replicate only non-5 objects from the top m rows downward
     FG = objects(I, T, F, T)
-    FGinds = mapply(toindices, FG)
-    top_h = increment(lowermost(FGinds))
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
     W = width(I)
+    H = height(I)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
-    motif = crop(I, ORIGIN, astuple(m, W))
-    motif0 = replace(motif, FIVE, ZERO)
-    base = canvas(ZERO, shape(I))
-    obj = asobject(motif0)
-    off = astuple(top_h, ZERO)
-    placed = move(base, obj, off)
-    O = underpaint(I, asobject(placed))
+    tile = crop(I, ORIGIN, astuple(m, W))
+    objs = objects(tile, T, F, T)
+    fiveobjs = colorfilter(objs, FIVE)
+    non5 = difference(objs, fiveobjs)
+    fused = merge(non5)
+    bottom_h = subtract(H, top_h)
+    k = divide(bottom_h, m)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(top_h, ZERO)
+    offs = apply(lbind(add, start), scaled)
+    copies = mapply(lbind(shift, fused), offs)
+    repobj = merge(copies)
+    O = underpaint(I, repobj)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,13 +1,22 @@
 def dsl4(I):
-    # Geometric reasoning: keep the initial motif block, append its (5->0) version vertically repeated to fill height
+    # Geometric alignment: build a full-height bottom-aligned periodic background from (5->0), then repaint original FG
     W = width(I)
     H = height(I)
+    FG = objects(I, T, F, T)
+    fusedFG = merge(FG)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
     motif = crop(I, ORIGIN, astuple(m, W))
     motif0 = replace(motif, FIVE, ZERO)
-    bottom_h = subtract(H, m)
-    k = divide(bottom_h, m)
-    rep = vupscale(motif0, k)
-    O = vconcat(motif, rep)
+    obj = asobject(motif0)
+    kfull = divide(H, m)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, kfull, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(subtract(H, multiply(m, kfull)), ZERO)
+    offs = apply(lbind(add, start), scaled)
+    copies = mapply(lbind(shift, obj), offs)
+    baseobj = merge(copies)
+    base = paint(canvas(ZERO, shape(I)), baseobj)
+    O = paint(base, fusedFG)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,23 +1,21 @@
 def dsl1(I):
-    # Global tiling of (5->0) top-motif into the background below last foreground row
-    FG = objects(I, T, F, T)
-    FGI = merge(mapply(toindices, FG))
-    top_h = increment(lowermost(FGI))
+    # Global: build bottom by tiling the top m-row motif with 5->0, then append under unchanged head
     W = width(I)
     H = height(I)
+    NZ = difference(asindices(I), ofcolor(I, ZERO))
+    top_h = height(subgrid(NZ, I))
     M5 = ofcolor(I, FIVE)
     m = height(M5)
-    motif = crop(I, ORIGIN, astuple(m, W))
-    motif0 = replace(motif, FIVE, ZERO)
-    obj = asobject(motif0)
+    tile = crop(I, ORIGIN, astuple(m, W))
+    tile0 = replace(tile, FIVE, ZERO)
+    obj = asobject(tile0)
     bottom_h = subtract(H, top_h)
     k = divide(bottom_h, m)
     vec = astuple(m, ZERO)
     times = interval(ZERO, k, ONE)
-    scaled = apply(rbind(multiply, vec), times)
-    start = astuple(top_h, ZERO)
-    offs = apply(lbind(add, start), scaled)
-    copies = mapply(lbind(shift, obj), offs)
-    repobj = merge(copies)
-    O = underpaint(I, repobj)
+    offs = apply(lbind(add, astuple(top_h, ZERO)), apply(rbind(multiply, vec), times))
+    repobj = merge(mapply(lbind(shift, obj), offs))
+    head = crop(I, ORIGIN, astuple(top_h, W))
+    bottom = paint(canvas(ZERO, astuple(bottom_h, W)), repobj)
+    O = vconcat(head, bottom)
     return O
```

## Program 4

### Train scores

|        | Grid size cost          | Value cost                                           | Pixel overlap cost                                        | Bounding box cost                                                       | Total cost                                                           |
|:-------|:------------------------|:-----------------------------------------------------|:----------------------------------------------------------|:------------------------------------------------------------------------|:---------------------------------------------------------------------|
| train1 | 0.0,1.0,NaN,NaN,NaN,0.0 | 18.547236990991408,16.0,NaN,NaN,NaN,17.4928556845359 | 0.20512820512820518,150.0,NaN,NaN,NaN,0.17948717948717952 | 0.2793721182102703,0.03606092228572704,NaN,NaN,NaN,0.03492151477628379  | 19.03173731432988,167.0360609222857,NaN,NaN,NaN,17.707264378799362   |
| train2 | 0.0,2.0,NaN,NaN,NaN,0.0 | 14.45683229480096,8.0,NaN,NaN,NaN,13.30413469565007  | 0.0892857142857143,98.0,NaN,NaN,NaN,0.1071428571428571    | 0.1411081301911679,0.10101525440420066,NaN,NaN,NaN,0.09407208679411193  | 14.687226139277842,108.1010152544042,NaN,NaN,NaN,13.50534963958704   |
| train3 | 0.0,1.0,NaN,NaN,NaN,0.0 | 21.166010488516726,16.0,NaN,NaN,NaN,24.0             | 0.15873015873015872,119.0,NaN,NaN,NaN,0.23809523809523814 | 0.17541160378448276,0.04540766089803142,NaN,NaN,NaN,0.04385290094612069 | 21.500152251031366,136.04540766089804,NaN,NaN,NaN,24.281948139041358 |
| train4 | 0.0,0.0,NaN,NaN,NaN,0.0 | 22.360679774997898,5.385164807134504,NaN,NaN,NaN,0.0 | 0.23809523809523814,0.04761904761904767,NaN,NaN,NaN,0.0   | 0.2711630721262614,0.0,NaN,NaN,NaN,0.0                                  | 22.869938085219395,5.432783854753551,NaN,NaN,NaN,0.0                 |
| train5 | 0.0,1.0,NaN,NaN,NaN,0.0 | 9.16515138991168,6.0,NaN,NaN,NaN,9.16515138991168    | 0.16000000000000003,45.0,NaN,NaN,NaN,0.24                 | 0.1414213561373095,0.07432941456946801,NaN,NaN,NaN,0.07071067806865475  | 9.466572746048989,52.07432941456947,NaN,NaN,NaN,9.475862067980335    |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      13.8564 |             0.185714 |           0.0409616 |      14.0831 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,13 @@
 def dsl4(I):
-    O = I
+    # Geometric reasoning: keep the initial motif block, append its (5->0) version vertically repeated to fill height
+    W = width(I)
+    H = height(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    bottom_h = subtract(H, m)
+    k = divide(bottom_h, m)
+    rep = vupscale(motif0, k)
+    O = vconcat(motif, rep)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,17 +1,23 @@
 def dsl1(I):
-    # Global transformation: crop top (all foreground), then tile the top-5-rows-pattern (with 5->0) to fill the remainder
+    # Global tiling of (5->0) top-motif into the background below last foreground row
     FG = objects(I, T, F, T)
-    FGinds = mapply(toindices, FG)
-    top_h = increment(lowermost(FGinds))
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
+    W = width(I)
     H = height(I)
-    W = width(I)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
     motif = crop(I, ORIGIN, astuple(m, W))
     motif0 = replace(motif, FIVE, ZERO)
+    obj = asobject(motif0)
     bottom_h = subtract(H, top_h)
     k = divide(bottom_h, m)
-    rep = vupscale(motif0, k)
-    top = crop(I, ORIGIN, astuple(top_h, W))
-    O = vconcat(top, rep)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(top_h, ZERO)
+    offs = apply(lbind(add, start), scaled)
+    copies = mapply(lbind(shift, obj), offs)
+    repobj = merge(copies)
+    O = underpaint(I, repobj)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,15 +1,25 @@
 def dsl3(I):
-    # Color-based fill: repeat the last non-empty row (with 5->0) to fill all trailing background rows
+    # Color-based fill: build bottom canvas by tiling the (5->0) motif, then append under the unchanged head
     FG = objects(I, T, F, T)
-    FGinds = mapply(toindices, FG)
-    last = lowermost(FGinds)
-    top_h = increment(last)
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
+    W = width(I)
     H = height(I)
-    W = width(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    obj = asobject(motif0)
     bottom_h = subtract(H, top_h)
-    lastrow = crop(I, astuple(last, ZERO), astuple(ONE, W))
-    lastrow0 = replace(lastrow, FIVE, ZERO)
-    rep = vupscale(lastrow0, bottom_h)
-    top = crop(I, ORIGIN, astuple(top_h, W))
-    O = vconcat(top, rep)
+    k = divide(bottom_h, m)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    offs0 = apply(lbind(add, ORIGIN), scaled)
+    copies0 = mapply(lbind(shift, obj), offs0)
+    repobj0 = merge(copies0)
+    head = crop(I, ORIGIN, astuple(top_h, W))
+    bottom_canvas = canvas(ZERO, astuple(bottom_h, W))
+    bottom_filled = paint(bottom_canvas, repobj0)
+    O = vconcat(head, bottom_filled)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,26 @@
 def dsl5(I):
-    # Relational/structural: build a background from a vertically repeated (5->0) motif, then repaint all original foreground on top
+    # Relational/structural: place multiple moved copies of the (5->0) motif onto a zero base and underpaint
+    FG = objects(I, T, F, T)
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
     W = width(I)
     H = height(I)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
     motif = crop(I, ORIGIN, astuple(m, W))
     motif0 = replace(motif, FIVE, ZERO)
-    bottom_h = subtract(H, m)
+    obj = asobject(motif0)
+    bottom_h = subtract(H, top_h)
     k = divide(bottom_h, m)
-    rep = vupscale(motif0, k)
-    base = vconcat(motif0, rep)
-    FG = objects(I, T, F, T)
-    fused = merge(FG)
-    O = paint(base, fused)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(top_h, ZERO)
+    offs = apply(lbind(add, start), scaled)
+    base0 = canvas(ZERO, shape(I))
+    mover = lbind(lbind(move, base0), obj)
+    placed_grids = mapply(mover, offs)
+    placed_objs = mapply(asobject, placed_grids)
+    repobj = merge(placed_objs)
+    O = underpaint(I, repobj)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,10 +1,9 @@
 def dsl2(I):
     # Object extraction: replicate only non-5 objects from the top m rows downward
-    FG = objects(I, T, F, T)
-    FGI = merge(mapply(toindices, FG))
-    top_h = increment(lowermost(FGI))
     W = width(I)
     H = height(I)
+    NZ = difference(asindices(I), ofcolor(I, ZERO))
+    top_h = height(subgrid(NZ, I))
     M5 = ofcolor(I, FIVE)
     m = height(M5)
     tile = crop(I, ORIGIN, astuple(m, W))
@@ -15,11 +14,7 @@
     bottom_h = subtract(H, top_h)
     k = divide(bottom_h, m)
     vec = astuple(m, ZERO)
-    times = interval(ZERO, k, ONE)
-    scaled = apply(rbind(multiply, vec), times)
-    start = astuple(top_h, ZERO)
-    offs = apply(lbind(add, start), scaled)
-    copies = mapply(lbind(shift, fused), offs)
-    repobj = merge(copies)
+    offs = apply(lbind(add, astuple(top_h, ZERO)), apply(rbind(multiply, vec), interval(ZERO, k, ONE)))
+    repobj = merge(mapply(lbind(shift, fused), offs))
     O = underpaint(I, repobj)
     return O
```

## Program 5

### Train scores

|        | Grid size cost          | Value cost                                             | Pixel overlap cost                                         | Bounding box cost                                                       | Total cost                                                          |
|:-------|:------------------------|:-------------------------------------------------------|:-----------------------------------------------------------|:------------------------------------------------------------------------|:--------------------------------------------------------------------|
| train1 | 0.0,1.0,NaN,NaN,NaN,0.0 | 18.547236990991408,6.0,NaN,NaN,NaN,10.0                | 0.20512820512820518,150.0,NaN,NaN,NaN,0.05128205128205132  | 0.2793721182102703,0.03606092228572704,NaN,NaN,NaN,0.10476454432885136  | 19.03173731432988,157.0360609222857,NaN,NaN,NaN,10.156046595610903  |
| train2 | 0.0,2.0,NaN,NaN,NaN,0.0 | 14.45683229480096,23.0,NaN,NaN,NaN,8.660254037844387   | 0.0892857142857143,98.0,NaN,NaN,NaN,0.0535714285714286     | 0.1411081301911679,0.10101525440420066,NaN,NaN,NaN,0.09407208679411193  | 14.687226139277842,123.1010152544042,NaN,NaN,NaN,8.807897553209928  |
| train3 | 0.0,1.0,NaN,NaN,NaN,0.0 | 21.166010488516726,16.0,NaN,NaN,NaN,7.0710678118654755 | 0.15873015873015872,119.0,NaN,NaN,NaN,0.031746031746031744 | 0.17541160378448276,0.04540766089803142,NaN,NaN,NaN,0.08770580189224138 | 21.500152251031366,136.04540766089804,NaN,NaN,NaN,7.190519645503748 |
| train4 | 0.0,0.0,NaN,NaN,NaN,0.0 | 22.360679774997898,0.0,NaN,NaN,NaN,5.0                 | 0.23809523809523814,0.0,NaN,NaN,NaN,0.023809523809523836   | 0.2711630721262614,0.0,NaN,NaN,NaN,0.10846522885050455                  | 22.869938085219395,0.0,NaN,NaN,NaN,5.132274752660028                |
| train5 | 0.0,1.0,NaN,NaN,NaN,0.0 | 9.16515138991168,6.0,NaN,NaN,NaN,7.0710678118654755    | 0.16000000000000003,45.0,NaN,NaN,NaN,0.07999999999999996   | 0.1414213561373095,0.07432941456946801,NaN,NaN,NaN,0.07071067806865475  | 9.466572746048989,52.07432941456947,NaN,NaN,NaN,7.22177848993413    |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      8.66025 |            0.0428571 |           0.0819232 |      8.78503 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,16 @@
 def dsl5(I):
-    O = I
+    # Relational/structural: build a background from a vertically repeated (5->0) motif, then repaint all original foreground on top
+    W = width(I)
+    H = height(I)
+    M5 = ofcolor(I, FIVE)
+    m = height(M5)
+    motif = crop(I, ORIGIN, astuple(m, W))
+    motif0 = replace(motif, FIVE, ZERO)
+    bottom_h = subtract(H, m)
+    k = divide(bottom_h, m)
+    rep = vupscale(motif0, k)
+    base = vconcat(motif0, rep)
+    FG = objects(I, T, F, T)
+    fused = merge(FG)
+    O = paint(base, fused)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,25 @@
 def dsl2(I):
-    # Object extraction: build a single shifted copy of the (5->0) motif placed just below the last foreground row, paint only on background
+    # Object extraction: replicate only non-5 objects from the top m rows downward
     FG = objects(I, T, F, T)
-    FGinds = mapply(toindices, FG)
-    top_h = increment(lowermost(FGinds))
+    FGI = merge(mapply(toindices, FG))
+    top_h = increment(lowermost(FGI))
     W = width(I)
+    H = height(I)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
-    motif = crop(I, ORIGIN, astuple(m, W))
-    motif0 = replace(motif, FIVE, ZERO)
-    base = canvas(ZERO, shape(I))
-    obj = asobject(motif0)
-    off = astuple(top_h, ZERO)
-    placed = move(base, obj, off)
-    O = underpaint(I, asobject(placed))
+    tile = crop(I, ORIGIN, astuple(m, W))
+    objs = objects(tile, T, F, T)
+    fiveobjs = colorfilter(objs, FIVE)
+    non5 = difference(objs, fiveobjs)
+    fused = merge(non5)
+    bottom_h = subtract(H, top_h)
+    k = divide(bottom_h, m)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, k, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(top_h, ZERO)
+    offs = apply(lbind(add, start), scaled)
+    copies = mapply(lbind(shift, fused), offs)
+    repobj = merge(copies)
+    O = underpaint(I, repobj)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,13 +1,22 @@
 def dsl4(I):
-    # Geometric reasoning: keep the initial motif block, append its (5->0) version vertically repeated to fill height
+    # Geometric alignment: build a full-height bottom-aligned periodic background from (5->0), then repaint original FG
     W = width(I)
     H = height(I)
+    FG = objects(I, T, F, T)
+    fusedFG = merge(FG)
     M5 = ofcolor(I, FIVE)
     m = height(M5)
     motif = crop(I, ORIGIN, astuple(m, W))
     motif0 = replace(motif, FIVE, ZERO)
-    bottom_h = subtract(H, m)
-    k = divide(bottom_h, m)
-    rep = vupscale(motif0, k)
-    O = vconcat(motif, rep)
+    obj = asobject(motif0)
+    kfull = divide(H, m)
+    vec = astuple(m, ZERO)
+    times = interval(ZERO, kfull, ONE)
+    scaled = apply(rbind(multiply, vec), times)
+    start = astuple(subtract(H, multiply(m, kfull)), ZERO)
+    offs = apply(lbind(add, start), scaled)
+    copies = mapply(lbind(shift, obj), offs)
+    baseobj = merge(copies)
+    base = paint(canvas(ZERO, shape(I)), baseobj)
+    O = paint(base, fusedFG)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,23 +1,21 @@
 def dsl1(I):
-    # Global tiling of (5->0) top-motif into the background below last foreground row
-    FG = objects(I, T, F, T)
-    FGI = merge(mapply(toindices, FG))
-    top_h = increment(lowermost(FGI))
+    # Global: build bottom by tiling the top m-row motif with 5->0, then append under unchanged head
     W = width(I)
     H = height(I)
+    NZ = difference(asindices(I), ofcolor(I, ZERO))
+    top_h = height(subgrid(NZ, I))
     M5 = ofcolor(I, FIVE)
     m = height(M5)
-    motif = crop(I, ORIGIN, astuple(m, W))
-    motif0 = replace(motif, FIVE, ZERO)
-    obj = asobject(motif0)
+    tile = crop(I, ORIGIN, astuple(m, W))
+    tile0 = replace(tile, FIVE, ZERO)
+    obj = asobject(tile0)
     bottom_h = subtract(H, top_h)
     k = divide(bottom_h, m)
     vec = astuple(m, ZERO)
     times = interval(ZERO, k, ONE)
-    scaled = apply(rbind(multiply, vec), times)
-    start = astuple(top_h, ZERO)
-    offs = apply(lbind(add, start), scaled)
-    copies = mapply(lbind(shift, obj), offs)
-    repobj = merge(copies)
-    O = underpaint(I, repobj)
+    offs = apply(lbind(add, astuple(top_h, ZERO)), apply(rbind(multiply, vec), times))
+    repobj = merge(mapply(lbind(shift, obj), offs))
+    head = crop(I, ORIGIN, astuple(top_h, W))
+    bottom = paint(canvas(ZERO, astuple(bottom_h, W)), repobj)
+    O = vconcat(head, bottom)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,25 +1,20 @@
 def dsl3(I):
-    # Color-based fill: build bottom canvas by tiling the (5->0) motif, then append under the unchanged head
-    FG = objects(I, T, F, T)
-    FGI = merge(mapply(toindices, FG))
-    top_h = increment(lowermost(FGI))
+    # Color filtering: form a full repeated pattern from origin (5->0), then splice its bottom under the head
     W = width(I)
     H = height(I)
+    NZ = difference(asindices(I), ofcolor(I, ZERO))
+    top_h = height(subgrid(NZ, I))
     M5 = ofcolor(I, FIVE)
     m = height(M5)
-    motif = crop(I, ORIGIN, astuple(m, W))
-    motif0 = replace(motif, FIVE, ZERO)
-    obj = asobject(motif0)
-    bottom_h = subtract(H, top_h)
-    k = divide(bottom_h, m)
+    tile = crop(I, ORIGIN, astuple(m, W))
+    tile0 = replace(tile, FIVE, ZERO)
+    obj = asobject(tile0)
+    kfull = divide(H, m)
     vec = astuple(m, ZERO)
-    times = interval(ZERO, k, ONE)
-    scaled = apply(rbind(multiply, vec), times)
-    offs0 = apply(lbind(add, ORIGIN), scaled)
-    copies0 = mapply(lbind(shift, obj), offs0)
-    repobj0 = merge(copies0)
+    offs0 = apply(lbind(add, ORIGIN), apply(rbind(multiply, vec), interval(ZERO, kfull, ONE)))
+    repobj0 = merge(mapply(lbind(shift, obj), offs0))
+    full = paint(canvas(ZERO, shape(I)), repobj0)
     head = crop(I, ORIGIN, astuple(top_h, W))
-    bottom_canvas = canvas(ZERO, astuple(bottom_h, W))
-    bottom_filled = paint(bottom_canvas, repobj0)
-    O = vconcat(head, bottom_filled)
+    tail = crop(full, astuple(top_h, ZERO), astuple(subtract(H, top_h), W))
+    O = vconcat(head, tail)
     return O
```

