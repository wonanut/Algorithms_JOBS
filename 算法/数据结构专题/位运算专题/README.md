# 数据结构与算法专题之位运算篇

@ Author: Howard Wonanut

@ Date: 2020-02



## 1 知识清单

位运算有：

- `&`（与）
- `|`（或）
-  `~`（按位取反） 
- `^`（异或）
- `>>`（右移）
- ` <<`（左移）



## 2 常见题型

### 2.1 乘除2

位运算效率更高，可以使用`<<`和`>>`完成这一操作。



### 2.2 检查是否为奇数

直接使用`&`完成：

```python
num & 0x1 == 1
```



### 2.3 n&(n-1)

很神奇很有用的方法，会将整数n从右边数的第1个1变成0.

`典型题目`

- [191. 位1的个数](https://leetcode-cn.com/problems/number-of-1-bits/)

- [231. 2的幂](https://leetcode-cn.com/problems/power-of-two/)



### 2.4 使用异或完成数字交换

很实用也很酷的数字交换方法：

```python
# python中可以一行完成，不过其他语言不一定可以
a, b = b, a

# 异或实现交换
a = a ^ b
b = a ^ b
a = a ^ b
```



### 2.5 整数转化为二进制字符串（python）

```python
bin(10)
# '0b1010'
```



## 3 经典题目

- [面试题65. 不用加减乘除做加法](https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/)

- [191. 位1的个数](https://leetcode-cn.com/problems/number-of-1-bits/)