 import re
import os


# 解析下载网址,返回解析后的列表
def getWebAddress(fileName):
    fileArray = []
    file = open(fileName)
    while True:
        fileInLine = file.readline()
        if not fileInLine:
            break
        fileUrl = re.findall(r'^http\S+', str(fileInLine))
        if len(fileUrl):
            fileArray.append(fileUrl)
    return fileArray


# 遍历指定目录，显示目录下的所有文件名
def eachFile(filepath):
    dirArray = []
    pathDir =  os.listdir(filepath)
    for allDir in pathDir:
        child = os.path.normpath(r'%s\\%s' % (filepath, allDir))
        dirArray.append(child)
    return dirArray

# 遍历指定目录，拿到下面的 .m3u8 为后缀的文件
def getEveryM3u8(filepath):
    realyArray = []
    m3u8Array  = []
    M3u8 = eachFile(filepath)
    for file in M3u8:
        a = os.path.normpath(file)
        childFile = os.listdir(a)   #找到其中的m3u8
        for m3u8File in childFile:
            trueFile = re.findall(r'\S+\.m3u8', str(m3u8File))
            realyArray.append(trueFile)
        for m3u8Name in realyArray:
            m3u8Path = os.path.normpath(r'%s\\%s' % (file, m3u8Name[0] ))
            m3u8Array.append(m3u8Path)
    return m3u8Array
    # return childFile






