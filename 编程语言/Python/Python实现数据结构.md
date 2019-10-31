@Author: Howard Wonanut

@Date: 2019-10



## Python实现栈

实现接口：

- init() 用于初始化stack，数据类型为list
- size() 用于获得stack的大小
- push() 用于往栈中添加元素，添加的元素类型可以是int或者list
- top(）获取栈顶元素
- pop() 弹出并返回栈顶元素
- print_stack() 打印栈
  


```python
class Stack(object):
    def __init__(self):
        self.len = 0
        self._stack = []
        
    def init(self, init_list):
        self._stack = init_list
        self.len = len(init_list)
    
    def size(self):
        return self.len
    
    def push(self, val):
        if isinstance(val, int):
            self._stack.append(val)
            self.len += 1
        elif isinstance(val, list):
            self._stack.extend(val)
            self.len += len(val)
        else:
            assert isinstance(val, int) or isinstance(val, list)
    
    def top(self):
        return None if self.len == 0 else self._stack[self.len - 1]
    
    def pop(self):
        if self.len == 0:
            assert self.len > 0
        else:
            self.len -= 1
            return self._stack.pop()
        return None
    
    def print_stack(self):
        print('Bottom |', *self._stack, '| Top >')
```

测试


```python
stack = Stack()
stack.push(1)
stack.size()
stack.init([1,2,3,4,5])
stack.print_stack()
stack.pop()
stack.print_stack()
stack.push(11)
stack.print_stack()
stack.size()
stack.top()
```

    Bottom | 1 2 3 4 5 | Top >
    Bottom | 1 2 3 4 | Top >
    Bottom | 1 2 3 4 11 | Top >
    11



## Python实现单端队列

实现接口：

- init() 用于初始化队列，数据类型为list
- size() 用于获得队列的大小
- push() 用于往队列尾部添加元素，添加的元素类型可以是int或者list
- rear(）获取队列尾部元素
- front() 获取队列头部元素
- pop() 弹出并返回队列头部元素
- print_queue() 打印队列
  


```python
class Queue(object):
    def __init__(self):
        self.len = 0
        self._queue = []
        
    def init(self, init_list):
        self._queue = init_list
        self.len = len(init_list)
    
    def size(self):
        return self.len
    
    def push(self, val):
        if isinstance(val, int):
            self._queue.append(val)
            self.len += 1
        elif isinstance(val, list):
            self._queue.extend(val)
            self.len += len(val)
        else:
            assert isinstance(val, int) or isinstance(val, list)
    
    def rear(self):
        return None if self.len == 0 else self._queue[self.len - 1]
    
    def front(self):
        return None if self.len == 0 else self._queue[0]
    
    def pop(self):
        assert self.len > 0
        self.len -= 1
        return self._queue.pop(0)
    
    def print_queue(self):
        print('Front |', *self._queue, '| Rear >')
```

测试


```python
queue = Queue()
queue.init([1,2,3,4,5])
queue.print_queue()
queue.pop()
queue.print_queue()
queue.push(11)
queue.print_queue()
queue.front()
queue.rear()
queue.size()
```

    Front | 1 2 3 4 5 | Rear >
    Front | 2 3 4 5 | Rear >
    Front | 2 3 4 5 11 | Rear >
    5


