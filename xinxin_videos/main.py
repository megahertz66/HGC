import tkinter
from tkinter.filedialog import askdirectory
from tkinter import ttk

import threadDown
from getVideos import getEveryM3u8


global O_path 
global O_maxPro
global O_button
global O_canvas

# 显示标题
# 
def printTitle(where):
    appTitle = tkinter.Label(where, 
                            text='选择文件，并选择线程数量',     # 标签的文字
                            bg='yellow',                  # 背景颜色
                            font=('Arial', 12),          # 字体和字体大小
                            width=200, height=2           # 标签长宽)
                            )
    appTitle.pack()

# 显示文件夹
# 方便又快捷
def printSelectFile(where):
    #选择文件夹
    def selectPath():
        path_ = askdirectory()
        path.set(path_)

    path = tkinter.StringVar()

    tkinter.Label(where, text="目标路径").grid(row=0, column=0)
    filePath = tkinter.Entry(where, width='60', textvariable=path)
    filePath.grid(row=0, column=1)
    tkinter.Button(where, text="选择路径", command=selectPath).grid(row=0, column=2)
    return filePath

# 放置滑块表示将要创建进程的数量
# TODO：如果选择的进程过多而文件却特别少，那么就按照文件数量自行安排进程数
def putScale(where):
    # 放一个Label用于显示滑块的刻度
    l = tkinter.Label(where, bg='blue', fg='white', width=40, text='empty')
    l.pack()
    # 定义一个触发函数功能

    def printInLabel(v):
        l.config(text='you have selected  -' + v + '-')

    #放滑块
    s = tkinter.Scale(where, from_=1, to=50, orient=tkinter.HORIZONTAL, 
                    length=300, showvalue=5,tickinterval=9, resolution=1, command=printInLabel)
    s.pack()
    return s

# 放置开始按钮
#
def putButton(where):
    button1 = tkinter.Button(where, text="开始下载", command=func, width='10', height='2')
    button1.pack(expand='no', fill='none')
    return button1

# 按钮动作
def func():
    # print(getEveryM3u8(O_path.get()))
    # print(O_maxPro.get())
    threadDown.threadRun(getEveryM3u8(O_path.get()), O_maxPro.get(), len(getEveryM3u8(O_path.get())))
    O_button["text"] = "正在下载"
    O_button["state"] = "disable"

# 放置进度条
def putHorizontalBar(where):
    tkinter.Label(where, text='下载进度:', ).pack(side='left')
    canvas = tkinter.Canvas(where, width=400, height=25, bg="red")
    # canvas.create_rectangle(0, 0, 100, 25, fill="green")
    canvas.pack(side='left')
    return canvas

# 进度条动作, 最好不要每次都更新进度条
def barAction(O_bar, whereBar,  now, all):
    pos =  (now * 400) // all
    O_bar.create_rectangle(0, 0, pos, 25, fill="green")
    whereBar.update()


####################################################################################################

def main():
    global O_path 
    global O_maxPro
    global O_button
    global O_canvas

    #建立窗口
    win = tkinter.Tk()
    win.title("Welcome!")
    win.geometry("600x600+200+50")
    # 主frame
    frameRoot = ttk.Frame(win)
    frameRoot.pack()

    # frameTitle 放置标题
    frameTitle = tkinter.Frame(frameRoot)
    printTitle(frameTitle)
    # frameTitle 放置标题
    frameSelect = ttk.Frame(frameRoot)
    O_path = printSelectFile(frameSelect)
    # 放置滑块frame
    frameScale = ttk.Frame(frameRoot)
    O_maxPro =  putScale(frameScale)
    # 放置按钮
    frameButton = ttk.Frame(frameRoot)
    O_button = putButton(frameButton)
    # 放置进度条
    frameBar = ttk.Frame(frameRoot)
    O_canvas = putHorizontalBar(frameBar)

    #放置布局
    frameTitle.pack(pady=40)
    frameSelect.pack(pady=40)
    frameScale.pack(pady=40)
    frameButton.pack(pady=20)
    frameBar.pack()

    for i in range(0, 10000, 100):
        barAction(O_canvas, frameBar, i, 10000)
        print(i)

    win.mainloop()

if __name__ == "__main__":
    main()
