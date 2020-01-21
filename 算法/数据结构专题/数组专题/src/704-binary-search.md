# 704 Binary Search

`简单` `双指针`

https://leetcode-cn.com/problems/binary-search/



## 题目描述

给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。



## 思路分析

经典问题，使用双指针完成即可，但是这个问题需要注意以下两点：

- 边界问题：如果修改low的初始值为-1，或者high的初始值为len(nums)，则代码第4行，第9，11行可能会变
- 加法上溢出问题：使用下面代码第5行写法即可杜绝上溢出问题。



## 代码

Python代码

```python
class Solution(object):
    def search(self, nums, target):
        low, high = 0, len(nums) - 1			# 设置搜索区间为[low, high]
        while low <= high:
            mid = low + (high - low) // 2
            if nums[mid] == target:
                return mid
            elif nums[mid] > target:
                high = mid - 1					# 更新区间为[low, mid - 1]
            else:
                low = mid + 1					# 更新区间为[mid + 1, high]
        return -1
```

