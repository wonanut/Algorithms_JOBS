# 剑指offer题解（Java）



## 1 [M] 二维数组中的查找

> 题目描述：
>
> 在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
>
> 题目链接：  https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=13&tqId=11154&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking 

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
> 请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
>
> 题目链接： https://www.nowcoder.com/practice/4060ac7e3e404ad1a894ef3e17650423?tpId=13&tqId=11155&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking 

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
> 输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。



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
//根据前序遍历和中序遍历的特性，构造二叉树
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


