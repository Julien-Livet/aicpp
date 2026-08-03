#ifndef AICPP_HODEL_H
#define AICPP_HODEL_H

#include <any>
#include <functional>
#include <set>
#include <utility>
#include <variant>
#include <vector>

namespace hodel
{
    typedef bool Boolean;
    typedef int8_t Integer;
    typedef std::pair<Integer, Integer> IntegerTuple;
    typedef std::variant<Integer, IntegerTuple> Numerical;
    typedef std::set<Integer> IntegerSet;
    typedef std::vector<std::vector<Integer> > Grid;
    typedef std::pair<Integer, IntegerTuple> Cell;
    typedef std::set<Cell> Object;
    typedef std::set<Object> Objects;
    typedef std::set<IntegerTuple> Indices;
    typedef std::set<Indices> IndicesSet;
    typedef std::variant<Object, Indices> Patch;
    typedef std::variant<Object, Grid> Element;
    typedef std::variant<Grid, Patch> Piece;
    typedef std::variant<std::vector<Integer>, std::vector<Element>, std::vector<Piece>, std::vector<Grid> > Tuple;

    Boolean constexpr F = false;
    Boolean constexpr T = true;

    Integer constexpr ZERO = 0;
    Integer constexpr ONE = 1;
    Integer constexpr TWO = 2;
    Integer constexpr THREE = 3;
    Integer constexpr FOUR = 4;
    Integer constexpr FIVE = 5;
    Integer constexpr SIX = 6;
    Integer constexpr SEVEN = 7;
    Integer constexpr EIGHT = 8;
    Integer constexpr NINE = 9;
    Integer constexpr TEN = 10;

    Integer constexpr NEG_ONE = -1;
    Integer constexpr NEG_TWO = -2;

    IntegerTuple constexpr DOWN = IntegerTuple{1, 0};
    IntegerTuple constexpr RIGHT = IntegerTuple{0, 1};
    IntegerTuple constexpr UP = IntegerTuple{-1, 0};
    IntegerTuple constexpr LEFT = IntegerTuple{0, -1};

    IntegerTuple constexpr ORIGIN = IntegerTuple{0, 0};
    IntegerTuple constexpr UNITY = IntegerTuple{1, 1};
    IntegerTuple constexpr NEG_UNITY = IntegerTuple{1, -1};
    IntegerTuple constexpr UP_RIGHT = IntegerTuple{1, 1};
    IntegerTuple constexpr DOWN_LEFT = IntegerTuple{1, -1};

    IntegerTuple constexpr ZERO_BY_TWO = IntegerTuple{0, 2};
    IntegerTuple constexpr TWO_BY_ZERO = IntegerTuple{2, 0};
    IntegerTuple constexpr TWO_BY_TWO = IntegerTuple{2, 2};
    IntegerTuple constexpr THREE_BY_THREE = IntegerTuple{3, 3};

    typedef Numerical Numerical1;
    typedef Numerical Numerical2;
    typedef Numerical Numerical3;

    std::any identity(std::vector<std::any> const& args); //Any(Any): identity function
    std::any add(std::vector<std::any> const& args); //Numerical1(Numerical2, Numerical3): addition
    std::any subtract(std::vector<std::any> const& args); //Numerical1(Numerical2, Numerical3): subtraction
    std::any multiply(std::vector<std::any> const& args); //Numerical1(Numerical2, Numerical3): multiplication
    std::any divide(std::vector<std::any> const& args); //Numerical1(Numerical2, Numerical3): floor division
    std::any invert(std::vector<std::any> const& args); //Numerical(Numerical): inversion with respect to addition
    std::any even(std::vector<std::any> const& args); //Boolean(Integer): evenness
    std::any double_(std::vector<std::any> const& args); //Numerical(Numerical): scaling by two
    std::any halve(std::vector<std::any> const& args); //Numerical(Numerical): scaling by one half
    std::any flip(std::vector<std::any> const& args); //Boolean(Boolean): logical not
    std::any equality(std::vector<std::any> const& args); //Any(Any): equality
    std::any contained(std::vector<std::any> const& args); //Boolean(Any, Container): element of
    std::any combine(std::vector<std::any> const& args); //Container1(Container1, Container2): union
    std::any intersection(std::vector<std::any> const& args); //FrozenSet(FrozenSet, FrozenSet): returns the intersection of two containers
    std::any difference(std::vector<std::any> const& args); //FrozenSet(FrozenSet, FrozenSet): set difference
    std::any dedupe(std::vector<std::any> const& args); //Tuple(Tuple): remove duplicates
    std::any order(std::vector<std::any> const& args); //Tuple(Container, Callable): order container by custom key
    std::any repeat(std::vector<std::any> const& args); //Tuple(Any, Integer): repetition of item within vector
    std::any greater(std::vector<std::any> const& args); //Boolean(Integer, Integer): greater
    std::any size(std::vector<std::any> const& args); //Integer(Container): cardinality
    //std::any merge(std::vector<std::any> const& args); //Container(ContainerContainer): merging
    std::any maximum(std::vector<std::any> const& args); //Integer(IntegerSet): maximum
    std::any minimum(std::vector<std::any> const& args); //Integer(IntegerSet): minimum
    std::any valmax(std::vector<std::any> const& args); //Integer(Container, Callable): maximum by custom function
    std::any valmin(std::vector<std::any> const& args); //Integer(Container, Callable): minimum by custom function
    std::any argmax(std::vector<std::any> const& args); //Any(Container, Callable): largest item by custom order
    std::any argmin(std::vector<std::any> const& args); //Any(Container, Callable): smallest item by custom order
    std::any mostcommon(std::vector<std::any> const& args); //Any(Container): most common item
    std::any leastcommon(std::vector<std::any> const& args); //Any(Container): least common item
    std::any initset(std::vector<std::any> const& args); //FrozenSet(Any): initialize container
    std::any both(std::vector<std::any> const& args); //Boolean(Boolean, Boolean): logical and
    std::any either(std::vector<std::any> const& args); //Boolean(Boolean, Boolean): logical or
    std::any increment(std::vector<std::any> const& args); //Numerical(Numerical): incrementing
    std::any decrement(std::vector<std::any> const& args); //Numerical(Numerical): decrementing
    std::any crement(std::vector<std::any> const& args); //Numerical(Numerical): incrementing positive and decrementing negative
    std::any sign(std::vector<std::any> const& args); //Numerical(Numerical): sign
    std::any positive(std::vector<std::any> const& args); //Boolean(Integer): positive
    std::any toivec(std::vector<std::any> const& args); //IntegerTuple(Integer): vector pointing vertically
    std::any tojvec(std::vector<std::any> const& args); //IntegerTuple(Integer): vector pointing horizontally
    //std::any sfilter(std::vector<std::any> const& args); //Container(Container, Callable): keep elements in container that satisfy condition
    //std::any mfilter(std::vector<std::any> const& args); //FrozenSet(Container, Callable): filter and merge
    //std::any extract(std::vector<std::any> const& args); //Any(Container, Callable): first element of container that satisfies condition
    std::any totuple(std::vector<std::any> const& args); //Tuple(FrozenSet): conversion to tuple
    std::any first(std::vector<std::any> const& args); //Any(Container): first item of container
    std::any last(std::vector<std::any> const& args); //Any(Container): last item of container
    //std::any insert(std::vector<std::any> const& args); //FrozenSet(Any, FrozenSet): insert item into container
    //std::any remove(std::vector<std::any> const& args); //Container(Any, Container): remove item from container
    //std::any other(std::vector<std::any> const& args); //Any(Container, Any): other value in the container
    std::any interval(std::vector<std::any> const& args); //Tuple(Integer, Integer, Integer): range
    std::any astuple(std::vector<std::any> const& args); //IntegerTuple(Integer, Integer): constructs a tuple
    //std::any product(std::vector<std::any> const& args); //FrozenSet(Container, Container): cartesian product
    //std::any pair(std::vector<std::any> const& args); //TupleTuple(Tuple, Tuple): zipping of two tuples
    std::any branch(std::vector<std::any> const& args); //Any(Boolean, Any, Any): if else branching
    std::any compose(std::vector<std::any> const& args); //Callable(Callable, Callable): function composition
    std::any chain(std::vector<std::any> const& args); //Callable(Callable, Callable, Callable): function composition with three functions
    std::any matcher(std::vector<std::any> const& args); //Callable(Callable, Any): construction of equality function
    std::any rbind(std::vector<std::any> const& args); //Callable(Callable, Any): fix the rightmost argument
    std::any lbind(std::vector<std::any> const& args); //Callable(Callable, Any): fix the leftmost argument
    std::any power(std::vector<std::any> const& args); //Callable(Callable, Integer): power of function
    std::any fork(std::vector<std::any> const& args); //Callable(Callable, Callable, Callable): creates a wrapper function
    std::any apply(std::vector<std::any> const& args); //Container(Callable, Container): apply function to each item in container
    //std::any rapply(std::vector<std::any> const& args); //Container(Container, Any): apply each function in container to value
    //std::any mapply(std::vector<std::any> const& args); //FrozenSet(Callable, ContainerContainer): apply and merge
    //std::any papply(std::vector<std::any> const& args); //Tuple(Callable, Tuple, Tuple): apply function on two vectors
    //std::any mpapply(std::vector<std::any> const& args); //Tuple(Callable, Tuple, Tuple): apply function on two vectors and merge
    //std::any prapply(std::vector<std::any> const& args); //FrozenSet(Callable, Container, Container): apply function on cartesian product
    std::any mostcolor(std::vector<std::any> const& args); //Integer(Element): most common color
    std::any leastcolor(std::vector<std::any> const& args); //Integer(Element): least common color
    std::any height(std::vector<std::any> const& args); //Integer(Piece): height of grid or patch
    std::any width(std::vector<std::any> const& args); //Integer(Piece): width of grid or patch
    std::any shape(std::vector<std::any> const& args); //IntegerTuple(Piece): height and width of grid or patch 
    std::any portrait(std::vector<std::any> const& args); //Boolean(Piece): whether height is greater than width
    std::any colorcount(std::vector<std::any> const& args); //Integer(Element, Integer): number of cells with color
    std::any colorfilter(std::vector<std::any> const& args); //Objects(Objects, Integer): filter objects by color
    //std::any sizefilter(std::vector<std::any> const& args); //FrozenSet(Container, Integer): filter items by size
    std::any asindices(std::vector<std::any> const& args); //Indices(Grid): indices of all grid cells
    std::any ofcolor(std::vector<std::any> const& args); //Indices(Grid, Integer): indices of all grid cells with value
    std::any ulcorner(std::vector<std::any> const& args); // IntegerTuple(Patch): index of upper left corner
    std::any urcorner(std::vector<std::any> const& args); // IntegerTuple(Patch): index of upper right corner
    std::any llcorner(std::vector<std::any> const& args); // IntegerTuple(Patch): index of lower left corner
    std::any lrcorner(std::vector<std::any> const& args); // IntegerTuple(Patch): index of lower right corner
    std::any crop(std::vector<std::any> const& args); //Grid(Grid, IntegerTuple, IntegerTuple): subgrid specified by start and dimension
    std::any toindices(std::vector<std::any> const& args); //Indices(Patch): indices of object cells
    std::any recolor(std::vector<std::any> const& args); //Object(Integer, Patch): recolor patch
    std::any shift(std::vector<std::any> const& args); //Patch(Patch, IntegerTuple): shift patch
    std::any normalize(std::vector<std::any> const& args); //Patch(Patch): moves upper left corner to origin
    std::any dneighbors(std::vector<std::any> const& args); //Indices(IntegerTuple): directly adjacent indices
    std::any ineighbors(std::vector<std::any> const& args); //Indices(IntegerTuple): diagonally adjacent indices
    std::any neighbors(std::vector<std::any> const& args); //Indices(IntegerTuple): adjacent indices
    std::any objects(std::vector<std::any> const& args); //Objects(Grid, Boolean, Boolean, Boolean): objects occurring on the grid
    std::any partition(std::vector<std::any> const& args); //Objects(Grid): each cell with the same value part of the same object
    std::any fgpartition(std::vector<std::any> const& args); //Objects(Grid): each cell with the same value part of the same object without background
    std::any uppermost(std::vector<std::any> const& args); //Integer(Patch): row index of uppermost occupied cell
    std::any lowermost(std::vector<std::any> const& args); //Integer(Patch): row index of lowermost occupied cell
    std::any leftmost(std::vector<std::any> const& args); //Integer(Patch): column index of leftmost occupied cell
    std::any rightmost(std::vector<std::any> const& args); //Integer(Patch): column index of rightmost occupied cell
    std::any square(std::vector<std::any> const& args); //Boolean(Piece): whether the piece forms a square
    std::any vline(std::vector<std::any> const& args); //Boolean(Patch): whether the piece forms a vertical line
    std::any hline(std::vector<std::any> const& args); //Boolean(Patch): whether the piece forms a horizontal line
    std::any hmatching(std::vector<std::any> const& args); //Boolean(Patch, Patch): whether there exists a row for which both patches have cells
    std::any vmatching(std::vector<std::any> const& args); //Boolean(Patch, Patch): whether there exists a column for which both patches have cells
    std::any manhattan(std::vector<std::any> const& args); //Integer(Patch, Patch):  closest manhattan distance between two patches
    std::any adjacent(std::vector<std::any> const& args); //Boolean(Patch, Patch): whether two patches are adjacent
    std::any bordering(std::vector<std::any> const& args); //Boolean(Patch, Grid): whether a patch is adjacent to a grid border
    std::any centerofmass(std::vector<std::any> const& args); //IntegerTuple(Patch): center of mass
    std::any palette(std::vector<std::any> const& args); //IntegerSet(Element):  colors occurring in object or grid
    std::any numcolors(std::vector<std::any> const& args); //Integer(Element): number of colors occurring in object or grid
    std::any color(std::vector<std::any> const& args); //Integer(Object): color of object
    std::any toobject(std::vector<std::any> const& args); //Object(Patch, Grid): object from patch and grid
    std::any asobject(std::vector<std::any> const& args); //Object(Grid): conversion of grid to object
    std::any rot90(std::vector<std::any> const& args); //Grid(Grid): quarter clockwise rotation
    std::any rot180(std::vector<std::any> const& args); //Grid(Grid): half rotation
    std::any rot270(std::vector<std::any> const& args); //Grid(Grid): quarter anticlockwise rotation
    std::any hmirror(std::vector<std::any> const& args); //Piece(Piece): mirroring along horizontal
    std::any vmirror(std::vector<std::any> const& args); //Piece(Piece): mirroring along vertical
    std::any dmirror(std::vector<std::any> const& args); //Piece(Piece): mirroring along diagonal
    std::any cmirror(std::vector<std::any> const& args); //Piece(Piece): mirroring along counterdiagonal
    std::any fill(std::vector<std::any> const& args); //Grid(Grid, Integer, Patch): fill value at indices
    std::any paint(std::vector<std::any> const& args); //Grid(Grid, Object): paint object to grid
    std::any underfill(std::vector<std::any> const& args); //Grid(Grid, Integer, Patch): fill value at indices that are background
    std::any underpaint(std::vector<std::any> const& args); //Grid(Grid, Object): paint object to grid where there is background
    std::any hupscale(std::vector<std::any> const& args); //Grid(Grid, Integer): upscale grid horizontally
    std::any vupscale(std::vector<std::any> const& args); //Grid(Grid, Integer): upscale grid vertically
    std::any upscale(std::vector<std::any> const& args); //Element(Element, Integer): upscale object or grid
    std::any downscale(std::vector<std::any> const& args); //Grid(Grid, Integer): downscale object or grid
    std::any hconcat(std::vector<std::any> const& args); //Grid(Grid, Grid): concatenate two grids horizontally
    std::any vconcat(std::vector<std::any> const& args); //Grid(Grid, Grid): concatenate two grids vertically
    std::any subgrid(std::vector<std::any> const& args); //Grid(Patch, Grid): smallest subgrid containing object
    std::any hsplit(std::vector<std::any> const& args); //Tuple(Grid, Integer): split grid horizontally
    std::any vsplit(std::vector<std::any> const& args); //Tuple(Grid, Integer): split grid vertically
    std::any cellwise(std::vector<std::any> const& args); //Grid(Grid, Grid, Integer): cellwise match of two grids
    std::any replace(std::vector<std::any> const& args); //Grid(Grid, Integer, Integer): color substitution
    std::any switch_(std::vector<std::any> const& args); //Grid(Grid, Integer, Integer): color switching
    std::any center(std::vector<std::any> const& args); //IntegerTuple(Patch): center of the patch
    std::any position(std::vector<std::any> const& args); //IntegerTuple(Patch, Patch): relative position between two patches
    std::any index(std::vector<std::any> const& args); //Integer(Grid, IntegerTuple): color at location
    std::any canvas(std::vector<std::any> const& args); //Grid(Integer, IntegerTuple): grid construction
    std::any corners(std::vector<std::any> const& args); //Indices(Patch): indices of corners
    std::any connect(std::vector<std::any> const& args); //Indices(IntegerTuple, IntegerTuple): line between two points
    std::any cover(std::vector<std::any> const& args); //Grid(Grid, Patch): remove object from grid
    std::any trim(std::vector<std::any> const& args); //Grid(Grid): trim border of grid
    std::any move(std::vector<std::any> const& args); //Grid(Grid, Object, IntegerTuple): move object on grid
    std::any tophalf(std::vector<std::any> const& args); //Grid(Grid): upper half of grid
    std::any bottomhalf(std::vector<std::any> const& args); //Grid(Grid): lower half of grid
    std::any lefthalf(std::vector<std::any> const& args); //Grid(Grid): left half of grid
    std::any righthalf(std::vector<std::any> const& args); //Grid(Grid): right half of grid
    std::any vfrontier(std::vector<std::any> const& args); //Indices(IntegerTuple): vertical frontier
    std::any hfrontier(std::vector<std::any> const& args); //Indices(IntegerTuple): horizontal frontier
    std::any backdrop(std::vector<std::any> const& args); //Indices(Patch): indices in bounding box of patch
    std::any delta(std::vector<std::any> const& args); //Indices(Patch): indices in bounding box but not part of patch
    std::any gravitate(std::vector<std::any> const& args); //IntegerTuple(Patch, Patch): direction to move source until adjacent to destination
    std::any inbox(std::vector<std::any> const& args); //Indices(Patch): inbox for patch
    std::any outbox(std::vector<std::any> const& args); //Indices(Patch): outbox for patch
    std::any box(std::vector<std::any> const& args); //Indices(Patch): outline of patch
    std::any shoot(std::vector<std::any> const& args); //Indices(IntegerTuple, IntegerTuple): line from starting point and direction
    std::any occurrences(std::vector<std::any> const& args); //Indices(Grid, Object): locations of occurrences of object in grid
    std::any frontiers(std::vector<std::any> const& args); //Objects(Grid): set of frontiers
    std::any compress(std::vector<std::any> const& args); //Grid(Grid): removes frontiers from grid
    std::any hperiod(std::vector<std::any> const& args); //Integer(Object): horizontal periodicity
    std::any vperiod(std::vector<std::any> const& args); //Integer(Object): vertical periodicity
}

#endif // AICPP_HODEL_H
