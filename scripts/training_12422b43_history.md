# Task 12422b43

train failed, test failed

10 iterations

[Best program](#iteration-10-dsl-diff)

## Program 1

### Train scores

|        | Grid size cost                              | Value cost                                                                                                                                       | Pixel overlap cost                                                                                                                                          | Bounding box cost                                                                                                                           | Total cost                                                                                                                                           |
|:-------|:--------------------------------------------|:-------------------------------------------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------|:-----------------------------------------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,NaN,NaN,0.0,NaN,0.0,0.0,NaN,0.0,0.0 | 18.547236990991408,21.166010488516726,NaN,NaN,18.547236990991408,NaN,18.547236990991408,18.547236990991408,NaN,15.0996688705415,17.4928556845359 | 0.20512820512820518,0.20512820512820518,NaN,NaN,0.20512820512820518,NaN,0.20512820512820518,0.20512820512820518,NaN,0.17948717948717952,0.17948717948717952 | 0.2793721182102703,0.17460757388141893,NaN,NaN,0.2793721182102703,NaN,0.2793721182102703,0.2793721182102703,NaN,0.0,0.03492151477628379     | 19.03173731432988,21.54574626752635,NaN,NaN,19.03173731432988,NaN,19.03173731432988,19.03173731432988,NaN,15.279156050028678,17.707264378799362      |
| train2 | 0.0,0.0,NaN,NaN,0.0,NaN,0.0,0.0,NaN,0.0,0.0 | 14.45683229480096,18.35755975068582,NaN,NaN,14.45683229480096,NaN,14.45683229480096,14.45683229480096,NaN,13.638181696985855,13.30413469565007   | 0.0892857142857143,0.2142857142857143,NaN,NaN,0.0892857142857143,NaN,0.0892857142857143,0.0892857142857143,NaN,0.125,0.1071428571428571                     | 0.1411081301911679,0.0,NaN,NaN,0.1411081301911679,NaN,0.1411081301911679,0.1411081301911679,NaN,0.0,0.09407208679411193                     | 14.687226139277842,18.571845464971535,NaN,NaN,14.687226139277842,NaN,14.687226139277842,14.687226139277842,NaN,13.763181696985855,13.50534963958704  |
| train3 | 0.0,0.0,NaN,NaN,0.0,NaN,0.0,0.0,NaN,0.0,0.0 | 21.166010488516726,22.360679774997898,NaN,NaN,21.166010488516726,NaN,21.166010488516726,21.166010488516726,NaN,21.908902300206645,24.0           | 0.15873015873015872,0.23809523809523814,NaN,NaN,0.15873015873015872,NaN,0.15873015873015872,0.15873015873015872,NaN,0.23809523809523814,0.23809523809523814 | 0.17541160378448276,0.04385290094612069,NaN,NaN,0.17541160378448276,NaN,0.17541160378448276,0.17541160378448276,NaN,0.0,0.04385290094612069 | 21.500152251031366,22.642627914039256,NaN,NaN,21.500152251031366,NaN,21.500152251031366,21.500152251031366,NaN,22.146997538301882,24.281948139041358 |
| train4 | 0.0,0.0,NaN,NaN,0.0,NaN,0.0,0.0,NaN,0.0,0.0 | 22.360679774997898,16.06237840420901,NaN,NaN,22.360679774997898,NaN,22.360679774997898,22.360679774997898,NaN,0.0,0.0                            | 0.23809523809523814,0.19047619047619047,NaN,NaN,0.23809523809523814,NaN,0.23809523809523814,0.23809523809523814,NaN,0.0,0.0                                 | 0.2711630721262614,0.10846522885050455,NaN,NaN,0.2711630721262614,NaN,0.2711630721262614,0.2711630721262614,NaN,0.0,0.0                     | 22.869938085219395,16.361319823535705,NaN,NaN,22.869938085219395,NaN,22.869938085219395,22.869938085219395,NaN,0.0,0.0                               |
| train5 | 0.0,0.0,NaN,NaN,0.0,NaN,0.0,0.0,NaN,0.0,0.0 | 9.16515138991168,8.246211251235321,NaN,NaN,9.16515138991168,NaN,9.16515138991168,9.16515138991168,NaN,8.48528137423857,9.16515138991168          | 0.16000000000000003,0.19999999999999996,NaN,NaN,0.16000000000000003,NaN,0.16000000000000003,0.16000000000000003,NaN,0.24,0.24                               | 0.1414213561373095,0.0,NaN,NaN,0.1414213561373095,NaN,0.1414213561373095,0.1414213561373095,NaN,0.0,0.07071067806865475                     | 9.466572746048989,8.44621125123532,NaN,NaN,9.466572746048989,NaN,9.466572746048989,9.466572746048989,NaN,8.72528137423857,9.475862067980335          |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      13.8564 |             0.185714 |           0.0409616 |      14.0831 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,10 @@
 def dsl1(I):
-    O = I
+    G = replace(I, FIVE, ZERO)
+    obj = asobject(G)
+    s1 = shift(obj, DOWN)
+    s2 = shift(obj, multiply(DOWN, TWO))
+    s3 = shift(obj, multiply(DOWN, THREE))
+    S = insert(s2, insert(s1, initset(s3)))
+    U = merge(S)
+    O = underpaint(I, U)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,5 @@
 def dsl3(I):
-    O = I
+    G = replace(I, FIVE, ZERO)
+    M = hmirror(G)
+    O = underpaint(I, asobject(M))
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,12 @@
 def dsl5(I):
-    O = I
+    col = toobject(ofcolor(I, FIVE), I)
+    vec = toivec(vperiod(col))
+    RFs = mapply(hfrontier, ofcolor(I, FIVE))
+    Rows = merge(RFs)
+    G = replace(I, FIVE, ZERO)
+    P = toobject(Rows, G)
+    s1 = shift(P, vec)
+    s2 = shift(P, multiply(vec, TWO))
+    U = merge(insert(s1, initset(s2)))
+    O = underpaint(I, U)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,11 +1,16 @@
 def dsl2(I):
+    G = replace(I, FIVE, ZERO)
+    Os = objects(G, T, F, T)
     A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
-    Rows = merge(RFs)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
-    s1 = shift(P, DOWN)
-    s2 = shift(P, multiply(DOWN, TWO))
-    U = merge(insert(s1, initset(s2)))
+    Sel = mfilter(Os, lbind(hmatching, A))
+    P = merge(Sel)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,9 +1,16 @@
 def dsl4(I):
-    A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
+    col = toobject(ofcolor(I, FIVE), I)
+    B = backdrop(col)
+    RFs = mapply(hfrontier, B)
     Rows = merge(RFs)
     G = replace(I, FIVE, ZERO)
     P = toobject(Rows, G)
-    M = hmirror(P)
-    O = underpaint(I, M)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
+    O = underpaint(I, U)
     return O
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -1,17 +1,18 @@
 def dsl1(I):
     A = ofcolor(I, FIVE)
-    L = merge(mapply(lbind(shoot, LEFT), A))
-    R = merge(mapply(lbind(shoot, RIGHT), A))
+    L = merge(mapply(rbind(shoot, LEFT), A))
+    R = merge(mapply(rbind(shoot, RIGHT), A))
     Rows = combine(combine(L, R), A)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
+    Z = ofcolor(I, ZERO)
+    M = difference(Rows, combine(A, Z))
+    P = toobject(M, I)
     col = toobject(A, I)
     k = height(subgrid(col, I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
+    Fs = papply(power, repeat(step, n), Ns)
     U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,16 @@
 def dsl3(I):
     A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
-    Rows = merge(RFs)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
     col = toobject(A, I)
     k = height(subgrid(col, I))
+    W = width(I)
+    B = crop(I, ORIGIN, astuple(k, W))
+    M = difference(asindices(B), combine(ofcolor(B, ZERO), ofcolor(B, FIVE)))
+    P0 = toobject(M, B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Fs = papply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P0))
     O = underpaint(I, U)
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -1,20 +1,20 @@
 def dsl5(I):
     A = ofcolor(I, FIVE)
-    L = merge(mapply(lbind(shoot, LEFT), A))
-    R = merge(mapply(lbind(shoot, RIGHT), A))
+    L = merge(mapply(rbind(shoot, LEFT), A))
+    R = merge(mapply(rbind(shoot, RIGHT), A))
     Rows = combine(combine(L, R), A)
-    G = replace(I, FIVE, ZERO)
-    NonRows = difference(asindices(I), Rows)
-    RmObj = toobject(NonRows, G)
-    RowGrid = cover(G, RmObj)
-    P = asobject(RowGrid)
+    NZ = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, FIVE)))
+    M = intersection(Rows, NZ)
+    Pind = M
+    P = toobject(Pind, I)
     col = toobject(A, I)
     k = height(subgrid(col, I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Fs = papply(power, repeat(step, n), Ns)
+    Uinds = merge(rapply(Fs, Pind))
+    U = toobject(Uinds, I)
     O = underpaint(I, U)
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,17 @@
 def dsl2(I):
-    G = replace(I, FIVE, ZERO)
-    Os = objects(G, T, F, T)
     A = ofcolor(I, FIVE)
-    Sel = mfilter(Os, lbind(hmatching, A))
-    P = merge(Sel)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
+    k = height(subgrid(toobject(A, I), I))
+    W = width(I)
+    B = crop(I, ORIGIN, astuple(k, W))
+    IBI = asindices(B)
+    ZB = ofcolor(B, ZERO)
+    F5B = ofcolor(B, FIVE)
+    M = difference(difference(IBI, ZB), F5B)
+    P0 = toobject(M, B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P0), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,14 @@
 def dsl4(I):
-    Os = objects(I, T, F, T)
-    A5 = colorfilter(Os, FIVE)
-    A = merge(A5)
-    Non5 = difference(Os, A5)
-    Sel = mfilter(Non5, lbind(hmatching, toindices(A)))
+    A = ofcolor(I, FIVE)
+    G = replace(I, FIVE, ZERO)
+    Os = fgpartition(G)
+    Sel = mfilter(Os, lbind(hmatching, A))
     P = merge(Sel)
-    k = height(subgrid(A, I))
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

## Program 2

### Train scores

|        | Grid size cost                              | Value cost                                                 | Pixel overlap cost                                          | Bounding box cost                                           | Total cost                                                 |
|:-------|:--------------------------------------------|:-----------------------------------------------------------|:------------------------------------------------------------|:------------------------------------------------------------|:-----------------------------------------------------------|
| train1 | 0.0,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 18.547236990991408,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 0.20512820512820518,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 0.2793721182102703,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN  | 19.03173731432988,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN  |
| train2 | 0.0,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 14.45683229480096,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN  | 0.0892857142857143,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN  | 0.1411081301911679,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN  | 14.687226139277842,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN |
| train3 | 0.0,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 21.166010488516726,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 0.15873015873015872,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 0.17541160378448276,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 21.500152251031366,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN |
| train4 | 0.0,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 22.360679774997898,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 0.23809523809523814,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 0.2711630721262614,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN  | 22.869938085219395,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN |
| train5 | 0.0,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 9.16515138991168,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN   | 0.16000000000000003,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN | 0.1414213561373095,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN  | 9.466572746048989,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN,NaN  |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |              nan |          nan |                  nan |                 nan |          nan |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,11 @@
 def dsl2(I):
-    O = I
+    A = ofcolor(I, FIVE)
+    RFs = mapply(hfrontier, A)
+    Rows = merge(RFs)
+    G = replace(I, FIVE, ZERO)
+    P = toobject(Rows, G)
+    s1 = shift(P, DOWN)
+    s2 = shift(P, multiply(DOWN, TWO))
+    U = merge(insert(s1, initset(s2)))
+    O = underpaint(I, U)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,9 @@
 def dsl4(I):
-    O = I
+    A = ofcolor(I, FIVE)
+    RFs = mapply(hfrontier, A)
+    Rows = merge(RFs)
+    G = replace(I, FIVE, ZERO)
+    P = toobject(Rows, G)
+    M = hmirror(P)
+    O = underpaint(I, M)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,10 +1,17 @@
 def dsl1(I):
+    A = ofcolor(I, FIVE)
+    L = merge(mapply(lbind(shoot, LEFT), A))
+    R = merge(mapply(lbind(shoot, RIGHT), A))
+    Rows = combine(combine(L, R), A)
     G = replace(I, FIVE, ZERO)
-    obj = asobject(G)
-    s1 = shift(obj, DOWN)
-    s2 = shift(obj, multiply(DOWN, TWO))
-    s3 = shift(obj, multiply(DOWN, THREE))
-    S = insert(s2, insert(s1, initset(s3)))
-    U = merge(S)
+    P = toobject(Rows, G)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,5 +1,16 @@
 def dsl3(I):
+    A = ofcolor(I, FIVE)
+    RFs = mapply(hfrontier, A)
+    Rows = merge(RFs)
     G = replace(I, FIVE, ZERO)
-    M = hmirror(G)
-    O = underpaint(I, asobject(M))
+    P = toobject(Rows, G)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
+    O = underpaint(I, U)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,12 +1,20 @@
 def dsl5(I):
-    col = toobject(ofcolor(I, FIVE), I)
-    vec = toivec(vperiod(col))
-    RFs = mapply(hfrontier, ofcolor(I, FIVE))
-    Rows = merge(RFs)
+    A = ofcolor(I, FIVE)
+    L = merge(mapply(lbind(shoot, LEFT), A))
+    R = merge(mapply(lbind(shoot, RIGHT), A))
+    Rows = combine(combine(L, R), A)
     G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
-    s1 = shift(P, vec)
-    s2 = shift(P, multiply(vec, TWO))
-    U = merge(insert(s1, initset(s2)))
+    NonRows = difference(asindices(I), Rows)
+    RmObj = toobject(NonRows, G)
+    RowGrid = cover(G, RmObj)
+    P = asobject(RowGrid)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -10,7 +10,7 @@
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
+    Fs = papply(power, repeat(step, n), Ns)
     U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,16 @@
 def dsl4(I):
-    col = toobject(ofcolor(I, FIVE), I)
-    B = backdrop(col)
-    RFs = mapply(hfrontier, B)
-    Rows = merge(RFs)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
-    k = height(subgrid(col, I))
+    Os = objects(I, T, F, T)
+    A5 = colorfilter(Os, FIVE)
+    A = merge(A5)
+    Non5 = difference(Os, A5)
+    Sel = mfilter(Non5, lbind(hmatching, toindices(A)))
+    P = merge(Sel)
+    k = height(subgrid(A, I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
+    Fs = papply(power, repeat(step, n), Ns)
     U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -2,17 +2,17 @@
     A = ofcolor(I, FIVE)
     L = merge(mapply(rbind(shoot, LEFT), A))
     R = merge(mapply(rbind(shoot, RIGHT), A))
-    Rows = combine(combine(L, R), A)
-    Z = ofcolor(I, ZERO)
-    M = difference(Rows, combine(A, Z))
+    C = insert(R, insert(A, initset(L)))
+    Rows = merge(C)
+    NZ1 = difference(asindices(I), ofcolor(I, ZERO))
+    NZ2 = difference(NZ1, A)
+    M = intersection(Rows, NZ2)
     P = toobject(M, I)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,14 @@
 def dsl3(I):
     A = ofcolor(I, FIVE)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
-    W = width(I)
-    B = crop(I, ORIGIN, astuple(k, W))
-    M = difference(asindices(B), combine(ofcolor(B, ZERO), ofcolor(B, FIVE)))
-    P0 = toobject(M, B)
+    Os = objects(I, T, F, T)
+    Non5 = difference(Os, colorfilter(Os, FIVE))
+    Sel = mfilter(Non5, lbind(hmatching, A))
+    P = merge(Sel)
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P0))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -1,20 +1,15 @@
 def dsl5(I):
     A = ofcolor(I, FIVE)
-    L = merge(mapply(rbind(shoot, LEFT), A))
-    R = merge(mapply(rbind(shoot, RIGHT), A))
-    Rows = combine(combine(L, R), A)
-    NZ = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, FIVE)))
-    M = intersection(Rows, NZ)
-    Pind = M
-    P = toobject(Pind, I)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
+    Rows = merge(mapply(hfrontier, A))
+    NZ1 = difference(asindices(I), ofcolor(I, ZERO))
+    NZ2 = difference(NZ1, A)
+    M = intersection(Rows, NZ2)
+    P = toobject(M, I)
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    Uinds = merge(rapply(Fs, Pind))
-    U = toobject(Uinds, I)
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

## Program 3

### Train scores

|        | Grid size cost                              | Value cost                                                                                                                                                          | Pixel overlap cost                                                                                                                                                          | Bounding box cost                                                                                                                           | Total cost                                                                                                                                                          |
|:-------|:--------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,NaN,0.0,NaN,0.0,0.0,0.0,NaN,0.0,0.0 | 18.547236990991408,12.165525060596439,NaN,15.0996688705415,NaN,18.547236990991408,18.547236990991408,18.547236990991408,NaN,18.547236990991408,18.547236990991408   | 0.20512820512820518,0.17948717948717952,NaN,0.17948717948717952,NaN,0.20512820512820518,0.20512820512820518,0.20512820512820518,NaN,0.20512820512820518,0.20512820512820518 | 0.2793721182102703,0.0,NaN,0.0,NaN,0.2793721182102703,0.2793721182102703,0.2793721182102703,NaN,0.2793721182102703,0.2793721182102703       | 19.03173731432988,12.345012240083618,NaN,15.279156050028678,NaN,19.03173731432988,19.03173731432988,19.03173731432988,NaN,19.03173731432988,19.03173731432988       |
| train2 | 0.0,0.0,NaN,0.0,NaN,0.0,0.0,0.0,NaN,0.0,0.0 | 14.45683229480096,13.856406460551018,NaN,13.638181696985855,NaN,14.45683229480096,14.45683229480096,14.45683229480096,NaN,14.45683229480096,14.45683229480096       | 0.0892857142857143,0.1071428571428571,NaN,0.125,NaN,0.0892857142857143,0.0892857142857143,0.0892857142857143,NaN,0.0892857142857143,0.0892857142857143                      | 0.1411081301911679,0.0,NaN,0.0,NaN,0.1411081301911679,0.1411081301911679,0.1411081301911679,NaN,0.1411081301911679,0.1411081301911679       | 14.687226139277842,13.963549317693875,NaN,13.763181696985855,NaN,14.687226139277842,14.687226139277842,14.687226139277842,NaN,14.687226139277842,14.687226139277842 |
| train3 | 0.0,0.0,NaN,0.0,NaN,0.0,0.0,0.0,NaN,0.0,0.0 | 21.166010488516726,18.920887928424502,NaN,21.908902300206645,NaN,21.166010488516726,21.166010488516726,21.166010488516726,NaN,21.166010488516726,21.166010488516726 | 0.15873015873015872,0.17460317460317465,NaN,0.23809523809523814,NaN,0.15873015873015872,0.15873015873015872,0.15873015873015872,NaN,0.15873015873015872,0.15873015873015872 | 0.17541160378448276,0.0,NaN,0.0,NaN,0.17541160378448276,0.17541160378448276,0.17541160378448276,NaN,0.17541160378448276,0.17541160378448276 | 21.500152251031366,19.095491103027676,NaN,22.146997538301882,NaN,21.500152251031366,21.500152251031366,21.500152251031366,NaN,21.500152251031366,21.500152251031366 |
| train4 | 0.0,0.0,NaN,0.0,NaN,0.0,0.0,0.0,NaN,0.0,0.0 | 22.360679774997898,18.138357147217054,NaN,0.0,NaN,22.360679774997898,22.360679774997898,22.360679774997898,NaN,22.360679774997898,22.360679774997898                | 0.23809523809523814,0.19047619047619047,NaN,0.0,NaN,0.23809523809523814,0.23809523809523814,0.23809523809523814,NaN,0.23809523809523814,0.23809523809523814                 | 0.2711630721262614,0.0,NaN,0.0,NaN,0.2711630721262614,0.2711630721262614,0.2711630721262614,NaN,0.2711630721262614,0.2711630721262614       | 22.869938085219395,18.328833337693244,NaN,0.0,NaN,22.869938085219395,22.869938085219395,22.869938085219395,NaN,22.869938085219395,22.869938085219395                |
| train5 | 0.0,0.0,NaN,0.0,NaN,0.0,0.0,0.0,NaN,0.0,0.0 | 9.16515138991168,8.48528137423857,NaN,8.48528137423857,NaN,9.16515138991168,9.16515138991168,9.16515138991168,NaN,9.16515138991168,9.16515138991168                 | 0.16000000000000003,0.24,NaN,0.24,NaN,0.16000000000000003,0.16000000000000003,0.16000000000000003,NaN,0.16000000000000003,0.16000000000000003                               | 0.1414213561373095,0.0,NaN,0.0,NaN,0.1414213561373095,0.1414213561373095,0.1414213561373095,NaN,0.1414213561373095,0.1414213561373095       | 9.466572746048989,8.72528137423857,NaN,8.72528137423857,NaN,9.466572746048989,9.466572746048989,9.466572746048989,NaN,9.466572746048989,9.466572746048989           |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      17.2047 |             0.142857 |             0.24577 |      17.5933 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,5 @@
 def dsl3(I):
-    O = I
+    G = replace(I, FIVE, ZERO)
+    M = hmirror(G)
+    O = underpaint(I, asobject(M))
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,12 @@
 def dsl5(I):
-    O = I
+    col = toobject(ofcolor(I, FIVE), I)
+    vec = toivec(vperiod(col))
+    RFs = mapply(hfrontier, ofcolor(I, FIVE))
+    Rows = merge(RFs)
+    G = replace(I, FIVE, ZERO)
+    P = toobject(Rows, G)
+    s1 = shift(P, vec)
+    s2 = shift(P, multiply(vec, TWO))
+    U = merge(insert(s1, initset(s2)))
+    O = underpaint(I, U)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,11 +1,16 @@
 def dsl2(I):
+    G = replace(I, FIVE, ZERO)
+    Os = objects(G, T, F, T)
     A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
-    Rows = merge(RFs)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
-    s1 = shift(P, DOWN)
-    s2 = shift(P, multiply(DOWN, TWO))
-    U = merge(insert(s1, initset(s2)))
+    Sel = mfilter(Os, lbind(hmatching, A))
+    P = merge(Sel)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,9 +1,16 @@
 def dsl4(I):
-    A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
+    col = toobject(ofcolor(I, FIVE), I)
+    B = backdrop(col)
+    RFs = mapply(hfrontier, B)
     Rows = merge(RFs)
     G = replace(I, FIVE, ZERO)
     P = toobject(Rows, G)
-    M = hmirror(P)
-    O = underpaint(I, M)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
+    O = underpaint(I, U)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,17 +1,18 @@
 def dsl1(I):
     A = ofcolor(I, FIVE)
-    L = merge(mapply(lbind(shoot, LEFT), A))
-    R = merge(mapply(lbind(shoot, RIGHT), A))
+    L = merge(mapply(rbind(shoot, LEFT), A))
+    R = merge(mapply(rbind(shoot, RIGHT), A))
     Rows = combine(combine(L, R), A)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
+    Z = ofcolor(I, ZERO)
+    M = difference(Rows, combine(A, Z))
+    P = toobject(M, I)
     col = toobject(A, I)
     k = height(subgrid(col, I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
+    Fs = papply(power, repeat(step, n), Ns)
     U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,16 @@
 def dsl3(I):
     A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
-    Rows = merge(RFs)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
     col = toobject(A, I)
     k = height(subgrid(col, I))
+    W = width(I)
+    B = crop(I, ORIGIN, astuple(k, W))
+    M = difference(asindices(B), combine(ofcolor(B, ZERO), ofcolor(B, FIVE)))
+    P0 = toobject(M, B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Fs = papply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P0))
     O = underpaint(I, U)
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -1,20 +1,20 @@
 def dsl5(I):
     A = ofcolor(I, FIVE)
-    L = merge(mapply(lbind(shoot, LEFT), A))
-    R = merge(mapply(lbind(shoot, RIGHT), A))
+    L = merge(mapply(rbind(shoot, LEFT), A))
+    R = merge(mapply(rbind(shoot, RIGHT), A))
     Rows = combine(combine(L, R), A)
-    G = replace(I, FIVE, ZERO)
-    NonRows = difference(asindices(I), Rows)
-    RmObj = toobject(NonRows, G)
-    RowGrid = cover(G, RmObj)
-    P = asobject(RowGrid)
+    NZ = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, FIVE)))
+    M = intersection(Rows, NZ)
+    Pind = M
+    P = toobject(Pind, I)
     col = toobject(A, I)
     k = height(subgrid(col, I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Fs = papply(power, repeat(step, n), Ns)
+    Uinds = merge(rapply(Fs, Pind))
+    U = toobject(Uinds, I)
     O = underpaint(I, U)
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,17 @@
 def dsl2(I):
-    G = replace(I, FIVE, ZERO)
-    Os = objects(G, T, F, T)
     A = ofcolor(I, FIVE)
-    Sel = mfilter(Os, lbind(hmatching, A))
-    P = merge(Sel)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
+    k = height(subgrid(toobject(A, I), I))
+    W = width(I)
+    B = crop(I, ORIGIN, astuple(k, W))
+    IBI = asindices(B)
+    ZB = ofcolor(B, ZERO)
+    F5B = ofcolor(B, FIVE)
+    M = difference(difference(IBI, ZB), F5B)
+    P0 = toobject(M, B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P0), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,14 @@
 def dsl4(I):
-    Os = objects(I, T, F, T)
-    A5 = colorfilter(Os, FIVE)
-    A = merge(A5)
-    Non5 = difference(Os, A5)
-    Sel = mfilter(Non5, lbind(hmatching, toindices(A)))
+    A = ofcolor(I, FIVE)
+    G = replace(I, FIVE, ZERO)
+    Os = fgpartition(G)
+    Sel = mfilter(Os, lbind(hmatching, A))
     P = merge(Sel)
-    k = height(subgrid(A, I))
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -1,18 +1,18 @@
 def dsl1(I):
-    A = ofcolor(I, FIVE)
-    L = merge(mapply(rbind(shoot, LEFT), A))
-    R = merge(mapply(rbind(shoot, RIGHT), A))
-    C = insert(R, insert(A, initset(L)))
-    Rows = merge(C)
-    NZ1 = difference(asindices(I), ofcolor(I, ZERO))
-    NZ2 = difference(NZ1, A)
-    M = intersection(Rows, NZ2)
-    P = toobject(M, I)
-    k = height(subgrid(toobject(A, I), I))
+    # Global crop-and-tile of the top non-empty band (use compress to get band height), excluding FIVE
+    G = compress(I)
+    k = height(G)
+    W = width(I)
+    B = crop(I, ORIGIN, astuple(k, W))
+    IBI = asindices(B)
+    ZB = ofcolor(B, ZERO)
+    F5B = ofcolor(B, FIVE)
+    M = difference(difference(IBI, ZB), F5B)
+    P0 = toobject(M, B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     Ns = apply(increment, interval(ZERO, n, ONE))
     Offs = apply(lbind(multiply, vec), Ns)
-    U = merge(mapply(lbind(shift, P), Offs))
+    U = merge(mapply(lbind(shift, P0), Offs))
     O = underpaint(I, U)
     return O
```

## Program 4

### Train scores

|        | Grid size cost                              | Value cost                                                                                                             | Pixel overlap cost                                                                                                          | Bounding box cost                                                                                                           | Total cost                                                                                                             |
|:-------|:--------------------------------------------|:-----------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------|:-----------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,NaN,NaN,NaN,NaN,0.0,NaN,NaN,0.0,0.0,0.0 | 18.547236990991408,NaN,NaN,NaN,NaN,18.547236990991408,NaN,NaN,18.547236990991408,18.547236990991408,18.547236990991408 | 0.20512820512820518,NaN,NaN,NaN,NaN,0.20512820512820518,NaN,NaN,0.20512820512820518,0.20512820512820518,0.20512820512820518 | 0.2793721182102703,NaN,NaN,NaN,NaN,0.2793721182102703,NaN,NaN,0.2793721182102703,0.2793721182102703,0.2793721182102703      | 19.03173731432988,NaN,NaN,NaN,NaN,19.03173731432988,NaN,NaN,19.03173731432988,19.03173731432988,19.03173731432988      |
| train2 | 0.0,NaN,NaN,NaN,NaN,0.0,NaN,NaN,0.0,0.0,0.0 | 14.45683229480096,NaN,NaN,NaN,NaN,14.45683229480096,NaN,NaN,14.45683229480096,14.45683229480096,14.45683229480096      | 0.0892857142857143,NaN,NaN,NaN,NaN,0.0892857142857143,NaN,NaN,0.0892857142857143,0.0892857142857143,0.0892857142857143      | 0.1411081301911679,NaN,NaN,NaN,NaN,0.1411081301911679,NaN,NaN,0.1411081301911679,0.1411081301911679,0.1411081301911679      | 14.687226139277842,NaN,NaN,NaN,NaN,14.687226139277842,NaN,NaN,14.687226139277842,14.687226139277842,14.687226139277842 |
| train3 | 0.0,NaN,NaN,NaN,NaN,0.0,NaN,NaN,0.0,0.0,0.0 | 21.166010488516726,NaN,NaN,NaN,NaN,21.166010488516726,NaN,NaN,21.166010488516726,21.166010488516726,21.166010488516726 | 0.15873015873015872,NaN,NaN,NaN,NaN,0.15873015873015872,NaN,NaN,0.15873015873015872,0.15873015873015872,0.15873015873015872 | 0.17541160378448276,NaN,NaN,NaN,NaN,0.17541160378448276,NaN,NaN,0.17541160378448276,0.17541160378448276,0.17541160378448276 | 21.500152251031366,NaN,NaN,NaN,NaN,21.500152251031366,NaN,NaN,21.500152251031366,21.500152251031366,21.500152251031366 |
| train4 | 0.0,NaN,NaN,NaN,NaN,0.0,NaN,NaN,0.0,0.0,0.0 | 22.360679774997898,NaN,NaN,NaN,NaN,22.360679774997898,NaN,NaN,22.360679774997898,22.360679774997898,22.360679774997898 | 0.23809523809523814,NaN,NaN,NaN,NaN,0.23809523809523814,NaN,NaN,0.23809523809523814,0.23809523809523814,0.23809523809523814 | 0.2711630721262614,NaN,NaN,NaN,NaN,0.2711630721262614,NaN,NaN,0.2711630721262614,0.2711630721262614,0.2711630721262614      | 22.869938085219395,NaN,NaN,NaN,NaN,22.869938085219395,NaN,NaN,22.869938085219395,22.869938085219395,22.869938085219395 |
| train5 | 0.0,NaN,NaN,NaN,NaN,0.0,NaN,NaN,0.0,0.0,0.0 | 9.16515138991168,NaN,NaN,NaN,NaN,9.16515138991168,NaN,NaN,9.16515138991168,9.16515138991168,9.16515138991168           | 0.16000000000000003,NaN,NaN,NaN,NaN,0.16000000000000003,NaN,NaN,0.16000000000000003,0.16000000000000003,0.16000000000000003 | 0.1414213561373095,NaN,NaN,NaN,NaN,0.1414213561373095,NaN,NaN,0.1414213561373095,0.1414213561373095,0.1414213561373095      | 9.466572746048989,NaN,NaN,NaN,NaN,9.466572746048989,NaN,NaN,9.466572746048989,9.466572746048989,9.466572746048989      |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      17.2047 |             0.142857 |             0.24577 |      17.5933 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,9 @@
 def dsl4(I):
-    O = I
+    A = ofcolor(I, FIVE)
+    RFs = mapply(hfrontier, A)
+    Rows = merge(RFs)
+    G = replace(I, FIVE, ZERO)
+    P = toobject(Rows, G)
+    M = hmirror(P)
+    O = underpaint(I, M)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,10 +1,17 @@
 def dsl1(I):
+    A = ofcolor(I, FIVE)
+    L = merge(mapply(lbind(shoot, LEFT), A))
+    R = merge(mapply(lbind(shoot, RIGHT), A))
+    Rows = combine(combine(L, R), A)
     G = replace(I, FIVE, ZERO)
-    obj = asobject(G)
-    s1 = shift(obj, DOWN)
-    s2 = shift(obj, multiply(DOWN, TWO))
-    s3 = shift(obj, multiply(DOWN, THREE))
-    S = insert(s2, insert(s1, initset(s3)))
-    U = merge(S)
+    P = toobject(Rows, G)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,5 +1,16 @@
 def dsl3(I):
+    A = ofcolor(I, FIVE)
+    RFs = mapply(hfrontier, A)
+    Rows = merge(RFs)
     G = replace(I, FIVE, ZERO)
-    M = hmirror(G)
-    O = underpaint(I, asobject(M))
+    P = toobject(Rows, G)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
+    O = underpaint(I, U)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,12 +1,20 @@
 def dsl5(I):
-    col = toobject(ofcolor(I, FIVE), I)
-    vec = toivec(vperiod(col))
-    RFs = mapply(hfrontier, ofcolor(I, FIVE))
-    Rows = merge(RFs)
+    A = ofcolor(I, FIVE)
+    L = merge(mapply(lbind(shoot, LEFT), A))
+    R = merge(mapply(lbind(shoot, RIGHT), A))
+    Rows = combine(combine(L, R), A)
     G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
-    s1 = shift(P, vec)
-    s2 = shift(P, multiply(vec, TWO))
-    U = merge(insert(s1, initset(s2)))
+    NonRows = difference(asindices(I), Rows)
+    RmObj = toobject(NonRows, G)
+    RowGrid = cover(G, RmObj)
+    P = asobject(RowGrid)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -10,7 +10,7 @@
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
+    Fs = papply(power, repeat(step, n), Ns)
     U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,16 @@
 def dsl4(I):
-    col = toobject(ofcolor(I, FIVE), I)
-    B = backdrop(col)
-    RFs = mapply(hfrontier, B)
-    Rows = merge(RFs)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
-    k = height(subgrid(col, I))
+    Os = objects(I, T, F, T)
+    A5 = colorfilter(Os, FIVE)
+    A = merge(A5)
+    Non5 = difference(Os, A5)
+    Sel = mfilter(Non5, lbind(hmatching, toindices(A)))
+    P = merge(Sel)
+    k = height(subgrid(A, I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
+    Fs = papply(power, repeat(step, n), Ns)
     U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -2,17 +2,17 @@
     A = ofcolor(I, FIVE)
     L = merge(mapply(rbind(shoot, LEFT), A))
     R = merge(mapply(rbind(shoot, RIGHT), A))
-    Rows = combine(combine(L, R), A)
-    Z = ofcolor(I, ZERO)
-    M = difference(Rows, combine(A, Z))
+    C = insert(R, insert(A, initset(L)))
+    Rows = merge(C)
+    NZ1 = difference(asindices(I), ofcolor(I, ZERO))
+    NZ2 = difference(NZ1, A)
+    M = intersection(Rows, NZ2)
     P = toobject(M, I)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,14 @@
 def dsl3(I):
     A = ofcolor(I, FIVE)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
-    W = width(I)
-    B = crop(I, ORIGIN, astuple(k, W))
-    M = difference(asindices(B), combine(ofcolor(B, ZERO), ofcolor(B, FIVE)))
-    P0 = toobject(M, B)
+    Os = objects(I, T, F, T)
+    Non5 = difference(Os, colorfilter(Os, FIVE))
+    Sel = mfilter(Non5, lbind(hmatching, A))
+    P = merge(Sel)
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P0))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -1,20 +1,15 @@
 def dsl5(I):
     A = ofcolor(I, FIVE)
-    L = merge(mapply(rbind(shoot, LEFT), A))
-    R = merge(mapply(rbind(shoot, RIGHT), A))
-    Rows = combine(combine(L, R), A)
-    NZ = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, FIVE)))
-    M = intersection(Rows, NZ)
-    Pind = M
-    P = toobject(Pind, I)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
+    Rows = merge(mapply(hfrontier, A))
+    NZ1 = difference(asindices(I), ofcolor(I, ZERO))
+    NZ2 = difference(NZ1, A)
+    M = intersection(Rows, NZ2)
+    P = toobject(M, I)
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    Uinds = merge(rapply(Fs, Pind))
-    U = toobject(Uinds, I)
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -1,13 +1,12 @@
 def dsl2(I):
+    # Object extraction within the top band (crop by k), filter out FIVE, then tile downward
     A = ofcolor(I, FIVE)
     k = height(subgrid(toobject(A, I), I))
     W = width(I)
     B = crop(I, ORIGIN, astuple(k, W))
-    IBI = asindices(B)
-    ZB = ofcolor(B, ZERO)
-    F5B = ofcolor(B, FIVE)
-    M = difference(difference(IBI, ZB), F5B)
-    P0 = toobject(M, B)
+    OsB = objects(B, T, F, T)
+    Non5B = difference(OsB, colorfilter(OsB, FIVE))
+    P0 = merge(Non5B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     Ns = apply(increment, interval(ZERO, n, ONE))
```

## Program 5

### Train scores

|        | Grid size cost                              | Value cost                                                                                                                            | Pixel overlap cost                                                                                                                          | Bounding box cost                                                                                                           | Total cost                                                                                                                            |
|:-------|:--------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,NaN,NaN,0.0,0.0,NaN,NaN,NaN,0.0,0.0,0.0 | 18.547236990991408,NaN,NaN,18.547236990991408,18.547236990991408,NaN,NaN,NaN,15.0996688705415,18.547236990991408,18.547236990991408   | 0.20512820512820518,NaN,NaN,0.20512820512820518,0.20512820512820518,NaN,NaN,NaN,0.17948717948717952,0.20512820512820518,0.20512820512820518 | 0.2793721182102703,NaN,NaN,0.2793721182102703,0.2793721182102703,NaN,NaN,NaN,0.0,0.2793721182102703,0.2793721182102703      | 19.03173731432988,NaN,NaN,19.03173731432988,19.03173731432988,NaN,NaN,NaN,15.279156050028678,19.03173731432988,19.03173731432988      |
| train2 | 0.0,NaN,NaN,0.0,0.0,NaN,NaN,NaN,0.0,0.0,0.0 | 14.45683229480096,NaN,NaN,14.45683229480096,14.45683229480096,NaN,NaN,NaN,13.638181696985855,14.45683229480096,14.45683229480096      | 0.0892857142857143,NaN,NaN,0.0892857142857143,0.0892857142857143,NaN,NaN,NaN,0.125,0.0892857142857143,0.0892857142857143                    | 0.1411081301911679,NaN,NaN,0.1411081301911679,0.1411081301911679,NaN,NaN,NaN,0.0,0.1411081301911679,0.1411081301911679      | 14.687226139277842,NaN,NaN,14.687226139277842,14.687226139277842,NaN,NaN,NaN,13.763181696985855,14.687226139277842,14.687226139277842 |
| train3 | 0.0,NaN,NaN,0.0,0.0,NaN,NaN,NaN,0.0,0.0,0.0 | 21.166010488516726,NaN,NaN,21.166010488516726,21.166010488516726,NaN,NaN,NaN,21.908902300206645,21.166010488516726,21.166010488516726 | 0.15873015873015872,NaN,NaN,0.15873015873015872,0.15873015873015872,NaN,NaN,NaN,0.23809523809523814,0.15873015873015872,0.15873015873015872 | 0.17541160378448276,NaN,NaN,0.17541160378448276,0.17541160378448276,NaN,NaN,NaN,0.0,0.17541160378448276,0.17541160378448276 | 21.500152251031366,NaN,NaN,21.500152251031366,21.500152251031366,NaN,NaN,NaN,22.146997538301882,21.500152251031366,21.500152251031366 |
| train4 | 0.0,NaN,NaN,0.0,0.0,NaN,NaN,NaN,0.0,0.0,0.0 | 22.360679774997898,NaN,NaN,22.360679774997898,22.360679774997898,NaN,NaN,NaN,0.0,22.360679774997898,22.360679774997898                | 0.23809523809523814,NaN,NaN,0.23809523809523814,0.23809523809523814,NaN,NaN,NaN,0.0,0.23809523809523814,0.23809523809523814                 | 0.2711630721262614,NaN,NaN,0.2711630721262614,0.2711630721262614,NaN,NaN,NaN,0.0,0.2711630721262614,0.2711630721262614      | 22.869938085219395,NaN,NaN,22.869938085219395,22.869938085219395,NaN,NaN,NaN,0.0,22.869938085219395,22.869938085219395                |
| train5 | 0.0,NaN,NaN,0.0,0.0,NaN,NaN,NaN,0.0,0.0,0.0 | 9.16515138991168,NaN,NaN,9.16515138991168,9.16515138991168,NaN,NaN,NaN,8.48528137423857,9.16515138991168,9.16515138991168             | 0.16000000000000003,NaN,NaN,0.16000000000000003,0.16000000000000003,NaN,NaN,NaN,0.24,0.16000000000000003,0.16000000000000003                | 0.1414213561373095,NaN,NaN,0.1414213561373095,0.1414213561373095,NaN,NaN,NaN,0.0,0.1414213561373095,0.1414213561373095      | 9.466572746048989,NaN,NaN,9.466572746048989,9.466572746048989,NaN,NaN,NaN,8.72528137423857,9.466572746048989,9.466572746048989        |

### Test scores

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      17.2047 |             0.142857 |             0.24577 |      17.5933 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,12 @@
 def dsl5(I):
-    O = I
+    col = toobject(ofcolor(I, FIVE), I)
+    vec = toivec(vperiod(col))
+    RFs = mapply(hfrontier, ofcolor(I, FIVE))
+    Rows = merge(RFs)
+    G = replace(I, FIVE, ZERO)
+    P = toobject(Rows, G)
+    s1 = shift(P, vec)
+    s2 = shift(P, multiply(vec, TWO))
+    U = merge(insert(s1, initset(s2)))
+    O = underpaint(I, U)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,11 +1,16 @@
 def dsl2(I):
+    G = replace(I, FIVE, ZERO)
+    Os = objects(G, T, F, T)
     A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
-    Rows = merge(RFs)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
-    s1 = shift(P, DOWN)
-    s2 = shift(P, multiply(DOWN, TWO))
-    U = merge(insert(s1, initset(s2)))
+    Sel = mfilter(Os, lbind(hmatching, A))
+    P = merge(Sel)
+    col = toobject(A, I)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,9 +1,16 @@
 def dsl4(I):
-    A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
+    col = toobject(ofcolor(I, FIVE), I)
+    B = backdrop(col)
+    RFs = mapply(hfrontier, B)
     Rows = merge(RFs)
     G = replace(I, FIVE, ZERO)
     P = toobject(Rows, G)
-    M = hmirror(P)
-    O = underpaint(I, M)
+    k = height(subgrid(col, I))
+    vec = multiply(DOWN, k)
+    n = divide(height(I), k)
+    step = rbind(shift, vec)
+    Ns = apply(increment, interval(ZERO, n, ONE))
+    Fs = mpapply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P))
+    O = underpaint(I, U)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,17 +1,18 @@
 def dsl1(I):
     A = ofcolor(I, FIVE)
-    L = merge(mapply(lbind(shoot, LEFT), A))
-    R = merge(mapply(lbind(shoot, RIGHT), A))
+    L = merge(mapply(rbind(shoot, LEFT), A))
+    R = merge(mapply(rbind(shoot, RIGHT), A))
     Rows = combine(combine(L, R), A)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
+    Z = ofcolor(I, ZERO)
+    M = difference(Rows, combine(A, Z))
+    P = toobject(M, I)
     col = toobject(A, I)
     k = height(subgrid(col, I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
+    Fs = papply(power, repeat(step, n), Ns)
     U = merge(rapply(Fs, P))
     O = underpaint(I, U)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,16 @@
 def dsl3(I):
     A = ofcolor(I, FIVE)
-    RFs = mapply(hfrontier, A)
-    Rows = merge(RFs)
-    G = replace(I, FIVE, ZERO)
-    P = toobject(Rows, G)
     col = toobject(A, I)
     k = height(subgrid(col, I))
+    W = width(I)
+    B = crop(I, ORIGIN, astuple(k, W))
+    M = difference(asindices(B), combine(ofcolor(B, ZERO), ofcolor(B, FIVE)))
+    P0 = toobject(M, B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Fs = papply(power, repeat(step, n), Ns)
+    U = merge(rapply(Fs, P0))
     O = underpaint(I, U)
     return O
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -1,20 +1,20 @@
 def dsl5(I):
     A = ofcolor(I, FIVE)
-    L = merge(mapply(lbind(shoot, LEFT), A))
-    R = merge(mapply(lbind(shoot, RIGHT), A))
+    L = merge(mapply(rbind(shoot, LEFT), A))
+    R = merge(mapply(rbind(shoot, RIGHT), A))
     Rows = combine(combine(L, R), A)
-    G = replace(I, FIVE, ZERO)
-    NonRows = difference(asindices(I), Rows)
-    RmObj = toobject(NonRows, G)
-    RowGrid = cover(G, RmObj)
-    P = asobject(RowGrid)
+    NZ = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, FIVE)))
+    M = intersection(Rows, NZ)
+    Pind = M
+    P = toobject(Pind, I)
     col = toobject(A, I)
     k = height(subgrid(col, I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = mpapply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Fs = papply(power, repeat(step, n), Ns)
+    Uinds = merge(rapply(Fs, Pind))
+    U = toobject(Uinds, I)
     O = underpaint(I, U)
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,17 @@
 def dsl2(I):
-    G = replace(I, FIVE, ZERO)
-    Os = objects(G, T, F, T)
     A = ofcolor(I, FIVE)
-    Sel = mfilter(Os, lbind(hmatching, A))
-    P = merge(Sel)
-    col = toobject(A, I)
-    k = height(subgrid(col, I))
+    k = height(subgrid(toobject(A, I), I))
+    W = width(I)
+    B = crop(I, ORIGIN, astuple(k, W))
+    IBI = asindices(B)
+    ZB = ofcolor(B, ZERO)
+    F5B = ofcolor(B, FIVE)
+    M = difference(difference(IBI, ZB), F5B)
+    P0 = toobject(M, B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P0), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -1,16 +1,14 @@
 def dsl4(I):
-    Os = objects(I, T, F, T)
-    A5 = colorfilter(Os, FIVE)
-    A = merge(A5)
-    Non5 = difference(Os, A5)
-    Sel = mfilter(Non5, lbind(hmatching, toindices(A)))
+    A = ofcolor(I, FIVE)
+    G = replace(I, FIVE, ZERO)
+    Os = fgpartition(G)
+    Sel = mfilter(Os, lbind(hmatching, A))
     P = merge(Sel)
-    k = height(subgrid(A, I))
+    k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
-    step = rbind(shift, vec)
     Ns = apply(increment, interval(ZERO, n, ONE))
-    Fs = papply(power, repeat(step, n), Ns)
-    U = merge(rapply(Fs, P))
+    Offs = apply(lbind(multiply, vec), Ns)
+    U = merge(mapply(lbind(shift, P), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -1,18 +1,18 @@
 def dsl1(I):
-    A = ofcolor(I, FIVE)
-    L = merge(mapply(rbind(shoot, LEFT), A))
-    R = merge(mapply(rbind(shoot, RIGHT), A))
-    C = insert(R, insert(A, initset(L)))
-    Rows = merge(C)
-    NZ1 = difference(asindices(I), ofcolor(I, ZERO))
-    NZ2 = difference(NZ1, A)
-    M = intersection(Rows, NZ2)
-    P = toobject(M, I)
-    k = height(subgrid(toobject(A, I), I))
+    # Global crop-and-tile of the top non-empty band (use compress to get band height), excluding FIVE
+    G = compress(I)
+    k = height(G)
+    W = width(I)
+    B = crop(I, ORIGIN, astuple(k, W))
+    IBI = asindices(B)
+    ZB = ofcolor(B, ZERO)
+    F5B = ofcolor(B, FIVE)
+    M = difference(difference(IBI, ZB), F5B)
+    P0 = toobject(M, B)
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
     Ns = apply(increment, interval(ZERO, n, ONE))
     Offs = apply(lbind(multiply, vec), Ns)
-    U = merge(mapply(lbind(shift, P), Offs))
+    U = merge(mapply(lbind(shift, P0), Offs))
     O = underpaint(I, U)
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -1,9 +1,11 @@
 def dsl3(I):
+    # Color filtering on rows that contain FIVE (row mask via hfrontier), then periodic downward replication
     A = ofcolor(I, FIVE)
-    Os = objects(I, T, F, T)
-    Non5 = difference(Os, colorfilter(Os, FIVE))
-    Sel = mfilter(Non5, lbind(hmatching, A))
-    P = merge(Sel)
+    Rows = merge(mapply(hfrontier, A))
+    NZ = difference(asindices(I), ofcolor(I, ZERO))
+    NZn5 = difference(NZ, A)
+    M = intersection(Rows, NZn5)
+    P = toobject(M, I)
     k = height(subgrid(toobject(A, I), I))
     vec = multiply(DOWN, k)
     n = divide(height(I), k)
```

