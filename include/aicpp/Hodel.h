#ifndef AICPP_HODEL_H
#define AICPP_HODEL_H

#include <any>
#include <functional>
#include <set>
#include <utility>
#include <variant>
#include <vector>

namespace hdl
{
    typedef bool Boolean;
    typedef int Integer;
    typedef unsigned int UnsignedInteger;
    typedef std::pair<Integer, Integer> IntegerTuple;
    typedef std::variant<Integer, IntegerTuple> Numerical;
    typedef std::set<Integer> IntegerSet;
    typedef std::vector<std::vector<Integer> > Grid;
    typedef std::variant<Integer, IntegerTuple> Cell;
    typedef std::set<Cell> Object;
    typedef std::set<Object> Objects;
    typedef std::set<IntegerTuple> Indices;
    typedef std::set<Indices> IndicesSet;
    typedef std::variant<Object, Indices> Patch;
    typedef std::variant<Object, Grid> Element;
    typedef std::variant<Grid, Patch> Piece;
    typedef std::pair<UnsignedInteger, UnsignedInteger> Size;
    typedef IntegerTuple Direction;
    
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

    Direction constexpr DOWN = std::make_pair<Integer, Integer>(1, 0);
    Direction constexpr RIGHT = std::make_pair<Integer, Integer>(0, 1);
    Direction constexpr UP = std::make_pair<Integer, Integer>(-1, 0);
    Direction constexpr LEFT = std::make_pair<Integer, Integer>(0, -1);

    Direction constexpr ORIGIN = std::make_pair<Integer, Integer>(0, 0);
    Direction constexpr UNITY = std::make_pair<Integer, Integer>(1, 1);
    Direction constexpr NEG_UNITY = std::make_pair<Integer, Integer>(-1, -1);
    Direction constexpr UP_RIGHT = std::make_pair<Integer, Integer>(-1, 1);
    Direction constexpr DOWN_LEFT = std::make_pair<Integer, Integer>(1, -1);

    Size constexpr ZERO_BY_TWO = std::make_pair<UnsignedInteger, UnsignedInteger>(0, 2);
    Size constexpr TWO_BY_ZERO = std::make_pair<Integer, UnsignedInteger>(2, 0);
    Size constexpr TWO_BY_TWO = std::make_pair<UnsignedInteger, UnsignedInteger>(2, 2);
    Size constexpr THREE_BY_THREE = std::make_pair<UnsignedInteger, UnsignedInteger>(3, 3);

    std::any identity(std::any const& x); //Any(Any): identity function
    std::any add(std::any const& a, std::any const& b); //Numerical(Numerical, Numerical): addition
    std::any subtract(std::any const& a, std::any const& b); //Numerical(Numerical, Numerical): subtraction
    std::any multiply(std::any const& a, std::any const& b); //Numerical(Numerical, Numerical): multiplication
    std::any divide(std::any const& a, std::any const& b); //Numerical(Numerical, Numerical): floor division
    std::any invert(std::any const& n); //Numerical(Numerical): inversion with respect to addition
    std::any even(std::any const& n); //Integer(Boolean): evenness
    std::any double_(std::any const& n); //Integer(Integer): scaling by two
    std::any halve(std::any const& n); //Integer(Integer): scaling by one half
    std::any flip(std::any const& b); //Boolean(Boolean): logical not
    std::any equality(std::any const& a, std::any const& b); //Any(Any): equality
    std::any contained(std::any const& value, std::any const& container); //Boolean(Any, Container): element of
    std::any combine(std::any const& a, std::any const& b); //Container(Container, Container): union
    std::any intersection(std::any const& a, std::any const& b); //FrozenSet(FrozenSet, FrozenSet): returns the intersection of two containers
    std::any difference(std::any const& a, std::any const& b); //FrozenSet(FrozenSet, FrozenSet): set difference
    std::any dedupe(std::any const& tup); //Tuple(Tuple): remove duplicates
    std::any order(std::any const& container, std::any const& compfunc); //Tuple(Container, Callable): order container by custom key
    std::any repeat(std::any const& item, std::any const& num); //Tuple(Any, Integer): repetition of item within vector
    std::any greater(std::any const& a, std::any const& b); //Boolean(Integer, Integer): greater
    std::any size(std::any const& container); //UnsignedInteger(Container): cardinality
    std::any maximum(std::any const& container); //Integer(IntegerSet): maximum
    std::any minimum(std::any const& container); //Integer(IntegerSet): minimum
    std::any initset(std::any const& value); //FrozenSet(Any): initialize container
    std::any both(std::any const& a, std::any const& b); //Boolean(Boolean, Boolean): logical and
    std::any either(std::any const& a, std::any const& b); //Boolean(Boolean, Boolean): logical or
    std::any increment(std::any const& x); //Numerical(Numerical): incrementing
    std::any decrement(std::any const& x); //Numerical(Numerical): decrementing
    std::any crement(std::any const& x); //Numerical(Numerical): incrementing positive and decrementing negative
    std::any sign(std::any const& x); //Numerical(Numerical): sign
    std::any positive(std::any const& x); //Boolean(Numerical): positive
    std::any toivec(std::any const& i); //IntegerTuple(Integer): vector pointing vertically
    std::any tojvec(std::any const& j); //IntegerTuple(Integer): vector pointing horizontally
    std::any totuple(std::any const& container); //Tuple(FrozenSet): conversion to tuple
    std::any first(std::any const& container); //Any(Container): first item of container
    std::any last(std::any const& container); //Any(Container): last item of container
    std::any interval(std::any const& start, std::any const& stop, std::any const& step); //Tuple(Integer, Integer, Integer): range
    std::any astuple(std::any const& a, std::any const& b); //IntegerTuple(Integer, Integer): constructs a tuple
}

#endif // AICPP_HODEL_H
