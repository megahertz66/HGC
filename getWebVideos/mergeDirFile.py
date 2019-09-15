import os

def getMergeFilesNameArray(pathArray):
    longName = ""
    for smartFile in pathArray:
        longName += smartFile+" + "
    delpos = longName.rfind("+")
    return longName[:delpos-1]

# 传入一个文件夹中含有下载好的视频，和存放位置的绝对路径
def MergeFile(pathArray, savePos):
    longName = ""
    reallyPos = "  "+savePos+r"\complete.ts"
    longName = getMergeFilesNameArray(pathArray)
    cmdName = "copy /b "+longName+ reallyPos
    print(cmdName)
    d = os.system(cmdName)
    # print(str(d).encode('utf-8'))



# MergeFile函数使用
def mergeDirFile(filepath):
    dirArray = []
    pathDir =  os.listdir(filepath)
    for allDir in pathDir:
        child = os.path.normpath(r'%s\\%s' % (filepath, allDir))
        dirArray.append(child)
    saveFilePath = os.path.normpath(filepath)
    MergeFile(dirArray, saveFilePath)
    print("merge ok !")
