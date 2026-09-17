# ARC-AGI-2

## Benchmark

ARC-AGI-1 was created in 2019 (before the rise of LLMs). It endured five years of global competitions, a 50,000x scale-up of base LLMs, and saw little progress until late 2024, with the introduction of test-time adaptation methods pioneered by ARC Prize 2024 entrants and OpenAI.

ARC-AGI-2 - the next iteration of the benchmark - is designed to stress-test the capabilities of state-of-the-art AI reasoning systems, provide useful signal on AGI progress, and inspire researchers to work on new ideas.

Can you create a system that can reach 85% accuracy?

## aicpp approach

aicpp approaches ARC-AGI-2 as a program synthesis problem.

Given demonstrations:

    input → output

the system searches for an executable DSL program that reproduces
the observed transformations.

## DSL

### Types

- `Boolean`
- `IntegerType`
- `IntegerTuple`
- `Numerical`
- `IntegerSet`
- `GridType`
- `Cell`
- `ObjectType`
- `Objects`
- `IndicesType`
- `IndicesSet`
- `Patch`
- `Element`
- `Piece`

### Constants

- `F`
- `T`
- `ZERO`
- `ONE`
- `TWO`
- `THREE`
- `FOUR`
- `FIVE`
- `SIX`
- `SEVEN`
- `EIGHT`
- `NINE`
- `TEN`
- `NEG_ONE`
- `NEG_TWO`
- `DOWN`
- `RIGHT`
- `UP`
- `LEFT`
- `ORIGIN`
- `UNITY`
- `NEG_UNITY`
- `UP_RIGHT`
- `DOWN_LEFT`
- `ZERO_BY_TWO`
- `TWO_BY_ZERO`
- `TWO_BY_TWO`
- `THREE_BY_THREE`

### Functions

- `identity`: identity function
- `add`: addition
- `subtract`: subtraction
- `multiply`: multiplication
- `divide`: floor division
- `invert`: inversion with respect to addition
- `even`: evenness
- `double_`: scaling by two
- `halve`: scaling by one half
- `flip`: logical not
- `equality`: equality
- `contained`: element of
- `combine`: union
- `intersection`: returns the intersection of two containers
- `difference`: set difference
- `dedupe`: remove duplicates
- `order`: order container by custom key
- `repeat`: repetition of item within vector
- `greater`: greater
- `size`: cardinality
- `merge`: merging
- `maximum`: maximum
- `minimum`: minimum
- `valmax`: maximum by custom function
- `valmin`: minimum by custom function
- `argmax`: largest item by custom order
- `argmin`: smallest item by custom order
- `mostcommon`: most common item
- `leastcommon`: least common item
- `initset`: initialize container
- `both`: logical and
- `either`: logical or
- `increment`: incrementing
- `decrement`: decrementing
- `crement`: incrementing positive and decrementing negative
- `sign`: sign
- `positive`: positive
- `toivec`: vector pointing vertically
- `tojvec`: vector pointing horizontally
- `sfilter`: keep elements in container that satisfy condition
- `mfilter`: filter and merge
- `extract`: first element of container that satisfies condition
- `totuple`: conversion to tuple
- `first`: first item of container
- `last`: last item of container
- `insert`: insert item into container
- `remove`: remove item from container
- `other`: other value in the container
- `interval`: range
- `astuple`: constructs a tuple
- `product`: cartesian product
- `pair`: zipping of two tuples
- `branch`: if else branching
- `compose`: function composition
- `chain`: function composition with three functions
- `matcher`: construction of equality function
- `rbind`: fix the rightmost argument
- `lbind`: fix the leftmost argument
- `power`: power of function
- `fork`: creates a wrapper function
- `apply`: apply function to each item in container
- `rapply`: apply each function in container to value
- `mapply`: apply and merge
- `papply`: apply function on two vectors
- `mpapply`: apply function on two vectors and merge
- `prapply`: apply function on cartesian product
- `mostcolor`: most common color
- `leastcolor`: least common color
- `height`: height of grid or patch
- `width`: width of grid or patch
- `shape`: height and width of grid or patch 
- `portrait`: whether height is greater than width
- `colorcount`: number of cells with color
- `colorfilter`: filter object by color
- `sizefilter`: filter items by size
- `asindices`: indices of all grid cells
- `ofcolor`: indices of all grid cells with value
- `ulcorner`: index of upper left corner
- `urcorner`: index of upper right corner
- `llcorner`: index of lower left corner
- `lrcorner`: index of lower right corner
- `crop`: subgrid specified by start and dimension
- `toindices`: indices of object cells
- `recolor`: recolor patch
- `shift`: shift patch
- `normalize`: moves upper left corner to origin
- `dneighbors`: directly adjacent indices
- `ineighbors`: diagonally adjacent indices
- `neighbors`: adjacent indices
- `objects`: Objects occurring on the grid
- `partition`: each cell with the same value part of the same object
- `fgpartition`: each cell with the same value part of the same object without background
- `uppermost`: row index of uppermost occupied cell
- `lowermost`: row index of lowermost occupied cell
- `leftmost`: column index of leftmost occupied cell
- `rightmost`: column index of rightmost occupied cell
- `square`: whether the piece forms a square
- `vline`: whether the piece forms a vertical line
- `hline`: whether the piece forms a horizontal line
- `hmatching`: whether there exists a row for which both patches have cells
- `vmatching`: whether there exists a column for which both patches have cells
- `manhattan`: closest manhattan distance between two patches
- `adjacent`: whether two patches are adjacent
- `bordering`: whether a patch is adjacent to a grid border
- `centerofmass`: center of mass
- `palette`: colors occurring in object or grid
- `numcolors`: number of colors occurring in object or grid
- `color`: color of object
- `toobject`: object from patch and grid
- `asobject`: conversion of grid to object
- `rot90`: quarter clockwise rotation
- `rot180`: half rotation
- `rot270`: quarter anticlockwise rotation
- `hmirror`: mirroring along horizontal
- `vmirror`: mirroring along vertical
- `dmirror`: mirroring along diagonal
- `cmirror`: mirroring along counterdiagonal
- `fill`: fill value at indices
- `paint`: paint object to grid
- `underfill`: fill value at indices that are background
- `underpaint`: paint object to grid where there is background
- `hupscale`: upscale grid horizontally
- `vupscale`: upscale grid vertically
- `upscale`: upscale object or grid
- `downscale`: downscale object or grid
- `hconcat`: concatenate two grids horizontally
- `vconcat`: concatenate two grids vertically
- `subgrid`: smallest subgrid containing object
- `hsplit`: split grid horizontally
- `vsplit`: split grid vertically
- `cellwise`: cellwise match of two grids
- `replace`: color substitution
- `switch_`: color switching
- `center`: center of the patch
- `position`: relative position between two patches
- `index`: color at location
- `canvas`: grid construction
- `corners`: indices of corners
- `connect`: line between two points
- `cover`: remove object from grid
- `trim`: trim border of grid
- `move`: move object on grid
- `tophalf`: upper half of grid
- `bottomhalf`: lower half of grid
- `lefthalf`: left half of grid
- `righthalf`: right half of grid
- `vfrontier`: vertical frontier
- `hfrontier`: horizontal frontier
- `backdrop`: indices in bounding box of patch
- `delta`: indices in bounding box but not part of patch
- `gravitate`: direction to move source until adjacent to destination
- `inbox`: inbox for patch
- `outbox`: outbox for patch
- `box`: outline of patch
- `shoot`: line from starting point and direction
- `occurrences`: locations of occurrences of object in grid
- `frontiers`: set of frontiers
- `compress`: removes frontiers from grid
- `hperiod`: horizontal periodicity
- `vperiod`: vertical periodicity

## Search

aicpp formulates ARC solving as a constrained program synthesis problem.

Starting from the identity program `I`, the system iteratively generates candidate programs using the neural model. The model combines representations of the ARC task, the current program structure, and its execution cost to predict the next program tokens.

Program generation is constrained by the DSL grammar and the current AST state. This prevents syntactically invalid programs from entering the search space.

At each iteration, generated candidates are executed symbolically on the training examples. Their outputs are compared with the expected outputs and a cost is computed. The resulting candidates are then ranked, and the most promising programs are retained for subsequent search iterations.

The process can be summarized as:

```text
ARC task
   ↓
Task representation
   ↓
Neural program generation
   ↓
DSL-constrained candidate programs
   ↓
Symbolic execution
   ↓
Cost evaluation
   ↓
Candidate selection
   ↓
Next search iteration
```

The search terminates when an exact solution is found, when the search budget is exhausted, or when no further improvement is obtained.

## Evaluation protocol

aicpp evaluates candidate programs by executing them on the ARC demonstrations and comparing their outputs with the expected outputs.

### Training examples

For each ARC task, the training examples consist of input/output grid pairs provided by the benchmark.

Candidate programs are executed on every training input. Their generated grids are compared with the corresponding expected outputs, and a training cost is computed from these comparisons.

The training cost is used to guide program search and to rank candidate programs.

### Test examples

Once the search process has produced a set of promising candidate programs, the candidates are executed on the test inputs provided by the benchmark.

Test outputs are not used to train or guide the model. They are used only to evaluate whether the synthesized programs generalize to unseen inputs.

### Symbolic execution

Every candidate is executed by the aicpp symbolic engine using the operations defined by the DSL.

Because programs are executable symbolic objects, their behavior can be evaluated deterministically on arbitrary ARC grids.

### Cost

The cost function measures the discrepancy between the program outputs and the expected training outputs.

A cost of zero means that the candidate reproduces all expected training outputs exactly.

Lower costs therefore indicate better agreement with the demonstrations.

### Exact match

A program is considered an exact solution for a task when its output matches the expected output for every relevant example.

For a test example, an exact match means that every cell of the predicted grid is identical to the corresponding cell of the ground-truth grid.

### Candidate selection

At each search iteration, generated candidates are evaluated and ranked according to their cost.

Only the most promising candidates are retained for subsequent iterations. This limits the effective search space while allowing the neural model to progressively refine its exploration of the DSL program space.

The final evaluation is performed by executing the selected candidate programs on the benchmark test inputs and checking for exact grid matches.

An interesting aspect of the evaluation is that training cost and test
performance are not necessarily perfectly correlated. In particular,
some synthesized programs may fail to reproduce all training examples
while still producing the correct output on unseen test inputs. This
provides an additional perspective on the generalization properties of
the learned program search.

## Current results

- 10.83% on subset of public training dataset (120 tasks)
- 0% on public evaluation dataset
- 0% on private dataset

## Kaggle

[Link to the competition/submission information.](https://www.kaggle.com/competitions/arc-prize-2026-arc-agi-2/overview)
