# Task 28a6681f
train failed, test failed

## Iteration 1

### Program 1

#### Train costs

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |                0 |      3.74166 |                 0.14 |                   0 |      3.88166 |
| train2 |                0 |      3.74166 |                 0.14 |                   0 |      3.88166 |
| train3 |                0 |      2.44949 |                 0.06 |                   0 |      2.50949 |

#### Test costs

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      2.82843 |                 0.08 |                   0 |      2.90843 |

#### DSL

```python
def dsl1(I):
    # Object-based clipping of 1s above the top of the leftmost non-1 object
    h = height(I)
    w = width(I)
    objs = objects(I, True, False, True)
    non1 = difference(objs, colorfilter(objs, ONE))
    anchor = argmin(non1, leftmost)
    cut = uppermost(anchor)
    top = crop(I, (0, 0), (cut, w))
    top_cleared = replace(top, ONE, ZERO)
    bottom = crop(I, (cut, 0), (h - cut, w))
    O = vconcat(top_cleared, bottom)
    return O
```

### Program 2

#### Train costs

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |                0 |      3.31662 |                 0.11 |           0.0707107 |      3.49734 |
| train2 |                0 |      3.74166 |                 0.14 |           0         |      3.88166 |
| train3 |                0 |      3.31662 |                 0.11 |           0         |      3.42662 |

#### Test costs

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |                0 |      3.31662 |                 0.11 |           0.0353553 |      3.46198 |

#### DSL

```python
def dsl2(I):
    # Periodic translation: shift the rightmost object left by its width and underpaint
    objs = objects(I, True, False, True)
    right_obj = argmax(objs, rightmost)
    wobj = width(right_obj)
    shifted = shift(toindices(right_obj), astuple(0, -wobj))
    addobj = recolor(ONE, shifted)
    O = underpaint(I, addobj)
    return O
```

### Program 3

#### Train costs

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |              nan |          nan |                  nan |                 nan |          nan |
| train2 |              nan |          nan |                  nan |                 nan |          nan |
| train3 |              nan |          nan |                  nan |                 nan |          nan |

#### Test costs

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |              nan |          nan |                  nan |                 nan |          nan |

#### DSL

```python
def dsl3(I):
    # Geometric continuation: extend every non-1 object one cell left with 1s on background
    objs = objects(I, True, False, True)
    non1 = difference(objs, colorfilter(objs, ONE))
    idxsets = mapply(toindices, non1)
    shift_left = rbind(shift, LEFT)
    shiftedsets = mapply(shift_left, idxsets)
    union_shifted = merge(shiftedsets)
    addobj = recolor(ONE, union_shifted)
    base = replace(I, ONE, ZERO)
    O = underpaint(base, addobj)
    return O
```

### Program 4

#### Train costs

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |              nan |          nan |                  nan |                 nan |          nan |
| train2 |              nan |          nan |                  nan |                 nan |          nan |
| train3 |              nan |          nan |                  nan |                 nan |          nan |

#### Test costs

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |              nan |          nan |                  nan |                 nan |          nan |

#### DSL

```python
def dsl4(I):
    # Causal propagation: drop all 1s as one object until adjacent to non-1 foreground
    objs = objects(I, True, False, True)
    non1 = difference(objs, colorfilter(objs, ONE))
    non1_idxsets = mapply(toindices, non1)
    dest = merge(non1_idxsets)
    ones_idx = ofcolor(I, ONE)
    off = gravitate(ones_idx, dest)
    moved = shift(ones_idx, off)
    moved_obj = recolor(ONE, moved)
    base = replace(I, ONE, ZERO)
    O = paint(base, moved_obj)
    return O
```

### Program 5

#### Train costs

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |              nan |          nan |                  nan |                 nan |          nan |
| train2 |              nan |          nan |                  nan |                 nan |          nan |
| train3 |              nan |          nan |                  nan |                 nan |          nan |

#### Test costs

|       |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| test1 |              nan |          nan |                  nan |                 nan |          nan |

#### DSL

```python
def dsl5(I):
    # Structural pattern completion: fill each object's bounding-box gaps with 1s (clear old 1s)
    objs = objects(I, True, False, True)
    non1 = difference(objs, colorfilter(objs, ONE))
    gaps = mapply(delta, non1)  # box minus object, per object
    union_gaps = merge(gaps)
    addobj = recolor(ONE, union_gaps)
    base = replace(I, ONE, ZERO)
    O = underpaint(base, addobj)
    return O
```

