# Linux NetLink  

Netlink 是一种特殊的 socket，它是 Linux 所特有的，类似于 BSD 中的AF_ROUTE 但又远比它的功能强大,  
目前在最新的 Linux 内核（2.6.14）中使用netlink 进行应用与内核通信的应用很多,   
 
**包括**：    

	路由 daemon（NETLINK_ROUTE），1-wire 子系统（NETLINK_W1），用户态 socket 协议（NETLINK_USERSOCK），  
	
	防火墙（NETLINK_FIREWALL），socket 监视（NETLINK_INET_DIAG），netfilter 日志（NETLINK_NFLOG），    
	
	ipsec 安全策略（NETLINK_XFRM），SELinux 事件通知（NETLINK_SELINUX），iSCSI 子系统（NETLINK_ISCSI），    
	
	进程审计（NETLINK_AUDIT），转发信息表查询 （NETLINK_FIB_LOOKUP），netlink connector(NETLINK_CONNECTOR),    
	
	netfilter 子系统（NETLINK_NETFILTER），IPv6 防火墙（NETLINK_IP6_FW），DECnet 路由信息（NETLINK_DNRTMSG），    
	
	内核事件向用户态通知（NETLINK_KOBJECT_UEVENT），通用 netlink（NETLINK_GENERIC）。
	
	
## NetLink 相较于其他实现方式的优点

Netlink 相对于系统调用，ioctl 以及 /proc 文件系统而言具有以下优点：

1. 为了使用 netlink，用户仅需要在 include/linux/netlink.h 中增加一个新类型的 netlink 协议定义即可， 如 #define NETLINK_MYTEST 17 然后，内核和用户态应用就可以立即通过 socket API 使用该 netlink 协议类型进行数据交换。但系统调用需要增加新的系统调用，ioctl 则需要增加设备或文件， 那需要不少代码，proc 文件系统则需要在 /proc 下添加新的文件或目录，那将使本来就混乱的 /proc 更加混乱。
  
2. netlink是一种异步通信机制，在内核与用户态应用之间传递的消息保存在socket缓存队列中，发送消息只是把消息保存在接收者的socket的接 收队列，而不需要等待接收者收到消息，但系统调用与 ioctl 则是同步通信机制，如果传递的数据太长，将影响调度粒度。
  
3. 使用 netlink 的内核部分可以采用模块的方式实现，使用 netlink 的应用部分和内核部分没有编译时依赖，但系统调用就有依赖，而且新的系统调用的实现必须静态地连接到内核中，它无法在模块中实现，使用新系统调用的应用在编译时需要依赖内核。
  
4. netlink 支持多播，内核模块或应用可以把消息多播给一个netlink组，属于该neilink 组的任何内核模块或应用都能接收到该消息，内核事件向用户态的通知机制就使用了这一特性，任何对内核事件感兴趣的应用都能收到该子系统发送的内核事件，在 后面的文章中将介绍这一机制的使用。
  
5. 内核可以使用 netlink 首先发起会话，但系统调用和 ioctl 只能由用户应用发起调用。
  
6. netlink 使用标准的 socket API，因此很容易使用，但系统调用和 ioctl则需要专门的培训才能使用。  


## 用户态 和 内核态  

用户态应用使用标准的socket APIs， socket(), bind(), sendmsg(), recvmsg() 和 close() 就可以完成对netlink的使用。  

*注意，使用netlink需要包含 #include<link/netlink.h> 文件*  

`socket(AF_NETLINK, SOCK_RAM, netlink_type);`  

第一个参数必须是 AF_NETLINK 或 PF_NETLINK，在 Linux 中，它们俩实际为一个东西，它表示要使用netlink，  
第二个参数必须是SOCK_RAW或SOCK_DGRAM， 第三个参数指定netlink协议类型，如前面讲的用户自定义协议类型NETLINK_MYTEST，   
NETLINK_GENERIC是一个通用的协议类型，它是专门为用户使用的，因此，用户可以直接使用它，而不必再添加新的协议类型。  
内核预定义的协议类型有:  

```c
#define NETLINK_ROUTE           0       /* Routing/device hook                          */
#define NETLINK_W1              1       /* 1-wire subsystem                             */
#define NETLINK_USERSOCK        2       /* Reserved for user mode socket protocols      */
#define NETLINK_FIREWALL        3       /* Firewalling hook                             */
#define NETLINK_INET_DIAG       4       /* INET socket monitoring                       */
#define NETLINK_NFLOG           5       /* netfilter/iptables ULOG */
#define NETLINK_XFRM            6       /* ipsec */
#define NETLINK_SELINUX         7       /* SELinux event notifications */
#define NETLINK_ISCSI           8       /* Open-iSCSI */
#define NETLINK_AUDIT           9       /* auditing */
#define NETLINK_FIB_LOOKUP      10
#define NETLINK_CONNECTOR       11
#define NETLINK_NETFILTER       12      /* netfilter subsystem */
#define NETLINK_IP6_FW          13
#define NETLINK_DNRTMSG         14      /* DECnet routing messages */
#define NETLINK_KOBJECT_UEVENT  15      /* Kernel messages to userspace */
#define NETLINK_GENERIC         16
```

对于每一个netlink协议类型，可以有多达 32多播组，每一个多播组用一个位表示，netlink 的多播特性使得发送消息给同一个组仅需要一次系统调用，  
  
因而对于需要多拨消息的应用而言，大大地降低了系统调用的次数。

函数 bind() 用于把一个打开的 netlink socket 与 netlink 源 socket 地址绑定在一起。netlink socket 的地址结构如下：  

```c 
struct sockaddr_nl
{
  sa_family_t    nl_family;
  unsigned short nl_pad;
  __u32          nl_pid;
  __u32          nl_groups;
};
```
字段 nl_family 必须设置为 AF_NETLINK 或着 PF_NETLINK，字段 nl_pad 当前没有使用，因此要总是设置为 0，  

字段 nl_pid 为接收或发送消息的进程的 ID，如果希望内核处理消息或多播消息，就把该字段设置为 0，  

否则设置为处理消息的进程 ID。字段 nl_groups 用于指定多播组，bind 函数用于把调用进程加入到该字段指定的多播组，  

如果设置为 0，表示调用者不加入任何多播组。

传递给 bind 函数的地址的 nl_pid 字段应当设置为本进程的进程 ID，这相当于 netlink socket 的本地地址。  

但是，对于一个进程的多个线程使用 netlink socket 的情况，字段 nl_pid 则可以设置为其它的值，如：













  

