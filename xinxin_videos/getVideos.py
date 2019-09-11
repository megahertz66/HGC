import re
import os

# 解析下载网址,返回可用的下载网址
def getWebAddress(fileName):
    webArray=[]
    file = open(fileName)

    while True:
        fileInLine = file.readline()
        if not fileInLine:
            break
        fileUrl = re.findall(r'^http\S+', str(fileInLine))
        if(len(fileUrl)):
            webArray.append(fileUrl)
    return webArray


# 进入目录
def getFileInDir(dirName):
    os.listdir(os.getcwd)