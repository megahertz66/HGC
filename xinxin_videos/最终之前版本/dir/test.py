import os
import requests
import re

path = r"G:\Mygithub\HGC\xinxin_videos\2019-精讲班-测试\第一章-第二节-法律行为与代理3\b570d7dea311f96530b3d66d2a44784d932814b2115922179085712118m3u960_100com.m3u8"

# def dowLoadFile(fileUrl):
#     a = os.path.normpath(fileUrl)
#     r = requests.get(a)
#     openUrl = fileUrl[:fileUrl.rfind(".")-1]+".ts"
#     with open(openUrl , "wb") as code:
#         code.write(r.content)
#     return openUrl

def downLoadFile(fileUrl):
    i = 0
    openUrl = fileUrl[:fileUrl.rfind(".") - 1] + ".ts"
    file = open(fileUrl)
    while True:
        fileInLine = file.readline()
        if not fileInLine:
            break
        fileUrl = re.findall(r'^http\S+', str(fileInLine))
        if len(fileUrl):
            url = str(fileUrl[0])
            r = requests.get(url)
            with open(openUrl, "wb") as code:
                code.write(r.content)
            return openUrl

downLoadFile(path)

# file = open(fileM3u8)
# url = ''
# i = 0
# dirM3u8 = os.path.dirname(fileM3u8)
#
# while True:
#
#     fileInLine = file.readline()
#     if not fileInLine:
#         break
#     fileUrl = re.findall(r'^http\S+', str(fileInLine))
#     if len(fileUrl):
#         i = i+1
#         url = str(fileUrl[0])
#         print(url)
#         r = requests.get(url)
#         tmpFileName = "file%d"% i
#         with open(str(dirM3u8) + "//"+str(tmpFileName)+".ts", "wb") as code:
#              code.write(r.content)