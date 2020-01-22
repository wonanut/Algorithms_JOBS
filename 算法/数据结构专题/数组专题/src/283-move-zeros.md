# 283 Move Zeros

`简单` `双指针`

https://leetcode-cn.com/problems/move-zeroes/



## 题目描述

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]



## 思路分析

定义双指针i和j，使用指针j进行遍历，确保在[0, i)之间的元素全为非0。如果遇到nums[j]不等于0，执行swap(nums[i++], nums[j]) ，当j到达数组末尾之后结束。



## 代码

Python代码

```python
class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        i = 0
        for j in range(len(nums)):
            if nums[j] != 0:
                nums[i], nums[j], i = nums[j], nums[i], i + 1
```

上面的代码还可以进行优化，如果数组中没有非零元素，则每次都需要执行nums[i]和nums[i]自身的交换，增加了额外的运行时间，因此可以多加一层判断：

```python
class Solution(object):
    def moveZeroes(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        i = 0
        for j in range(len(nums)):
            if nums[j] != 0:
                if i != j:
                	nums[i], nums[j], i = nums[j], nums[i], i + 1
                else:
                    i += 1
```

