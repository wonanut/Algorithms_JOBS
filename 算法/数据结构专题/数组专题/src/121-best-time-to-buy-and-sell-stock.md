# 121 best-time-to-buy-and-sell-stock

`简单` `数组DP`

https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/



## 题目描述

给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。

注意你不能在买入股票前卖出股票。



## 思路分析

用一个temp_min存储遍历到当前位置遇到的最小值，然后使用当前值减去最小值得到temp_max = max(temp_max, price - temp_min)，遍历完成后temp_max中的值即为所求。



## 代码

Python代码

```python
class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        temp_min, temp_max = float('inf'), 0
        for price in prices:
            temp_min = min(temp_min, price)
            temp_max = max(temp_max, price - temp_min)
        return temp_max
```
