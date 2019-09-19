import requests
import json
"""
写的有点跑偏，学习了一下 python怎么调用公用api接口
"""
# https://www.avatardata.cn/  阿凡达数据
# https://www.juhe.cn/ 聚合数据

# http://api.avatardata.cn/Weather/Query?key=dde7710b3cea4b0c9083b444b00ba6db&cityname=武汉

url = r"http://api.avatardata.cn/Weather/Query"

USurl = r"https://www.mycurrency.net/US.json"

appkey = r"dde7710b3cea4b0c9083b444b00ba6db"

cityname = r"苏州"

headers = {r"User-Agent": r"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36"}

payload = {"key": appkey, "cityname": cityname}

#r=requests.get(url, params=payload, headers=headers)

r=requests.get(USurl, headers=headers)
sdw=r.content.decode('utf-8')

lks=json.loads(sdw)

#print(lks["result"]["realtime"]["wind"])
print(lks)
