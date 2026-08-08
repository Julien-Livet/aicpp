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
    typedef int8_t IntegerType;
    typedef std::pair<IntegerType, IntegerType> IntegerTuple;
    typedef std::variant<IntegerType, IntegerTuple> Numerical;
    typedef std::set<IntegerType> IntegerSet;
    typedef std::vector<std::vector<IntegerType> > Grid;
    typedef std::pair<IntegerType, IntegerTuple> Cell;
    typedef std::set<Cell> ObjectType;
    typedef std::set<ObjectType> Objects;
    typedef std::set<IntegerTuple> IndicesType;
    typedef std::set<IndicesType> IndicesSet;
    typedef std::variant<ObjectType, IndicesType> Patch;
    typedef std::variant<ObjectType, Grid> Element;
    typedef std::variant<Grid, Patch> Piece;

    Boolean constexpr F = false;
    Boolean constexpr T = true;

    IntegerType constexpr ZERO = 0;
    IntegerType constexpr ONE = 1;
    IntegerType constexpr TWO = 2;
    IntegerType constexpr THREE = 3;
    IntegerType constexpr FOUR = 4;
    IntegerType constexpr FIVE = 5;
    IntegerType constexpr SIX = 6;
    IntegerType constexpr SEVEN = 7;
    IntegerType constexpr EIGHT = 8;
    IntegerType constexpr NINE = 9;
    IntegerType constexpr TEN = 10;

    IntegerType constexpr NEG_ONE = -1;
    IntegerType constexpr NEG_TWO = -2;

    IntegerTuple constexpr DOWN = IntegerTuple{-1, 0};
    IntegerTuple constexpr RIGHT = IntegerTuple{0, 1};
    IntegerTuple constexpr UP = IntegerTuple{1, 0};
    IntegerTuple constexpr LEFT = IntegerTuple{0, -1};

    IntegerTuple constexpr ORIGIN = IntegerTuple{0, 0};
    IntegerTuple constexpr UNITY = IntegerTuple{1, 1};
    IntegerTuple constexpr NEG_UNITY = IntegerTuple{-1, -1};
    IntegerTuple constexpr UP_RIGHT = IntegerTuple{-1, 1};
    IntegerTuple constexpr DOWN_LEFT = IntegerTuple{1, -1};

    IntegerTuple constexpr ZERO_BY_TWO = IntegerTuple{0, 2};
    IntegerTuple constexpr TWO_BY_ZERO = IntegerTuple{2, 0};
    IntegerTuple constexpr TWO_BY_TWO = IntegerTuple{2, 2};
    IntegerTuple constexpr THREE_BY_THREE = IntegerTuple{3, 3};

    typedef Numerical Num1;
    typedef Numerical Num2;
    typedef Numerical Num3;

    typedef std::function<std::any(std::vector<std::any> const&)> Callable;
    typedef std::tuple<Boolean, IntegerType, IntegerTuple, IntegerSet, Grid, Cell, ObjectType, Objects, IndicesType, IndicesSet, Callable, std::vector<IntegerType>, std::vector<Grid>, std::vector<Boolean>, std::vector<ObjectType>, std::vector<Objects>, std::vector<IndicesType>, std::vector<IndicesSet>, std::vector<Callable> > AnyIdentity;
    typedef std::tuple<Boolean, IntegerType, IntegerTuple, IntegerSet, Grid, Cell, ObjectType, Objects, IndicesType, IndicesSet, std::vector<Grid>, std::vector<Boolean>, std::vector<Objects> > AnyEquality;
    typedef std::tuple<Boolean, IntegerType, IntegerTuple, std::vector<IntegerType>, Grid, Objects, Callable> AnyVector1;
    typedef std::tuple<Boolean, IntegerType, IntegerTuple, std::vector<IntegerType>, Grid, Objects> AnyVector2;
    typedef std::tuple<IntegerType, Cell, ObjectType, IntegerTuple, IndicesType> AnySet1;
    typedef std::vector<IntegerType> IntegerVector;

    //AnyIdentity identity(AnyIdentity)
    std::any identity(std::vector<std::any> const& args); //identity function
    //Num1 add(Num2, Num3)
    std::any add(std::vector<std::any> const& args); //addition
    //Num1 subtract(Num2, Num3)
    std::any subtract(std::vector<std::any> const& args); //subtraction
    //Num1 multiply(Num2, Num3)
    std::any multiply(std::vector<std::any> const& args); //multiplication
    //Num1 divide(Num2, Num3)
    std::any divide(std::vector<std::any> const& args); //floor division
    //Numerical invert(Numerical)
    std::any invert(std::vector<std::any> const& args); //inversion with respect to addition
    //Boolean even(Numerical)
    std::any even(std::vector<std::any> const& args); //evenness
    //Numerical double_(Numerical)
    std::any double_(std::vector<std::any> const& args); //scaling by two
    //Numerical halve(Numerical)
    std::any halve(std::vector<std::any> const& args); //scaling by one half
    //Boolean flip(Boolean)
    std::any flip(std::vector<std::any> const& args); //logical not
    //Boolean equality(AnyEquality, AnyEquality)
    std::any equality(std::vector<std::any> const& args); //equality
    //Boolean contained(AnyVector, std::vector<AnyVector>)
    //Boolean contained(AnySet1, std::set<AnySet1>)
    std::any contained(std::vector<std::any> const& args); //element of
    std::any combine(std::vector<std::any> const& args); //Container1(Container1, Container2): union
    //std::vector<AnyVector1> intersection(std::vector<AnyVector1>, std::vector<AnyVector1>)
    //std::set<AnySet1> intersection(std::set<AnySet1>, std::set<AnySet1>)
    std::any intersection(std::vector<std::any> const& args); //returns the intersection of two containers
    //std::vector<AnyVector1> difference(std::vector<AnyVector1>, std::vector<AnyVector1>)
    //std::set<AnySet1> difference(std::set<AnySet1>, std::set<AnySet1>)
    std::any difference(std::vector<std::any> const& args); //set difference
    //std::vector<AnyVector1> dedupe(std::vector<AnyVector1>, std::vector<AnyVector1>)
    std::any dedupe(std::vector<std::any> const& args); //remove duplicates
    //std::vector<AnyVector1> order(std::vector<AnyVector1>, Callable)
    std::any order(std::vector<std::any> const& args); //order container by custom key
    //std::vector<AnyVector1> repeat(AnyVector1, IntegerType)
    std::any repeat(std::vector<std::any> const& args); //repetition of item within vector
    //Boolean greater(IntegerType, IntegerType)
    std::any greater(std::vector<std::any> const& args); //greater
    //IntegerType size(std::vector<AnyVector1>)
    //IntegerType size(std::set<AnySet1>)
    std::any size(std::vector<std::any> const& args); //cardinality
    std::any merge(std::vector<std::any> const& args); //Container(ContainerContainer): merging
    //IntegerType maximum(std::vector<AnyVector1>)
    //IntegerType maximum(std::set<AnySet1>)
    std::any maximum(std::vector<std::any> const& args); //maximum
    //IntegerType minimum(std::vector<AnyVector1>)
    //IntegerType minimum(std::set<AnySet1>)
    std::any minimum(std::vector<std::any> const& args); //minimum
    //IntegerType valmax(IntegerVector, Callable)
    //IntegerType valmax(IntegerSet, Callable)
    std::any valmax(std::vector<std::any> const& args); //maximum by custom function
    //IntegerType valmin(IntegerVector, Callable)
    //IntegerType valmin(IntegerSet, Callable)
    std::any valmin(std::vector<std::any> const& args); //minimum by custom function
    //AnyVector1 argmax(std::vector<AnyVector1>, Callable)
    //AnySet1 argmax(std::set<AnySet1>, Callable)
    std::any argmax(std::vector<std::any> const& args); //largest item by custom order
    //AnyVector1 argmin(std::vector<AnyVector1>, Callable)
    //AnySet1 argmin(std::set<AnySet1>, Callable)
    std::any argmin(std::vector<std::any> const& args); //smallest item by custom order
    //AnyVector1 mostcommon(std::vector<AnyVector1>)
    std::any mostcommon(std::vector<std::any> const& args); //most common item
    //AnyVector1 leastcommon(std::vector<AnyVector1>)
    std::any leastcommon(std::vector<std::any> const& args); //least common item
    //std::vector<AnyVector1> initset(AnyVector1)
    //std::set<AnySet1> initset(AnySet1)
    std::any initset(std::vector<std::any> const& args); //initialize container
    //Boolean both(Boolean, Boolean)
    std::any both(std::vector<std::any> const& args); //logical and
    //Boolean either(Boolean, Boolean)
    std::any either(std::vector<std::any> const& args); //logical or
    //Numerical increment(Numerical)
    std::any increment(std::vector<std::any> const& args); //incrementing
    //Numerical decrement(Numerical)
    std::any decrement(std::vector<std::any> const& args); //decrementing
    //Numerical crement(Numerical)
    std::any crement(std::vector<std::any> const& args); //incrementing positive and decrementing negative
    //Numerical sign(Numerical)
    std::any sign(std::vector<std::any> const& args); //sign
    //Boolean positive(IntegerType)
    std::any positive(std::vector<std::any> const& args); //positive
    //IntegerTuple toivec(IntegerType)
    std::any toivec(std::vector<std::any> const& args); //vector pointing vertically
    //IntegerTuple tojvec(IntegerType)
    std::any tojvec(std::vector<std::any> const& args); //vector pointing horizontally
    //AnyVector1 sfilter(std::vector<AnyVector1>, Callable)
    //AnySet1 sfilter(std::set<AnySet1>, Callable)
    std::any sfilter(std::vector<std::any> const& args); //keep elements in container that satisfy condition
    std::any mfilter(std::vector<std::any> const& args); //FrozenSet(Container, Callable): filter and merge
    //AnyVector1 extract(std::vector<AnyVector1>, Callable)
    //AnySet1 extract(std::set<AnySet1>, Callable)
    std::any extract(std::vector<std::any> const& args); //first element of container that satisfies condition
    //std::vector<AnySet1> totuple(std::set<AnySet1>)
    std::any totuple(std::vector<std::any> const& args); //Container(FrozenSet): conversion to tuple
    //AnyVector1 first(std::vector<AnyVector1>)
    //AnySet1 first(std::vector<AnySet1>)
    std::any first(std::vector<std::any> const& args); //first item of container
    //AnyVector1 last(std::vector<AnyVector1>)
    //AnySet1 last(std::vector<AnySet1>)
    std::any last(std::vector<std::any> const& args); //last item of container
    //std::vector<AnyVector1> insert(AnyVector1, std::vector<AnyVector1>)
    //std::set<AnySet1> insert(AnySet1, std::set<AnySet1>)
    std::any insert(std::vector<std::any> const& args); //insert item into container
    //std::vector<AnyVector2> remove(AnyVector2, std::vector<AnyVector2>)
    //std::set<AnySet1> remove(AnySet1, std::set<AnySet1>)
    std::any remove(std::vector<std::any> const& args); //remove item from container
    //AnyVector1 other(std::vector<AnyVector1>, AnyVector1)
    //AnySet1 other(std::set<AnySet1>, AnySet1)
    std::any other(std::vector<std::any> const& args); //other value in the container
    //IntegerVector interval(IntegerType, IntegerType, IntegerType)
    std::any interval(std::vector<std::any> const& args); //range
    //IntegerTuple astuple(IntegerType, IntegerType)
    std::any astuple(std::vector<std::any> const& args); //constructs a tuple
    std::any product(std::vector<std::any> const& args); //Container1(Container2, Container3): cartesian product
    std::any pair(std::vector<std::any> const& args); //ContainerContainer(Container, Container): zipping of two tuples
    //AnyIdentity branch(Boolean, AnyIdentity, AnyIdentity)
    std::any branch(std::vector<std::any> const& args); //if else branching
    //Callable compose(Callable, Callable)
    std::any compose(std::vector<std::any> const& args); //function composition
    //Callable chain(Callable, Callable, Callable)
    std::any chain(std::vector<std::any> const& args); //function composition with three functions
    //Callable matcher(Callable, AnyIdentity)
    std::any matcher(std::vector<std::any> const& args); //construction of equality function
    //Callable rbind(Callable, AnyIdentity)
    std::any rbind(std::vector<std::any> const& args); //fix the rightmost argument
    //Callable lbind(Callable, AnyIdentity)
    std::any lbind(std::vector<std::any> const& args); //fix the leftmost argument
    //Callable power(Callable, IntegerType)
    std::any power(std::vector<std::any> const& args); //power of function
    //Callable fork(Callable, Callable, Callable)
    std::any fork(std::vector<std::any> const& args); //creates a wrapper function
    std::any apply(std::vector<std::any> const& args); //Container(Callable, Container): apply function to each item in container
    std::any rapply(std::vector<std::any> const& args); //Container(Container, Any): apply each function in container to value
    std::any mapply(std::vector<std::any> const& args); //Container(Callable, ContainerContainer): apply and merge
    std::any papply(std::vector<std::any> const& args); //Container1(Callable, Container2, Container3): apply function on two vectors
    std::any mpapply(std::vector<std::any> const& args); //Container1(Callable, Container2, Container2): apply function on two vectors and merge
    std::any prapply(std::vector<std::any> const& args); //Container1(Callable, Container2, Container2): apply function on cartesian product
    //IntegerType mostcolor(Element)
    std::any mostcolor(std::vector<std::any> const& args); //most common color
    //IntegerType leastcolor(Element)
    std::any leastcolor(std::vector<std::any> const& args); //least common color
    //IntegerType height(Piece)
    std::any height(std::vector<std::any> const& args); //height of grid or patch
    //IntegerType width(Piece)
    std::any width(std::vector<std::any> const& args); //width of grid or patch
    //IntegerTuple shape(Piece)
    std::any shape(std::vector<std::any> const& args); //height and width of grid or patch 
    //Boolean portrait(Piece)
    std::any portrait(std::vector<std::any> const& args); //whether height is greater than width
    //IntegerType colorcount(Element, IntegerType)
    std::any colorcount(std::vector<std::any> const& args); //number of cells with color
    //Objects colorfilter(Objects, IntegerType)
    std::any colorfilter(std::vector<std::any> const& args); //filter Objects by color
    std::any sizefilter(std::vector<std::any> const& args); //ContainerContainer(ContainerContainer, IntegerType): filter items by size
    //IndicesType asindices(Grid)
    std::any asindices(std::vector<std::any> const& args); //IndicesType of all grid cells
    //IndicesType ofcolor(Grid, IntegerType)
    std::any ofcolor(std::vector<std::any> const& args); //IndicesType of all grid cells with value
    //IntegerTuple ulcorner(Patch)
    std::any ulcorner(std::vector<std::any> const& args); //index of upper left corner
    //IntegerTuple urcorner(Patch)
    std::any urcorner(std::vector<std::any> const& args); //index of upper right corner
    //IntegerTuple llcorner(Patch)
    std::any llcorner(std::vector<std::any> const& args); //index of lower left corner
    //IntegerTuple lrcorner(Patch)
    std::any lrcorner(std::vector<std::any> const& args); //index of lower right corner
    //Grid crop(Grid, IntegerTuple, IntegerTuple)
    std::any crop(std::vector<std::any> const& args); //subgrid specified by start and dimension
    //IndicesType toindices(Patch)
    std::any toindices(std::vector<std::any> const& args); //IndicesType of ObjectType cells
    //ObjectType recolor(IntegerType, Patch)
    std::any recolor(std::vector<std::any> const& args); //recolor patch
    //Patch shift(Patch, IntegerTuple)
    std::any shift(std::vector<std::any> const& args); //shift patch
    //Patch normalize(Patch)
    std::any normalize(std::vector<std::any> const& args); //moves upper left corner to origin
    //IndicesType dneighbors(IntegerTuple)
    std::any dneighbors(std::vector<std::any> const& args); //directly adjacent IndicesType
    //IndicesType ineighbors(IntegerTuple)
    std::any ineighbors(std::vector<std::any> const& args); //diagonally adjacent IndicesType
    //IndicesType neighbors(IntegerTuple)
    std::any neighbors(std::vector<std::any> const& args); //adjacent IndicesType
    //Objects objects(Grid, Boolean, Boolean, Boolean)
    std::any objects(std::vector<std::any> const& args); //Objects occurring on the grid
    //Objects partition(Grid)
    std::any partition(std::vector<std::any> const& args); //each cell with the same value part of the same ObjectType
    //Objects fgpartition(Grid)
    std::any fgpartition(std::vector<std::any> const& args); //each cell with the same value part of the same ObjectType without background
    //IntegerType uppermost(Patch)
    std::any uppermost(std::vector<std::any> const& args); //row index of uppermost occupied cell
    //IntegerType lowermost(Patch)
    std::any lowermost(std::vector<std::any> const& args); //row index of lowermost occupied cell
    //IntegerType leftmost(Patch)
    std::any leftmost(std::vector<std::any> const& args); //column index of leftmost occupied cell
    //IntegerType rightmost(Patch)
    std::any rightmost(std::vector<std::any> const& args); //column index of rightmost occupied cell
    //Boolean square(Piece)
    std::any square(std::vector<std::any> const& args); //whether the piece forms a square
    //Boolean vline(Patch)
    std::any vline(std::vector<std::any> const& args); //whether the piece forms a vertical line
    //Boolean hline(Patch)
    std::any hline(std::vector<std::any> const& args); //whether the piece forms a horizontal line
    //Boolean hmatching(Patch, Patch)
    std::any hmatching(std::vector<std::any> const& args); //whether there exists a row for which both patches have cells
    //Boolean vmatching(Patch, Patch)
    std::any vmatching(std::vector<std::any> const& args); //whether there exists a column for which both patches have cells
    //IntegerType manhattan(Patch, Patch)
    std::any manhattan(std::vector<std::any> const& args); //closest manhattan distance between two patches
    //Boolean adjacent(Patch, Patch)
    std::any adjacent(std::vector<std::any> const& args); //whether two patches are adjacent
    //Boolean bordering(Patch, Grid)
    std::any bordering(std::vector<std::any> const& args); //whether a patch is adjacent to a grid border
    //IntegerTuple centerofmass(Patch)
    std::any centerofmass(std::vector<std::any> const& args); //center of mass
    //IntegerSet palette(Element)
    std::any palette(std::vector<std::any> const& args); //colors occurring in ObjectType or grid
    //IntegerType numcolors(Element)
    std::any numcolors(std::vector<std::any> const& args); //number of colors occurring in ObjectType or grid
    //IntegerType color(ObjectType)
    std::any color(std::vector<std::any> const& args); //color of ObjectType
    //ObjectType toobject(Patch, Grid)
    std::any toobject(std::vector<std::any> const& args); //ObjectType from patch and grid
    //ObjectType asobject(Grid)
    std::any asobject(std::vector<std::any> const& args); //conversion of grid to ObjectType
    //Grid rot90(Grid)
    std::any rot90(std::vector<std::any> const& args); //quarter clockwise rotation
    //Grid rot180(Grid)
    std::any rot180(std::vector<std::any> const& args); //half rotation
    //Grid rot270(Grid)
    std::any rot270(std::vector<std::any> const& args); //quarter anticlockwise rotation
    //Piece hmirror(Piece)
    std::any hmirror(std::vector<std::any> const& args); //mirroring along horizontal
    //Piece vmirror(Piece)
    std::any vmirror(std::vector<std::any> const& args); //mirroring along vertical
    //Piece dmirror(Piece)
    std::any dmirror(std::vector<std::any> const& args); //mirroring along diagonal
    //Piece cmirror(Piece)
    std::any cmirror(std::vector<std::any> const& args); //mirroring along counterdiagonal
    //Grid fill(Grid, IntegerType, Patch)
    std::any fill(std::vector<std::any> const& args); //fill value at IndicesType
    //Grid paint(Grid, ObjectType)
    std::any paint(std::vector<std::any> const& args); //paint ObjectType to grid
    //Grid underfill(Grid, IntegerType, Patch)
    std::any underfill(std::vector<std::any> const& args); //fill value at IndicesType that are background
    //Grid underpaint(Grid, ObjectType)
    std::any underpaint(std::vector<std::any> const& args); //paint ObjectType to grid where there is background
    //Grid hupscale(Grid, IntegerType)
    std::any hupscale(std::vector<std::any> const& args); //upscale grid horizontally
    //Grid vupscale(Grid, IntegerType)
    std::any vupscale(std::vector<std::any> const& args); //upscale grid vertically
    //Element downscale(Element, IntegerType)
    std::any upscale(std::vector<std::any> const& args); //upscale ObjectType or grid
    //Grid downscale(Grid, IntegerType)
    std::any downscale(std::vector<std::any> const& args); //downscale ObjectType or grid
    //Grid hconcat(Grid, Grid)
    std::any hconcat(std::vector<std::any> const& args); //concatenate two grids horizontally
    //Grid vconcat(Grid, Grid)
    std::any vconcat(std::vector<std::any> const& args); //concatenate two grids vertically
    //Grid subgrid(Patch, Grid)
    std::any subgrid(std::vector<std::any> const& args); //smallest subgrid containing ObjectType
    std::any hsplit(std::vector<std::any> const& args); //Container(Grid, IntegerType): split grid horizontally
    std::any vsplit(std::vector<std::any> const& args); //Container(Grid, IntegerType): split grid vertically
    //Grid cellwise(Grid, Grid, IntegerType)
    std::any cellwise(std::vector<std::any> const& args); //Grid(Grid, Grid, IntegerType): cellwise match of two grids
    //Grid replace(Grid, IntegerType, IntegerType)
    std::any replace(std::vector<std::any> const& args); //color substitution
    //Grid switch_(Grid, IntegerType, IntegerType)
    std::any switch_(std::vector<std::any> const& args); //color switching
    //IntegerTuple center(Patch)
    std::any center(std::vector<std::any> const& args); //center of the patch
    //IntegerTuple position(Patch, Patch)
    std::any position(std::vector<std::any> const& args); //relative position between two patches
    //IntegerType index(Grid, IntegerTuple)
    std::any index(std::vector<std::any> const& args); //color at location
    //Grid canvas(IntegerTuple, IntegerTuple)
    std::any canvas(std::vector<std::any> const& args); //grid construction
    //IndicesType corners(Patch)
    std::any corners(std::vector<std::any> const& args); //IndicesType of corners
    //IndicesType connect(IntegerTuple, IntegerTuple)
    std::any connect(std::vector<std::any> const& args); //line between two points
    //Grid cover(Grid, Patch)
    std::any cover(std::vector<std::any> const& args); //remove ObjectType from grid
    //Grid trim(Grid)
    std::any trim(std::vector<std::any> const& args); //trim border of grid
    //Grid move(Grid, ObjectType, IntegerTuple)
    std::any move(std::vector<std::any> const& args); //move ObjectType on grid
    //Grid tophalf(Grid)
    std::any tophalf(std::vector<std::any> const& args); //upper half of grid
    //Grid bottomhalf(Grid)
    std::any bottomhalf(std::vector<std::any> const& args); //lower half of grid
    //Grid lefthalf(Grid)
    std::any lefthalf(std::vector<std::any> const& args); //left half of grid
    //Grid righthalf(Grid)
    std::any righthalf(std::vector<std::any> const& args); //right half of grid
    //IndicesType vfrontier(IntegerTuple)
    std::any vfrontier(std::vector<std::any> const& args); //vertical frontier
    //IndicesType hfrontier(IntegerTuple)
    std::any hfrontier(std::vector<std::any> const& args); //horizontal frontier
    //IndicesType backdrop(Patch)
    std::any backdrop(std::vector<std::any> const& args); //IndicesType in bounding box of patch
    //IndicesType delta(Patch)
    std::any delta(std::vector<std::any> const& args); //IndicesType in bounding box but not part of patch
    //IntegerTuple gravitate(Patch, Patch)
    std::any gravitate(std::vector<std::any> const& args); //direction to move source until adjacent to destination
    //IndicesType inbox(Patch)
    std::any inbox(std::vector<std::any> const& args); //inbox for patch
    //IndicesType outbox(Patch)
    std::any outbox(std::vector<std::any> const& args); //outbox for patch
    //IndicesType box(Patch)
    std::any box(std::vector<std::any> const& args); //outline of patch
    //IndicesType shoot(IntegerTuple, IntegerTuple)
    std::any shoot(std::vector<std::any> const& args); //line from starting point and direction
    //IndicesType occurrences(Grid, ObjectType)
    std::any occurrences(std::vector<std::any> const& args); //locations of occurrences of ObjectType in grid
    //Objects frontiers(Grid)
    std::any frontiers(std::vector<std::any> const& args); //set of frontiers
    //Grid compress(Grid)
    std::any compress(std::vector<std::any> const& args); //removes frontiers from grid
    //IntegerType hperiod(ObjectType)
    std::any hperiod(std::vector<std::any> const& args); //horizontal periodicity
    //IntegerType vperiod(ObjectType)
    std::any vperiod(std::vector<std::any> const& args); //vertical periodicity
}

#endif // AICPP_HODEL_H
