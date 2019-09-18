import urllib 

print("downloading with urllib")
url = 'http://edu100hqvideo.bs2cdn.100.com/d69a42a88e4b4b5414852be83cbdb1e753f43bd3113680272911447391m3u960.ts?s=0&e=190255'
urllib.urlretrieve(url, "001.ts")