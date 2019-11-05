# Shell必备知识

整理者： Howard Wonanut

时    间： 2019-11

参    考：https://mp.weixin.qq.com/s/TW38w2wowsi2hszMwF3xjg

​				https://mp.weixin.qq.com/s/X6F4Lju9OeIDJMjABsFFWw



## 1 入参和默认变量

对于shell脚本而言，有些内容是专门用于处理参数的，如：

```bash
bash test.sh input.txt output.txt
```

上面的bash指令中`input.txt`和`output.txt`是输入的两个参数，在程序中使用`$1`,`$2`来取得它们的值，如果有多个参数，以此类推。另外`$0`代表了执行的脚本名，上面的命中`$0`的值为`bash test.sh`。

除此之外还有一些默认变量：

```bash
$#	# 代表脚本后面跟的参数个数
$@	# 代表了所有参数，并且可以被遍历
$*	# 代表了所有参数，且作为整体
$$	# 代表了当前脚本的进程ID
$?	# 代表了上一条命令的退出状态
```



## 2 变量

给变量赋值的时候**等号两边不能有空格**！等号右边的字符串如果含有空格必须用引号引起来(单引号双引号均可)。

```bash
val_a="hello world"
```

使用变量的时候，在变量前面加$

```bash
echo "value of val_a is $val_a"
# or
echo "value of val_a is ${val_a}"
```

使用unset取消变量

```bash
unset val_a
```



## 3 执行命令

在shell中执行命令通常只需要像在终端一样执行命令即可，不过，如果想要命令结果打印出来的时候，这样的方式就行不通了。因此，shell的命令方式常有：

```bash
a=`ls`
```

或者使用$，后面括号内是执行的命令：

```bash
echo "current path is $(pwd)"
```

另外，前面两种方式对于计算表达式也是行不通的，而要采取下面的方式：

```bash
echo "1+1=$((1+1))"
```

即$后面用**两重括号将要计算的表达式包裹起来**。

那如果要执行的命令存储在变量中呢？前面的方法都不可行了，当然括号内的内容被当成命令执行还是成立的。要使用下面的方式，例如：

```bash
a="ls"
echo "$($a)"
```

但是如果字符串时多条命令的时候，上面的方式又不可行了，而要采用下面的方式：

```bash
a="ls;pwd"
echo "$(eval $a)"
```

这是使用了eval，将a的内容都作为命令来执行。



## 4 条件分支

一般说明，如果命令执行成功，则其返回值为0，否则为非0，因此，可以通过下面的方式判断上条命令的执行结果：

```bash
if [ $? -eq 0 ]
then
	echo "success"
elif [ $? -eq 1 ]
then
	echo "failed"
else
	echo "others"
fi
```

case语句使用方法：

```bash
name="aa"
case $name in
	"aa")
	echo "name is $name"
	;;
	"")
	echo "name is empty"
	;;
	"bb")
	echo "name is $name"
	;;
	*)
	echo "other name"
	;;
esac
```

**注意**：

- []前面要有空格，它里面是逻辑表达式
- if elif后面要跟then，然后才是要执行的语句
- 如果想打印上一条命令的执行结果，最好的做法是将 $?赋给一个变量，因为一旦执行了一条命令，$?的值就可能会变。
- case每个分支最后以两个分号结尾，最后是case反过来写，即esac



如果有多个条件，有以下两种写法：

```bash
if [10 -gt 5 -o 10 -gt 4 ]; then
	echo "10>5 or 10>4"
fi
# or
if [10 -gt 5 || 10 -gt 4 ]; then
	echo "10>5 or 10>4"
fi
```

**注意**：

- -o or 或者，同||
- -a and 与，同&&
- ! 非



**整数判断**：

- -eq 两数是否相等
- -ne 两数是否不等
- -gt 前者是否大于后者（greater then）
- -lt 前面是否小于后者（less than）
- -ge 前者是否大于等于后者（greater then or equal）
- -le 前者是否小于等于后者（less than or equal）



**字符串判断str1 exp str2**:

- -z "$str1" str1是否为空字符串
- -n "$str1" str1是否不是空字符串
- "\$str1" == "\$str2" str1是否与str2相等
- "\$str1" != "\$str2" str1是否与str2不等
- "$str1" =~ "str2" str1是否包含str2

特别注意，**字符串变量最好用引号引起来**，因为一旦字符串中有空格，这个表达式就错了!



**文件目录判断**：filename

- -f $filename 是否为文件
- -e $filename 是否存在
- -d $filename 是否为目录
- -s $filename 文件存在且不为空
- ! -s $filename 文件是否为空



## 5 循环

形式1

```bash
# 遍历输出脚本的参数
for i in $@; do
	echo $i
done
```

形式2

```bash
# 循环打印0-9
for ((i = 0 ; i < 10 ; i++)); do
	echo $i
done
```

形式3

```bash
# 循环打印1-5
for i in {1..5}; do
	echo $i
done
```

形式4

```bash
ans=yes
until [ $ans != 'yes']
do
	read -p "please input yes to exit loop:" ans
done
```

形式5

```bash
# 每隔3打印一次,打印结果为：5，8，11，14
for i in {5..15..3}; do
	echo $i
done
```



## 6 函数

定义函数方式如下：

```bash
myfunc()
{
	echo "hello, $1"
}
```

或者

```bash
function myfunc()
{
	echo "hello, $1"
}
```

函数调用

```bash
para1="xiaoming"
myfunc $para1
```



## 7 返回值

通常函数的return返回值只支持0-255，因此想要获得返回值，可以通过下面的方式。

```bash
function myfunc() {
	local myresult='some value'
	echo $myresult
}
val=$(myfunc)	# val的值为some value
```

通过return的方式**适用于判断函数的执行是否成功**：

```bash
function my func() {
	# do something
	return 0
}
if myfunc; then
	ehco "success"
else
	echo "failed"
fi
```



## 8 日志保存

脚本执行后免不了要记录日志，最常用的方法就是重定向。以下面的脚本为例：

```bash
#!/bin/bash
#test.sh
lll  #这个命令是没有的，因此会报错
date
```

方式一，将标准输出保存到文件中，打印标准错误：

```bash
./test.sh > log.dat
```

这种情况下，如果命令执行出错，错误将会打印到控制台。所以如果你在程序中调用，这样将不会讲错误信息保存在日志中。

方式二，标准输出和标准错误都保存到日志文件中：

```
./test.sh > log.dat 2>&1
```

2>&1的含义可以参考《[如何理解linuxshell中的2>&1](http://mp.weixin.qq.com/s?__biz=MzI2OTA3NTk3Ng==&mid=2649284005&idx=1&sn=dc9e9db84ec363d5a0ed7f84bc6ec866&chksm=f2f9aec2c58e27d42eee09ae646e493530d8d0deda822df2ffa2e5153d210b709a6d69272957&scene=21#wechat_redirect)》

方式三，保存日志文件的同时，也输出到控制台：

```bash
./test.sh |tee log.dat
```



## 9 脚本执行

最常见的执行方式前面已经看到了：

```bash
./test.sh
```

其它执行方式：

```bash
sh test.sh  #在子进程中执行
sh -x test.sh #会在终端打印执行到命令，适合调试
source test.sh #test.sh在父进程中执行
. test.sh   #不需要赋予执行权限，临时执行
```

