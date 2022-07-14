### 最小生成树

* 吐槽一句，英文笔记看得还是比较费精力2333.
* 首先是概念，一个拥有n个节点连通图的最小生成树是原图的极小联通子图，包含所有的节点，包含n - 1条边，一般由kruskal算法或者prim算法求出。prim适用于稠密图，kruskal适用于简单图。
* 首先是kruskal，整体的流程还是比较简单直接，对图中所有的权值边进行一个排序，从小到大选取边，如果改边对应的两个点没有联通，就选取这条边。如果该边对应的两个顶点已经连通，则跳过这条边选取下一条边，如此往复，每一轮选取结束之后检查所有点是否都已经连通，如果是，则跳出循环，完成算法。
* 



## Eulerain Path

Today we are talking about the Eurain Path/Circuit algorithm.
* Definition

An Eulerain path is a graph which qualifies 3 conditions below:
> One vertex(start point) with **(out_degrees - in_degrees)=1** 
> One vertex(end point) with **(in_degrees - out_degrees)=1** 
> Other vertices with out_degree == in_degree

If all the vertices' in_degree equals to their out_degree, this graph will be an Eulerain Circuit.

* Main steps of this algorithm

Verify if or not this is an Eurain path or circuit and find the start and end vertex.

The algorithm is transformed from depth-first search. 

First,use dfs to find the main path, if all edges have been included,it will be the final result.

Second, when we trace back and find if there is some node with extra out_degrees,dfs into that path again until all edges are traversed.

The related problem is leetcode 332.

```c++
class Solution {
unordered_map<string,priority_queue<string,vector<string>,greater<string>>> mp;
public:
    vector<string> ans;
    void dfs(const string& target){
        while(mp.count(target)&&mp[target].size()>0){
            string temp = mp[target].top();
            mp[target].pop();
            dfs(temp);
        }
        ans.emplace_back(target);
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for(auto& item:tickets){
            mp[item[0]].emplace(item[1]);
        }
        dfs("JFK");
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
```