import threading

def dowLoadFile(fileUrl):
    r = requests.get(fileUrl)
    openUrl = fileUrl[:fileUrl.rfind(".")-1]+".ts"
    with open(openUrl , "wb") as code:
        code.write(r.content)
    return openUrl

def downPros(file_path, down_num, region):
    for i in range(0, down_num):
        downURL(file_path[region + i])

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
        print(down_region)
        if i <= down_cnt:
            t = threading.Thread(target=downPros, args=(file_path, down_num + 1, down_region))
            down_region = down_region + down_num + 1
        else:
            t = threading.Thread(target=downPros, args=(file_path, down_num, down_region))
            down_region = down_region + down_num
        t.start()  # 启动线程，即让线程开始执行