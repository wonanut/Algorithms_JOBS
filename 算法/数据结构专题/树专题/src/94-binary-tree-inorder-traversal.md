# 27 Binary Tree Inorder Traversal

`简单` `二叉树中序遍历`

 https://leetcode-cn.com/problems/binary-tree-inorder-traversal/ 



## 题目描述

给定一个二叉树，返回它的 *中序* 遍历。

 **示例:**

```
输入: [1,null,2,3]  
   1
    \
     2
    /
   3 

输出: [1,3,2]
```

 **进阶:** 递归算法很简单，你可以通过迭代算法完成吗？ 

## 思路分析

- 递归实现：按照左根右的顺序访问二叉树,递归调用函数

- 迭代实现：使用栈来实现，模拟递归步骤，如果当前节点还存在左子节点，就将其入栈，若其左子节点为空，则其为当前最左端的节点，将其加入结果，然后访问该节点的右节点，继续循环。



## 代码

Java代码

递归实现：

``` java
class Solution {
    List<Integer> res = new ArrayList<Integer>();
    public List<Integer> inorderTraversal(TreeNode root) {
        if(root == null)
            return res;
        inorderTraversal(root.left);
        res.add(root.val);
        inorderTraversal(root.right);
        return res;
    }
}
```

迭代实现：

```java
class Solution {
    List<Integer> res = new ArrayList<Integer>();
    public List<Integer> inorderTraversal(TreeNode root) {
        Stack<TreeNode> stack = new Stack<TreeNode>();
    	TreeNode node = root;
    	while (node != null || !stack.isEmpty()) {
            if (node != null) {
                stack.push(node);
                node = node.left;
            } else {
                node = stack.pop();
                res.add(node.val);
                node = node.right;
            }
        }
        return res;
    }
}
```

