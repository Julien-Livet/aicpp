You are given several input-output grid pairs from an ARC task:
([[2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 2, 2, 2, 2, 2, 2, 4, 4, 1, 4, 4, 2, 2], [2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 2, 2, 2], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 4, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]], [[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0], [2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 8], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8], [2, 2, 2, 2, 2, 2, 2, 4, 4, 1, 4, 4, 2, 8], [2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 2, 2, 8], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8], [2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8], [2, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8], [2, 4, 8, 2, 8, 2, 8, 2, 8, 2, 8, 2, 8, 8], [2, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8], [2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8]])
([[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 8, 1, 1, 1, 8, 8, 3, 8, 8, 1], [1, 1, 1, 8, 8, 1, 1, 1, 8, 8, 8, 1, 1], [1, 1, 1, 2, 8, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]], [[0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1], [2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [2, 1, 1, 8, 1, 1, 1, 8, 8, 3, 8, 8, 1], [2, 1, 1, 8, 8, 1, 1, 1, 8, 8, 8, 1, 1], [2, 2, 1, 2, 8, 1, 1, 1, 1, 1, 1, 1, 1], [2, 1, 1, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1], [2, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1], [2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]])
([[3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 3], [3, 3, 3, 1, 1, 6, 1, 1, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]], [[3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 3], [3, 3, 3, 1, 1, 6, 1, 1, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 6, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 6, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 6, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 6, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 6, 3, 3, 3, 3, 3, 3], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6]])

Available types:
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

Available variables:
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

Available primitives:
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

Previous program scores (best, intermediate, worst):

|Program|Size cost|Value cost|Pixel overlap cost|Bounding box cost|Total cost|
|-|-|-|-|-|
|def dsl2(I):;    # Two singletons: prefer vertical clear path if any, else horizontal; paint border + step-2 ray; zero corners;    inds = asindices(I);    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds);    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc);    bg = mostcolor(I);    singles = sizefilter(objects(I, T, F, T), ONE);;    o1 = first(singles); o2 = last(singles);    two = flip(equality(o1, o2));;    def proc(O, o, gate):;        p = first(toindices(o));        bu = difference(intersection(shoot(p, UP), inds), initset(p));        bd = difference(intersection(shoot(p, DOWN), inds), initset(p));        bl = difference(intersection(shoot(p, LEFT), inds), initset(p));        br = difference(intersection(shoot(p, RIGHT), inds), initset(p));        cu = equality(bu, intersection(bu, ofcolor(I, bg)));        cd = equality(bd, intersection(bd, ofcolor(I, bg)));        cl = equality(bl, intersection(bl, ofcolor(I, bg)));        cr = equality(br, intersection(br, ofcolor(I, bg)));        vert = either(cu, cd);        sel_u = cu;        sel_d = both(flip(cu), cd);        sel_l = both(flip(vert), cl);        sel_r = both(flip(either(vert, cl)), cr);        c = color(o);        su = both(gate, sel_u); sd = both(gate, sel_d); sl = both(gate, sel_l); sr = both(gate, sel_r);        O = branch(su, fill(O, c, top), O);        O = branch(sd, fill(O, c, bot), O);        O = branch(sl, fill(O, c, lef), O);        O = branch(sr, fill(O, c, rig), O);        O = branch(su, fill(O, c, intersection(shoot(p, double(UP)), inds)), O);        O = branch(sd, fill(O, c, intersection(shoot(p, double(DOWN)), inds)), O);        O = branch(sl, fill(O, c, intersection(shoot(p, double(LEFT)), inds)), O);        O = branch(sr, fill(O, c, intersection(shoot(p, double(RIGHT)), inds)), O);        return O, su, sd, sl, sr;;    O = I;    O, su1, sd1, sl1, sr1 = proc(O, o1, T);    O, su2, sd2, sl2, sr2 = proc(O, o2, two);;    topleft = intersection(top, lef); topright = intersection(top, rig);    botleft = intersection(bot, lef); botright = intersection(bot, rig);    btop = either(su1, su2); bbot = either(sd1, sd2);    bleft = either(sl1, sl2); bright = either(sr1, sr2);    O = branch(both(btop, bleft), fill(O, ZERO, topleft), O);    O = branch(both(btop, bright), fill(O, ZERO, topright), O);    O = branch(both(bbot, bleft), fill(O, ZERO, botleft), O);    O = branch(both(bbot, bright), fill(O, ZERO, botright), O);    return O|0.0|23.038161252923032|0.08303363303363298|0.0|23.121194885956665|
|def dsl4(I):;    # Single least-common non-background color: choose any clear direction by priority U,R,L,D; else default to nearest border;    inds = asindices(I);    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds);    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc);    bg = mostcolor(I);    # pick least-common foreground color;    objs = objects(I, T, F, T);    lc = leastcolor(I);    # if leastcolor is background, fallback to color of smallest non-bg object;    smallest = argmin(objs, size);    c = branch(equality(lc, bg), color(smallest), lc);    o = toobject(ofcolor(I, c), I);    p = first(toindices(o));    bu = difference(intersection(shoot(p, UP), inds), initset(p));    bd = difference(intersection(shoot(p, DOWN), inds), initset(p));    bl = difference(intersection(shoot(p, LEFT), inds), initset(p));    br = difference(intersection(shoot(p, RIGHT), inds), initset(p));    cu = equality(bu, intersection(bu, ofcolor(I, bg)));    cd = equality(bd, intersection(bd, ofcolor(I, bg)));    cl = equality(bl, intersection(bl, ofcolor(I, bg)));    cr = equality(br, intersection(br, ofcolor(I, bg)));    # primary selection by clear path;    sel_u = cu;    sel_r = both(flip(cu), cr);    sel_l = both(flip(either(cu, cr)), cl);    sel_d = both(flip(either(either(cu, cr), cl)), cd);    # paint selected border and step-2 ray;    O = I;    O = branch(sel_u, fill(O, c, top), O);    O = branch(sel_r, fill(O, c, rig), O);    O = branch(sel_l, fill(O, c, lef), O);    O = branch(sel_d, fill(O, c, bot), O);    O = branch(sel_u, fill(O, c, intersection(shoot(p, double(UP)), inds)), O);    O = branch(sel_r, fill(O, c, intersection(shoot(p, double(RIGHT)), inds)), O);    O = branch(sel_l, fill(O, c, intersection(shoot(p, double(LEFT)), inds)), O);    O = branch(sel_d, fill(O, c, intersection(shoot(p, double(DOWN)), inds)), O);    return O|0.0|30.960682067829296|0.2572760572760573|0.0|31.217958125105355|
|def dsl3(I):;    # Assign exactly one border per singleton: choose the closest border among those with a clear path; draw step-2 rays;    inds = asindices(I);    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds);    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc);    bg = mostcolor(I);    singles = sizefilter(objects(I, T, F, T), ONE);;    # Process first singleton (if any);    o1 = first(singles);    p1 = first(toindices(o1));    # Clear in each direction;    bu = difference(intersection(shoot(p1, UP), inds), initset(p1));    bd = difference(intersection(shoot(p1, DOWN), inds), initset(p1));    bl = difference(intersection(shoot(p1, LEFT), inds), initset(p1));    br = difference(intersection(shoot(p1, RIGHT), inds), initset(p1));    cu = equality(bu, intersection(bu, ofcolor(I, bg)));    cd = equality(bd, intersection(bd, ofcolor(I, bg)));    cl = equality(bl, intersection(bl, ofcolor(I, bg)));    cr = equality(br, intersection(br, ofcolor(I, bg)));;    # Distances to borders to break ties;    du = manhattan(o1, top); dd = manhattan(o1, bot);    dl = manhattan(o1, lef); dr = manhattan(o1, rig);;    # Choose preferred direction by clear-then-min-distance priority;    # Build booleans that emulate argmin over the clear ones;    up_best = both(cu, both( less := flip(greater(du, dl)), both(flip(greater(du, dr)), flip(greater(du, dd))) ));    # Fallback approximate: prioritize in order U, L, R, D if clear;    sel_u = cu;    sel_l = both(flip(cu), cl);    sel_r = both(flip(either(cu, cl)), cr);    sel_d = both(flip(either(either(cu, cl), cr)), cd);;    c1 = color(o1);    O = I;    O = branch(sel_u, underfill(O, c1, top), O);    O = branch(sel_l, underfill(O, c1, lef), O);    O = branch(sel_r, underfill(O, c1, rig), O);    O = branch(sel_d, underfill(O, c1, bot), O);;    O = branch(sel_u, underfill(O, c1, intersection(shoot(p1, double(UP)), inds)), O);    O = branch(sel_l, underfill(O, c1, intersection(shoot(p1, double(LEFT)), inds)), O);    O = branch(sel_r, underfill(O, c1, intersection(shoot(p1, double(RIGHT)), inds)), O);    O = branch(sel_d, underfill(O, c1, intersection(shoot(p1, double(DOWN)), inds)), O);;    # Corner zeroing when two different selected borders meet;    topleft = intersection(top, lef); topright = intersection(top, rig);    botleft = intersection(bot, lef); botright = intersection(bot, rig);    # Compute which borders were actually selected;    bt = sel_u; blf = sel_l; brg = sel_r; bb = sel_d;    O = branch(both(both(bt, blf), T), fill(O, ZERO, topleft), O);    O = branch(both(both(bt, brg), T), fill(O, ZERO, topright), O);    O = branch(both(both(bb, blf), T), fill(O, ZERO, botleft), O);    O = branch(both(both(bb, brg), T), fill(O, ZERO, botright), O);    return O|0.0|38.9399342239629|0.24537129537129532|0.0|39.18530551933419|

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
