# myAlgorithmNote
The guy is lazy and left nothing

我觉得负数部分可以这么理解：
第K个最大值就等于最大值（所有非负数和）减去第K个最小的子序列。这个减去可以理解为：减去一些正数，添加一些负数。总之我们的目的就是让这个最大值减小一些减小到第K大个数，所以我们只要选出所有元素的绝对值组成的数组的第K小序列，如果这个序列中原来的数字就是正数，那么就是在最大值序列中减去这些正数；如果第k小序列中的数字是原数列中负数转变过来的，就相当于在最大值序列中添加这个负数。

```c++
class Solution {
public:
    typedef pair<long long, int> p;
    long long kSum(vector<int>& nums, int k) {
        long long maxSum = 0, n = nums.size();
        for(int i = 0; i < n; ++i){
            if(nums[i] > 0)
                maxSum += nums[i];
            else
                nums[i] *= -1;
        }
        sort(nums.begin(), nums.end());
        priority_queue<p, vector<p>, greater<p>> pq;
        // pq为空的时已经push进去一个0了，所以只要再找接下来的k - 1个堆顶即可
        for(int i = 1; i < k; ++i){
            if(i == 1){
                pq.push({nums[0], 0});
                continue;
            }
            p temp = pq.top();
            pq.pop();
            if(temp.second == n - 1)continue;
            pq.push({temp.first + nums[temp.second + 1], temp.second + 1});
            pq.push({temp.first + nums[temp.second + 1] - nums[temp.second], temp.second + 1});
        }
        return maxSum - (pq.empty() ? 0 : pq.top().first);
    }
};
```