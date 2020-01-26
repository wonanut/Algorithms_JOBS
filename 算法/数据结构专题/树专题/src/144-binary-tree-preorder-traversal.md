# 27 Binary Tree Preorder Traversal

`简单` `二叉树遍历`

 https://leetcode-cn.com/problems/binary-tree-preorder-traversal/ 



## 题目描述

给定一个二叉树，返回它的 *前序* 遍历。

 **示例:**

```
输入: [1,null,2,3]  
   1
    \
     2
    /
   3 

输出: [1,2,3]
```

 **进阶:** 递归算法很简单，你可以通过迭代算法完成吗？ 

## 思路分析

- 递归实现：按照根左右的顺序访问二叉树,递归调用函数

- 迭代实现：使用栈来实现，右节点先入栈，左节点后入栈



## 代码

Java代码

递归实现：

``` java
class Solution {
    List<Integer> res = new ArrayList<Integer>();
    public List<Integer> preorderTraversal(TreeNode root) {  
        if(root == null)
            return res;
        res.add(root.val);
        preorderTraversal(root.left);
        preorderTraversal(root.right);
        return res;
    }
}
```

迭代实现：

```java
class Solution {
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> res = new ArrayList<Integer>();
        if(root == null)
            return res;
        Stack<TreeNode> stack = new Stack<TreeNode>();
        stack.push(root);
        while(!stack.isEmpty()){
            TreeNode node = stack.pop();
            res.add(node.val);
            if(node.right != null)
                stack.push(node.right);
            if(node.left != null)
                stack.push(node.left);
        }
        return res;
    }
}
```

