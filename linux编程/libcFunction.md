# all of printf

> The functions in the printf() family produce output according to a  format  as  described  below. The  functions  printf()  and  vprintf()  write  output  to  stdout,  the standard output stream;fprintf() and vfprintf()  write  output  to  the  given  output  stream;  sprintf(),  snprintf(),
vsprintf() and vsnprintf() write to the character string str.   ---------man  printf(3)


## sprintf
`int sprintf(char *str, const char *format, ...);`
- *str 是一个指向一块空闲内存的指针，用于存放c字符串
- *format 是字符串格式化字符串
- ... 就是要被格式化之后存到str中的字符指针

## snprintf
` int snprintf(char *str, size_t size, const char *format, ...);`
这个用法和sprintf差不多，n是为了要求一下格式化的字符个数。这样安全。

## vsprintf
`int vsprintf(char *str, const char *format, va_list ap);`
前两个参数可以参考sprintf。重点最后一个参数。这东西是为了可以使用可变参。   
- 为了在参数中能加上...使之变为可变参函数，就要引用头文件 stdarg.h，其中定义va_list类型  
``` c
va_list ap   			/* 就等价于char *ap，定义一个指针 */
va_start(ap, format)    /* 就是将指针ap移动到第一个可变参数的地方 */
va_arg(ap, 变量类型)     /* 返回当前ap指针指向的值，然后指向下一个可变参数 */
va_end                  /* 将指针请为NULL */
```
就是va_start第二个参数一般就是写可变参数的前一个参数。就是写...之前的那个参数。  
- 那个format参数就是和printf格式化输出是一回事。  
- str就是指向被写入空间的指针。  

## vsnprintf
`int vsnprintf(char *str, size_t size, const char *format, va_list ap);`   
- 参数和上面的vsprintf基本一样就是多了个size参数，用来说明最大写入个数。