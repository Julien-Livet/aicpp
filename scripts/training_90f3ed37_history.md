# Task 90f3ed37

train solved, test solved

5 iterations

[Best program](#iteration-5-dsl-diff-2)

[Hodel solution](https://github.com/michaelhodel/arc-dsl/blob/main/solvers.py#L3715)

## Program 1

### Train scores

|        | Grid size cost          | Value cost                                                                                                    | Pixel overlap cost                                                                                                    | Bounding box cost                                                                                            | Total cost                                                                                                  |
|:-------|:------------------------|:--------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------|:-------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 4.58257569495584,0.0,0.0,0.0,0.0,4.58257569495584                                                             | 0.14,0.0,0.0,0.0,0.0,0.14                                                                                             | 0.0,0.0,0.0,0.0,0.0,0.0                                                                                      | 4.7225756949558395,0.0,0.0,0.0,0.0,4.7225756949558395                                                       |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.605551275463989,7.483314773547883,7.483314773547883,4.795831523312719,5.0990195135927845,5.0990195135927845 | 0.08666666666666667,0.3733333333333333,0.3733333333333333,0.15333333333333332,0.17333333333333334,0.17333333333333334 | 0.027735009803569147,0.027735009803569147,0.027735009803569147,0.0,0.027735009803569147,0.027735009803569147 | 3.719952951934225,7.884383116684785,7.884383116684785,4.949164856646052,5.300087856729688,5.300087856729688 |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.4641016151377544,5.196152422706632,5.196152422706632,6.4031242374328485,3.1622776601683795,0.0              | 0.07999999999999996,0.18000000000000005,0.18000000000000005,0.2733333333333333,0.06666666666666665,0.0                | 0.0,0.0,0.0,0.027735009803569147,0.0,0.0                                                                     | 3.5441016151377545,5.376152422706632,5.376152422706632,6.704192580569751,3.2289443268350464,0.0             |

### Test scores

|       | Grid size cost          | Value cost                                                                                      | Pixel overlap cost                                                                                      | Bounding box cost       | Total cost                                                                                      |
|:------|:------------------------|:------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------|:------------------------|:------------------------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.1622776601683795,3.872983346207417,3.872983346207417,3.872983346207417,0.0,3.1622776601683795 | 0.06666666666666665,0.09999999999999998,0.09999999999999998,0.09999999999999998,0.0,0.06666666666666665 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.2289443268350464,3.972983346207417,3.972983346207417,3.972983346207417,0.0,3.2289443268350464 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,6 @@
 def dsl1(I):
-    O = I
+    E = ofcolor(I, EIGHT)
+    S = shift(E, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,13 @@
 def dsl3(I):
-    O = I
+    E = ofcolor(I, EIGHT)
+    L = shift(E, LEFT)
+    R = shift(E, RIGHT)
+    U = shift(E, UP)
+    D = shift(E, DOWN)
+    Adj = combine(combine(L, R), combine(U, D))
+    Isolated = difference(E, Adj)
+    S = shift(Isolated, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    RaysD = shift(Rays, DOWN)
+    O = underfill(I, ONE, RaysD)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,8 @@
 def dsl5(I):
-    O = I
+    Objs = colorfilter(objects(I, T, F, T), EIGHT)
+    BorderObjs = sfilter(Objs, rbind(bordering, I))
+    BorderIdx = mapply(toindices, totuple(BorderObjs))
+    S = shift(BorderIdx, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,8 +1,11 @@
 def dsl2(I):
     E = ofcolor(I, EIGHT)
-    RightNeighbors = shift(E, LEFT)
-    Rightmost = difference(E, RightNeighbors)
-    S = shift(Rightmost, RIGHT)
+    L = shift(E, LEFT)
+    R = shift(E, RIGHT)
+    HAdj = combine(L, R)
+    IsoH = difference(E, HAdj)
+    S = shift(IsoH, RIGHT)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
-    O = underfill(I, ONE, Rays)
+    RaysD = shift(Rays, DOWN)
+    O = underfill(I, ONE, RaysD)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,8 +1,7 @@
 def dsl4(I):
     E = ofcolor(I, EIGHT)
-    Above = shift(E, UP)
-    Topmost = difference(E, Above)
-    S = shift(Topmost, RIGHT)
+    Z = ofcolor(I, ZERO)
+    S = intersection(shift(E, RIGHT), Z)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
     O = underfill(I, ONE, Rays)
     return O
```

## Program 2

### Train scores

|        | Grid size cost          | Value cost                                                                                       | Pixel overlap cost                                                                                    | Bounding box cost                                                                           | Total cost                                                                                      |
|:-------|:------------------------|:-------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 4.58257569495584,0.0,4.58257569495584,0.0,0.0,4.58257569495584                                   | 0.14,0.0,0.14,0.0,0.0,0.14                                                                            | 0.0,0.0,0.0,0.0,0.0,0.0                                                                     | 4.7225756949558395,0.0,4.7225756949558395,0.0,0.0,4.7225756949558395                            |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.605551275463989,7.483314773547883,0.0,5.0990195135927845,0.0,5.0990195135927845                | 0.08666666666666667,0.3733333333333333,0.0,0.17333333333333334,0.0,0.17333333333333334                | 0.027735009803569147,0.027735009803569147,0.0,0.027735009803569147,0.0,0.027735009803569147 | 3.719952951934225,7.884383116684785,0.0,5.300087856729688,0.0,5.300087856729688                 |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.4641016151377544,5.196152422706632,6.4031242374328485,4.358898943540674,3.1622776601683795,0.0 | 0.07999999999999996,0.18000000000000005,0.2733333333333333,0.1266666666666667,0.06666666666666665,0.0 | 0.0,0.0,0.027735009803569147,0.0,0.0,0.0                                                    | 3.5441016151377545,5.376152422706632,6.704192580569751,4.485565610207341,3.2289443268350464,0.0 |

### Test scores

|       | Grid size cost          | Value cost                                                                         | Pixel overlap cost                                                                      | Bounding box cost       | Total cost                                                                         |
|:------|:------------------------|:-----------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------|:------------------------|:-----------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.1622776601683795,3.872983346207417,3.1622776601683795,0.0,0.0,3.1622776601683795 | 0.06666666666666665,0.09999999999999998,0.06666666666666665,0.0,0.0,0.06666666666666665 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.2289443268350464,3.972983346207417,3.2289443268350464,0.0,0.0,3.2289443268350464 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,8 @@
 def dsl2(I):
-    O = I
+    E = ofcolor(I, EIGHT)
+    RightNeighbors = shift(E, LEFT)
+    Rightmost = difference(E, RightNeighbors)
+    S = shift(Rightmost, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,8 @@
 def dsl4(I):
-    O = I
+    E = ofcolor(I, EIGHT)
+    Above = shift(E, UP)
+    Topmost = difference(E, Above)
+    S = shift(Topmost, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,6 +1,11 @@
 def dsl1(I):
     E = ofcolor(I, EIGHT)
-    S = shift(E, RIGHT)
+    RightNbr = shift(E, LEFT)
+    Rightmost = difference(E, RightNbr)
+    BelowNbr = shift(E, UP)
+    Lowermost = difference(E, BelowNbr)
+    Anch = intersection(Rightmost, Lowermost)
+    S = shift(Anch, RIGHT)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
     O = underfill(I, ONE, Rays)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,13 +1,9 @@
 def dsl3(I):
     E = ofcolor(I, EIGHT)
-    L = shift(E, LEFT)
-    R = shift(E, RIGHT)
-    U = shift(E, UP)
-    D = shift(E, DOWN)
-    Adj = combine(combine(L, R), combine(U, D))
-    Isolated = difference(E, Adj)
-    S = shift(Isolated, RIGHT)
+    Topmost = difference(E, shift(E, UP))
+    Rightmost = difference(E, shift(E, LEFT))
+    Corners = intersection(Topmost, Rightmost)
+    S = shift(Corners, RIGHT)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
-    RaysD = shift(Rays, DOWN)
-    O = underfill(I, ONE, RaysD)
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,8 +1,14 @@
 def dsl5(I):
-    Objs = colorfilter(objects(I, T, F, T), EIGHT)
-    BorderObjs = sfilter(Objs, rbind(bordering, I))
-    BorderIdx = mapply(toindices, totuple(BorderObjs))
-    S = shift(BorderIdx, RIGHT)
-    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    E = ofcolor(I, EIGHT)
+    Rightmost = difference(E, shift(E, LEFT))
+    VAdj = combine(shift(E, UP), shift(E, DOWN))
+    VertIso = difference(E, VAdj)
+    A = intersection(Rightmost, VertIso)
+    B = difference(Rightmost, A)
+    SA = shift(A, RIGHT)
+    SB = shift(B, RIGHT)
+    RaysA = mapply(rbind(shoot, RIGHT), totuple(SA))
+    RaysB = mapply(rbind(shoot, RIGHT), totuple(SB))
+    Rays = combine(shift(RaysA, DOWN), RaysB)
     O = underfill(I, ONE, Rays)
     return O
```

## Program 3

### Train scores

|        | Grid size cost          | Value cost                                                                                      | Pixel overlap cost                                                                                    | Bounding box cost                                                          | Total cost                                                                                      |
|:-------|:------------------------|:------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------|:---------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 4.58257569495584,4.58257569495584,0.0,0.0,0.0,0.0                                               | 0.14,0.14,0.0,0.0,0.0,0.0                                                                             | 0.0,0.0,0.0,0.0,0.0,0.0                                                    | 4.7225756949558395,4.7225756949558395,0.0,0.0,0.0,0.0                                           |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.605551275463989,0.0,7.483314773547883,7.483314773547883,0.0,0.0                               | 0.08666666666666667,0.0,0.3733333333333333,0.3733333333333333,0.0,0.0                                 | 0.027735009803569147,0.0,0.027735009803569147,0.027735009803569147,0.0,0.0 | 3.719952951934225,0.0,7.884383116684785,7.884383116684785,0.0,0.0                               |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.4641016151377544,6.4031242374328485,5.196152422706632,4.69041575982343,3.7416573867739413,0.0 | 0.07999999999999996,0.2733333333333333,0.18000000000000005,0.1466666666666666,0.09333333333333338,0.0 | 0.0,0.027735009803569147,0.0,0.0,0.0,0.0                                   | 3.5441016151377545,6.704192580569751,5.376152422706632,4.837082426490096,3.8349907201072746,0.0 |

### Test scores

|       | Grid size cost          | Value cost                                                          | Pixel overlap cost                                                      | Bounding box cost       | Total cost                                                          |
|:------|:------------------------|:--------------------------------------------------------------------|:------------------------------------------------------------------------|:------------------------|:--------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.1622776601683795,3.1622776601683795,3.872983346207417,0.0,0.0,0.0 | 0.06666666666666665,0.06666666666666665,0.09999999999999998,0.0,0.0,0.0 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.2289443268350464,3.2289443268350464,3.972983346207417,0.0,0.0,0.0 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,13 @@
 def dsl3(I):
-    O = I
+    E = ofcolor(I, EIGHT)
+    L = shift(E, LEFT)
+    R = shift(E, RIGHT)
+    U = shift(E, UP)
+    D = shift(E, DOWN)
+    Adj = combine(combine(L, R), combine(U, D))
+    Isolated = difference(E, Adj)
+    S = shift(Isolated, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    RaysD = shift(Rays, DOWN)
+    O = underfill(I, ONE, RaysD)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,8 @@
 def dsl5(I):
-    O = I
+    Objs = colorfilter(objects(I, T, F, T), EIGHT)
+    BorderObjs = sfilter(Objs, rbind(bordering, I))
+    BorderIdx = mapply(toindices, totuple(BorderObjs))
+    S = shift(BorderIdx, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,8 +1,11 @@
 def dsl2(I):
     E = ofcolor(I, EIGHT)
-    RightNeighbors = shift(E, LEFT)
-    Rightmost = difference(E, RightNeighbors)
-    S = shift(Rightmost, RIGHT)
+    L = shift(E, LEFT)
+    R = shift(E, RIGHT)
+    HAdj = combine(L, R)
+    IsoH = difference(E, HAdj)
+    S = shift(IsoH, RIGHT)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
-    O = underfill(I, ONE, Rays)
+    RaysD = shift(Rays, DOWN)
+    O = underfill(I, ONE, RaysD)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,8 +1,7 @@
 def dsl4(I):
     E = ofcolor(I, EIGHT)
-    Above = shift(E, UP)
-    Topmost = difference(E, Above)
-    S = shift(Topmost, RIGHT)
+    Z = ofcolor(I, ZERO)
+    S = intersection(shift(E, RIGHT), Z)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
     O = underfill(I, ONE, Rays)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,11 +1,16 @@
 def dsl1(I):
     E = ofcolor(I, EIGHT)
-    RightNbr = shift(E, LEFT)
-    Rightmost = difference(E, RightNbr)
-    BelowNbr = shift(E, UP)
-    Lowermost = difference(E, BelowNbr)
-    Anch = intersection(Rightmost, Lowermost)
-    S = shift(Anch, RIGHT)
-    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    Rightmost = difference(E, shift(E, LEFT))
+    Lowermost = difference(E, shift(E, UP))
+    Corners = intersection(Rightmost, Lowermost)
+    HAdj = combine(shift(E, LEFT), shift(E, RIGHT))
+    IsoH = difference(E, HAdj)
+    A = intersection(Corners, IsoH)
+    B = difference(Corners, A)
+    SA = shift(A, RIGHT)
+    SB = shift(B, RIGHT)
+    RaysA = mapply(rbind(shoot, RIGHT), totuple(SA))
+    RaysB = mapply(rbind(shoot, RIGHT), totuple(SB))
+    Rays = combine(shift(RaysA, DOWN), RaysB)
     O = underfill(I, ONE, Rays)
     return O
```

## Program 4

### Train scores

|        | Grid size cost          | Value cost                                                                                                  | Pixel overlap cost                                                                                                  | Bounding box cost                                                                                            | Total cost                                                                                                  |
|:-------|:------------------------|:------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------|:-------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 4.58257569495584,0.0,0.0,0.0,0.0,4.58257569495584                                                           | 0.14,0.0,0.0,0.0,0.0,0.14                                                                                           | 0.0,0.0,0.0,0.0,0.0,0.0                                                                                      | 4.7225756949558395,0.0,0.0,0.0,0.0,4.7225756949558395                                                       |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.605551275463989,7.483314773547883,7.483314773547883,7.483314773547883,3.605551275463989,4.358898943540674 | 0.08666666666666667,0.3733333333333333,0.3733333333333333,0.3733333333333333,0.08666666666666667,0.1266666666666667 | 0.027735009803569147,0.027735009803569147,0.027735009803569147,0.027735009803569147,0.0,0.027735009803569147 | 3.719952951934225,7.884383116684785,7.884383116684785,7.884383116684785,3.6922179421306556,4.51330062001091 |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.4641016151377544,5.196152422706632,5.196152422706632,5.196152422706632,6.557438524302,0.0                 | 0.07999999999999996,0.18000000000000005,0.18000000000000005,0.18000000000000005,0.2866666666666666,0.0              | 0.0,0.0,0.0,0.0,0.027735009803569147,0.0                                                                     | 3.5441016151377545,5.376152422706632,5.376152422706632,5.376152422706632,6.871840200772237,0.0              |

### Test scores

|       | Grid size cost          | Value cost                                                                                      | Pixel overlap cost                                                                                      | Bounding box cost       | Total cost                                                                                      |
|:------|:------------------------|:------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------|:------------------------|:------------------------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.1622776601683795,3.872983346207417,3.872983346207417,3.872983346207417,0.0,3.1622776601683795 | 0.06666666666666665,0.09999999999999998,0.09999999999999998,0.09999999999999998,0.0,0.06666666666666665 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.2289443268350464,3.972983346207417,3.972983346207417,3.972983346207417,0.0,3.2289443268350464 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,8 @@
 def dsl4(I):
-    O = I
+    E = ofcolor(I, EIGHT)
+    Above = shift(E, UP)
+    Topmost = difference(E, Above)
+    S = shift(Topmost, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,6 +1,11 @@
 def dsl1(I):
     E = ofcolor(I, EIGHT)
-    S = shift(E, RIGHT)
+    RightNbr = shift(E, LEFT)
+    Rightmost = difference(E, RightNbr)
+    BelowNbr = shift(E, UP)
+    Lowermost = difference(E, BelowNbr)
+    Anch = intersection(Rightmost, Lowermost)
+    S = shift(Anch, RIGHT)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
     O = underfill(I, ONE, Rays)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,13 +1,9 @@
 def dsl3(I):
     E = ofcolor(I, EIGHT)
-    L = shift(E, LEFT)
-    R = shift(E, RIGHT)
-    U = shift(E, UP)
-    D = shift(E, DOWN)
-    Adj = combine(combine(L, R), combine(U, D))
-    Isolated = difference(E, Adj)
-    S = shift(Isolated, RIGHT)
+    Topmost = difference(E, shift(E, UP))
+    Rightmost = difference(E, shift(E, LEFT))
+    Corners = intersection(Topmost, Rightmost)
+    S = shift(Corners, RIGHT)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
-    RaysD = shift(Rays, DOWN)
-    O = underfill(I, ONE, RaysD)
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,8 +1,14 @@
 def dsl5(I):
-    Objs = colorfilter(objects(I, T, F, T), EIGHT)
-    BorderObjs = sfilter(Objs, rbind(bordering, I))
-    BorderIdx = mapply(toindices, totuple(BorderObjs))
-    S = shift(BorderIdx, RIGHT)
-    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    E = ofcolor(I, EIGHT)
+    Rightmost = difference(E, shift(E, LEFT))
+    VAdj = combine(shift(E, UP), shift(E, DOWN))
+    VertIso = difference(E, VAdj)
+    A = intersection(Rightmost, VertIso)
+    B = difference(Rightmost, A)
+    SA = shift(A, RIGHT)
+    SB = shift(B, RIGHT)
+    RaysA = mapply(rbind(shoot, RIGHT), totuple(SA))
+    RaysB = mapply(rbind(shoot, RIGHT), totuple(SB))
+    Rays = combine(shift(RaysA, DOWN), RaysB)
     O = underfill(I, ONE, Rays)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,11 +1,9 @@
 def dsl2(I):
     E = ofcolor(I, EIGHT)
-    L = shift(E, LEFT)
-    R = shift(E, RIGHT)
-    HAdj = combine(L, R)
-    IsoH = difference(E, HAdj)
-    S = shift(IsoH, RIGHT)
+    Z = ofcolor(I, ZERO)
+    S0 = intersection(shift(E, RIGHT), Z)
+    DownHasE = shift(E, UP)
+    S = difference(S0, DownHasE)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
-    RaysD = shift(Rays, DOWN)
-    O = underfill(I, ONE, RaysD)
+    O = underfill(I, ONE, Rays)
     return O
```

## Program 5

### Train scores

|        | Grid size cost          | Value cost                                                                                       | Pixel overlap cost                                                                                    | Bounding box cost                                                          | Total cost                                                                                       |
|:-------|:------------------------|:-------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------|:---------------------------------------------------------------------------|:-------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 4.58257569495584,0.0,6.48074069840786,0.0,0.0,0.0                                                | 0.14,0.0,0.28,0.0,0.0,0.0                                                                             | 0.0,0.0,0.027735009803569147,0.0,0.0,0.0                                   | 4.7225756949558395,0.0,6.78847570821143,0.0,0.0,0.0                                              |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.605551275463989,6.0,4.47213595499958,6.0,0.0,0.0                                               | 0.08666666666666667,0.24,0.1333333333333333,0.24,0.0,0.0                                              | 0.027735009803569147,0.027735009803569147,0.0,0.027735009803569147,0.0,0.0 | 3.719952951934225,6.26773500980357,4.6054692883329125,6.26773500980357,0.0,0.0                   |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.4641016151377544,4.69041575982343,6.4031242374328485,3.4641016151377544,3.1622776601683795,0.0 | 0.07999999999999996,0.1466666666666666,0.2733333333333333,0.07999999999999996,0.06666666666666665,0.0 | 0.0,0.0,0.027735009803569147,0.0,0.0,0.0                                   | 3.5441016151377545,4.837082426490096,6.704192580569751,3.5441016151377545,3.2289443268350464,0.0 |

### Test scores

|       | Grid size cost          | Value cost                                                         | Pixel overlap cost                                                                      | Bounding box cost                        | Total cost                                                                       |
|:------|:------------------------|:-------------------------------------------------------------------|:----------------------------------------------------------------------------------------|:-----------------------------------------|:---------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0 | 3.1622776601683795,5.0,3.872983346207417,3.872983346207417,0.0,0.0 | 0.06666666666666665,0.16666666666666663,0.09999999999999998,0.09999999999999998,0.0,0.0 | 0.0,0.0,0.027735009803569147,0.0,0.0,0.0 | 3.2289443268350464,5.166666666666667,4.000718356010986,3.972983346207417,0.0,0.0 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,8 @@
 def dsl5(I):
-    O = I
+    Objs = colorfilter(objects(I, T, F, T), EIGHT)
+    BorderObjs = sfilter(Objs, rbind(bordering, I))
+    BorderIdx = mapply(toindices, totuple(BorderObjs))
+    S = shift(BorderIdx, RIGHT)
+    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    O = underfill(I, ONE, Rays)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,8 +1,11 @@
 def dsl2(I):
     E = ofcolor(I, EIGHT)
-    RightNeighbors = shift(E, LEFT)
-    Rightmost = difference(E, RightNeighbors)
-    S = shift(Rightmost, RIGHT)
+    L = shift(E, LEFT)
+    R = shift(E, RIGHT)
+    HAdj = combine(L, R)
+    IsoH = difference(E, HAdj)
+    S = shift(IsoH, RIGHT)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
-    O = underfill(I, ONE, Rays)
+    RaysD = shift(Rays, DOWN)
+    O = underfill(I, ONE, RaysD)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,8 +1,7 @@
 def dsl4(I):
     E = ofcolor(I, EIGHT)
-    Above = shift(E, UP)
-    Topmost = difference(E, Above)
-    S = shift(Topmost, RIGHT)
+    Z = ofcolor(I, ZERO)
+    S = intersection(shift(E, RIGHT), Z)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
     O = underfill(I, ONE, Rays)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,11 +1,16 @@
 def dsl1(I):
     E = ofcolor(I, EIGHT)
-    RightNbr = shift(E, LEFT)
-    Rightmost = difference(E, RightNbr)
-    BelowNbr = shift(E, UP)
-    Lowermost = difference(E, BelowNbr)
-    Anch = intersection(Rightmost, Lowermost)
-    S = shift(Anch, RIGHT)
-    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
+    Rightmost = difference(E, shift(E, LEFT))
+    Lowermost = difference(E, shift(E, UP))
+    Corners = intersection(Rightmost, Lowermost)
+    HAdj = combine(shift(E, LEFT), shift(E, RIGHT))
+    IsoH = difference(E, HAdj)
+    A = intersection(Corners, IsoH)
+    B = difference(Corners, A)
+    SA = shift(A, RIGHT)
+    SB = shift(B, RIGHT)
+    RaysA = mapply(rbind(shoot, RIGHT), totuple(SA))
+    RaysB = mapply(rbind(shoot, RIGHT), totuple(SB))
+    Rays = combine(shift(RaysA, DOWN), RaysB)
     O = underfill(I, ONE, Rays)
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,9 +1,9 @@
 def dsl3(I):
     E = ofcolor(I, EIGHT)
-    Topmost = difference(E, shift(E, UP))
-    Rightmost = difference(E, shift(E, LEFT))
-    Corners = intersection(Topmost, Rightmost)
-    S = shift(Corners, RIGHT)
+    Z = ofcolor(I, ZERO)
+    S0 = intersection(shift(E, RIGHT), Z)
+    UpHasE = shift(E, DOWN)
+    S = difference(S0, UpHasE)
     Rays = mapply(rbind(shoot, RIGHT), totuple(S))
     O = underfill(I, ONE, Rays)
     return O
```

