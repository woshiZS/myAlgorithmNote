### 最小生成树

* 吐槽一句，英文笔记看得还是比较费精力2333.

* 首先是概念，一个拥有n个节点连通图的最小生成树是原图的极小联通子图，包含所有的节点，包含n - 1条边，一般由kruskal算法或者prim算法求出。prim适用于稠密图，kruskal适用于简单图。

#### Kruskal

* 首先是kruskal，整体的流程还是比较简单直接，对图中所有的权值边进行一个排序，从小到大选取边，如果改边对应的两个点没有联通，就选取这条边。如果该边对应的两个顶点已经连通，则跳过这条边选取下一条边，如此往复，每一轮选取结束之后检查所有点是否都已经连通，如果是，则跳出循环，完成算法。
* 在kruskal算法检测两点是否连通的过程中，需要用到并查集做检测。最后跳出循环可以用选取的边数量为点的数量减一来判定。
* 对应题目：[leetcode 1584 连接所有点的最小费用](https://leetcode.cn/problems/min-cost-to-connect-all-points/)

### 最小高度树

* 原题链接： [leetcode 310 最小高度树](https://leetcode.cn/problems/minimum-height-trees/)
* 这道题主要用到了拓扑排序的解法，拓扑排序实现比较简单，关键在于如何证明这种方法的正确性。
* 首先，根节点肯定位于两个叶子节点的路径中，并且树的高度受限制为从根节点出发最长的一边，所以使得树高度最小的关键在于均摊最大叶子节点之间的长度，当这个路径中的节点数量为奇数的时候，目标根节点就只有一个，如果是偶数个，那么目标根节点就有两个。
* 每次将度为1的点入队，并且更新与之相关的节点度数，相当于挪去最底下一层之后，求剩下的树的最小高度，原题的最小高度就是剩下的树的最小高度加上挪去的叶子节点层数，有点类似于递归的思想。

```c++
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1)return {0};
        vector<int> degree(n, 0);
        vector<vector<int>> graph(n);
        for(auto& edge : edges){
            ++degree[edge[0]];
            ++degree[edge[1]];
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        queue<int> q;
        for(int i = 0; i < n; ++i){
            if(degree[i] == 1)
                q.push(i);
        }
        int leftCnt = n;
        while(leftCnt > 2){
            int sz = q.size();
            leftCnt -= sz;
            while(sz--){
                int temp = q.front();
                q.pop();
                for(auto& num : graph[temp]){
                    --degree[num];
                    if(degree[num] == 1){
                        q.push(num);
                    }
                }
            }
        }
        vector<int> ans;
        while(!q.empty()){
            ans.push_back(q.front());
            q.pop();
        }
        return ans;
    }
};
```



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