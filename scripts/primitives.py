import copy
import numpy as np
import utils

"""
Verb properties:
Map: output pixel positions are identical to input positions.
Flip: output pixel VALUES are identical to input values (only positions change).
Segment: new pixels appear between existing pixels to form continuous structures.
Pair: output changes depend on relationships between two or more input elements.
"""

def segments(dst: list[np.ndarray], pairs: list[list[tuple[tuple[int, int], tuple[int, int]]]], value: int, start: bool, finish: bool) -> list[np.ndarray]:
    """
    Segment two locations in numpy arrays
    """
    if (len(dst) != len(pairs)):
        return []

    result = []

    for i in range(0, len(dst)):
        m = copy.deepcopy(dst[i])

        for pair in pairs[i]:
            if (utils.validIndex(m, pair[0]) and utils.validIndex(m, pair[1])):
                s = m[pair[0][0]][pair[0][1]]
                f = m[pair[1][0]][pair[1][1]]

                m = utils.dotSegment(m, pair[0], pair[1], value, 1)

                if (start):
                    m[pair[0][0]][pair[0][1]] = s

                if (finish):
                    m[pair[1][0]][pair[1][1]] = f

        result.append(m)

    return result

def map(x: list[np.ndarray], mapping: dict[int, int]) -> list[np.ndarray]:
    """
    Map numpy arrays cells from a mapping
    """

    result = []

    for v in x:
        y = copy.deepcopy(v)

        for i in range(0, y.shape[0]):
            for j in range(0, y.shape[1]):
                y[i, j] = mapping.get(y[i, j], y[i, j])

        result.append(y)

    return result

def inferColorMapping(pairs: list[tuple[np.ndarray, np.ndarray]]) -> dict[int, int]:
    """
    Map given locations of numpy arrays
    """
    mapping = {}

    for pair in pairs:
        h, w = pair[0].shape

        for i in range(h):
            for j in range(w):
                a = int(pair[0][i, j])
                b = int(pair[1][i, j])

                if (a in mapping):
                    if (mapping[a] != b):
                        return mapping
                else:
                    mapping[a] = b

    return mapping

def sameElement(pairs: list[list[tuple[tuple[int, int], tuple[int, int]]]], first: bool) -> list[list[tuple[tuple[int, int], tuple[int, int]]]]:
    """
    Pair a list of index pairs where the elements are the same considering first or second element of a pair (a pair is a grid location)
    """

    result = []

    for pair in pairs:
        results = []

        for p in pair:
            if (first):
                if (p[0][0] == p[1][0]):
                    results.append(p)
            else:
                if (p[0][1] == p[1][1]):
                    results.append(p)

        result.append(results)

    return result

def regionPairs(regions: list[list[list[tuple[int, int]]]]) -> list[list[tuple[tuple[int, int], tuple[int, int]]]]:
    """
    Pair a list of regions (a region is a list of connected pairs of same value, a pair is a grid location)
    """

    result = []

    for x in regions:
        pairs = []

        for i1 in range(0, len(x)):
            for j1 in range(i1 + 1, len(x)):
                for i2 in range(0, len(x[i1])):
                    for j2 in range(0, len(x[j1])):
                        pairs.append((x[i1][i2], x[j1][j2]))

        result.append(pairs)

    return result

def fliplr(x: list[np.ndarray]) -> list[np.ndarray]:
    """
    Flip left and right columns
    """

    return [np.fliplr(y) for y in x]

def flipud(x: list[np.ndarray]) -> list[np.ndarray]:
    """
    Flip up and down rows
    """

    return [np.flipud(y) for y in x]
