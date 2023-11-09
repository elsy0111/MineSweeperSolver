import pyautogui as pgui

import solver
import lib

M = lib.get_map()
F = [[0 for _ in range(32)] for _ in range(32)]

solver.solve(M, F)
