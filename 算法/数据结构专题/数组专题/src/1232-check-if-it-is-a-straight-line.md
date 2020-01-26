# 1232 check-if-it-is-a-straight-line

`简单` `数学`

https://leetcode-cn.com/problems/check-if-it-is-a-straight-line/



## 题目描述

在一个 XY 坐标系中有一些点，我们用数组 coordinates 来分别记录它们的坐标，其中 coordinates[i] = [x, y] 表示横坐标为 x、纵坐标为 y 的点。

请你来判断，这些点是否在该坐标系中属于同一条直线上，是则返回 true，否则请返回 false。



## 思路分析

使用斜率判断，但要注意特殊情况：k不存在！



## 代码

Python代码

```python
class Solution(object):
    def checkStraightLine(self, coordinates):
        """
        :type coordinates: List[List[int]]
        :rtype: bool
        """
        # (y1 - y0) / (x1 - x0) = (yi - y0) / (xi - x0)可能存在分母为0的情况
        # 因此将除法转换为乘法：(y1 - y0) * (xi - x0) = (yi - y0) * (x1 - x0)
        first, second = coordinates[0], coordinates[1]
        for coordinate in coordinates:
            if (second[1] - first[1]) * (coordinate[0] - first[0]) != (coordinate[1] - first[1]) * (second[0] - first[0]):
                return False
        return True
```