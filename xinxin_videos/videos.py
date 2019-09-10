import requests

def downLoadThread(path, num):
    pathLengh = len(path)
    pass


def dowLoadFile(fileUrl):
    r = requests.get(fileUrl)
    openUrl = fileUrl[:fileUrl.rfind(".")-1]+".ts"
    with open(openUrl , "wb") as code:
        code.write(r.content)
    return openUrl



