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
    typedef int16_t Integer;
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
    typedef std::vector<Integer> IntegerVector;
    typedef std::vector<Object> ObjectVector;
    typedef std::vector<Boolean> BooleanVector;
    typedef std::vector<Grid> GridVector;
    typedef std::vector<IntegerTuple> IntegerTupleVector;
    typedef std::vector<Indices> IndicesVector;
    typedef std::vector<Callable> CallableVector;
    typedef std::tuple<Boolean, Integer, IntegerTuple, IntegerSet, Grid, Cell, Object, Objects, Indices, IndicesSet, Callable, IntegerVector, GridVector, BooleanVector, ObjectVector, std::vector<Objects>, IndicesVector, std::vector<IndicesSet>, CallableVector> AnyIdentity;
    typedef std::tuple<Boolean, Integer, IntegerTuple, IntegerSet, Grid, Cell, Object, Objects, Indices, IndicesSet, GridVector, BooleanVector, std::vector<Objects> > AnyEquality;
    typedef std::tuple<Boolean, Integer, IntegerTuple, IntegerVector, Grid, Object, Indices, Objects, Callable, IntegerTupleVector > AnyVector1;
    typedef std::tuple<Boolean, Integer, IntegerTuple, IntegerVector, Grid, Objects> AnyVector2;
    typedef std::tuple<Integer, Cell, Object, IntegerTuple, Indices> AnySet1;
    typedef std::tuple<IntegerVector, Grid, Object> AnyVector3;
    typedef std::tuple<Object, Indices> AnySet2;
    typedef std::pair<IntegerTuple, IntegerTuple> IntegerTuplePair;
    typedef std::pair<Object, Object> ObjectPair;
    typedef std::pair<Grid, Boolean> GridBooleanPair;
    typedef std::pair<Object, Integer> ObjectIntegerPair;
    typedef std::pair<Indices, Integer> IndicesIntegerPair;
    typedef std::pair<IntegerTuple, IndicesIntegerPair> IntegerTupleIndicesIntegerPairPair;
    typedef std::pair<Cell, Cell> CellPair;
    typedef std::pair<Callable, Callable> CallablePair;
    
    //AnyIdentity identity(AnyIdentity)
    std::any identity(std::vector<std::any> const& args); //identity function
    //Num1 add(Num2, Num3)
    //IntegerVector add(IntegerVector, Integer)
    //IntegerVector add(Integer, IntegerVector)
    //Integer add(Boolean, Integer)
    //Integer add(Integer, Boolean)
    std::any add(std::vector<std::any> const& args); //addition
    //Num1 subtract(Num2, Num3)
    //IntegerVector subtract(IntegerVector, Integer)
    //IntegerVector subtract(Integer, IntegerVector)
    //Integer subtract(Boolean, Integer)
    //Integer subtract(Integer, Boolean)
    std::any subtract(std::vector<std::any> const& args); //subtraction
    //Num1 multiply(Num2, Num3)
    //IntegerVector multiply(IntegerVector, Integer)
    //IntegerVector multiply(Integer, IntegerVector)
    //Integer multiply(Boolean, Integer)
    //Integer multiply(Integer, Boolean)
    std::any multiply(std::vector<std::any> const& args); //multiplication
    //Num1 divide(Num2, Num3)
    //IntegerVector divide(IntegerVector, Integer)
    std::any divide(std::vector<std::any> const& args); //floor division
    //Numerical invert(Numerical)
    std::any invert(std::vector<std::any> const& args); //inversion with respect to addition
    //Boolean even(Numerical)
    std::any even(std::vector<std::any> const& args); //evenness
    //Numerical double_(Numerical)
    //Integer double_(Boolean)
    std::any double_(std::vector<std::any> const& args); //scaling by two
    //Numerical halve(Numerical)
    std::any halve(std::vector<std::any> const& args); //scaling by one half
    //Boolean flip(Boolean)
    std::any flip(std::vector<std::any> const& args); //logical not
    //Boolean equality(AnyEquality, AnyEquality)
    std::any equality(std::vector<std::any> const& args); //equality
    //Boolean contained(AnyVector1, std::vector<AnyVector1>)
    //Boolean contained(AnySet1, std::set<AnySet1>)
    std::any contained(std::vector<std::any> const& args); //element of
    //IntegerTuple combine(Integer, Integer)
    //IntegerSet combine(IntegerSet, IntegerSet)
    //IntegerVector combine(IntegerVector, IntegerSet)
    //IntegerSet combine(IntegerSet, IntegerVector)
    //ObjectVector combine(Object, Object)
    //std::vector<Objects> combine(Objects, Objects)
    //Indices combine(Indices, Indices)
    //IntegerTupleVector combine(IntegerTupleVector, Indices)
    //Indices combine(Indices, IntegerTupleVector)
    //IndicesSet combine(IndicesSet, IndicesSet)
    //IntegerTupleVector combine(IntegerTupleVector, IntegerTupleVector)
    //IntegerVector combine(IntegerVector, IntegerVector)
    //Grid combine(Grid, Grid)
    //GridVector combine(GridVector, GridVector)
    //ObjectVector combine(ObjectVector, ObjectVector)
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
    //std::set<AnySet1> order(std::set<AnySet1>, Callable)
    std::any order(std::vector<std::any> const& args); //order container by custom key
    //std::vector<AnyVector1> repeat(AnyVector1, Integer)
    std::any repeat(std::vector<std::any> const& args); //repetition of item within vector
    //Boolean greater(Integer, Integer)
    //Boolean greater(IntegerTuple, IntegerTuple)
    //Boolean greater(Object, Object)
    std::any greater(std::vector<std::any> const& args); //greater
    //Integer size(std::vector<AnyVector1>)
    //Integer size(std::set<AnySet1>)
    //Integer size(IntegerTuple)
    std::any size(std::vector<std::any> const& args); //cardinality
    //AnyVector3 merge(std::vector<AnyVector3>)
    //AnySet2 merge(std::set<AnySet2>)
    //GridVector merge(std::vector<GridVector>)
    //Object merge(ObjectPair)
    std::any merge(std::vector<std::any> const& args); //merging
    //Integer maximum(IntegerVector)
    //Integer maximum(std::set<Integer>)
    //Integer maximum(IntegerTuple)
    std::any maximum(std::vector<std::any> const& args); //maximum
    //Integer minimum(IntegerVector)
    //Integer minimum(std::set<Integer>)
    //Integer minimum(IntegerTuple)
    std::any minimum(std::vector<std::any> const& args); //minimum
    //Integer valmax(IntegerVector, Callable)
    //Integer valmax(IntegerSet, Callable)
    //Integer valmax(GridVector, Callable)
    //Integer valmax(Objects, Callable)
    //Integer valmax(IndicesSet, Callable)
    std::any valmax(std::vector<std::any> const& args); //maximum by custom function
    //Integer valmin(IntegerVector, Callable)
    //Integer valmin(IntegerSet, Callable)
    //Integer valmin(GridVector, Callable)
    //Integer valmin(Objects, Callable)
    //Integer valmin(IndicesSet, Callable)
    std::any valmin(std::vector<std::any> const& args); //minimum by custom function
    //AnyVector1 argmax(std::vector<AnyVector1>, Callable)
    //AnySet1 argmax(std::set<AnySet1>, Callable)
    std::any argmax(std::vector<std::any> const& args); //largest item by custom order
    //AnyVector1 argmin(std::vector<AnyVector1>, Callable)
    //AnySet1 argmin(std::set<AnySet1>, Callable)
    std::any argmin(std::vector<std::any> const& args); //smallest item by custom order
    //AnyVector1 mostcommon(std::vector<AnyVector1>)
    //AnySet1 mostcommon(std::vector<AnySet1>)
    std::any mostcommon(std::vector<std::any> const& args); //most common item
    //AnyVector1 leastcommon(std::vector<AnyVector1>)
    //AnySet1 leastcommon(std::vector<AnySet1>)
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
    //Boolean positive(Integer)
    std::any positive(std::vector<std::any> const& args); //positive
    //IntegerTuple toivec(Integer)
    std::any toivec(std::vector<std::any> const& args); //vector pointing vertically
    //IntegerTuple tojvec(Integer)
    std::any tojvec(std::vector<std::any> const& args); //vector pointing horizontally
    //std::vector<AnyVector1> sfilter(std::vector<AnyVector1>, Callable)
    //std::set<AnySet1> sfilter(std::set<AnySet1>, Callable)
    //std::set<ObjectPair> sfilter(std::set<ObjectPair>, Callable)
    //std::vector<ObjectIntegerPair> sfilter(std::vector<ObjectIntegerPair>, Callable)
    //std::set<IntegerTuplePair> sfilter(std::set<IntegerTuplePair>, Callable)
    //std::set<CellPair> sfilter(std::set<CellPair>, Callable)
    std::any sfilter(std::vector<std::any> const& args); //keep elements in container that satisfy condition
    //AnyVector3 mfilter(std::vector<AnyVector3>, Callable)
    //AnySet2 mfilter(std::set<AnySet2>, Callable)
    std::any mfilter(std::vector<std::any> const& args); //filter and merge
    //AnyVector1 extract(std::vector<AnyVector1>, Callable)
    //AnySet1 extract(std::set<AnySet1>, Callable)
    //GridBooleanPair extract(std::vector<GridBooleanPair>, Callable)
    std::any extract(std::vector<std::any> const& args); //first element of container that satisfies condition
    //std::vector<AnySet1> totuple(std::set<AnySet1>)
    //IntegerVector totuple(IntegerTuple)
    std::any totuple(std::vector<std::any> const& args); //conversion to tuple
    //AnyVector1 first(std::vector<AnyVector1>)
    //AnySet1 first(std::set<AnySet1>)
    //Integer first(IntegerTuple)
    //Integer first(Cell)
    //IntegerTuple first(IntegerTuplePair)
    //Object first(ObjectPair)
    //Grid first(GridBooleanPair)
    //Object first(ObjectIntegerPair)
    //Indices first(IndicesIntegerPair)
    //IntegerTuple first(IntegerTupleIndicesIntegerPairPair)
    //Cell first(CellPair)
    //Callable first(CallablePair)
    std::any first(std::vector<std::any> const& args); //first item of container
    //AnyVector1 last(std::vector<AnyVector1>)
    //AnySet1 last(std::set<AnySet1>)
    //Integer last(IntegerTuple)
    //IntegerTuple last(Cell)
    //IntegerTuple last(IntegerTuplePair)
    //Object last(ObjectPair)
    //Boolean last(GridBooleanPair)
    //IntegerVector last(ObjectIntegerPair)
    //Integer last(IndicesIntegerPair)
    //IndicesIntegerPair last(IntegerTupleIndicesIntegerPairPair)
    //Cell last(CellPair)
    //Callable last(CallablePair)
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
    //IntegerVector interval(Integer, Integer, Integer)
    std::any interval(std::vector<std::any> const& args); //range
    //IntegerTuple astuple(Integer, Integer)
    //Indices astuple(IntegerTuple, IntegerTuple)
    //GridVector astuple(Grid, Grid)
    //Cell astuple(Integer, IntegerTuple)
    //IntegerTuplePair astuple(IntegerTupleVector, IntegerTupleVector)
    std::any astuple(std::vector<std::any> const& args); //constructs a tuple
    //Object product(Integer, IntegerTuple)
    //Indices product(Integer, Integer)
    //std::set<IntegerTuplePair> product(Indices, Indices)
    //std::set<ObjectPair> product(Objects, Objects)
    //std::set<CellPair> product(Object, Object)
    //std::vector<CallablePair> product(CallableVector, CallableVector)
    std::any product(std::vector<std::any> const& args); //cartesian product
    //IntegerTupleVector pair(IntegerVector, IntegerVector)
    //GridBooleanPair pair(GridVector, BooleanVector)
    //ObjectIntegerPair pair(ObjectVector, IntegerVector)
    //IntegerTuplePair pair(Indices, Indices)
    //Object pair(IntegerVector, IntegerTupleVector)
    //std::vector<IndicesIntegerPair> pair(Indices, IntegerVector)
    //std::vector<ObjectPair> pair(ObjectVector, ObjectVector)
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
    //Callable power(Callable, Integer)
    std::any power(std::vector<std::any> const& args); //power of function
    //Callable fork(Callable, Callable, Callable)
    std::any fork(std::vector<std::any> const& args); //creates a wrapper function
    //BooleanVector apply(Callable, BooleanVector)
    //BooleanVector apply(Callable, GridVector)
    //IntegerVector apply(Callable, IntegerVector)
    //std::vector<IntegerVector> apply(Callable, IntegerVector)
    //IntegerVector apply(Callable, GridVector)
    //GridVector apply(Callable, GridVector)
    //IntegerSet apply(Callable, Objects)
    //IntegerVector apply(Callable, Objects)
    //IntegerVector apply(Callable, ObjectVector)
    //Objects apply(Callable, Objects)
    //ObjectVector apply(Callable, ObjectVector)
    //Grid apply(Callable, std::vector<IntegerTupleVector>)
    //IntegerVector apply(Callable, IntegerTupleVector)
    //IndicesSet apply(Callable, Indices)
    //IndicesVector apply(Callable, IntegerTupleVector)
    //Indices apply(Callable, IndicesSet)
    //GridVector apply(Callable, std::vector<GridVector>)
    //IndicesSet apply(Callable, IndicesSet)
    //Grid apply(Callable, Grid)
    //IndicesSet apply(Callable, std::set<IntegerTuplePair>)
    //GridVector apply(Callable, IntegerVector)
    //Objects apply(Callable, Indices)
    //ObjectVector apply(Callable, IntegerTupleVector)
    //Indices apply(Callable, IntegerSet)
    //IntegerTupleVector apply(Callable, IntegerVector)
    //Indices apply(Callable, IntegerSet)
    //GridVector apply(Callable, ObjectVector)
    //IntegerVector apply(Callable, std::vector<Objects>)
    //IntegerTuple apply(Callable, std::vector<Objects>)
    //std::set<Grid> apply(Callable, Objects)
    //GridVector apply(Callable, ObjectVector)
    //Indices apply(Callable, Indices)
    //IntegerTupleVector apply(Callable, IntegerTupleVector)
    //IntegerVector apply(Callable, IntegerTupleVector)
    //Objects apply(Callable, IntegerSet)
    //ObjectVector apply(Callable, GridVector)
    //ObjectVector apply(Callable, IntegerVector)
    //IntegerTupleVector apply(Callable, IntegerVector)
    //Indices apply(Callable, std::set<IntegerTuplePair>)
    //Object apply(Callable, Objects)
    //Objects apply(Callable, std::set<ObjectPair>)
    //ObjectVector apply(Callable, std::vector<ObjectIntegerPair>)
    //IndicesVector apply(Callable, GridVector)
    //IntegerTupleVector apply(Callable, std::vector<IntegerTuplePair>)
    //IndicesVector apply(Callable, std::vector<IntegerTuplePair>)
    //IntegerTupleVector apply(Callable, GridVector)
    //Objects apply(Callable, IndicesSet)
    //IntegerVector apply(Callable, Grid)
    //IntegerTupleVector apply(Callable, ObjectVector)
    //IndicesSet apply(Callable, std::set<ObjectPair>)
    //Indices apply(Callable, std::set<ObjectPair>)
    //IndicesVector apply(Callable, std::vector<IndicesIntegerPair>)
    //IndicesVector apply(Callable, Grid)
    //Objects apply(Callable, std::set<CellPair>)
    //IndicesVector apply(CallableVector, IntegerVector)
    //ObjectVector apply(Callable, std::vector<ObjectPair>)
    //Object apply(Callable, Indices)
    //CallableVector apply(Callable, IntegerVector)
    //CallableVector apply(Callable, std::vector<CallablePair>)
    //IndicesVector apply(Callable, ObjectVector)
    std::any apply(std::vector<std::any> const& args); //apply function to each item in container
    //BooleanVector rapply(CallableVector, Boolean)
    //BooleanVector rapply(CallableVector, Integer)
    //IntegerVector rapply(CallableVector, Integer)
    //IntegerTupleVector rapply(CallableVector, IntegerTuple)
    //IntegerVector rapply(CallableVector, IntegerTuple)
    //GridVector rapply(CallableVector, Grid)
    //BooleanVector rapply(CallableVector, Grid)
    //std::vector<IndicesSet> rapply(CallableVector, IndicesSet)
    //ObjectVector rapply(CallableVector, Object)
    //IntegerVector rapply(CallableVector, Object)
    std::any rapply(std::vector<std::any> const& args); //apply each function in container to value
    //Grid mapply(Callable, GridVector)
    //IntegerVector mapply(Callable, Grid)
    //Indices mapply(Callable, Grid)
    //Object mapply(Callable, Objects)
    //Object mapply(Callable, ObjectVector)
    //Object mapply(Callable, Indices)
    //Object mapply(Callable, IntegerTupleVector)
    //Object mapply(Callable, IntegerSet)
    //Object mapply(Callable, IntegerVector)
    //Indices mapply(Callable, IntegerVector)
    //Object mapply(Callable, std::vector<ObjectIntegerPair>)
    //Indices mapply(Callable, std::vector<IntegerTuplePair>)
    //Indices mapply(Callable, std::set<ObjectPair>)
    //Indices mapply(Callable, std::vector<IndicesIntegerPair>)
    std::any mapply(std::vector<std::any> const& args); //apply and merge
    //Boolean papply(Callable, BooleanVector, BooleanVector)
    //IntegerTuple papply(Callable, IntegerVector, IntegerVector)
    //Boolean papply(Callable, IndicesVector, IndicesVector)
    //Boolean papply(Callable, IndicesVector, ObjectVector)
    //Boolean papply(Callable, ObjectVector, IndicesVector)
    //Boolean papply(Callable, ObjectVector, ObjectVector)
    //Integer papply(Callable, IndicesVector, IndicesVector)
    //Integer papply(Callable, IndicesVector, ObjectVector)
    //Integer papply(Callable, ObjectVector, IndicesVector)
    //Integer papply(Callable, ObjectVector, ObjectVector)
    //IntegerTuple papply(Callable, IndicesVector, IndicesVector)
    //IntegerTuple papply(Callable, IndicesVector, ObjectVector)
    //IntegerTuple papply(Callable, ObjectVector, IndicesVector)
    //IntegerTuple papply(Callable, ObjectVector, ObjectVector)
    //Boolean papply(Callable, IndicesVector, GridVector)
    //Boolean papply(Callable, ObjectVector, GridVector)
    //Grid papply(Callable, GridVector, ObjectVector)
    //Grid papply(Callable, GridVector, IntegerVector)
    //Indices papply(Callable, GridVector, IntegerVector)
    //Object papply(Callable, IntegerVector, ObjectVector)
    //Object papply(Callable, IntegerVector, IndicesVector)
    //Objects papply(Callable, std::vector<Objects>, IntegerVector)
    //IntegerVector papply(Callable, CallableVector, GridVector)
    //GridVector papply(Callable, GridVector, GridVector)
    //Integer papply(Callable, std::vector<IntegerVector>, CallableVector)
    //Integer papply(Callable, std::vector<IntegerSet>, CallableVector)
    //Integer papply(Callable, std::vector<Objects>, CallableVector)
    //Integer papply(Callable, std::vector<IndicesSet>, CallableVector)
    //std::vector<IntegerTupleVector> papply(Callable, Grid, Grid)
    //BooleanVector papply(Callable, GridVector, GridVector)
    //ObjectVector papply(Callable, Objects, Indices)
    //ObjectVector papply(Callable, ObjectVector, IntegerTupleVector)
    //Indices papply(Callable, IntegerTupleVector, IntegerTupleVector)
    std::any papply(std::vector<std::any> const& args); //apply function on two vectors
    //IntegerVector mpapply(Callable, GridVector, GridVector)
    //Object mpapply(Callable, std::vector<Objects>, IntegerVector)
    //Object mpapply(Callable, std::vector<Objects>, IntegerTupleVector)
    //IntegerVector mpapply(Callable, GridVector, ObjectVector)
    //IntegerVector mpapply(Callable, GridVector, IntegerVector)
    //Object mpapply(Callable, IntegerVector, ObjectVector)
    //Object mpapply(Callable, IntegerVector, Objects)
    //Object mpapply(Callable, IntegerVector, ObjectVector)
    std::any mpapply(std::vector<std::any> const& args); //apply function on two vectors and merge
    //BooleanVector prapply(Callable, IndicesVector, IndicesVector)
    //IntegerVector prapply(Callable, IndicesVector, IndicesVector)
    //BooleanVector prapply(Callable, ObjectVector, ObjectVector)
    //IntegerVector prapply(Callable, ObjectVector, ObjectVector)
    //CallableVector prapply(Callable, CallableVector, BooleanVector)
    //CallableVector prapply(Callable, CallableVector, IntegerVector)
    //CallableVector prapply(Callable, CallableVector, IntegerTupleVector)
    //CallableVector prapply(Callable, CallableVector, Grid)
    //CallableVector prapply(Callable, CallableVector, GridVector)
    //CallableVector prapply(Callable, CallableVector, Object)
    //CallableVector prapply(Callable, CallableVector, Objects)
    //CallableVector prapply(Callable, CallableVector, Indices)
    //CallableVector prapply(Callable, CallableVector, IndicesSet)
    //IndicesSet prapply(Callable, Indices, Indices)
    //IndicesSet prapply(Callable, IntegerVector, IntegerVector)
    //IndicesSet prapply(Callable, IndicesSet, Indices)
    //IndicesSet prapply(Callable, IndicesSet, IntegerTupleVector)
    //Indices prapply(Callable, Indices, IntegerVector)
    std::any prapply(std::vector<std::any> const& args); //apply function on cartesian product
    //Integer mostcolor(Element)
    std::any mostcolor(std::vector<std::any> const& args); //most common color
    //Integer leastcolor(Element)
    std::any leastcolor(std::vector<std::any> const& args); //least common color
    //Integer height(Piece)
    std::any height(std::vector<std::any> const& args); //height of grid or patch
    //Integer width(Piece)
    std::any width(std::vector<std::any> const& args); //width of grid or patch
    //IntegerTuple shape(Piece)
    std::any shape(std::vector<std::any> const& args); //height and width of grid or patch 
    //Boolean portrait(Piece)
    std::any portrait(std::vector<std::any> const& args); //whether height is greater than width
    //Integer colorcount(Element, Integer)
    std::any colorcount(std::vector<std::any> const& args); //number of cells with color
    //Objects colorfilter(Objects, Integer)
    std::any colorfilter(std::vector<std::any> const& args); //filter object by color
    //std::vector<AnyVector3> sizefilter(std::vector<AnyVector3>, Integer)
    //std::set<AnySet2> sizefilter(std::set<AnySet2>, Integer)
    std::any sizefilter(std::vector<std::any> const& args); //filter items by size
    //Indices asindices(Grid)
    std::any asindices(std::vector<std::any> const& args); //indices of all grid cells
    //Indices ofcolor(Grid, Integer)
    std::any ofcolor(std::vector<std::any> const& args); //indices of all grid cells with value
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
    //Indices toindices(Patch)
    std::any toindices(std::vector<std::any> const& args); //indices of object cells
    //Object recolor(Integer, Patch)
    std::any recolor(std::vector<std::any> const& args); //recolor patch
    //Patch shift(Patch, IntegerTuple)
    std::any shift(std::vector<std::any> const& args); //shift patch
    //Patch normalize(Patch)
    std::any normalize(std::vector<std::any> const& args); //moves upper left corner to origin
    //Indices dneighbors(IntegerTuple)
    std::any dneighbors(std::vector<std::any> const& args); //directly adjacent indices
    //Indices ineighbors(IntegerTuple)
    std::any ineighbors(std::vector<std::any> const& args); //diagonally adjacent indices
    //Indices neighbors(IntegerTuple)
    std::any neighbors(std::vector<std::any> const& args); //adjacent indices
    //Objects objects(Grid, Boolean, Boolean, Boolean)
    std::any objects(std::vector<std::any> const& args); //objects occurring on the grid
    //Objects partition(Grid)
    std::any partition(std::vector<std::any> const& args); //each cell with the same value part of the same object
    //Objects fgpartition(Grid)
    std::any fgpartition(std::vector<std::any> const& args); //each cell with the same value part of the same object without background
    //Integer uppermost(Patch)
    std::any uppermost(std::vector<std::any> const& args); //row index of uppermost occupied cell
    //Integer lowermost(Patch)
    std::any lowermost(std::vector<std::any> const& args); //row index of lowermost occupied cell
    //Integer leftmost(Patch)
    std::any leftmost(std::vector<std::any> const& args); //column index of leftmost occupied cell
    //Integer rightmost(Patch)
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
    //Integer manhattan(Patch, Patch)
    std::any manhattan(std::vector<std::any> const& args); //closest manhattan distance between two patches
    //Boolean adjacent(Patch, Patch)
    std::any adjacent(std::vector<std::any> const& args); //whether two patches are adjacent
    //Boolean bordering(Patch, Grid)
    std::any bordering(std::vector<std::any> const& args); //whether a patch is adjacent to a grid border
    //IntegerTuple centerofmass(Patch)
    std::any centerofmass(std::vector<std::any> const& args); //center of mass
    //IntegerSet palette(Element)
    std::any palette(std::vector<std::any> const& args); //colors occurring in object or grid
    //Integer numcolors(Element)
    std::any numcolors(std::vector<std::any> const& args); //number of colors occurring in object or grid
    //Integer color(Object)
    std::any color(std::vector<std::any> const& args); //color of object
    //Object toobject(Patch, Grid)
    std::any toobject(std::vector<std::any> const& args); //object from patch and grid
    //Object asobject(Grid)
    std::any asobject(std::vector<std::any> const& args); //conversion of grid to object
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
    //Grid fill(Grid, Integer, Patch)
    //Grid fill(Grid, Integer, IntegerTupleVector)
    std::any fill(std::vector<std::any> const& args); //fill value at indices
    //Grid paint(Grid, Object)
    std::any paint(std::vector<std::any> const& args); //paint object to grid
    //Grid underfill(Grid, Integer, Patch)
    std::any underfill(std::vector<std::any> const& args); //fill value at indices that are background
    //Grid underpaint(Grid, Object)
    std::any underpaint(std::vector<std::any> const& args); //paint object to grid where there is background
    //Grid hupscale(Grid, Integer)
    std::any hupscale(std::vector<std::any> const& args); //upscale grid horizontally
    //Grid vupscale(Grid, Integer)
    std::any vupscale(std::vector<std::any> const& args); //upscale grid vertically
    //Element upscale(Element, Integer)
    std::any upscale(std::vector<std::any> const& args); //upscale object or grid
    //Grid downscale(Grid, Integer)
    std::any downscale(std::vector<std::any> const& args); //downscale object or grid
    //Grid hconcat(Grid, Grid)
    std::any hconcat(std::vector<std::any> const& args); //concatenate two grids horizontally
    //Grid vconcat(Grid, Grid)
    std::any vconcat(std::vector<std::any> const& args); //concatenate two grids vertically
    //Grid subgrid(Patch, Grid)
    std::any subgrid(std::vector<std::any> const& args); //smallest subgrid containing object
    //GridVector hsplit(Grid, Integer)
    std::any hsplit(std::vector<std::any> const& args); //split grid horizontally
    //GridVector vsplit(Grid, Integer)
    std::any vsplit(std::vector<std::any> const& args); //split grid vertically
    //Grid cellwise(Grid, Grid, Integer)
    std::any cellwise(std::vector<std::any> const& args); //cellwise match of two grids
    //Grid replace(Grid, Integer, Integer)
    std::any replace(std::vector<std::any> const& args); //color substitution
    //Grid switch_(Grid, Integer, Integer)
    std::any switch_(std::vector<std::any> const& args); //color switching
    //IntegerTuple center(Patch)
    std::any center(std::vector<std::any> const& args); //center of the patch
    //IntegerTuple position(Patch, Patch)
    std::any position(std::vector<std::any> const& args); //relative position between two patches
    //Integer index(Grid, IntegerTuple)
    std::any index(std::vector<std::any> const& args); //color at location
    //Grid canvas(Integer, IntegerTuple)
    std::any canvas(std::vector<std::any> const& args); //grid construction
    //Indices corners(Patch)
    std::any corners(std::vector<std::any> const& args); //indices of corners
    //Indices connect(IntegerTuple, IntegerTuple)
    std::any connect(std::vector<std::any> const& args); //line between two points
    //Grid cover(Grid, Patch)
    std::any cover(std::vector<std::any> const& args); //remove object from grid
    //Grid trim(Grid)
    std::any trim(std::vector<std::any> const& args); //trim border of grid
    //Grid move(Grid, Object, IntegerTuple)
    std::any move(std::vector<std::any> const& args); //move object on grid
    //Grid tophalf(Grid)
    std::any tophalf(std::vector<std::any> const& args); //upper half of grid
    //Grid bottomhalf(Grid)
    std::any bottomhalf(std::vector<std::any> const& args); //lower half of grid
    //Grid lefthalf(Grid)
    std::any lefthalf(std::vector<std::any> const& args); //left half of grid
    //Grid righthalf(Grid)
    std::any righthalf(std::vector<std::any> const& args); //right half of grid
    //Indices vfrontier(IntegerTuple)
    std::any vfrontier(std::vector<std::any> const& args); //vertical frontier
    //Indices hfrontier(IntegerTuple)
    std::any hfrontier(std::vector<std::any> const& args); //horizontal frontier
    //Indices backdrop(Patch)
    std::any backdrop(std::vector<std::any> const& args); //indices in bounding box of patch
    //Indices delta(Patch)
    std::any delta(std::vector<std::any> const& args); //indices in bounding box but not part of patch
    //IntegerTuple gravitate(Patch, Patch)
    std::any gravitate(std::vector<std::any> const& args); //direction to move source until adjacent to destination
    //Indices inbox(Patch)
    std::any inbox(std::vector<std::any> const& args); //inbox for patch
    //Indices outbox(Patch)
    std::any outbox(std::vector<std::any> const& args); //outbox for patch
    //Indices box(Patch)
    //Indices box(IntegerTuplePair)
    std::any box(std::vector<std::any> const& args); //outline of patch
    //Indices shoot(IntegerTuple, IntegerTuple)
    std::any shoot(std::vector<std::any> const& args); //line from starting point and direction
    //Indices occurrences(Grid, Object)
    std::any occurrences(std::vector<std::any> const& args); //locations of occurrences of object in grid
    //Objects frontiers(Grid)
    std::any frontiers(std::vector<std::any> const& args); //set of frontiers
    //Grid compress(Grid)
    std::any compress(std::vector<std::any> const& args); //removes frontiers from grid
    //Integer hperiod(Object)
    std::any hperiod(std::vector<std::any> const& args); //horizontal periodicity
    //Integer vperiod(Object)
    std::any vperiod(std::vector<std::any> const& args); //vertical periodicity

    std::string type(std::type_index const& t);
}

#endif // AICPP_HODEL_H
