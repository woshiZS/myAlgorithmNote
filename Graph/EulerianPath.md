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