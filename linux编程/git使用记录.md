# git 备忘

## 便于理解的图  


![git流程](./picture-for-note/gitok.png)  


## 强制覆盖本地与提交

```shell
git push -f orgin master	#强制提交
 
git fetch -all				#强制覆盖本地
git -reset --hard origin/master
```

## 远程仓库删除文件或者文件夹  

```shell
git pull origin master		#拉取远程仓库项目
git rm -r --cached target	#删除target文件夹
git commit -m 删除了target文件夹
git push -u orgin master	#提交文件
```

## 获得帮助

```shell
git --help		#简短帮助
git help -a		#详细git命令
git help <command>	#获得command的详细内容，会从网页打开
```

##  同步远端仓库

```shell
git remote -v				#查看与其他仓库之间的连接
git fetch <remote>			#remote 就是上一个命令中看到的远程仓库url的名字
git merge <remote/master>	#合并到本地文件
```

## 解决冲突 （待实践）

**假设场景** ： A和B都从远端仓库拉取了代码进行修改。提交的时候A先提交了，这时B再提交就会失败，原因是服务器上的代码和他拉下来的时候已经不一样了。  

**解决** ：  
```shell
git pull		#拉取最新的代码,这时候就会显示那个文件是冲突的(conflict)
git status 		#可能也会显示冲突的代码。
#去那几个文件中修改代码，把git自动填的体现冲突的符号一并删除
git add <file>
git commit -m 解决冲突
git push
```

## 提交代码到自己的远端仓库

```shell
git add --all	#把所有修改的都添加到缓存区
git commit -m 	#我要提交了
git push		#搞定！
```

## 分支太强了，放弃主干怎么办

master只是一个名字，废了，再建。（破而后立）  

```shell
git branch -D master		#破
git checkout -b master		#立
```

## 合并分支

```shell
git checkout master		#切换到master分支
git meger --no--ff <要被merge的分支>
```

## 那些文件名前面的 D M 是什么意思  

- A ：增加的文件
- C：文件的一个拷贝
- D：删除一个文件
- M：文件内容或者mode被修改
- R：文件名被修改
- T：文件类型被修改
- U：文件没有合并（完成合并才能提交）
- X：未知状态

## fetch & pull


```shell
git fetch <远程主机名>空格<分支名>	#分支名可省略

#更新后返回FETCH_HEAD,本地可通过log查看
git log -p FETCH_HEAD

#如需同步到本地
git merge <远程主机名>/<本地分支>


#git pull 相当于 fetch 和 merge 的合体
git pull <远程主机名>空格<远程分支名>:<本地分支名>
```

。
















