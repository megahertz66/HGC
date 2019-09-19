# 刷57道题的时候的经验记录  

## CSS记录  

### <label> 标签的 for 属性  

for 属性规定 label 与哪个表单元素绑定。  
checkbox默认的样式非常丑 ，无法直接修改checkbox和radio的样式，这里我们借助label标签来对它进行样式美化。  
就是将 input hidden 或者将其dispaly设置为none，然后借助label标签美化这个radios。  

### css中div中内容居中的5种方法  
[原文.风雨后见彩虹(侵删!)](https://www.cnblogs.com/moqiutao/p/4807792.html)
    一、行高（line-height）法
    二、内边距（padding）法
    三、模拟表格法
    四、CSS3的transform来实现
    五：css3的box方法实现水平垂直居中
    六：flex布局（2018/04/17补充）
### 行高  
如果要垂直居中的只有一行或几个文字，那它的制作最为简单，只要让文字的行高和容器的高度相同即可，比如：
`p { height:30px; line-height:30px; width:100px; overflow:hidden; }`
这段代码可以达到让文字在段落中垂直居中的效果。
### 内边距  
另一种方法和行高法很相似，它同样适合一行或几行文字垂直居中，原理就是利用padding将内容垂直居中，比如：
`p { padding:20px 0; }`
这段代码的效果和line-height法差不多。  
### 模拟表格法  
将容器设置为display:table，然后将子元素也就是要垂直居中显示的元素设置为display:table-cell，然后加上vertical-align:middle来实现。

html结构如下：
```html
<div id="wrapper">
    <div id="cell">
        <p>测试垂直居中效果测试垂直居中效果</p>
        <p>测试垂直居中效果测试垂直居中效果</p>
    </div>
</div>
```
css代码：
```
#wrapper {display:table;width:300px;height:300px;background:#000;margin:0 auto;color:red;}
#cell{display:table-cell; vertical-align:middle;}
```
### css3的box方法实现水平垂直居中  
```html
<div class="center">
  <div class="text">
    <p>我是多行文字</p>
    <p>我是多行文字</p>
    <p>我是多行文字</p>
  </div>
</div>
```
css代码:  
```css
.center {
  width: 300px;
  height: 200px;
  padding: 10px;
  border: 1px solid #ccc;
  background:#000;
  color:#fff;
  margin: 20px auto;

  display: -webkit-box;
  -webkit-box-orient: horizontal;
  -webkit-box-pack: center;
  -webkit-box-align: center;
  
  display: -moz-box;
  -moz-box-orient: horizontal;
  -moz-box-pack: center;
  -moz-box-align: center;
  
  display: -o-box;
  -o-box-orient: horizontal;
  -o-box-pack: center;
  -o-box-align: center;
  
  display: -ms-box;
  -ms-box-orient: horizontal;
  -ms-box-pack: center;
  -ms-box-align: center;
  
  display: box;
  box-orient: horizontal;
  box-pack: center;
  box-align: center;
}
```

### flex布局  
html代码：
```html
<div class="flex">
    <div>
       <p>我是多行文字我是多行文字我是多行文字我是多行文字</p>
      <p>我是多行文字我是多行文字我是多行文字我是多行文字</p>
    </div>
</div>
```
css代码:  
```css
.flex{
    /*flex 布局*/
    display: flex;
    /*实现垂直居中*/
    align-items: center;
    /*实现水平居中*/
    justify-content: center;
    
    text-align: justify;
    width:200px;
    height:200px;
    background: #000;
    margin:0 auto;
    color:#fff;
}
```  

## JS记录

### input相关  

document.getElementById("ElementId").setAttribute("placeholder","你想修改的内容");

**还有取消与添加**
text_1.setAttribute("hidden",true);
text_2.removeAttribute("hidden");

### html元素更改内容  
p			使用innerHTML    
input		 使用value  


### 四舍五入等  

- 类型不变  				`result = Math.round(num * 100) / 100;  `  
- 不四舍五入 ，向下取整		`num = Math.floor(num * 100) / 100; `  
- 保留两位小数，将数值类型的数据改变成了字符串类型  `num = num.toFixed(2);`  
- 字符串匹配    `num = Number(num.toString().match(/^\d+(?:\.\d{0,2})?/));`   
```javascript 
// 1.只保留整数部分（丢弃小数部分）
parseInt(5.1234);// 5
// 2.向下取整（<= 该数值的最大整数）和parseInt()一样
Math.floor(5.1234);// 5    
// 3.向上取整（有小数，整数就+1）
Math.ceil(5.1234);

// 4.四舍五入（小数部分）
Math.round(5.1234);// 5
Math.round(5.6789);// 6
// 5.绝对值
Math.abs(-1);// 1
// 6.返回两者中的较大值
Math.max(1,2);// 2
// 7.返回两者中的较小值
Math.min(1,2);// 1
// 随机数（0-1）
Math.random();
```

## c语言获取系统时间  
使用 #include<time.h>




## Python记录  

### 取整  

向下取整 int(x)  
四舍五入用 round() 函数  
```python  
import math

f = 11.2
print math.ceil(f) #向上取整
print math.floor(f) #向下取整
print round(f) #四舍五入
```


## c 语言记录    

### 一、浮点数

double 类型的数据使用 int 强转换后只会单纯的抛弃小数点后的数字。  

**double 可以和 int 的数据比较大小**  

```
1.000 == 1	->true
2.001 >  2  ->true
```


