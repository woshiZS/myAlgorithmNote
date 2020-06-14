---
typora-copy-images-to: image
typora-root-url: ./
---

[TOC]

### Introduction

![slamdunk](/image/slamdunk.bmp)

Tree,one type of data structure which is often used,is commonly applied to simulate data set with Tree-like characters.

We can also regard it as directed acyclic graph which has N nodes and N-1 sides.More specifically,for any node in binary tree,it mostly has two off-spring nodes.

### 1.Traverse

#### preOrder Traverse

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

#### InOrder Traverse

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

#### postOrder Traverse

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

#### levelOrder Traversal

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

### 2.Use recursion to solve Tree-related problem

As is known tous all,binary tree is one kind of recursively defined structure.Thus, a majority of tree-related problems can be solved by recursion,Usually,there is two patterns:top-down mode and bottom-up mode.

#### top-down mode

Like preOrder Traversal,the principle is below:

```cpp
1. return specific value for null node
2. update the answer if needed                      // anwer <-- params
3. left_ans = top_down(root.left, left_params)      // left_params <-- root.val, params
4. right_ans = top_down(root.right, right_params)   // right_params <-- root.val, params
5. return the answer if needed                      // answer <-- left_ans, right_ans
```

If we need to calculate the maxdeepth of a tree,we can code like this:

```c++
int answer;		       // don't forget to initialize answer before call maximum_depth
void maximum_depth(TreeNode* root, int depth) {
    if (!root) {
        return;
    }
    if (!root->left && !root->right) {
        answer = max(answer, depth);
    }
    maximum_depth(root->left, depth + 1);
    maximum_depth(root->right, depth + 1);
}
/*
In this program,we update the max value when it traverses to a leaf node(and depth must be greater than max),we can also set depth starting with 0 and update value when curr node is nullptr. 
*/
```

#### bottom-up mode

Personally,I think this mode is easier to understand an use,Let's use the same example:caculate depth.

```cpp
1. return 0 if root is null                 // return 0 for null node
2. left_depth = maximum_depth(root.left)
3. right_depth = maximum_depth(root.right)
4. return max(left_depth, right_depth) + 1  // return depth of the subtree rooted at root
```

And implementation

```c++
int maximum_depth(TreeNode* root) {
	if (!root) {
		return 0;                                 // return 0 for null node
	}
	int left_depth = maximum_depth(root->left);
	int right_depth = maximum_depth(root->right);
	return max(left_depth, right_depth) + 1;	  // return depth of the subtree rooted at root
}
```

#### summary

**In my perspective,I think the most important thing is to comfirm two things:**

* what is the relation between the current anwser and the next anwser?
* when should we stop iteration?

think differently and understand abstract theory when we are writing OJ. 

###  Exercise

#### max depth

```cpp
class Solution {
public:
    int ans;
    void travel(TreeNode* root,int depth){
        if(!root){
            ans=max(depth,ans);
            return;
        }
        travel(root->left,depth+1);
        travel(root->right,depth+1);
    }
    int maxDepth(TreeNode* root) {
        ans=0;
        travel(root,0);
        return ans;
    }
};
```

#### symmetry binary tree

```c++
class Solution {
public:
    bool theSame(TreeNode* left,TreeNode* right){//judge two 
        if(left==NULL&&right==NULL)return true;
        else if(left==NULL||right==NULL)return false;
        else if(left->val!=right->val)return false;
        else{
            return theSame(left->left,right->right)&&theSame(left->right,right->left);
        }
    }
    bool isSymmetric(TreeNode* root) {
        if(!root)return true;
        return theSame(root->left,root->right);
    }
};
```

