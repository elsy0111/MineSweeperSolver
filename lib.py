import pyautogui as pgui
from PIL import Image

image_path = 'img/corner.png'
div = 32
SIZE = 39

def pos_origin():
    location = pgui.locateOnScreen(image_path)
    if location:
        cx, cy = location[0], location[1]
        ox, oy = cx + div * 2 - 4, cy + div * 2 - 6 
        pgui.moveTo(ox, oy)
    else:
        ox = oy = -1
    return (ox, oy)

ox, oy = pos_origin()

def click(j, i, left = 1):
    # ox, oy = pos_origin()
    if ox != -1:
        pgui.moveTo(ox + i * div, oy + j * div)
        if left:
            print("dig  :", i, j)
            pgui.leftClick()
        else:
            print("flag :", i, j)
            pgui.rightClick()
    else:
        print("Window Not Found(on click)")

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
        return 9
    elif v == (128,   0, 128):
        return 6

def get_map():
    # ox, oy = pos_origin()
    ox_ = ox - 16; 
    oy_ = oy - 16; 

    pgui.screenshot('img/src.png', region=(ox_,oy_,SIZE * div,SIZE * div))
    im = Image.open('img/src.png').convert('RGB')

    res = [[0 for _ in range(SIZE)]for _ in range(SIZE)]
    for i in range(SIZE):
        for j in range(SIZE):
            lx, ty = j * div, i * div
            im_crop = im.crop((lx, ty, lx + div, ty + div))
            
            res[i][j] = cell(im_crop.getpixel((15, 17)))
    return res

