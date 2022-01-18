#include <string.h>
#include <algorithm.h>

int valueMainCondition(int n, int W, int* values, int* weights){
  if(values == NULL || weights == NULL)
    return -1;
  int bound = 0;
  for(int i = 0; i < n; ++)
    bound += values[i];
  int dp[bound + 1];
  fill(dp[0], dp[0] + bound + 1, INF);
}
