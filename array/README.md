#### 差分数组

> 起因是昨天双周赛第三题区间修改，遍历会超时，但是用线段树做又太过于繁琐，因此学习了下差分数据。

* 定义：顾名思义，差分数组就是原来的数组当前项和前一项的差值，具体公式如下：
* ![image-20220821100312908](../image/diffArray)

通过差分数组快速的进行区间修改操作，我们知道前缀和数组使用频繁地进行区间查询，但是并不适用于有区间修改地情况，遇到有区间修改地情况时，差分数组就比较方便。

* 假设我们对[l, r]区间都加上一个值val，我们需要做的是

```c++
diff[l] += val;
diff[r + 1] -= val;
```

根据diff的定义不难推出上述式子，在进行所有的区间操作之后，再进行还原，还原就是对当前差分数组进行累加即可，换句话说，原数组当前index的值等于差分数组从0到index的前缀和。

```c++
vector<int> original(n, 0);
original[0] = diff[0]
for(int i = 1; i < n; ++i){
    original[i] = original[i - 1] + diff[i]; 
}
```

* 例题 [字母移位 II](https://leetcode.cn/problems/shifting-letters-ii/)

```c++
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& sfts) {
        int n = s.size(), m = sfts.size();
        vector<long long> arr(n + 1);
        for(int i = 0; i < m; ++i){
            int val = sfts[i][2] == 1 ? 1 : -1;
            arr[sfts[i][0]] += val;
            arr[sfts[i][1] + 1] -= val;
        }
        long long offset = 0;
        for(int i = 0; i < n; ++i){
            offset += arr[i];
            long long val = (offset + s[i] - 'a') % 26;
            if(val < 0) val += 26;
            s[i] = (char)(val + 'a');
        }
        return s;
    }
};
```

