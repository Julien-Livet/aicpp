# Input->output grid pairs of an ARC task

## train1

### Input

```bash
020002080002020200280020800000
000333333000111111112882000000
802333333002111111110009999900
808333333222111111118089999988
280333333880111111110029999900
800333333002228888028209999900
000800800282002000000809999988
088800208000288000802020800880
000000000222002882002002008280
800000828280000002820000080000
002666608004444442000800200020
808666608084444442022201111180
020666680224444448080001111102
028666680804444440822021111108
002666600024444440080881111180
000666600280882808000001111102
280666602000028000280020000000
008020000080002800000000820002
002080002808000808880800802202
800000882280822800008020800082
220000280800228002000222000228
088008808080000000002200008200
002820200800020800028808020008
200000008802080000002200200880
820008080820008008020080228000
080228280220002222220008080082
002828000000008002022008020088
000080008028000000000028280080
820288000200088080008288028222
208800080080800080200808002800
```

### Output

```bash
319
641
```

## train2

### Input

```bash
020002522052550225225502002000
500522525002255225052000505502
502288888885024444500233333002
050588888882004444002033333020
505088888882204444220233333505
000588888882004444002233333002
000255522000250520205052020552
002255002050500022002000202000
020200002020205200052052005200
020200200025200200202000205050
022211111222333333300777770050
000211111050333333320777772555
005211111520333333302777770252
250211111200333333325777770000
000200502220333333300777772022
002005020205500205222205200220
005200205000050002200005502005
022088888020544444200200500020
002088888225044444025011111202
220088888500044444005511111500
255088888050544444050211111000
200088888000525002502211111000
052552202002505005000011111000
200025005520220055000502050025
005000020550250002020050000005
020205250520000005225200000550
000550222002020052022000000200
000200000000022022000052220005
222000020550005020500050202225
500225220000250205005550020005
```

### Output

```bash
843
137
841
```

## train3

### Input

```bash
100091101910900101000019011999
000091000110100111109900111190
111001191010444444110010100019
019000010011444444090088881010
001109090009444444901188880190
110888888100444444100088881090
109888888009444444001988881010
900888888000000990900101910091
091101910109100099101100000901
110990090000777711101033333010
010033319100777701090033333119
101133310010777700900033333010
011033390109110001911133333009
000109990991990010100900009090
010109101919001000000999909910
109019000099111901914444490100
900090900900900010094444401000
909222229919888809094444400001
001222221010888819914444410990
010222220101888809104444401111
100222220010888809001100111100
919090991999100100101100010110
909001009119910910001000000001
100019111100910111919091111000
100019911010090010000000090911
001110100110000000009991110000
009010100001011100110990101101
000901911110990000009010000901
101909000091000090110111000100
100009901090901110010090109991
```

### Output

```bash
848
373
284
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
    # ① Global – down‑scale the whole picture then restore its original size.
    #     The idea is that a coarse view may reveal the dominant pattern.
    D   = downscale(I, 2)                 # make the picture half size
    O   = hupscale(vupscale(D, 2), 2)      # restore original dimensions
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          38.8973 |         1928 |                  906 |            0.846194 |      2873.74 |
| train2 |          38.1838 |         2097 |                  909 |            0.818182 |      3045    |
| train3 |          38.1838 |         2017 |                  909 |            0.818182 |      2965    |

## Output grids

### train1 output

```bash
000000000000000000220022880000
000000000000000000220022880000
882233333300111111110000999900
882233333300111111110000999900
220033333388111111110022999900
220033333388111111110022999900
000000880088002200000000999988
000000880088002200000000999988
000000000022002288002200008888
000000000022002288002200008888
002266668800444444000000220022
002266668800444444000000220022
000066660022444444000000111100
000066660022444444000000111100
002266660022444444000088111188
002266660022444444000088111188
220066662200008800220022000000
220066662200008800220022000000
002288002200000000880000882200
002288002200000000880000882200
220000220000228800000022000022
220000220000228800000022000022
002222220000000000008800000000
002222220000000000008800000000
880000000022008800000088228800
880000000022008800000088228800
002222000000008800002200000088
002222000000008800002200000088
880088000000008888008888008822
880088000000008888008888008822
```

### train2 output

```bash
000000552255550022225500002200
000000552255550022225500002200
552288888888004444550033333300
552288888888004444550033333300
555588888888224444220033333300
555588888888224444220033333300
000055552200220022225555000055
000055552200220022225555000055
000000002222225500002255005500
000000002222225500002255005500
002211111122333333330077770055
002211111122333333330077770055
005511111122333333332277770055
005511111122333333332277770055
000000552222333333330077772222
000000552222333333330077772222
005500225500000000220000552200
005500225500000000220000552200
002288888822004444005511111100
002288888822004444005511111100
225588888855554444000011111100
225588888855554444000011111100
002255222200555500000011111100
002255222200555500000011111100
005500000055220000000055000000
005500000055220000000055000000
000055222200000055002200000000
000055222200000055002200000000
222200000055005522550055222222
222200000055005522550055222222
```

### train3 output

```bash
110099111111990000000011001199
110099111111990000000011001199
111100111111444444110011110011
111100111111444444110011110011
001100000000444444991188880099
001100000000444444991188880099
119988888800444444001188881111
119988888800444444001188881111
001100990000110099111100000000
001100990000110099111100000000
000033339900777700000033333311
000033339900777700000033333311
001133330000110000991133333300
001133330000110000991133333300
000000111111001100000099999911
000000111111001100000099999911
990099990000990011004444441100
990099990000990011004444441100
001122221111888811994444440099
001122221111888811994444440099
110022220011888800001100111100
110022220011888800001100111100
999900009911990011001100000000
999900009911990011001100000000
110011991111000011000000000011
110011991111000011000000000011
009911110000001100110099111100
009911110000001100110099111100
111100000099000099110011000000
111100000099000099110011000000
```


---

# Program 2
## DSL
```python
def dsl2(I):
    # ② Object‑extraction – keep the biggest non‑background object
    #     and crop tightly around it.
    bg      = mostcolor(I)                                      # background colour
    fg      = difference(asindices(I), ofcolor(I, bg))          # all foreground cells
    objs    = fgobjects(I, univalued=True, diagonal=False)    # separate objects
    bigobj  = argmax(objs, lambda o: size(o))                   # the largest object
    O       = crop(I, ulcorner(bigobj), shape(bigobj))          # its tight bounding box
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |              nan |          nan |                  nan |                 nan |          nan |
| train2 |              nan |          nan |                  nan |                 nan |          nan |
| train3 |              nan |          nan |                  nan |                 nan |          nan |

## Output grids


## Tracebacks
```bash
NameError: name 'fgobjects' is not defined. Did you mean: 'objects'?
def dsl2(I):
    # ② Object‑extraction – keep the biggest non‑background object
    #     and crop tightly around it.
    bg      = mostcolor(I)                                      # background colour
    fg      = difference(asindices(I), ofcolor(I, bg))          # all foreground cells
    objs    = fgobjects(I, univalued=True, diagonal=False)    # separate objects
    bigobj  = argmax(objs, lambda o: size(o))                   # the largest object
    O       = crop(I, ulcorner(bigobj), shape(bigobj))          # its tight bounding box
    return O
```

---

# Program 3
## DSL
```python
def dsl3(I):
    # ③ Colour‑filter – erase the most common colour, then compress.
    bg      = mostcolor(I)                     # background colour
    J       = replace(I, bg, -1)                # give background a unique placeholder
    O       = compress(J)                       # strip the uniform border of that placeholder
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          38.8973 |         1811 |                  906 |            0.846194 |      2756.74 |
| train2 |          38.1838 |         1590 |                  909 |            0.818182 |      2538    |
| train3 |          38.1838 |         1902 |                  909 |            0.818182 |      2850    |

## Output grids

### train1 output

```bash
-12-1-1-12-18-1-1-12-12-12-1-128-1-12-18-1-1-1-1-1
-1-1-1333333-1-1-1111111112882-1-1-1-1-1-1
8-12333333-1-1211111111-1-1-199999-1-1
8-18333333222111111118-189999988
28-133333388-111111111-1-1299999-1-1
8-1-1333333-1-12228888-1282-199999-1-1
-1-1-18-1-18-1-1282-1-12-1-1-1-1-1-18-19999988
-1888-1-12-18-1-1-1288-1-1-18-12-12-18-1-188-1
-1-1-1-1-1-1-1-1-1222-1-12882-1-12-1-12-1-1828-1
8-1-1-1-1-182828-1-1-1-1-1-1282-1-1-1-1-18-1-1-1-1
-1-126666-18-1-14444442-1-1-18-1-12-1-1-12-1
8-186666-18-184444442-1222-1111118-1
-12-166668-1224444448-18-1-1-111111-12
-12866668-18-1444444-1822-1211111-18
-1-126666-1-1-12444444-1-18-188111118-1
-1-1-16666-1-128-18828-18-1-1-1-1-111111-12
28-16666-12-1-1-1-128-1-1-128-1-12-1-1-1-1-1-1-1
-1-18-12-1-1-1-1-18-1-1-128-1-1-1-1-1-1-1-182-1-1-12
-1-12-18-1-1-128-18-1-1-18-1888-18-1-18-122-12
8-1-1-1-1-188228-18228-1-1-1-18-12-18-1-1-182
22-1-1-1-128-18-1-1228-1-12-1-1-1222-1-1-1228
-188-1-188-18-18-1-1-1-1-1-1-1-1-122-1-1-1-182-1-1
-1-1282-12-1-18-1-1-12-18-1-1-1288-18-12-1-1-18
2-1-1-1-1-1-1-188-12-18-1-1-1-1-1-122-1-12-1-188-1
82-1-1-18-18-182-1-1-18-1-18-12-1-18-1228-1-1-1
-18-122828-122-1-1-1222222-1-1-18-18-1-182
-1-12828-1-1-1-1-1-1-1-18-1-12-122-1-18-12-1-188
-1-1-1-18-1-1-18-128-1-1-1-1-1-1-1-1-1-12828-1-18-1
82-1288-1-1-12-1-1-188-18-1-1-18288-128222
2-188-1-1-18-1-18-18-1-1-18-12-1-18-18-1-128-1-1
```

### train2 output

```bash
-12-1-1-12522-15255-12252255-12-1-12-1-1-1
5-1-1522525-1-12255225-152-1-1-15-155-12
5-12288888885-1244445-1-1233333-1-12
-15-1588888882-1-14444-1-12-133333-12-1
5-15-1888888822-1444422-12333335-15
-1-1-1588888882-1-14444-1-12233333-1-12
-1-1-1255522-1-1-125-152-12-15-152-12-1552
-1-12255-1-12-15-15-1-1-122-1-12-1-1-12-12-1-1-1
-12-12-1-1-1-12-12-12-152-1-1-152-152-1-152-1-1
-12-12-1-12-1-1-1252-1-12-1-12-12-1-1-12-15-15-1
-1222111112223333333-1-177777-1-15-1
-1-1-1211111-15-133333332-1777772555
-1-1521111152-13333333-1277777-1252
25-12111112-1-133333332577777-1-1-1-1
-1-1-12-1-15-1222-13333333-1-1777772-122
-1-12-1-15-12-12-155-1-12-152222-152-1-122-1
-1-152-1-12-15-1-1-1-15-1-1-122-1-1-1-155-12-1-15
-122-188888-12-15444442-1-12-1-15-1-1-12-1
-1-12-188888225-144444-125-1111112-12
22-1-1888885-1-1-144444-1-155111115-1-1
255-188888-15-1544444-15-1211111-1-1-1
2-1-1-188888-1-1-1525-1-125-12211111-1-1-1
-1525522-12-1-125-15-1-15-1-1-1-111111-1-1-1
2-1-1-125-1-1552-122-1-155-1-1-15-12-15-1-125
-1-15-1-1-1-12-155-125-1-1-12-12-1-15-1-1-1-1-1-15
-12-12-1525-152-1-1-1-1-1-152252-1-1-1-1-155-1
-1-1-155-1222-1-12-12-1-152-122-1-1-1-1-1-12-1-1
-1-1-12-1-1-1-1-1-1-1-1-122-122-1-1-1-15222-1-1-15
222-1-1-1-12-155-1-1-15-12-15-1-1-15-12-12225
5-1-122522-1-1-1-125-12-15-1-1555-1-12-1-1-15
```

### train3 output

```bash
1-1-1-1911-1191-19-1-11-11-1-1-1-119-111999
-1-1-1-191-1-1-111-11-1-11111-199-1-111119-1
111-1-11191-11-144444411-1-11-11-1-1-119
-119-1-1-1-11-1-111444444-19-1-188881-11-1
-1-111-19-19-1-1-194444449-1118888-119-1
11-18888881-1-14444441-1-1-188881-19-1
1-19888888-1-19444444-1-11988881-11-1
9-1-1888888-1-1-1-1-1-199-19-1-11-1191-1-191
-1911-1191-11-191-1-1-1991-111-1-1-1-1-19-11
11-199-1-19-1-1-1-17777111-11-133333-11-1
-11-1-1333191-1-17777-11-19-1-133333119
1-1113331-1-11-17777-1-19-1-1-133333-11-1
-111-13339-11-1911-1-1-11911133333-1-19
-1-1-11-1999-199199-1-11-11-1-19-1-1-1-19-19-1
-11-11-191-11919-1-11-1-1-1-1-1-19999-1991-1
1-19-119-1-1-1-1991119-1191444449-11-1-1
9-1-1-19-19-1-19-1-19-1-1-11-1-1944444-11-1-1-1
9-192222299198888-19-1944444-1-1-1-11
-1-11222221-11-188881991444441-199-1
-11-122222-11-118888-191-144444-11111
1-1-122222-1-11-18888-19-1-111-1-11111-1-1
919-19-19919991-1-11-1-11-111-1-1-11-111-1
9-19-1-11-1-1911991-191-1-1-11-1-1-1-1-1-1-1-11
1-1-1-1191111-1-191-1111919-191111-1-1-1
1-1-1-119911-11-1-19-1-11-1-1-1-1-1-1-1-19-1911
-1-1111-11-1-111-1-1-1-1-1-1-1-1-1999111-1-1-1-1
-1-19-11-11-1-1-1-11-1111-1-111-199-11-111-11
-1-1-19-1191111-199-1-1-1-1-1-19-11-1-1-1-19-11
1-119-19-1-1-1-191-1-1-1-19-111-1111-1-1-11-1-1
1-1-1-1-199-11-19-19-1111-1-11-1-19-11-19991
```


---

# Program 4
## DSL
```python
def dsl4(I):
    # ④ Geometric – mirror the picture across the main diagonal,
    #     then keep only the part that lies above the diagonal.
    M      = dmirror(I)                         # mirror along the counter‑diagonal
    # build a mask that contains the upper‑right triangular region
    idx    = asindices(M)
    mask   = {p for p in idx if p[0] <= p[1]}    # cells on / above the diagonal
    O      = fill(I, 0, mask)                    # keep those cells, set the rest to 0
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          38.8973 |         1087 |                  906 |            0.817751 |      2032.72 |
| train2 |          38.1838 |          808 |                  909 |            0.788752 |      1755.97 |
| train3 |          38.1838 |         1074 |                  909 |            0.804316 |      2021.99 |

## Output grids

### train1 output

```bash
000000000000000000000000000000
000000000000000000000000000000
800000000000000000000000000000
808000000000000000000000000000
280300000000000000000000000000
800330000000000000000000000000
000800000000000000000000000000
088800200000000000000000000000
000000000000000000000000000000
800000828000000000000000000000
002666608000000000000000000000
808666608080000000000000000000
020666680224000000000000000000
028666680804400000000000000000
002666600024440000000000000000
000666600280882000000000000000
280666602000028000000000000000
008020000080002800000000000000
002080002808000808000000000000
800000882280822800000000000000
220000280800228002000000000000
088008808080000000002000000000
002820200800020800028800000000
200000008802080000002200000000
820008080820008008020080000000
080228280220002222220008000000
002828000000008002022008020000
000080008028000000000028280000
820288000200088080008288028200
208800080080800080200808002800
```

### train2 output

```bash
000000000000000000000000000000
500000000000000000000000000000
500000000000000000000000000000
050000000000000000000000000000
505000000000000000000000000000
000580000000000000000000000000
000255000000000000000000000000
002255000000000000000000000000
020200000000000000000000000000
020200200000000000000000000000
022211111200000000000000000000
000211111050000000000000000000
005211111520000000000000000000
250211111200300000000000000000
000200502220330000000000000000
002005020205500000000000000000
005200205000050000000000000000
022088888020544440000000000000
002088888225044444000000000000
220088888500044444000000000000
255088888050544444050000000000
200088888000525002502000000000
052552202002505005000000000000
200025005520220055000500000000
005000020550250002020050000000
020205250520000005225200000000
000550222002020052022000000000
000200000000022022000052220000
222000020550005020500050202200
500225220000250205005550020000
```

### train3 output

```bash
000000000000000000000000000000
000000000000000000000000000000
110000000000000000000000000000
019000000000000000000000000000
001100000000000000000000000000
110880000000000000000000000000
109888000000000000000000000000
900888800000000000000000000000
091101910000000000000000000000
110990090000000000000000000000
010033319100000000000000000000
101133310010000000000000000000
011033390109000000000000000000
000109990991900000000000000000
010109101919000000000000000000
109019000099111000000000000000
900090900900900000000000000000
909222229919888800000000000000
001222221010888819000000000000
010222220101888809100000000000
100222220010888809000000000000
919090991999100100101000000000
909001009119910910001000000000
100019111100910111919090000000
100019911010090010000000000000
001110100110000000009991100000
009010100001011100110990100000
000901911110990000009010000000
101909000091000090110111000100
100009901090901110010090109990
```


---

# Program 5
## DSL
```python
def dsl5(I):
    # ⑤ Relational – find pairs of adjacent objects of the same colour,
    #     colour‑merge them, then return the resulting picture.
    bg      = mostcolor(I)
    objs    = fgobjects(I, univalued=True, diagonal=False)
    # pick every pair of objects that share the same colour and are adjacent
    pairs   = { (a,b) for a in objs for b in objs
                if a is not b
                and color(a) == color(b)
                and adjacent({a},{b}) }
    # merge each pair into a single recoloured object (colour = original colour + 1)
    merged  = { recolor(add(color(a), ONE), a | b) for (a,b) in pairs }
    # paint all merged objects over the original grid
    O = I
    for m in merged:
        O = paint(O, m)
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |              nan |          nan |                  nan |                 nan |          nan |
| train2 |              nan |          nan |                  nan |                 nan |          nan |
| train3 |              nan |          nan |                  nan |                 nan |          nan |

## Output grids


## Tracebacks
```bash
NameError: name 'fgobjects' is not defined. Did you mean: 'objects'?
def dsl5(I):
    # ⑤ Relational – find pairs of adjacent objects of the same colour,
    #     colour‑merge them, then return the resulting picture.
    bg      = mostcolor(I)
    objs    = fgobjects(I, univalued=True, diagonal=False)
    # pick every pair of objects that share the same colour and are adjacent
    pairs   = { (a,b) for a in objs for b in objs
                if a is not b
                and color(a) == color(b)
                and adjacent({a},{b}) }
    # merge each pair into a single recoloured object (colour = original colour + 1)
    merged  = { recolor(add(color(a), ONE), a | b) for (a,b) in pairs }
    # paint all merged objects over the original grid
    O = I
    for m in merged:
        O = paint(O, m)
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