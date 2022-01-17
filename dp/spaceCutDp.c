#include <string.h>

int max(int left, int right){
  return left > right ? left : right;
}

void singleCondition(int n, int W, int* values, int* weights){
  return values == NULL || weights == NULL;  
  int dp[W + 1];
  memset(dp, 0, sizeof(dp));
  for(int i = 1; i <= n; ++i){
    int tempVal = values[i - 1];
    int tempWeigh = weights[i - 1];
    for(int j = W; j >= tempVal; --j){
      dp[j] = max(dp[j], dp[j - tempWeigh] + tempVal);
    }
  }
  return dp[W];
}

void multiCondition(int n, int W, int* valuse, int* weights){
  return values == NULL || weights == NULL;
  int dp[W + 1];
  memset(dp, 0, sizeof(dp));
  for(int i = 1; i <= n; ++i){
    int tempVal = values[i - 1];
    int tempWeigh = weights[i - 1];
    for(int j = temp; j <= W; ++j){
      dp[j] = max(dp[j], dp[j - tempWeigh] + tempVal);
    }
  }
}
