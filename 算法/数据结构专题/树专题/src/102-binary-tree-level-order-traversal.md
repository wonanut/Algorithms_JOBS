# 102 Binary Tree Level OrderTraversal

`中等` `二叉树后序遍历`

 https://leetcode-cn.com/problems/binary-tree-level-order-traversal/submissions/ 



## 题目描述

给定一个二叉树，返回其按层次遍历的节点值。 （即逐层地，从左到右访问所有节点）。

例如:
给定二叉树: `[3,9,20,null,null,15,7]`

 **示例:**

```
输入: [3,9,20,null,null,15,7]
    3
   / \
  9  20
    /  \
   15   7

返回其层次遍历结果：
[
  [3],
  [9,20],
  [15,7]
]
```

## 思路分析

- 迭代实现：用队列实现广度优先遍历



## 代码

Java代码

迭代实现：

```java
class Solution {
    public List<List<Integer>> levelOrder(TreeNode root) {
        if(root == null)
            return new ArrayList<>();
        List<List<Integer>> res = new ArrayList<>();
        Queue<TreeNode> queue = new LinkedList<TreeNode>();
        queue.add(root);
        while(!queue.isEmpty()){
            int count = queue.size();
            List<Integer> list = new ArrayList<Integer>();
            while(count-- > 0){
                TreeNode node = queue.poll();
                list.add(node.val);
                if(node.left != null)
                    queue.add(node.left);
                if(node.right != null)
                    queue.add(node.right);
            }
            res.add(list);
        }
        return res;
    }
}
```

