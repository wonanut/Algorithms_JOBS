# stack

一种线性存储结构，数据元素遵循“先进后出”（FILO）原则，只能在栈顶进行插入和删除操作。

```c++
#include <stack>
stack<int> s;

s.empty() //如果栈为空，返回true，否则返回false
s.size()  //返回栈中元素个数
s.top() //返回栈顶元素但不删除其值
s.pop() //删除栈顶元素但不返回其值
s.push(X)  //在栈顶压入新元素X
```

# queue

线性存储结构，数据元素遵循“先进先出”（FIFO）原则。

```c++
#include <queue>
queue<int> q;

q.empty() //队列为空，返回true
q.size() //返回队列中的元素个数
q.front() //返回第一个元素
q.back() //返回最后一个元素
q.pop() //删除第一个元素但不返回其值
q.push() //在末尾加入一个元素
```

