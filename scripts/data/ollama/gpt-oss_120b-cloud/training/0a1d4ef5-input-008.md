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
    # Global – trim uniform border then rotate 90° clockwise.
    O = rot90(trim(I))
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          36.0694 |         1984 |                  790 |            0.836114 |      2810.91 |
| train2 |          35.3553 |         1767 |                  793 |            0.806452 |      2596.16 |
| train3 |          35.3553 |         2027 |                  793 |            0.806452 |      2856.16 |

## Output grids

### train1 output

```bash
2008200820008002200008008000
0020002800280028082008000820
2082008000006666666008833333
8822002000826666666000033333
8088800800006666666000033333
0002002828006666666802833333
0008800088000008800200033333
0800080802202000088808033333
2002888082800208200220208200
0202200808080820280820808200
0800020000800044444020220220
0000000028000844444002021111
8000082022002844444008021111
8082800082028244444028281111
0002008008880844444080081111
8002000000000044444080081111
0022800020800800822220081111
0002000000802008000808001111
0022202000808082820200021111
8020028208000002020022080802
2000028220800080028000820008
8200800022002082000002002808
8888008020000111110020999992
0200220008880111112008999990
2828202000020111110800999990
8000800800200111110080999990
2000080220200111110028999990
2888080028000080082088800800
```

### train2 output

```bash
2002005052020005002220000500
2000502050225200502002005020
0252005000002022222222250525
0050025888880001111005588882
0005052888880501111005588882
0022002888882051111200588885
2025200888880201111000288882
0020052888885021111022288885
5005550005200222502000088880
5002520050220020252225088880
0020002000500500002500022252
0000225550050533333225202002
0220520244445033333000500025
5200005544440033333050044445
0000000044440233333220544442
2250050044440033333002244442
0225255244442533333002044445
5002000500022233333200202050
0022200050200202020050002005
0025000205500205200222520202
0002050225020277777000022020
5500501111100077777050533330
0200021111105577777020233330
2200001111155277777202033335
0200051111100077777000233330
2000001111102020020552033335
2025000005200200250020505005
2005020000020220555500500200
```

### train3 output

```bash
0000000101000010101190010110
1091009900190900110010901910
9901000022220011010918881000
0011110922229100333908880009
9100991022220999333018889011
0911910922229019333098880010
0100110922220009911918889190
0100119100190010009008880010
0101011901099099101010010001
9101101910110919010000000111
1010009901090991900090909100
0900099188889109177710444441
0910911088880109177700444440
0010000088880110077700444440
0010019188880900077709444441
9000111000101001000199444441
0000010099990100101190444441
1010090101900901990119019011
1010010000199100109000000910
0909091114444400100110101009
1099000114444499100011901009
1199090004444490333300888810
1001010004444490333301888800
0011010014444490333309888811
0001910110100900333301888801
0010010011001099333300110101
1910900111900190001090001001
0000100101900019011109199119
```


---

# Program 2
## DSL
```python
def dsl2(I):
    # Object‑extraction – crop tightly around the largest non‑background object.
    bg   = mostcolor(I)
    objs = objects(I, True, False, True)                 # foreground objects only
    big  = argmax(objs, lambda o: size(o))             # biggest object
    O    = crop(I, ulcorner(big), shape(big))            # its bounding box
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          5.38516 |            8 |                   38 |            0.429783 |      51.8149 |
| train2 |          4.47214 |           66 |                   44 |            0.349215 |     114.821  |
| train3 |          3.60555 |           73 |                   39 |            0.299425 |     115.905  |

## Output grids

### train1 output

```bash
11111111
11111111
11111111
11111111
```

### train2 output

```bash
3333333
3333333
3333333
3333333
3333333
```

### train3 output

```bash
444444
444444
444444
444444
444444
```


---

# Program 3
## DSL
```python
def dsl3(I):
    # Colour‑filter – replace the most common colour by 0 and strip the outer‑most layer.
    O = compress(switch(I, mostcolor(I), 0))
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          38.8973 |         2234 |                  906 |            0.846194 |      3179.74 |
| train2 |          38.1838 |         1954 |                  909 |            0.818182 |      2902    |
| train3 |          38.1838 |         2270 |                  909 |            0.818182 |      3218    |

## Output grids

### train1 output

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

### train2 output

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

### train3 output

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


---

# Program 4
## DSL
```python
def dsl4(I):
    # Geometric – mirror across the counter‑diagonal and keep the lower‑right triangle.
    M    = dmirror(I)                                    # mirror on the main diagonal
    idx  = asindices(M)
    mask = {p for p in idx if p[0] >= p[1]}               # cells on / below the diagonal
    O    = fill(I, 0, mask)                              # zero‑out everything else
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          38.8973 |         1056 |                  906 |            0.830956 |      2001.73 |
| train2 |          38.1838 |         1048 |                  909 |            0.803459 |      1995.99 |
| train3 |          38.1838 |         1069 |                  909 |            0.793106 |      2016.98 |

## Output grids

### train1 output

```bash
020002080002020200280020800000
000333333000111111112882000000
000333333002111111110009999900
000033333222111111118089999988
000003333880111111110029999900
000000333002228888028209999900
000000000282002000000809999988
000000008000288000802020800880
000000000222002882002002008280
000000000080000002820000080000
000000000004444442000800200020
000000000000444442022201111180
000000000000044448080001111102
000000000000004440822021111108
000000000000000440080881111180
000000000000000008000001111102
000000000000000000280020000000
000000000000000000000000820002
000000000000000000080800802202
000000000000000000008020800082
000000000000000000000222000228
000000000000000000000000008200
000000000000000000000008020008
000000000000000000000000200880
000000000000000000000000028000
000000000000000000000000000082
000000000000000000000000000088
000000000000000000000000000080
000000000000000000000000000002
000000000000000000000000000000
```

### train2 output

```bash
020002522052550225225502002000
000522525002255225052000505502
000288888885024444500233333002
000088888882004444002033333020
000008888882204444220233333505
000000888882004444002233333002
000000022000250520205052020552
000000002050500022002000202000
000000000020205200052052005200
000000000025200200202000205050
000000000002333333300777770050
000000000000333333320777772555
000000000000033333302777770252
000000000000003333325777770000
000000000000000333300777772022
000000000000000005222205200220
000000000000000002200005502005
000000000000000000200200500020
000000000000000000025011111202
000000000000000000005511111500
000000000000000000000211111000
000000000000000000000011111000
000000000000000000000001111000
000000000000000000000000050025
000000000000000000000000000005
000000000000000000000000000550
000000000000000000000000000200
000000000000000000000000000005
000000000000000000000000000005
000000000000000000000000000000
```

### train3 output

```bash
000091101910900101000019011999
000091000110100111109900111190
000001191010444444110010100019
000000010011444444090088881010
000009090009444444901188880190
000000888100444444100088881090
000000088009444444001988881010
000000008000000990900101910091
000000000109100099101100000901
000000000000777711101033333010
000000000000777701090033333119
000000000000777700900033333010
000000000000010001911133333009
000000000000000010100900009090
000000000000000000000999909910
000000000000000001914444490100
000000000000000000094444401000
000000000000000000094444400001
000000000000000000014444410990
000000000000000000004444401111
000000000000000000000100111100
000000000000000000000000010110
000000000000000000000000000001
000000000000000000000000111000
000000000000000000000000090911
000000000000000000000000000000
000000000000000000000000000101
000000000000000000000000000001
000000000000000000000000000000
000000000000000000000000000000
```


---

# Program 5
## DSL
```python
def dsl5(I):
    # Relational – merge every pair of adjacent objects that share the same colour.
    objs    = objects(I, True, False, True)               # foreground objects
    pairs   = { (a, b) for a in objs for b in objs
                if a is not b
                and color(a) == color(b)
                and adjacent(toindices(a), toindices(b)) }
    merged  = { recolor(add(color(a), ONE), a | b) for (a, b) in pairs }
    O       = I
    # paint all merged objects (functional style, no explicit loops)
    O = apply(lambda m: paint(O, m), merged).pop()
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
KeyError: 'pop from an empty set'
def dsl5(I):
    # Relational – merge every pair of adjacent objects that share the same colour.
    objs    = objects(I, True, False, True)               # foreground objects
    pairs   = { (a, b) for a in objs for b in objs
                if a is not b
                and color(a) == color(b)
                and adjacent(toindices(a), toindices(b)) }
    merged  = { recolor(add(color(a), ONE), a | b) for (a, b) in pairs }
    O       = I
    # paint all merged objects (functional style, no explicit loops)
    O = apply(lambda m: paint(O, m), merged).pop()
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