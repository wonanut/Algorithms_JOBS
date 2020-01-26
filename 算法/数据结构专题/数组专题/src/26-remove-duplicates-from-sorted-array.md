# 26 remove-duplicates-from-sorted-array

`简单` `双指针`

https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/



## 题目描述

给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。



## 思路分析

解法同其他双指针题目



## 代码

Python代码

```python
class Solution(object):
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i = 0
        for j in range(len(nums)):
            if nums[i] != nums[j]:
                i += 1
                nums[i] = nums[j]
        return i + 1
```

