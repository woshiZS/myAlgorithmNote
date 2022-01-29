#include <stdio.h>
#include <string.h>
int max(int a, int b){
    return a > b ? a : b; 
}


int main(){
    int n = 5;
    int a[5] = {4, 2, 3, 1, 5};
    int dp[n];
    memset(dp, 0, sizeof(dp));
    int ret = 1;
    for(int i = 0; i < n; ++i){
        dp[i] = 1;
        for(int j = 0; j < i; ++j)
            if(a[i] > a[j])
                dp[i] = max(dp[i], dp[j] + 1);
        ret = max(ret, dp[i]);
    }
    printf("The length of LIS is %d\n", ret);
    return 0;
}