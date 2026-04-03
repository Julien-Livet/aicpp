# Task 11dc524f

train failed, test failed

10 iterations

[Best program](#iteration-8-dsl-diff)

## Program 1

### Train scores

|        | Grid size cost                              | Value cost                                                                                                                                                                                                       | Pixel overlap cost                                                                                                                                                                                                                 | Bounding box cost                           | Total cost                                                                                                                                                                                                    |
|:-------|:--------------------------------------------|:-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.856406460551018,13.856406460551018,4.0,11.0,12.24744871391589,11.575836902790225,15.231546211727817,0.0,3.4641016151377544,2.8284271247461903                                              | 0.059171597633136064,0.08284023668639051,0.08284023668639051,0.023668639053254448,0.047337278106508895,0.035502958579881616,0.059171597633136064,0.09467455621301779,0.0,0.017751479289940808,0.011834319526627168                 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.939246697237408,13.939246697237408,4.023668639053255,11.04733727810651,12.282951672495772,11.635008500423362,15.326220767940836,0.0,3.481853094427695,2.8402614442728176                |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.569805089976535,11.916375287812984,11.045361017187261,4.0,8.717797887081348,8.717797887081348,11.0,13.490737563232042,2.0,3.4641016151377544,3.4641016151377544                                               | 0.047337278106508895,0.07100591715976334,0.0650887573964497,0.023668639053254448,0.035502958579881616,0.035502958579881616,0.047337278106508895,0.08284023668639051,0.00591715976331364,0.017751479289940808,0.017751479289940808  | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.617142368083044,11.987381204972747,11.11044977458371,4.023668639053255,8.75330084566123,8.75330084566123,11.04733727810651,13.573577799918432,2.005917159763314,3.481853094427695,3.481853094427695        |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.856406460551018,13.856406460551018,2.8284271247461903,12.767145334803704,12.083045973594572,13.379088160259652,15.231546211727817,3.4641016151377544,3.4641016151377544,3.4641016151377544 | 0.059171597633136064,0.08284023668639051,0.08284023668639051,0.011834319526627168,0.047337278106508895,0.053254437869822535,0.07100591715976334,0.09467455621301779,0.017751479289940808,0.017751479289940808,0.017751479289940808 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.939246697237408,13.939246697237408,2.8402614442728176,12.814482612910213,12.136300411464395,13.450094077419415,15.326220767940836,3.481853094427695,3.481853094427695,3.481853094427695 |

### Test scores

|       | Grid size cost                              | Value cost                                                                                                                                          | Pixel overlap cost                                                                                                                                                                                                                  | Bounding box cost                           | Total cost                                                                                                                                                                                                    |
|:------|:--------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,12.0,13.856406460551018,11.575836902790225,12.24744871391589,12.24744871391589,13.076696830622021,15.231546211727817,4.0,2.0,4.0 | 0.059171597633136064,0.059171597633136064,0.08284023668639051,0.059171597633136064,0.035502958579881616,0.035502958579881616,0.059171597633136064,0.09467455621301779,0.023668639053254448,0.00591715976331364,0.023668639053254448 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,12.059171597633137,13.939246697237408,11.635008500423362,12.282951672495772,12.282951672495772,13.135868428255158,15.326220767940836,4.023668639053255,2.005917159763314,4.023668639053255 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,24 @@
 def dsl1(I):
-    O = I
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    v = gravitate(s2, s5)
+    dv = double(v)
+    s2p = shift(s2, dv)
+    w = width(s2p)
+    h = height(s2p)
+    cand_r = shift(hmirror(s2p), tojvec(w))
+    cand_l = shift(hmirror(s2p), invert(tojvec(w)))
+    cand_d = shift(vmirror(s2p), toivec(h))
+    cand_u = shift(vmirror(s2p), invert(toivec(h)))
+    cset = initset(cand_r)
+    cset = insert(cand_l, cset)
+    cset = insert(cand_d, cset)
+    cset = insert(cand_u, cset)
+    chooser = lbind(manhattan, s5)
+    best = argmin(cset, chooser)
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(bg, obj2), obj5)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,30 @@
 def dsl3(I):
-    O = I
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    v = gravitate(s2, s5)
+    s2p = shift(s2, double(v))
+    w = width(s2p)
+    h = height(s2p)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    offR = tojvec(w)
+    offL = invert(offR)
+    offD = toivec(h)
+    offU = invert(offD)
+    s5candR = shift(mh, offR)
+    s5candL = shift(mh, offL)
+    s5candD = shift(mv, offD)
+    s5candU = shift(mv, offU)
+    isR = equality(v, RIGHT)
+    isL = equality(v, LEFT)
+    isD = equality(v, DOWN)
+    bestRL = branch(isR, s5candR, s5candL)
+    bestUD = branch(isD, s5candD, s5candU)
+    hor = either(isR, isL)
+    best = branch(hor, bestRL, bestUD)
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(bg, obj2), obj5)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,21 @@
 def dsl5(I):
-    O = I
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    clean = cover(cover(I, s2), s5)
+    v = gravitate(s2, s5)
+    s2p = shift(s2, double(v))
+    w = width(s2p)
+    h = height(s2p)
+    mr = shift(hmirror(s2p), tojvec(w))
+    ml = shift(hmirror(s2p), invert(tojvec(w)))
+    md = shift(vmirror(s2p), toivec(h))
+    mu = shift(vmirror(s2p), invert(toivec(h)))
+    cset = initset(mr)
+    cset = insert(ml, cset)
+    cset = insert(md, cset)
+    cset = insert(mu, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(clean, obj2), obj5)
     return O
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,26 +1,28 @@
 def dsl2(I):
     dims = shape(I)
     bg = canvas(SEVEN, dims)
-    s2 = ofcolor(I, TWO)
-    s5 = ofcolor(I, FIVE)
+    objs = objects(I, T, F, T)
+    o2s = colorfilter(objs, TWO)
+    o5s = colorfilter(objs, FIVE)
+    o2 = first(o2s)
+    o5 = first(o5s)
+    s2 = toindices(o2)
+    s5 = toindices(o5)
     v = gravitate(s2, s5)
-    dv = double(v)
-    s2p = shift(s2, dv)
+    s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    right = shift(hmirror(s2p), tojvec(w))
-    left = shift(hmirror(s2p), invert(tojvec(w)))
-    down = shift(vmirror(s2p), toivec(h))
-    up = shift(vmirror(s2p), invert(tojvec(h)))
-    hr = hmatching(s2, s5)
-    hset = initset(right)
-    hset = insert(left, hset)
-    vset = initset(down)
-    vset = insert(up, vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
-    best = branch(hr, besth, bestv)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    candR = shift(mh, tojvec(w))
+    candL = shift(mh, invert(tojvec(w)))
+    candD = shift(mv, toivec(h))
+    candU = shift(mv, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -1,28 +1,31 @@
 def dsl4(I):
     dims = shape(I)
     bg = canvas(SEVEN, dims)
-    objs = objects(I, T, F, T)
-    o2s = colorfilter(objs, TWO)
-    o5s = colorfilter(objs, FIVE)
-    o2 = first(o2s)
-    o5 = first(o5s)
-    s2 = toindices(o2)
-    s5 = toindices(o5)
-    v = gravitate(s2, s5)
-    s2p = shift(s2, add(v, v))
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    com2 = centerofmass(s2)
+    com5 = centerofmass(s5)
+    dirv = sign(subtract(com5, com2))
+    s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    cand_r = shift(mh, tojvec(w))
-    cand_l = shift(mh, invert(tojvec(w)))
-    cand_d = shift(mv, toivec(h))
-    cand_u = shift(mv, invert(toivec(h)))
-    cset = initset(cand_r)
-    cset = insert(cand_l, cset)
-    cset = insert(cand_d, cset)
-    cset = insert(cand_u, cset)
-    best = argmin(cset, lbind(manhattan, s5))
+    offR = tojvec(w)
+    offL = invert(offR)
+    offD = toivec(h)
+    offU = invert(offD)
+    candR = shift(mh, offR)
+    candL = shift(mh, offL)
+    candD = shift(mv, offD)
+    candU = shift(mv, offU)
+    isR = equality(dirv, RIGHT)
+    isL = equality(dirv, LEFT)
+    isD = equality(dirv, DOWN)
+    hor = either(isR, isL)
+    bestRL = branch(isR, candR, candL)
+    bestUD = branch(isD, candD, candU)
+    best = branch(hor, bestRL, bestUD)
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -3,28 +3,22 @@
     bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    com2 = centerofmass(s2)
+    com5 = centerofmass(s5)
+    dirv = sign(subtract(com5, com2))
+    s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    offR = tojvec(w)
-    offL = invert(offR)
-    offD = toivec(h)
-    offU = invert(offD)
-    candR = shift(mh, offR)
-    candL = shift(mh, offL)
-    candD = shift(mv, offD)
-    candU = shift(mv, offU)
-    isR = equality(v, RIGHT)
-    isL = equality(v, LEFT)
-    isD = equality(v, DOWN)
-    hor = either(isR, isL)
-    bestRL = branch(isR, candR, candL)
-    bestUD = branch(isD, candD, candU)
-    best = branch(hor, bestRL, bestUD)
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    candR = shift(mh, tojvec(w))
+    candL = shift(mh, invert(tojvec(w)))
+    candD = shift(mv, toivec(h))
+    candU = shift(mv, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -7,22 +7,15 @@
     s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    mh = hmirror(s2p)
-    mv = vmirror(s2p)
-    right = shift(mh, tojvec(w))
-    left = shift(mh, invert(tojvec(w)))
-    down = shift(mv, toivec(h))
-    up = shift(mv, invert(toivec(h)))
-    hr = hmatching(s2, s5)
-    hset = initset(right)
-    hset = insert(left, hset)
-    vset = initset(down)
-    vset = insert(up, vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
-    best = branch(hr, besth, bestv)
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    rot = vmirror(hmirror(s2p))
+    candR = shift(rot, tojvec(w))
+    candL = shift(rot, invert(tojvec(w)))
+    candD = shift(rot, toivec(h))
+    candU = shift(rot, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -1,23 +1,22 @@
 def dsl5(I):
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    clean = cover(cover(I, s2), s5)
     v = gravitate(s2, s5)
     s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    candR = shift(mh, tojvec(w))
-    candL = shift(mh, invert(tojvec(w)))
-    candD = shift(mv, toivec(h))
-    candU = shift(mv, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
-    best = argmin(cset, lbind(manhattan, s5))
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(clean, obj2), obj5)
+    cand = initset(shift(s2p, tojvec(w)))
+    cand = insert(shift(s2p, invert(tojvec(w))), cand)
+    cand = insert(shift(s2p, toivec(h)), cand)
+    cand = insert(shift(s2p, invert(toivec(h))), cand)
+    cand = insert(shift(mh, tojvec(w)), cand)
+    cand = insert(shift(mh, invert(tojvec(w))), cand)
+    cand = insert(shift(mv, toivec(h)), cand)
+    cand = insert(shift(mv, invert(toivec(h))), cand)
+    best = argmin(cand, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -6,21 +6,36 @@
     o5 = first(colorfilter(objs, FIVE))
     s2 = toindices(o2)
     s5 = toindices(o5)
-    rel = position(s2, s5)
-    dirv = sign(rel)
-    s2p = shift(s2, double(dirv))
+    v = gravitate(s2, s5)
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
+    l2 = leftmost(s2p)
+    t2 = uppermost(s2p)
+    l5 = leftmost(s5)
+    r5 = rightmost(s5)
+    t5 = uppermost(s5)
+    b5 = lowermost(s5)
+    w1 = decrement(w)
+    h1 = decrement(h)
+    tL = subtract(r5, w1)
+    tT = subtract(b5, h1)
+    dxR = subtract(tL, l2)
+    dxL = subtract(l5, l2)
+    dyB = subtract(tT, t2)
+    dyT = subtract(t5, t2)
+    cH1 = shift(mh, tojvec(dxR))
+    cH2 = shift(mh, tojvec(dxL))
+    cV1 = shift(mv, toivec(dyB))
+    cV2 = shift(mv, toivec(dyT))
+    chooser = lbind(manhattan, s5)
+    besth = argmin(initset(cH1), chooser)
+    besth = branch(greater(chooser(cH2), chooser(besth)), besth, cH2)
+    bestv = argmin(initset(cV1), chooser)
+    bestv = branch(greater(chooser(cV2), chooser(bestv)), bestv, cV2)
     hr = hmatching(s2, s5)
-    hset = initset(shift(mh, tojvec(w)))
-    hset = insert(shift(mh, invert(tojvec(w))), hset)
-    vset = initset(shift(mv, toivec(h)))
-    vset = insert(shift(mv, invert(toivec(h))), vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
     best = branch(hr, besth, bestv)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -3,22 +3,13 @@
     bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    com2 = centerofmass(s2)
-    com5 = centerofmass(s5)
-    dirv = sign(subtract(com5, com2))
-    s2p = shift(s2, double(dirv))
-    w = width(s2p)
-    h = height(s2p)
-    dd = dmirror(s2p)
-    cc = cmirror(s2p)
-    cand1 = shift(dd, tojvec(w))
-    cand2 = shift(dd, invert(tojvec(w)))
-    cand3 = shift(cc, toivec(h))
-    cand4 = shift(cc, invert(toivec(h)))
-    cset = initset(cand1)
-    cset = insert(cand2, cset)
-    cset = insert(cand3, cset)
-    cset = insert(cand4, cset)
-    best = argmin(cset, lbind(manhattan, s5))
+    v = gravitate(s2, s5)
+    s2p = shift(s2, multiply(v, TWO))
+    hr = hmatching(s2, s5)
+    mir = branch(hr, hmirror(s2p), vmirror(s2p))
+    c_mir = center(mir)
+    c_s5 = center(s5)
+    off = subtract(c_s5, c_mir)
+    best = shift(mir, off)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

## Program 2

### Train scores

|        | Grid size cost                              | Value cost                                                                                                                                                                                                      | Pixel overlap cost                                                                                                                                                                                                                    | Bounding box cost                           | Total cost                                                                                                                                                                                                    |
|:-------|:--------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.856406460551018,12.041594578792296,9.746794344808963,12.041594578792296,12.041594578792296,11.704699910719626,11.916375287812984,11.916375287812984,3.4641016151377544,3.4641016151377544 | 0.059171597633136064,0.08284023668639051,0.059171597633136064,0.047337278106508895,0.059171597633136064,0.059171597633136064,0.047337278106508895,0.047337278106508895,0.047337278106508895,0.017751479289940808,0.017751479289940808 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.939246697237408,12.100766176425433,9.794131622915472,12.100766176425433,12.100766176425433,11.752037188826135,11.963712565919494,11.963712565919494,3.481853094427695,3.481853094427695 |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.569805089976535,11.916375287812984,11.916375287812984,4.0,10.04987562112089,10.677078252031311,11.224972160321824,13.711309200802088,13.856406460551018,3.4641016151377544,3.4641016151377544                | 0.047337278106508895,0.07100591715976334,0.07100591715976334,0.023668639053254448,0.041420118343195256,0.053254437869822535,0.047337278106508895,0.053254437869822535,0.059171597633136064,0.017751479289940808,0.017751479289940808  | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.617142368083044,11.987381204972747,11.987381204972747,4.023668639053255,10.091295739464085,10.730332689901134,11.272309438428334,13.76456363867191,13.915578058184154,3.481853094427695,3.481853094427695  |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.114877048604,10.770329614269007,12.041594578792296,10.770329614269007,10.770329614269007,10.583005244258363,13.114877048604,13.711309200802088,3.4641016151377544,3.4641016151377544      | 0.059171597633136064,0.07692307692307687,0.047337278106508895,0.059171597633136064,0.047337278106508895,0.047337278106508895,0.041420118343195256,0.053254437869822535,0.053254437869822535,0.017751479289940808,0.017751479289940808 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.191800125527077,10.817666892375517,12.100766176425433,10.817666892375517,10.817666892375517,10.624425362601558,13.168131486473824,13.76456363867191,3.481853094427695,3.481853094427695 |

### Test scores

|       | Grid size cost                              | Value cost                                                                                                                                                           | Pixel overlap cost                                                                                                                                                                                                                | Bounding box cost                           | Total cost                                                                                                                                                                                                   |
|:------|:--------------------------------------------|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,12.0,12.0,14.966629547095765,12.24744871391589,12.922847983320086,13.416407864998739,13.711309200802088,13.711309200802088,3.4641016151377544,2.0 | 0.059171597633136064,0.059171597633136064,0.059171597633136064,0.08284023668639051,0.035502958579881616,0.07692307692307687,0.0650887573964497,0.053254437869822535,0.053254437869822535,0.017751479289940808,0.00591715976331364 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,12.059171597633137,12.059171597633137,15.049469783782156,12.282951672495772,12.999771060243162,13.481496622395188,13.76456363867191,13.76456363867191,3.481853094427695,2.005917159763314 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,27 @@
 def dsl2(I):
-    O = I
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    v = gravitate(s2, s5)
+    dv = double(v)
+    s2p = shift(s2, dv)
+    w = width(s2p)
+    h = height(s2p)
+    right = shift(hmirror(s2p), tojvec(w))
+    left = shift(hmirror(s2p), invert(tojvec(w)))
+    down = shift(vmirror(s2p), toivec(h))
+    up = shift(vmirror(s2p), invert(tojvec(h)))
+    hr = hmatching(s2, s5)
+    hset = initset(right)
+    hset = insert(left, hset)
+    vset = initset(down)
+    vset = insert(up, vset)
+    chooser = lbind(manhattan, s5)
+    besth = argmin(hset, chooser)
+    bestv = argmin(vset, chooser)
+    best = branch(hr, besth, bestv)
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(bg, obj2), obj5)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,29 @@
 def dsl4(I):
-    O = I
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
+    objs = objects(I, T, F, T)
+    o2s = colorfilter(objs, TWO)
+    o5s = colorfilter(objs, FIVE)
+    o2 = first(o2s)
+    o5 = first(o5s)
+    s2 = toindices(o2)
+    s5 = toindices(o5)
+    v = gravitate(s2, s5)
+    s2p = shift(s2, add(v, v))
+    w = width(s2p)
+    h = height(s2p)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    cand_r = shift(mh, tojvec(w))
+    cand_l = shift(mh, invert(tojvec(w)))
+    cand_d = shift(mv, toivec(h))
+    cand_u = shift(mv, invert(toivec(h)))
+    cset = initset(cand_r)
+    cset = insert(cand_l, cset)
+    cset = insert(cand_d, cset)
+    cset = insert(cand_u, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(bg, obj2), obj5)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -4,20 +4,26 @@
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
-    dv = double(v)
-    s2p = shift(s2, dv)
+    s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    cand_r = shift(hmirror(s2p), tojvec(w))
-    cand_l = shift(hmirror(s2p), invert(tojvec(w)))
-    cand_d = shift(vmirror(s2p), toivec(h))
-    cand_u = shift(vmirror(s2p), invert(toivec(h)))
-    cset = initset(cand_r)
-    cset = insert(cand_l, cset)
-    cset = insert(cand_d, cset)
-    cset = insert(cand_u, cset)
-    chooser = lbind(manhattan, s5)
-    best = argmin(cset, chooser)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    offR = tojvec(w)
+    offL = invert(offR)
+    offD = toivec(h)
+    offU = invert(offD)
+    candR = shift(mh, offR)
+    candL = shift(mh, offL)
+    candD = shift(mv, offD)
+    candU = shift(mv, offU)
+    isR = equality(v, RIGHT)
+    isL = equality(v, LEFT)
+    isD = equality(v, DOWN)
+    hor = either(isR, isL)
+    bestRL = branch(isR, candR, candL)
+    bestUD = branch(isD, candD, candU)
+    best = branch(hor, bestRL, bestUD)
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -9,21 +9,19 @@
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    offR = tojvec(w)
-    offL = invert(offR)
-    offD = toivec(h)
-    offU = invert(offD)
-    s5candR = shift(mh, offR)
-    s5candL = shift(mh, offL)
-    s5candD = shift(mv, offD)
-    s5candU = shift(mv, offU)
-    isR = equality(v, RIGHT)
-    isL = equality(v, LEFT)
-    isD = equality(v, DOWN)
-    bestRL = branch(isR, s5candR, s5candL)
-    bestUD = branch(isD, s5candD, s5candU)
-    hor = either(isR, isL)
-    best = branch(hor, bestRL, bestUD)
+    right = shift(mh, tojvec(w))
+    left = shift(mh, invert(tojvec(w)))
+    down = shift(mv, toivec(h))
+    up = shift(mv, invert(toivec(h)))
+    hr = hmatching(s2, s5)
+    hset = initset(right)
+    hset = insert(left, hset)
+    vset = initset(down)
+    vset = insert(up, vset)
+    chooser = lbind(manhattan, s5)
+    besth = argmin(hset, chooser)
+    bestv = argmin(vset, chooser)
+    best = branch(hr, besth, bestv)
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -6,14 +6,16 @@
     s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    mr = shift(hmirror(s2p), tojvec(w))
-    ml = shift(hmirror(s2p), invert(tojvec(w)))
-    md = shift(vmirror(s2p), toivec(h))
-    mu = shift(vmirror(s2p), invert(toivec(h)))
-    cset = initset(mr)
-    cset = insert(ml, cset)
-    cset = insert(md, cset)
-    cset = insert(mu, cset)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    candR = shift(mh, tojvec(w))
+    candL = shift(mh, invert(tojvec(w)))
+    candD = shift(mv, toivec(h))
+    candU = shift(mv, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
     best = argmin(cset, lbind(manhattan, s5))
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -2,28 +2,25 @@
     dims = shape(I)
     bg = canvas(SEVEN, dims)
     objs = objects(I, T, F, T)
-    o2s = colorfilter(objs, TWO)
-    o5s = colorfilter(objs, FIVE)
-    o2 = first(o2s)
-    o5 = first(o5s)
+    o2 = first(colorfilter(objs, TWO))
+    o5 = first(colorfilter(objs, FIVE))
     s2 = toindices(o2)
     s5 = toindices(o5)
-    v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    rel = position(s2, s5)
+    dirv = sign(rel)
+    s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    candR = shift(mh, tojvec(w))
-    candL = shift(mh, invert(tojvec(w)))
-    candD = shift(mv, toivec(h))
-    candU = shift(mv, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
-    best = argmin(cset, lbind(manhattan, s5))
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    hr = hmatching(s2, s5)
+    hset = initset(shift(mh, tojvec(w)))
+    hset = insert(shift(mh, invert(tojvec(w))), hset)
+    vset = initset(shift(mv, toivec(h)))
+    vset = insert(shift(mv, invert(toivec(h))), vset)
+    chooser = lbind(manhattan, s5)
+    besth = argmin(hset, chooser)
+    bestv = argmin(vset, chooser)
+    best = branch(hr, besth, bestv)
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -9,24 +9,16 @@
     s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
-    mh = hmirror(s2p)
-    mv = vmirror(s2p)
-    offR = tojvec(w)
-    offL = invert(offR)
-    offD = toivec(h)
-    offU = invert(offD)
-    candR = shift(mh, offR)
-    candL = shift(mh, offL)
-    candD = shift(mv, offD)
-    candU = shift(mv, offU)
-    isR = equality(dirv, RIGHT)
-    isL = equality(dirv, LEFT)
-    isD = equality(dirv, DOWN)
-    hor = either(isR, isL)
-    bestRL = branch(isR, candR, candL)
-    bestUD = branch(isD, candD, candU)
-    best = branch(hor, bestRL, bestUD)
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    dd = dmirror(s2p)
+    cc = cmirror(s2p)
+    cand1 = shift(dd, tojvec(w))
+    cand2 = shift(dd, invert(tojvec(w)))
+    cand3 = shift(cc, toivec(h))
+    cand4 = shift(cc, invert(toivec(h)))
+    cset = initset(cand1)
+    cset = insert(cand2, cset)
+    cset = insert(cand3, cset)
+    cset = insert(cand4, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -3,22 +3,25 @@
     bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    com2 = centerofmass(s2)
-    com5 = centerofmass(s5)
-    dirv = sign(subtract(com5, com2))
-    s2p = shift(s2, double(dirv))
+    v = gravitate(s2, s5)
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    candR = shift(mh, tojvec(w))
-    candL = shift(mh, invert(tojvec(w)))
-    candD = shift(mv, toivec(h))
-    candU = shift(mv, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
-    best = argmin(cset, lbind(manhattan, s5))
+    l2 = leftmost(s2p)
+    t2 = uppermost(s2p)
+    r5 = rightmost(s5)
+    b5 = lowermost(s5)
+    w1 = decrement(w)
+    h1 = decrement(h)
+    tL = subtract(r5, w1)
+    tT = subtract(b5, h1)
+    dx = subtract(tL, l2)
+    dy = subtract(tT, t2)
+    candH = shift(mh, tojvec(dx))
+    candV = shift(mv, toivec(dy))
+    hr = hmatching(s2, s5)
+    best = branch(hr, candH, candV)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -4,18 +4,33 @@
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
-    rot = vmirror(hmirror(s2p))
-    candR = shift(rot, tojvec(w))
-    candL = shift(rot, invert(tojvec(w)))
-    candD = shift(rot, toivec(h))
-    candU = shift(rot, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    l2 = leftmost(s2p)
+    t2 = uppermost(s2p)
+    l5 = leftmost(s5)
+    r5 = rightmost(s5)
+    t5 = uppermost(s5)
+    b5 = lowermost(s5)
+    w1 = decrement(w)
+    h1 = decrement(h)
+    tL = subtract(r5, w1)
+    tT = subtract(b5, h1)
+    dxR = subtract(tL, l2)
+    dxL = subtract(l5, l2)
+    dyB = subtract(tT, t2)
+    dyT = subtract(t5, t2)
+    c1 = shift(mh, tojvec(dxR))
+    c2 = shift(mh, tojvec(dxL))
+    c3 = shift(mv, toivec(dyB))
+    c4 = shift(mv, toivec(dyT))
+    cset = initset(c1)
+    cset = insert(c2, cset)
+    cset = insert(c3, cset)
+    cset = insert(c4, cset)
     best = argmin(cset, lbind(manhattan, s5))
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -4,19 +4,21 @@
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    cand = initset(shift(s2p, tojvec(w)))
-    cand = insert(shift(s2p, invert(tojvec(w))), cand)
-    cand = insert(shift(s2p, toivec(h)), cand)
-    cand = insert(shift(s2p, invert(toivec(h))), cand)
-    cand = insert(shift(mh, tojvec(w)), cand)
-    cand = insert(shift(mh, invert(tojvec(w))), cand)
-    cand = insert(shift(mv, toivec(h)), cand)
-    cand = insert(shift(mv, invert(toivec(h))), cand)
-    best = argmin(cand, lbind(manhattan, s5))
+    wgap = add(w, ONE)
+    hgap = add(h, ONE)
+    candR = shift(mh, tojvec(wgap))
+    candL = shift(mh, invert(tojvec(wgap)))
+    candD = shift(mv, toivec(hgap))
+    candU = shift(mv, invert(toivec(hgap)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

## Program 3

### Train scores

|        | Grid size cost                              | Value cost                                                                                                                                                                                      | Pixel overlap cost                                                                                                                                                                                                                | Bounding box cost                           | Total cost                                                                                                                                                                                                    |
|:-------|:--------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.856406460551018,13.856406460551018,13.856406460551018,11.0,13.2664991614216,13.856406460551018,12.922847983320086,13.856406460551018,0.0,4.0                              | 0.059171597633136064,0.08284023668639051,0.08284023668639051,0.08284023668639051,0.047337278106508895,0.059171597633136064,0.08284023668639051,0.053254437869822535,0.059171597633136064,0.0,0.023668639053254448                 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.939246697237408,13.939246697237408,13.939246697237408,11.04733727810651,13.325670759054736,13.939246697237408,12.976102421189909,13.915578058184154,0.0,4.023668639053255               |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.569805089976535,11.045361017187261,11.916375287812984,11.916375287812984,10.04987562112089,10.862780491200215,11.575836902790225,8.18535277187245,11.916375287812984,2.0,2.0                 | 0.047337278106508895,0.0650887573964497,0.07100591715976334,0.07100591715976334,0.041420118343195256,0.035502958579881616,0.059171597633136064,0.029585798816568087,0.047337278106508895,0.00591715976331364,0.00591715976331364  | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.617142368083044,11.11044977458371,11.987381204972747,11.987381204972747,10.091295739464085,10.898283449780097,11.635008500423362,8.214938570689018,11.963712565919494,2.005917159763314,2.005917159763314  |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.856406460551018,13.856406460551018,13.564659966250536,11.789826122551595,12.96148139681572,13.856406460551018,10.04987562112089,14.422205101855956,3.4641016151377544,2.0 | 0.059171597633136064,0.08284023668639051,0.08284023668639051,0.07100591715976334,0.059171597633136064,0.047337278106508895,0.08284023668639051,0.041420118343195256,0.059171597633136064,0.017751479289940808,0.00591715976331364 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.939246697237408,13.939246697237408,13.635665883410299,11.848997720184732,13.00881867492223,13.939246697237408,10.091295739464085,14.481376699489093,3.481853094427695,2.005917159763314 |

### Test scores

|       | Grid size cost                              | Value cost                                                                                                                                                                                        | Pixel overlap cost                                                                                                                                                                                                                  | Bounding box cost                           | Total cost                                                                                                                                                                                                     |
|:------|:--------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.856406460551018,12.0,12.489995996796797,11.916375287812984,12.96148139681572,12.922847983320086,11.224972160321824,14.422205101855956,2.8284271247461903,2.8284271247461903 | 0.059171597633136064,0.08284023668639051,0.059171597633136064,0.053254437869822535,0.07100591715976334,0.047337278106508895,0.07692307692307687,0.047337278106508895,0.059171597633136064,0.011834319526627168,0.011834319526627168 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.939246697237408,12.059171597633137,12.54325043466662,11.987381204972747,13.00881867492223,12.999771060243162,11.272309438428334,14.481376699489093,2.8402614442728176,2.8402614442728176 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,30 @@
 def dsl3(I):
-    O = I
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    v = gravitate(s2, s5)
+    s2p = shift(s2, double(v))
+    w = width(s2p)
+    h = height(s2p)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    offR = tojvec(w)
+    offL = invert(offR)
+    offD = toivec(h)
+    offU = invert(offD)
+    s5candR = shift(mh, offR)
+    s5candL = shift(mh, offL)
+    s5candD = shift(mv, offD)
+    s5candU = shift(mv, offU)
+    isR = equality(v, RIGHT)
+    isL = equality(v, LEFT)
+    isD = equality(v, DOWN)
+    bestRL = branch(isR, s5candR, s5candL)
+    bestUD = branch(isD, s5candD, s5candU)
+    hor = either(isR, isL)
+    best = branch(hor, bestRL, bestUD)
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(bg, obj2), obj5)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,21 @@
 def dsl5(I):
-    O = I
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    clean = cover(cover(I, s2), s5)
+    v = gravitate(s2, s5)
+    s2p = shift(s2, double(v))
+    w = width(s2p)
+    h = height(s2p)
+    mr = shift(hmirror(s2p), tojvec(w))
+    ml = shift(hmirror(s2p), invert(tojvec(w)))
+    md = shift(vmirror(s2p), toivec(h))
+    mu = shift(vmirror(s2p), invert(toivec(h)))
+    cset = initset(mr)
+    cset = insert(ml, cset)
+    cset = insert(md, cset)
+    cset = insert(mu, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(clean, obj2), obj5)
     return O
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,26 +1,28 @@
 def dsl2(I):
     dims = shape(I)
     bg = canvas(SEVEN, dims)
-    s2 = ofcolor(I, TWO)
-    s5 = ofcolor(I, FIVE)
+    objs = objects(I, T, F, T)
+    o2s = colorfilter(objs, TWO)
+    o5s = colorfilter(objs, FIVE)
+    o2 = first(o2s)
+    o5 = first(o5s)
+    s2 = toindices(o2)
+    s5 = toindices(o5)
     v = gravitate(s2, s5)
-    dv = double(v)
-    s2p = shift(s2, dv)
+    s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    right = shift(hmirror(s2p), tojvec(w))
-    left = shift(hmirror(s2p), invert(tojvec(w)))
-    down = shift(vmirror(s2p), toivec(h))
-    up = shift(vmirror(s2p), invert(tojvec(h)))
-    hr = hmatching(s2, s5)
-    hset = initset(right)
-    hset = insert(left, hset)
-    vset = initset(down)
-    vset = insert(up, vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
-    best = branch(hr, besth, bestv)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    candR = shift(mh, tojvec(w))
+    candL = shift(mh, invert(tojvec(w)))
+    candD = shift(mv, toivec(h))
+    candU = shift(mv, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -1,28 +1,31 @@
 def dsl4(I):
     dims = shape(I)
     bg = canvas(SEVEN, dims)
-    objs = objects(I, T, F, T)
-    o2s = colorfilter(objs, TWO)
-    o5s = colorfilter(objs, FIVE)
-    o2 = first(o2s)
-    o5 = first(o5s)
-    s2 = toindices(o2)
-    s5 = toindices(o5)
-    v = gravitate(s2, s5)
-    s2p = shift(s2, add(v, v))
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    com2 = centerofmass(s2)
+    com5 = centerofmass(s5)
+    dirv = sign(subtract(com5, com2))
+    s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    cand_r = shift(mh, tojvec(w))
-    cand_l = shift(mh, invert(tojvec(w)))
-    cand_d = shift(mv, toivec(h))
-    cand_u = shift(mv, invert(toivec(h)))
-    cset = initset(cand_r)
-    cset = insert(cand_l, cset)
-    cset = insert(cand_d, cset)
-    cset = insert(cand_u, cset)
-    best = argmin(cset, lbind(manhattan, s5))
+    offR = tojvec(w)
+    offL = invert(offR)
+    offD = toivec(h)
+    offU = invert(offD)
+    candR = shift(mh, offR)
+    candL = shift(mh, offL)
+    candD = shift(mv, offD)
+    candU = shift(mv, offU)
+    isR = equality(dirv, RIGHT)
+    isL = equality(dirv, LEFT)
+    isD = equality(dirv, DOWN)
+    hor = either(isR, isL)
+    bestRL = branch(isR, candR, candL)
+    bestUD = branch(isD, candD, candU)
+    best = branch(hor, bestRL, bestUD)
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -3,28 +3,22 @@
     bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    com2 = centerofmass(s2)
+    com5 = centerofmass(s5)
+    dirv = sign(subtract(com5, com2))
+    s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    offR = tojvec(w)
-    offL = invert(offR)
-    offD = toivec(h)
-    offU = invert(offD)
-    candR = shift(mh, offR)
-    candL = shift(mh, offL)
-    candD = shift(mv, offD)
-    candU = shift(mv, offU)
-    isR = equality(v, RIGHT)
-    isL = equality(v, LEFT)
-    isD = equality(v, DOWN)
-    hor = either(isR, isL)
-    bestRL = branch(isR, candR, candL)
-    bestUD = branch(isD, candD, candU)
-    best = branch(hor, bestRL, bestUD)
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    candR = shift(mh, tojvec(w))
+    candL = shift(mh, invert(tojvec(w)))
+    candD = shift(mv, toivec(h))
+    candU = shift(mv, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -7,22 +7,15 @@
     s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    mh = hmirror(s2p)
-    mv = vmirror(s2p)
-    right = shift(mh, tojvec(w))
-    left = shift(mh, invert(tojvec(w)))
-    down = shift(mv, toivec(h))
-    up = shift(mv, invert(toivec(h)))
-    hr = hmatching(s2, s5)
-    hset = initset(right)
-    hset = insert(left, hset)
-    vset = initset(down)
-    vset = insert(up, vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
-    best = branch(hr, besth, bestv)
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    rot = vmirror(hmirror(s2p))
+    candR = shift(rot, tojvec(w))
+    candL = shift(rot, invert(tojvec(w)))
+    candD = shift(rot, toivec(h))
+    candU = shift(rot, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -1,23 +1,22 @@
 def dsl5(I):
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    clean = cover(cover(I, s2), s5)
     v = gravitate(s2, s5)
     s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    candR = shift(mh, tojvec(w))
-    candL = shift(mh, invert(tojvec(w)))
-    candD = shift(mv, toivec(h))
-    candU = shift(mv, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
-    best = argmin(cset, lbind(manhattan, s5))
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(clean, obj2), obj5)
+    cand = initset(shift(s2p, tojvec(w)))
+    cand = insert(shift(s2p, invert(tojvec(w))), cand)
+    cand = insert(shift(s2p, toivec(h)), cand)
+    cand = insert(shift(s2p, invert(toivec(h))), cand)
+    cand = insert(shift(mh, tojvec(w)), cand)
+    cand = insert(shift(mh, invert(tojvec(w))), cand)
+    cand = insert(shift(mv, toivec(h)), cand)
+    cand = insert(shift(mv, invert(toivec(h))), cand)
+    best = argmin(cand, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -6,21 +6,36 @@
     o5 = first(colorfilter(objs, FIVE))
     s2 = toindices(o2)
     s5 = toindices(o5)
-    rel = position(s2, s5)
-    dirv = sign(rel)
-    s2p = shift(s2, double(dirv))
+    v = gravitate(s2, s5)
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
+    l2 = leftmost(s2p)
+    t2 = uppermost(s2p)
+    l5 = leftmost(s5)
+    r5 = rightmost(s5)
+    t5 = uppermost(s5)
+    b5 = lowermost(s5)
+    w1 = decrement(w)
+    h1 = decrement(h)
+    tL = subtract(r5, w1)
+    tT = subtract(b5, h1)
+    dxR = subtract(tL, l2)
+    dxL = subtract(l5, l2)
+    dyB = subtract(tT, t2)
+    dyT = subtract(t5, t2)
+    cH1 = shift(mh, tojvec(dxR))
+    cH2 = shift(mh, tojvec(dxL))
+    cV1 = shift(mv, toivec(dyB))
+    cV2 = shift(mv, toivec(dyT))
+    chooser = lbind(manhattan, s5)
+    besth = argmin(initset(cH1), chooser)
+    besth = branch(greater(chooser(cH2), chooser(besth)), besth, cH2)
+    bestv = argmin(initset(cV1), chooser)
+    bestv = branch(greater(chooser(cV2), chooser(bestv)), bestv, cV2)
     hr = hmatching(s2, s5)
-    hset = initset(shift(mh, tojvec(w)))
-    hset = insert(shift(mh, invert(tojvec(w))), hset)
-    vset = initset(shift(mv, toivec(h)))
-    vset = insert(shift(mv, invert(toivec(h))), vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
     best = branch(hr, besth, bestv)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -3,22 +3,13 @@
     bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    com2 = centerofmass(s2)
-    com5 = centerofmass(s5)
-    dirv = sign(subtract(com5, com2))
-    s2p = shift(s2, double(dirv))
-    w = width(s2p)
-    h = height(s2p)
-    dd = dmirror(s2p)
-    cc = cmirror(s2p)
-    cand1 = shift(dd, tojvec(w))
-    cand2 = shift(dd, invert(tojvec(w)))
-    cand3 = shift(cc, toivec(h))
-    cand4 = shift(cc, invert(toivec(h)))
-    cset = initset(cand1)
-    cset = insert(cand2, cset)
-    cset = insert(cand3, cset)
-    cset = insert(cand4, cset)
-    best = argmin(cset, lbind(manhattan, s5))
+    v = gravitate(s2, s5)
+    s2p = shift(s2, multiply(v, TWO))
+    hr = hmatching(s2, s5)
+    mir = branch(hr, hmirror(s2p), vmirror(s2p))
+    c_mir = center(mir)
+    c_s5 = center(s5)
+    off = subtract(c_s5, c_mir)
+    best = shift(mir, off)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -5,23 +5,13 @@
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
     s2p = shift(s2, multiply(v, TWO))
-    w = width(s2p)
-    h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    l2 = leftmost(s2p)
-    t2 = uppermost(s2p)
-    r5 = rightmost(s5)
-    b5 = lowermost(s5)
-    w1 = decrement(w)
-    h1 = decrement(h)
-    tL = subtract(r5, w1)
-    tT = subtract(b5, h1)
-    dx = subtract(tL, l2)
-    dy = subtract(tT, t2)
-    candH = shift(mh, tojvec(dx))
-    candV = shift(mv, toivec(dy))
-    hr = hmatching(s2, s5)
-    best = branch(hr, candH, candV)
+    c5 = centerofmass(s5)
+    ch = centerofmass(mh)
+    cv = centerofmass(mv)
+    posh = shift(mh, subtract(c5, ch))
+    posv = shift(mv, subtract(c5, cv))
+    best = branch(adjacent(posh, s5), posh, posv)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

## Program 4

### Train scores

|        | Grid size cost                              | Value cost                                                                                                                                                                                       | Pixel overlap cost                                                                                                                                                                                                                     | Bounding box cost                           | Total cost                                                                                                                                                                                                     |
|:-------|:--------------------------------------------|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,12.041594578792296,4.0,5.656854249492381,12.083045973594572,12.083045973594572,11.789826122551595,14.422205101855956,14.422205101855956,4.0,3.4641016151377544                | 0.059171597633136064,0.059171597633136064,0.023668639053254448,0.047337278106508895,0.053254437869822535,0.053254437869822535,0.059171597633136064,0.059171597633136064,0.059171597633136064,0.023668639053254448,0.017751479289940808 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,12.100766176425433,4.023668639053255,5.70419152759889,12.136300411464395,12.136300411464395,11.848997720184732,14.481376699489093,14.481376699489093,4.023668639053255,3.481853094427695    |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.569805089976535,11.916375287812984,4.0,4.0,10.04987562112089,9.539392014169456,11.357816691600547,14.422205101855956,12.569805089976535,0.0,2.0                                               | 0.047337278106508895,0.07100591715976334,0.023668639053254448,0.023668639053254448,0.041420118343195256,0.041420118343195256,0.059171597633136064,0.059171597633136064,0.047337278106508895,0.0,0.00591715976331364                    | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.617142368083044,11.987381204972747,4.023668639053255,4.023668639053255,10.091295739464085,9.580812132512651,11.416988289233684,14.481376699489093,12.617142368083044,0.0,2.005917159763314                  |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,10.770329614269007,2.8284271247461903,4.898979485566356,12.083045973594572,12.409673645990857,13.564659966250536,14.422205101855956,12.569805089976535,2.8284271247461903,2.0 | 0.059171597633136064,0.047337278106508895,0.011834319526627168,0.035502958579881616,0.053254437869822535,0.0650887573964497,0.07100591715976334,0.059171597633136064,0.047337278106508895,0.011834319526627168,0.00591715976331364     | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,10.817666892375517,2.8402614442728176,4.934482444146237,12.136300411464395,12.474762403387306,13.635665883410299,14.481376699489093,12.617142368083044,2.8402614442728176,2.005917159763314 |

### Test scores

|       | Grid size cost                              | Value cost                                                                                                                                                                          | Pixel overlap cost                                                                                                                                                                                                                  | Bounding box cost                           | Total cost                                                                                                                                                                                                      |
|:------|:--------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,12.0,11.575836902790225,11.575836902790225,13.076696830622021,12.083045973594572,12.409673645990857,12.569805089976535,14.422205101855956,2.8284271247461903,2.0 | 0.059171597633136064,0.059171597633136064,0.059171597633136064,0.059171597633136064,0.059171597633136064,0.053254437869822535,0.0650887573964497,0.047337278106508895,0.059171597633136064,0.011834319526627168,0.00591715976331364 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,12.059171597633137,11.635008500423362,11.635008500423362,13.135868428255158,12.136300411464395,12.474762403387306,12.617142368083044,14.481376699489093,2.8402614442728176,2.005917159763314 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,29 @@
 def dsl4(I):
-    O = I
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
+    objs = objects(I, T, F, T)
+    o2s = colorfilter(objs, TWO)
+    o5s = colorfilter(objs, FIVE)
+    o2 = first(o2s)
+    o5 = first(o5s)
+    s2 = toindices(o2)
+    s5 = toindices(o5)
+    v = gravitate(s2, s5)
+    s2p = shift(s2, add(v, v))
+    w = width(s2p)
+    h = height(s2p)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    cand_r = shift(mh, tojvec(w))
+    cand_l = shift(mh, invert(tojvec(w)))
+    cand_d = shift(mv, toivec(h))
+    cand_u = shift(mv, invert(toivec(h)))
+    cset = initset(cand_r)
+    cset = insert(cand_l, cset)
+    cset = insert(cand_d, cset)
+    cset = insert(cand_u, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(bg, obj2), obj5)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -4,20 +4,26 @@
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
-    dv = double(v)
-    s2p = shift(s2, dv)
+    s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    cand_r = shift(hmirror(s2p), tojvec(w))
-    cand_l = shift(hmirror(s2p), invert(tojvec(w)))
-    cand_d = shift(vmirror(s2p), toivec(h))
-    cand_u = shift(vmirror(s2p), invert(toivec(h)))
-    cset = initset(cand_r)
-    cset = insert(cand_l, cset)
-    cset = insert(cand_d, cset)
-    cset = insert(cand_u, cset)
-    chooser = lbind(manhattan, s5)
-    best = argmin(cset, chooser)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    offR = tojvec(w)
+    offL = invert(offR)
+    offD = toivec(h)
+    offU = invert(offD)
+    candR = shift(mh, offR)
+    candL = shift(mh, offL)
+    candD = shift(mv, offD)
+    candU = shift(mv, offU)
+    isR = equality(v, RIGHT)
+    isL = equality(v, LEFT)
+    isD = equality(v, DOWN)
+    hor = either(isR, isL)
+    bestRL = branch(isR, candR, candL)
+    bestUD = branch(isD, candD, candU)
+    best = branch(hor, bestRL, bestUD)
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -9,21 +9,19 @@
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    offR = tojvec(w)
-    offL = invert(offR)
-    offD = toivec(h)
-    offU = invert(offD)
-    s5candR = shift(mh, offR)
-    s5candL = shift(mh, offL)
-    s5candD = shift(mv, offD)
-    s5candU = shift(mv, offU)
-    isR = equality(v, RIGHT)
-    isL = equality(v, LEFT)
-    isD = equality(v, DOWN)
-    bestRL = branch(isR, s5candR, s5candL)
-    bestUD = branch(isD, s5candD, s5candU)
-    hor = either(isR, isL)
-    best = branch(hor, bestRL, bestUD)
+    right = shift(mh, tojvec(w))
+    left = shift(mh, invert(tojvec(w)))
+    down = shift(mv, toivec(h))
+    up = shift(mv, invert(toivec(h)))
+    hr = hmatching(s2, s5)
+    hset = initset(right)
+    hset = insert(left, hset)
+    vset = initset(down)
+    vset = insert(up, vset)
+    chooser = lbind(manhattan, s5)
+    besth = argmin(hset, chooser)
+    bestv = argmin(vset, chooser)
+    best = branch(hr, besth, bestv)
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -6,14 +6,16 @@
     s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    mr = shift(hmirror(s2p), tojvec(w))
-    ml = shift(hmirror(s2p), invert(tojvec(w)))
-    md = shift(vmirror(s2p), toivec(h))
-    mu = shift(vmirror(s2p), invert(toivec(h)))
-    cset = initset(mr)
-    cset = insert(ml, cset)
-    cset = insert(md, cset)
-    cset = insert(mu, cset)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    candR = shift(mh, tojvec(w))
+    candL = shift(mh, invert(tojvec(w)))
+    candD = shift(mv, toivec(h))
+    candU = shift(mv, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
     best = argmin(cset, lbind(manhattan, s5))
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -2,28 +2,25 @@
     dims = shape(I)
     bg = canvas(SEVEN, dims)
     objs = objects(I, T, F, T)
-    o2s = colorfilter(objs, TWO)
-    o5s = colorfilter(objs, FIVE)
-    o2 = first(o2s)
-    o5 = first(o5s)
+    o2 = first(colorfilter(objs, TWO))
+    o5 = first(colorfilter(objs, FIVE))
     s2 = toindices(o2)
     s5 = toindices(o5)
-    v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    rel = position(s2, s5)
+    dirv = sign(rel)
+    s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    candR = shift(mh, tojvec(w))
-    candL = shift(mh, invert(tojvec(w)))
-    candD = shift(mv, toivec(h))
-    candU = shift(mv, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
-    best = argmin(cset, lbind(manhattan, s5))
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    hr = hmatching(s2, s5)
+    hset = initset(shift(mh, tojvec(w)))
+    hset = insert(shift(mh, invert(tojvec(w))), hset)
+    vset = initset(shift(mv, toivec(h)))
+    vset = insert(shift(mv, invert(toivec(h))), vset)
+    chooser = lbind(manhattan, s5)
+    besth = argmin(hset, chooser)
+    bestv = argmin(vset, chooser)
+    best = branch(hr, besth, bestv)
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -9,24 +9,16 @@
     s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
-    mh = hmirror(s2p)
-    mv = vmirror(s2p)
-    offR = tojvec(w)
-    offL = invert(offR)
-    offD = toivec(h)
-    offU = invert(offD)
-    candR = shift(mh, offR)
-    candL = shift(mh, offL)
-    candD = shift(mv, offD)
-    candU = shift(mv, offU)
-    isR = equality(dirv, RIGHT)
-    isL = equality(dirv, LEFT)
-    isD = equality(dirv, DOWN)
-    hor = either(isR, isL)
-    bestRL = branch(isR, candR, candL)
-    bestUD = branch(isD, candD, candU)
-    best = branch(hor, bestRL, bestUD)
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    dd = dmirror(s2p)
+    cc = cmirror(s2p)
+    cand1 = shift(dd, tojvec(w))
+    cand2 = shift(dd, invert(tojvec(w)))
+    cand3 = shift(cc, toivec(h))
+    cand4 = shift(cc, invert(toivec(h)))
+    cset = initset(cand1)
+    cset = insert(cand2, cset)
+    cset = insert(cand3, cset)
+    cset = insert(cand4, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -3,22 +3,25 @@
     bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    com2 = centerofmass(s2)
-    com5 = centerofmass(s5)
-    dirv = sign(subtract(com5, com2))
-    s2p = shift(s2, double(dirv))
+    v = gravitate(s2, s5)
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    candR = shift(mh, tojvec(w))
-    candL = shift(mh, invert(tojvec(w)))
-    candD = shift(mv, toivec(h))
-    candU = shift(mv, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
-    best = argmin(cset, lbind(manhattan, s5))
+    l2 = leftmost(s2p)
+    t2 = uppermost(s2p)
+    r5 = rightmost(s5)
+    b5 = lowermost(s5)
+    w1 = decrement(w)
+    h1 = decrement(h)
+    tL = subtract(r5, w1)
+    tT = subtract(b5, h1)
+    dx = subtract(tL, l2)
+    dy = subtract(tT, t2)
+    candH = shift(mh, tojvec(dx))
+    candV = shift(mv, toivec(dy))
+    hr = hmatching(s2, s5)
+    best = branch(hr, candH, candV)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -4,18 +4,33 @@
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
-    rot = vmirror(hmirror(s2p))
-    candR = shift(rot, tojvec(w))
-    candL = shift(rot, invert(tojvec(w)))
-    candD = shift(rot, toivec(h))
-    candU = shift(rot, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    l2 = leftmost(s2p)
+    t2 = uppermost(s2p)
+    l5 = leftmost(s5)
+    r5 = rightmost(s5)
+    t5 = uppermost(s5)
+    b5 = lowermost(s5)
+    w1 = decrement(w)
+    h1 = decrement(h)
+    tL = subtract(r5, w1)
+    tT = subtract(b5, h1)
+    dxR = subtract(tL, l2)
+    dxL = subtract(l5, l2)
+    dyB = subtract(tT, t2)
+    dyT = subtract(t5, t2)
+    c1 = shift(mh, tojvec(dxR))
+    c2 = shift(mh, tojvec(dxL))
+    c3 = shift(mv, toivec(dyB))
+    c4 = shift(mv, toivec(dyT))
+    cset = initset(c1)
+    cset = insert(c2, cset)
+    cset = insert(c3, cset)
+    cset = insert(c4, cset)
     best = argmin(cset, lbind(manhattan, s5))
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -4,19 +4,21 @@
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    cand = initset(shift(s2p, tojvec(w)))
-    cand = insert(shift(s2p, invert(tojvec(w))), cand)
-    cand = insert(shift(s2p, toivec(h)), cand)
-    cand = insert(shift(s2p, invert(toivec(h))), cand)
-    cand = insert(shift(mh, tojvec(w)), cand)
-    cand = insert(shift(mh, invert(tojvec(w))), cand)
-    cand = insert(shift(mv, toivec(h)), cand)
-    cand = insert(shift(mv, invert(toivec(h))), cand)
-    best = argmin(cand, lbind(manhattan, s5))
+    wgap = add(w, ONE)
+    hgap = add(h, ONE)
+    candR = shift(mh, tojvec(wgap))
+    candL = shift(mh, invert(tojvec(wgap)))
+    candD = shift(mv, toivec(hgap))
+    candU = shift(mv, invert(toivec(hgap)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -8,34 +8,13 @@
     s5 = toindices(o5)
     v = gravitate(s2, s5)
     s2p = shift(s2, multiply(v, TWO))
-    w = width(s2p)
-    h = height(s2p)
+    rel = position(s2p, s5)
+    off = invert(rel)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    l2 = leftmost(s2p)
-    t2 = uppermost(s2p)
-    l5 = leftmost(s5)
-    r5 = rightmost(s5)
-    t5 = uppermost(s5)
-    b5 = lowermost(s5)
-    w1 = decrement(w)
-    h1 = decrement(h)
-    tL = subtract(r5, w1)
-    tT = subtract(b5, h1)
-    dxR = subtract(tL, l2)
-    dxL = subtract(l5, l2)
-    dyB = subtract(tT, t2)
-    dyT = subtract(t5, t2)
-    cH1 = shift(mh, tojvec(dxR))
-    cH2 = shift(mh, tojvec(dxL))
-    cV1 = shift(mv, toivec(dyB))
-    cV2 = shift(mv, toivec(dyT))
-    chooser = lbind(manhattan, s5)
-    besth = argmin(initset(cH1), chooser)
-    besth = branch(greater(chooser(cH2), chooser(besth)), besth, cH2)
-    bestv = argmin(initset(cV1), chooser)
-    bestv = branch(greater(chooser(cV2), chooser(bestv)), bestv, cV2)
-    hr = hmatching(s2, s5)
-    best = branch(hr, besth, bestv)
+    ph = shift(mh, off)
+    pv = shift(mv, off)
+    cset = insert(pv, initset(ph))
+    best = argmin(cset, lbind(manhattan, s5))
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

## Program 5

### Train scores

|        | Grid size cost                              | Value cost                                                                                                                                                                                                       | Pixel overlap cost                                                                                                                                                                                                                  | Bounding box cost                           | Total cost                                                                                                                                                                                                     |
|:-------|:--------------------------------------------|:-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| train1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.856406460551018,13.856406460551018,10.583005244258363,13.114877048604,12.083045973594572,13.114877048604,2.8284271247461903,14.422205101855956,2.8284271247461903,4.0                      | 0.059171597633136064,0.08284023668639051,0.08284023668639051,0.059171597633136064,0.07692307692307687,0.053254437869822535,0.053254437869822535,0.011834319526627168,0.059171597633136064,0.011834319526627168,0.023668639053254448 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.939246697237408,13.939246697237408,10.6421768418915,13.191800125527077,12.136300411464395,13.168131486473824,2.8402614442728176,14.481376699489093,2.8402614442728176,4.023668639053255  |
| train2 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.569805089976535,11.916375287812984,11.916375287812984,11.916375287812984,11.916375287812984,8.717797887081348,10.099504938362077,2.8284271247461903,14.422205101855956,2.8284271247461903,3.4641016151377544  | 0.047337278106508895,0.07100591715976334,0.07100591715976334,0.07100591715976334,0.07100591715976334,0.035502958579881616,0.035502958579881616,0.011834319526627168,0.059171597633136064,0.011834319526627168,0.017751479289940808  | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 12.617142368083044,11.987381204972747,11.987381204972747,11.987381204972747,11.987381204972747,8.75330084566123,10.135007896941959,2.8402614442728176,14.481376699489093,2.8402614442728176,3.481853094427695  |
| train3 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,13.856406460551018,13.856406460551018,13.856406460551018,13.856406460551018,12.083045973594572,12.489995996796797,2.8284271247461903,14.422205101855956,2.8284271247461903,3.4641016151377544 | 0.059171597633136064,0.08284023668639051,0.08284023668639051,0.08284023668639051,0.08284023668639051,0.053254437869822535,0.053254437869822535,0.011834319526627168,0.059171597633136064,0.011834319526627168,0.017751479289940808  | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,13.939246697237408,13.939246697237408,13.939246697237408,13.939246697237408,12.136300411464395,12.54325043466662,2.8402614442728176,14.481376699489093,2.8402614442728176,3.481853094427695 |

### Test scores

|       | Grid size cost                              | Value cost                                                                                                                                                           | Pixel overlap cost                                                                                                                                                                                                                    | Bounding box cost                           | Total cost                                                                                                                                                                                                      |
|:------|:--------------------------------------------|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| test1 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.422205101855956,12.0,12.0,12.0,12.328828005937952,12.24744871391589,12.96148139681572,2.8284271247461903,14.422205101855956,2.8284271247461903,2.8284271247461903 | 0.059171597633136064,0.059171597633136064,0.059171597633136064,0.059171597633136064,0.07100591715976334,0.035502958579881616,0.047337278106508895,0.011834319526627168,0.059171597633136064,0.011834319526627168,0.011834319526627168 | 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 | 14.481376699489093,12.059171597633137,12.059171597633137,12.059171597633137,12.399833923097715,12.282951672495772,13.00881867492223,2.8402614442728176,14.481376699489093,2.8402614442728176,2.8402614442728176 |

### Iteration 1 DSL diff

```bash
--- 
+++ 
@@ -1,3 +1,21 @@
 def dsl5(I):
-    O = I
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    clean = cover(cover(I, s2), s5)
+    v = gravitate(s2, s5)
+    s2p = shift(s2, double(v))
+    w = width(s2p)
+    h = height(s2p)
+    mr = shift(hmirror(s2p), tojvec(w))
+    ml = shift(hmirror(s2p), invert(tojvec(w)))
+    md = shift(vmirror(s2p), toivec(h))
+    mu = shift(vmirror(s2p), invert(toivec(h)))
+    cset = initset(mr)
+    cset = insert(ml, cset)
+    cset = insert(md, cset)
+    cset = insert(mu, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    obj2 = recolor(TWO, s2p)
+    obj5 = recolor(FIVE, best)
+    O = paint(paint(clean, obj2), obj5)
     return O
```

### Iteration 2 DSL diff

```bash
--- 
+++ 
@@ -1,26 +1,28 @@
 def dsl2(I):
     dims = shape(I)
     bg = canvas(SEVEN, dims)
-    s2 = ofcolor(I, TWO)
-    s5 = ofcolor(I, FIVE)
+    objs = objects(I, T, F, T)
+    o2s = colorfilter(objs, TWO)
+    o5s = colorfilter(objs, FIVE)
+    o2 = first(o2s)
+    o5 = first(o5s)
+    s2 = toindices(o2)
+    s5 = toindices(o5)
     v = gravitate(s2, s5)
-    dv = double(v)
-    s2p = shift(s2, dv)
+    s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    right = shift(hmirror(s2p), tojvec(w))
-    left = shift(hmirror(s2p), invert(tojvec(w)))
-    down = shift(vmirror(s2p), toivec(h))
-    up = shift(vmirror(s2p), invert(tojvec(h)))
-    hr = hmatching(s2, s5)
-    hset = initset(right)
-    hset = insert(left, hset)
-    vset = initset(down)
-    vset = insert(up, vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
-    best = branch(hr, besth, bestv)
+    mh = hmirror(s2p)
+    mv = vmirror(s2p)
+    candR = shift(mh, tojvec(w))
+    candL = shift(mh, invert(tojvec(w)))
+    candD = shift(mv, toivec(h))
+    candU = shift(mv, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 3 DSL diff

```bash
--- 
+++ 
@@ -1,28 +1,31 @@
 def dsl4(I):
     dims = shape(I)
     bg = canvas(SEVEN, dims)
-    objs = objects(I, T, F, T)
-    o2s = colorfilter(objs, TWO)
-    o5s = colorfilter(objs, FIVE)
-    o2 = first(o2s)
-    o5 = first(o5s)
-    s2 = toindices(o2)
-    s5 = toindices(o5)
-    v = gravitate(s2, s5)
-    s2p = shift(s2, add(v, v))
+    s2 = ofcolor(I, TWO)
+    s5 = ofcolor(I, FIVE)
+    com2 = centerofmass(s2)
+    com5 = centerofmass(s5)
+    dirv = sign(subtract(com5, com2))
+    s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    cand_r = shift(mh, tojvec(w))
-    cand_l = shift(mh, invert(tojvec(w)))
-    cand_d = shift(mv, toivec(h))
-    cand_u = shift(mv, invert(toivec(h)))
-    cset = initset(cand_r)
-    cset = insert(cand_l, cset)
-    cset = insert(cand_d, cset)
-    cset = insert(cand_u, cset)
-    best = argmin(cset, lbind(manhattan, s5))
+    offR = tojvec(w)
+    offL = invert(offR)
+    offD = toivec(h)
+    offU = invert(offD)
+    candR = shift(mh, offR)
+    candL = shift(mh, offL)
+    candD = shift(mv, offD)
+    candU = shift(mv, offU)
+    isR = equality(dirv, RIGHT)
+    isL = equality(dirv, LEFT)
+    isD = equality(dirv, DOWN)
+    hor = either(isR, isL)
+    bestRL = branch(isR, candR, candL)
+    bestUD = branch(isD, candD, candU)
+    best = branch(hor, bestRL, bestUD)
     obj2 = recolor(TWO, s2p)
     obj5 = recolor(FIVE, best)
     O = paint(paint(bg, obj2), obj5)
```

### Iteration 4 DSL diff

```bash
--- 
+++ 
@@ -3,28 +3,22 @@
     bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    v = gravitate(s2, s5)
-    s2p = shift(s2, double(v))
+    com2 = centerofmass(s2)
+    com5 = centerofmass(s5)
+    dirv = sign(subtract(com5, com2))
+    s2p = shift(s2, double(dirv))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    offR = tojvec(w)
-    offL = invert(offR)
-    offD = toivec(h)
-    offU = invert(offD)
-    candR = shift(mh, offR)
-    candL = shift(mh, offL)
-    candD = shift(mv, offD)
-    candU = shift(mv, offU)
-    isR = equality(v, RIGHT)
-    isL = equality(v, LEFT)
-    isD = equality(v, DOWN)
-    hor = either(isR, isL)
-    bestRL = branch(isR, candR, candL)
-    bestUD = branch(isD, candD, candU)
-    best = branch(hor, bestRL, bestUD)
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    candR = shift(mh, tojvec(w))
+    candL = shift(mh, invert(tojvec(w)))
+    candD = shift(mv, toivec(h))
+    candU = shift(mv, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 5 DSL diff

```bash
--- 
+++ 
@@ -7,22 +7,15 @@
     s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
-    mh = hmirror(s2p)
-    mv = vmirror(s2p)
-    right = shift(mh, tojvec(w))
-    left = shift(mh, invert(tojvec(w)))
-    down = shift(mv, toivec(h))
-    up = shift(mv, invert(toivec(h)))
-    hr = hmatching(s2, s5)
-    hset = initset(right)
-    hset = insert(left, hset)
-    vset = initset(down)
-    vset = insert(up, vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
-    best = branch(hr, besth, bestv)
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(bg, obj2), obj5)
+    rot = vmirror(hmirror(s2p))
+    candR = shift(rot, tojvec(w))
+    candL = shift(rot, invert(tojvec(w)))
+    candD = shift(rot, toivec(h))
+    candU = shift(rot, invert(toivec(h)))
+    cset = initset(candR)
+    cset = insert(candL, cset)
+    cset = insert(candD, cset)
+    cset = insert(candU, cset)
+    best = argmin(cset, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 6 DSL diff

```bash
--- 
+++ 
@@ -1,23 +1,22 @@
 def dsl5(I):
+    dims = shape(I)
+    bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    clean = cover(cover(I, s2), s5)
     v = gravitate(s2, s5)
     s2p = shift(s2, double(v))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    candR = shift(mh, tojvec(w))
-    candL = shift(mh, invert(tojvec(w)))
-    candD = shift(mv, toivec(h))
-    candU = shift(mv, invert(toivec(h)))
-    cset = initset(candR)
-    cset = insert(candL, cset)
-    cset = insert(candD, cset)
-    cset = insert(candU, cset)
-    best = argmin(cset, lbind(manhattan, s5))
-    obj2 = recolor(TWO, s2p)
-    obj5 = recolor(FIVE, best)
-    O = paint(paint(clean, obj2), obj5)
+    cand = initset(shift(s2p, tojvec(w)))
+    cand = insert(shift(s2p, invert(tojvec(w))), cand)
+    cand = insert(shift(s2p, toivec(h)), cand)
+    cand = insert(shift(s2p, invert(toivec(h))), cand)
+    cand = insert(shift(mh, tojvec(w)), cand)
+    cand = insert(shift(mh, invert(tojvec(w))), cand)
+    cand = insert(shift(mv, toivec(h)), cand)
+    cand = insert(shift(mv, invert(toivec(h))), cand)
+    best = argmin(cand, lbind(manhattan, s5))
+    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 7 DSL diff

```bash
--- 
+++ 
@@ -6,21 +6,36 @@
     o5 = first(colorfilter(objs, FIVE))
     s2 = toindices(o2)
     s5 = toindices(o5)
-    rel = position(s2, s5)
-    dirv = sign(rel)
-    s2p = shift(s2, double(dirv))
+    v = gravitate(s2, s5)
+    s2p = shift(s2, multiply(v, TWO))
     w = width(s2p)
     h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
+    l2 = leftmost(s2p)
+    t2 = uppermost(s2p)
+    l5 = leftmost(s5)
+    r5 = rightmost(s5)
+    t5 = uppermost(s5)
+    b5 = lowermost(s5)
+    w1 = decrement(w)
+    h1 = decrement(h)
+    tL = subtract(r5, w1)
+    tT = subtract(b5, h1)
+    dxR = subtract(tL, l2)
+    dxL = subtract(l5, l2)
+    dyB = subtract(tT, t2)
+    dyT = subtract(t5, t2)
+    cH1 = shift(mh, tojvec(dxR))
+    cH2 = shift(mh, tojvec(dxL))
+    cV1 = shift(mv, toivec(dyB))
+    cV2 = shift(mv, toivec(dyT))
+    chooser = lbind(manhattan, s5)
+    besth = argmin(initset(cH1), chooser)
+    besth = branch(greater(chooser(cH2), chooser(besth)), besth, cH2)
+    bestv = argmin(initset(cV1), chooser)
+    bestv = branch(greater(chooser(cV2), chooser(bestv)), bestv, cV2)
     hr = hmatching(s2, s5)
-    hset = initset(shift(mh, tojvec(w)))
-    hset = insert(shift(mh, invert(tojvec(w))), hset)
-    vset = initset(shift(mv, toivec(h)))
-    vset = insert(shift(mv, invert(toivec(h))), vset)
-    chooser = lbind(manhattan, s5)
-    besth = argmin(hset, chooser)
-    bestv = argmin(vset, chooser)
     best = branch(hr, besth, bestv)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 8 DSL diff

```bash
--- 
+++ 
@@ -3,22 +3,13 @@
     bg = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
-    com2 = centerofmass(s2)
-    com5 = centerofmass(s5)
-    dirv = sign(subtract(com5, com2))
-    s2p = shift(s2, double(dirv))
-    w = width(s2p)
-    h = height(s2p)
-    dd = dmirror(s2p)
-    cc = cmirror(s2p)
-    cand1 = shift(dd, tojvec(w))
-    cand2 = shift(dd, invert(tojvec(w)))
-    cand3 = shift(cc, toivec(h))
-    cand4 = shift(cc, invert(toivec(h)))
-    cset = initset(cand1)
-    cset = insert(cand2, cset)
-    cset = insert(cand3, cset)
-    cset = insert(cand4, cset)
-    best = argmin(cset, lbind(manhattan, s5))
+    v = gravitate(s2, s5)
+    s2p = shift(s2, multiply(v, TWO))
+    hr = hmatching(s2, s5)
+    mir = branch(hr, hmirror(s2p), vmirror(s2p))
+    c_mir = center(mir)
+    c_s5 = center(s5)
+    off = subtract(c_s5, c_mir)
+    best = shift(mir, off)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 9 DSL diff

```bash
--- 
+++ 
@@ -5,23 +5,13 @@
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
     s2p = shift(s2, multiply(v, TWO))
-    w = width(s2p)
-    h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    l2 = leftmost(s2p)
-    t2 = uppermost(s2p)
-    r5 = rightmost(s5)
-    b5 = lowermost(s5)
-    w1 = decrement(w)
-    h1 = decrement(h)
-    tL = subtract(r5, w1)
-    tT = subtract(b5, h1)
-    dx = subtract(tL, l2)
-    dy = subtract(tT, t2)
-    candH = shift(mh, tojvec(dx))
-    candV = shift(mv, toivec(dy))
-    hr = hmatching(s2, s5)
-    best = branch(hr, candH, candV)
+    c5 = centerofmass(s5)
+    ch = centerofmass(mh)
+    cv = centerofmass(mv)
+    posh = shift(mh, subtract(c5, ch))
+    posv = shift(mv, subtract(c5, cv))
+    best = branch(adjacent(posh, s5), posh, posv)
     O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
     return O
```

### Iteration 10 DSL diff

```bash
--- 
+++ 
@@ -1,36 +1,19 @@
 def dsl3(I):
     dims = shape(I)
-    bg = canvas(SEVEN, dims)
+    base = canvas(SEVEN, dims)
     s2 = ofcolor(I, TWO)
     s5 = ofcolor(I, FIVE)
     v = gravitate(s2, s5)
     s2p = shift(s2, multiply(v, TWO))
-    w = width(s2p)
-    h = height(s2p)
     mh = hmirror(s2p)
     mv = vmirror(s2p)
-    l2 = leftmost(s2p)
-    t2 = uppermost(s2p)
-    l5 = leftmost(s5)
-    r5 = rightmost(s5)
-    t5 = uppermost(s5)
-    b5 = lowermost(s5)
-    w1 = decrement(w)
-    h1 = decrement(h)
-    tL = subtract(r5, w1)
-    tT = subtract(b5, h1)
-    dxR = subtract(tL, l2)
-    dxL = subtract(l5, l2)
-    dyB = subtract(tT, t2)
-    dyT = subtract(t5, t2)
-    c1 = shift(mh, tojvec(dxR))
-    c2 = shift(mh, tojvec(dxL))
-    c3 = shift(mv, toivec(dyB))
-    c4 = shift(mv, toivec(dyT))
-    cset = initset(c1)
-    cset = insert(c2, cset)
-    cset = insert(c3, cset)
-    cset = insert(c4, cset)
-    best = argmin(cset, lbind(manhattan, s5))
-    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
+    c5 = centerofmass(s5)
+    ch = centerofmass(mh)
+    cv = centerofmass(mv)
+    ph = shift(mh, subtract(c5, ch))
+    pv = shift(mv, subtract(c5, cv))
+    chooser = lbind(manhattan, s5)
+    best = branch(greater(chooser(ph), chooser(pv)), pv, ph)
+    layer2 = paint(base, recolor(TWO, s2p))
+    O = underpaint(layer2, recolor(FIVE, best))
     return O
```

