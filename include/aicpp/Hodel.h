#ifndef AICPP_HODEL_H
#define AICPP_HODEL_H

#include <set>
#include <stdexcept>
#include <vector>

namespace hodel
{
    class IdentityIntegerTuple : public std::runtime_error
    {
        public:
            IdentityIntegerTuple(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class IdentityInteger : public std::runtime_error
    {
        public:
            IdentityInteger(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class IdentityObject : public std::runtime_error
    {
        public:
            IdentityObject(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class IdentityIndices : public std::runtime_error
    {
        public:
            IdentityIndices(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class InvalidIntegerTuple : public std::runtime_error
    {
        public:
            InvalidIntegerTuple(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class InvalidInteger : public std::runtime_error
    {
        public:
            InvalidInteger(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class EmptyContainer : public std::runtime_error
    {
            public:
            EmptyContainer(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class EmptyIndices : public std::runtime_error
    {
            public:
            EmptyIndices(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class EmptyObject : public std::runtime_error
    {
        public:
            EmptyObject(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class EmptyGrid : public std::runtime_error
    {
        public:
            EmptyGrid(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class InvalidGrid : public std::runtime_error
    {
        public:
            InvalidGrid(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    class IdentityGrid : public std::runtime_error
    {
        public:
            IdentityGrid(std::string const& name) : std::runtime_error{name}
            {
            }
    };

    typedef bool Boolean;
    typedef int16_t Integer;

    struct IntegerTuple : public std::pair<Integer, Integer>
    {
        constexpr IntegerTuple(Integer const& first, Integer const& second) : std::pair<Integer, Integer>(first, second)
        {
        }

        constexpr IntegerTuple() : std::pair<Integer, Integer>(0, 0)
        {
        }

        constexpr IntegerTuple(IntegerTuple const& other) : std::pair<Integer, Integer>(other.first, other.second)
        {
        }

        IntegerTuple& operator=(IntegerTuple const& other)
        {
            this->first = other.first;
            this->second = other.second;

            return *this;
        }

        IntegerTuple& operator+=(IntegerTuple const& other)
        {
            this->first += other.first;
            this->second += other.second;

            return *this;
        }

        IntegerTuple& operator*=(IntegerTuple const& other)
        {
            this->first *= other.first;
            this->second *= other.second;

            return *this;
        }

        IntegerTuple& operator/=(IntegerTuple const& other)
        {
            if (!other.first || !other.second)
                throw std::invalid_argument("Division by zero in IntegerTuple division.");

            this->first /= other.first;
            this->second /= other.second;

            return *this;
        }

        IntegerTuple& operator-=(IntegerTuple const& other)
        {
            this->first -= other.first;
            this->second -= other.second;

            return *this;
        }

        IntegerTuple& operator+=(Integer const& n)
        {
            this->first += n;
            this->second += n;

            return *this;
        }

        IntegerTuple& operator-=(Integer const& n)
        {
            this->first -= n;
            this->second -= n;

            return *this;
        }

        IntegerTuple& operator*=(Integer const& n)
        {
            this->first *= n;
            this->second *= n;

            return *this;
        }

        IntegerTuple& operator/=(Integer const& n)
        {
            if (!n)
                throw std::invalid_argument("Division by zero in IntegerTuple division.");

            this->first /= n;
            this->second /= n;

            return *this;
        }
    };

    typedef std::set<Integer> IntegerSet;
    typedef std::vector<std::vector<Integer> > Grid;
    typedef std::pair<Integer, IntegerTuple> Cell;
    typedef std::set<Cell> Object;
    typedef std::set<Object> Objects;
    typedef std::set<IntegerTuple> Indices;
    typedef std::set<Indices> IndicesSet;
    typedef std::vector<Grid> GridVector;
    typedef std::vector<Integer> IntegerVector;
    typedef std::vector<Indices> IndicesVector;
    typedef std::vector<Object> ObjectVector;
    typedef std::vector<Objects> ObjectsVector;

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

    IntegerTuple constexpr DOWN(1, 0);
    IntegerTuple constexpr RIGHT(0, 1);
    IntegerTuple constexpr UP(-1, 0);
    IntegerTuple constexpr LEFT(0, -1);

    IntegerTuple constexpr ORIGIN(0, 0);
    IntegerTuple constexpr UNITY(1, 1);
    IntegerTuple constexpr NEG_UNITY(-1, -1);
    IntegerTuple constexpr UP_RIGHT(-1, 1);
    IntegerTuple constexpr DOWN_LEFT(1, -1);

    IntegerTuple constexpr ZERO_BY_TWO(0, 2);
    IntegerTuple constexpr TWO_BY_ZERO(2, 0);
    IntegerTuple constexpr TWO_BY_TWO(2, 2);
    IntegerTuple constexpr THREE_BY_THREE(3, 3);

    Integer add(Integer const& a, Integer const& b); //addition
    IntegerTuple add(IntegerTuple const& a, Integer const& b); //addition
    IntegerTuple add(Integer const& a, IntegerTuple const& b); //addition
    IntegerTuple add(IntegerTuple const& a, IntegerTuple const& b); //addition
    Integer subtract(Integer const& a, Integer const& b); //subtraction
    IntegerTuple subtract(IntegerTuple const& a, Integer const& b); //subtraction
    IntegerTuple subtract(Integer const& a, IntegerTuple const& b); //subtraction
    IntegerTuple subtract(IntegerTuple const& a, IntegerTuple const& b); //subtraction
    Integer multiply(Integer const& a, Integer const& b); //multiplication
    IntegerTuple multiply(IntegerTuple const& a, Integer const& b); //multiplication
    IntegerTuple multiply(Integer const& a, IntegerTuple const& b); //multiplication
    IntegerTuple multiply(IntegerTuple const& a, IntegerTuple const& b); //multiplication
    Integer divide(Integer const& a, Integer const& b); //floor division
    IntegerTuple divide(IntegerTuple const& a, Integer const& b); //floor division
    IntegerTuple divide(IntegerTuple const& a, IntegerTuple const& b); //floor division
    Integer invert(Integer const& n); //inversion with respect to addition
    IntegerTuple invert(IntegerTuple const& n); //inversion with respect to addition
    Boolean even(Integer const& n); //evenness
    Integer double_(Integer const& n); //scaling by two
    IntegerTuple double_(IntegerTuple const& n); //scaling by two
    Integer halve(Integer const& n); //scaling by one half
    IntegerTuple halve(IntegerTuple const& n); //scaling by one half
    Boolean flip(Boolean const& b); //logical not
    Boolean greater(Integer const& a, Integer const& b); //greater
    Integer maximum(IntegerSet const& container); //maximum
    Integer maximum(IntegerVector const& container); //maximum
    Integer minimum(IntegerSet const& container); //minimum
    Integer minimum(IntegerVector const& container); //minimum
    Boolean both(Boolean const& a, Boolean const& b); //logical and
    Boolean either(Boolean const& a, Boolean const& b); //logical or
    Integer increment(Integer const& x); //incrementing
    IntegerTuple increment(IntegerTuple const& x); //incrementing
    Integer decrement(Integer const& x); //decrementing
    IntegerTuple decrement(IntegerTuple const& x); //decrementing
    Integer crement(Integer const& x); //incrementing positive and decrementing negative
    IntegerTuple crement(IntegerTuple const& x); //incrementing positive and decrementing negative
    Integer sign(Integer const& x); //sign
    IntegerTuple sign(IntegerTuple const& x); //sign
    Boolean positive(Integer const& x); //positive
    IntegerTuple toivec(Integer const& i); //vector pointing vertically
    IntegerTuple tojvec(Integer const& j); //vector pointing horizontally
    std::vector<Integer> interval(Integer start, Integer const& stop, Integer const& step); //range
    IntegerTuple astuple(Integer const& a, Integer const& b); //constructs a tuple
    IntegerTuple ulcorner(Object const& patch); //index of upper left corner
    IntegerTuple ulcorner(Indices const& patch); //index of upper left corner
    IntegerTuple urcorner(Object const& patch); //index of upper right corner
    IntegerTuple urcorner(Indices const& patch); //index of upper right corner
    IntegerTuple llcorner(Object const& patch); //index of lower left corner
    IntegerTuple llcorner(Indices const& patch); //index of lower left corner
    IntegerTuple lrcorner(Object const& patch); //index of lower right corner
    IntegerTuple lrcorner(Indices const& patch); //index of lower right corner
    Grid crop(Grid const& grid, IntegerTuple const& start, IntegerTuple const& dims); //subgrid specified by start and dimension
    Indices toindices(Object const& patch); //indices of object cells
    Object shift(Object const& patch, IntegerTuple const& directions); //shift patch
    Indices shift(Indices const& patch, IntegerTuple const& directions); //shift patch
    Integer uppermost(Object const& patch); //row index of uppermost occupied cell
    Integer uppermost(Indices const& patch); //row index of uppermost occupied cell
    Integer lowermost(Object const& patch); //row index of lowermost occupied cell
    Integer lowermost(Indices const& patch); //row index of lowermost occupied cell
    Integer leftmost(Object const& patch); //column index of leftmost occupied cell
    Integer leftmost(Indices const& patch); //column index of leftmost occupied cell
    Integer rightmost(Object const& patch); //column index of rightmost occupied cell
    Integer rightmost(Indices const& patch); //column index of rightmost occupied cell
    Grid rot90(Grid const& grid); //quarter clockwise rotation
    Grid rot180(Grid const& grid); //half rotation
    Grid rot270(Grid const& grid); //quarter anticlockwise rotation
    Grid hmirror(Grid const& piece); //mirroring along horizontal
    Object hmirror(Object const& piece); //mirroring along horizontal
    Indices hmirror(Indices const& piece); //mirroring along horizontal
    Grid vmirror(Grid const& piece); //mirroring along vertical
    Object vmirror(Object const& piece); //mirroring along vertical
    Indices vmirror(Indices const& piece); //mirroring along vertical
    Grid dmirror(Grid const& piece); //mirroring along diagonal
    Object dmirror(Object const& piece); //mirroring along diagonal
    Indices dmirror(Indices const& piece); //mirroring along diagonal
    Grid cmirror(Grid const& piece); //mirroring along counterdiagonal
    Object cmirror(Object const& piece); //mirroring along counterdiagonal
    Indices cmirror(Indices const& piece); //mirroring along counterdiagonal
    Grid hupscale(Grid const& grid, Integer const& factor); //upscale grid horizontally
    Grid vupscale(Grid const& grid, Integer const& factor); //upscale grid vertically
    Grid upscale(Grid const& element, Integer const& factor); //upscale object or grid
    Object upscale(Object const& element, Integer const& factor); //upscale object or grid
    Grid downscale(Grid const& grid, Integer const& factor); //downscale grid
    Grid hconcat(Grid const& a, Grid const& b); //concatenate two grids horizontally
    Grid vconcat(Grid const& a, Grid const& b); //concatenate two grids vertically
    Grid replace(Grid const& grid, Integer const& replacee, Integer const& replacer); //color substitution
    Grid switch_(Grid const& grid, Integer const& a, Integer const& b); //color switching
    Grid tophalf(Grid const& grid); //upper half of grid
    Grid bottomhalf(Grid const& grid); //lower half of grid
    Grid lefthalf(Grid const& grid); //left half of grid
    Grid righthalf(Grid const& grid); //right half of grid
    Grid trim(Grid const& grid); //trim border of grid
    Grid compress(Grid const& grid); //removes frontiers from grid
}

#endif // AICPP_HODEL_H
