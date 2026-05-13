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

    std::any identity(std::vector<std::any> const& args); //Any(Any): identity function
    std::any add(std::vector<std::any> const& args); //Numerical(Numerical, Numerical): addition
    std::any subtract(std::vector<std::any> const& args); //Numerical(Numerical, Numerical): subtraction
    std::any multiply(std::vector<std::any> const& args); //Numerical(Numerical, Numerical): multiplication
    std::any divide(std::vector<std::any> const& args); //Numerical(Numerical, Numerical): floor division
    std::any invert(std::vector<std::any> const& args); //Numerical(Numerical): inversion with respect to addition
    std::any even(std::vector<std::any> const& args); //Integer(Boolean): evenness
    std::any double_(std::vector<std::any> const& args); //Integer(Integer): scaling by two
    std::any halve(std::vector<std::any> const& args); //Integer(Integer): scaling by one half
    std::any flip(std::vector<std::any> const& args); //Boolean(Boolean): logical not
    std::any equality(std::vector<std::any> const& args); //Any(Any): equality
    std::any contained(std::vector<std::any> const& args); //Boolean(Any, Container): element of
    std::any combine(std::vector<std::any> const& args); //Container(Container, Container): union
    std::any intersection(std::vector<std::any> const& args); //FrozenSet(FrozenSet, FrozenSet): returns the intersection of two containers
    std::any difference(std::vector<std::any> const& args); //FrozenSet(FrozenSet, FrozenSet): set difference
    std::any dedupe(std::vector<std::any> const& args); //Tuple(Tuple): remove duplicates
    std::any order(std::vector<std::any> const& args); //Tuple(Container, Callable): order container by custom key
    std::any repeat(std::vector<std::any> const& args); //Tuple(Any, Integer): repetition of item within vector
    std::any greater(std::vector<std::any> const& args); //Boolean(Integer, Integer): greater
    std::any size(std::vector<std::any> const& args); //UnsignedInteger(Container): cardinality
    std::any maximum(std::vector<std::any> const& args); //Integer(IntegerSet): maximum
    std::any minimum(std::vector<std::any> const& args); //Integer(IntegerSet): minimum
    std::any initset(std::vector<std::any> const& args); //FrozenSet(Any): initialize container
    std::any both(std::vector<std::any> const& args); //Boolean(Boolean, Boolean): logical and
    std::any either(std::vector<std::any> const& args); //Boolean(Boolean, Boolean): logical or
    std::any increment(std::vector<std::any> const& args); //Numerical(Numerical): incrementing
    std::any decrement(std::vector<std::any> const& args); //Numerical(Numerical): decrementing
    std::any crement(std::vector<std::any> const& args); //Numerical(Numerical): incrementing positive and decrementing negative
    std::any sign(std::vector<std::any> const& args); //Numerical(Numerical): sign
    std::any positive(std::vector<std::any> const& args); //Boolean(Numerical): positive
    std::any toivec(std::vector<std::any> const& args); //IntegerTuple(Integer): vector pointing vertically
    std::any tojvec(std::vector<std::any> const& args); //IntegerTuple(Integer): vector pointing horizontally
    std::any totuple(std::vector<std::any> const& args); //Tuple(FrozenSet): conversion to tuple
    std::any first(std::vector<std::any> const& args); //Any(Container): first item of container
    std::any last(std::vector<std::any> const& args); //Any(Container): last item of container
    std::any interval(std::vector<std::any> const& args); //Tuple(Integer, Integer, Integer): range
    std::any astuple(std::vector<std::any> const& args); //IntegerTuple(Integer, Integer): constructs a tuple
    std::any ulcorner(std::vector<std::any> const& args); // IntegerTuple(Patch): index of upper left corner
    std::any urcorner(std::vector<std::any> const& args); // IntegerTuple(Patch): index of upper right corner
    std::any llcorner(std::vector<std::any> const& args); // IntegerTuple(Patch): index of lower left corner
    std::any lrcorner(std::vector<std::any> const& args); // IntegerTuple(Patch): index of lower right corner
    std::any crop(std::vector<std::any> const& args); //Grid(Grid, IntegerTuple, Size): subgrid specified by start and dimension
    std::any toindices(std::vector<std::any> const& args); //Indices(Patch): indices of object cells
    std::any shift(std::vector<std::any> const& args); //Patch(Patch, IntegerTuple): shift patch
    std::any uppermost(std::vector<std::any> const& args); //Integer(Patch): row index of uppermost occupied cell
    std::any lowermost(std::vector<std::any> const& args); //Integer(Patch): row index of lowermost occupied cell
    std::any leftmost(std::vector<std::any> const& args); //Integer(Patch): column index of leftmost occupied cell
    std::any rightmost(std::vector<std::any> const& args); //Integer(Patch): column index of rightmost occupied cell
    std::any rot90(std::vector<std::any> const& args); //Grid(Grid): quarter clockwise rotation
    std::any rot180(std::vector<std::any> const& args); //Grid(Grid): half rotation
    std::any rot270(std::vector<std::any> const& args); //Grid(Grid): quarter anticlockwise rotation
    std::any hmirror(std::vector<std::any> const& args); //Piece(Piece): mirroring along horizontal
    std::any vmirror(std::vector<std::any> const& args); //Piece(Piece): mirroring along vertical
    std::any dmirror(std::vector<std::any> const& args); //Piece(Piece): mirroring along diagonal
    std::any cmirror(std::vector<std::any> const& args); //Piece(Piece): mirroring along counterdiagonal
    std::any hupscale(std::vector<std::any> const& args); //Grid(Grid, UnsignedInteger): upscale grid horizontally
    std::any vupscale(std::vector<std::any> const& args); //Grid(Grid, UnsignedInteger): upscale grid vertically
    std::any upscale(std::vector<std::any> const& args); //Element(Element, UnsignedInteger): upscale object or grid
    std::any downscale(std::vector<std::any> const& args); //Grid(Grid, UnsignedInteger): downscale object or grid
    std::any hconcat(std::vector<std::any> const& args); //Grid(Grid, Grid): concatenate two grids horizontally
    std::any vconcat(std::vector<std::any> const& args); //Grid(Grid, Grid): concatenate two grids vertically
    std::any replace(std::vector<std::any> const& args); //Grid(Grid, Integer, Integer): color substitution
    std::any switch_(std::vector<std::any> const& args); //Grid(Grid, Integer, Integer): color switching
    std::any tophalf(std::vector<std::any> const& args); //Grid(Grid): upper half of grid
    std::any bottomhalf(std::vector<std::any> const& args); //Grid(Grid): lower half of grid
    std::any lefthalf(std::vector<std::any> const& args); //Grid(Grid): left half of grid
    std::any righthalf(std::vector<std::any> const& args); //Grid(Grid): right half of grid
}

#endif // AICPP_HODEL_H
