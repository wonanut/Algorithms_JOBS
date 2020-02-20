# 75 Sort Colors

`中等` `三路快排`

https://leetcode-cn.com/problems/sort-colors/



## 题目描述

给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

*注意: 不能使用代码库中的排序函数来解决这道题。*



## 思路分析

**三路快排的典型题目**，定义两个指针left和right，确保[0,left)之间的元素值为0，(right, len(nums) - 1]之间的元素为2。再定义一个移动指针i从0一直遍历到right的位置即可，nums[i]为不同值对应的不同操作如下：

- nums[i] == 0: 需要`swap(nums[i], nums[left])`，之后left和i均右移一位！
- nums[i] == 1: 直接不需要操作，直接将i右移即可；
- nums[i] == 2: 需要`swap(nums[i], nums[right])`，之后将right左移一位。



## 代码

Python代码

```python
class Solution(object):
    def sortColors(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        1, 1, 2, 0, 1
        """
        left, right = 0, len(nums) - 1
        i = 0
        while i <= right:
            if nums[i] == 0:
                nums[left], nums[i] = nums[i], nums[left]
                left += 1
                i += 1
            elif nums[i] == 1:
                i += 1
            elif nums[i] == 2:
                nums[right], nums[i] = nums[i], nums[right]
                right -= 1
            print(nums, left, right, i)



```

