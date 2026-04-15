Looking at the training examples carefully:

- **Train1**: 2-object moves right toward 5 (gravitate), 5 stays but 5 gets hmirror shape of 2
- **Train2**: 2 moves down 2 steps (gravitate), 5 takes hmirror shape of 2 and repositions adjacent
- **Train3**: 2 moves up (gravitate), 5 takes hmirror of 2 shape placed adjacent

The key insight: **2-object gravitates toward 5, and 5-object is replaced by hmirror of 2's normalized shape (recolored 5), placed adjacent to the moved 2**.

```python
def dsl1(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    new5 = recolor(FIVE, hmirror(normalize(obj2)))
    placed5 = shift(new5, gravitate(new5, moved2))
    cleared = cover(cover(I, obj2), obj5)
    O = paint(paint(cleared, moved2), placed5)
    return O

def dsl2(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    norm2 = normalize(obj2)
    new5 = shift(recolor(FIVE, vmirror(norm2)), gravitate(recolor(FIVE, vmirror(norm2)), moved2))
    cleared = cover(cover(I, obj2), obj5)
    O = paint(paint(cleared, moved2), new5)
    return O

def dsl3(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    new5_shape = recolor(FIVE, hmirror(normalize(obj2)))
    dir5 = gravitate(new5_shape, moved2)
    placed5 = shift(new5_shape, dir5)
    cleared = cover(cover(I, obj5), obj2)
    O = paint(paint(cleared, placed5), moved2)
    return O

def dsl4(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    new5 = recolor(FIVE, rot180(normalize(obj2)))
    placed5 = shift(new5, gravitate(new5, moved2))
    cleared = cover(cover(I, obj2), obj5)
    O = paint(paint(cleared, moved2), placed5)
    return O

def dsl5(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    mirrored2 = recolor(FIVE, cmirror(normalize(obj2)))
    placed5 = shift(mirrored2, gravitate(mirrored2, moved2))
    cleared = cover(cover(I, obj2), obj5)
    O = paint(paint(cleared, moved2), placed5)
    return O
```