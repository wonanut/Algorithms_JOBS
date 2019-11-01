

# 84.柱状图中最大的矩形

## （1）暴力（超时）

```python
#python
class Solution(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        l = len(heights)
        resArea = 0
        for  i in range(l):
            j = i
            while(j < l):
                area = (j-i+1)*min(heights[i:j+1])
                if(area>resArea):
                    resArea = area
                j +=1
        return resArea
```

时间复杂度o(n^2^)

空间复杂度o(1)



## （2）栈

​    目的是每个柱子左右两个方向上，找到都比它低且离它最近的柱子，从而计算以当前柱子为高度时的最大面积。比如，途中柱子3的左右两个边界是柱子2和柱子5，以柱子3的高度为高时，形成的最大面积是：5*(5-2-1)=10。利用栈，可以只遍历一次列表，巧妙的找到以当前柱子为高时的左边界和右边界。

![histogram_area](/Users/qinxiuxin/Downloads/histogram_area.png)



```C++
//C++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        if(size == 0)
            return 0;
        stack <int> s;
        s.push(0);
        int maxArea = 0,i=0;
        for(i = 0; i < size;i++){
            while(!s.empty() &&heights[s.top()]>=heights[i]){
                int value = heights[s.top()];s.pop();
                maxArea = max(maxArea,value*(s.empty()?i:i-1-s.top()));
            }
            s.push(i);  
        }
        while(!s.empty()){
           int value = heights[s.top()];s.pop();
           maxArea =  max(maxArea,value*(s.empty()?i:i-1-s.top()));
        }
        return maxArea;
    }
    
};
```

时间复杂度o(n)

空间复杂度o(n)