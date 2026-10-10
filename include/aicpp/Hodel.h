#ifndef AICPP_HODEL_H
#define AICPP_HODEL_H

#include <set>
#include <stdexcept>
#include <variant>
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

    class IdentityObjects : public std::runtime_error
    {
        public:
            IdentityObjects(std::string const& name) : std::runtime_error{name}
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

    class InvalidIntegerVector : public std::runtime_error
    {
        public:
            InvalidIntegerVector(std::string const& name) : std::runtime_error{name}
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

    class InvalidContainer : public std::runtime_error
    {
            public:
            InvalidContainer(std::string const& name) : std::runtime_error{name}
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

    enum class Type
    {
        Boolean,
        Integer,
        IntegerTuple,
        IntegerSet,
        Grid,
        Cell,
        Object,
        Objects,
        Indices,
        IndicesSet,
        GridVector,
        IntegerVector,
        IndicesVector,
        ObjectVector,
        ObjectsVector
    };

    using Value = std::variant<
        hodel::Boolean,
        hodel::Integer,
        hodel::IntegerTuple,
        hodel::IntegerSet,
        hodel::Grid,
        hodel::Cell,
        hodel::Object,
        hodel::Objects,
        hodel::Indices,
        hodel::IndicesSet,
        hodel::GridVector,
        hodel::IntegerVector,
        hodel::IndicesVector,
        hodel::ObjectVector,
        hodel::ObjectsVector
    >;

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

    IntegerTuple constexpr DOWN = {1, 0};
    IntegerTuple constexpr RIGHT = {0, 1};
    IntegerTuple constexpr UP = {-1, 0};
    IntegerTuple constexpr LEFT = {0, -1};

    IntegerTuple constexpr ORIGIN = {0, 0};
    IntegerTuple constexpr UNITY = {1, 1};
    IntegerTuple constexpr NEG_UNITY = {-1, -1};
    IntegerTuple constexpr UP_RIGHT = {-1, 1};
    IntegerTuple constexpr DOWN_LEFT = {1, -1};

    IntegerTuple constexpr ZERO_BY_TWO = {0, 2};
    IntegerTuple constexpr TWO_BY_ZERO = {2, 0};
    IntegerTuple constexpr TWO_BY_TWO = {2, 2};
    IntegerTuple constexpr THREE_BY_THREE = {3, 3};

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
    IntegerVector interval(Integer start, Integer const& stop, Integer const& step); //range
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
    Object normalize(Object const& patch); //moves upper left corner to origin
    Indices normalize(Indices const& patch); //moves upper left corner to origin
    Indices dneighbors(IntegerTuple const& loc); //directly adjacent indices
    Indices ineighbors(IntegerTuple const& loc); //diagonally adjacent indices
    Indices neighbors(IntegerTuple const& loc); //adjacent indices
    Object recolor(Integer const& value, Object const& patch); //recolor patch
    Object recolor(Integer const& value, Indices const& patch); //recolor patch
    Boolean square(Grid const& piece); //whether the piece forms a square
    Boolean square(Object const& piece); //whether the piece forms a square
    Boolean square(Indices const& piece); //whether the piece forms a square
    Boolean vline(Object const& patch); //whether the piece forms a vertical line
    Boolean vline(Indices const& patch); //whether the piece forms a vertical line
    Boolean hline(Object const& patch); //whether the piece forms a horizontal line
    Boolean hline(Indices const& patch); //whether the piece forms a horizontal line
    Integer height(Grid const& piece); //height of grid or patch
    Integer height(Object const& piece); //height of grid or patch
    Integer height(Indices const& piece); //height of grid or patch
    Integer width(Grid const& piece); //width of grid or patch
    Integer width(Object const& piece); //width of grid or patch
    Integer width(Indices const& piece); //width of grid or patch
    IntegerTuple shape(Grid const& piece); //height and width of grid or patch
    IntegerTuple shape(Object const& piece); //height and width of grid or patch
    IntegerTuple shape(Indices const& piece); //height and width of grid or patch
    Boolean portrait(Grid const& piece); //whether height is greater than width 
    Boolean portrait(Object const& piece); //whether height is greater than width 
    Boolean portrait(Indices const& piece); //whether height is greater than width
    Boolean branch(Boolean const& condition, Boolean const& a, Boolean const& b); //if else branching
    Integer branch(Boolean const& condition, Integer const& a, Integer const& b); //if else branching
    IntegerTuple branch(Boolean const& condition, IntegerTuple const& a, IntegerTuple const& b); //if else branching
    Indices branch(Boolean const& condition, Indices const& a, Indices const& b); //if else branching
    Object branch(Boolean const& condition, Object const& a, Object const& b); //if else branching
    Grid branch(Boolean const& condition, Grid const& a, Grid const& b); //if else branching
    GridVector branch(Boolean const& condition, GridVector const& a, GridVector const& b); //if else branching
    IntegerVector branch(Boolean const& condition, IntegerVector const& a, IntegerVector const& b); //if else branching
    IndicesSet branch(Boolean const& condition, IndicesSet const& a, IndicesSet const& b); //if else branching
    IntegerSet branch(Boolean const& condition, IntegerSet const& a, IntegerSet const& b); //if else branching
    Objects branch(Boolean const& condition, Objects const& a, Objects const& b); //if else branching
    ObjectVector branch(Boolean const& condition, ObjectVector const& a, ObjectVector const& b); //if else branching
    ObjectsVector branch(Boolean const& condition, ObjectsVector const& a, ObjectsVector const& b); //if else branching
    IndicesVector branch(Boolean const& condition, IndicesVector const& a, IndicesVector const& b); //if else branching
    Integer color(Object const& object); //color of object
    Object toobject(Object const& patch, Grid const& grid); //object from patch and grid
    Object toobject(Indices const& patch, Grid const& grid); //object from patch and grid
    Object asobject(Grid const &grid); //conversion of grid to object
    Integer mostcolor(Grid const& element); //most common color
    Integer mostcolor(Object const& element); //most common color
    Integer leastcolor(Grid const& element); //least common color
    Integer leastcolor(Object const& element); //least common color
    Indices ofcolor(Grid const& grid, Integer const& value); //indices of all grid cells with value
    Integer colorcount(Grid const& element, Integer const& value); //number of cells with color
    Integer colorcount(Object const& element, Integer const& value); //number of cells with color
    Objects colorfilter(Objects const& objs, Integer const& value); //filter object by color
    Objects objects(Grid const& grid, Boolean const& univalued, Boolean const& diagonal, Boolean const& without_bg); //objects occurring on the grid
    Objects partition(Grid const& grid); //each cell with the same value part of the same object
    Objects fgpartition(Grid const& grid); //each cell with the same value part of the same object without background
    Indices asindices(Grid const& grid); //indices of all grid cells
    Boolean equality(Boolean const& a, Boolean const& b); //equality
    Boolean equality(Integer const& a, Integer const& b); //equality
    Boolean equality(IntegerTuple const& a, IntegerTuple const& b); //equality
    Boolean equality(Indices const& a, Indices const& b); //equality
    Boolean equality(Object const& a, Object const& b); //equality
    Boolean equality(Grid const& a, Grid const& b); //equality
    Boolean equality(GridVector const& a, GridVector const& b); //equality
    Boolean equality(IntegerVector const& a, IntegerVector const& b); //equality
    Boolean equality(IndicesSet const& a, IndicesSet const& b); //equality
    Boolean equality(IntegerSet const& a, IntegerSet const& b); //equality
    Boolean equality(Objects const& a, Objects const& b); //equality
    Boolean equality(ObjectVector const& a, ObjectVector const& b); //equality
    Boolean equality(ObjectsVector const& a, ObjectsVector const& b); //equality
    Boolean equality(IndicesVector const& a, IndicesVector const& b); //equality
    Boolean hmatching(Indices const& a, Indices const& b); //whether there exists a row for which both patches have cells
    Boolean hmatching(Object const& a, Indices const& b); //whether there exists a row for which both patches have cells
    Boolean hmatching(Indices const& a, Object const& b); //whether there exists a row for which both patches have cells
    Boolean hmatching(Object const& a, Object const& b); //whether there exists a row for which both patches have cells
    Boolean vmatching(Indices const& a, Indices const& b); //whether there exists a column for which both patches have cells
    Boolean vmatching(Object const& a, Indices const& b); //whether there exists a column for which both patches have cells
    Boolean vmatching(Indices const& a, Object const& b); //whether there exists a column for which both patches have cells
    Boolean vmatching(Object const& a, Object const& b); //whether there exists a column for which both patches have cells
    Integer manhattan(Indices const& a, Indices const& b); //closest manhattan distance between two patches
    Integer manhattan(Object const& a, Indices const& b); //closest manhattan distance between two patches
    Integer manhattan(Indices const& a, Object const& b); //closest manhattan distance between two patches
    Integer manhattan(Object const& a, Object const& b); //closest manhattan distance between two patches
    Boolean adjacent(Indices const& a, Indices const& b); //whether two patches are adjacent
    Boolean adjacent(Object const& a, Indices const& b); //whether two patches are adjacent
    Boolean adjacent(Indices const& a, Object const& b); //whether two patches are adjacent
    Boolean adjacent(Object const& a, Object const& b); //whether two patches are adjacent
    Boolean bordering(Indices const& patch, Grid const grid); //whether a patch is adjacent to a grid border
    Boolean bordering(Object const& patch, Grid const grid); //whether a patch is adjacent to a grid border
    IntegerTuple centerofmass(Indices const &patch); //center of mass
    IntegerTuple centerofmass(Object const &patch); //center of mass
    IntegerSet palette(Grid const& element); //colors occurring in object or grid
    IntegerSet palette(Object const& element); //colors occurring in object or grid
    Integer numcolors(Grid const& element); //number of colors occurring in object or grid
    Integer numcolors(Object const& element); //number of colors occurring in object or grid
    Grid fill(Grid const& grid, Integer const& value, Indices const& patch); //fill value at indices
    Grid fill(Grid const& grid, Integer const& value, Object const& patch); //fill value at indices
    Grid paint(Grid const& grid, Object const& obj); //paint object to grid
    Grid underfill(Grid const& grid, Integer const& value, Indices const& patch); //fill value at indices that are background
    Grid underfill(Grid const& grid, Integer const& value, Object const& patch); //fill value at indices that are background
    Grid underpaint(Grid const& grid, Object const& obj); //paint object to grid where there is background
    IntegerTuple center(Indices const& patch); //center of the patch
    IntegerTuple center(Object const& patch); //center of the patch
    IntegerTuple position(Indices const& a, Indices const& b); //relative position between two patches
    IntegerTuple position(Object const& a, Indices const& b); //relative position between two patches
    IntegerTuple position(Indices const& a, Object const& b); //relative position between two patches
    IntegerTuple position(Object const& a, Object const& b); //relative position between two patches
    Integer index(Grid const& grid, IntegerTuple const& loc); //color at location
    Grid canvas(Integer const& value, IntegerTuple const& dimensions); //grid construction
    Indices corners(Indices const& patch); //indices of corners
    Indices corners(Object const& patch); //indices of corners
    Indices connect(IntegerTuple const& a, IntegerTuple const& b); //line between two points
    Grid cover(Grid const& grid, Indices const& patch); //remove object from grid
    Grid cover(Grid const& grid, Object const& patch); //remove object from grid
    Indices vfrontier(IntegerTuple const& location); //vertical frontier
    Indices hfrontier(IntegerTuple const& location); //horizontal frontier
    Indices backdrop(Object const& patch); //indices in bounding box of patch
    Indices backdrop(Indices const& patch); //indices in bounding box of patch
    Indices delta(Object const& patch); //indices in bounding box but not part of patch
    Indices delta(Indices const& patch); //indices in bounding box but not part of patch
    IntegerTuple gravitate(Indices const& source, Indices const& destination); //direction to move source until adjacent to destination
    IntegerTuple gravitate(Object const& source, Indices const& destination); //direction to move source until adjacent to destination
    IntegerTuple gravitate(Indices const& source, Object const& destination); //direction to move source until adjacent to destination
    IntegerTuple gravitate(Object const& source, Object const& destination); //direction to move source until adjacent to destination
    Indices inbox(Object const& patch); //inbox for patch
    Indices inbox(Indices const& patch); //inbox for patch
    Indices outbox(Object const& patch); //outbox for patch
    Indices outbox(Indices const& patch); //outbox for patch
    Indices box(Object const& patch); //outline of patch
    Indices box(Indices const& patch); //outline of patch
    Indices shoot(IntegerTuple const& start, IntegerTuple const& direction); //line from starting point and direction
    Indices occurrences(Grid const& grid, Object const& obj); //locations of occurrences of object in grid
    Objects frontiers(Grid const& grid); //set of frontiers
    Integer hperiod(Object const& obj); //horizontal periodicity
    Integer vperiod(Object const& obj); //vertical periodicity
    Grid pair(IntegerVector const& a, IntegerVector const &b); //zipping of two tuples
    Integer size(Objects const& container); //cardinality
    Integer size(ObjectVector const& container); //cardinality
    Integer size(ObjectsVector const& container); //cardinality
    Integer size(IndicesSet const& container); //cardinality
    Integer size(IntegerSet const& container); //cardinality
    Integer size(Grid const& container); //cardinality
    Integer size(GridVector const& container); //cardinality
    Integer size(IntegerTuple const& container); //cardinality
    Integer size(IndicesVector const& container); //cardinality
    Boolean identity(Boolean const& x); //identity function
    Integer identity(Integer const& x); //identity function
    IntegerTuple identity(IntegerTuple const& x); //identity function
    Indices identity(Indices const& x); //identity function
    Object identity(Object const& x); //identity function
    Grid identity(Grid const& x); //identity function
    GridVector identity(GridVector const& x); //identity function
    IntegerVector identity(IntegerVector const& x); //identity function
    IndicesSet identity(IndicesSet const& x); //identity function
    IntegerSet identity(IntegerSet const& x); //identity function
    Objects identity(Objects const& x); //identity function
    ObjectVector identity(ObjectVector const& x); //identity function
    ObjectsVector identity(ObjectsVector const& x); //identity function
    IndicesVector identity(IndicesVector const& x); //identity function
    Integer first(IntegerTuple const& x); //first item of container
    IntegerTuple first(Indices const& x); //first item of container
    Cell first(Object const& x); //first item of container
    IntegerVector first(Grid const& x); //first item of container
    Grid first(GridVector const& x); //first item of container
    Integer first(IntegerVector const& x); //first item of container
    Indices first(IndicesSet const& x); //first item of container
    Integer first(IntegerSet const& x); //first item of container
    Object first(Objects const& x); //first item of container
    Object first(ObjectVector const& x); //first item of container
    Objects first(ObjectsVector const& x); //first item of container
    Indices first(IndicesVector const& x); //first item of container
    Integer last(IntegerTuple const& x); //last item of container
    IntegerTuple last(Indices const& x); //last item of container
    Cell last(Object const& x); //last item of container
    IntegerVector last(Grid const& x); //last item of container
    Grid last(GridVector const& x); //last item of container
    Integer last(IntegerVector const& x); //last item of container
    Indices last(IndicesSet const& x); //last item of container
    Integer last(IntegerSet const& x); //last item of container
    Object last(Objects const& x); //last item of container
    Object last(ObjectVector const& x); //last item of container
    Objects last(ObjectsVector const& x); //last item of container
    Indices last(IndicesVector const& x); //last item of container
    Indices insert(IntegerTuple const& value, Indices const& container); //insert item into container
    Object insert(Cell const& value, Object const& container); //insert item into container
    Grid insert(IntegerVector const& value, Grid const& container); //insert item into container
    GridVector insert(Grid const& value, GridVector const& container); //insert item into container
    IntegerVector insert(Integer const& value, IntegerVector const& container); //insert item into container
    IndicesSet insert(Indices const& value, IndicesSet const& container); //insert item into container
    IntegerSet insert(Integer const& value, IntegerSet const& container); //insert item into container
    Objects insert(Object const& value, Objects const& container); //insert item into container
    ObjectVector insert(Object const& value, ObjectVector const& container); //insert item into container
    ObjectsVector insert(Objects const& value, ObjectsVector const& container); //insert item into container
    IndicesVector insert(Indices const& value, IndicesVector const& container); //insert item into container
    Indices remove(IntegerTuple const& value, Indices const& container); //remove item from container
    Object remove(Cell const& value, Object const& container); //remove item from container
    Grid remove(IntegerVector const& value, Grid const& container); //remove item from container
    GridVector remove(Grid const& value, GridVector const& container); //remove item from container
    IntegerVector remove(Integer const& value, IntegerVector const& container); //remove item from container
    IndicesSet remove(Indices const& value, IndicesSet const& container); //remove item from container
    IntegerSet remove(Integer const& value, IntegerSet const& container); //remove item from container
    Objects remove(Object const& value, Objects const& container); //remove item from container
    ObjectVector remove(Object const& value, ObjectVector const& container); //remove item from container
    ObjectsVector remove(Objects const& value, ObjectsVector const& container); //remove item from container
    IndicesVector remove(Indices const& value, IndicesVector const& container); //remove item from container
    IntegerTuple other(Indices const& container, IntegerTuple const& value); //other value in the container
    Cell other(Object const& container, Cell const& value); //other value in the container
    IntegerVector other(Grid const& container, IntegerVector const& value); //other value in the container
    Grid other(GridVector const& container, Grid const& value); //other value in the container
    Integer other(IntegerVector const& container, Integer const& value); //other value in the container
    Indices other(IndicesSet const& container, Indices const& value); //other value in the container
    Integer other(IntegerSet const& container, Integer const& value); //other value in the container
    Object other(Objects const& container, Object const& value); //other value in the container
    Object other(ObjectVector const& container, Object const& value); //other value in the container
    Objects other(ObjectsVector const& container, Objects const& value); //other value in the container
    Indices other(IndicesVector const& container, Indices const& value); //other value in the container
    Indices initset(IntegerTuple const& value); //initialize container
    Object initset(Cell const& value); //initialize container
    Grid initset(IntegerVector const& value); //initialize container
    GridVector initset(Grid const& value); //initialize container
    IndicesSet initset(Indices const& value); //initialize container
    IntegerSet initset(Integer const& value); //initialize container
    Objects initset(Object const& value); //initialize container
    ObjectsVector initset(Objects const& value); //initialize container
    IntegerVector totuple(IntegerTuple const& container); //conversion to tuple
    IntegerVector totuple(IntegerSet const& container); //conversion to tuple
    IndicesVector totuple(IndicesSet const& container); //conversion to tuple
    ObjectVector totuple(Objects const& container); //conversion to tuple
}

#endif // AICPP_HODEL_H
