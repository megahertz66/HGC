# grep

> grep (global search regular expression(RE) and print out the line,全面搜索正则表达式并把行打印出来)是一种强大的文本搜索工具，它能使用正则表达式搜索文本，并把匹配的行打印出来。  

## 常用参数
- -w 整字匹配
- -E 使用正则表达式
- -i 忽略大小写
- -R 递归查找
- -n 显示找到内容所在的行号
- --include 指定某些文件
- --exclude 排除某些文件
- -A n 打印搜索结果之后的n行
- -B n 打印搜索结果之前的n行  

## 举例  

- 在当前目录下递归搜索具有main的文件，并显示行号
	`grep "main" -rn . --include *.c`  
- 在当前目录下后缀为.h .c的文件递归搜索具有hahaha的文件并显示行号
	`grep "hahaha" -rn . --include *.{c,h}`  
- dsa 


