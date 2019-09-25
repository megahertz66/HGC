# c语言中结构体位域使用  

```c
/*  1  */
struct foo{
	int mem1:1;
	int mem2:3;
	int mem3:8;
};


/*  2  */
struct foo new{
	.mem3 = 2,
};
``` 

待续……………………
  
结构体位域参考文章：  
  
[C语言位域的定义和使用](https://blog.csdn.net/xxxxxx91116/article/details/9224307)  

[C语言的位域赋值问题](https://blog.csdn.net/sunyubo458/article/details/7695065)   

结构体成员初始化:  
  
[原文连接](https://blog.csdn.net/maochengtao/article/details/50366328)
有关designated initializer的进一步信息可以参考c99标准的6.7.8节Ininialization。  
标准C89需要初始化语句的元素以固定的顺序出现，和被初始化的数组或结构体中的元素顺序一样。  
在ISO C99中，你可以按任何顺序给出这些元素，指明它们对应的数组的下标或结构体的成员名，  
并且GNU C也把这作为C89模式下的一个扩展。这个扩展没有在GNU C++中实现。为了指定一个数组下标，  
在元素值的前面写上“[index] =”。比如： int a[6] = { [4] = 29, [2] = 15 };  
相当于： int a[6] = { 0, 0, 15, 0, 29, 0 };  

为了把一系列的元素初始化为相同的值，写为“[first ... last] = value”。这是一个GNU扩展。  
比如： int widths[] = { [0 ... 9] = 1, [10 ... 99] = 2, [100] = 3 };
如果其中的值有副作用，这个副作用将只发生一次，而不是范围内的每次初始化一次。注意，数组的长度是指定的最大值加一。 
在结构体的初始化语句中，在元素值的前面用“.fieldname = ”指定要初始化的成员名。  
例如，给定下面的结构体， struct point { int x, y; };
和下面的初始化， struct point p = { .y = yvalue, .x = xvalue };
等价于： struct point p = { xvalue, yvalue };
另一有相同含义的语法是“.fieldname:”，不过从GCC 2.5开始废除了，就像这里所示： struct point p = { y: yvalue, x: xvalue };
“[index]”或“.fieldname”就是指示符。在初始化共同体时，你也可以使用一个指示符(或不再使用的冒号语法)，  
来指定共同体的哪个元素应该使用。比如： union foo { int i; double d; }; union foo f = { .d = 4 };
将会使用第二个元素把4转换成一个double类型来在共同体存放。  
相反，把4转换成union foo类型将会把它作为整数i存入共同体，既然它是一个整数。  
(参考5.24节向共同体类型转换。)你可以把这种命名元素的技术和连续元素的普通C初始化结合起来。  
每个没有指示符的初始化元素应用于数组或结构体中的下一个连续的元素。比如， int a[6] = { [1] = v1, v2, [4] = v4 };