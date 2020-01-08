# How To Use Tcpdump

## Parameter Description  

```
-i  specify the network card. (E.g eth0)  
-c  specify the numbers of packets that the Tcpdump can capture 
-v  it can produce more detailed data
-e  it can print the link header data
-D  it can print network interface that can capture packets. (E.g tcpdump -D)
-n  display the address in numbers
-nn in addition to the function of '-n',the port can also be displayed in digital form.
```

## Output Format

### 例一，dns捕获  
`tcpdump -nn -v -i enp1s0 port domain`  
enp1s0  是ubuntu18.04中的网卡名称  
此时在另外一个终端，输入：  
`host www.taobao.com`   
在第一个窗口得到如下输出：  
**插图**   
hh:mm:ss.xxxxxx 表示时间，在手册中提到改时间很精准。  ttl 剩余跳数。 id （ipv4标识 Identification）对于每个数据包都不同，逐个加1。offest分片偏移。flag(DF)不分片（Don‘t Fragment)。proto 协议类型。length 长度，此处包含UDP和IP头部。  
为 src > dst形式，前面为IP地址，最后一个点后面是端口号。’+‘前面是查询编号。 ’+‘ 代表如果服务器不知道答案，向别的服务器请教。*[1au] 暂时不知道*。A?是要知道后面那个网址的地址的意思。（）中数组是此次查询大小的结果，单位字节。  
下面一条， 4/0/1这个使用’/‘隔开的意思是，4条应答记录，0条名称服务器记录，以及1条附加记录(根据tcpdump man手册)。CNAME(别名记录)，后面的A为(Addriess 记录)。这一条的意思是，’www.taobao.com‘ 这个网址是 ’www.taobao.com.danuoyi.tbcache.com‘ 这玩意的别名，这玩意还有四个网址分别是……  
下一条，有了上面得分析接下来得就不是个事了。虽然[1au]依然不知道什么意思！！AAAA? 就是要问问那个几个IP得MAC地址是多少。  
下~， 然后就告诉它，这四个MAC地址都是啥。  
下~， 然后它又问， ’www.taobao.com.danuoyi.tbcache.com‘ 这玩意得记录。MX？，(MX recard 邮件交换记录) 问后面的地址这个记录，解释如下：   
> 邮件交换记录 (MX record)是域名系统（DNS）中的一种资源记录类型，用于指定负责处理发往收件人域名的邮件服务器。MX记录允许设置一个优先级，当多个邮件服务器可用时，会根据该值决定投递邮件的服务器。简单邮件传输协议（SMTP）会根据MX记录的值来决定邮件的路由过程。——百度百科  
> 用于电子邮件系统发邮件时根据收信人的地址后缀来定位邮件服务器。域名的MX记录需要到域名管理界面才可以更改。
例如，当有人发邮件给“vincen@example.com”时，系统将对“example.com”进行DNS中的MX记录解析。如果MX记录存在，系统就根据MX记录的优先级，将邮件转发到与该MX相应的邮件服务器上。 ——腾讯企业邮 帮助中心  

我也不知道为什么要问这个邮箱干什么。反正是问了(再好好研究一下dns协议吧)。  
下~，回了个 0/1/1 这个和上面那个解释不太一样。这个代表答案记录数、域名服务器授权记录、其他记录(貌似和上面是一样的哦，就是换了个叫法。《Effective TCP/IP Programming》中的解释  
**破案了(20.1.7)！**这三个是DNS协议的消息头后6个字节。  
下~， 和上面一模一样就不逐条解释了。  

## 例二，ping包捕获  
窗口1(由于ping是根据icmp协议实现的)：  
`tcpdump -s 1500 -vv -i enp1s0 icmp or ftp`  
窗口2(随便找一个不能成功的连接)：  
`ftp 172.21.2.66`  
**插图**  
从那个icmp报文开始。  
说的比较明白，是网络不可达  
下面还有一个UDP报文，NXDomain 意思是域名不存在。PTR也是一个邮件记录（不懂为什么要这么做）。
下表为完整的ICMPV4 网络不可达报文格式(下方数字为各个部分字节数)：  
| IPV4头 | ICMP头 | 违规数据报IP头 | UDP/TCP头 | 差错数据 |
| ------ | ------ | -------------- | --------- | -------- |
| 20     | 8      | 20             | 8         | <=520    |
> 尽可能包含尽量多的ICMP报文，但是总长度不得超过 20+8+20+8+520=576字节。——TCP/IP卷一原书368页  
> 

## 其他一些使用Tcpdump的例子  
```shell
#抓取所有经过eth1，目的或源端口是25的网络数据
tcpdump -i eth1 port 25  

#指定目的端口 
tcpdump -i eth1 dst port 25  

#指定源端口
tcpdump -i eth1 src port 25

#网络过滤
tcpdump -i eth1 net 192.168
tcpdump -i eth1 src net 192.168
tcpdump -i eth1 dst net 192.168

#协议过滤
tcpdump -i eth1 arp
tcpdump -i eth1 ip
tcpdump -i eth1 tcp
tcpdump -i eth1 udp
tcpdump -i eth1 icmp

#抓大于X字节的包
tcpdump -i eth1 'ip[2:2] > 600'

#抓HTTP get的数据包
tcpdump -i eth1 'tcp[(tcp[12]>>2):4] = 0x47455420'
```
































