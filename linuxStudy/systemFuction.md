# [转]Linux下使用system函数一定要谨慎  

原网址：[system函数](https://blog.csdn.net/frecon/article/details/79783536)  

曾经的曾经，被system()函数折磨过，之所以这样，是因为对system()函数了解不够深入。只是简单的知道用这个函数执行一个系统命令，这远远不够，它的返回值、它所执行命令的返回值以及命令执行失败原因如何定位，这才是重点。当初因为这个函数风险较多，故抛弃不用，改用其他的方法。这里先不说我用了什么方法，这里必须要搞懂system()函数，因为还是有很多人用了system()函数，有时你不得不面对它。

先来看一下system()函数的简单介绍：

2 int system(const char *command);
system() executes a command specified in command by calling /bin/sh -c command, and returns after the command has been completed. During execution of the command, SIGCHLD will be blocked, and SIGINT and SIGQUIT will be ignored.

system()函数调用/bin/sh来执行参数指定的命令，/bin/sh 一般是一个软连接，指向某个具体的shell，比如bash，-c选项是告诉shell从字符串command中读取命令；

在该command执行期间，SIGCHLD是被阻塞的，好比在说：hi，内核，这会不要给我送SIGCHLD信号，等我忙完再说；

在该command执行期间，SIGINT和SIGQUIT是被忽略的，意思是进程收到这两个信号后没有任何动作。

再来看一下system()函数返回值：

The value returned is -1 on error (e.g. fork(2) failed), and the return status of the command otherwise. This latter return status is in the format specified in wait(2). Thus, the exit code of the command will be WEXITSTATUS(status). In case /bin/sh could not be executed, the exit status will be that of a command that does exit(127).

If the value of command is NULL, system() returns nonzero if the shell is available, and zero if not.

为了更好的理解system()函数返回值，需要了解其执行过程，实际上system()函数执行了三步操作：

1.fork一个子进程；

2.在子进程中调用exec函数去执行command；

3.在父进程中调用wait去等待子进程结束。

对于fork失败，system()函数返回-1。

如果exec执行成功，也即command顺利执行完毕，则返回command通过exit或return返回的值。

（注意，command顺利执行不代表执行成功，比如command：”rm debuglog.txt”，不管文件存不存在该command都顺利执行了）

如果exec执行失败，也即command没有顺利执行，比如被信号中断，或者command命令根本不存在，system()函数返回127.

如果command为NULL，则system()函数返回非0值，一般为1.

popen和system都可以执行外部命令。

popen相当于是先创建一个管道，fork，关闭管道的一端，执行exec，返回一个标准的io文件指针。

system相当于是先后调用了fork， exec，waitpid来执行外部命令

popen本身是不阻塞的，要通过标准io的读取使它阻塞

system本身就是阻塞的。
看一下system()函数的源码

看完这些，我想肯定有人对system()函数返回值还是不清楚，看源码最清楚，下面给出一个system()函数的实现：

01 int system(const char * cmdstring)
08 return (1); //如果cmdstring为空，返回非零值，一般为1
13 status = -1; //fork失败，返回-1
17 execl(“/bin/sh”, ”sh”, ”-c”, cmdstring, (char *)0);
18 _exit(127); // exec执行失败返回127，注意exec只在失败时才返回现在的进程，成功的话现在的进程就不存在啦~~
22 while(waitpid(pid, &status, 0) < 0)
24 if(errno != EINTR)
26 status = -1; //如果waitpid被信号中断，则返回-1
27 break;
32 return status; //如果waitpid成功，则返回子进程的返回状态
仔细看完这个system()函数的简单实现，那么该函数的返回值就清晰了吧，那么什么时候system()函数返回0呢？只在command命令返回0时。

看一下该怎么监控system()函数执行状态

这里给我出的做法：

02 if(NULL == cmdstring) //如果cmdstring为空趁早闪退吧，尽管system()函数也能处理空指针popen和system都可以执行外部命令。
popen相当于是先创建一个管道，fork，关闭管道的一端，执行exec，返回一个标准的io文件指针。
system相当于是先后调用了fork， exec，waitpid来执行外部命令
popen本身是不阻塞的，要通过标准io的读取使它阻塞
system本身就是阻塞的。popen和system都可以执行外部命令。
popen相当于是先创建一个管道，fork，关闭管道的一端，执行exec，返回一个标准的io文件指针。
system相当于是先后调用了fork， exec，waitpid来执行外部命令
popen本身是不阻塞的，要通过标准io的读取使它阻塞
system本身就是阻塞的。
06 status = system(cmdstring);
09 printf(“cmd: %s\t error: %s”, cmdstring, strerror(errno)); // 这里务必要把errno信息输出或记入Log
15 printf(“normal termination, exit status = %d\n”, WEXITSTATUS(status)); //取得cmdstring执行结果
17 else if(WIFSIGNALED(status))
19 printf(“abnormal termination,signal number =%d\n”, WTERMSIG(status)); //如果cmdstring被信号中断，取得信号值
21 else if(WIFSTOPPED(status))
23 printf(“process stopped, signal number =%d\n”, WSTOPSIG(status)); //如果cmdstring被信号暂停执行，取得信号值
到于取得子进程返回值的相关介绍可以参考另一篇文章：http://my.oschina.net/renhc/blog/35116

system()函数用起来很容易出错，返回值太多，而且返回值很容易跟command的返回值混淆。这里推荐使用popen()函数替代，关于popen()函数的简单使用也可以通过上面的链接查看。

popen()函数较于system()函数的优势在于使用简单，popen()函数只返回两个值：
成功返回子进程的status，使用WIFEXITED相关宏就可以取得command的返回结果；
失败返回-1，我们可以使用perro()函数或strerror()函数得到有用的错误信息。

这篇文章只涉及了system()函数的简单使用，还没有谈及SIGCHLD、SIGINT和SIGQUIT对system()函数的影响，事实上，之所以今天写这篇文章，是因为项目中因有人使用了system()函数而造成了很严重的事故。现像是system()函数执行时会产生一个错误：“No child processes”。

关于这个错误的分析，感兴趣的朋友可以看一下：http://my.oschina.net/renhc/blog/54582

上面这个链接续上，分割线，篇2——————————————————————————

——————————————————————————————————————-

今天，一个运行了近一年的程序突然挂掉了，问题定位到是system()函数出的问题，关于该函数的简单使用在我上篇文章做过介绍：
http://my.oschina.net/renhc/blog/53580
先看一下问题

简单封装了一下system()函数：

1 int pox_system(const char *cmd_line)
3 return system(cmd_line);
函数调用：

2 ret = pox_system(“gzip -c /var/opt/I00005.xml > /var/opt/I00005.z”);
5 Log(“zip file failed\n”);
问题现象：每次执行到此处，都会zip failed。而单独把该命令拿出来在shell里执行却总是对的，事实上该段代码已运行了很长时间，从没出过问题。

糟糕的日志

system非阻塞方式注意点：’&’转后台，同时将输出重定向。否则变为阻塞方式。system非阻塞方式注意点：’&’转后台，同时将输出重定向。否则变为阻塞方式。system非阻塞方式注意点：’&’转后台，同时将输出重定向。否则变为阻塞方式。分析log时，我们只能看到“zip file failed”这个我们自定义的信息，至于为什么fail，毫无线索。

那好，我们先试着找出更多的线索：

2 ret = pox_system(“gzip -c /var/opt/I00005.xml > /var/opt/I00005.z”);
5 Log(“zip file failed: %s\n”, strerror(errno)); //尝试打印出系统错误信息
我们增加了log，通过system()函数设置的errno，我们得到一个非常有用的线索：system()函数失败是由于“
No child processes”。继续找Root Cause。

谁动了errno

我们通过上面的线索，知道system()函数设置了errno为ECHILD，然而从system()函数的man手册里我们找不到任何有关EHILD的信息。我们知道system()函数执行过程为：fork()->exec()->waitpid()。很显然waitpid()有重大嫌疑，我们去查一下man手册，看该函数有没有可能设置ECHILD：

ECHILD

(for waitpid() or waitid()) The process specified by pid (waitpid()) or idtype and id (waitid()) does not exist or is not a child of the calling process. (This can happen for one’s own child if the action for SIGCHLD is set to SIG_IGN. See also the Linux Notes section about threads.)

果然有料，如果SIGCHLD信号行为被设置为SIG_IGN时，waitpid()函数有可能因为找不到子进程而报ECHILD错误。似乎我们找到了问题的解决方案：在调用system()函数前重新设置SIGCHLD信号为缺省值，即signal(SIGCHLD, SIG_DFL)。我们很兴奋，暂时顾不上看Linux Notes部分，直接加上代码测试！乖乖，问题解决了！

如此处理问题是你的风格吗

正当我们急于check in 代码时，一个疑问出现了：“这个错误为什么以前没发生”？是啊，运行良好的程序怎么突然就挂了呢？首先我们代码没有改动，那么肯定是外部因素了。一想到外部因素，我们开始抱怨：“肯定是其他组的程序影响我们了！”但抱怨这是没用的，如果你这么认为，那么请拿出证据！但静下来分析一下不难发现，这不可能是其他程序的影响，其他进程不可能影响我们进程对信号的处理方式。

system()函数之前没出错，是因为systeme()函数依赖了系统的一个特性，那就是内核初始化进程时对SIGCHLD信号的处理方式为SIG_DFL，这是什么什么意思呢？即内核发现进程的子进程终止后给进程发送一个SIGCHLD信号，进程收到该信号后采用SIG_DFL方式处理，那么SIG_DFL又是什么方式呢？SIG_DFL是一个宏，定义了一个信号处理函数指针，事实上该信号处理函数什么也没做。这个特性正是system()函数需要的，system()函数首先fork()一个子进程执行command命令，执行完后system()函数会使用waitpid()函数对子进程进行收尸。

通过上面的分析，我们可以清醒的得知，system()执行前，SIGCHLD信号的处理方式肯定变了，不再是SIG_DFL了，至于变成什么暂时不知道，事实上，我们也不需要知道，我们只需要记得使用system()函数前把SIGCHLD信号处理方式显式修改为SIG_DFL方式，同时记录原来的处理方式，使用完system()后再设为原来的处理方式。这样我们可以屏蔽因系统升级或信号处理方式改变带来的影响。

验证猜想

我们公司采用的是持续集成+敏捷开发模式，每天都会由专门的team负责自动化case的测试，每次称为一个build，我们分析了本次build与上次build使用的系统版本，发现版本确实升级了。于是我们找到了相关team进行验证，我们把问题详细的描述了一下，很快对方给了反馈，下面是邮件回复原文：

LIBGEN 里新增加了SIGCHLD的处理。将其ignore。为了避免僵尸进程的产生。

看来我们的猜想没错！问题分析到这里，解决方法也清晰了，于是我们修改了我们的pox_system()函数：

01 typedef void (*sighandler_t)(int);
02 int pox_system(const char *cmd_line)
05 sighandler_t old_handler;
07 old_handler = signal(SIGCHLD, SIG_DFL);
08 ret = system(cmd_line);
09 signal(SIGCHLD, old_handler);
我想这是调用system()比较完美的解决方案了，同时使用pox_system()函数封装带来了非常棒的易维护性，我们只需要修改此处一个函数，其他调用处都不需要改。

后来，查看了对方修改的代码，果然从代码上找到了答案：

1 /* Ignore SIGCHLD to avoid zombie process */
2 if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
system非阻塞方式注意点：’&’转后台，同时将输出重定向。否则变为阻塞方式。system非阻塞方式注意点：’&’转后台，同时将输出重定向。否则变为阻塞方式。system非阻塞方式注意点：’&’转后台，同时将输出重定向。否则变为阻塞方式。
其他思考

我们公司的代码使用SVN进程管理的，到目前为止有很多branch，逐渐的，几乎每个branch都出现了上面的问题，于是我逐个在各个branchc上fix这个问题，几乎忙了一天，因为有的branch已被锁定，再想merge代码必须找相关负责人说明问题的严重性，还要在不同的环境上测试，我边做这些边想，系统这样升级合适吗？

首先，由于系统的升级导致我们的代码在测试时发现问题，这时再急忙去fix，造成了我们的被动，我想这是他们的一个失误。你做的升级必须要考虑到对其他team的影响吧？何况你做的是系统升级。升级前需要做个风险评估，对可能造成的影响通知大家，这样才职业嘛。

再者，据他们的说法，修改信号处理方式是为了避免僵尸进程，当然初衷是好的，但这样的升级影响了一些函数的使用方式，比如system()函数、wait()函数、waipid()、fork()函数，这些函数都与子进程有关，如果你希望使用wait()或waitpid()对子进程收尸，那么你必须使用上面介绍的方式：在调用前（事实上是fork()前）将SIGCHLD信号置为SIG_DFL处理方式，调用后（事实上wait()/waitpid()后）再将信号处理方式设置为从前的值。你的系统升级，强制大家完善代码，确实提高了代码质量，但是对于这种升级我不是很认同，试想一下，你见过多少fork()->waitpid()前后都设置SIGCHLD信号的代码？

使用system()函数的建议

上在给出了调用system()函数的比较安全的用法，但使用system()函数还是容易出错，错在哪？那就是system()函数的返回值，关于其返回值的介绍请见上篇文章。system()函数有时很方便，但不可滥用！

1、建议system()函数只用来执行shell命令，因为一般来讲，system()返回值不是0就说明出错了；

2、建议监控一下system()函数的执行完毕后的errno值，争取出错时给出更多有用信息；

3、建议考虑一下system()函数的替代函数popen()；其用法在我的另一篇文章有介绍。

ps:

1.如果waitpid()函数是被信号中断而返回负数的，则继续调用waitpid()函数。

这个包括SIGINT的啊，不违反POSIX.1定义啊

2.system非阻塞方式注意点：’&’转后台，同时将输出重定向。否则变为阻塞方式。

3,

popen和system都可以执行外部命令。

popen相当于是先创建一个管道，fork，关闭管道的一端，执行exec，返回一个标准的io文件指针。

system相当于是先后调用了fork， exec，waitpid来执行外部命令

popen本身是不阻塞的，要通过标准io的读取使它阻塞

system本身就是阻塞的。