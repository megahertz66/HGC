import threading
# import requests

# 根据完整的文件路径信息进行下载，
# 保存的位置就是路径所在位置，文件名称最后以.ts结尾
def dowLoadFile(fileUrl):
    r = requests.get(fileUrl)
    openUrl = fileUrl[:fileUrl.rfind(".")-1]+".ts"
    with open(openUrl , "wb") as code:
        code.write(r.content)
    return openUrl

# 每次下载的文件个数以及在列表中所在的位置
def downPros(file_path, down_num, region):
    for i in range(0, down_num):
        # dowLoadFile(file_path[region + i])
        print(file_path[region + i])


def threadRun(file_path, thread_num, dir_num):

    down_num = 0
    down_cnt = 0
    down_region = 0
    
    if dir_num <= thread_num:
        down_cnt = dir_num
    else:
        down_num = dir_num // thread_num
        down_cnt = dir_num % thread_num

    for i in range(1, thread_num + 1):
        #print(down_region)
        if i <= down_cnt:
            t = threading.Thread(target=downPros, args=(file_path, down_num + 1, down_region))
            down_region = down_region + down_num + 1
        else:
            t = threading.Thread(target=downPros, args=(file_path, down_num, down_region))
            down_region = down_region + down_num
        t.start()  # 启动线程，即让线程开始执行
