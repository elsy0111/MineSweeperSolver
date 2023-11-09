import pyautogui as pgui
SIZE = 39
import solver
import lib

M = lib.get_map()
F = [[0 for _ in range(SIZE)] for _ in range(SIZE)]

solver.solve(M, F)
