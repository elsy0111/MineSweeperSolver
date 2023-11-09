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

## Run
```shell
>>> pwd
...\MineSweeper_SOLVER
>>> py .\main.py
```

プレイ画面:

![Screen](https://github.com/elsy0111/MineSweeperSolver/blob/master/img/src.png)

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
