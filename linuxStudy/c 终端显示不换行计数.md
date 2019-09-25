# c语言如何实现终端显示计数而不换行  

今天启动程序的时候发现可以始终在一行刷新计数。之前并没有注意过这个东西。  
打算实现一下。  

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
	int i = 0;
	
	for(i; i<=100; i++){
		printf("Now ------> %3d%%\r", i);
		sleep(1);
		fflush(stdout);
	}
	return 0;
}
```  

因为要输出%所以需要使用2个%  
\r 是回车键的意思，\n是换行，本质区别就是\r会回到开头并且覆盖掉原先的输入。  

关于fflush函数：  
> man 手册： 
	For  output  streams,  fflush()  forces a write of all user-space buffered data for the given output or update
	stream via the stream's underlying write function.

	For input streams associated with seekable files (e.g., disk files, but not pipes or terminals), fflush() dis‐
	cards  any  buffered  data  that  has  been fetched from the underlying file, but has not been consumed by the
	application    
	
> StackOverflow :  
	You would use fflush(stdout) to ensure that whatever you just wrote in a file/the console is indeed written out on disk/the console.
	The reason is that actually writing, whether to disk, to the terminal, or pretty much anywhere else, is pretty slow.  
	Further, writing 1 byte takes roughly the same time as writing, say, a few hundred bytes[1].   
	Because of this, data you write to a stream is actually stored in a buffer which is flushed when it is full or when you call fflush.  
	Calling fflush means you are accepting that your function call will take a bit of time but that you are 100% sure that you want this out right away.




