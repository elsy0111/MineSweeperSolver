import lib
from collections import deque

SIZE_W = 48
SIZE_H = 39

def in_board(i, j):
    return (0 <= i < SIZE_H and 0 <= j < SIZE_W)

d = [
     (-1, -1), 
     (-1,  0), 
     (-1,  1), 
     ( 0,  1), 
     ( 1,  1), 
     ( 1,  0), 
     ( 1, -1), 
     ( 0, -1)
     ]

def around(i, j, v, f):
    Find = 0
    s = []
    s_= []
    for D in d:
        dx, dy = D
        ny = i + dy
        nx = j + dx
        if in_board(ny, nx):
            if v[ny][nx] == 0:
                s.append((ny, nx))
                if f[ny][nx]:
                    s_.append((ny, nx))
            else:
                None
    return s, s_

dir = [(-1, 0), (1, 0), (0, -1), (0, 1)]

def solve():
    v = lib.get_map()
    f = [[0 for _ in range(SIZE_W)] for _ in range(SIZE_H)]
    for i in range(SIZE_H):
        for j in range(SIZE_W):
            if v[i][j] != 0:
                (start_i, start_j) = (i, j)
    while(1):
        # lib.is_arrive()
        v = lib.get_map()

        visited = [[False] * SIZE_W for _ in range(SIZE_H)]
        queue = deque([(start_i, start_j)])
        visited[start_i][start_j] = True
        while queue:
            current_i, current_j = queue.popleft()
            for di, dj in dir:
                i, j = current_i + di, current_j + dj
                if in_board(i, j) and v[i][j] != -1 and not visited[i][j]:
                    queue.append((i, j))
                    visited[i][j] = True

                    s, s_ = around(i, j, v, f)
                    if len(s) == v[i][j]:
                        for c in s:
                            if not f[c[0]][c[1]]:
                                print("bomb :", c[0], c[1])
                                lib.click(c[0], c[1], left = 0)
                                f[c[0]][c[1]] = 1
                    elif len(s_) == v[i][j] and v[i][j] != 0: 
                        for c in s:
                            print("safe :", c[0], c[1])
                            lib.click(c[0], c[1], left = 1)

