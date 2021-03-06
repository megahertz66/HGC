# git 备忘

## 便于理解的图  


![git流程](./picture-for-note/gitok.png)  


## 几个关于GIT的问题  

1.   
	问：如果我和别人都克隆同一个项目别人提交我也提交，这会是怎么样的一个场景？  
	答：只有当你有所克隆服务器的写入权限，并且之前没有人推送过时，push命令才能生效。 当你和其他人在同一时
		间克隆，他们先推送到上游然后你再推送到上游，你的推送就会毫无疑问地被拒绝。 你必须先将他们的工作拉
		取下来并将其合并进你的工作后才能推送。  

## 别名  

这个功能可以有效的让你省打几个字来实现命令，但是估计用久了原本的命令就忘记了吧，汗！  

```shell
$ git config --global alias.co checkout
$ git config --global alias.br branch
$ git config --global alias.ci commit
$ git config --global alias.st status
```

## 强制覆盖本地与提交

```shell
git push -f orgin master	#强制提交
 
git fetch --all				#强制覆盖本地
git reset --hard origin/master
git merge <remote/master>
```

## 远程仓库删除文件或者文件夹  
  
**要从 Git 中移除某个文件，就必须要从已跟踪文件清单中移除（确切地说，是从暂存区域移除），然后提交。**
**如果删除之前修改过并且已经放到暂存区域的话，则必须要用强制删除选项 -f（译注：即 force 的首字母）。**  

### 删除远程仓库并且从暂存区删除  
  
加入 --cached命令
` $ git rm --cached XXX `

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

## 本地分支同步远端分支

```shell
git branch -a 	#可以查看本地和远端的全部分支

git push <远端主机名称> <本地分支>:<远端分支>

#上传本地master分支到远端，如上传的是本地分支，远端分支则被自动创建
git push origin master	
#如果省略本地分支，则表示上传一个空的远端分支。即是删除远端分支
git push : refs/for/master
#如果远端分支与本地分支存在追踪关系，本地分支与远端分支都可以省略
git push origin
#如果只有一个远程分支
git push
```

## 远端分支同步本地分支

```shell
git fetch <远程主机名>	#就是把全部的远程主机更新都拉回本地
git fetch <远程主机名>空格<分支名>	#拉取指定远端分支
```  

## 撤销操作  
  
如果提交发现漏了几个文件，可以使用如下命令，使得最终只有一个提交  
   
```shell
$ git commit -m 'initial commit'
$ git add forgotten_file
$ git commit --amend
```  

## 取消暂存文件  


如果提交的时候发现提交多了（到暂存区），可以使用：  

```shell
$ git reset HEAD XXXXX
``` 

## 撤销修改  

如果你对一个文件改来改去懵了，还不如不改，或者干脆重改（回复到上次提交的状态）：  

`$ git checkout[空格]--[空格]<file>`


## 版本回滚

**采用git log & git reflog**  

```shell
git log --pretty=oneline	#在一行显示
git reflog 	#支持之前所有的commit和reset操作

#回退
git reset --soft <回退的hash值>		#只是切换回去
git reset --hard <回退的hash值>		#直接改变本地代码

#使用图形方式更加直观
git log --grap --pretty=oneline --abbrev-commit
```

## 那些文件名前面的 D M 是什么意思  

**就是之前分支没有提交带过来的状态**  

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

## 文件改名  

```shell
$ git mv file_from file_to
#此命令视同如下三条命令：
$ mv README.md README
$ git rm README.md
$ git add README
```
















