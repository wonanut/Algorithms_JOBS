
# 剑指Offer解题笔记
题目顺序参考：微信小程序-图解剑指offer(共66题)

解答参考网站：牛客网-剑指offer专题

各题的解法参考内容在相应题目中有给出

@Author： Howard Wonanut

@Date： 2019-10

难度标记（最优思路难度）：[H]困难，[M]中等，[E]容易

其他标记：[\*]解法较多

## 需要的基本数据结构与算法基础
- 十大排序算法
- 二叉树的先序遍历、中序遍历、后序遍历和层序遍历的递归非递归实现
- 快慢指针
- 链表的操作

## 1 [M]二维数组的查找
从右上角开始寻找


```python
def find(target, array):
    if array == []:
        return False
    num_row, num_col = len(array), len(array[0])
    row, col = 0, num_col - 1
    while row < num_row and col >= 0:
        if array[row][col] == target:
            return True
        elif array[row][col] > target:
            col -= 1
        else:
            row += 1
    return False
```


```python
test_arr = [
    [1, 4, 7, 11, 15],
    [2, 5, 8, 12, 19],
    [3, 6, 9, 16, 22],
    [10, 13, 14, 17, 24],
    [18, 21, 23, 26, 30]
]
find(31, test_arr)
```




    False



## 2 [M]数组中的重复数字
要求时间复杂度$O(n)$，空间复杂度$O(1)$，因此不能使用桶排序、不能直接使用set、map等。解决思路有点类似桶排序和插入排序的思想，将arr[i]的值存在arr[arr[i]]的位置，然后每次在存储的时候检查该位置是否已经满足:'arr[i] == arr[arr[i]]'，如果已经满足，就说明出现了相同的数，返回该数即可，如果一直没出现这种情况，则不存在重复数字。


```python
def duplicate_number(arr):
    for i in range(len(arr)):
        while arr[i] != i:
            if arr[arr[i]] == arr[i]:
                return True
            else:
                arr[i], arr[arr[i]] = arr[arr[i]], arr[i]
    return False
```


```python
test_arr = [0, 1, 2, 1, 4, 5]
duplicate_number(test_arr)
```




    True



## 3 [M]构建乘积数组
给定一个数组A[0, 1, …, n-1]，请构建一个数组B[0, 1, …, n-1]，其中B中的元素B[i] =A[0]×A[1]×… ×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

### 3.1  [⭐]最基础的方法，复杂度为$O(n^2)$


```python
def multiply(A):
    B = [1] * len(A)
    for i in range(len(A)):
        for j in range(len(A)):
            B[i] = B[i]*A[j] if j != i else B[i]
    return B
```


```python
test_arr = [2, 5, 3, 1, 7]
multiply(test_arr)
```




    [105, 42, 70, 210, 30]



### 3.2 [⭐⭐⭐]优化思路，复杂度为$O(n)$
参考自：https://www.cnblogs.com/yongh/p/9971936.html

由于无法使用除法，正常连乘的话时间复杂度为O(n^2)，效率非常低。

考虑到计算每个B[i]时都会有重复，思考B[i]之间的联系，找出规律，提高效率
![image.png](attachment:image.png)

如上图所示，可以发现：

    B[i]的左半部分(红色部分)和B[i-1]有关（将B[i]的左半部分乘积看成C[i]，有C[i]=C[i-1]*A[i-1]），

    B[i]的右半部分(紫色部分)与B[i+1]有关（将B[i]的右半部分乘积看成D[i]，有D[i]=D[i+1]*A[i+1]），

因此我们先从0到n-1遍历，计算每个B[i]的左半部分；  然后定义一个变量temp代表右半部分的乘积，从n-1到0遍历，令B[i]\*=temp，而每次的temp与上次的temp关系即为temp*=A[i+1]。


```python
def multiply(A):
    B = [1] * len(A)
    for i in range(1, len(A)):
        B[i] = B[i - 1] * A[i - 1]
    temp = 1
    for i in range(len(A) - 2, -1, -1):
        temp *= A[i + 1] 
        B[i] *= temp
    return B
```


```python
test_arr = [2, 5, 3, 1, 7]
multiply(test_arr)
```




    [105, 42, 70, 210, 30]



## 4 [E]替换空格
请实现一个函数，把字符串中的每个空格替换成"%20"。例如输入“We are happy.”，则输出“We%20are%20happy.”。

参考自: 
- https://www.cnblogs.com/yongh/p/9328270.html
- https://www.cnblogs.com/yajun-yin/p/8596338.html

这道题如果使用Python解决有天然的优势，一方面python自带的replace函数即可完成该题目，另一方面python在做字符分割和连接也有对应的函数：split, join。因此在做这道题的时候要把能用到的方法尽可能地都实现一遍。

### 1  [⭐]使用replace方法


```python
def replace_space(str):
    return str.replace(" ", "%20")
```

### 2  [⭐]使用join方法


```python
def replace_space(str):
    word_list = str.split()
    return "%20".join(word_list)
```

### 3  [⭐⭐]自己动手丰衣足食


```python
def replace_space(str):
    # 统计空格个数
    space_counter = 0
    for i in range(len(str)):
        space_counter = space_counter + 1 if str[i] == ' 'else space_counter
    new_str_len = len(str) + 2 * space_counter
    new_string = [None for i in range(new_str_len)]
    idx_origin_str, idx_new_str = len(str) - 1, new_str_len - 1
    while idx_new_str >= 0:
        if str[idx_origin_str] == ' ':
            new_string[idx_new_str - 2: idx_new_str + 1] = ['%', '2', '0']
            idx_new_str -= 3
        else:
            new_string[idx_new_str] = str[idx_origin_str]
            idx_new_str -= 1
        idx_origin_str -= 1
    return "".join(new_string)
```


```python
test_str = "We are happy."
replace_space(test_str)
```




    'We%20are%20happy.'



## 5 [M]正则表达式匹配
| 完成时间： 2019-10-11

请实现一个函数用来匹配包括'.'和'\*'的正则表达式。模式中的字符'.'表示任意一个字符，而'\*'表示它前面的字符（指紧挨着的字符）可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab\*ac\*a"匹配，但是与"aa.a"和"ab\*a"均不匹配

这种题目最好使用递归，如果使用循环写起来会比较复杂，下面是我尝试使用循环写的代码，我觉得也可以嘛

**不过在有的情况这这样写无法通过所有测试样例哦，比如：str="bbaa", pattern=".\*aa"**


```python
def match(str, pattern):
    str_len, pattern_len = len(str), len(pattern)
    str_ptr, pattern_ptr = 0, 0
    while str_ptr < str_len and pattern_ptr < pattern_len:
        if str[str_ptr] == pattern[pattern_ptr]:
            str_ptr += 1
            pattern_ptr += 1
        elif pattern[pattern_ptr] == '.':
            str_ptr += 1
            pattern_ptr += 1
        elif pattern[pattern_ptr + 1] == '*':
            while True:
                if pattern[pattern_ptr] == str[str_ptr]:
                    str_ptr += 1
                else:
                    break
            pattern_ptr += 2
        else:
            break
    return str_ptr == len(str) and pattern_ptr == len(pattern)
```


```python
print(match("aaa", "a.a"))
```

    True
    


```python
print(match("bbaa", ".*aa"))
```

    False
    

弃暗投明，改用**递归**(参考自微信小程序解答)


```python
def match(str, pattern):
    # 如果str和pattern都为空，返回True
    if len(str) == 0 and len(pattern) == 0:
        return True
    # 如果str不为空，pattern为空，返回False
    elif len(str) != 0 and len(pattern) == 0:
        return False
    # 如果str为空，pattern不为空，需要进一步分析
    elif len(str) == 0 and len(pattern) != 0:
        # 如果pattern中的第二个字符为*，仍然符合要求，将pattern后移两位递归调用后继续比较
        if len(pattern) > 1 and pattern[1] == '*':
            return match(str, pattern[2:])
        else:
            return False
    # 如果str和match都不为空
    else:
        # pattern的第二个字符为*的情况
        if len(pattern) > 1 and pattern[1] == '*':
            # str与pattern的一个元素不同，则s不变，pattern后移两位
            if str[0] != pattern[0] and pattern[0] != '.':
                return match(str, pattern[2:])
            else:
                # 如果str[0]与pattern[0]相同，且pattern[1]为*，这时候有三种情况：
                # pattern后移两个，str不变
                # pattern后移两个，str后移一个
                # pattern不变，str后移一个
                return match(str, pattern[2:]) or match(str[1:], pattern[2:]) or match(str[1:], pattern)
        # 如果pattern的第二个字符不是*
        else:
            if str[0] == pattern[0] or pattern[0] == '.':
                return match(str[1:], pattern[1:])
            else:
                return False
```


```python
print(match("aaa", "ab*a"))
```

    False
    


```python
print(match("bbaa", ".*aa"))
```

    True
    

## 6 [M*]表示数值的字符串
| 完成时间： 2019-10-14

请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。

### [⭐⭐]我的思路
从左往右依次遍历，并设置小数点标志位、eE标志位和正负号标志位

（下面的代码参考了微信小程序答案）


```python
def is_numeric(s):
    if len(s) <= 0:
        return False
    
    has_sign, has_point, has_e = False, False, False
    for i in range(len(s)):
        if s[i] == 'e' or s[i] == 'E':
            if has_e:
                return False
            else:
                has_e = True
                if i == len(s) - 1:
                    return False
        elif s[i] == '+' or s[i] == '-':
            if has_sign:
                if s[i-1] != 'e' and s[i-1] != 'E':
                    return False
            else:
                has_sign = True
                if i > 0 and s[i-1] != 'e' and s[i-1] != 'E':
                    return False
        elif s[i] == '.':
            if has_point or has_e:
                return False
            else:
                has_point = True
                if has_e:
                    return False
        elif s[i] < '0' or s[i] > '9':
            return False
    return True
```


```python
test_arr = [
    "+100",
    "5e2",
    "-123",
    "3.1416",
    "-1E-16",
    "12e",
    "1a3.14",
    "1.2.3",
    "+-5",
    "12e+4.3"
]

result_arr = [is_numeric(s) for s in test_arr]
print(result_arr)
```

    [True, True, True, True, True, False, False, False, False, False]
    

### [⭐⭐⭐]另外一种思路：正则表达式

直接使用表达式匹配即可
    
    .                    匹配任意字符（不包括换行符）
    ^                    匹配开始位置，多行模式下匹配每一行的开始
    $                    匹配结束位置，多行模式下匹配每一行的结束
    *                    匹配前一个元字符0到多次
    +                    匹配前一个元字符1到多次
    ?                    匹配前一个元字符0到1次
    {m,n}                匹配前一个元字符m到n次
    \\                   转义字符，跟在其后的字符将失去作为特殊元字符的含义，例如\\.只能匹配.，不能再匹配任意字符
    []                   字符集，一个字符的集合，可匹配其中任意一个字符


```python
import re
def is_numeric(s):
    return re.match(r"^[\+\-]?[0-9]*(\.[0-9]*)?([eE][\+\-]?[0-9]+)?$",s) != None
```


```python
test_arr = [
    "+100",
    "5e2",
    "-123",
    "3.1416",
    "-1E-16",
    "12e",
    "1a3.14",
    "1.2.3",
    "+-5",
    "12e+4.3"
    "12e"
]

result_arr = [is_numeric(s) for s in test_arr]
print(result_arr)
```

    [True, True, True, True, True, False, False, False, False, False]
    

### [⭐]另另外一种思路：使用编译原理中的自动机实现

https://www.nowcoder.com/questionTerminal/6f8c901d091949a5837e24bb82a731f2

### [⭐⭐⭐]最骚的做法？


```python
def is_numeric(s):
    # write code here
    try:
        ss=float(s)
        return True
    except:
        return False
```


```python
test_arr = [
    "+100",
    "5e2",
    "-123",
    "3.1416",
    "-1E-16",
    "12e",
    "1a3.14",
    "1.2.3",
    "+-5",
    "12e+4.3"
]

result_arr = [is_numeric(s) for s in test_arr]
print(result_arr)
```

    [True, True, True, True, True, False, False, False, False, False]
    

## 7 [E]字符流中第一个不重复的字符
完成时间 | 2019-10-14

请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。

### 我的思路
首先考虑边界情况：len(s)==0: return None
之后，从左往右遍历数组s，使用set记录途中遇到过的字符，如果发现位置i的字符s[i]在set中已经存在，调用replace函数将s中的s[i]字符替换为' '，完成之后从左往右找到第一个非空字符即为答案。


```python
def first_apperaing_once(s):
    if len(s) == 0:
        return None
    str_dict = set()
    for i in range(len(s)):
        if s[i] not in str_dict:
            str_dict.add(s[i])
        else:
            s = s.replace(s[i], ' ')
    for i in range(len(s)):
        if s[i] != ' ':
            return s[i]
    return None
```


```python
test_arr = [
    ".ab.a",
    "google",
    "go",
    "\0"
]
result = [first_apperaing_once(s) for s in test_arr]
print(result)
```

    ['b', 'l', 'g', '\x00']
    

### 不过
这道题目要求找出字符流中第一个只出现一次的字符，因此在牛客网上它的代码框架是这样子的：


```python
# -*- coding:utf-8 -*-
class Solution:
    def __init__(self):
        self.s = ''
        self.dict = {}
    # 返回对应char
    def FirstAppearingOnce(self):
        # write code here
        for i in self.s:
            if self.dict[i] == 1:
                return i
        return '#'

    def Insert(self, char):
        # write code here
        self.s = self.s + char
        if char in self.dict:
            self.dict[char] += 1
        else:
            self.dict[char] = 1
        
```

## 8 [E*]从尾到头打印链表
完成时间 | 2019-10-14

输入一个链表，按链表从尾到头的顺序返回一个ArrayList

### 1 使用栈可以说很方便了（C++）
下面是C++代码

```
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        stack<int> istack;
        vector<int> ret;
        while(head) { istack.push(head->val); head = head->next; }
        while(!istack.empty()) { ret.push_back(istack.top()); istack.pop(); }
        return ret;
    }
};
```

### 2 使用头插法


```python
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

def printListFromTailToHead(listNode):
    if not listNode:
        return []
    result = []
    while listNode:
        result.insert(0, listNode.val)
        listNode = listNode.next
    return result
```


```python
node1 = ListNode(1)
node2 = ListNode(2)
node3 = ListNode(3)
node4 = ListNode(4)
node1.next = node2
node2.next = node3
node3.next = node4
print(printListFromTailToHead(node1))
```

    [4, 3, 2, 1]
    

### 3 使用递归


```python
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

def printListFromTailToHead(listNode):
    result = []
    def printListNode(listNode):
        if listNode != None:
            printListNode(listNode.next)
            result.append(listNode.val)
    printListNode(listNode)
    return result

```


```python
node1 = ListNode(1)
node2 = ListNode(2)
node3 = ListNode(3)
node4 = ListNode(4)
node1.next = node2
node2.next = node3
node3.next = node4
print(printListFromTailToHead(node1))
```

    [4, 3, 2, 1]
    

## 9 [M]链表中环的入口结点

完成时间 | 2019-10-14

给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。

### 解题思路1：[⭐]将每个结点的地址保存在dict中
```
作者：叶神同桌
链接：https://www.nowcoder.com/questionTerminal/253d2c59ec3e4bc68da16833f79a38e4?f=discussion
来源：牛客网


class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if(!pHead) return nullptr;
        map<ListNode*,int> flag;
        while(pHead){
            if(++flag[pHead]==2)
            return pHead;
            pHead=pHead->next;
        }
        return nullptr;
        
    }
};
```

### 在牛客网上，大部分的通过代码是这样子的

之前一直以为python中没有地址的概念，现在发现：python中也是有地址的啊！


```python
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
        
def EntryNodeOfLoop(pHead):
    tempList = []
    p = pHead
    while p:
        if p in tempList:
            return p
        else:
            tempList.append(p)
        print(tempList)
        p = p.next
```


```python
node1 = ListNode(1)
node2 = ListNode(2)
node3 = ListNode(1)
node1.next = node2
node2.next = node3
print(EntryNodeOfLoop(node1))
```

    [<__main__.ListNode object at 0x000001828EAEE128>]
    [<__main__.ListNode object at 0x000001828EAEE128>, <__main__.ListNode object at 0x000001828EAE82E8>]
    [<__main__.ListNode object at 0x000001828EAEE128>, <__main__.ListNode object at 0x000001828EAE82E8>, <__main__.ListNode object at 0x000001828EAEE198>]
    None
    

### 解题思路2：[⭐⭐⭐]使用快慢指针

链接：https://www.nowcoder.com/questionTerminal/253d2c59ec3e4bc68da16833f79a38e4?f=discussion
来源：牛客网

![image.png](attachment:image.png)


```python
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def EntryNodeOfLoop(self, pHead):
        # write code here
        if pHead == None or pHead.next == None or pHead.next.next == None:
            return None
        slow, fast = pHead.next, pHead.next.next
        while slow != fast:
            if fast.next == None or fast.next.next == None:
                return None
            slow = slow.next
            fast = fast.next.next
        fast = pHead
        while slow != fast:
            slow = slow.next
            fast = fast.next
        return fast
```


```python
bool(0.0)
```




    False



## 10 [M]删除链表中重复的结点

完成时间 | 2019-10-16

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5



### 设置快慢指针解法
详细的解释说明：https://www.cnblogs.com/darlinFly/p/9328847.html
```
解题思路：

首先初始化一个起始指针preNode指向头结点、工作指针walkNode指向链表的第一个元素，即preNode.next=walkNode。

迭代开始：

while(walkNode!=null){

　　如果当前工作结点的数据域walkNode.val与下一个结点的数据域walkNode.next.val相同（出现重复结点）：

　　　　preNode不移动；（指向重复结点段的前一个结点）

　　　　walkNode移动：walkNode=walkNode.next；（此时preNode.next!=walkNode）

　　否则，

　　　　如果preNode.next==walkNode（说明未出现重复节点）：

　　　　　　preNode移动，walkNode移动：preNode=walkNode；walkNode=walkNode.next；

       　　否则，说明有重复结点，此时preNode指向重复结点段的前一个结点，walkNode指向重复结点段的最后一个重复结点

　　　　　　使preNode直接指向重复结点段的下一个结点：preNode.next=walkNode.next;

　　　　　　walkNode移动：walkNode=walkNode.next；

}
```

自己写了半天没写出来啊


```python
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
        
def deleteDuplication(pHead):
    if pHead == None or pHead.next == None:
        return pHead
    
    first = ListNode(-1)
    first.next = pHead
    
    slow, fast = first, pHead
    while fast:
        while fast.next and fast.val == fast.next.val:
            fast = fast.next
        # 如果fast后面存在和其值相同的点
        if slow.next != fast:
            slow.next = fast.next
            fast = fast.next
        # 如果fast后面的结点的值和其不同
        else:
            slow = fast
            fast = fast.next
        
    return first.next
```


```python
node1 = ListNode(1)
node2 = ListNode(1)
node3 = ListNode(1)
node4 = ListNode(1)
node5 = ListNode(1)
node6 = ListNode(1)
node7 = ListNode(1)
node1.next = node2
node2.next = node3
node3.next = node4
node4.next = node5
node5.next = node6
node6.next = node7

retNode = deleteDuplication(node1)
while retNode:
    print(retNode.val)
    retNode = retNode.next
```

### 使用递归的代码


```python
def deleteDuplication(self, pHead):
        # write code here
        if pHead is None or pHead.next is None:
            return pHead
        head1 = pHead.next
        if head1.val != pHead.val:
            pHead.next = self.deleteDuplication(pHead.next)
        else:
            while pHead.val == head1.val and head1.next is not None:
                head1 = head1.next
            if head1.val != pHead.val:
                pHead = self.deleteDuplication(head1)
            else:
                return None
        return pHead
```

## 11 [E-M]重建二叉树

完成时间 | 2019-10-16

输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。


```python
# -*- coding:utf-8 -*-
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        
# 返回构造的TreeNode根节点
def reConstructBinaryTree(pre, tin):
    # write code here
    if len(pre) == 0:
        return None
    root = TreeNode(pre[0])
    buildTree(root, pre, tin[:tin.index(pre[0])], tin[tin.index(pre[0])+1:])
    return root

def buildTree(root, pre, tin_left, tin_right):
    if len(tin_left) == 0:
        root.left = None
    else:
        for v in pre:
            if v in tin_left:
                break
        root.left = TreeNode(v)
        buildTree(root.left, pre, tin_left[:tin_left.index(v)], tin_left[tin_left.index(v)+1:])

    if len(tin_right) == 0:
        root.right = None
    else:
        for v in pre:
            if v in tin_right:
                break
        root.right = TreeNode(v)
        buildTree(root.right, pre, tin_right[:tin_right.index(v)], tin_right[tin_right.index(v)+1:])
```


```python
root = reConstructBinaryTree([1,2,4,7,3,5,6,8],[4,7,2,1,5,3,8,6])
```

    [4, 7, 2] [5, 3, 8, 6]
    left: 2
    [4, 7] []
    left: 4
    [] [7]
    right: 7
    [] []
    right: 3
    [5] [8, 6]
    left: 5
    [] []
    right: 6
    [8] []
    left: 8
    [] []
    

### 我的写法不够简洁，下面是更好的写法
来自微信小程序


```python
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

def reConstructBinaryTree(self, pre, tin):
    if not pre and not tin:
        return None
    root = TreeNode(pre[0])
    if set(pre) != set(tin):
        return None
    i = tin.index(pre[0])
    root.left = self.reConstructBinaryTree(pre[1:i+1], tin[:i])
    root.right = self.reConstructBinaryTree(pre[i+1:], tin[i+1:])
    return root
```

## 12 [M]二叉树的下一个结点

完成时间 | 2019-10-16

给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
![image.png](attachment:image.png)
链接：https://www.nowcoder.com/questionTerminal/9023a0c988684a53960365b889ceaf5e?f=discussion
来源：牛客网

思路：

（1） 若该节点存在右子树：则下一个节点为右子树最左子节点(B)

（2） 若该节点不存在右子树：这时分两种情况：

    2.1 该节点为父节点的左子节点(I)，则下一个节点为其父节点

    2.2 该节点为父节点的右子节点(J)，则沿着父节点向上遍历，知道找到一个节点的父节点的左子节点为该节点，则该节点的父节点下一个节点


```python
# -*- coding:utf-8 -*-
class TreeLinkNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        self.next = None
        
def GetNext(node):
    # write code here
    if node == None:
        return None
    if node.right != None:
        node = node.right
        while node.left != None:
            node = node.left
        return node
    while node.next != None:
        if node.next.left == node:
            return node.next
        node = node.next
    return None
```


```python
GetNext(root).val
```




    5



## 13 [M]对称的二叉树

完成时间 | 2019-10-16

请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。

思路1：如果先序遍历的顺序分为两种先左后右和先右后左两种顺序遍历，如果两者相等说明二叉树是对称的二叉树。如果采用这种思路，可以做两个前序遍历或者中序遍历后比较两个序列是否相等。不过这样的解法有漏洞：如果整棵树是数值相同的非对称二叉树呢？

思路2：采用递归的思想，进行比较（如下）


```python
# -*- coding:utf-8 -*-
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        
class Solution:
    def isSymmetrical(self, pRoot):
        # write code here
        return selfIsSym(pRoot, pRoot)
    
    def selfIsSym(self, root1, root2):
        if root1 == root2 and root1 == None:
            return True
        if root1 == None or root2 == None:
            return False
        if root1.val != root2.val:
            return False
        return self.selfIsSym(root1.left, root2.right) and self.selfIsSym(root1.right, root2.left)
```

## 14 [M]按之字形打印二叉树

完成时间 | 2019-10-23

请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。

### 最容易想到的办法
这道题和二叉树的层序遍历既有联系又有区别，二叉树的层序遍历使用的是队列，但是这道题不能使用队列而应该使用栈。不过应该使用两个栈分别保存奇数行和偶数行的结点。在保存奇数行的时候应该先保存左节点后保存右节点；在保存偶数行时应该先保存右节点后保存左节点。

下面的代码使用C++实现


```python
## C++代码
#include <iostream>
#include <stack>
#include <queue>
using namespace std; 

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<vector<int> > ans;
        if (pRoot == NULL) {
            return ans;
        }
        int layer = 1;
        stack<TreeNode*> stack1, stack2;
        stack1.push(pRoot);
        while(!stack1.empty() || !stack2.empty()) {
            vector<int> temp_vec;
            if(layer % 2 != 0) {
            	while(!stack1.empty()) {
	                TreeNode* cur_node = stack1.top();
	                stack1.pop();
	                temp_vec.push_back(cur_node->val);
	                if(cur_node->left) stack2.push(cur_node->left);
	                if(cur_node->right) stack2.push(cur_node->right);
	            }
	            if(!temp_vec.empty()) ans.push_back(temp_vec);
            }
            else {
	            while(!stack2.empty()) {
	                TreeNode* cur_node = stack2.top();
	                stack2.pop();
	                temp_vec.push_back(cur_node->val);
	                if(cur_node->right) stack1.push(cur_node->right);
	                if(cur_node->left) stack1.push(cur_node->left);
	            }
	            if(!temp_vec.empty()) ans.push_back(temp_vec);	
            }
            cout << layer << endl;
            layer += 1;
        }
        return ans;
    }
    
    void print_ans(vector<vector<int>> ans){
    	for (auto vec : ans) {
    		for (auto val : vec) {
    			cout << val << ", ";
    		}
    	}
    }
    
};

int main() {
	TreeNode node1 = TreeNode(1);
	TreeNode node2 = TreeNode(2);
	TreeNode node3 = TreeNode(3);
	TreeNode node4 = TreeNode(4);
	TreeNode node5 = TreeNode(5);
	TreeNode node6 = TreeNode(6);
	TreeNode node7 = TreeNode(7);
	
	node1.left = &node2;
	node1.right = &node3;
	node2.left = &node4;
	node2.right = &node5;
	node3.left = &node6;
	node3.right = &node7;
	
	Solution solution;
	vector<vector<int>> ans = solution.Print(&node1);
	solution.print_ans(ans);
	return 0;
}

```


      File "<ipython-input-1-fdbca4c6345e>", line 5
        using namespace std;
                      ^
    SyntaxError: invalid syntax
    


## 15 [E]把二叉树打印成多行
完成时间 | 2019-10-24

从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

### 使用最简单的方法：两个队列分别保存奇数行和偶数行的结点即可
下面的代码使用C++实现


```python

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
        vector<vector<int> > Print(TreeNode* pRoot) {
            vector<vector<int> > ans;
            queue<TreeNode*> q1, q2;
            int layer = 1;
            if (pRoot == NULL) { return ans; }
            q1.push(pRoot);
            while (!q1.empty() || !q2.empty()) {
                vector<int> temp_vec;
                if (layer % 2 != 0) {
                    while(!q1.empty()) {
                        TreeNode *cur_node = q1.front();
                        q1.pop();
                        temp_vec.push_back(cur_node->val);
                        if (cur_node->left) q2.push(cur_node->left);
                        if (cur_node->right) q2.push(cur_node->right);
                    }
                }
                else {
                    while(!q2.empty()) {
                        TreeNode *cur_node = q2.front();
                        q2.pop();
                        temp_vec.push_back(cur_node->val);
                        if (cur_node->left) q1.push(cur_node->left);
                        if (cur_node->right) q1.push(cur_node->right);
                    }
                }
                if (!temp_vec.empty()) ans.push_back(temp_vec);
                layer++;
            }
            return ans;
        }
    
};
```

## 16 [M-H]序列化二叉树

完成时间 | 2019-10-24

请实现两个函数，分别用来序列化和反序列化二叉树

二叉树的序列化是指：把一棵二叉树按照某种遍历方式的结果以某种格式保存为字符串，从而使得内存中建立起来的二叉树可以持久保存。序列化可以基于先序、中序、后序、层序的二叉树遍历方式来进行修改，序列化的结果是一个字符串，序列化时通过 某种符号表示空节点（#），以 ！ 表示一个结点值的结束（value!）。

二叉树的反序列化是指：根据某种遍历顺序得到的序列化字符串结果str，重构二叉树。


### 😔递归这一块还需要加把劲啊！
不看别人的写法我是不会想到怎么用递归的，我想到了用快慢指针。


```python
# -*- coding:utf-8 -*-
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def __init__(self):
        self.pos_ = -1
    
    def Serialize(self, root):
        # write code here
        if root:
            return str(root.val) + ',' + self.Serialize(root.left) + self.Serialize(root.right)
        else:
            return '#,'

    def Deserialize(self, s):
        # write code here
        self.pos_ += 1
        nodeList = s.split(',')
        
        if self.pos_ >= len(nodeList):
            return None
        root = None
        
        if nodeList[self.pos_] != '#':
            root = TreeNode(int(nodeList[self.pos_]))
            root.left = self.Deserialize(s)
            root.right = self.Deserialize(s)
        return root
            
    def preOrder(self, root):
        if root:
            print(root.val, ',')
            self.preOrder(root.left)
            self.preOrder(root.right)
            
    
```


```python
node1, node2, node3 = TreeNode(1), TreeNode(2), TreeNode(3)
node1.left = node2
node2.left = node3
solution = Solution()
seq = solution.Serialize(node1)
root = solution.Deserialize(seq)
solution.preOrder(root)
```

    1 ,
    2 ,
    3 ,
    

## 17 [E-M]二叉搜索树的第k个结点

完成时间 | 2019-10-24

给定一棵二叉搜索树，请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8）    中，按结点数值大小顺序第三小结点的值为4。

### 还是递归思路~

中序遍历的结果即是按照从小到大排好序的了，因此使用中序遍历。递归的思路很容易想到，但是写起来很容易出错！


```python
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        
class Solution:
    def __init__(self):
        self.nodeVisited = 0
        
    def KthNode(self, pRoot, k):
        if pRoot:
            node = self.kthNode(pRoot.left, k)
            if node:
                return node
            self.nodeVisited += 1
            if k == self.nodeVisited:
                return pRoot
            node = self.kthNode(pRoot.right, k)
            if node:
                return node
        return None
```


```python
node1, node2, node3 = TreeNode(2), TreeNode(1), TreeNode(3)
node1.left = node2
node2.left = node3
solution = Solution()
ans = solution.kthNode(node1,2)
print(ans.val)
```

    1
    

## 18 数据流中的中位数
`堆`

完成时间 | 2019-10-24

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。

### 注意
这道题和第7题很像，题干中要求处理的是**流数据**，因此需要按照牛客网上提供的框架进行实现哦

## 19 [E]用两个栈实现队列
完成时间 | 2019-10-24

用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。

### 总结
这道题的思路比较简单，自己模拟一下就知道大致的逻辑了。通过下面的代码，我又了解到python中的list竟然有`pop()`方法！
- pop() 函数用于移除列表中的一个元素（默认最后一个元素），并且返回该元素的值。


```python
# -*- coding:utf-8 -*-
class Solution:
    def __init__(self):
        self.stack1 = []
        self.stack2 = []
        
    def push(self, node):
        # write code here
        self.stack1.append(node)
        
    def pop(self):
        # return xx
        if len(self.stack1) == 0 and len(self.stack2) == 0:
            return
        elif len(self.stack2) == 0:
            while len(self.stack1) > 0:
                self.stack2.append(self.stack1.pop())
                
        return self.stack2.pop()
```

## 20 [E-M]滑动窗口的最大值
`双端队列` `滑动窗口` `数组`

完成时间 | 2019-10-24

给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。

### 下面是比较麻烦的一种做法，但是尽可能地让时间复杂度小


```python
# -*- coding:utf-8 -*-
class Solution:
    def maxInWindows(self, num, size):
        # write code here
        if len(num) == 0 or size <= 0 or size > len(num):
            return []
        if size == 1:
            return num
        left, right = 0, size - 1
        cur_max = num[0]
        ans = []
        for i in range(size):
            cur_max = num[i] if num[i] > cur_max else cur_max
        ans.append(cur_max)
        left, right = left + 1, right + 1
        while right < len(num):
            if num[left - 1] != cur_max:
                cur_max = num[right] if num[right] > cur_max else cur_max
            else:
                cur_max = num[left]
                for i in range(left, right+1):
                    cur_max = num[i] if num[i] > cur_max else cur_max
            ans.append(cur_max)
            left, right = left+1, right+1
        return ans
        
```


```python
solution = Solution()
print(solution.maxInWindows([2,3,4,2,6,2,5,1], 3))
```

    [4, 4, 6, 6, 6, 5]
    

### 下面是很简洁的一种写法，但是我感觉并不好
每次都要执行一次max函数


```python
# -*- coding:utf-8 -*-
class Solution:
    def maxInWindows(self, num, size):
        # write code here
        ans, i = [], 0
        while size > 0 and i + size - 1 < len(num):
            ans.append(max(num[i:i+size]))
            i += 1
        return ans
        
```

## 21 旋转数组的最小数字
`二分查找`

完成时间 | 2019-10-24

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

### 分析
这道题考验的是**优化**，如果从头到尾遍历一遍找到最小值，也可以在$O(n)$的时间复杂度内完成这道题目，但如果真的这样写，怕是Offer就和你没关系了。仔细一想：比$O(n)$的时间复杂度更优秀的还有$O(logn)$和$O(1)$，显然这道题$O(1)$是不可能的了，想都不要想，那就只有二分法了！（二分法的时间复杂度为$O(logn)$）

详细分析：https://www.nowcoder.com/questionTerminal/9f3231a991af4f55b95579b44b7a01ba?f=discussion

### 解题思路
本题可以修改二分查找算法进行求解：
- 当nums[m] <= nums[h]时，说明解在[l,m]之间，此时令h=m
- 否则解在[m+1,h]之间，令l=m+1

😀注意：python中'//'运算符为整数除！


```python
class Solution:
    def minNumberInRotateArray(self, rotateArray):
        if len(rotateArray) == 0:
            return 0
        front, rear = 0, len(rotateArray) - 1
        minVal = rotateArray[0]
        
        if rotateArray[front] < rotateArray[rear]:
            return rotateArray[front]
        else:
            while rear - front > 1:
                print(front, rear)
                mid = (front - rear) // 2
                if rotateArray[mid] >= rotateArray[front]:
                    front = mid
                elif rotateArray[mid] <= rotateArray[rear]:
                    rear = mid
                elif rotateArray[front] == rotateArray[mid] == rotateArray[rear]:
                    for i in range(1, len(rotateArray)):
                        if rotateArray[i] < minVal:
                            minVal = rotateArray[i]
                            rear = i
            minVal = rotateArray[rear]
            return minVal
```


```python
solution = Solution()
solution.minNumberInRotateArray([3,4,5,1,2])
```

    0 4
    




    1



## 22 [E]斐波那契数列
`动态规划`

完成时间 | 2019-10-25

大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）。n<=39


```python
# -*- coding:utf-8 -*-
class Solution:
    def Fibonacci(self, n):
        # write code here
        a, b, index = 0, 1, 0
        while index != n:
            a, b, index = b, a+b, index+1
        return a
```

## 23 [E]跳台阶
`动态规划`

完成时间 | 2019-10-25

一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。


```python
# -*- coding:utf-8 -*-
class Solution:
    def jumpFloor(self, number):
        # write code here
        if number == 0:
            return 0
        a, b, index = 1, 1, 1
        while index != number:
            a, b, index = b, a+b, index+1
        return b
```

## 24 [H]变态跳台阶
`找规律` `分析`

完成时间 | 2019-10-25

一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。

### 🙅‍最笨的解法
虽然能通过，但是真的太笨了这个方法


```python
# -*- coding:utf-8 -*-
class Solution:
    def jumpFloorII(self, number):
        # write code here
        if number == 0:
            return 0
        count_list = [1, 2]
        while len(count_list) < number:
            temp_count = 1
            for count in count_list:
                temp_count += count
            count_list.append(temp_count)
        return count_list[number - 1]
```


```python
solution = Solution()
solution.jumpFloorII(4)
```




    8



### 🐂高级的解法
$f(n)=f(n-1)+f(n-2)+...+f(1)$

$f(n-1)=f(n-2)+f(n-3)+...f(1)$

因此有$f(n)=2f(n-1)$

并且有$f(0)=0,f(1)=1$

因此得到递推式：当$n>0时，f(n)=2^(n-1)$，当$n=0$时，$f(n)=0$


```python
# -*- coding:utf-8 -*-
class Solution:
    def jumpFloorII(self, number):
        # write code here
        return 2**(number - 1)
```

### 🐂🐂同样的思路，但是写的高级点
用左移运算符替代*2


```python
# -*- coding:utf-8 -*-
class Solution:
    def jumpFloorII(self, number):
        # write code here
        return 1<<(number - 1)
```

## 25 矩形覆盖
完成时间 | 2019-10-25

我们可以用2\*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？


```python
# -*- coding:utf-8 -*-
class Solution:
    def rectCover(self, number):
        # write code here
        
```

## 29 链表中倒数第k个结点
`链表` `递归`

完成时间 | 2019-10-25

输入一个链表，输出该链表中倒数第k个结点。

### 我自己想的解法：递归！
不过说到递归，肯定会被吐槽空间复杂度的问题


```python
# -*- coding:utf-8 -*-
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def __init__(self):
        self.k = 0
        
    def FindKthToTail(self, head, k):
        # write code here
        if not head:
            return None
        node = self.FindKthToTail(head.next, k)
        if node:
            return node
        self.k += 1
        if self.k == k:
            return head
        return None
        
```


```python
node1 = ListNode(1)
node2 = ListNode(2)
node3 = ListNode(3)
node1.next = node2
node2.next = node3

s = Solution()
print(s.FindKthToTail(node1, 1).val)
```

    3
    

### 方法2：快慢指针👍
看到牛客网上有好多人使用快慢指针的，这个的确算是解决这道题最好的方法之一了


```python
# -*- coding:utf-8 -*-
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def FindKthToTail(self, head, k):
        # write code here
        if not head:
            return None
        fast, slow = head, head
        for i in range(k-1):
            if fast.next != None:
                fast = fast.next
            else:
                return None
        while fast.next:
            fast = fast.next
            slow = slow.next
        return slow
```


```python
node1 = ListNode(1)
node2 = ListNode(2)
node3 = ListNode(3)
node4 = ListNode(4)
node1.next = node2
node2.next = node3
node3.next = node4

s = Solution()
print(s.FindKthToTail(node1, 1).val)
```

    4
    

## 30 [E-M]反转链表
`指针` `链表`

完成时间 | 2019-10-25

输入一个链表，反转链表后，输出新链表的表头。

### 😊这是我写的版本1
有点冗余，但是很好理解


```python
# -*- coding:utf-8 -*-
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
        
class Solution:
    # 返回ListNode
    def ReverseList(self, pHead):
        if not pHead or not pHead.next:
            return pHead
        pre_node, cur_node, next_node = None, pHead, pHead.next
        cur_node.next = pre_node
        while next_node:
            pre_node, cur_node, next_node = cur_node, next_node, next_node.next
            cur_node.next = pre_node
        cur_node.next = pre_node
        return cur_node
```

### 🐂🐂🐂递归写法
先利用递归走到链表的末端，然后更新每一个node的next值，实现链表的反转


```python
# -*- coding:utf-8 -*-
#class ListNode:
#    def __init__(self, x):
#        self.val = x
#        self.next = None
        
class Solution:
    # 返回ListNode
    def ReverseList(self, pHead):
        if not pHead or not pHead.next:
            return pHead
        node = self.ReverseList(pHead.next)
        pHead.next.next = pHead
        pHead.next = None
        
        return node
```

### 另一种简洁的写法

https://www.nowcoder.com/questionTerminal/75e878df47f24fdc9dc3e400ec6058ca?f=discussion

作者`牛客829441号`使用Java实现的，我用Python改写后会报错，还没调试


```python
# -*- coding:utf-8 -*-
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None
class Solution:
    # 返回ListNode
    def ReverseList(self, pHead):
        # write code here
        pre, next = None
        while pHead:
            next = pHead.next
            pHead.next = pre
            pre = pHead
            pHead = next
        return pre
```

## 31 [E]合并两个排序的链表
`链表`

完成时间 | 2019-10-25

输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。


```python
# -*- coding:utf-8 -*-
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None
class Solution:
    # 返回合并后列表
    def Merge(self, pHead1, pHead2):
        # write code here
        if not pHead1:
            return pHead2
        if not pHead2:
            return pHead1
        
        # 新建一个头节点，作为起点
        head = ListNode(-1)
        ans = head
        while pHead1 and pHead2:
            if pHead1.val < pHead2.val:
                head.next = ListNode(pHead1.val)
                pHead1, head = pHead1.next, head.next
            else:
                head.next = ListNode(pHead2.val)
                pHead2, head = pHead2.next, head.next
        if pHead1:
            head.next = pHead1
        if pHead2:
            head.next = pHead2
        return ans.next
```

## 32 树的子结构
完成时间 | 2019-10-25


