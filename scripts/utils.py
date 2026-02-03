import copy
import numpy as np

def associate(mapping: dict[int, int], a: int, b: int) -> dict[int, int]:
    """
    Associate a value with another value in a dictionnary
    """
    m = copy.deepcopy(mapping)

    m[a] = b

    return m

def dotSegment(dst: np.ndarray, begin: tuple[int, int], end: tuple[int, int], value: int, dot_step: int) -> np.ndarray:
    """
    Dot a straight line between two points in an numpy array with the specified value.
    """
    m = copy.deepcopy(dst)

    u = np.array([end[0], end[1]]) - np.array([begin[0], begin[1]])
    v = u / np.linalg.norm(u)

    if (min(v)):
        v *= min(v)

    step = np.linalg.norm(v) / np.linalg.norm(u)
    i = 0

    for t in np.arange(0, 1 + 0.1 * step, step):
        if (i % dot_step == 0):
            m[round(begin[0] + t * u[0]), round(begin[1] + t * u[1])] = value

        i += 1

    return m

def regionSet(m: np.ndarray, diagonals: bool) -> set:
    s = set()

    for i in range(0, m.shape[0]):
        for j in range(0, m.shape[1]):
            r = tuple(sorted(region(m, (i, j), diagonals)))

            if (not r in s):
                s.add(r)

    return s

def validIndex(a: np.ndarray, at: tuple[int, int]) -> bool:
    """
    Check if the index is within the bounds of a numpy array
    """
    
    return (0 <= at[0] and at[0] < a.shape[0] and 0 <= at[1] and at[1] < a.shape[1])

def neighbors(loc: tuple[int, int], size: tuple[int, int], diagonals: bool) -> list[tuple[int, int]]:
    """
    Return a list of the neighboring indices of a given index considering diagonal neihbors or not
    """
    n = []

    for di in range(-1, 2):
        for dj in range(-1, 2):
            if (di == 0 and dj == 0):
                continue

            i = loc[0] + di
            j = loc[1] + dj

            if (not (0 <= i and i < size[0] and 0 <= j and j < size[1])):
                continue

            if (not diagonals and abs(di) == abs(dj)):
                continue

            n.append((i, j))

    return n

def region(a: np.ndarray, at: tuple[int, int], diagonals: bool) -> list[tuple[int, int]]:
    """
    Return a list of indices in the same region as the given index considering diagonal neihbors or not
    """
    
    if (not validIndex(a, at)):
        return []

    s = set()
    stack = set()
    stack.add(at)

    v = a[at[0]][at[1]]

    indices = []

    while (len(stack)):
        l = list(stack)
        loc = l[0]
        del l[0]
        stack = set(l)

        if (not loc in s):
            s.add(loc)

            if (abs(a[loc[0]][loc[1]] - v) < np.finfo(float).eps):
                indices.append(loc)

                for n in neighbors(loc, (a.shape[0], a.shape[1]), diagonals):
                    stack.add(n)

    return indices
