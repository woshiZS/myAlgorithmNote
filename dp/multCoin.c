#include <stdio.h>
#include <string.h>
int MAXK = 101;

int MAXN = 101;

int main(){
    int n = 3, k = 17;
    int a[3] = {3, 5, 8};
    int m[3] = {3, 2, 2};
    // dp[i + 1][j]表示从前i个中选取和为j，第i个数字剩下的个数
    int dp[MAXN][MAXK];
    memset(dp, -1, sizeof(dp));
    // 第一列应该全部初始化为，因为和为0时不需要任何一个数字
    for(int j = 0; j <= n; ++j)
        dp[j][0] = m[j - 1];
    for(int i = 1; i <= n; ++i){
        int currentValue = a[i - 1];
        for(int j = 0; j <= k; ++j){
            if(dp[i - 1][j] >= 0)
                dp[i][j] = m[i - 1];
            else if(currentValue > j || dp[i][j - currentValue] <= 0)
                dp[i][j] = -1;
            else
                dp[i][j] = dp[i][j - currentValue] - 1;
        }
    }
    if(dp[n][k] >= 0)
        printf("There exists some number whose total sum equals to %d\n", k);
    else
        printf("Required number don't exist.\n%d\n", dp[n][k]);   
    return 0;
}