import win32api,win32gui,win32con
from ctypes import *
import time
import math
import pyHook
import pythoncom


#  左键单击
def clickLefCur():
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN | win32con.MOUSEEVENTF_LEFTUP, 0, 0)

# 移动鼠标到指定位置
def moveCurPos(x, y):
    time.sleep(0.01)
    windll.user32.SetCursorPos(x, y)

# 获取鼠标位置
def getCurPos():
    return win32gui.GetCursorPos()

# 移动指定位置并点击
def moveAndClick(x, y):
    moveCurPos(x, y)
    clickLefCur()

# 圆的半径
r = 100

# 画圆在x,y上
def drawRound(x, y):
    for angle in range(0,100):
        posX = int(math.sin(2 * math.pi * (angle/100) ) * r + x)
        posY = int(math.cos(2 * math.pi * (angle/100)) * r  + y)
        moveCurPos(posX, posY)
        moveAndClick()


# 画三角形的三个点
def drawTriangle(x, y):
    posX = int(x + r // 2)
    posY = y
    moveAndClick(posX, posY)
    posX = x
    posY = int(y - r // 2)
    moveAndClick(posX, posY)
    posX = int(x - r // 2)
    posY = y
    moveAndClick(posX, posY)

# 监听左键点击事件
def leftDown(event):
    global num
    num += 1
    print("left is down!")
    return True

# 监听鼠标左键
def listenLeftClick():
    hm = pyHook.HookManager()
    hm.MouseLeftDown = leftDown
    hm.HookMouse()

    # 进入循环，如不手动关闭，程序将一直处于监听状态
    pythoncom.PumpMessages()

def main():
    listenLeftClick()
    pass

if __name__ == '__main__':
    # time.sleep(1)
    # nowPos = getCurPos()
    # #drawRound(nowPos[0], nowPos[1])
    # drawTriangle(nowPos[0], nowPos[1])
    num = 0
    main()























