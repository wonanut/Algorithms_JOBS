# Python标准库模块之heapq

原文链接：https://www.jianshu.com/p/801318c77ab5

------

该模块提供了堆排序算法的实现。堆是二叉树，最大堆中父节点大于或等于两个子节点，最小堆父节点小于或等于两个子节点。

### *说明

heapq模块中实现的是小顶堆，**没有大顶堆！没有大顶堆！没有大顶堆！也不能传参数修改为大顶堆！**

因此如果想使用大顶堆，可以取所有元素的复数！



### 创建堆

heapq有两种方式创建堆， 一种是使用一个空列表，然后使用`heapq.heappush()`函数把值加入堆中，另外一种就是使用`heap.heapify(list)`转换列表成为堆结构

```python
import heapq

# 第一种
"""
函数定义：
heapq.heappush(heap, item)
    - Push the value item onto the heap, maintaining the heap invariant.
heapq.heappop(heap)
    - Pop and return the smallest item from the heap, maintaining the heap invariant.
    If the heap is empty, IndexError is raised. To access the smallest item without popping it, use heap[0].
"""
nums = [2, 3, 5, 1, 54, 23, 132]
heap = []
for num in nums:
    heapq.heappush(heap, num)  # 加入堆

print(heap[0])  # 如果只是想获取最小值而不是弹出，使用heap[0]
print([heapq.heappop(heap) for _ in range(len(nums))])  # 堆排序结果
# out: [1, 2, 3, 5, 23, 54, 132]


# 第二种
nums = [2, 3, 5, 1, 54, 23, 132]
heapq.heapify(nums)
print([heapq.heappop(heap) for _ in range(len(nums))])  # 堆排序结果
# out: [1, 2, 3, 5, 23, 54, 132]
```

heapq 模块还有一个`heapq.merge(*iterables)` 方法，用于合并多个排序后的序列成一个排序后的序列， 返回排序后的值的迭代器。

类似于`sorted(itertools.chain(*iterables))`，但返回的是可迭代的。

```python
"""
函数定义：
heapq.merge(*iterables)
    - Merge multiple sorted inputs into a single sorted output (for example, merge timestamped entries from multiple log files). Returns an iterator over the sorted values.
    - Similar to sorted(itertools.chain(*iterables)) but returns an iterable, does not pull the data into memory all at once, and assumes that each of the input streams is already sorted (smallest to largest).
"""
import heapq

num1 = [32, 3, 5, 34, 54, 23, 132]
num2 = [23, 2, 12, 656, 324, 23, 54]
num1 = sorted(num1)
num2 = sorted(num2)

res = heapq.merge(num1, num2)
print(list(res))
```



### 访问堆内容

堆创建好后，可以通过`heapq.heappop() `函数弹出堆中最小值。

```python
import heapq
nums = [2, 43, 45, 23, 12]
heapq.heapify(nums)

print(heapq.heappop(nums))
# out: 2

# 如果需要所有堆排序后的元素
result = [heapq.heappop(nums) for _ in range(len(nums))]
print(result)
# out: [12, 23, 43, 45]
```

如果需要删除堆中最小元素并加入一个元素，可以使用`heapq.heaprepalce()` 函数

```go
import heapq

nums = [1, 2, 4, 5, 3]
heapq.heapify(nums)

heapq.heapreplace(nums, 23)

print([heapq.heappop(nums) for _ in range(len(nums))])
# out: [2, 3, 4, 5, 23]
```



### 获取堆最大或最小值

如果需要获取堆中最大或最小的范围值，则可以使用`heapq.nlargest()` 或`heapq.nsmallest()` 函数

```python
"""
函数定义：
heapq.nlargest(n, iterable[, key])¶
    - Return a list with the n largest elements from the dataset defined by iterable. 
    - key if provided, specifies a function of one argument that is used to extract a comparison key from each element in the iterable: key=str.lower
    - Equivalent to: sorted(iterable, key=key, reverse=True)[:n]
"""
import heapq

nums = [1, 3, 4, 5, 2]
print(heapq.nlargest(3, nums))
print(heapq.nsmallest(3, nums))

"""
输出：
[5, 4, 3]
[1, 2, 3]
"""
```

这两个函数还接受一个key参数，用于dict或其他数据结构类型使用

```python
import heapq
from pprint import pprint
portfolio = [
    {'name': 'IBM', 'shares': 100, 'price': 91.1},
    {'name': 'AAPL', 'shares': 50, 'price': 543.22},
    {'name': 'FB', 'shares': 200, 'price': 21.09},
    {'name': 'HPQ', 'shares': 35, 'price': 31.75},
    {'name': 'YHOO', 'shares': 45, 'price': 16.35},
    {'name': 'ACME', 'shares': 75, 'price': 115.65}
]
cheap = heapq.nsmallest(3, portfolio, key=lambda s: s['price'])
expensive = heapq.nlargest(3, portfolio, key=lambda s: s['price'])
pprint(cheap)
pprint(expensive)

"""
输出：
[{'name': 'YHOO', 'price': 16.35, 'shares': 45},
 {'name': 'FB', 'price': 21.09, 'shares': 200},
 {'name': 'HPQ', 'price': 31.75, 'shares': 35}]
[{'name': 'AAPL', 'price': 543.22, 'shares': 50},
 {'name': 'ACME', 'price': 115.65, 'shares': 75},
 {'name': 'IBM', 'price': 91.1, 'shares': 100}]
"""
```



### heapq应用

实现heap堆排序算法

```python
>>> def heapsort(iterable):
...     h = []
...     for value in iterable:
...         heappush(h, value)
...     return [heappop(h) for i in range(len(h))]
...
>>> heapsort([1, 3, 5, 7, 9, 2, 4, 6, 8, 0])
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
```

该算法和`sorted(iterable)` 类似，但是它是不稳定的。

堆的值可以是元组类型，可以实现对带权值的元素进行排序。

```ruby
>>> h = []
>>> heappush(h, (5, 'write code'))
>>> heappush(h, (7, 'release product'))
>>> heappush(h, (1, 'write spec'))
>>> heappush(h, (3, 'create tests'))
>>> heappop(h)
(1, 'write spec')
```