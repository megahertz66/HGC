import requests

def downLoadThread(path, num):
    pathLengh = len(path)
    pass

# 根据完整的文件路径信息进行下载，
# 保存的位置就是路径所在位置，文件名称最后以.ts结尾
def dowLoadFile(fileUrl):
    r = requests.get(fileUrl)
    openUrl = fileUrl[:fileUrl.rfind(".")-1]+".ts"
    with open(openUrl , "wb") as code:
        code.write(r.content)
    return openUrl



