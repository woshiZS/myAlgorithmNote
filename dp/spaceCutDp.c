#include <string.h>

int max(int left, int right){
  return left > right ? left : right;
}

int singleCondition(int n, int W, int* values, int* weights){
  if(values == NULL || weights == NULL)
    return -1;
  int dp[W + 1];
  memset(dp, 0, sizeof(dp));
  for(int i = 1; i <= n; ++i){
    int tempVal = values[i - 1];
    int tempWeigh = weights[i - 1];
    for(int j = W; j >= tempWeigh; --j){
      dp[j] = max(dp[j], dp[j - tempWeigh] + tempVal);
    }
  }
  return dp[W];
}

int multiCondition(int n, int W, int* values, int* weights){
  if(values == NULL || weights == NULL)
    return -1;
  int dp[W + 1];
  memset(dp, 0, sizeof(dp));
  for(int i = 1; i <= n; ++i){
    int tempVal = values[i - 1];
    int tempWeigh = weights[i - 1];
    for(int j = tempWeigh; j <= W; ++j){
      dp[j] = max(dp[j], dp[j - tempWeigh] + tempVal);
    }
  }
  return dp[W];
}
