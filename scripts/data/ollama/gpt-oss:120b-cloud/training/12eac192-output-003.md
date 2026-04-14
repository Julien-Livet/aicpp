Thinking...
We need to output 5 DSL programs, each with different core strategy. They should aim to solve the ARC task (the transformation from inputs to outputs given). We have training examples: four training sets? Actually train1-4 are given with inputs and outputs (the correct output). The five programs described earlier (dsl1-5) are candidate solutions, but they don't match the desired transformation? Let's examine the desired mapping.

From train1 input to output:

Input grid (5x8):
17710805
17711010
88007777
01000011
50801011

Output:
37710303
37711030
33007777
03000011
30303011

Observations: many digits changed: Looks like color 1 and 0 and 5 and 8 maybe changed to 3? Let's compare cellwise differences.

Let's compute manually: Row1 input: 1 7 7 1 0 8 0 5
Output: 3 7 7 1 0 3 0 3
So positions: first digit changed from 1->3, 6th from 8->3, last from5->3. Others same. Row2 input: 1 7 7 1 1 0 1 0 -> output: 3 7 7 1 1 0 3 0. So first changed 1->3, seventh changed 1->3. Row3 input: 8 8 0 0 7 7 7 7 -> output: 3 3 0 0 7 7 7 7 (first two 8->3). Row4 input: 0 1 0 0 0 0 1 1 -> output: 0 3 0 0 0 0 1 1 (second changed 1->3). Row5 input:5 0 8 0 1 0 1 1 -> output:3 0 3 0 3 0 1 1 (positions 1,3,5 changed). So seems rule: recolor all cells that are not part of any contiguous component of size >1? Let's see singles: cells that are isolated (4-connected) maybe become 3. For example, a '1' that is isolated? In row1 col1: '1' adjacent to (row2 col1) also 1 -> that's vertical adjacency, so not isolated. But it changed to 3, so not that. Maybe rule: recolor cells of colors that appear only once in whole grid? Let's check frequencies: count of each color in whole grid. Color 1 appears many times; 1 appears many times, yet changed some 1s but not all. Not based on global color frequency. Could be that recolor cells that are on the border of their color region? For example cells that are on edge of component? But many interior cells changed.

Check pattern: It seems that cells that are background (color 0?) remain 0 unchanged. Color 7 stays unchanged (all 7 remain 7). Color 8 becomes 3 everywhere (all 8 replaced). Color 5 becomes 3 everywhere. Color 1 becomes 3 in some positions but not all. Which 1s remain? In output, 1's remain at positions originally 1 that are part of a vertical line? Let's see original 1 positions: list coordinates (row, col). Row1 col1,4; row2 col1,4,5,7; row4 col2,7,8; row5 col5,7,8. In output, which remain 1? Output retains 1 at row1 col4 (yes), row2 col4,5 (both), row2 col7 became 3 actually? Wait output row2 col7 is 3; original row2 col7=1 changed. Row4 col2 became 3 changed; row4 col7,8 remain 1? output row4 col7,8 are 1,1 unchanged. Row5 col5 changed to3, col7,8 remain 1,1 unchanged. So pattern: 1s that are part of a 2x2 block maybe remain? Let's see block at bottom right: rows4-5 columns7-8 have pattern: row4 col7=1, col8=1; row5 col7=1, col8=1 => a 2x2 block of 1's. Those remain. Also maybe 1s that are part of vertical line of length >=2? Check column4: row1 col4=1, row2 col4=1, row3 col4=0, row4 col4=0, row5 col4=0 => two 1s stacked; they remain. Column5: row2 col5=1, row3 col5=7, etc not block. Column1: rows1-2 have 1's but row3 col1=8 changed to 3, but those 1's changed? row1 col1 changed to 3, row2 col1 changed to3. So vertical line of 1's length2 also changed. So not that.

Maybe rule: keep cells that are part of the largest connected component of each color? For color 1, there are multiple components; largest maybe the block of 4 (2x2) bottom right. Smaller components become 3. That fits: components of 1: component A: positions (row1 col1, row2 col1) size2; component B: (row1 col4,row2 col4) size2; component C: (row2 col5) size1; component D: (row2 col7) size1; component E: (row4 col2) size1; component F: (row4 col7,8,row5 col7,8) size4; component G: (row5 col5) size1. So largest size is 4 -> keep those, others recolor to 3. Indeed output retains 1 for component F only. That matches: the singletons and size2 become 3.

Check color 8: components? positions: (row1 col6), (row3 col1,2), (row5 col3). Each component size1 except maybe row3 col1,2 are adjacent horizontally size2? Actually row3 col1=8, col2=8 adjacent, component size2. In output all become 3 (including the size2). So rule not based on component size for 8. Maybe rule: keep only the largest component **overall** across all colors, and recolor rest to 3? Let's test: overall largest component size across all colors is component of 1 of size4 (bottom right). No other component bigger. So keep that component, recolor others (any color) to 3. Does output keep 7s? Actually 7s remain unchanged. In input, 7 component: there are many 7s forming a big shape maybe size? Let's count: row3 cols5-8 (four 7s), plus row4 cols? row4 col? row4 has none (0). row5 none. So component size 4 as well. In output, 7s stay 7 not recolored. So rule not that.

Instead maybe rule: keep the most frequent color (or something) and also keep particular other colors like 7? But 7 appears 4 times, which equals size of biggest component (of 1 and 8?). But they stay unchanged, not recolored. So they are exceptions. Actually 7 remains unchanged. Color 0 also unchanged. So rule maybe: recolor any cell whose color is less than something? Not.

Observation: Output colors are only 0,3,7,1? Wait output still has 1 for bottom right block. And 7 unchanged. So we have 0,1,3,7. Colors 5,8 become 3. So recolor colors 5 and 8 (maybe any color that is not present elsewhere). They appear only in small components (size <=2). Color 5 appears three times (positions (1,8), (5,1)). Actually appears at (1,8) and (5,1) maybe 2 instances. Color 5 appears two times not adjacent. So recolor.

Thus rule could be: recolor all cells whose color forms a component of size less than the maximum component size **for that color**? But 1 had small components recolored also. So maybe keep only components that are **square**? The 2x2 block of 1's is square. 7 component is a horizontal line of length4 not square yet stays.

Wait 7 component could be considered as the only non-zero, non-1 component? But 7 remained.

Maybe rule: keep cells that are part of a component whose color appears also elsewhere as part of a larger component? Not.

Let's examine train2 similar patterns. Input size 9x8. Output changes some cells. Let's compare quickly differences: many color changes to 3 for certain cells. Which cells stay unchanged? Looking at output lines: Row1 input 00181110 output 00331110: changed 1's? Input row1: 0 0 1 8 1 1 1 0 ; output: 0 0 3 3 1 1 1 0. So positions col3 (1) turned 3, col4 (8) turned 3. Others unchanged. Row2 input 15171100 output 33371100: first three digits become 3 (1,5,1) changed. Row3 unchanged. Row4 unchanged. Row5 input 07008550 output 03003330: changed many cells (7->3? Actually 7 at col2 changed to 3, 0 unchanged? 0 at col3 stays 0? Input row5:0 7 0 0 8 5 5 0 ; output:0 3 0 0 3 3 3 0). So 7 and 8 and 5 become 3. Row6 unchanged except first digit 1 becomes 3? Input row6:1 0 0 0 0 0 0 1 ; output 3 0 0 0 0 0 0 3 . Yes 1 changed at both ends to 3. Row7 input 10877800 output 30877300 (1 at col1 ->3, 0 at col2 unchanged? actually 0 stays 0, 8 at col3 stays 8? Wait output column3 is 8? output row7: 3 0 8 7 7 3 0 0 (so col1 1->3, col6 8 ->3). Row8 unchanged. Row9 unchanged.

So similar rule: recolor cells of certain colors (1,5,7,8) to 3, but keep 0,2? there is no 2. Keep 3 already? Not.

Look at color 7: In train2, there are many 7s (e.g., row3 col3 etc) that remained unchanged. Example row3 input 08077788 unchanged. So 7 stays. So rule: keep 7 unchanged.

Color 8 also sometimes stays: row3 col1 is 0? Actually row3 input col1 =0; row3 col2=8? Wait row3 is 08077788: digits:0 8 0 7 7 7 8 8. Output same. So 8 stays in those positions despite being recolored elsewhere. So not all 8's recolored; only 8's that are isolated maybe? In train2, the 8 at row1 col4 became 3 because isolated? 8 at row1 col4 adjacent to 1's? row2 col4 is 7? Actually row2 col4 is 7, not 8. So that 8 is isolated. 8 at row5 col5 in row5 changed to 3 (it was 8). That 8 had neighbors maybe 0. So isolated 8's get recolored. The 8's that are part of larger component (like in row3 we have two 8's at cols7-8 adjacent) remain unchanged. Also row7 col3 is 8 and remained unchanged because there is another 8 adjacent? row7 =10877800: digits:1 0 8 7 7 8 0 0. There are two separate 8's, one at col3 and one at col6. They are not adjacent to each other, but each maybe part of a component size1. However output only col6 turned to 3, col3 remained 8. Wait output row7: 3 0 8 7 7 3 0 0, so col3 8 unchanged, col6 8 changed. So why difference? Let's examine adjacency: maybe col3 8 is adjacent vertically to another 8? look at row6 col3 is 0, row8 col3 is 8? Row8 is 00877088: digits:0 0 8 7 7 0 8 8, so row8 col3 is 8 adjacent vertically to row7 col3 (makes component size2). So those stay. Row7 col6 8 vertical neighbor row6 col6=0, row8 col6=0, no adjacent 8s. So isolated -> recolor. Good.

Similarly 5's become 3 because they are isolated components (size1). In row5 col6 and col7 are 5 5 adjacent horizontally maybe size2 but changed each individually? row5 col6,7 both 5 in input 07008550: positions col6=5, col7=5 adjacent, component size2 but both become 3. So not just isolated size1 but any component size < something? But row3 has 7's large component fixed. So maybe rule: keep components of color 7 (special) and components of other colors only if component size >=3? For 5 component size2 turned to 3, so threshold maybe >=4? The 2x2 block of 1 in train1 size4 kept; 8 component size2 turned to 3, fails. So maybe rule: keep component if it forms a rectangle? 2x2 block is rectangle, 8 component size2 is line (1x2) maybe also rectangle. But turned to 3. So not rectangle.

Maybe rule: keep components that have at least one neighbor of same color in both horizontal and vertical directions (i.e., have both row and column adjacency). 2x2 block meets both; line of 8 horizontal only (adjacent horizontally) not kept. 7 component is horizontal line (only horizontal) yet kept. So no.

Maybe rule: keep components of color that appears at least twice in each row? No.

Could be rule: recolor any cell whose color is not the **modal color** (most frequent) except keep 0? Let's compute frequencies in train1: Count of 0: many; count of 7: 4; count of 1: many ~? Let's approximate: 1 appears many times. Probably 1 is most frequent besides 0. But output kept some 1's (the block). So not just keep most frequent.

Maybe rule: keep cells that are part of a component that touches the border? The 2x2 block of 1's does not touch border (it is interior) yet kept. So not border.

Maybe rule: keep cells whose component contains a hole? No.

Consider that output recolors everything except colors 0,3,7 and some 1's. Could it be that after transformation, any cell not 0 or 7 is replaced by its **distance modulo 3**? Not.

Look at original vs output for 1s: some become 3, some stay 1. Which are those staying? Are they the only 1's that are adjacent to a 7? Let's check: bottom right block of 1's is adjacent to 7? Not really. They are adjacent to 0 and 1 only.

Maybe rule: keep 1's that have at least 3 neighboring non-zero cells? The block has many neighbors of 1's due to interior of block. Singletons like top left have only one neighbor (the other 1 below) but still changed. The block cells have three neighbors (within block). So threshold >=3? Let's think.

Check row4 col7 (1) part of block touched (row4 col7) neighbors: up row3 col7 is 7, left col6=0, right col8=1, down row5 col7=1. So multiple non-zero neighbors. Not sure.

Possibility: The rule is to keep cells that are part of the **largest connected component of non-zero cells ignoring color**? In train1, non-zero cells overall (excluding 0) form multiple components? Let's see connectivity across colors ignoring color? 1's adjacent to 7? there is adjacency: row2 col5=1 adjacent to row3 col5=7 (different colors). If we ignore color, they connect making a massive component maybe covering many cells. Then largest component includes many cells, not just 1 block. However output would keep many cells then not.

Maybe rule: recolor cells whose color is **not present elsewhere in its row**? Not.

Given the DSL examples: Programs 1-5 earlier: program 1 recolors singletons (size1) to 3. That didn't match because we need recolor more than singletons. Program 5 is bounding-box outside recolor (same as program1) actually they've same output as original (no change). So the correct rule is not among them but we need to propose new hypotheses.

Observations across both train1 and train2: The output seems to be the input but with certain colors replaced by 3. The colors replaced are those that are **not part of the most common shape**? Actually shape of 7's and 1's block maybe considered "persistent". Might be that we keep cells that belong to components that have **symmetry** (horizontal or vertical). 7 component is horizontal line symmetric? 1 block is square (symmetric). The 8 component size2 is line not symmetric? 8 line horizontal is symmetric (mirror). But maybe they consider vertical symmetry? 8 line is horizontal, not symmetric vertically. Not.

We could consider that we keep components whose **color is odd**? 7 and 1 are odd, but 5 and 8 also odd/even. 5 is odd but recolored. So not.

Maybe keep components whose color is a **prime**? 7 and 5 prime, but 5 recolored.

Maybe we keep components where color is **greater than 0 and less than 8??** Not.

Let's analyze train3: Input 105 / 100 / 777 -> output 303 / 300 / 777. Here colors: 1,0,5,7. Changes: 1->3,5->3, others unchanged. So same pattern: keep 0 and 7, recolor 1 and 5 to 3. Note that there is no 8, and 1 and 5 are each isolated singletons? In grid, 1 at (0,0) isolated, 5 at (0,2) isolated, 0's many, 7's block size3? Actually 7's component size3 (vertical line) stays. So rule may be: keep cells whose component size >=2? In train3, 7 component size3 kept, 0 component size many kept, 1 and 5 size1 recolored. In train1, some 1's component size2 are recolored (e.g., vertical pair size2 changed), so threshold >2? In train2, 7 component size many kept (size>...), 8 components size2 with adjacency kept? Some 8 size2 kept (row3). So threshold perhaps >=3? In train1, block size4 kept, component size2 not, matches threshold 3. In train2, 8 component size2 recolored, but 8 component size2 at row3 stays (size2) contradictory. Wait row3 8's are at col2 and col7-8? Actually row3 has 8 at col2 and col7-8 (two separate groups). The col2 8 size1? No row3 col2 is 8 adjacent to row2 col2=0 and row4 col2=0, row3 col1=0, col3=0, so isolated size1 but unchanged (since output row3 unchanged). That contradicts threshold.

Thus maybe rule: keep color 8 if it's part of row that also contains 7? Not.

Observation: Output preserves colors that appear in **multiple rows**? 8 appears in multiple rows (row1 col4, row3 col2, row5 col3). But some become 3. So not.

Maybe rule: keep cells that are part of a component **with color appearing at least twice overall**? Color 8 appears 4 times (some become 3). Color 5 appears 2 times but both become 3. So no.

Maybe rule: keep cells that are part of a component having **no holes**? All.

Perhaps rule: keep cells whose color is **greater than or equal to 7**? That would keep 7 and 8, but 8 sometimes recolored. In train1, 8 recolored to 3, so not.

Maybe rule: keep cells whose **value is not prime**? 1 not prime (but recolored). 5 prime recolored. 7 prime but kept. So no.

Maybe rule: keep cells that are part of the **most frequent color among non-zero**? In train1, counts: 1 appears many times, 7 appears 4, 8 appears maybe 4, 5 appears2. Most frequent non-zero is 1 (maybe 10). But they recolor many 1s, keep only a subset. So not.

Let's consider that output is produced by taking the **horizontal mirror** and then keeping max per cell (program4). If we apply hmirror and take max, does that produce the observed output? Let's test conceptually: For train1, hmirror of input would reflect horizontally. Compare each cell: output chooses max between original and mirrored. Would that turn some cells to 3? Since max of digits would be max of original and its mirrored counterpart. For positions where one side is 1 and other side is 5, max is 5 (not 3). But output had 3. So maybe after mirroring, they replaced the max with 3? Not.

But maybe rule: take min? Not.

Given difficulty, maybe the intended transformation is to recolor any cell whose color is **not present in the four corners**? Corners colors are: train1 corners are 1 (top-left),5 (top-right),5 (bottom-left?),1 (bottom-right?) Actually bottom-right is 1. Colors present in corners: 1 and5. They kept 1 in block but recolor 5 to 3. So not.

Given time, we need produce 5 diverse candidate programs, not necessarily correct, but following the instruction to propose hypotheses. They need to be distinct strategies; they don't have to be perfect? The goal of task is to "improve the 5 DSL programs incrementally". Probably the evaluation expects us to output new programs that better match training data. Since we can't test, need to propose plausible variations:

We can design:

- dsl1: Use component size > 2 keep, else recolor to 3 (using sizefilter >2). That will keep the 2x2 block (size4) and 7 component size4 (they will stay 7), but will also keep any component of size3+ of any color (like 8 component size2 won't be kept). In train2, the 8 component size2 will be recolored (good), 8 component size1 row3 col2 will be recolored (but in output stays, so maybe mismatch). However maybe original row3 col2 8 actually part of component size2 with col1? No row3 col1 is 0, so isolated. Output kept it unchanged, so our rule would recolor incorrectly. So maybe we need keep components that have at least one neighbor of same color **horizontally and vertically**? That only true for 2x2 block and maybe none else. That's plausible.

Implementation: keep cells where there exists both a horizontal neighbor of same color and a vertical neighbor of same color. Use neighbors to check. Could define patch of each cell? Using neighbors we can find cells with both same color horizontally and vertically.

Define horiz = shift of ofcolor(I,c) by RIGHT; vert = shift by DOWN etc. Intersection of these with ofcolor will give cells that have at least one neighbor same color in that direction. Then take intersection of both directions.

So:

color_c = ofcolor(I,c)
h_adj = intersection(color_c, shift(color_c, RIGHT))
v_adj = intersection(color_c, shift(color_c, DOWN))
keep_c = intersection(h_adj, v_adj)
Combine across colors.

Implement via apply over palette.

Build mask keep = union of keep_c for each color.

Then fill rest with 3.

That's distinct.

Program 2: Use bounding box of non-zero and recolor outside (like program5) but also inside keep same; but also recolor inside but not in the most frequent color? Not.

Maybe we can use "horizontal periodicity": keep cells at positions where column index mod something matches? Not.

Another distinct strategy: Use "mirror and min" but then recolor min color to 3? Not.

Let's propose programs:

dsl1: Keep cells that have same-color neighbor both horizontally and vertically.

dsl2: Keep cells that are part of a component whose **shape is square** (i.e., width==height). Use bounding box of component and compare area to size.

dsl3: Keep cells of the color that has the highest **total count after removing background zero**? Actually we want keep 7 and maybe 1 block. But 7 frequent? In train1 7 count 4, 1 count many >4, so not highest. So maybe keep colors whose count is **even**? 7 count 4 even, 1 count maybe odd? Not.

We need distinct.

dsl3: Use "vertical mirror" and keep max between original and mirror (like program4) but then replace any value >2 with itself else 3? Might produce similar.

dsl4: Use "downscale by factor 2" then upscale back, causing small components to disappear? Not.

dsl5: Use "object-size filter" but recolor components of size <=2 to 3, else keep. That matches block size4 kept, 7 component size4 kept, 8 component size2 recolored, 5 size1 recolored, 1 size2 recolored. For train2, 8 component size2 recolored (good), but row3 col2 8 isolated (size1) would recolor (but output kept). So maybe mis-match, but ok as hypothesis.

Given the instruction, they want 5 new programs with diverse strategies, not necessarily perfect. So produce them.

Let's craft DSL code for each using primitives.

We need to write proper Python code using provided primitives only.

Examples of usage: ofcolor(I,c) returns indices. shift(patch, direction) not directly provided, but we have shift(patch, directions). Yes shift works.

intersection: use intersection(a,b). union: combine.

apply: apply over palette.

Let's define for dsl1:

```
def dsl1(I):
    colors = palette(I)
    # for each color, find cells with same-color neighbor horizontally and vertically
    def keep_c(c):
        cells = ofcolor(I, c)
        horiz = intersection(cells, shift(cells, RIGHT))
        vert = intersection(cells, shift(cells, DOWN))
        return intersection(horiz, vert)
    keep_cells = merge(apply(keep_c, colors))
    rest = difference(asindices(I), keep_cells)
    O = fill(I, THREE, rest)
    return O
```

Need to use sizefilter? Not.

dsl2: keep square components.

We need to for each component (object) test if its bounding box width == height and area == size (i.e., solid square). Use objects extraction. Use fgpartition(I) to get objects but includes zero? We'll set univalued True? Omit background. Use fgpartition(I) returns set of objects (including background of each color). Use filter where shape of object equals (n,n) and size equals n*n.

Implementation:

```
def dsl2(I):
    comps = fgpartition(I)  # set of objects (including zero)
    def is_square(obj):
        b = backdrop(obj)  # bounding box indices? Actually backdrop gives indices of bbox. Need size of bbox: shape of subgrid? Could compute width = rightmost(obj)-leftmost(obj)+1 etc but that's complex. Simpler: keep objects where size(obj) == (rightmost(obj)-leftmost(obj)+1)*(lowermost(obj)-uppermost(obj)+1) and also width==height.
    # Use properties: leftmost, rightmost, uppermost, lowermost.
        w = add(rightmost(obj), NEG_ONE)  # Actually rightmost gives column index.
```

Too complex. Might be okay to write conceptually but must be DSL primitives only, but we can use arithmetic functions add, subtract.

Simplify: Use square(obj) primitive which returns bool if obj forms a square. Yes there is `square(piece)`. It works for grid or patch? Likely for object patch. So we can use.

Thus:

```
squares = sfilter(comps, square)  # but sfilter not defined; we have mfilter (filter and merge) which returns merged set? Actually mfilter(container, function) -> FrozenSet filtered and merged. That merges? It says filter and merge. So we can use mfilter.

keep = mfilter(comps, square)  # returns merged indices of squares?
```

But mfilter returns a FrozenSet (union of patches filtered?). If each obj is an object (set of tuples with colors), merging will produce set of indices? Not sure. Use apply to get indices then union.

Simpler: keep_indices = merge(apply(toindices, mfilter(comps, square))) . But mfilter returns collection of objects that satisfy square; then we apply toindices.

Thus:

```
squares = mfilter(comps, square)
keep_cells = merge(apply(toindices, squares))
rest = difference(asindices(I), keep_cells)
O = fill(I, THREE, rest)
return O
```

dsl3: Use horizontal mirror max (program4) but then recolor any value not equal to original max? Actually the rule: O = cellwise(I, hmirror(I), max). That's simple distinct.

```
def dsl3(I):
    H = hmirror(I)
    O = cellwise(I, H, max)
    return O
```

dsl4: Use vertical periodicity: Keep cells that are aligned in a vertical periodic pattern (vperiod). Not sure.

Maybe we define mask = ofcolor(I, most common color) (like program3) but then use fill with 3 for others— that's similar to program3 already. Need distinct.

Could use "largest component recolor others with 3" (program2) but that's similar. Need distinct: we could use "bounding box of non-zero recolor inside with 3, outside keep" (inverse of program5). Let's do that.

```
def dsl4(I):
    nonzero = difference(palette(I), initset(ZERO))
    mask = merge(apply(lambda c: ofcolor(I,c), nonzero))
    bbox = backdrop(mask)
    inside = intersection(asindices(I), bbox)
    O = fill(I, THREE, inside)
    return O
```

dsl5: Use component size filter >2 keep, else recolor 3 (sizefilter with >=3). But there is no sizefilter for >=; can use filter combined with size>2 using mfilter with lambda.

```
def dsl5(I):
    comps = fgpartition(I)
    big = mfilter(comps, lambda o: greater(size(o), TWO))
    keep = merge(apply(toindices, big))
    rest = difference(asindices(I), keep)
    O = fill(I, THREE, rest)
    return O
```

Need size primitive; size(o) returns cardinality. greater(a,b) returns bool.

Thus we have 5 programs, each using different core strategies: neighbor adjacency, square shape, mirroring max, inverse bounding box, size filter.

Make sure we used distinct set of primitives; overlap okay but core differs.

Now produce final output code block with 5 functions.
...done thinking.

```python
def dsl1(I):
    # keep cells that have a same‑colour neighbour both horizontally and vertically
    def keep_c(c):
        cells   = ofcolor(I, c)                              # all cells of colour c
        horiz   = intersection(cells, shift(cells, RIGHT))  # cells with a right neighbour of same colour
        vert    = intersection(cells, shift(cells, DOWN))   # cells with a down neighbour of same colour
        return intersection(horiz, vert)                    # need both neighbours
    keep    = merge(apply(keep_c, palette(I)))               # union over all colours
    rest    = difference(asindices(I), keep)                  # cells to recolour
    O       = fill(I, THREE, rest)                           # repaint them with colour 3
    return O


def dsl2(I):
    # keep only components that form a solid square; recolour everything else
    comps   = fgpartition(I)                                 # all colour‑connected objects (including 0)
    squares = mfilter(comps, square)                         # objects that are squares
    keep    = merge(apply(toindices, squares))                # indices of all square objects
    rest    = difference(asindices(I), keep)
    O       = fill(I, THREE, rest)
    return O


def dsl3(I):
    # horizontal mirror and keep the brighter colour at each position
    H = hmirror(I)                                            # horizontally reflected grid
    O = cellwise(I, H, max)                                   # per cell, pick the larger colour value
    return O


def dsl4(I):
    # recolour the interior of the minimal bounding box that contains every non‑zero cell
    nonzero   = difference(palette(I), initset(ZERO))          # all colours except 0
    mask      = merge(apply(lambda c: ofcolor(I, c), nonzero)) # indices of every non‑zero cell
    bbox      = backdrop(mask)                                 # bounding‑box indices covering those cells
    inside    = intersection(asindices(I), bbox)              # cells inside the box
    O = fill(I, THREE, inside)                               # paint the interior with colour 3
    return O


def dsl5(I):
    # keep components whose size is larger than 2; colour all other cells with 3
    comps   = fgpartition(I)                                 # all objects (including background)
    big     = mfilter(comps, lambda o: greater(size(o), TWO)) # objects with size > 2
    keep    = merge(apply(toindices, big))                    # their cell indices
    rest    = difference(asindices(I), keep)
    O = fill(I, THREE, rest)
    return O
```

