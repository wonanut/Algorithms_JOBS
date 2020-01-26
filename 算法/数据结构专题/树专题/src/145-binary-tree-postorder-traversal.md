# 145 Binary Tree Postorder Traversal

`中等` `二叉树后序遍历`

 https://leetcode-cn.com/problems/binary-tree-postorder-traversal/



## 题目描述

给定一个二叉树，返回它的 *后序* 遍历。

 **示例:**

```
输入: [1,null,2,3]  
   1
    \
     2
    /
   3 

输出: [3,2,1]
```

 **进阶:** 递归算法很简单，你可以通过迭代算法完成吗？ 

## 思路分析

- 递归实现：按照左右根的顺序访问二叉树,递归调用函数
- 迭代实现：
  - 方法1：迭代写法，利用pre记录上一个访问过的结点，与当前结点比较，如果是当前结点的子节点，说明其左右结点均已访问，将当前结点出栈，更新pre记录的对象。 
  - 方法2：利用两个栈来实现，一个栈存放标志位
  - 方法3：先序遍历迭代的变种，实际上不是后序遍历，但是能解题



## 代码

Java代码

递归实现：

``` java
class Solution {
    public List<Integer> res = new ArrayList<Integer>();
    public List<Integer> postorderTraversal(TreeNode root) {//递归写法
        if(root == null)
            return res;
        postorderTraversal(root.left);
        postorderTraversal(root.right);
        res.add(root.val);
        return res;
    }
}
```

迭代实现：

- 方法1：

```java
class Solution {
    public List<Integer> postorderTraversal(TreeNode root) {//非递归写法
        List<Integer> res = new ArrayList<Integer>();
        if(root == null)
            return res;
        Stack<TreeNode> stack = new Stack<TreeNode>();
        TreeNode pre = null;
        stack.push(root);
        while(!stack.isEmpty()){
            TreeNode curr = stack.peek();            
            if((curr.left == null && curr.right == null) ||
               (pre != null && (pre == curr.left || pre == curr.right))){ 
              //如果当前结点左右子节点为空或上一个访问的结点为当前结点的子节点时，当前结点出栈
                res.add(curr.val);
                pre = curr;
                stack.pop();
            }else{
                if(curr.right != null) stack.push(curr.right); //先将右结点压栈
                if(curr.left != null) stack.push(curr.left);   //再将左结点入栈
            }            
        }
        return res;        
    }
}
```

- 方法2：

```java
//写法（2）：利用两个栈来实现，一个栈存放标志位
class Solution {
    public List<Integer> postorderTraversal(TreeNode root) {//非递归写法
        List<Integer> res = new ArrayList<Integer>();
        if(root == null)
            return res;
        Stack<TreeNode> stack1 = new Stack<TreeNode>();
        Stack<Integer> stack2 = new Stack<Integer>();
        stack1.push(root);
        stack2.push(0);
        while(!stack1.isEmpty()){
            int flag = stack2.pop();
            if(flag == 0){
                stack2.push(1);
                TreeNode currNode = stack1.peek();
                if(currNode.right != null){
                    stack1.push(currNode.right);
                    stack2.push(0);
                }
                if(currNode.left != null){
                    stack1.push(currNode.left);
                    stack2.push(0);
                }                  
            }else{
                res.add(stack1.pop().val);
            }                        
        }
        return res;        
    }
}
```

- 方法3：

```java
class Solution {
    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> res = new LinkedList<Integer>();
        if(root == null)
            return res;
        Stack<TreeNode> stack = new Stack<TreeNode>();
        stack.push(root);
        while(!stack.isEmpty()){
            TreeNode node = stack.pop();
            if(node.left != null) stack.push(node.left);
            //和传统先序遍历不一样，先将左结点入栈
            if(node.right != null) stack.push(node.right);//后将右结点入栈
            res.add(0,node.val);                        //逆序添加结点值
        }     
        return res;
    }
}
```

