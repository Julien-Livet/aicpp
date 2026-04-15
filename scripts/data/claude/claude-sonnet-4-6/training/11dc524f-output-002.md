Looking at the training examples carefully:

- **Train1**: obj2 is LEFT of obj5 → gravitates RIGHT → obj5 takes **vmirror** shape of obj2 and gravitates back
- **Train2**: obj2 is ABOVE obj5 → gravitates DOWN → obj5 takes **hmirror** shape of obj2 and gravitates back  
- **Train3**: obj2 is BELOW obj5 → gravitates UP → obj5 takes **hmirror** shape of obj2 and gravitates back

The key insight: if the gravitation direction is vertical (first component nonzero), use `hmirror`; if horizontal, use `vmirror`. The `branch` primitive handles this without control flow.

```python
def dsl1(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    norm2 = normalize(obj2)
    mirrored = branch(equality(ZERO, first(dir2)), recolor(FIVE, vmirror(norm2)), recolor(FIVE, hmirror(norm2)))
    placed5 = shift(mirrored, gravitate(mirrored, moved2))
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
    is_horizontal = equality(ZERO, first(dir2))
    new5 = recolor(FIVE, branch(is_horizontal, vmirror(norm2), hmirror(norm2)))
    placed5 = shift(new5, gravitate(new5, moved2))
    O = paint(paint(cover(cover(I, obj5), obj2), moved2), placed5)
    return O

def dsl3(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    norm2 = normalize(obj2)
    vertical = flip(equality(ZERO, first(dir2)))
    new5_indices = branch(vertical, hmirror(norm2), vmirror(norm2))
    new5 = recolor(FIVE, new5_indices)
    placed5 = shift(new5, gravitate(new5, moved2))
    cleared = cover(cover(I, obj2), obj5)
    O = paint(paint(cleared, placed5), moved2)
    return O

def dsl4(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    norm2 = normalize(obj2)
    is_vert = flip(equality(ZERO, first(dir2)))
    mirrored_shape = branch(is_vert, hmirror(norm2), vmirror(norm2))
    new5 = shift(recolor(FIVE, mirrored_shape), gravitate(recolor(FIVE, mirrored_shape), moved2))
    O = paint(paint(cover(cover(I, obj2), obj5), moved2), new5)
    return O

def dsl5(I):
    objs = objects(I, True, False, True)
    obj2 = extract(objs, matcher(color, TWO))
    obj5 = extract(objs, matcher(color, FIVE))
    dir2 = gravitate(obj2, obj5)
    moved2 = shift(obj2, dir2)
    norm2 = normalize(obj2)
    use_hmirror = positive(sign(first(dir2)))
    shape5 = branch(use_hmirror, hmirror(norm2), vmirror(norm2))
    new5 = recolor(FIVE, shape5)
    placed5 = shift(new5, gravitate(new5, moved2))
    cleared = cover(cover(I, obj2), obj5)
    O = paint(paint(cleared, moved2), placed5)
    return O
```