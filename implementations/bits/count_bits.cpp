#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Recognise this as a dp problem. Note that is 1 + dp(current state - most
   * significant bit)
   *  */
  std::vector<int> countBits(int n) {
    std::vector<int> dp(n + 1, 0);
    int offset = 1;

    for (int i = 1; i < n + 1; ++i) {
      if (offset * 2 == i) {
        offset = i;
      }
      dp[i] = dp[i - offset] + 1;
    }
    return dp;
  }
};

class brute_force_solution {
public:
  std::vector<int> countBits(int n) {
    std::vector<int> res(n + 1, 0);
    for (int i = 1; i < n + 1; ++i) {
      int num = i;
      while (num != 0) {
        num = num & (num - 1);
        res[i]++;
      }
    }

    return res;
  }
};
