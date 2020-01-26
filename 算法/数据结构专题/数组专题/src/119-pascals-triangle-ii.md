# 119 pascals-triangle-ii

`简单` `数组DP`

https://leetcode-cn.com/problems/pascals-triangle-ii/



## 题目描述

给定一个非负索引 *k*，其中 *k* ≤ 33，返回杨辉三角的第 *k* 行。

**示例:**

```python
输入: 3
输出: [1,3,3,1]
```



## 思路分析

数组DP



## 代码

Python代码

```python
class Solution(object):
    def getRow(self, rowIndex):
        """
        :type rowIndex: int
        :rtype: List[int]
        """
        preLine = [1]
        for row in range(1, rowIndex + 1):
            curLine = [1 for i in range(row + 1)]
            curLine[0], curLine[-1] = 1, 1

            for i in range(1, row):
                curLine[i] = preLine[i - 1] + preLine[i]
            preLine = curLine
        return preLine
```