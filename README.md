# MineSweeperSolver
自動でマインスイーパーを解いてくれるやつ

## Require
使用させていただいたマインスイーパー : [Total Minesweeper](https://www.microsoft.com/store/productId/9P9W03N34992?ocid=pdpshare "from MS Store")
```python
# pip install pyautogui
import pyautogui as pgui
# pip install pillow
from PIL import Image
```
Setting:  
![Setting](https://github.com/elsy0111/MineSweeperSolver/blob/master/img/number(Not_Using)/to_readme_setting.png)  
私は画面が QHD(2560 x 1440 px) の環境で行っていますので、動かしたい場合は `img/face.png` を撮り直して `lib > div = 32` を変更するといいと思います。(この32は各マス間の距離なので H,W のマスの個数の32とは関係ありません)

## Run
```shell
>>> pwd
...\MineSweeper_SOLVER
>>> py .\main.py
```

## Description
プレイ画面:  
![Screen](https://github.com/elsy0111/MineSweeperSolver/blob/master/img/number(Not_Using)/to_readme.png)

### 盤面の取得  
まずは表示されている盤面をとらなければなりません。  
そのために、ウィンドウのある座標を基準として座標をとる必要があります。  
今回は上部中央に表示されている黄色いにこちゃんマークの座標を取得し、そこから基準をとります。


```python
image_path = 'img/face.png'

def pos_origin():
    location = pgui.locateOnScreen(image_path)
    if location:
        cx, cy = location[0], location[1]
        ox, oy = cx - 458, cy + 125
    else:
        ox = oy = -1
    return (ox, oy)
```
`ox, oy` は左上の座標です。

盤面の取得は `lib.getmap()` 関数で行っており、左上から右下のスクリーンショットを１枚撮った後、各マスの中心の色(`lib.cell(v)`)を見て、マスを判別しています。

```python
def get_map():
    ox, oy = pos_origin()
    im = pgui.screenshot('img/src.png', region=(ox_, oy_, 32 * div, 32 * div))
    res = [[0 for _ in range(32)]for _ in range(32)]
    for i in range(32):
        for j in range(32):
            lx, ty = j * div, i * div
            im_crop = im.crop((lx, ty, lx + div, ty + div))
            
            res[i][j] = cell(im_crop.getpixel((15, 17)))
    return res
```

```python
def cell(v):
    if   v == (  0,   0, 255):
        return 1
    ...
    elif v == (128,   0, 128):
        return 6
```

### solver  
ソルバですが、非常にシンプルなものです。  
現在の盤面を `v`, 旗の有無を `f` とするとき、全てのマスに対して以下の操作を行います。  
```python
while 1: for i in H: for j in W:
    IF v[i][j] == 数字:
        IF 周り8方向の壁の個数 == v[i][j]:
            f[周り8方向の壁の座標] = True
        ELSE IF 周り8方向の旗の個数 == v[i][j]:
            dig(旗が立っていない座標)
```
あとは `click(i, j)` 関数とかを作っておけばすぐに作れるでしょう。
