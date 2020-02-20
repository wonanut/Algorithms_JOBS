# 209 minimum-size-subarray-sum

`中等` `滑动窗口`

https://leetcode-cn.com/problems/minimum-size-subarray-sum/



## 题目描述

给定一个含有 **n** 个正整数的数组和一个正整数 **s ，**找出该数组中满足其和 **≥ s** 的长度最小的连续子数组**。**如果不存在符合条件的连续子数组，返回 0。



## 思路分析

滑动窗口



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

