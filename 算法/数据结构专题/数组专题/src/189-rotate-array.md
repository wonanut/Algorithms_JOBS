# 189 rotate-array

`简单` `数组反转`

https://leetcode-cn.com/problems/rotate-array/



## 题目描述

给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。

```
示例:
输入: [1,2,3,4,5,6,7] 和 k = 3
输出: [5,6,7,1,2,3,4]

解释:
向右旋转 1 步: [7,1,2,3,4,5,6]
向右旋转 2 步: [6,7,1,2,3,4,5]
向右旋转 3 步: [5,6,7,1,2,3,4]
```



## 思路分析

原始数组						: 1 2 3 4 5 6 7
反转所有数字后			: 7 6 5 4 3 2 1
反转前 k 个数字后         : 5 6 7 4 3 2 1
反转后 n-k 个数字后     : 5 6 7 1 2 3 4 --> 结果



## 代码

Python代码

```python
class Solution(object):
    def rotate(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        def reverse(arr, start, end):
            while start < end:
                arr[start], arr[end] = arr[end], arr[start]
                start += 1
                end -= 1

        k %= len(nums)
        reverse(nums, 0, len(nums) - 1)
        reverse(nums, 0, k - 1)
        reverse(nums, k, len(nums) - 1)
```