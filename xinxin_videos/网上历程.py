import requests
import threading
import datetime
import os

count = 0;


def Handler(start, end, url, filename):
    headers = {'Origin': 'https://xdzy.andisk.com','Referer':'https://xdzy.andisk.com/andisk/app/videoviewFrame.html',
               'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36'}

    for i in filename[start:end]:
        global count

        r = requests.get("https://bk.andisk.com/data/3048aa1f-b2fb-4fb7-b452-3ebc96c76374/res/" + i.replace("\n", ""),
                         headers=headers,
                         stream=True)
  
        with open("C:\\Users\\chen\\Desktop\\downloadfiles/" + i.replace("\n", ""), "wb") as code:
            code.write(r.content)
        count = count + 1
        print("下载进度：%.2f" % (count / len(filename)))


def download_file(url, num_thread=100):
    cwd = os.getcwd()  # 获取当前目录即dir目录下
    print("------------------------current working directory------------------" + cwd)
    f = open('index.m3u8', 'r', encoding='utf-8')
    text_list = f.readlines()
    s_list = []
    for i in text_list:
        if i.find('#EX') == -1:
            s_list.append(i)

    f.close()
    file_size = len(s_list)

    # 启动多线程写文件
    part = file_size // num_thread  # 如果不能整除，最后一块应该多几个字节
    for i in range(num_thread):
        start = part * i
        if i == num_thread - 1:  # 最后一块
            end = file_size
        else:
            end = start + part

        t = threading.Thread(target=Handler, kwargs={'start': start, 'end': end, 'url': url, 'filename': s_list})
        t.setDaemon(True)
        t.start()

    # 等待所有线程下载完成
    main_thread = threading.current_thread()
    for t in threading.enumerate():
        if t is main_thread:
            continue
        t.join()
 
def before_merge():
    cwd = os.getcwd()  # 获取当前目录即dir目录下
    print("------------------------current working directory------------------" + cwd)
    f = open('index.m3u8', 'r', encoding='utf-8')
    text_list = f.readlines()
    files = []
    for i in text_list:
        if i.find('#EX') == -1:
            files.append(i)
    f.close()
    tmp = []
    for file in files[0:568]:
        tmp.append(file.replace("\n", ""))
        # 合并ts文件
    # os.chdir("ts/")
    shell_str = '+'.join(tmp)
    # print(shell_str)
    shell_str = 'copy /b ' + shell_str + ' 5.mp4'+'\n'+'del *.ts'
    return shell_str
    
def wite_to_file(cmdString):
    cwd = os.getcwd()  # 获取当前目录即dir目录下
    print("------------------------current working directory------------------"+cwd)
    f = open("combined.cmd", 'w')
    f.write(cmdString)
    f.close()

if __name__ == '__main__':
    url = "https://bk.andisk.com/data/3048aa1f-b2fb-4fb7-b452-3ebc96c76374/res/";
    # 下载：开始下载
    start = datetime.datetime.now().replace(microsecond=0)
    download_file(url)
    end = datetime.datetime.now().replace(microsecond=0)
    print(end - start)
    # 结束下载
    #合并小文件
    cmd=before_merge();
    #把合并命令写到文件中
    wite_to_file(cmd);