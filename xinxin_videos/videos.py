import requests
import re

file = open("originVideos.m3u8")
url = ''
i = 0


while True:

    fileInLine = file.readline()
    if not fileInLine:
        break
    fileUrl = re.findall(r'^http\S+', str(fileInLine))
    if len(fileUrl):
        i = i+1
        url = str(fileUrl[0])
        print(url)
        r = requests.get(url)
        tmpFileName = "file%d"% i
        with open("./videos/"+str(tmpFileName)+".ts", "wb") as code:
             code.write(r.content)

