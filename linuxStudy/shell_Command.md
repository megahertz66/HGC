# shell 使用记录  

## 在一行上使用多条shell命令  

1. [ ; ] 
如果被分号(;)所分隔的命令会连续的执行下去，就算是错误的命令也会继续执行后面的命令。  

``` shell 
[root@localhost etc]# lld ; echo “ok” ; lok 
-bash: lld: command not found 
ok 
-bash: lok: command not found 
```

2. [ && ]   

```shell
如果命令被 && 所分隔，那么命令也会一直执行下去，但是中间有错误的命令存在就不会执行后面的命令，没错就直行至完为止。 
[root@localhost etc]# echo “ok” && lld && echo “ok” 
ok 
-bash: lld: command not found
```

3. [ || ]   

如果每个命令被双竖线 || 所分隔，那么一遇到可以执行成功的命令就会停止执行后面的命令，而不管后面的命令是否正确与否。如果执行到错误的命令就是继续执行后一个命令，一直执行到遇到正确的命令为止。 
```shell
[root@localhost etc]# echo “ok” || echo “haha” 
ok 
[root@localhost etc]# lld || echo “ok” || echo “haha” 
-bash: lld: command not found 
ok
```