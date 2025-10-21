#include <stdio.h>
#include <vector>

// enum class Direction { UP = 0, DOWN = 1 };

class Solution {
public:
  /* Idea: Dynamic Programming. Each state depends on three things; current
   * array length, previous element and the direction the previous element ends
   * in. This requires us to have a 3d dynamic array.
   * Optimization: for calculation of a particular array length, we need to sum
   * multiple values of the previous array length; we can use prefix sum here
   * */

  /* Iterate through array length (bottom up approach). */
  int zigZagArrays(int n, int l, int r) {
    int UP = 0;
    int DOWN = 1;
    long long MOD = 1e9 + 7;

    std::vector<std::vector<std::vector<long long>>> dp(
        n + 1, std::vector<std::vector<long long>>(
                   r + 1, std::vector<long long>(2, 0)));

    for (int j = l; j <= r; ++j) {
      if (j > l) {
        dp[2][j][UP] = j - l;
      }
      if (j < r) {
        dp[2][j][DOWN] = r - j;
      }
    }

    for (int i = 3; i <= n; ++i) {
      std::vector<long long> pref_sum_up(r + 2, 0);
      std::vector<long long> pref_sum_down(r + 1, 0);

      for (int k = l; k <= r; ++k) {
        pref_sum_down[k] = (pref_sum_down[k - 1] + dp[i - 1][k][DOWN]) % MOD;
      }

      for (int k = r; k >= l; --k) {
        pref_sum_up[k] = (pref_sum_up[k + 1] + dp[i - 1][k][UP]) % MOD;
      }

      for (int j = l; j <= r; ++j) {
        if (j > l) {
          dp[i][j][UP] = pref_sum_down[j - 1];
        }

        if (j < r) {
          dp[i][j][DOWN] = pref_sum_up[j + 1];
        }
      }
    }

    long long res = 0;
    for (int i = l; i <= r; ++i) {
      res += dp[n][i][UP];
      res += dp[n][i][DOWN];
    }

    return static_cast<int>(res % MOD);
  }
};

/* A more efficient implementation */
class Efficient {
public:
  /* The key idea is that it only keeps information that is required to solve
   * the problem. ANy information that isn't required is discarded. The idea
   * involved 3 key ideas; specific numbers don't matter, only the number of
   * choices, to calculate length i, you only need the results from length i -
   * 1, the problem is symmetrical (hence we can multiply 2 at the end, since we
   * start with an up step. The down step is symmetrical). Integer is used here
   * rather than long long due to the clever use of MOD each time there may be
   * an overload. */

  int zigZagArrays(int n, int l, int r) {
    int MOD = 1e9 + 7;
    r -= l;
    std::vector<int> dp(r + 1, 1);
    for (int i = 1; i < n; ++i) {
      int pre = 0, pre2;

      if (i & 1) {
        for (int v = 0; v <= r; ++v) {
          pre2 = pre + dp[v];
          dp[v] = pre;
          pre = pre2 % MOD;
        }
      } else {
        for (int v = r; v >= 0; --v) {
          pre2 = pre + dp[v];
          dp[v] = pre;
          pre = pre2 % MOD;
        }
      }
    }
    int res = 0;
    for (int v : dp) {
      res = (res + v) % MOD;
    }

    return (2 * res) % MOD;
  }
};

/*
 * Key idea; Notice the resuse of information; whether the dynamic programming
 * approach, or the repetitiveness in the summation (pointing to using a prefix
 * sum approach for better optimization). Be very careful of boundary
 * conditions, and make sure to clearly define the variables before starting the
 * problem
 *
 * Possible test cases to test the problem: extreme array boundaries, no input,
 * single element input etc...
 *
 * */
