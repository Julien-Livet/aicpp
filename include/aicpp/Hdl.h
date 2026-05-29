#ifndef AICPP_HDL_H
#define AICPP_HDL_H

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
    typedef std::pair<Integer, IntegerTuple> Cell;
    typedef std::set<Cell> Object;
    typedef std::set<Object> Objects;
    typedef std::set<IntegerTuple> Indices;
    typedef std::set<Indices> IndicesSet;
    typedef std::variant<Object, Indices> Patch;
    typedef std::variant<Object, Grid> Element;
    typedef std::variant<Grid, Patch> Piece;
    typedef std::pair<UnsignedInteger, UnsignedInteger> Size;

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

    UnsignedInteger constexpr U_ONE = 1;
    UnsignedInteger constexpr U_TWO = 2;
    UnsignedInteger constexpr U_THREE = 3;
    UnsignedInteger constexpr U_FOUR = 4;
    UnsignedInteger constexpr U_FIVE = 5;
    UnsignedInteger constexpr U_SIX = 6;
    UnsignedInteger constexpr U_SEVEN = 7;
    UnsignedInteger constexpr U_EIGHT = 8;
    UnsignedInteger constexpr U_NINE = 9;
    UnsignedInteger constexpr U_TEN = 10;

    IntegerTuple constexpr DOWN = std::make_pair<Integer, Integer>(1, 0);
    IntegerTuple constexpr RIGHT = std::make_pair<Integer, Integer>(0, 1);
    IntegerTuple constexpr UP = std::make_pair<Integer, Integer>(-1, 0);
    IntegerTuple constexpr LEFT = std::make_pair<Integer, Integer>(0, -1);

    IntegerTuple constexpr ORIGIN = std::make_pair<Integer, Integer>(0, 0);
    IntegerTuple constexpr UNITY = std::make_pair<Integer, Integer>(1, 1);
    IntegerTuple constexpr NEG_UNITY = std::make_pair<Integer, Integer>(-1, -1);
    IntegerTuple constexpr UP_RIGHT = std::make_pair<Integer, Integer>(-1, 1);
    IntegerTuple constexpr DOWN_LEFT = std::make_pair<Integer, Integer>(1, -1);

    Size constexpr ZERO_BY_TWO = std::make_pair<UnsignedInteger, UnsignedInteger>(0, 2);
    Size constexpr TWO_BY_ZERO = std::make_pair<Integer, UnsignedInteger>(2, 0);
    Size constexpr TWO_BY_TWO = std::make_pair<UnsignedInteger, UnsignedInteger>(2, 2);
    Size constexpr THREE_BY_THREE = std::make_pair<UnsignedInteger, UnsignedInteger>(3, 3);

    //std::any identity(std::vector<std::any> const& args); //Any(Any): identity function
    Numerical add(Numerical const& a, Numerical const& b); //addition
    Numerical subtract(Numerical const& a, Numerical const& b); //subtraction
    Numerical multiply(Numerical const& a, Numerical const& b); //multiplication
    Numerical divide(Numerical const& a, Numerical const& b); //floor division
    Numerical invert(Numerical const& n); //inversion with respect to addition
    Boolean even(Integer const& n); //evenness
    Numerical double_(Numerical const& n); //scaling by two
    Numerical halve(Numerical const& n); //scaling by one half
    Boolean flip(Boolean const& b); //logical not
/*
    std::any equality(std::vector<std::any> const& args); //Any(Any): equality
    std::any contained(std::vector<std::any> const& args); //Boolean(Any, Container): element of
    std::any combine(std::vector<std::any> const& args); //Container(Container, Container): union
    std::any intersection(std::vector<std::any> const& args); //FrozenSet(FrozenSet, FrozenSet): returns the intersection of two containers
    std::any difference(std::vector<std::any> const& args); //FrozenSet(FrozenSet, FrozenSet): set difference
    std::any dedupe(std::vector<std::any> const& args); //Tuple(Tuple): remove duplicates
    std::any order(std::vector<std::any> const& args); //Tuple(Container, Callable): order container by custom key
    std::any repeat(std::vector<std::any> const& args); //Tuple(Any, Integer): repetition of item within vector
*/
    Boolean greater(Integer const& a, Integer const& b); //greater
    //std::any size(std::vector<std::any> const& args); //UnsignedInteger(Container): cardinality
    Integer maximum(IntegerSet const& container); //maximum
    Integer minimum(IntegerSet const& container); //minimum
    //std::any initset(std::vector<std::any> const& args); //FrozenSet(Any): initialize container
    Boolean both(Boolean const& a, Boolean const& b); //logical and
    Boolean either(Boolean const& a, Boolean const& b); //logical or
    Numerical increment(Numerical const& x); //incrementing
    Numerical decrement(Numerical const& x); //decrementing
    Numerical crement(Numerical const& x); //incrementing positive and decrementing negative
    Numerical sign(Numerical const& x); //sign
    Boolean positive(Integer const& x); //positive
    IntegerTuple toivec(Integer const& i); //vector pointing vertically
    IntegerTuple tojvec(Integer const& j); //vector pointing horizontally
/*
    std::any totuple(std::vector<std::any> const& args); //Tuple(FrozenSet): conversion to tuple
    std::any first(std::vector<std::any> const& args); //Any(Container): first item of container
    std::any last(std::vector<std::any> const& args); //Any(Container): last item of container
*/
    std::vector<Integer> interval(Integer start, Integer const& stop, Integer const& step); //range
    IntegerTuple astuple(Integer const& a, Integer const& b); //constructs a tuple
    IntegerTuple ulcorner(Patch const& patch); //index of upper left corner
    IntegerTuple urcorner(Patch const& patch); //index of upper right corner
    IntegerTuple llcorner(Patch const& patch); //index of lower left corner
    IntegerTuple lrcorner(Patch const& patch); //index of lower right corner
    Grid crop(Grid const& grid, IntegerTuple const& start, Size const& dims); //subgrid specified by start and dimension
    Indices toindices(Patch const& patch); //indices of object cells
    Patch shift(Patch const& patch, IntegerTuple const& directions); //shift patch
    Integer uppermost(Patch const& patch); //row index of uppermost occupied cell
    Integer lowermost(Patch const& patch); //row index of lowermost occupied cell
    Integer leftmost(Patch const& patch); //column index of leftmost occupied cell
    Integer rightmost(Patch const& patch); //column index of rightmost occupied cell
    Grid rot90(Grid const& grid); //quarter clockwise rotation
    Grid rot180(Grid const& grid); //half rotation
    Grid rot270(Grid const& grid); //quarter anticlockwise rotation
    Piece hmirror(Piece const& piece); //mirroring along horizontal
    Piece vmirror(Piece const& piece); //mirroring along vertical
    Piece dmirror(Piece const& piece); //mirroring along diagonal
    Piece cmirror(Piece const& piece); //mirroring along counterdiagonal
    Grid hupscale(Grid const& grid, UnsignedInteger const& factor); //upscale grid horizontally
    Grid vupscale(Grid const& grid, UnsignedInteger const& factor); //upscale grid vertically
    Element upscale(Element const& element, UnsignedInteger const& factor); //upscale object or grid
    Grid downscale(Grid const& grid, UnsignedInteger const& factor); //downscale object or grid
    Grid hconcat(Grid const& a, Grid const& b); //concatenate two grids horizontally
    Grid vconcat(Grid const& a, Grid const& b); //concatenate two grids vertically
    Grid replace(Grid const& grid, Integer const& replacee, Integer const& replacer); //color substitution
    Grid switch_(Grid const& grid, Integer const& a, Integer const& b); //color switching
    Grid tophalf(Grid const& grid); //upper half of grid
    Grid bottomhalf(Grid const& grid); //lower half of grid
    Grid lefthalf(Grid const& grid); //left half of grid
    Grid righthalf(Grid const& grid); //right half of grid
}

#endif // AICPP_HDL_H
