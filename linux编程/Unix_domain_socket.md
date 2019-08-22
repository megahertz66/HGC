# Unix domain socket  
liux中的一种进程间通信方式就是通过网络套接字进行通讯的。  
> UNIX domain sockets are used to communicate with processes running on the same machine. Although Internet domain sockets can be used for this same purpose, UNIX domain sockets are more efficient. UNIX domain sockets only copy data; they have no protocol processing to perform, no network headers to add or remove, no checksums to calculate, no sequence numbers to generate, and no acknowledgements to send.  --------from APUE 17.3  
> 
## 创建套接字
```c
 #include <sys/types.h>         
 #include <sys/socket.h>
 int socket(int domain, int type, int protocol);
```
和正常创建套接字使用的API是相同的，只不过参数不同。  
**第一个参数**使用AF_LOCAL 或者 AF_UNIX，还有的代码里面是PF_LOCAL或者PFUNIX，在man手册中解释是，P开头的是低版本使用的。
**第二个参数**可以选择数据报或者流式数据对应SOCKTET_DGAM和SOCKET_STREAM  
**第三个参数**设置为0