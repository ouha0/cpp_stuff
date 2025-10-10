#include <stdio.h>
#include <vector>

class Solution {
public:
  int uniquePaths(int m, int n) {
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
      dp[1][i] = 1;
    }

    for (int i = 1; i <= m; ++i) {
      dp[i][1] = 1;
    }

    for (int i = 2; i <= m; ++i) {
      for (int j = 2; j <= n; ++j) {
        if (j - 1 >= 1) {
          dp[i][j] += dp[i][j - 1];
        }

        if (i - 1 >= 1) {
          dp[i][j] += dp[i - 1][j];
        }
      }
    }

    return dp[m][n];
  }
};

/* Key idea: Just a standard 2d dp question. Be careful of boundary conditions.
 * Remember to have extreme test cases; empty input, small input, standard
 * input, behaviour when input is on the boundary */
