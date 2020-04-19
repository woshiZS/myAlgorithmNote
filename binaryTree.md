---
typora-copy-images-to: image
typora-root-url: ./
---

[TOC]

### Introduction

![slamdunk](/C:/Users/刘韧韬/slamdunk.bmp)

Tree,one type of data structure which is often used,is commonly applied to simulate data set with Tree-like characters.

We can also regard it as directed acyclic graph which has N nodes and N-1 sides.More specifically,for any code in binary tree,it mostly has two off-spring nodes.

### 1.Traverse

* preOrder Traverse

root   ==>  left child  ==> right child

recursion version:

```cpp
class Solution {
public:
    vector<int> ans;
    vector<int> preorderTraversal(TreeNode* root) {
        if(root != NULL){
            ans.push_back(root -> val);
            preorderTraversal(root -> left);
            preorderTraversal(root -> right);
        }
        return ans;
    }
}
```

Iteration version:

```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        TreeNode* curr=root;
        stack<TreeNode*> stk;
        while(curr||stk.size()){
            while(curr){
                ans.push_back(curr->val);
                stk.push(curr->right);
                curr=curr->left;
            }
            if(!stk.empty()){curr=stk.top();stk.pop();}
        }
        return ans;
    }
};
```

* InOrder Traverse

left child ==> root ==> right child

Generally speaking we can get an increasing sequence through Inorder traverse a binary search tree.

recursion version:

```cpp
class Solution {
public:
    vector<int> ans;
    vector<int> inorderTraversal(TreeNode* root) {
        if(root){
            inorderTraversal(root->left);
            ans.push_back(root->val);
            inorderTraversal(root->right);
        }
        return ans;
    }
};
```

iteration version:

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> stk;
        TreeNode* curr=root;
        while(curr||!stk.empty()){
            while(curr){
                stk.push(curr);
                curr=curr->left;
            }
            curr=stk.top()->right;
            ans.push_back(stk.top()->val);
            stk.pop();
        }
        return ans;
    }
};
```

* postOrder Traverse

left child ==> right child ==>root

It is worth noticing that when we delete a node from a tree,we should firstly delete the left child,then the right child and finally the root.

We can build binary tree to analyse postfix expression.And you can find the primitive expression by InOrder Traverse.

See also at the codeup **Implete a Caculator**.

recursion version

```c++
class Solution {
public:
    vector<int> ans;
    vector<int> postorderTraversal(TreeNode* root) {
        if(root){
            postorderTraversal(root->left);
            postorderTraversal(root->right);
            ans.push_back(root->val);
        }
        return ans;//useful skill we only need the last return value of this function
    }
};
```

Iteration version:

different from the kinds of traversal above,we need to add a flag to record if the current pointer is back from the right child or not.Only when current  pointer is back from the right child,can we add stack's top's value into ans.

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> stk;
        unordered_map<TreeNode*,int> mp;
        TreeNode* curr=root;
        while(curr||!stk.empty()){
            while(curr){
                stk.push(curr);
                curr=curr->left;
            }
            if(mp.find(stk.top())!=mp.end()){
                ans.push_back(stk.top()->val);
                stk.pop();
            }
            else{
                mp[stk.top()]=1;
                curr=stk.top()->right;
            }
        }
        return ans;
    }
};
```

* levelOrder Traversal

Use BFS and queue for implementation.

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root)return ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            vector<int> temp;
            int size=q.size();//calculate the amount of each layer!!!
            while(size--){
                TreeNode* curr=q.front();
                temp.push_back(curr->val);
                if(curr->left)q.push(curr->left);
                if(curr->right)q.push(curr->right);
                q.pop();
            }
            ans.push_back(temp);
        }
        return ans;
    }
};
```

