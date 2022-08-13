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

### 双向BFS && 一些图问题的trick

* [leetcode 787 k站中转最便宜的航班](https://leetcode.cn/problems/cheapest-flights-within-k-stops/)

算是一个图的问题，使用bell ford算法的变种，我们知道bell ford就是不断遍历每条边，然后去比对到dst的距离经过这条边的距离是否可以使原来的距离变小，如果经过一轮遍历不能缩短任何边，那么就说明已经求出了最短路径。

**本题的关键在于最多中转k次在这个算法中如何去表示，实例中如果像原bell ford算法那样去遍历一遍所有边，一个点可能被松弛多次，重点在于保存每次遍历边之前的距离数组，我们新距离的比对应该用遍历前的状态去比而非实际更新的距离数组，因为有可能更新的点在这轮遍历前就更新过了。**

```cpp'
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // 以src为出发点，加上一个最多松弛k + 1次的限制
        long dist[n];
        for(int i = 0; i < n; ++i){
            dist[i] = INT_MAX;
        }
        dist[src] = 0;
        int bound = k + 1;
        for(int i = 0; i < bound; ++i){
            bool check = false;
            long temp[n];
            for(int j = 0; j < n; ++j)temp[j] = dist[j];
            for(auto& edge : flights){
                int start = edge[0], end = edge[1], weight = edge[2];
                if(dist[end] > temp[start] + weight){
                    dist[end] = temp[start] + weight;
                    check = true;
                }
            }
            if(!check)break;
        }
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};
```

* [leetcode 127单词接龙](https://leetcode.cn/problems/word-ladder/)

这道题其实思路也比较直接，就是BFS，但是有几个小细节可以减小时间复杂度

1. 首先就是将每个单词都分配一个id，用一个map来记录string到int的映射关系，比直接用string做key稍微好一点。
2. 如何处理单词距离为1的单词，如果做一个二重循环检测两个单词是否相差一个字母，需要O(N^2*C)的时间复杂度，如果额外添加一个中间状态，将每个单词添加一个中间节点，这些中间节点依次将每个字母修改为\*, 那么与之相邻的单词势必也会连接这个中间节点，所以只需要O(NC)的时间复杂度。
3. 采用dist数组来更新begin到各个点的距离，这样就不用每次算层次遍历时候队列的长度了。
4. 另外就是双向BFS，大致就是begin和end各有一个dist数组，如果每次对方层次遍历时队列pop出来的值，和对方的起点是连通的，说明双向搜索相遇了。

```cpp
class Solution {
public:
    unordered_map<string, int> wordId;
    vector<vector<int>> edge;
    int nodeNum = 0;

    void addWord(string& word) {
        if (!wordId.count(word)) {
            wordId[word] = nodeNum++;
            edge.emplace_back();
        }
    }

    void addEdge(string& word) {
        addWord(word);
        int id1 = wordId[word];
        for (char& it : word) {
            char tmp = it;
            it = '*';
            addWord(word);
            int id2 = wordId[word];
            edge[id1].push_back(id2);
            edge[id2].push_back(id1);
            it = tmp;
        }
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        for (string& word : wordList) {
            addEdge(word);
        }
        addEdge(beginWord);
        if (!wordId.count(endWord)) {
            return 0;
        }

        vector<int> disBegin(nodeNum, INT_MAX);
        int beginId = wordId[beginWord];
        disBegin[beginId] = 0;
        queue<int> queBegin;
        queBegin.push(beginId);

        vector<int> disEnd(nodeNum, INT_MAX);
        int endId = wordId[endWord];
        disEnd[endId] = 0;
        queue<int> queEnd;
        queEnd.push(endId);

        while (!queBegin.empty() && !queEnd.empty()) {
            int queBeginSize = queBegin.size();
            for (int i = 0; i < queBeginSize; ++i) {
                int nodeBegin = queBegin.front();
                queBegin.pop();
                if (disEnd[nodeBegin] != INT_MAX) {
                    return (disBegin[nodeBegin] + disEnd[nodeBegin]) / 2 + 1;
                }
                for (int& it : edge[nodeBegin]) {
                    if (disBegin[it] == INT_MAX) {
                        disBegin[it] = disBegin[nodeBegin] + 1;
                        queBegin.push(it);
                    }
                }
            }

            int queEndSize = queEnd.size();
            for (int i = 0; i < queEndSize; ++i) {
                int nodeEnd = queEnd.front();
                queEnd.pop();
                if (disBegin[nodeEnd] != INT_MAX) {
                    return (disBegin[nodeEnd] + disEnd[nodeEnd]) / 2 + 1;
                }
                for (int& it : edge[nodeEnd]) {
                    if (disEnd[it] == INT_MAX) {
                        disEnd[it] = disEnd[nodeEnd] + 1;
                        queEnd.push(it);
                    }
                }
            }
        }
        return 0;
    }
};
```

* [leetcode815 公交路线](https://leetcode.cn/problems/bus-routes/)

这道题自己做的大致思路和官方题解差不多，但是可能做的时候不够快吧。有两个细节需要注意一下：

1. 一个是建图的时候，我还是很笨地对每个公交栈经过的路线做二重循环，但是其实可以拿一个哈希表记录每个节点存有公交线路，如果遍历另外一个线路也有之前出现过的点，那么这个点有的线路都和这一轮的线路要连接。
2. 还是dist数组的建立可以优化BFS的写法，让最后的代码写地不那么麻烦。

```cpp
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) {
            return 0;
        }

        int n = routes.size();
        vector<vector<int>> edge(n, vector<int>(n));
        unordered_map<int, vector<int>> rec;
        for (int i = 0; i < n; i++) {
            for (int site : routes[i]) {
                for (int j : rec[site]) {
                    edge[i][j] = edge[j][i] = true;
                }
                rec[site].push_back(i);
            }
        }

        vector<int> dis(n, -1);
        queue<int> que;
        for (int bus : rec[source]) {
            dis[bus] = 1;
            que.push(bus);
        }
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int y = 0; y < n; y++) {
                if (edge[x][y] && dis[y] == -1) {
                    dis[y] = dis[x] + 1;
                    que.push(y);
                }
            }
        }

        int ret = INT_MAX;
        for (int bus : rec[target]) {
            if (dis[bus] != -1) {
                ret = min(ret, dis[bus]);
            }
        }
        return ret == INT_MAX ? -1 : ret;
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

### 二分图匹配

>  写这个的原因是因为上周微软笔试T3，涉及到了这个问题，所以刚好学习一下

* 什么是二分图？简而言之，二分图的所有顶点可以分为两个集合，每个集合内部的点之间没有点连接，图的所有边的顶点都分属于两个集合。

* 关于二分图的判定：使用染色法，先将一个点染成一个颜色，然后将他相邻的点染成另一个颜色，如此往复，如果找到一个相邻点已经染色并且该点颜色和当前点颜色相同，那么则不是二分图，否则是二分图。具体做法是bfs，然后没染色的染色，已经染色的检查是否不同颜色。

* Ford-Fulkerson Algorithm for Maximum Flow Problem。二分图匹配可以转化为最大流问题。其中比较出名的Ford-Fulkerson算法，本质思想是维护一个剩余权重图，具体的算法实现可以参考[这里](https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/)

* 然后将二分图转化为最大流问题，就手动添加一个source和一个sink，分别连接两个集合所有的点。然后每个边的权重为1。最后最大流的数量就等于匹配的个数。具体实现参考[这里](https://www.geeksforgeeks.org/maximum-bipartite-matching/)
* 匈牙利算法，专门用于解决匹配问题的算法。具体思路是如果有匹配项并且没被其他人占有，那就先匹配，如果被其他人占用了，那么就让那个人尝试换一个匹配，如果可以，那么匹配数量加一，如果不行这个人无法添加新的匹配，进入下一个遍历。

对于微软那道题的实现代码

```c++
#define N 1000
int slot[N]; // 每个slot对应的人标号
bool vis[N]; // 标记每个slot是否被访问过。
int g[N][N];
int S;


bool dfs(int x){
    for(int i = 1; i <= S; ++i){
        if(!vis[i] && g[x][i]){
            vis[i] = true;
            if(slot[i] == 0 || dfs(slot[i])){
                slot[i] = x;
                return true;
            }
        }
    }
    return false;
}

bool canMatch(vector<int>& a, vector<int>& b, int s){
    // 图，行为人数
    int n = a.size();
    if(n > s)return false;
    S = s;
    memset(g, 0, sizeof(g));
    for(int i = 1; i <= n; ++i){
        g[i][a[i - 1]] = g[i][b[i - 1]] = 1;
    }
    memset(slot, 0, sizeof(slot));
    
    // finish building a graph.
    int ans = 0;
    cout << "preprocsss finish" << endl;
    for(int i = 1; i <= n; ++i){
        memset(vis, 0, sizeof(vis));
        if(dfs(i))++ans;
    }
    cout << ans << endl;
    return ans == n;
}

int main(int argc, char** argv){
    vector<int> a{1, 2, 1, 6, 8, 7, 8};
    vector<int> b{2,3,4,7,7,8,7};
    cout << canMatch(a, b, 10) << endl;
    return 0;
}
```

