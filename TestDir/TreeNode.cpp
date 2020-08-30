#include<iostream>
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
};
int main(){
    TreeNode* sample=new TreeNode();
    sample->val=15;
    std::cout<<sample->val<<std::endl;
    return 0;
}