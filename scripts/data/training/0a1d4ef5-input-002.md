You are given several input->output grid pairs from an ARC task:
train1: ((0, 2, 0, 0, 0, 2, 0, 8, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 2, 8, 0, 0, 2, 0, 8, 0, 0, 0, 0, 0), (0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 8, 8, 2, 0, 0, 0, 0, 0, 0), (8, 0, 2, 3, 3, 3, 3, 3, 3, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0), (8, 0, 8, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 8, 0, 8, 9, 9, 9, 9, 9, 8, 8), (2, 8, 0, 3, 3, 3, 3, 3, 3, 8, 8, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 9, 9, 9, 9, 9, 0, 0), (8, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 2, 2, 2, 8, 8, 8, 8, 0, 2, 8, 2, 0, 9, 9, 9, 9, 9, 0, 0), (0, 0, 0, 8, 0, 0, 8, 0, 0, 2, 8, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 8, 0, 9, 9, 9, 9, 9, 8, 8), (0, 8, 8, 8, 0, 0, 2, 0, 8, 0, 0, 0, 2, 8, 8, 0, 0, 0, 8, 0, 2, 0, 2, 0, 8, 0, 0, 8, 8, 0), (0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 8, 8, 2, 0, 0, 2, 0, 0, 2, 0, 0, 8, 2, 8, 0), (8, 0, 0, 0, 0, 0, 8, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 2, 8, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0), (0, 0, 2, 6, 6, 6, 6, 0, 8, 0, 0, 4, 4, 4, 4, 4, 4, 2, 0, 0, 0, 8, 0, 0, 2, 0, 0, 0, 2, 0), (8, 0, 8, 6, 6, 6, 6, 0, 8, 0, 8, 4, 4, 4, 4, 4, 4, 2, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 8, 0), (0, 2, 0, 6, 6, 6, 6, 8, 0, 2, 2, 4, 4, 4, 4, 4, 4, 8, 0, 8, 0, 0, 0, 1, 1, 1, 1, 1, 0, 2), (0, 2, 8, 6, 6, 6, 6, 8, 0, 8, 0, 4, 4, 4, 4, 4, 4, 0, 8, 2, 2, 0, 2, 1, 1, 1, 1, 1, 0, 8), (0, 0, 2, 6, 6, 6, 6, 0, 0, 0, 2, 4, 4, 4, 4, 4, 4, 0, 0, 8, 0, 8, 8, 1, 1, 1, 1, 1, 8, 0), (0, 0, 0, 6, 6, 6, 6, 0, 0, 2, 8, 0, 8, 8, 2, 8, 0, 8, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 2), (2, 8, 0, 6, 6, 6, 6, 0, 2, 0, 0, 0, 0, 2, 8, 0, 0, 0, 2, 8, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0), (0, 0, 8, 0, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 2), (0, 0, 2, 0, 8, 0, 0, 0, 2, 8, 0, 8, 0, 0, 0, 8, 0, 8, 8, 8, 0, 8, 0, 0, 8, 0, 2, 2, 0, 2), (8, 0, 0, 0, 0, 0, 8, 8, 2, 2, 8, 0, 8, 2, 2, 8, 0, 0, 0, 0, 8, 0, 2, 0, 8, 0, 0, 0, 8, 2), (2, 2, 0, 0, 0, 0, 2, 8, 0, 8, 0, 0, 2, 2, 8, 0, 0, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 8), (0, 8, 8, 0, 0, 8, 8, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 8, 2, 0, 0), (0, 0, 2, 8, 2, 0, 2, 0, 0, 8, 0, 0, 0, 2, 0, 8, 0, 0, 0, 2, 8, 8, 0, 8, 0, 2, 0, 0, 0, 8), (2, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 2, 0, 8, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 8, 8, 0), (8, 2, 0, 0, 0, 8, 0, 8, 0, 8, 2, 0, 0, 0, 8, 0, 0, 8, 0, 2, 0, 0, 8, 0, 2, 2, 8, 0, 0, 0), (0, 8, 0, 2, 2, 8, 2, 8, 0, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 8, 0, 8, 0, 0, 8, 2), (0, 0, 2, 8, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 2, 0, 2, 2, 0, 0, 8, 0, 2, 0, 0, 8, 8), (0, 0, 0, 0, 8, 0, 0, 0, 8, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 2, 8, 0, 0, 8, 0), (8, 2, 0, 2, 8, 8, 0, 0, 0, 2, 0, 0, 0, 8, 8, 0, 8, 0, 0, 0, 8, 2, 8, 8, 0, 2, 8, 2, 2, 2), (2, 0, 8, 8, 0, 0, 0, 8, 0, 0, 8, 0, 8, 0, 0, 0, 8, 0, 2, 0, 0, 8, 0, 8, 0, 0, 2, 8, 0, 0)) -> ((3, 1, 9), (6, 4, 1))
train2: ((0, 2, 0, 0, 0, 2, 5, 2, 2, 0, 5, 2, 5, 5, 0, 2, 2, 5, 2, 2, 5, 5, 0, 2, 0, 0, 2, 0, 0, 0), (5, 0, 0, 5, 2, 2, 5, 2, 5, 0, 0, 2, 2, 5, 5, 2, 2, 5, 0, 5, 2, 0, 0, 0, 5, 0, 5, 5, 0, 2), (5, 0, 2, 2, 8, 8, 8, 8, 8, 8, 8, 5, 0, 2, 4, 4, 4, 4, 5, 0, 0, 2, 3, 3, 3, 3, 3, 0, 0, 2), (0, 5, 0, 5, 8, 8, 8, 8, 8, 8, 8, 2, 0, 0, 4, 4, 4, 4, 0, 0, 2, 0, 3, 3, 3, 3, 3, 0, 2, 0), (5, 0, 5, 0, 8, 8, 8, 8, 8, 8, 8, 2, 2, 0, 4, 4, 4, 4, 2, 2, 0, 2, 3, 3, 3, 3, 3, 5, 0, 5), (0, 0, 0, 5, 8, 8, 8, 8, 8, 8, 8, 2, 0, 0, 4, 4, 4, 4, 0, 0, 2, 2, 3, 3, 3, 3, 3, 0, 0, 2), (0, 0, 0, 2, 5, 5, 5, 2, 2, 0, 0, 0, 2, 5, 0, 5, 2, 0, 2, 0, 5, 0, 5, 2, 0, 2, 0, 5, 5, 2), (0, 0, 2, 2, 5, 5, 0, 0, 2, 0, 5, 0, 5, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0), (0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 5, 2, 0, 0, 0, 5, 2, 0, 5, 2, 0, 0, 5, 2, 0, 0), (0, 2, 0, 2, 0, 0, 2, 0, 0, 0, 2, 5, 2, 0, 0, 2, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 5, 0, 5, 0), (0, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 0, 0, 7, 7, 7, 7, 7, 0, 0, 5, 0), (0, 0, 0, 2, 1, 1, 1, 1, 1, 0, 5, 0, 3, 3, 3, 3, 3, 3, 3, 2, 0, 7, 7, 7, 7, 7, 2, 5, 5, 5), (0, 0, 5, 2, 1, 1, 1, 1, 1, 5, 2, 0, 3, 3, 3, 3, 3, 3, 3, 0, 2, 7, 7, 7, 7, 7, 0, 2, 5, 2), (2, 5, 0, 2, 1, 1, 1, 1, 1, 2, 0, 0, 3, 3, 3, 3, 3, 3, 3, 2, 5, 7, 7, 7, 7, 7, 0, 0, 0, 0), (0, 0, 0, 2, 0, 0, 5, 0, 2, 2, 2, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 7, 7, 7, 7, 7, 2, 0, 2, 2), (0, 0, 2, 0, 0, 5, 0, 2, 0, 2, 0, 5, 5, 0, 0, 2, 0, 5, 2, 2, 2, 2, 0, 5, 2, 0, 0, 2, 2, 0), (0, 0, 5, 2, 0, 0, 2, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 2, 2, 0, 0, 0, 0, 5, 5, 0, 2, 0, 0, 5), (0, 2, 2, 0, 8, 8, 8, 8, 8, 0, 2, 0, 5, 4, 4, 4, 4, 4, 2, 0, 0, 2, 0, 0, 5, 0, 0, 0, 2, 0), (0, 0, 2, 0, 8, 8, 8, 8, 8, 2, 2, 5, 0, 4, 4, 4, 4, 4, 0, 2, 5, 0, 1, 1, 1, 1, 1, 2, 0, 2), (2, 2, 0, 0, 8, 8, 8, 8, 8, 5, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 5, 5, 1, 1, 1, 1, 1, 5, 0, 0), (2, 5, 5, 0, 8, 8, 8, 8, 8, 0, 5, 0, 5, 4, 4, 4, 4, 4, 0, 5, 0, 2, 1, 1, 1, 1, 1, 0, 0, 0), (2, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 5, 2, 5, 0, 0, 2, 5, 0, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0), (0, 5, 2, 5, 5, 2, 2, 0, 2, 0, 0, 2, 5, 0, 5, 0, 0, 5, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0), (2, 0, 0, 0, 2, 5, 0, 0, 5, 5, 2, 0, 2, 2, 0, 0, 5, 5, 0, 0, 0, 5, 0, 2, 0, 5, 0, 0, 2, 5), (0, 0, 5, 0, 0, 0, 0, 2, 0, 5, 5, 0, 2, 5, 0, 0, 0, 2, 0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5), (0, 2, 0, 2, 0, 5, 2, 5, 0, 5, 2, 0, 0, 0, 0, 0, 0, 5, 2, 2, 5, 2, 0, 0, 0, 0, 0, 5, 5, 0), (0, 0, 0, 5, 5, 0, 2, 2, 2, 0, 0, 2, 0, 2, 0, 0, 5, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0), (0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 5, 2, 2, 2, 0, 0, 0, 5), (2, 2, 2, 0, 0, 0, 0, 2, 0, 5, 5, 0, 0, 0, 5, 0, 2, 0, 5, 0, 0, 0, 5, 0, 2, 0, 2, 2, 2, 5), (5, 0, 0, 2, 2, 5, 2, 2, 0, 0, 0, 0, 2, 5, 0, 2, 0, 5, 0, 0, 5, 5, 5, 0, 0, 2, 0, 0, 0, 5)) -> ((8, 4, 3), (1, 3, 7), (8, 4, 1))
train3: ((1, 0, 0, 0, 9, 1, 1, 0, 1, 9, 1, 0, 9, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 9, 0, 1, 1, 9, 9, 9), (0, 0, 0, 0, 9, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 9, 9, 0, 0, 1, 1, 1, 1, 9, 0), (1, 1, 1, 0, 0, 1, 1, 9, 1, 0, 1, 0, 4, 4, 4, 4, 4, 4, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 9), (0, 1, 9, 0, 0, 0, 0, 1, 0, 0, 1, 1, 4, 4, 4, 4, 4, 4, 0, 9, 0, 0, 8, 8, 8, 8, 1, 0, 1, 0), (0, 0, 1, 1, 0, 9, 0, 9, 0, 0, 0, 9, 4, 4, 4, 4, 4, 4, 9, 0, 1, 1, 8, 8, 8, 8, 0, 1, 9, 0), (1, 1, 0, 8, 8, 8, 8, 8, 8, 1, 0, 0, 4, 4, 4, 4, 4, 4, 1, 0, 0, 0, 8, 8, 8, 8, 1, 0, 9, 0), (1, 0, 9, 8, 8, 8, 8, 8, 8, 0, 0, 9, 4, 4, 4, 4, 4, 4, 0, 0, 1, 9, 8, 8, 8, 8, 1, 0, 1, 0), (9, 0, 0, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 9, 9, 0, 9, 0, 0, 1, 0, 1, 9, 1, 0, 0, 9, 1), (0, 9, 1, 1, 0, 1, 9, 1, 0, 1, 0, 9, 1, 0, 0, 0, 9, 9, 1, 0, 1, 1, 0, 0, 0, 0, 0, 9, 0, 1), (1, 1, 0, 9, 9, 0, 0, 9, 0, 0, 0, 0, 7, 7, 7, 7, 1, 1, 1, 0, 1, 0, 3, 3, 3, 3, 3, 0, 1, 0), (0, 1, 0, 0, 3, 3, 3, 1, 9, 1, 0, 0, 7, 7, 7, 7, 0, 1, 0, 9, 0, 0, 3, 3, 3, 3, 3, 1, 1, 9), (1, 0, 1, 1, 3, 3, 3, 1, 0, 0, 1, 0, 7, 7, 7, 7, 0, 0, 9, 0, 0, 0, 3, 3, 3, 3, 3, 0, 1, 0), (0, 1, 1, 0, 3, 3, 3, 9, 0, 1, 0, 9, 1, 1, 0, 0, 0, 1, 9, 1, 1, 1, 3, 3, 3, 3, 3, 0, 0, 9), (0, 0, 0, 1, 0, 9, 9, 9, 0, 9, 9, 1, 9, 9, 0, 0, 1, 0, 1, 0, 0, 9, 0, 0, 0, 0, 9, 0, 9, 0), (0, 1, 0, 1, 0, 9, 1, 0, 1, 9, 1, 9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 9, 9, 1, 0), (1, 0, 9, 0, 1, 9, 0, 0, 0, 0, 9, 9, 1, 1, 1, 9, 0, 1, 9, 1, 4, 4, 4, 4, 4, 9, 0, 1, 0, 0), (9, 0, 0, 0, 9, 0, 9, 0, 0, 9, 0, 0, 9, 0, 0, 0, 1, 0, 0, 9, 4, 4, 4, 4, 4, 0, 1, 0, 0, 0), (9, 0, 9, 2, 2, 2, 2, 2, 9, 9, 1, 9, 8, 8, 8, 8, 0, 9, 0, 9, 4, 4, 4, 4, 4, 0, 0, 0, 0, 1), (0, 0, 1, 2, 2, 2, 2, 2, 1, 0, 1, 0, 8, 8, 8, 8, 1, 9, 9, 1, 4, 4, 4, 4, 4, 1, 0, 9, 9, 0), (0, 1, 0, 2, 2, 2, 2, 2, 0, 1, 0, 1, 8, 8, 8, 8, 0, 9, 1, 0, 4, 4, 4, 4, 4, 0, 1, 1, 1, 1), (1, 0, 0, 2, 2, 2, 2, 2, 0, 0, 1, 0, 8, 8, 8, 8, 0, 9, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0), (9, 1, 9, 0, 9, 0, 9, 9, 1, 9, 9, 9, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0), (9, 0, 9, 0, 0, 1, 0, 0, 9, 1, 1, 9, 9, 1, 0, 9, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1), (1, 0, 0, 0, 1, 9, 1, 1, 1, 1, 0, 0, 9, 1, 0, 1, 1, 1, 9, 1, 9, 0, 9, 1, 1, 1, 1, 0, 0, 0), (1, 0, 0, 0, 1, 9, 9, 1, 1, 0, 1, 0, 0, 9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 1, 1), (0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 1, 1, 1, 0, 0, 0, 0), (0, 0, 9, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 9, 9, 0, 1, 0, 1, 1, 0, 1), (0, 0, 0, 9, 0, 1, 9, 1, 1, 1, 1, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 0, 1, 0, 0, 0, 0, 9, 0, 1), (1, 0, 1, 9, 0, 9, 0, 0, 0, 0, 9, 1, 0, 0, 0, 0, 9, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0), (1, 0, 0, 0, 0, 9, 9, 0, 1, 0, 9, 0, 9, 0, 1, 1, 1, 0, 0, 1, 0, 0, 9, 0, 1, 0, 9, 9, 9, 1)) -> ((8, 4, 8), (3, 7, 3), (2, 8, 4))

Available types:
```python
from typing import (
    List,
    Union,
    Tuple,
    Any,
    Container,
    Callable,
    FrozenSet,
    Iterable
)

Boolean = bool
Integer = int
IntegerTuple = Tuple[Integer, Integer]
Numerical = Union[Integer, IntegerTuple]
IntegerSet = FrozenSet[Integer]
Grid = Tuple[Tuple[Integer]]
Cell = Tuple[Integer, IntegerTuple]
Object = FrozenSet[Cell]
Objects = FrozenSet[Object]
Indices = FrozenSet[IntegerTuple]
IndicesSet = FrozenSet[Indices]
Patch = Union[Object, Indices]
Element = Union[Object, Grid]
Piece = Union[Grid, Patch]
TupleTuple = Tuple[Tuple]
ContainerContainer = Container[Container]
```

Available variables:
```python
I: Tuple[Tuple]
F = False
T = True
ZERO = 0
ONE = 1
TWO = 2
THREE = 3
FOUR = 4
FIVE = 5
SIX = 6
SEVEN = 7
EIGHT = 8
NINE = 9
TEN = 10
NEG_ONE = -1
NEG_TWO = -2
DOWN = (1, 0)
RIGHT = (0, 1)
UP = (-1, 0)
LEFT = (0, -1)
ORIGIN = (0, 0)
UNITY = (1, 1)
NEG_UNITY = (-1, -1)
UP_RIGHT = (-1, 1)
DOWN_LEFT = (1, -1)
ZERO_BY_TWO = (0, 2)
TWO_BY_ZERO = (2, 0)
TWO_BY_TWO = (2, 2)
THREE_BY_THREE = (3, 3)
```

Available primitives:
```python
add(a: Union[int, Tuple[int, int]], b: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # addition
adjacent(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether two patches are adjacent
apply(function: Callable, container: Container) -> Container # apply function to each item in container
argmax(container: Container, compfunc: Callable) -> Any # largest item by custom order
argmin(container: Container, compfunc: Callable) -> Any # smallest item by custom order
asindices(grid: Tuple[Tuple[int]]) -> FrozenSet[Tuple[int, int]] # indices of all grid cells
asobject(grid: Tuple[Tuple[int]]) -> FrozenSet[Tuple[int, Tuple[int, int]]] # conversion of grid to object
astuple(a: int, b: int) -> Tuple[int, int] # constructs a tuple
backdrop(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # indices in bounding box of patch
bordering(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], grid: Tuple[Tuple[int]]) -> bool # whether a patch is adjacent to a grid border
both(a: bool, b: bool) -> bool # logical and
bottomhalf(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # lower half of grid
box(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # outline of patch
branch(condition: bool, a: Any, b: Any) -> Any # if else branching
canvas(value: int, dimensions: Tuple[int, int]) -> Tuple[Tuple[int]] # grid construction
cellwise(a: Tuple[Tuple[int]], b: Tuple[Tuple[int]], fallback: int) -> Tuple[Tuple[int]] # cellwise match of two grids
center(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # center of the patch
centerofmass(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # center of mass
chain(h: Callable, g: Callable, f: Callable) -> Callable # function composition with three functions
cmirror(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # mirroring along counterdiagonal
color(obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> int # color of object
colorcount(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]], value: int) -> int # number of cells with color
colorfilter(objs: FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]], value: int) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # filter objects by color
combine(a: Container, b: Container) -> Container # union
compose(outer: Callable, inner: Callable) -> Callable # function composition
compress(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # removes frontiers from grid
connect(a: Tuple[int, int], b: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # line between two points
contained(value: Any, container: Container) -> bool # element of
corners(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # indices of corners
cover(grid: Tuple[Tuple[int]], patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[Tuple[int]] # remove object from grid
crement(x: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # incrementing positive and decrementing negative
crop(grid: Tuple[Tuple[int]], start: Tuple[int, int], dims: Tuple[int, int]) -> Tuple[Tuple[int]] # subgrid specified by start and dimension
decrement(x: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # decrementing
dedupe(tup: Tuple) -> Tuple # remove duplicates
delta(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # indices in bounding box but not part of patch
difference(a: FrozenSet, b: FrozenSet) -> FrozenSet # set difference
divide(a: Union[int, Tuple[int, int]], b: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # floor division
dmirror(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # mirroring along diagonal
dneighbors(loc: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # directly adjacent indices
double(n: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # scaling by two
downscale(grid: Tuple[Tuple[int]], factor: int) -> Tuple[Tuple[int]] # downscale grid
either(a: bool, b: bool) -> bool # logical or
equality(a: Any, b: Any) -> bool # equality
even(n: int) -> bool # evenness
extract(container: Container, condition: Callable) -> Any # first element of container that satisfies condition
fgpartition(grid: Tuple[Tuple[int]]) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # each cell with the same value part of the same object without background
fill(grid: Tuple[Tuple[int]], value: int, patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[Tuple[int]] # fill value at indices
first(container: Container) -> Any # first item of container
flip(b: bool) -> bool # logical not
fork(outer: Callable, a: Callable, b: Callable) -> Callable # creates a wrapper function
frontiers(grid: Tuple[Tuple[int]]) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # set of frontiers
gravitate(source: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], destination: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # direction to move source until adjacent to destination
greater(a: int, b: int) -> bool # greater
halve(n: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # scaling by one half
hconcat(a: Tuple[Tuple[int]], b: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # concatenate two grids horizontally
height(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # height of grid or patch
hfrontier(location: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # horizontal frontier
hline(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether the piece forms a horizontal line
hmatching(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether there exists a row for which both patches have cells
hmirror(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # mirroring along horizontal
hperiod(obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> int # horizontal periodicity
hsplit(grid: Tuple[Tuple[int]], n: int) -> Tuple # split grid horizontally
hupscale(grid: Tuple[Tuple[int]], factor: int) -> Tuple[Tuple[int]] # upscale grid horizontally
identity(x: Any) -> Any # identity function
inbox(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # inbox for patch
increment(x: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # incrementing
index(grid: Tuple[Tuple[int]], loc: Tuple[int, int]) -> int # color at location
ineighbors(loc: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # diagonally adjacent indices
initset(value: Any) -> FrozenSet # initialize container
insert(value: Any, container: FrozenSet) -> FrozenSet # insert item into container
intersection(a: FrozenSet, b: FrozenSet) -> FrozenSet # returns the intersection of two containers
interval(start: int, stop: int, step: int) -> Tuple # range
invert(n: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # inversion with respect to addition
last(container: Container) -> Any # last item of container
lbind(function: Callable, fixed: Any) -> Callable # fix the leftmost argument
leastcolor(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]]) -> int # least common color
leastcommon(container: Container) -> Any # least common item
lefthalf(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # left half of grid
leftmost(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # column index of leftmost occupied cell
llcorner(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # index of lower left corner
lowermost(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # row index of lowermost occupied cell
lrcorner(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # index of lower right corner
manhattan(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # closest manhattan distance between two patches
mapply(function: Callable, container: Container[Container]) -> FrozenSet # apply and merge
matcher(function: Callable, target: Any) -> Callable # construction of equality function
maximum(container: FrozenSet[int]) -> int # maximum
merge(containers: Container[Container]) -> Container # merging
mfilter(container: Container, function: Callable) -> FrozenSet # filter and merge
minimum(container: FrozenSet[int]) -> int # minimum
mostcolor(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]]) -> int # most common color
mostcommon(container: Container) -> Any # most common item
move(grid: Tuple[Tuple[int]], obj: FrozenSet[Tuple[int, Tuple[int, int]]], offset: Tuple[int, int]) -> Tuple[Tuple[int]] # move object on grid
mpapply(function: Callable, a: Tuple, b: Tuple) -> Tuple # apply function on two vectors and merge
multiply(a: Union[int, Tuple[int, int]], b: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # multiplication
neighbors(loc: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # adjacent indices
normalize(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # moves upper left corner to origin
numcolors(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]]) -> FrozenSet[int] # number of colors occurring in object or grid
objects(grid: Tuple[Tuple[int]], univalued: bool, diagonal: bool, without_bg: bool) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # objects occurring on the grid
occurrences(grid: Tuple[Tuple[int]], obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # locations of occurrences of object in grid
ofcolor(grid: Tuple[Tuple[int]], value: int) -> FrozenSet[Tuple[int, int]] # indices of all grid cells with value
order(container: Container, compfunc: Callable) -> Tuple # order container by custom key
other(container: Container, value: Any) -> Any # other value in the container
outbox(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # outbox for patch
paint(grid: Tuple[Tuple[int]], obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> Tuple[Tuple[int]] # paint object to grid
pair(a: Tuple, b: Tuple) -> Tuple[Tuple] # zipping of two tuples
palette(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]]) -> FrozenSet[int] # colors occurring in object or grid
papply(function: Callable, a: Tuple, b: Tuple) -> Tuple # apply function on two vectors
partition(grid: Tuple[Tuple[int]]) -> FrozenSet[FrozenSet[Tuple[int, Tuple[int, int]]]] # each cell with the same value part of the same object
portrait(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether height is greater than width
position(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # relative position between two patches
positive(x: int) -> bool # positive
power(function: Callable, n: int) -> Callable # power of function
prapply(function, a: Container, b: Container) -> FrozenSet # apply function on cartesian product
product(a: Container, b: Container) -> FrozenSet # cartesian product
rapply(functions: Container, value: Any) -> Container # apply each function in container to value
rbind(function: Callable, fixed: Any) -> Callable # fix the rightmost argument
recolor(value: int, patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, Tuple[int, int]]] # recolor patch
remove(value: Any, container: Container) -> Container # remove item from container
repeat(item: Any, num: int) -> Tuple # repetition of item within vector
replace(grid: Tuple[Tuple[int]], replacee: int, replacer: int) -> Tuple[Tuple[int]] # color substitution
righthalf(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # right half of grid
rightmost(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # column index of rightmost occupied cell
rot180(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # half rotation
rot270(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # quarter anticlockwise rotation
rot90(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # quarter clockwise rotation
sfilter(container: Container, condition: Callable) -> Container # keep elements in container that satisfy condition
shape(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # height and width of grid or patch
shift(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], directions: Tuple[int, int]) -> Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # shift patch
shoot(start: Tuple[int, int], direction: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # line from starting point and direction
sign(x: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # sign
size(container: Container) -> int # cardinality
sizefilter(container: Container, n: int) -> FrozenSet # filter items by size
square(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether the piece forms a square
subgrid(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # smallest subgrid containing object
subtract(a: Union[int, Tuple[int, int]], b: Union[int, Tuple[int, int]]) -> Union[int, Tuple[int, int]] # subtraction
switch(grid: Tuple[Tuple[int]], a: int, b: int) -> Tuple[Tuple[int]] # color switching
toindices(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> FrozenSet[Tuple[int, int]] # indices of object cells
toivec(i: int) -> Tuple[int, int] # vector pointing vertically
tojvec(j: int) -> Tuple[int, int] # vector pointing horizontally
toobject(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], grid: Tuple[Tuple[int]]) -> FrozenSet[Tuple[int, Tuple[int, int]]] # object from patch and grid
tophalf(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # upper half of grid
totuple(container: FrozenSet) -> Tuple # conversion to tuple
trim(grid: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # trim border of grid
ulcorner(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # index of upper left corner
underfill(grid: Tuple[Tuple[int]], value: int, patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[Tuple[int]] # fill value at indices that are background
underpaint(grid: Tuple[Tuple[int]], obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> Tuple[Tuple[int]] # paint object to grid where there is background
uppermost(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # row index of uppermost occupied cell
upscale(element: Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]], factor: int) -> Union[FrozenSet[Tuple[int, Tuple[int, int]]], Tuple[Tuple[int]]] # upscale object or grid
urcorner(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Tuple[int, int] # index of upper right corner
valmax(container: Container, compfunc: Callable) -> int # maximum by custom function
valmin(container: Container, compfunc: Callable) -> int # minimum by custom function
vconcat(a: Tuple[Tuple[int]], b: Tuple[Tuple[int]]) -> Tuple[Tuple[int]] # concatenate two grids vertically
vfrontier(location: Tuple[int, int]) -> FrozenSet[Tuple[int, int]] # vertical frontier
vline(patch: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether the piece forms a vertical line
vmatching(a: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]], b: Union[FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> bool # whether there exists a column for which both patches have cells
vmirror(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]] # mirroring along vertical
vperiod(obj: FrozenSet[Tuple[int, Tuple[int, int]]]) -> int # vertical periodicity
vsplit(grid: Tuple[Tuple[int]], n: int) -> Tuple # split grid vertically
vupscale(grid: Tuple[Tuple[int]], factor: int) -> Tuple[Tuple[int]] # upscale grid vertically
width(piece: Union[Tuple[Tuple[int]], FrozenSet[Tuple[int, Tuple[int, int]]], FrozenSet[Tuple[int, int]]]) -> int # width of grid or patch
```

**Program 1**
*DSL*
```python
def dsl1(I):
    # Global 3x3 tiling summary via mostcolor per 10x10 tile, then crop zero rows/cols
    d10 = astuple(TEN, TEN)
    z = ZERO
    t = TEN
    tt = double(TEN)
    # tiles
    T00 = crop(I, astuple(z, z), d10)
    T01 = crop(I, astuple(z, t), d10)
    T02 = crop(I, astuple(z, tt), d10)
    T10 = crop(I, astuple(t, z), d10)
    T11 = crop(I, astuple(t, t), d10)
    T12 = crop(I, astuple(t, tt), d10)
    T20 = crop(I, astuple(tt, z), d10)
    T21 = crop(I, astuple(tt, t), d10)
    T22 = crop(I, astuple(tt, tt), d10)
    # colors
    c00 = mostcolor(T00); c01 = mostcolor(T01); c02 = mostcolor(T02)
    c10 = mostcolor(T10); c11 = mostcolor(T11); c12 = mostcolor(T12)
    c20 = mostcolor(T20); c21 = mostcolor(T21); c22 = mostcolor(T22)
    # assemble 3x3
    U = UNITY
    r0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    r1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    r2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```

*Explosive scores*

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |        nan       |          nan |                  nan |               nan   |     nan      |
| train2 |          2.82843 |           36 |                   10 |                 0.5 |      49.3284 |
| train3 |        nan       |          nan |                  nan |               nan   |     nan      |

*Output grids*
train2: ((3,),)

*Tracebacks*
```bash
  File "<string>", line 28, in dsl1
def dsl1(I):
    # Global 3x3 tiling summary via mostcolor per 10x10 tile, then crop zero rows/cols
    d10 = astuple(TEN, TEN)
    z = ZERO
    t = TEN
    tt = double(TEN)
    # tiles
    T00 = crop(I, astuple(z, z), d10)
    T01 = crop(I, astuple(z, t), d10)
    T02 = crop(I, astuple(z, tt), d10)
    T10 = crop(I, astuple(t, z), d10)
    T11 = crop(I, astuple(t, t), d10)
    T12 = crop(I, astuple(t, tt), d10)
    T20 = crop(I, astuple(tt, z), d10)
    T21 = crop(I, astuple(tt, t), d10)
    T22 = crop(I, astuple(tt, tt), d10)
    # colors
    c00 = mostcolor(T00); c01 = mostcolor(T01); c02 = mostcolor(T02)
    c10 = mostcolor(T10); c11 = mostcolor(T11); c12 = mostcolor(T12)
    c20 = mostcolor(T20); c21 = mostcolor(T21); c22 = mostcolor(T22)
    # assemble 3x3
    U = UNITY
    r0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    r1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    r2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 1166, in subgrid
    return crop(grid, ulcorner(patch), shape(patch))
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "/home/julien-livet/Documents/GitHub/aicpp/scripts/arc-dsl/dsl.py", line 690, in crop
    return tuple(r[start[1]:start[1]+dims[1]] for r in grid[start[0]:start[0]+dims[0]])
                                                            ~~~~~^^^
IndexError: tuple index out of range
```

---

**Program 2**
*DSL*
```python
def dsl2(I):
    # Geometric robustness: use central 8x8 of each 10x10 tile before mostcolor, then crop zeros
    d8 = astuple(EIGHT, EIGHT)
    z = ZERO
    t = TEN
    tt = double(TEN)
    o = ONE
    # starts for central 8x8 in each 10x10 tile
    s00 = astuple(o, o)
    s01 = astuple(o, add(t, o))
    s02 = astuple(o, add(tt, o))
    s10 = astuple(add(t, o), o)
    s11 = astuple(add(t, o), add(t, o))
    s12 = astuple(add(t, o), add(tt, o))
    s20 = astuple(add(tt, o), o)
    s21 = astuple(add(tt, o), add(t, o))
    s22 = astuple(add(tt, o), add(tt, o))
    # tiles (central 8x8)
    T00 = crop(I, s00, d8)
    T01 = crop(I, s01, d8)
    T02 = crop(I, s02, d8)
    T10 = crop(I, s10, d8)
    T11 = crop(I, s11, d8)
    T12 = crop(I, s12, d8)
    T20 = crop(I, s20, d8)
    T21 = crop(I, s21, d8)
    T22 = crop(I, s22, d8)
    # colors
    c00 = mostcolor(T00); c01 = mostcolor(T01); c02 = mostcolor(T02)
    c10 = mostcolor(T10); c11 = mostcolor(T11); c12 = mostcolor(T12)
    c20 = mostcolor(T20); c21 = mostcolor(T21); c22 = mostcolor(T22)
    # assemble and crop zeros
    U = UNITY
    r0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    r1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    r2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```

*Explosive scores*

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          0       |      6.08276 |             0.333333 |                 0   |       6.4161 |
| train2 |          1.41421 |     28       |            13        |                 0.2 |      42.6142 |
| train3 |          2.82843 |     43       |            10        |                 0.5 |      56.3284 |

*Output grids*
train1: ((3, 1, 9), (0, 4, 0))
train2: ((8, 0), (0, 3))
train3: ((4,),)

---

**Program 3**
*DSL*
```python
def dsl3(I):
    # Color filtering before coarse downscaling: suppress color FIVE noise, then downscale and crop
    F = replace(I, FIVE, ZERO)
    D = downscale(F, TEN)
    nz = difference(asindices(D), ofcolor(D, ZERO))
    O = subgrid(nz, D)
    return O
```

*Explosive scores*

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |          2.23607 |       22     |                    7 |            0.447214 |      31.6833 |
| train2 |          1.41421 |       35     |                   13 |            0.2      |      49.6142 |
| train3 |          0       |       15.748 |                    1 |            0        |      16.748  |

*Output grids*
train1: ((2,),)
train2: ((0, 2), (2, 0))
train3: ((1, 1, 0), (0, 0, 0), (1, 1, 1))

---

**Program 4**
*DSL*
```python
def dsl4(I):
    # Geometric sampling: take the color at the center of each 10x10 tile, assemble 3x3, crop zeros
    f = FIVE
    t = TEN
    tt = double(TEN)
    # centers
    r0 = f; r1 = add(t, f); r2 = add(tt, f)
    c0 = f; c1 = add(t, f); c2 = add(tt, f)
    # sampled colors
    c00 = index(I, astuple(r0, c0)); c01 = index(I, astuple(r0, c1)); c02 = index(I, astuple(r0, c2))
    c10 = index(I, astuple(r1, c0)); c11 = index(I, astuple(r1, c1)); c12 = index(I, astuple(r1, c2))
    c20 = index(I, astuple(r2, c0)); c21 = index(I, astuple(r2, c1)); c22 = index(I, astuple(r2, c2))
    # assemble and crop zeros
    U = UNITY
    row0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    row1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    row2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(row0, vconcat(row1, row2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```

*Explosive scores*

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |                1 |     29       |            15        |            0.128037 |      45.128  |
| train2 |                0 |      9.59166 |             0.666667 |            0        |      10.2583 |
| train3 |                0 |     12.3693  |             0.666667 |            0        |      13.036  |

*Output grids*
train1: ((3, 8, 9), (6, 8, 1), (8, 2, 8))
train2: ((8, 4, 3), (5, 2, 0), (5, 0, 0))
train3: ((8, 4, 8), (9, 9, 9), (0, 0, 1))

---

**Program 5**
*DSL*
```python
def dsl5(I):
    # Relational per-tile adjustment: swap ZERO with tile's leastcolor, then mostcolor per tile
    d10 = astuple(TEN, TEN)
    z = ZERO
    t = TEN
    tt = double(TEN)
    # tiles
    A00 = crop(I, astuple(z, z), d10)
    A01 = crop(I, astuple(z, t), d10)
    A02 = crop(I, astuple(z, tt), d10)
    A10 = crop(I, astuple(t, z), d10)
    A11 = crop(I, astuple(t, t), d10)
    A12 = crop(I, astuple(t, tt), d10)
    A20 = crop(I, astuple(tt, z), d10)
    A21 = crop(I, astuple(tt, t), d10)
    A22 = crop(I, astuple(tt, tt), d10)
    # swap zero with tile's leastcolor to de-emphasize background, then take mostcolor
    B00 = switch(A00, z, leastcolor(A00)); c00 = mostcolor(B00)
    B01 = switch(A01, z, leastcolor(A01)); c01 = mostcolor(B01)
    B02 = switch(A02, z, leastcolor(A02)); c02 = mostcolor(B02)
    B10 = switch(A10, z, leastcolor(A10)); c10 = mostcolor(B10)
    B11 = switch(A11, z, leastcolor(A11)); c11 = mostcolor(B11)
    B12 = switch(A12, z, leastcolor(A12)); c12 = mostcolor(B12)
    B20 = switch(A20, z, leastcolor(A20)); c20 = mostcolor(B20)
    B21 = switch(A21, z, leastcolor(A21)); c21 = mostcolor(B21)
    B22 = switch(A22, z, leastcolor(A22)); c22 = mostcolor(B22)
    # assemble and crop zeros
    U = UNITY
    r0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    r1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    r2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```

*Explosive scores*

|        |   Grid size cost |   Value cost |   Pixel overlap cost |   Bounding box cost |   Total cost |
|:-------|-----------------:|-------------:|---------------------:|--------------------:|-------------:|
| train1 |                1 |           12 |            15        |            0.128037 |     28.128   |
| train2 |                0 |            9 |             0.555556 |            0        |      9.55556 |
| train3 |                0 |            8 |             0.555556 |            0        |      8.55556 |

*Output grids*
train1: ((2, 8, 2), (2, 2, 8), (2, 8, 2))
train2: ((5, 8, 5), (5, 3, 1), (8, 4, 1))
train3: ((9, 7, 3), (3, 7, 1), (2, 8, 9))

---

The goal is to improve the 5 DSL programs incrementally in two phases:

--------------------------------
PHASE 1 — EXPANSION (DISCOVERY)
--------------------------------

- Analyze failures and identify missing spatial or relational patterns.
- Introduce new intermediate concepts using ONLY the provided DSL primitives.
- All transformations MUST be expressed as compositions of DSL primitives.
- Do NOT write imperative logic (loops, indexing, or manual grid traversal).
- Do NOT use global case distinctions based on grid-level properties.

Guidelines:
- Represent all structures as sets of indices or objects derived from the grid.
- Express behaviors as transformations over these sets.
- You may use multiple intermediate concepts, but each must be defined using DSL primitives.
- Avoid hardcoded positional logic or scanning patterns.

--------------------------------
PHASE 2 — REDUCTION (ABSTRACTION)
--------------------------------

- Identify structurally similar transformations.
- Merge them into higher-order transformations using apply, mapply, interval, etc.
- Reduce program length and number of concepts.

Guidelines:
- Merge only transformations that share the same structure.
- Prefer parameterized transformations over duplicated logic.
- Avoid unnecessary intermediate variables.

--------------------------------
STRICT DSL CONSTRAINTS
--------------------------------

- The final program MUST be written entirely using the provided DSL primitives.
- No Python control flow (if, for, while).
- No manual indexing (index, shape, etc.).
- No explicit loops or list comprehensions.
- No global grid analysis (e.g. "if a full row exists", "if checkerboard pattern exists").

--------------------------------
STRUCTURAL BIAS
--------------------------------

- Prefer local, compositional rules over global heuristics.
- Prefer transformations that operate uniformly across the grid.
- Avoid splitting the solution into unrelated cases.

--------------------------------
SEARCH STRATEGY
--------------------------------

- Maintain multiple candidate programs with different structural approaches.
- Vary:
    - how anchors are defined,
    - how propagation directions are constructed,
    - how masks are generated.
- Avoid reusing previously failed structural ideas.

--------------------------------
OBJECTIVE
--------------------------------

Among correct programs, prefer those that:
- use fewer concepts,
- are fully expressed in DSL primitives,
- and describe the transformation as a composition of local operations.

The program must use a single consistent rule to decide where to apply the transformation.
Do not combine multiple independent heuristics (parity, diagonal, density, etc.).
Choose ONE principle and apply it consistently.
Identify a single property that explains all training examples.
Use only that property to guide the transformation.
Remove any part of the program that does not strictly improve performance on all training examples.
Prefer shorter and simpler programs.
Try removing a component of the logic and check if performance improves.

If the transformation cannot be explained by a single local rule,
introduce a global structural property (e.g., symmetry, periodicity, alignment)
and branch on it.

Avoid reusing previously tried concepts such as:
- parity-based rules
- diagonal propagation
- run-length heuristics
unless they clearly solve all examples.

Prefer solutions that are:
1. correct on all training examples
2. simple
3. based on a single idea

Each program MUST belong to a different reasoning family:
1. Global transformation:
   - Apply operations like crop, compress, trim, downscale, symmetry
2. Object extraction:
   - Identify a subset of pixels (e.g., using ofcolor or object detection)
   - Extract a subgrid or bounding box from them
3. Color filtering:
   - Select or remove specific colors and reconstruct the output
4. Geometric reasoning:
   - Use symmetry, mirroring, alignment, or relative positions
5. Relational / structural reasoning:
   - Use relationships between parts (e.g., center, adjacency, repetition)

Constraints:
- Each program must use a DIFFERENT core strategy
- Avoid reusing the same sequence of operations
- Use the DSL primitives explicitly
- Avoid reusing the same core operators across candidates
- Each program should reflect a distinct hypothesis about the task


Programs should be short, clean, and compositional.
Prefer minimal and compositional programs.

Important:
Do NOT generate 5 variations of the same idea.

Before writing each program, explicitly choose a different reasoning strategy.

If two programs use similar primitives (e.g., both use compress + downscale),
they will be considered invalid.

nan values correspond to exceptions that are explained by tracebacks and must be corrected by analyzing them.

Generate 5 new structurally diverse hypotheses of plausible DSL programs exploring different transformations issued from the step 2.

EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION:
```python
def dsl1(I):
    # O = ...
    return O

def dsl2(I):
    # O = ...
    return O

def dsl3(I):
    # O = ...
    return O

def dsl4(I):
    # O = ...
    return O

def dsl5(I):
    # O = ...
    return O
```