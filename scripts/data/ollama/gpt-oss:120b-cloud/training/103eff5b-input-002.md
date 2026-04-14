# Input->output grid pairs of an ARC task

## train1

### Input

```bash
000000000000
000000000000
000000000000
000031000000
000430000000
000204000000
000000000000
000000000000
000000000000
000000000000
088888800000
088888800000
088888800000
000088888800
000088888800
000088888800
088800088800
088800088800
088800088800
000000000000
000000000000
000000000000
```

### Output

```bash
000000000000
000000000000
000000000000
000031000000
000430000000
000204000000
000000000000
000000000000
000000000000
000000000000
022244400000
022244400000
022244400000
000033333300
000033333300
000033333300
044400011100
044400011100
044400011100
000000000000
000000000000
000000000000
```

## train2

### Input

```bash
0000000000000
0000300000000
0020340000000
0021100000000
0020040000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0088888800000
0088888800000
0000880000000
0000880000000
0000888888000
0000888888000
0088008800000
0088008800000
0000000000000
0000000000000
0000000000000
0000000000000
```

### Output

```bash
0000000000000
0000300000000
0020340000000
0021100000000
0020040000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0022222200000
0022222200000
0000110000000
0000110000000
0000113333000
0000113333000
0044004400000
0044004400000
0000000000000
0000000000000
0000000000000
0000000000000
```

# Available types

```python
from typing import (
    List,
    Union,
    Tuple,
    Any,
    Container,
    Callable,
    FrozenSet,
    Iterable
)

Boolean = bool
Integer = int
IntegerTuple = Tuple[Integer, Integer]
Numerical = Union[Integer, IntegerTuple]
IntegerSet = FrozenSet[Integer]
Grid = Tuple[Tuple[Integer]]
Cell = Tuple[Integer, IntegerTuple]
Object = FrozenSet[Cell]
Objects = FrozenSet[Object]
Indices = FrozenSet[IntegerTuple]
IndicesSet = FrozenSet[Indices]
Patch = Union[Object, Indices]
Element = Union[Object, Grid]
Piece = Union[Grid, Patch]
TupleTuple = Tuple[Tuple]
ContainerContainer = Container[Container]
```

# Available variables

```python
I: Tuple[Tuple]
F = False
T = True
ZERO = 0
ONE = 1
TWO = 2
THREE = 3
FOUR = 4
FIVE = 5
SIX = 6
SEVEN = 7
EIGHT = 8
NINE = 9
TEN = 10
NEG_ONE = -1
NEG_TWO = -2
DOWN = (1, 0)
RIGHT = (0, 1)
UP = (-1, 0)
LEFT = (0, -1)
ORIGIN = (0, 0)
UNITY = (1, 1)
NEG_UNITY = (-1, -1)
UP_RIGHT = (-1, 1)
DOWN_LEFT = (1, -1)
ZERO_BY_TWO = (0, 2)
TWO_BY_ZERO = (2, 0)
TWO_BY_TWO = (2, 2)
THREE_BY_THREE = (3, 3)
```

# Available primitives

```python
add(a: Union[int, Tuple[int, int]], b: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # addition
adjacent(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether two patches are adjacent
apply(function: Callable, container: Container) -> Container # apply function to each item in container
argmax(container: Container, compfunc: Callable) -> Any # largest item by custom order
argmin(container: Container, compfunc: Callable) -> Any # smallest item by custom order
asindices(grid: Tuple[Tuple[int]]) -> FrozenSet[Tuple[int, int]] # indices of all grid cells
asobject(grid: Tuple[Tuple[int]]) -> FrozenSet[Tuple[int, Tuple[int, int]]] # conversion of grid to object
astuple(a: int, b: int) -> Tuple[int, int] # constructs a tuple
backdrop(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # indices in bounding box of patch
bordering(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], grid: Tuple[Tuple[int]]) -> bool # whether a patch is adjacent to a grid border
both(a: bool, b: bool) -> bool # logical and
bottomhalf(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # lower half of grid
box(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # outline of patch
branch(condition: bool, a: Any, b: Any) -> Any # if else branching
canvas(value: int, dimensions: Tuple[int, int]) -> Tuple[Tuple[int]] # grid construction
cellwise(a: Tuple[Tuple[int]], b: Tuple[Tuple[int]], fallback: int) -> Tuple[Tuple[int]] # cellwise match of two grids
center(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # center of the patch
centerofmass(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # center of mass
chain(h: Callable, g: Callable, f: Callable) -> Callable # function composition with three functions
cmirror(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # mirroring along counterdiagonal
color(obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> int # color of object
colorcount(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]], value: int) -> int # number of cells with color
colorfilter(objs: FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]], value: int) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # filter objects by color
combine(a: Container, b: Container) -> Container # union
compose(outer: Callable, inner: Callable) -> Callable # function composition
compress(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # removes frontiers from grid
connect(a: Tuple[int, int], b: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # line between two points
contained(value: Any, container: Container) -> bool # element of
corners(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # indices of corners
cover(grid: Tuple[Tuple[int]], patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[Tuple[int]] # remove object from grid
crement(x: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # incrementing positive and decrementing negative
crop(grid: Tuple[Tuple[int]], start: Tuple[int, int], dims: Tuple[int, int]) -> Tuple[Tuple[int]] # subgrid specified by start and dimension
decrement(x: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # decrementing
dedupe(tup: Tuple) -> Tuple # remove duplicates
delta(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # indices in bounding box but not part of patch
difference(a: FrozenSet, b: FrozenSet) -> FrozenSet # set difference
divide(a: Union[int, Tuple[int, int]], b: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # floor division
dmirror(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # mirroring along diagonal
dneighbors(loc: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # directly adjacent indices
double(n: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # scaling by two
downscale(grid: Tuple[Tuple[int]], factor: int) -> Tuple[Tuple[int]] # downscale grid
either(a: bool, b: bool) -> bool # logical or
equality(a: Any, b: Any) -> bool # equality
even(n: int) -> bool # evenness
extract(container: Container, condition: Callable) -> Any # first element of container that satisfies condition
fgpartition(grid: Tuple[Tuple[int]]) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # each cell with the same value part of the same object without background
fill(grid: Tuple[Tuple[int]], value: int, patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[Tuple[int]] # fill value at indices
first(container: Container) -> Any # first item of container
flip(b: bool) -> bool # logical not
fork(outer: Callable, a: Callable, b: Callable) -> Callable # creates a wrapper function
frontiers(grid: Tuple[Tuple[int]]) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # set of frontiers
gravitate(source: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], destination: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # direction to move source until adjacent to destination
greater(a: int, b: int) -> bool # greater
halve(n: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # scaling by one half
hconcat(a: Tuple[Tuple[int]], b: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # concatenate two grids horizontally
height(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # height of grid or patch
hfrontier(location: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # horizontal frontier
hline(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether the piece forms a horizontal line
hmatching(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether there exists a row for which both patches have cells
hmirror(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # mirroring along horizontal
hperiod(obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> int # horizontal periodicity
hsplit(grid: Tuple[Tuple[int]], n: int) -> Tuple # split grid horizontally
hupscale(grid: Tuple[Tuple[int]], factor: int) -> Tuple[Tuple[int]] # upscale grid horizontally
identity(x: Any) -> Any # identity function
inbox(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # inbox for patch
increment(x: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # incrementing
index(grid: Tuple[Tuple[int]], loc: Tuple[int, int]) -> int # color at location
ineighbors(loc: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # diagonally adjacent indices
initset(value: Any) -> FrozenSet # initialize container
insert(value: Any, container: FrozenSet) -> FrozenSet # insert item into container
intersection(a: FrozenSet, b: FrozenSet) -> FrozenSet # returns the intersection of two containers
interval(start: int, stop: int, step: int) -> Tuple # range
invert(n: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # inversion with respect to addition
last(container: Container) -> Any # last item of container
lbind(function: Callable, fixed: Any) -> Callable # fix the leftmost argument
leastcolor(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]]) -> int # least common color
leastcommon(container: Container) -> Any # least common item
lefthalf(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # left half of grid
leftmost(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # column index of leftmost occupied cell
llcorner(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # index of lower left corner
lowermost(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # row index of lowermost occupied cell
lrcorner(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # index of lower right corner
manhattan(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # closest manhattan distance between two patches
mapply(function: Callable, container: Container[Container]) -> FrozenSet # apply and merge
matcher(function: Callable, target: Any) -> Callable # construction of equality function
maximum(container: FrozenSet[int]) -> int # maximum
merge(containers: Container[Container]) -> Container # merging
mfilter(container: Container, function: Callable) -> FrozenSet # filter and merge
minimum(container: FrozenSet[int]) -> int # minimum
mostcolor(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]]) -> int # most common color
mostcommon(container: Container) -> Any # most common item
move(grid: Tuple[Tuple[int]], obj: FrozenSet[Tuple[int, Tuple[int, int]]], offset: Tuple[int, int]) -> Tuple[Tuple[int]] # move object on grid
mpapply(function: Callable, a: Tuple, b: Tuple) -> Tuple # apply function on two vectors and merge
multiply(a: Union[int, Tuple[int, int]], b: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # multiplication
neighbors(loc: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # adjacent indices
normalize(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # moves upper left corner to origin
numcolors(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]]) -> FrozenSet[int] # number of colors occurring in object or grid
objects(grid: Tuple[Tuple[int]], univalued: bool, diagonal: bool, without_bg: bool) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # objects occurring on the grid
occurrences(grid: Tuple[Tuple[int]], obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # locations of occurrences of object in grid
ofcolor(grid: Tuple[Tuple[int]], value: int) -> FrozenSet[Tuple[int, int]] # indices of all grid cells with value
order(container: Container, compfunc: Callable) -> Tuple # order container by custom key
other(container: Container, value: Any) -> Any # other value in the container
outbox(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # outbox for patch
paint(grid: Tuple[Tuple[int]], obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> Tuple[Tuple[int]] # paint object to grid
pair(a: Tuple, b: Tuple) -> Tuple[Tuple] # zipping of two tuples
palette(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]]) -> FrozenSet[int] # colors occurring in object or grid
papply(function: Callable, a: Tuple, b: Tuple) -> Tuple # apply function on two vectors
partition(grid: Tuple[Tuple[int]]) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # each cell with the same value part of the same object
portrait(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether height is greater than width
position(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # relative position between two patches
positive(x: int) -> bool # positive
power(function: Callable, n: int) -> Callable # power of function
prapply(function, a: Container, b: Container) -> FrozenSet # apply function on cartesian product
product(a: Container, b: Container) -> FrozenSet # cartesian product
rapply(functions: Container, value: Any) -> Container # apply each function in container to value
rbind(function: Callable, fixed: Any) -> Callable # fix the rightmost argument
recolor(value: int, patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, Tuple[int, int]]] # recolor patch
remove(value: Any, container: Container) -> Container # remove item from container
repeat(item: Any, num: int) -> Tuple # repetition of item within vector
replace(grid: Tuple[Tuple[int]], replacee: int, replacer: int) -> Tuple[Tuple[int]] # color substitution
righthalf(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # right half of grid
rightmost(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # column index of rightmost occupied cell
rot180(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # half rotation
rot270(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # quarter anticlockwise rotation
rot90(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # quarter clockwise rotation
sfilter(container: Container, condition: Callable) -> Container # keep elements in container that satisfy condition
shape(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # height and width of grid or patch
shift(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], directions: Tuple[int, int]) -> Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # shift patch
shoot(start: Tuple[int, int], direction: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # line from starting point and direction
sign(x: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # sign
size(container: Container) -> int # cardinality
sizefilter(container: Container, n: int) -> FrozenSet # filter items by size
square(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether the piece forms a square
subgrid(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # smallest subgrid containing object
subtract(a: Union[int, Tuple[int, int]], b: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # subtraction
switch(grid: Tuple[Tuple[int]], a: int, b: int) -> Tuple[Tuple[int]] # color switching
toindices(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # indices of object cells
toivec(i: int) -> Tuple[int, int] # vector pointing vertically
tojvec(j: int) -> Tuple[int, int] # vector pointing horizontally
toobject(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], grid: Tuple[Tuple[int]]) -> FrozenSet[Tuple[int, Tuple[int, int]]] # object from patch and grid
tophalf(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # upper half of grid
totuple(container: FrozenSet) -> Tuple # conversion to tuple
trim(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # trim border of grid
ulcorner(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # index of upper left corner
underfill(grid: Tuple[Tuple[int]], value: int, patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[Tuple[int]] # fill value at indices that are background
underpaint(grid: Tuple[Tuple[int]], obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> Tuple[Tuple[int]] # paint object to grid where there is background
uppermost(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # row index of uppermost occupied cell
upscale(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]], factor: int) -> Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]] # upscale object or grid
urcorner(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # index of upper right corner
valmax(container: Container, compfunc: Callable) -> int # maximum by custom function
valmin(container: Container, compfunc: Callable) -> int # minimum by custom function
vconcat(a: Tuple[Tuple[int]], b: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # concatenate two grids vertically
vfrontier(location: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # vertical frontier
vline(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether the piece forms a vertical line
vmatching(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether there exists a column for which both patches have cells
vmirror(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # mirroring along vertical
vperiod(obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> int # vertical periodicity
vsplit(grid: Tuple[Tuple[int]], n: int) -> Tuple # split grid vertically
vupscale(grid: Tuple[Tuple[int]], factor: int) -> Tuple[Tuple[int]] # upscale grid vertically
width(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # width of grid or patch
```

# Program 1
## DSL
```python
def dsl1(I):
    # ---- Global pixel‑averaging -------------------------------------------------
    # 1.  Trim the empty outer border.
    # 2.  Downscale the trimmed picture by a factor of 2 (global compression).
    # 3.  Upscale it back to the original size (nearest‑neighbour expansion).
    # 4.  Paint the up‑scaled picture over the original, but only on cells that
    #     originally contained colour 8 (all other colours stay unchanged).
    trimmed   = trim(I)
    tiny      = downscale(trimmed, 2)
    big       = upscale(tiny, 2)
    region8   = ofcolor(I, 8)
    O         = paint(I, toobject(region8, big))
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |                0 |      35.5387 |             0.204545 |           0.0199522 |      35.7632 |
| train2 |                0 |      33.9411 |             0.115385 |           0         |      34.0565 |

## Output grids

### train1 output

```bash
000000000000
000000000000
000000000000
000031000000
000430000000
000204000000
000000000000
000000000000
000000000000
000000000000
088888000000
088888000000
000088800000
000088888800
000088888800
000088888800
088800088800
088800088800
000000000000
000000000000
000000000000
000000000000
```

### train2 output

```bash
0000000000000
0000300000000
0020340000000
0021100000000
0020040000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0088888800000
0088888800000
0000880000000
0000880000000
0000888888000
0000888888000
0088008800000
0088008800000
0000000000000
0000000000000
0000000000000
0000000000000
```


---

# Program 2
## DSL
```python
def dsl2(I):
    # ---- Template‑extraction / re‑projection ----------------------------------
    # 1.  Extract every non‑zero, non‑8 object (the “template”).
    # 2.  Build a single object that contains all those cells (union).
    # 3.  Compute the bounding box of the 8‑region and of the template.
    # 4.  Scale the template to the size of the 8‑region using separate
    #     vertical and horizontal up‑scales (the factors are obtained by
    #     integer division of the two dimensions).
    # 5.  Paint the scaled template over the original 8‑region.
    template_pts   = {o for o in objects(I, False, True, True) if color(o) != 8}
    template       = combine(template_objs:=template_pts)          # union of the template cells
    box8           = backdrop(ofcolor(I, 8))
    box_template   = backdrop(template)
    vfactor        = divide(height(box8),   height(box_template))
    hfactor        = divide(width(box8),   width(box_template)))   # width = shape(...)[1]
    scaled_vert    = vupscale(toobject(box_template, template), vfactor)
    scaled_horiz   = hupscale(scaled_vert, hfactor)
    cleared        = cover(I, ofcolor(I, 8))                       # erase the 8 block
    O              = paint(cleared, toobject(backdrop(ofcolor(I, 8)), scaled_horiz))
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |              nan |          nan |                  nan |                 nan |          nan |
| train2 |              nan |          nan |                  nan |                 nan |          nan |

## Output grids


## Tracebacks
```bash
    hfactor        = divide(width(box8),   width(box_template)))   # width = shape(...)[1]
def dsl2(I):
    # ---- Template‑extraction / re‑projection ----------------------------------
    # 1.  Extract every non‑zero, non‑8 object (the “template”).
    # 2.  Build a single object that contains all those cells (union).
    # 3.  Compute the bounding box of the 8‑region and of the template.
    # 4.  Scale the template to the size of the 8‑region using separate
    #     vertical and horizontal up‑scales (the factors are obtained by
    #     integer division of the two dimensions).
    # 5.  Paint the scaled template over the original 8‑region.
    template_pts   = {o for o in objects(I, False, True, True) if color(o) != 8}
    template       = combine(template_objs:=template_pts)          # union of the template cells
    box8           = backdrop(ofcolor(I, 8))
    box_template   = backdrop(template)
    vfactor        = divide(height(box8),   height(box_template))
    hfactor        = divide(width(box8),   width(box_template)))   # width = shape(...)[1]
    scaled_vert    = vupscale(toobject(box_template, template), vfactor)
    scaled_horiz   = hupscale(scaled_vert, hfactor)
    cleared        = cover(I, ofcolor(I, 8))                       # erase the 8 block
    O              = paint(cleared, toobject(backdrop(ofcolor(I, 8)), scaled_horiz))
    return O
                                                               ^
SyntaxError: unmatched ')'
```

---

# Program 3
## DSL
```python
def dsl3(I):
    # ---- Quadrant colour‑fill ---------------------------------------------------
    # 1.  Locate the whole 8‑region.
    # 2.  Split the region into four equal quadrants.
    # 3.  In each quadrant find the most frequent colour among the
    #     non‑8 objects that lie inside the same quadrant of the original grid.
    # 4.  Replace the 8‑cells of that quadrant with the colour found.
    region8   = ofcolor(I, 8)
    box8      = backdrop(region8)
    hmid      = add(leftmost(box8), divide(width(box8), 2))
    vmid      = add(uppermost(box8), divide(height(box8), 2))
    tl        = intersection(region8, box(box8, (0, 0), (vmid, hmid)))   # top‑left
    tr        = intersection(region8, box(box8, (0, hmid), (vmid, rightmost(box8))))   # top‑right
    bl        = intersection(region8, box(box8, (vmid, 0), (lowermost(box8), hmid))) # bottom‑left
    br        = intersection(region8, box(box8, (vmid, hmid), (lowermost(box8), rightmost(box8)))) # bottom‑right

    fav_color = lambda quad: mostcommon(colorfilter(objects(I, False, True, True), mostcommon(quad)))
    O = fill(fill(fill(fill(replace(I, 8, 0),
                       fav_color(tl), tl),
                   fav_color(tr), tr),
               fav_color(bl), bl),
           fav_color(br), br)
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |              nan |          nan |                  nan |                 nan |          nan |
| train2 |              nan |          nan |                  nan |                 nan |          nan |

## Output grids


## Tracebacks
```bash
TypeError: box() takes 1 positional argument but 3 were given
def dsl3(I):
    # ---- Quadrant colour‑fill ---------------------------------------------------
    # 1.  Locate the whole 8‑region.
    # 2.  Split the region into four equal quadrants.
    # 3.  In each quadrant find the most frequent colour among the
    #     non‑8 objects that lie inside the same quadrant of the original grid.
    # 4.  Replace the 8‑cells of that quadrant with the colour found.
    region8   = ofcolor(I, 8)
    box8      = backdrop(region8)
    hmid      = add(leftmost(box8), divide(width(box8), 2))
    vmid      = add(uppermost(box8), divide(height(box8), 2))
    tl        = intersection(region8, box(box8, (0, 0), (vmid, hmid)))   # top‑left
    tr        = intersection(region8, box(box8, (0, hmid), (vmid, rightmost(box8))))   # top‑right
    bl        = intersection(region8, box(box8, (vmid, 0), (lowermost(box8), hmid))) # bottom‑left
    br        = intersection(region8, box(box8, (vmid, hmid), (lowermost(box8), rightmost(box8)))) # bottom‑right

    fav_color = lambda quad: mostcommon(colorfilter(objects(I, False, True, True), mostcommon(quad)))
    O = fill(fill(fill(fill(replace(I, 8, 0),
                       fav_color(tl), tl),
                   fav_color(tr), tr),
               fav_color(bl), bl),
           fav_color(br), br)
    return O
```

---

# Program 4
## DSL
```python
def dsl4(I):
    # ---- Mirrored‑tile of the non‑8 pattern ------------------------------------
    # 1.  Isolate the non‑zero, non‑8 cells (the “seed” pattern).
    # 2.  Extract the minimal subgrid that contains this pattern.
    # 3.  Build four variants of the pattern: original, horizontal mirror,
    #     vertical mirror and both‑mirrored.
    # 4.  Assemble the four variants into a 2×2 tile.
    # 5.  Paint the tile over the original 8‑region (erasing the 8’s first).
    seed          = difference(ofcolor(I, 0), ofcolor(I, 8))
    pattern       = subgrid(backdrop(seed), I)
    hmir          = hmirror(pattern)
    vmir          = vmirror(pattern)
    hvmir         = hmirror(vmir)
    tile          = vconcat(hconcat(pattern, hmir), hconcat(vmir, hvmir))
    cleared       = cover(I, ofcolor(I, 8))
    O             = paint(cleared, toobject(backdrop(ofcolor(I, 8)), tile))
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |                0 |      38.7685 |             0.204545 |                   0 |      38.9731 |
| train2 |                0 |      33.9411 |             0.115385 |                   0 |      34.0565 |

## Output grids

### train1 output

```bash
000000000000
000000000000
000000000000
000031000000
000430000000
000204000000
000000000000
000000000000
000000000000
000000000000
088888800000
088888800000
088888800000
000088888800
000088888800
000088888800
088800088800
088800088800
088800088800
000000000000
000000000000
000000000000
```

### train2 output

```bash
0000000000000
0000300000000
0020340000000
0021100000000
0020040000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0000000000000
0088888800000
0088888800000
0000880000000
0000880000000
0000888888000
0000888888000
0088008800000
0088008800000
0000000000000
0000000000000
0000000000000
0000000000000
```


---

# Program 5
## DSL
```python
def dsl5(I):
    # ---- Relational‑centroid alignment -----------------------------------------
    # 1.  Compute the centre of mass of all non‑8 objects.
    # 2.  Compute the centre of mass of the 8‑region.
    # 3.  Translate the 8‑region so that its centre coincides with the centre
    #     of the other objects.
    # 4.  Fill the moved region with the colour that occurs most often among
    #     the non‑8 objects (ignoring colour 0).
    objs           = difference(objects(I, False, True, True), {ofcolor(I, 8)})
    centre_objs    = centerofmass(combine(objs))
    region8        = ofcolor(I, 8)
    centre_region  = centerofmass(region8)
    shift_vec      = subtract(centre_objs, centre_region)
    moved_region   = shift(region8, shift_vec)
    dominant_color = mostcommon(colorfilter(objs, 0))
    O = fill(replace(I, 8, 0), dominant_color, moved_region)
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |              nan |          nan |                  nan |                 nan |          nan |
| train2 |              nan |          nan |                  nan |                 nan |          nan |

## Output grids


## Tracebacks
```bash
TypeError: combine() missing 1 required positional argument: 'b'
def dsl5(I):
    # ---- Relational‑centroid alignment -----------------------------------------
    # 1.  Compute the centre of mass of all non‑8 objects.
    # 2.  Compute the centre of mass of the 8‑region.
    # 3.  Translate the 8‑region so that its centre coincides with the centre
    #     of the other objects.
    # 4.  Fill the moved region with the colour that occurs most often among
    #     the non‑8 objects (ignoring colour 0).
    objs           = difference(objects(I, False, True, True), {ofcolor(I, 8)})
    centre_objs    = centerofmass(combine(objs))
    region8        = ofcolor(I, 8)
    centre_region  = centerofmass(region8)
    shift_vec      = subtract(centre_objs, centre_region)
    moved_region   = shift(region8, shift_vec)
    dominant_color = mostcommon(colorfilter(objs, 0))
    O = fill(replace(I, 8, 0), dominant_color, moved_region)
    return O
```

---

The goal is to improve the 5 DSL programs incrementally in two phases:

--------------------------------
PHASE 1 — EXPANSION (DISCOVERY)
--------------------------------

- Analyze failures and identify missing spatial or relational patterns.
- Introduce new intermediate concepts using ONLY the provided DSL primitives.
- All transformations MUST be expressed as compositions of DSL primitives.
- Do NOT write imperative logic (loops, indexing, or manual grid traversal).
- Do NOT use global case distinctions based on grid-level properties.

Guidelines:
- Represent all structures as sets of indices or objects derived from the grid.
- Express behaviors as transformations over these sets.
- You may use multiple intermediate concepts, but each must be defined using DSL primitives.
- Avoid hardcoded positional logic or scanning patterns.

--------------------------------
PHASE 2 — REDUCTION (ABSTRACTION)
--------------------------------

- Identify structurally similar transformations.
- Merge them into higher-order transformations using apply, mapply, interval, etc.
- Reduce program length and number of concepts.

Guidelines:
- Merge only transformations that share the same structure.
- Prefer parameterized transformations over duplicated logic.
- Avoid unnecessary intermediate variables.

--------------------------------
STRICT DSL CONSTRAINTS
--------------------------------

- The final program MUST be written entirely using the provided DSL primitives.
- No Python control flow (if, for, while).
- No manual indexing (index, shape, etc.).
- No explicit loops or list comprehensions.
- No global grid analysis (e.g. "if a full row exists", "if checkerboard pattern exists").

--------------------------------
STRUCTURAL BIAS
--------------------------------

- Prefer local, compositional rules over global heuristics.
- Prefer transformations that operate uniformly across the grid.
- Avoid splitting the solution into unrelated cases.

--------------------------------
SEARCH STRATEGY
--------------------------------

- Maintain multiple candidate programs with different structural approaches.
- Vary:
    - how anchors are defined,
    - how propagation directions are constructed,
    - how masks are generated.
- Avoid reusing previously failed structural ideas.

--------------------------------
OBJECTIVE
--------------------------------

Among correct programs, prefer those that:
- use fewer concepts,
- are fully expressed in DSL primitives,
- and describe the transformation as a composition of local operations.

The program must use a single consistent rule to decide where to apply the transformation.
Do not combine multiple independent heuristics (parity, diagonal, density, etc.).
Choose ONE principle and apply it consistently.
Identify a single property that explains all training examples.
Use only that property to guide the transformation.
Remove any part of the program that does not strictly improve performance on all training examples.
Prefer shorter and simpler programs.
Try removing a component of the logic and check if performance improves.

If the transformation cannot be explained by a single local rule,
introduce a global structural property (e.g., symmetry, periodicity, alignment)
and branch on it.

Avoid reusing previously tried concepts such as:
- parity-based rules
- diagonal propagation
- run-length heuristics
unless they clearly solve all examples.

Prefer solutions that are:
1. correct on all training examples
2. simple
3. based on a single idea

Each program MUST belong to a different reasoning family:
1. Global transformation:
   - Apply operations like crop, compress, trim, downscale, symmetry
2. Object extraction:
   - Identify a subset of pixels (e.g., using ofcolor or object detection)
   - Extract a subgrid or bounding box from them
3. Color filtering:
   - Select or remove specific colors and reconstruct the output
4. Geometric reasoning:
   - Use symmetry, mirroring, alignment, or relative positions
5. Relational / structural reasoning:
   - Use relationships between parts (e.g., center, adjacency, repetition)

Constraints:
- Each program must use a DIFFERENT core strategy
- Avoid reusing the same sequence of operations
- Use the DSL primitives explicitly
- Avoid reusing the same core operators across candidates
- Each program should reflect a distinct hypothesis about the task

Ensure diversity across candidates by varying:
- global vs local processing (full grid vs subgrid)
- object-level vs pixel-level reasoning
- use vs avoidance of normalization / cropping

Programs should be short, clean, and compositional.
Prefer minimal and compositional programs.

Important:
Do NOT generate 5 variations of the same idea.

Before writing each program, explicitly choose a different reasoning strategy.

If two programs use similar primitives (e.g., both use compress + downscale),
they will be considered invalid.

If a program achieves zero cost on any training example,
you MUST preserve the underlying transformation responsible for that success.

Do NOT modify or destroy parts of the program that already perfectly solve a training example,
unless you can generalize them without increasing their cost.

nan values correspond to exceptions that are explained by tracebacks and must be corrected by analyzing them.

Generate 5 new structurally diverse hypotheses of plausible DSL programs exploring different transformations issued from the step 2.

# EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION
```python
def dsl1(I):
    # O = ...
    return O

def dsl2(I):
    # O = ...
    return O

def dsl3(I):
    # O = ...
    return O

def dsl4(I):
    # O = ...
    return O

def dsl5(I):
    # O = ...
    return O
```