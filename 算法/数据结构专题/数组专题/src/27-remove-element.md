# 27 Remove Element

`简单` `双指针`

https://leetcode-cn.com/problems/remove-element/



## 题目描述

给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。



## 思路分析

双指针



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

