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
    O = downscale(I, TEN)
    return O
```

## Explosive scores

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |                1 |      22      |                   15 |            0.384111 |      38.3841 |
| train2 |                0 |      12.5698 |                    1 |            0        |      13.5698 |
| train3 |                0 |      15.748  |                    1 |            0        |      16.748  |

## Output grids

### train1 output

```bash
000
000
200
```

### train2 output

```bash
055
020
250
```

### train3 output

```bash
110
000
111
```


---

# Program 2
## DSL
```python
def dsl2(I):
    pal = remove(ZERO, palette(I))
    col2idx = rbind(ofcolor, I)
    idxsets = apply(col2idx, pal)
    mask = merge(idxsets)
    O = subgrid(mask, I)
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
  File "<string>", line 4, in dsl2
def dsl2(I):
    pal = remove(ZERO, palette(I))
    col2idx = rbind(ofcolor, I)
    idxsets = apply(col2idx, pal)
    mask = merge(idxsets)
    O = subgrid(mask, I)
    return O
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 517, in apply
    return type(container)(function(e) for e in container)
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 517, in <genexpr>
    return type(container)(function(e) for e in container)
                           ^^^^^^^^^^^
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 472, in <lambda>
    return lambda x: function(x, fixed)
                     ^^^^^^^^^^^^^^^^^^
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 653, in ofcolor
    return frozenset((i, j) for i, r in enumerate(grid) for j, v in enumerate(r) if v == value)
                                        ^^^^^^^^^^^^^^^
TypeError: 'int' object is not iterable
```

---

# Program 3
## DSL
```python
def dsl3(I):
    pal = remove(ZERO, palette(I))
    f = lbind(colorcount, I)
    dom = valmax(pal, f)
    mask = ofcolor(I, dom)
    base = canvas(ZERO, shape(I))
    single = fill(base, dom, mask)
    O = subgrid(mask, single)
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
  File "<string>", line 8, in dsl3
def dsl3(I):
    pal = remove(ZERO, palette(I))
    f = lbind(colorcount, I)
    dom = valmax(pal, f)
    mask = ofcolor(I, dom)
    base = canvas(ZERO, shape(I))
    single = fill(base, dom, mask)
    O = subgrid(mask, single)
    return O
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 1166, in subgrid
    return crop(grid, ulcorner(patch), shape(patch))
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 690, in crop
    return tuple(r[start[1]:start[1]+dims[1]] for r in grid[start[0]:start[0]+dims[0]])
                                                            ~~~~~^^^
IndexError: tuple index out of range
```

---

# Program 4
## DSL
```python
def dsl4(I):
    C = compress(I)
    R = rot90(C)
    O = vmirror(hmirror(R))
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
000800800000280202228080028020
000800888028008000082008088820
009999982001111100202208000028
009999908001111100200800800082
009999900801111102000020282820
809999980021111108880002200200
029999902001111100002080088888
280820020000028020022000800280
080002800082008000802282000028
020808022002020000080282002080
811112000202828080800020222000
211110080800080020800000020002
011118002222800800802000822000
011118008044444000000000020088
211118008044444808880080020000
011118282044444282028000828080
211112080044444820022028000080
011112020044444800082000000008
202202202044444000800002000800
000280802808202808080800220208
000280202200280200828088820020
033333080888000020220808000800
833333000200880000088000880008
033333820866666660082820020000
233333000066666660000800888080
033333000066666662800020022880
033333880066666660000080028028
002800080028082008200820002008
200080080000220080002800280020
008828000808000020082002800082
```

### train2 output

```bash
022052200005202050200005500555
000200500555502202000002050020
050050502005200200250000052020
253333025502002020111110000020
003333200077777000111115000202
053333020277777255111110000220
203333202077777550111112000200
003333505077777000111110500555
502022000077777202052205020005
520202522200250200550200052005
250020005002020200205000222000
205020200233333222000500020050
554444020033333524444255252205
224444220033333004444005005220
224444502233333204444000000002
054444005033333004444550000250
552000500033333054444202502205
520020252233333505005552200002
225222000520000500500020002000
508888052225202002205002520050
008888000020522200250005550050
258888222011112058888825002000
228888200011110208888800252022
558888500211115028888820022002
228888550011110508888825050005
028888550011110008888852005002
052505222222222020000050025202
002050020020500252205020500020
200500002220050002025050020020
055050000000020000022202000025
```

### train3 output

```bash
909000011090900001010010101101
991199190111091000910100100009
910010009010009100911100901919
110101100333399010011001001009
110888810333300900101101910000
011888890333309444441001011001
900888810333309444440001010010
101888800333309444440009099119
090010911000199444441100099010
090010101100100444441119090900
001900000090100199100001001011
011091091109910900910109001010
114444409110100109999001000000
014444499100010010100011100091
114444490777000908888191001001
004444400777001108888000001001
004444400777190108888011901900
914444401777190198888199000909
000190909000919909010990001010
111100000001091901101910110199
910001001010199099010911010100
101008880090001009100191100101
009198881911990002222901100100
101008889033391092222901911909
111098881033399902222019900199
990008880933300192222901111000
000018881901011002222000010990
001910901001100909100990019010
001101009110101000010100000000
101001190101000199001991100011
```


---

# Program 5
## DSL
```python
def dsl5(I):
    obs = objects(I, T, F, T)
    bobs = mfilter(obs, rbind(bordering, I))
    idxs = mapply(toindices, bobs)
    borderpatch = merge(idxs)
    inner = cover(I, borderpatch)
    ipal = remove(ZERO, palette(inner))
    occ = apply(rbind(ofcolor, inner), ipal)
    imask = merge(occ)
    O = subgrid(imask, inner)
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
  File "<string>", line 4, in dsl5
def dsl5(I):
    obs = objects(I, T, F, T)
    bobs = mfilter(obs, rbind(bordering, I))
    idxs = mapply(toindices, bobs)
    borderpatch = merge(idxs)
    inner = cover(I, borderpatch)
    ipal = remove(ZERO, palette(inner))
    occ = apply(rbind(ofcolor, inner), ipal)
    imask = merge(occ)
    O = subgrid(imask, inner)
    return O
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 533, in mapply
    return merge(apply(function, container))
                 ^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 517, in apply
    return type(container)(function(e) for e in container)
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 517, in <genexpr>
    return type(container)(function(e) for e in container)
                           ^^^^^^^^^^^
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 699, in toindices
    if isinstance(next(iter(patch))[1], tuple):
                  ~~~~~~~~~~~~~~~~~^^^
TypeError: 'int' object is not subscriptable
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