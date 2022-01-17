#include "spaceCutDp.h"
#include <stdio.h>

int main(){
  int n = 3, W = 7;
  int weights[3] = {3, 4, 2};
  int values[3] = {4, 5, 3};
  int singlerResult = singleCondition(n, W, values, weights);
  int multiResult = multiCondition(n, W, values, weights);
  printf("Single Result: %d\nMulti Result: %d\n", singleResult, multiResult);
  return 0;
}
