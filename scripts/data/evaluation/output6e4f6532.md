```python
def dsl1(I):
    h = height(I)
    w = width(I)
    top2 = crop(I, (0, 0), (2, w))
    bottom2 = crop(I, (h - 2, 0), (2, w))
    left2_mid = crop(I, (2, 0), (h - 4, 2))
    right2_mid = crop(I, (2, w - 2), (h - 4, 2))
    center = crop(I, (2, 2), (h - 4, w - 4))
    center_v = vmirror(center)
    middle = hconcat(hconcat(left2_mid, center_v), right2_mid)
    O = vconcat(vconcat(top2, middle), bottom2)
    return O

def dsl2(I):
    h = height(I)
    w = width(I)
    top2 = crop(I, (0, 0), (2, w))
    bottom2 = crop(I, (h - 2, 0), (2, w))
    left2_mid = crop(I, (2, 0), (h - 4, 2))
    right2_mid = crop(I, (2, w - 2), (h - 4, 2))
    center = crop(I, (2, 2), (h - 4, w - 4))
    center_h = hmirror(center)
    middle = hconcat(hconcat(left2_mid, center_h), right2_mid)
    O = vconcat(vconcat(top2, middle), bottom2)
    return O

def dsl3(I):
    h = height(I)
    w = width(I)
    left2 = crop(I, (0, 0), (h, 2))
    right2 = crop(I, (0, w - 2), (h, 2))
    midcols = crop(I, (0, 2), (h, w - 4))
    midcols_v = vmirror(midcols)
    O = hconcat(hconcat(left2, midcols_v), right2)
    return O

def dsl4(I):
    h = height(I)
    w = width(I)
    left2 = crop(I, (0, 0), (h, 2))
    right2 = crop(I, (0, w - 2), (h, 2))
    midcols = crop(I, (0, 2), (h, w - 4))
    midcols_h = hmirror(midcols)
    O = hconcat(hconcat(left2, midcols_h), right2)
    return O

def dsl5(I):
    h = height(I)
    w = width(I)
    left2 = crop(I, (0, 0), (h, 2))
    right2 = crop(I, (0, w - 2), (h, 2))
    mid = crop(I, (0, 2), (h, w - 4))
    mw = width(mid)
    left_half = crop(mid, (0, 0), (h, mw // 2))
    right_half = crop(mid, (0, mw // 2), (h, mw - mw // 2))
    mid_swapped = hconcat(right_half, left_half)
    O = hconcat(hconcat(left2, mid_swapped), right2)
    return O
```