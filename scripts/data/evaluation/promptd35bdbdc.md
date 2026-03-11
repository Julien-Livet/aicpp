You are given several input-output grid pairs from an ARC task:
([[0, 0, 0, 0, 0, 0, 0, 3, 3, 3], [0, 0, 5, 5, 5, 5, 5, 3, 4, 3], [0, 5, 0, 0, 0, 0, 0, 3, 3, 3], [0, 5, 4, 4, 4, 0, 0, 0, 0, 0], [5, 0, 4, 2, 4, 0, 0, 6, 6, 6], [0, 5, 4, 4, 4, 0, 5, 6, 1, 6], [0, 5, 5, 5, 5, 5, 0, 6, 6, 6], [0, 0, 1, 1, 1, 0, 0, 0, 0, 0], [0, 0, 1, 3, 1, 0, 0, 0, 0, 0], [0, 0, 1, 1, 1, 0, 0, 0, 0, 0]], [[0, 0, 0, 0, 0, 0, 0, 3, 3, 3], [0, 0, 5, 5, 5, 5, 5, 3, 2, 3], [0, 5, 0, 0, 0, 0, 0, 3, 3, 3], [0, 5, 0, 0, 0, 0, 0, 0, 0, 0], [5, 0, 0, 0, 0, 0, 0, 6, 6, 6], [0, 5, 0, 0, 0, 0, 5, 6, 3, 6], [0, 5, 5, 5, 5, 5, 0, 6, 6, 6], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]])
([[2, 2, 2, 0, 0, 0, 3, 3, 3, 0], [2, 6, 2, 0, 0, 0, 3, 2, 3, 0], [2, 2, 2, 0, 5, 0, 3, 3, 3, 0], [0, 0, 0, 5, 0, 5, 5, 5, 5, 0], [8, 8, 8, 0, 5, 0, 0, 1, 1, 1], [8, 3, 8, 0, 0, 5, 0, 1, 4, 1], [8, 8, 8, 0, 5, 0, 0, 1, 1, 1], [0, 5, 0, 5, 4, 4, 4, 0, 0, 0], [0, 5, 5, 0, 4, 8, 4, 0, 0, 0], [0, 0, 0, 0, 4, 4, 4, 0, 0, 0]], [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 5, 0, 0, 0, 0, 0], [0, 0, 0, 5, 0, 5, 5, 5, 5, 0], [8, 8, 8, 0, 5, 0, 0, 1, 1, 1], [8, 2, 8, 0, 0, 5, 0, 1, 8, 1], [8, 8, 8, 0, 5, 0, 0, 1, 1, 1], [0, 5, 0, 5, 0, 0, 0, 0, 0, 0], [0, 5, 5, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]])
([[1, 1, 1, 0, 0, 0, 0, 4, 4, 4], [1, 2, 1, 0, 0, 0, 0, 4, 3, 4], [1, 1, 1, 0, 0, 5, 0, 4, 4, 4], [0, 5, 0, 0, 5, 0, 5, 0, 0, 0], [0, 5, 0, 5, 3, 3, 3, 5, 0, 0], [0, 0, 5, 0, 3, 6, 3, 0, 5, 0], [0, 0, 0, 0, 3, 3, 3, 0, 5, 0], [2, 2, 2, 0, 0, 0, 0, 7, 7, 7], [2, 9, 2, 0, 0, 0, 0, 7, 4, 7], [2, 2, 2, 0, 0, 0, 0, 7, 7, 7]], [[1, 1, 1, 0, 0, 0, 0, 0, 0, 0], [1, 9, 1, 0, 0, 0, 0, 0, 0, 0], [1, 1, 1, 0, 0, 5, 0, 0, 0, 0], [0, 5, 0, 0, 5, 0, 5, 0, 0, 0], [0, 5, 0, 5, 0, 0, 0, 5, 0, 0], [0, 0, 5, 0, 0, 0, 0, 0, 5, 0], [0, 0, 0, 0, 0, 0, 0, 0, 5, 0], [0, 0, 0, 0, 0, 0, 0, 7, 7, 7], [0, 0, 0, 0, 0, 0, 0, 7, 3, 7], [0, 0, 0, 0, 0, 0, 0, 7, 7, 7]])

Available types:
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

Available variables:
```python
I: tuple[tuple]
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

Available primitives:
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

Previous program scores (best, intermediate, worst):

|Program|Size cost|Value cost|Pixel overlap cost|Bounding box cost|Total cost|
|-|-|-|-|-|
|def dsl2(I):;    # Keep rings in the most populated column lane; tiebreaker: choose the lane closest to the right border.;    # Fill kept centers top-to-bottom with ascending donor center values.;    obs = objects(I, T, F, T);    O = canvas(ZERO, shape(I));    h, w = shape(I);    rings = [];    lines5 = [];    for obj in totuple(obs):;        if (width(obj) == 3 and height(obj) == 3 and size(obj) >= 8):;            rings.append(obj);        elif color(obj) == FIVE and (hline(obj) or vline(obj)):;            lines5.append(obj);    if rings:;        colgroups = {};        for r in rings:;            lcol = leftmost(r);            colgroups[lcol] = colgroups.get(lcol, []) + [r];        best_col = None;        best_count = -1;        for cc, lst in colgroups.items():;            # prefer lane nearer the right (larger column) on ties;            if len(lst) > best_count or (len(lst) == best_count and (best_col is None or cc > best_col)):;                best_col = cc;                best_count = len(lst);        keep = set(colgroups.get(best_col, []));        donors = [];        for r in rings:;            if r not in keep:;                val = index(I, center(r));                if val != ZERO:;                    donors.append(val);        donors.sort();        keep_sorted = sorted(list(keep), key=lambda r: uppermost(r));        for r in keep_sorted:;            O = paint(O, r);        for i, r in enumerate(keep_sorted):;            if i < len(donors):;                O = fill(O, donors[i], initset(center(r)));    for ln in lines5:;        O = paint(O, ln);    return O|0.0|41.08799393319633|0.47|0.12195787939465261|41.67995181259098|
|def dsl3(I):;    # Prefer keeping the main diagonal pair (TL and BR) if present; else anti-diagonal (TR and BL).;    # Centers for kept rings taken from the opposite diagonal; fallback: densest column (rightmost on tie).;    obs = objects(I, T, F, T);    O = canvas(ZERO, shape(I));    rings = [];    lines5 = [];    for obj in totuple(obs):;        if (width(obj) == 3 and height(obj) == 3 and size(obj) >= 8):;            rings.append(obj);        elif color(obj) == FIVE and (hline(obj) or vline(obj)):;            lines5.append(obj);    kept = [];    donors_map = {};    if rings:;        info = [];        for r in rings:;            c = center(r);            info.append((c[0], c[1], r));        if info:;            tl = min(info, key=lambda x: (x[0], x[1]))  # smallest row, then col;            br = max(info, key=lambda x: (x[0], x[1]))  # largest row, then col;            tr_candidates = [x for x in info if x[0] == min(i[0] for i in info)];            bl_candidates = [x for x in info if x[0] == max(i[0] for i in info)];            tr = max(tr_candidates, key=lambda x: x[1]) if tr_candidates else None;            bl = min(bl_candidates, key=lambda x: x[1]) if bl_candidates else None;            used = set();            if tl and br and tl[2] != br[2]:;                kept = [tl[2], br[2]];                used.update([tl[2], br[2]]);                # donors from opposite diagonal positions if available;                if bl:;                    donors_map[tl[2]] = index(I, center(bl[2]));                    used.add(bl[2]);                if tr:;                    donors_map[br[2]] = index(I, center(tr[2]));                    used.add(tr[2]);            elif tr and bl and tr[2] != bl[2]:;                kept = [tr[2], bl[2]];                used.update([tr[2], bl[2]]);                if tl:;                    donors_map[tr[2]] = index(I, center(tl[2]));                    used.add(tl[2]);                if br:;                    donors_map[bl[2]] = index(I, center(br[2]));                    used.add(br[2]);            else:;                # fallback: densest column lane, tie -> rightmost;                colgroups = {};                for r in rings:;                    lcol = leftmost(r);                    colgroups[lcol] = colgroups.get(lcol, []) + [r];                best_col = None;                best_count = -1;                for cc, lst in colgroups.items():;                    if len(lst) > best_count or (len(lst) == best_count and (best_col is None or cc > best_col)):;                        best_col = cc;                        best_count = len(lst);                kept = list(colgroups.get(best_col, []));                used = set(kept);            # paint and assign donors;            for r in kept:;                O = paint(O, r);            # any remaining donors;            remaining_donors = [];            for r in rings:;                if r not in used:;                    v = index(I, center(r));                    if v != ZERO:;                        remaining_donors.append(v);            remaining_donors.sort();            # assign preferred mapped donors first;            assigned = set();            for r in kept:;                if r in donors_map and donors_map[r] != ZERO:;                    O = fill(O, donors_map[r], initset(center(r)));                    assigned.add(r);            # fill remaining kept without mapped donors using sorted donors;            ki = 0;            for r in kept:;                if r in assigned:;                    continue;                if ki < len(remaining_donors):;                    O = fill(O, remaining_donors[ki], initset(center(r)));                    ki += 1;    for ln in lines5:;        O = paint(O, ln);    return O|0.0|51.57518409559903|0.64|0.19266855748830736|52.40785265308733|
|def dsl5(I):;    # Keep rings in the row band whose centers are, on average, farthest to the right (max mean center column).;    # Donors: centers from other rings sorted ascending, assigned left-to-right within the kept band.;    obs = objects(I, T, F, T);    O = canvas(ZERO, shape(I));    rings = [];    lines5 = [];    for obj in totuple(obs):;        if (width(obj) == 3 and height(obj) == 3 and size(obj) >= 8):;            rings.append(obj);        elif color(obj) == FIVE and (hline(obj) or vline(obj)):;            lines5.append(obj);    if rings:;        # group by uppermost row (row band);        rowgroups = {};        for r in rings:;            rtop = uppermost(r);            rowgroups.setdefault(rtop, []).append(r);        best_row = None;        best_score = None;        for rr, lst in rowgroups.items():;            cols = [center(r)[1] for r in lst];            mean_col = sum(cols) / max(1, len(cols));            if (best_score is None) or (mean_col > best_score) or (mean_col == best_score and rr > best_row):;                best_row = rr;                best_score = mean_col;        keep = set(rowgroups.get(best_row, []));        donors = [];        for r in rings:;            if r not in keep:;                v = index(I, center(r));                if v != ZERO:;                    donors.append(v);        donors.sort();        keep_sorted = sorted(list(keep), key=lambda r: leftmost(r));        for r in keep_sorted:;            O = paint(O, r);        for i, r in enumerate(keep_sorted):;            if i < len(donors):;                O = fill(O, donors[i], initset(center(r)));    for ln in lines5:;        O = paint(O, ln);    return O|0.0|67.05301803980338|0.7300000000000001|0.2895463723288345|68.07256441213221|

Propose at most 5 diverse hypotheses of plausible DSL programs exploring different transformations avoiding previous low-scoring.

Workflow: analyze transformation -> identify relevant object properties -> propose possible rules -> analyze why previous programs failed based on their scores -> identify primitives -> generate DSL programs

All programs must be described within a single Python MarkDown tag.

EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION:
```python
def dsl1(I):
    O = vmirror(I)
    return O

def dsl2(I):
    O = hmirror(I)
    return O

def dsl3(I):
    O = dmirror(I)
    return O

def dsl4(I):
    O = rot180(I)
    return O
    
def dsl5(I):
    x1 = replace(I, FIVE, ZERO)
    O = downscale(x1, THREE)
    return O
```
