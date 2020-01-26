# 剑指offer题解（Java）



## 1 [M] 二维数组中的查找

> 题目描述：
>
> 在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
>
> 题目链接：  `https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=13&tqId=11154&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking` 

```
用例:
5,[[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]
输出：false
```

```java
/*
思路1：
    利用二维数组由上到下，由左到右递增的规律，
    那么选取右上角或者左下角的元素a[row][col]与target进行比较，
    当target小于元素a[row][col]时，那么target必定在元素a所在行的左边,
    即col--；
    当target大于元素a[row][col]时，那么target必定在元素a所在列的下边,
    即row++
*/
public boolean Find(int target, int [][] array) {
    int col = array[0].length - 1, row = 0;
    while (row < array.length && col >= 0) {
        if (target < array[row][col])
            col--;
        else if (target > array[row][col])
            row++;
        else 
            return true;
    }
    return false;
}
```

```java
//思路2：因为每一行都是有序的，因此可以通过对每一行进行二分查找得到答案，时间复杂度nlogn。
//二分直接调库了，Arrays.binarySearch的返回值：若找到该数字，返回其索引；
//若未找到该数字，返回(-(insertion point) - 1)
public boolean Find(int target, int [][] array) {
    for (int i = 0;i < array.length;i++) {
        int index = Arrays.binarySearch(array[i], target);
        if (index >= 0)
            return true;
    }
    return false;
}
```



------



## 2 [E] 替换空格 

> 题目描述：
>
> 请实现一个函数，将一个字符串中的每个空格替换成“`%20`”。例如，当字符串为 `We Are Happy`. 则经过替换之后的字符串为`We%20Are%20Happy`。
>
> 题目链接： `https://www.nowcoder.com/practice/4060ac7e3e404ad1a894ef3e17650423?tpId=13&tqId=11155&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking` 

```
用例：
We Are Happy
输出：
We%20Are%20Happy
```

```java
//简单的字符串替换
public String replaceSpace(StringBuffer str) {
    for (int i = 0;i < str.length();i++) {
        if (str.charAt(i) == ' ') {
            str.insert(i + 1, "%20");
            str.deleteCharAt(i);
        }
    }
    return str.toString();
}
```



------



## 3 [E] 从尾到头打印链表 

> 题目描述：
> 输入一个链表，按链表从尾到头的顺序返回一个ArrayList。
>
> 题目链接： `https://www.nowcoder.com/practice/d0267f7f55b3412ba93bd35cfa8e8035?tpId=13&tqId=11156&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking` 

```
用例：
1 -> 2 -> 3;
输出：
3 -> 2 -> 1;
```

```java
//思路1：存入List后交换一下
public ArrayList<Integer> printListFromTailToHead(ListNode listNode) {
    ArrayList<Integer> res = new ArrayList<Integer>();
    while (listNode != null) {
        res.add(listNode.val);
        listNode = listNode.next;
    }
    int i = 0, j = res.size() - 1;
    while (i < j) {
        //这一块可以交换Node，也可以交换val，根据题目要求处理
        int temp = res.get(i);
        res.set(i, res.get(j));
        res.set(j, temp);
        i++;
        j--;
    }
    return res;
}
```

```java
//思路2：递归或者用栈实现
ArrayList<Integer> res = new ArrayList<Integer>();
public ArrayList<Integer> printListFromTailToHead(ListNode listNode) {
    if (listNode == null) return res;
    if (listNode.next != null) {
        res = printListFromTailToHead(listNode.next);
    }
    res.add(listNode.val);
    return res;
}
```



------



## 4 [M] 重建二叉树 

> 题目描述:
> 输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列`{1,2,4,7,3,5,6,8}`和中序遍历序列`{4,7,2,1,5,3,8,6}`，则重建二叉树并返回。
>
> 题目链接： `https://www.nowcoder.com/practice/8a19cbe657394eeaac2f6ea9b0f6fcf6?tpId=13&tqId=11157&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking` 

    用例：
    给出前序遍历 preorder = [3,9,20,15,7]
    中序遍历 inorder = [9,3,15,20,7]
    返回如下的二叉树：
    	3
       / \
      9  20
        /  \
       15   7
```java
//思路：根据前序遍历和中序遍历的特性，构造二叉树
public TreeNode reConstructBinaryTree(int [] pre,int [] in) {
    if (pre.length == 0) return null;
    return reConstructBinaryTree(pre,in,0,0,pre.length - 1);
}
public TreeNode reConstructBinaryTree(int [] pre,int [] in,int preIndex,int start,int end) {
    if (start > end)
        return null;
    if (start == end)
        return new TreeNode(in[start]);
    int index = 0;
    for (int i = start;i <= end;i++) {
        if (in[i] == pre[preIndex]) {
            index = i;
            break;
        }
    }
    TreeNode root = new TreeNode(pre[preIndex]);
    root.left = reConstructBinaryTree(pre,in,preIndex + 1, start, index - 1);
    root.right = reConstructBinaryTree(pre,in,preIndex + (index - start) + 1, index + 1, end);
    return root;
}
```



------



## 5 [E]  用两个栈实现队列

> 题目描述：
> 用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
>
> 题目链接：`https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=13&tqId=11158&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking`

```java
//思路：想得到就想得到，想不到就想不到哭
import java.util.Stack;
public class Solution {
    Stack<Integer> stack1 = new Stack<Integer>();
    Stack<Integer> stack2 = new Stack<Integer>();
    
    public void push(int node) {
        stack1.push(node);
    }
    
    public int pop() {
        while (stack1.isEmpty() && stack2.isEmpty()) 
            throw new RuntimeException("The Queue is Empty!");
        if (stack2.isEmpty())
            while (!stack1.isEmpty()) 
                stack2.push(stack1.pop());
        return stack2.pop();
    }
}
```



------



## 6 [E]  旋转数组的最小数字 

> 题目描述:
> 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
> 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
> 例如数组`{3,4,5,1,2}`为`{1,2,3,4,5}`的一个旋转，该数组的最小值为1。
> NOTE：给出的所有元素都大于0，若数组大小为0，请返回0
>
> 题目链接： `https://www.nowcoder.com/practice/9f3231a991af4f55b95579b44b7a01ba?tpId=13&tqId=11159&tPage=1&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking` 

```
用例：
3 4 5 1 2
输出：
1
```

```java
/*思路：类似于二分查找的做法。由于数组是部分有序的，可以使用二分查找来加快查找速度，不过该问题边界条件容易写错，需要多加思考*/
public int minNumberInRotateArray(int [] array) {
    if (array.length == 0) 
        return 0;
    int index = 0, start = 0, end = array.length - 1, mid = (start + end) / 2;
    while (start <= end) {
        mid = (start + end) / 2;
        if (array[mid] >= array[end]) {
            if (mid < array.length - 1 && array[mid] > array[mid + 1])
                return array[mid + 1];
            start = mid + 1;
        } else if (array[mid] < array[end]) {
            if (mid > 0 && array[mid] < array[mid - 1]) 
                return array[mid];
            end = mid - 1;
        }
    }
    return array[mid];
}
```



------



## 8 [E]  斐波那契数列 

> 大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）。
> n<=39
>
> 题目链接:https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=13&tqId=11160&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking

```
用例：
n = 3
输出
3
```

```java
//解法一：递归（慢）
public class Solution {
    public int Fibonacci(int n) {
        return n <= 1 ? n : Fibonacci(n - 1) + Fibonacci(n - 2);
    }
}
```

```java
//解法二：动态规划，其中int[] Fibn可以压缩为一个两个值
public class Solution {
    public int Fibonacci(int n) {
         int[] Fibn = new int[40];
            Fibn[0]=0;
            Fibn[1]=1;
            for (int i = 2;i < 40;i++) {
                Fibn[i] = Fibn[i - 1] + Fibn[i - 2];
            }
            return Fibn[n];
    }
}
```

```java
//解法三：记忆化搜索 可以写，但没必要
```

