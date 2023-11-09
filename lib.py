import pyautogui as pgui
from PIL import Image
from time import sleep
from pynput.mouse import Controller, Button

image_path = 'img/corner.png'
div = 32
SIZE_W = 48
SIZE_H = 39

mouse = Controller()

def pos_origin():
    location = pgui.locateOnScreen(image_path)
    if location:
        cx, cy = location[0], location[1]
        ox, oy = cx + div * 2 - 3, cy + div * 2 - 5 
    else:
        ox = oy = -1
    return (ox, oy)

ox, oy = pos_origin()

def click(j, i, left = 1):
    if left:
        print("dig  :", i, j)
        # pgui.click(ox + i * div, oy + j * div)
        mouse.position = (ox + i * div, oy + j * div)
        sleep(.02)
        mouse.click(Button.left, 1)
        sleep(.02)
    else:
        print("flag :", i, j)
        # pgui.click(ox + i * div, oy + j * div, button="right")
        mouse.position = (ox + i * div, oy + j * div)
        sleep(.02)
        mouse.click(Button.right, 1)
        sleep(.02)

def cell(v):
    if   v == (  0,   0, 255):
        return 1
    elif v == (  0, 128,   0):
        return 2
    elif v == (255,   0,   0):
        return 3
    elif v == (  0,   0, 128):
        return 4
    elif v == (128,   0,   0):
        return 5
    elif v == (192, 192, 192):
        return -1
    elif v == (174, 189, 223):
        return 0
    elif v == (  0,   0,   0):
        return 0
    elif v == (128,   0, 128):
        return 6

dead_img = "img/dead.png"

def is_arrive():
    dead  = pgui.locateOnScreen(dead_img)
    if dead:
        print("DEAD :( ")
        exit()

def get_map(debug = 0):
    # ox, oy = pos_origin()
    ox_ = ox - 16; 
    oy_ = oy - 16; 

    pgui.screenshot('img/src.png', region=(ox_, oy_, 
                                           SIZE_W * div, SIZE_H * div))
    im = Image.open('img/src.png').convert('RGB')

    res = [[0 for _ in range(SIZE_W)] for _ in range(SIZE_H)]
    for i in range(SIZE_H):
        for j in range(SIZE_W):
            lx, ty = j * div, i * div
            im_crop = im.crop((lx, ty, lx + div, ty + div))
            res[i][j] = cell(im_crop.getpixel((16, 16)))
    if debug:
        for i in res:
            for p in i:
                if p == -1:
                    print(" ", end = "")
                else:
                    print(p, end = "")
            print()
    return res

