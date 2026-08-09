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
    typedef int16_t IntegerType;
    typedef std::pair<IntegerType, IntegerType> IntegerTuple;
    typedef std::variant<IntegerType, IntegerTuple> Numerical;
    typedef std::set<IntegerType> IntegerSet;
    typedef std::vector<std::vector<IntegerType> > GridType;
    typedef std::pair<IntegerType, IntegerTuple> Cell;
    typedef std::set<Cell> ObjectType;
    typedef std::set<ObjectType> Objects;
    typedef std::set<IntegerTuple> IndicesType;
    typedef std::set<IndicesType> IndicesSet;
    typedef std::variant<ObjectType, IndicesType> Patch;
    typedef std::variant<ObjectType, GridType> Element;
    typedef std::variant<GridType, Patch> Piece;

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
    typedef std::tuple<Boolean, IntegerType, IntegerTuple, IntegerSet, GridType, Cell, ObjectType, Objects, IndicesType, IndicesSet, Callable, std::vector<IntegerType>, std::vector<GridType>, std::vector<Boolean>, std::vector<ObjectType>, std::vector<Objects>, std::vector<IndicesType>, std::vector<IndicesSet>, std::vector<Callable> > AnyIdentity;
    typedef std::tuple<Boolean, IntegerType, IntegerTuple, IntegerSet, GridType, Cell, ObjectType, Objects, IndicesType, IndicesSet, std::vector<GridType>, std::vector<Boolean>, std::vector<Objects> > AnyEquality;
    typedef std::tuple<Boolean, IntegerType, IntegerTuple, std::vector<IntegerType>, GridType, ObjectType, IndicesType, Objects, Callable> AnyVector1;
    typedef std::tuple<Boolean, IntegerType, IntegerTuple, std::vector<IntegerType>, GridType, Objects> AnyVector2;
    typedef std::tuple<IntegerType, Cell, ObjectType, IntegerTuple, IndicesType> AnySet1;
    typedef std::vector<IntegerType> IntegerVector;
    typedef std::vector<GridType> GridVector;
    typedef std::tuple<IntegerVector, GridType> AnyVector3;
    typedef std::tuple<ObjectType, IndicesType> AnySet2;
    
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
    //IntegerTuple combine(IntegerType, IntegerType)
    //IntegerSet combine(IntegerSet, IntegerSet)
    //std::vector<IntegerType> combine(std::vector<IntegerType>, IntegerSet)
    //IntegerSet combine(IntegerSet, std::vector<IntegerType>)
    //std::vector<ObjectType> combine(ObjectType, ObjectType)
    //std::vector<Objects> combine(Objects, Objects)
    //IndicesType combine(IndicesType, IndicesType)
    //std::vector<IntegerTuple> combine(std::vector<IntegerTuple>, IndicesType)
    //IndicesType combine(IndicesType, std::vector<IntegerTuple>)
    //IndicesSet combine(IndicesSet, IndicesSet)
    //std::vector<IntegerTuple> combine(std::vector<IntegerTuple>, std::vector<IntegerTuple>)
    //std::vector<IntegerType> combine(std::vector<IntegerType>, std::vector<IntegerType>)
    //GridType combine(GridType, GridType)
    //std::vector<GridType> combine(std::vector<GridType>, std::vector<GridType>)
    std::any combine(std::vector<std::any> const& args); //union
    //std::vector<AnyVector1> intersection(std::vector<AnyVector1>, std::vector<AnyVector1>)
    //std::set<AnySet1> intersection(std::set<AnySet1>, std::set<AnySet1>)
    std::any intersection(std::vector<std::any> const& args); //returns the intersection of two containers
    //std::vector<AnyVector1> difference(std::vector<AnyVector1>, std::vector<AnyVector1>)
    //std::set<AnySet1> difference(std::set<AnySet1>, std::set<AnySet1>)
    std::any difference(std::vector<std::any> const& args); //set difference
    //std::vector<AnyVector1> dedupe(std::vector<AnyVector1>)
    std::any dedupe(std::vector<std::any> const& args); //remove duplicates
    //std::vector<AnyVector1> order(std::vector<AnyVector1>, Callable)
    std::any order(std::vector<std::any> const& args); //order container by custom key
    //std::vector<AnyVector1> repeat(AnyVector1, IntegerType)
    std::any repeat(std::vector<std::any> const& args); //repetition of item within vector
    //Boolean greater(IntegerType, IntegerType)
    std::any greater(std::vector<std::any> const& args); //greater
    //IntegerType size(std::vector<AnyVector1>)
    //IntegerType size(std::set<AnySet1>)
    //IntegerType size(IntegerTuple)
    std::any size(std::vector<std::any> const& args); //cardinality
    //AnyVector3 merge(std::vector<AnyVector3>)
    //AnySet2 merge(std::set<AnySet2>)
    std::any merge(std::vector<std::any> const& args); //merging
    //IntegerType maximum(std::vector<AnyVector1>)
    //IntegerType maximum(std::set<AnySet1>)
    std::any maximum(std::vector<std::any> const& args); //maximum
    //IntegerType minimum(std::vector<AnyVector1>)
    //IntegerType minimum(std::set<AnySet1>)
    std::any minimum(std::vector<std::any> const& args); //minimum
    //IntegerType valmax(IntegerVector, Callable)
    //IntegerType valmax(IntegerSet, Callable)
    //IntegerType valmax(std::vector<GridType>, Callable)
    //IntegerType valmax(Objects, Callable)
    //IntegerType valmax(IndicesSet, Callable)
    std::any valmax(std::vector<std::any> const& args); //maximum by custom function
    //IntegerType valmin(IntegerVector, Callable)
    //IntegerType valmin(IntegerSet, Callable)
    //IntegerType valmin(std::vector<GridType>, Callable)
    //IntegerType valmin(Objects, Callable)
    //IntegerType valmin(IndicesSet, Callable)
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
    //std::vector<AnyVector1> sfilter(std::vector<AnyVector1>, Callable)
    //std::set<AnySet1> sfilter(std::set<AnySet1>, Callable)
    std::any sfilter(std::vector<std::any> const& args); //keep elements in container that satisfy condition
    //AnyVector3 mfilter(std::vector<AnyVector3>, Callable)
    //AnySet2 mfilter(std::set<AnySet2>, Callable)
    std::any mfilter(std::vector<std::any> const& args); //filter and merge
    //AnyVector1 extract(std::vector<AnyVector1>, Callable)
    //AnySet1 extract(std::set<AnySet1>, Callable)
    std::any extract(std::vector<std::any> const& args); //first element of container that satisfies condition
    //std::vector<AnySet1> totuple(std::set<AnySet1>)
    std::any totuple(std::vector<std::any> const& args); //conversion to tuple
    //AnyVector1 first(std::vector<AnyVector1>)
    //AnySet1 first(std::set<AnySet1>)
    //IntegerType first(IntegerTuple)
    std::any first(std::vector<std::any> const& args); //first item of container
    //AnyVector1 last(std::vector<AnyVector1>)
    //AnySet1 last(std::set<AnySet1>)
    //IntegerType last(IntegerTuple)
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
    //ObjectType product(IntegerType, IntegerTuple)
    //IndicesType product(IntegerType, IntegerType)
    std::any product(std::vector<std::any> const& args); //cartesian product
    //std::vector<IntegerTuple> pair(IntegerTuple, IntegerTuple)
    //GridType pair(IntegerVector, IntegerVector)
    //GridVector pair(GridType, GridType)
    std::any pair(std::vector<std::any> const& args); //zipping of two tuples
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
    //std::vector<Boolean> apply(Callable, std::vector<Boolean>)
    //std::vector<Boolean> apply(Callable, std::vector<GridType>)
    //std::vector<IntegerType> apply(Callable, std::vector<IntegerType>)
    //std::vector<IntegerType> apply(Callable, std::vector<GridType>)
    //std::vector<GridType> apply(Callable, std::vector<GridType>)
    //std::vector<IntegerType> apply(Callable, Objects)
    std::any apply(std::vector<std::any> const& args); //apply function to each item in container
    //std::vector<Boolean> rapply(std::vector<Callable>, Boolean)
    //std::vector<Boolean> rapply(std::vector<Callable>, IntegerType)
    //std::vector<IntegerType> rapply(std::vector<Callable>, IntegerType)
    //std::vector<IntegerTuple> rapply(std::vector<Callable>, IntegerTuple)
    //std::vector<IntegerType> rapply(std::vector<Callable>, IntegerTuple)
    //std::vector<GridType> rapply(std::vector<Callable>, GridType)
    //std::vector<Boolean> rapply(std::vector<Callable>, GridType)
    //std::vector<IndicesSet> rapply(std::vector<Callable>, IndicesSet)
    //std::vector<ObjectType> rapply(std::vector<Callable>, ObjectType)
    //std::vector<IntegerType> rapply(std::vector<Callable>, ObjectType)
    std::any rapply(std::vector<std::any> const& args); //apply each function in container to value
    //GridType mapply(Callable, std::vector<GridType>)
    //IntegerVector mapply(Callable, GridType)
    std::any mapply(std::vector<std::any> const& args); //apply and merge
    //Boolean papply(Callable, std::vector<Boolean>, std::vector<Boolean>)
    //IntegerTuple papply(Callable, std::vector<IntegerType>, std::vector<IntegerType>)
    //Boolean papply(Callable, std::vector<IndicesType>, std::vector<IndicesType>)
    //Boolean papply(Callable, std::vector<IndicesType>, std::vector<ObjectType>)
    //Boolean papply(Callable, std::vector<ObjectType>, std::vector<IndicesType>)
    //Boolean papply(Callable, std::vector<ObjectType>, std::vector<ObjectType>)
    //IntegerType papply(Callable, std::vector<IndicesType>, std::vector<IndicesType>)
    //IntegerType papply(Callable, std::vector<IndicesType>, std::vector<ObjectType>)
    //IntegerType papply(Callable, std::vector<ObjectType>, std::vector<IndicesType>)
    //IntegerType papply(Callable, std::vector<ObjectType>, std::vector<ObjectType>)
    //IntegerTuple papply(Callable, std::vector<IndicesType>, std::vector<IndicesType>)
    //IntegerTuple papply(Callable, std::vector<IndicesType>, std::vector<ObjectType>)
    //IntegerTuple papply(Callable, std::vector<ObjectType>, std::vector<IndicesType>)
    //IntegerTuple papply(Callable, std::vector<ObjectType>, std::vector<ObjectType>)
    //Boolean papply(Callable, std::vector<IndicesType>, std::vector<GridType>)
    //Boolean papply(Callable, std::vector<ObjectType>, std::vector<GridType>)
    //GridType papply(Callable, std::vector<GridType>, std::vector<ObjectType>)
    //GridType papply(Callable, std::vector<GridType>, std::vector<IntegerType>)
    //IndicesType papply(Callable, std::vector<GridType>, std::vector<IntegerType>)
    //ObjectType papply(Callable, std::vector<IntegerType>, std::vector<ObjectType>)
    //ObjectType papply(Callable, std::vector<IntegerType>, std::vector<IndicesType>)
    //Objects papply(Callable, std::vector<Objects>, std::vector<IntegerType>)
    //IntegerVector papply(Callable, std::vector<Callable>, std::vector<GridType>)
    //GridVector papply(Callable, std::vector<GridType>, std::vector<GridType>)
    //IntegerType papply(Callable, std::vector<IntegerVector>, std::vector<Callable>)
    //IntegerType papply(Callable, std::vector<IntegerSet>, std::vector<Callable>)
    //IntegerType papply(Callable, std::vector<Objects>, std::vector<Callable>)
    //IntegerType papply(Callable, std::vector<IndicesSet>, std::vector<Callable>)
    std::any papply(std::vector<std::any> const& args); //apply function on two vectors
    //IntegerVector mpapply(Callable, std::vector<GridType>, std::vector<GridType>)
    //ObjectType mpapply(Callable, std::vector<Objects>, std::vector<IntegerType>)
    //IntegerVector mpapply(Callable, std::vector<GridType>, std::vector<ObjectType>)
    //IntegerVector mpapply(Callable, std::vector<GridType>, std::vector<IntegerType>)
    std::any mpapply(std::vector<std::any> const& args); //apply function on two vectors and merge
    //std::vector<Boolean> prapply(Callable, std::vector<IndicesType>, std::vector<IndicesType>)
    //std::vector<IntegerType> prapply(Callable, std::vector<IndicesType>, std::vector<IndicesType>)
    //std::vector<Boolean> prapply(Callable, std::vector<ObjectType>, std::vector<ObjectType>)
    //std::vector<IntegerType> prapply(Callable, std::vector<ObjectType>, std::vector<ObjectType>)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, std::vector<Boolean>)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, std::vector<IntegerType>)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, std::vector<IntegerTuple>)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, GridType)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, std::vector<GridType>)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, ObjectType)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, Objects)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, IndicesType)
    //std::vector<Callable> prapply(Callable, std::vector<Callable>, IndicesSet)
    std::any prapply(std::vector<std::any> const& args); //apply function on cartesian product
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
    std::any colorfilter(std::vector<std::any> const& args); //filter object by color
    //std::vector<AnyVector3> sizefilter(std::vector<AnyVector3>, IntegerType)
    //std::set<AnySet2> sizefilter(std::set<AnySet2>, IntegerType)
    std::any sizefilter(std::vector<std::any> const& args); //filter items by size
    //IndicesType asindices(GridType)
    std::any asindices(std::vector<std::any> const& args); //indices of all grid cells
    //IndicesType ofcolor(GridType, IntegerType)
    std::any ofcolor(std::vector<std::any> const& args); //indices of all grid cells with value
    //IntegerTuple ulcorner(Patch)
    std::any ulcorner(std::vector<std::any> const& args); //index of upper left corner
    //IntegerTuple urcorner(Patch)
    std::any urcorner(std::vector<std::any> const& args); //index of upper right corner
    //IntegerTuple llcorner(Patch)
    std::any llcorner(std::vector<std::any> const& args); //index of lower left corner
    //IntegerTuple lrcorner(Patch)
    std::any lrcorner(std::vector<std::any> const& args); //index of lower right corner
    //GridType crop(GridType, IntegerTuple, IntegerTuple)
    std::any crop(std::vector<std::any> const& args); //subgrid specified by start and dimension
    //IndicesType toindices(Patch)
    std::any toindices(std::vector<std::any> const& args); //indices of object cells
    //ObjectType recolor(IntegerType, Patch)
    std::any recolor(std::vector<std::any> const& args); //recolor patch
    //Patch shift(Patch, IntegerTuple)
    std::any shift(std::vector<std::any> const& args); //shift patch
    //Patch normalize(Patch)
    std::any normalize(std::vector<std::any> const& args); //moves upper left corner to origin
    //IndicesType dneighbors(IntegerTuple)
    std::any dneighbors(std::vector<std::any> const& args); //directly adjacent indices
    //IndicesType ineighbors(IntegerTuple)
    std::any ineighbors(std::vector<std::any> const& args); //diagonally adjacent indices
    //IndicesType neighbors(IntegerTuple)
    std::any neighbors(std::vector<std::any> const& args); //adjacent indices
    //Objects objects(GridType, Boolean, Boolean, Boolean)
    std::any objects(std::vector<std::any> const& args); //Objects occurring on the grid
    //Objects partition(GridType)
    std::any partition(std::vector<std::any> const& args); //each cell with the same value part of the same object
    //Objects fgpartition(GridType)
    std::any fgpartition(std::vector<std::any> const& args); //each cell with the same value part of the same object without background
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
    //Boolean bordering(Patch, GridType)
    std::any bordering(std::vector<std::any> const& args); //whether a patch is adjacent to a grid border
    //IntegerTuple centerofmass(Patch)
    std::any centerofmass(std::vector<std::any> const& args); //center of mass
    //IntegerSet palette(Element)
    std::any palette(std::vector<std::any> const& args); //colors occurring in object or grid
    //IntegerType numcolors(Element)
    std::any numcolors(std::vector<std::any> const& args); //number of colors occurring in object or grid
    //IntegerType color(ObjectType)
    std::any color(std::vector<std::any> const& args); //color of object
    //ObjectType toobject(Patch, GridType)
    std::any toobject(std::vector<std::any> const& args); //object from patch and grid
    //ObjectType asobject(GridType)
    std::any asobject(std::vector<std::any> const& args); //conversion of grid to object
    //GridType rot90(GridType)
    std::any rot90(std::vector<std::any> const& args); //quarter clockwise rotation
    //GridType rot180(GridType)
    std::any rot180(std::vector<std::any> const& args); //half rotation
    //GridType rot270(GridType)
    std::any rot270(std::vector<std::any> const& args); //quarter anticlockwise rotation
    //Piece hmirror(Piece)
    std::any hmirror(std::vector<std::any> const& args); //mirroring along horizontal
    //Piece vmirror(Piece)
    std::any vmirror(std::vector<std::any> const& args); //mirroring along vertical
    //Piece dmirror(Piece)
    std::any dmirror(std::vector<std::any> const& args); //mirroring along diagonal
    //Piece cmirror(Piece)
    std::any cmirror(std::vector<std::any> const& args); //mirroring along counterdiagonal
    //GridType fill(GridType, IntegerType, Patch)
    std::any fill(std::vector<std::any> const& args); //fill value at indices
    //GridType paint(GridType, ObjectType)
    std::any paint(std::vector<std::any> const& args); //paint object to grid
    //GridType underfill(GridType, IntegerType, Patch)
    std::any underfill(std::vector<std::any> const& args); //fill value at indices that are background
    //GridType underpaint(GridType, ObjectType)
    std::any underpaint(std::vector<std::any> const& args); //paint object to grid where there is background
    //GridType hupscale(GridType, IntegerType)
    std::any hupscale(std::vector<std::any> const& args); //upscale grid horizontally
    //GridType vupscale(GridType, IntegerType)
    std::any vupscale(std::vector<std::any> const& args); //upscale grid vertically
    //Element upscale(Element, IntegerType)
    std::any upscale(std::vector<std::any> const& args); //upscale object or grid
    //GridType downscale(GridType, IntegerType)
    std::any downscale(std::vector<std::any> const& args); //downscale object or grid
    //GridType hconcat(GridType, GridType)
    std::any hconcat(std::vector<std::any> const& args); //concatenate two grids horizontally
    //GridType vconcat(GridType, GridType)
    std::any vconcat(std::vector<std::any> const& args); //concatenate two grids vertically
    //GridType subgrid(Patch, GridType)
    std::any subgrid(std::vector<std::any> const& args); //smallest subgrid containing object
    //GridVector hsplit(GridType, IntegerType)
    std::any hsplit(std::vector<std::any> const& args); //split grid horizontally
    //GridVector vsplit(GridType, IntegerType)
    std::any vsplit(std::vector<std::any> const& args); //split grid vertically
    //GridType cellwise(GridType, GridType, IntegerType)
    std::any cellwise(std::vector<std::any> const& args); //cellwise match of two grids
    //GridType replace(GridType, IntegerType, IntegerType)
    std::any replace(std::vector<std::any> const& args); //color substitution
    //GridType switch_(GridType, IntegerType, IntegerType)
    std::any switch_(std::vector<std::any> const& args); //color switching
    //IntegerTuple center(Patch)
    std::any center(std::vector<std::any> const& args); //center of the patch
    //IntegerTuple position(Patch, Patch)
    std::any position(std::vector<std::any> const& args); //relative position between two patches
    //IntegerType index(GridType, IntegerTuple)
    std::any index(std::vector<std::any> const& args); //color at location
    //GridType canvas(IntegerType, IntegerTuple)
    std::any canvas(std::vector<std::any> const& args); //grid construction
    //IndicesType corners(Patch)
    std::any corners(std::vector<std::any> const& args); //indices of corners
    //IndicesType connect(IntegerTuple, IntegerTuple)
    std::any connect(std::vector<std::any> const& args); //line between two points
    //GridType cover(GridType, Patch)
    std::any cover(std::vector<std::any> const& args); //remove object from grid
    //GridType trim(GridType)
    std::any trim(std::vector<std::any> const& args); //trim border of grid
    //GridType move(GridType, ObjectType, IntegerTuple)
    std::any move(std::vector<std::any> const& args); //move object on grid
    //GridType tophalf(GridType)
    std::any tophalf(std::vector<std::any> const& args); //upper half of grid
    //GridType bottomhalf(GridType)
    std::any bottomhalf(std::vector<std::any> const& args); //lower half of grid
    //GridType lefthalf(GridType)
    std::any lefthalf(std::vector<std::any> const& args); //left half of grid
    //GridType righthalf(GridType)
    std::any righthalf(std::vector<std::any> const& args); //right half of grid
    //IndicesType vfrontier(IntegerTuple)
    std::any vfrontier(std::vector<std::any> const& args); //vertical frontier
    //IndicesType hfrontier(IntegerTuple)
    std::any hfrontier(std::vector<std::any> const& args); //horizontal frontier
    //IndicesType backdrop(Patch)
    std::any backdrop(std::vector<std::any> const& args); //indices in bounding box of patch
    //IndicesType delta(Patch)
    std::any delta(std::vector<std::any> const& args); //indices in bounding box but not part of patch
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
    //IndicesType occurrences(GridType, ObjectType)
    std::any occurrences(std::vector<std::any> const& args); //locations of occurrences of object in grid
    //Objects frontiers(GridType)
    std::any frontiers(std::vector<std::any> const& args); //set of frontiers
    //GridType compress(GridType)
    std::any compress(std::vector<std::any> const& args); //removes frontiers from grid
    //IntegerType hperiod(ObjectType)
    std::any hperiod(std::vector<std::any> const& args); //horizontal periodicity
    //IntegerType vperiod(ObjectType)
    std::any vperiod(std::vector<std::any> const& args); //vertical periodicity
}

#endif // AICPP_HODEL_H
