# Input->output grid pairs of an ARC task

# train1

## Input

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

## Output

```bash
319
641
```

# train2

## Input

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

## Output

```bash
843
137
841
```

# train3

## Input

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

## Output

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
    # Global transformation: remove interior frontiers globally, then trim outer background
    O = trim(compress(I))
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
0033333300011111111288200000
0233333300211111111000999990
0833333322211111111808999998
8033333388011111111002999990
0033333300222888802820999990
0080080028200200000080999998
8880020800028800080202080088
0000000022200288200200200828
0000082828000000282000008000
0266660800444444200080020002
0866660808444444202220111118
2066668022444444808000111110
2866668080444444082202111110
0266660002444444008088111118
0066660028088280800000111110
8066660200002800028002000000
0802000008000280000000082000
0208000280800080888080080220
0000088228082280000802080008
2000028080022800200022200022
8800880808000000000220000820
0282020080002080002880802000
0000000880208000000220020088
2000808082000800802008022800
8022828022000222222000808008
0282800000000800202200802008
0008000802800000000002828008
2028800020008808000828802822
```

### train2 output

```bash
0052252500225522505200050550
0228888888502444450023333300
5058888888200444400203333302
0508888888220444422023333350
0058888888200444400223333300
0025552200025052020505202055
0225500205050002200200020200
2020000202020520005205200520
2020020002520020020200020505
2221111122233333330077777005
0021111105033333332077777255
0521111152033333330277777025
5021111120033333332577777000
0020050222033333330077777202
0200502020550020522220520022
0520020500005000220000550200
2208888802054444420020050002
0208888822504444402501111120
2008888850004444400551111150
5508888805054444405021111100
0008888800052500250221111100
5255220200250500500001111100
0002500552022005500050205002
0500002055025000202005000000
2020525052000000522520000055
0055022200202005202200000020
0020000000002202200005222000
2200002055000502050005020222
```

### train3 output

```bash
0009100011010011110990011119
1100119101044444411001010001
1900001001144444409008888101
0110909000944444490118888019
1088888810044444410008888109
0988888800944444400198888101
0088888800000099090010191009
9110191010910009910110000090
1099009000077771110103333301
1003331910077770109003333311
0113331001077770090003333301
1103339010911000191113333300
0010999099199001010090000909
1010910191900100000099990991
0901900009911190191444449010
0009090090090001009444440100
0922222991988880909444440000
0122222101088881991444441099
1022222010188880910444440111
0022222001088880900110011110
1909099199910010010110001011
0900100911991091000100000000
0001911110091011191909111100
0001991101009001000000009091
0111010011000000000999111000
0901010000101110011099010110
0090191111099000000901000090
0190900009100009011011100010
```


---

# Program 2
## DSL
```python
def dsl2(I):
    # Object extraction: crop to the largest foreground univalued object
    obs = objects(I, T, F, T)
    o = argmax(obs, size)
    O = subgrid(o, I)
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
    # Color filtering: keep only the most frequent nonzero color and trim
    colors = remove(ZERO, palette(I))
    mc = argmax(colors, lbind(colorcount, I))
    inds = ofcolor(I, mc)
    obj = toobject(inds, I)
    O = trim(paint(canvas(ZERO, shape(I)), obj))
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          36.0694 |         1080 |                  790 |            0.836114 |     1906.91  |
| train2 |          35.3553 |          279 |                  793 |            0.806452 |     1108.16  |
| train3 |          35.3553 |          143 |                  793 |            0.806452 |      972.162 |

## Output grids

### train1 output

```bash
0000000000000000000088000000
0000000000000000000000000000
0800000000000000000808000008
8000000088000000000000000000
0000000000000888800800000000
0080080008000000000080000008
8880000800008800080000080088
0000000000000088000000000808
0000080808000000080000008000
0000000800000000000080000000
0800000808000000000000000008
0000008000000000808000000000
0800008080000000080000000000
0000000000000000008088000008
0000000008088080800000000000
8000000000000800008000000000
0800000008000080000000080000
0008000080800080888080080000
0000088008080080000800080008
0000008080000800000000000000
8800880808000000000000000800
0080000080000080000880800000
0000000880008000000000000088
0000808080000800800008000800
8000808000000000000000808008
0080800000000800000000800008
0008000800800000000000808008
0008800000008808000808800800
```

### train2 output

```bash
0002202000220022000200000000
0220000000002000000020000000
0000000000200000000200000002
0000000000220000022020000000
0000000000200000000220000000
0020002200020002020000202000
0220000200000002200200020200
2020000202020020000200200020
2020020002020020020200020000
2220000022200000000000000000
0020000000000000002000000200
0020000002000000000200000020
0020000020000000002000000000
0020000222000000000000000202
0200002020000020022220020022
0020020000000000220000000200
2200000002000000020020000002
0200000022000000002000000020
2000000000000000000000000000
0000000000000000000020000000
0000000000002000200220000000
0200220200200000000000000000
0002000002022000000000200002
0000002000020000202000000000
2020020002000000022020000000
0000022200202000202200000020
0020000000002202200000222000
2200002000000002000000020222
```

### train3 output

```bash
0000100011010011110000011110
1100110101000000011001010001
1000001001100000000000000101
0110000000000000000110000010
1000000010000000010000000100
0000000000000000000100000101
0000000000000000000010101000
0110101010010000010110000000
1000000000000001110100000001
1000001010000000100000000011
0110001001000000000000000001
1100000010011000101110000000
0010000000100001010000000000
1010010101000100000000000001
0001000000011100101000000010
0000000000000001000000000100
0000000001000000000000000000
0100000101000001001000001000
1000000010100000010000000111
0000000001000000000110011110
1000000100010010010110001011
0000100011001001000100000000
0001011110001011101000111100
0001001101000001000000000001
0111010011000000000000111000
0001010000101110011000010110
0000101111000000000001000000
0100000000100000011011100010
```


---

# Program 4
## DSL
```python
def dsl4(I):
    # Geometric reasoning: intersect the grid with its vertical mirror and trim
    S = cellwise(I, vmirror(I), ZERO)
    O = trim(S)
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          36.0694 |          304 |                  790 |            0.836114 |      1130.91 |
| train2 |          35.3553 |          297 |                  793 |            0.806452 |      1126.16 |
| train3 |          35.3553 |          497 |                  793 |            0.806452 |      1326.16 |

## Output grids

### train1 output

```bash
0000000000011111100000000000
0000000000011111100000000000
0000000000011111100000000000
0000000000011111100000000000
0000000000000880000000000000
0000000000000000000000000000
8800000000000000000000000088
0000000020000000000200000000
0000000000000000000000000000
0000000800004444000080000000
0000000000004444000000000000
0000000000004444000000000000
0000000000004444000000000000
0000000000004444000000000000
0000000000080000800000000000
0000000000000000000000000000
0002000000000000000000002000
0200000000800000080000000020
0000000000000000000000000000
2000020000020000200000200002
0000000000000000000000000000
0002000080000000000800002000
0000000000000000000000000000
0000008002000000002008000000
8000000002000220002000000008
0002000000000000000000002000
0008000000000000000000008000
2000000000008008000000000002
```

### train2 output

```bash
0050000000000000000000000500
0000000000500440050000000000
0000000000000440000000000000
0500000000200440020000000050
0000000000000440000000000000
0000000000000000000000000000
0020000000000000000000000200
0000000000000000000000000000
0000000000000000000000000000
0000000000033333300000000000
0020000000033333300000000200
0000000000033333300000000000
0000000000033333300000000000
0020000000033333300000000200
0200000020050000500200000020
0020000000000000000000000200
2000000000004444000000000002
0200000002004444002000000020
0000000050004444000500000000
0000000005004444005000000000
0000000000000000000000000000
0000000000050000500000000000
0000000500000000000050000000
0000000000020000200000000000
0000000052000000002500000000
0000000000000000000000000000
0000000000002002000000000000
2200000000000000000000000022
```

### train3 output

```bash
0000100000010000100000010000
1000100001044444401000010001
1000000000044444400000000001
0100000000944444490000000010
0008888000044444400008888000
0008888000044444400008888000
0000000000000000000000000000
0000000010000000000100000000
1000000000000770000000000001
1003330000000770000000333001
0003330000000770000000333000
0003330010910000190100333000
0000000000100000010000000000
1000900000000000000000090001
0000000000910000190000000000
0000000000000000000000000000
0000000000000880000000000000
0000000001000880001000000000
1000000000100880010000000001
0000000000000880000000000000
1000000100000000000010000001
0000000010001001000100000000
0001010000001001000000101000
0000000000000000000000000000
0001010000000000000000101000
0000000000100110010000000000
0000001000000000000001000000
0100000000100000010000000010
```


---

# Program 5
## DSL
```python
def dsl5(I):
    # Relational/structural: mark bounding-box corners of each object with its color, then trim
    obs = objects(I, T, F, T)
    mk = fork(recolor, color, corners)
    corners_objs = merge(apply(mk, obs))
    O = trim(paint(canvas(ZERO, shape(I)), corners_objs))
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          36.0694 |         1266 |                  790 |            0.836114 |      2092.91 |
| train2 |          35.3553 |          900 |                  793 |            0.806452 |      1729.16 |
| train3 |          35.3553 |         1285 |                  793 |            0.806452 |      2114.16 |

## Output grids

### train1 output

```bash
0030000300010000001288200000
0200000020200000000000900090
0800000020200000000808000008
8000000088010000001002000000
0030000300202800802820000000
8080080028202200000080900090
8080020800028800080202080000
0000000020200288200200200880
0000082828200000082000008000
0260060000400004000080020002
0800000808000000202020100018
2000008022000000808000000000
2800008080000000082202000000
0200000002400004008088000008
0000000028088280800000100010
8060060200002800028002000000
0802000008000280000000082000
0208000280800000808080000220
0000088228080280000800280008
2000088080020200200000000022
8800880808000000000200200822
0282020880002080002880802000
0000000000208000000220022088
2000808882000200800208022800
8022028022000000000008808008
0222800000000200000200002000
0008800802800000000002028008
2028800020008808000820002820
```

### train2 output

```bash
0052252500220522505200050550
0228000008502400450023000300
5050000000220000000200000002
0500000000000000022220000050
0058000008220400400223000300
2025052200025052220505202055
0005050005050002200200020200
0000002220220520005005200520
0000020000520020020200020550
0001000120230000030070007000
0000000005000000002000000200
0500000052000000000200000050
5001000202000000002500000000
2020050000030000030070007220
0200502202550020500020550020
0520020500005000000000000200
2208000822054000200020550002
2200000022500000002551000120
2000000050000000000550000050
5500000005054000405220000000
2008000800002500250220000000
5255220200250505500001000100
0002500505022005500050205002
0500002000025000220205000000
2020525505000000500520000055
0055020200202205220200000020
0020000000002200000505202000
0200022055000502250000202202
```

### train3 output

```bash
0009000000010000000990000090
0100119100040010401001010011
0100001010100000009008008101
0110909000900000090110000019
1080000810000000010000000109
1900000000940000400198008101
0080000800000090990110191009
9110191010910091910000000090
1099009000070070000113000311
1003031910000001019000000000
1010001001070070090000000011
1013939010911000191013000300
0010000099199001010090090999
1010010191910100000090090991
0901909009910190191400049010
0009090990090001009000000100
0920002991980080999000000000
0100000101000001001000001099
1000000010100000010400040000
0020002001080080990110000000
1909099190010010010000010000
0900110901001010100110000000
0101990090091000091909100100
0000990011009010100000009091
0000010011000000000909101000
0101010000101010011909101110
0090191001099000000910100090
0190990009100009011010100010
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