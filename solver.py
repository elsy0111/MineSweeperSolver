import lib

SIZE = 39

def in_board(i, j):
    return (0 <= i < SIZE and 0 <= j < SIZE)

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

def solve(v, f):
    while(1):
        for i in range(SIZE):
            v = lib.get_map()
            for j in range(SIZE):
                # print(i, j)
                if v[i][j] == 9:
                    f[i][j] = 1
                    v[i][j] = -1
                    continue
                if v[i][j] == -1 or f[i][j]:
                    continue
                s, s_ = around(i, j, v, f)
                if len(s) == v[i][j]:
                    for c in s:
                        if not f[c[0]][c[1]]:
                            print("bomb :", c[0], c[1])
                            lib.click(c[0], c[1], left = 0)
                            f[c[0]][c[1]] = 1
                elif len(s_) == v[i][j] and v[i][j] != 0: #len(s) == 0, len(s_) == v[i][j]
                    for c in s:
                        print("safe :", c[0], c[1])
                        lib.click(c[0], c[1], left = 1)

