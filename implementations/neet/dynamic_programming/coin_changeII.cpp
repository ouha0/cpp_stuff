#include <stdio.h>
#include <vector>

/* There are quite a few solutions to this problem; recursion with constraints,
 * and dynamic programming with two states */

class dfs_solution {
public:
  /* This is a the standard dfs solution, where we discover all possible paths,
   * but with some constraints.
   *
   * dfs solution takes 3 parameters; current amount, coins, and integer
   * representing which coins are allowed to be used
   */

  // The problem with this solution is that it is too slow
  // and does lots of repeated work
  int change(int amount, std::vector<int> &coins) {
    std::sort(coins.begin(), coins.end());
    int offset = 0;
    return dfs(amount, coins, 0);
  }

private:
  int dfs(int n, std::vector<int> &coins, int offset) {
    if (n == 0) {
      return 1;
    } else if (n < 0 || offset >= coins.size() || coins[offset] > n) {
      return 0;
    }

    int count = 0;
    for (int i = offset; i < coins.size(); ++i) {
      count += dfs(n - coins[i], coins, i);
    }
    return count;
  }
};

class dfs_solution_2 {
public:
  int change(int amount, std::vector<int> &coins) {
    std::sort(coins.begin(), coins.end());

    return dfs(amount, 0, coins);
  }

private:
  int dfs(int n, int offset, std::vector<int> &coins) {
    if (n == 0) {
      return 1;
    }

    if (offset >= coins.size()) {
      return 0;
    }

    int res = 0;
    if (n >= coins[offset]) {
      res += dfs(n - coins[offset], offset, coins);
      res += dfs(n, offset + 1, coins);
    }

    return res;
  }
};

class general_dp_solution {
public:
  int change(int amount, std::vector<int> &coins) {
    std::vector<std::vector<int>> dp(coins.size() + 1,
                                     std::vector<int>(amount + 1, 0));

    for (int i = 0; i < coins.size() + 1; ++i) {
      dp[i][0] = 1;
    }

    for (int i = coins.size() - 1; i >= 0; --i) {
      int curr_coin = coins[i];
      // Not the easy off by one error here for amount...
      for (int j = 1; j < amount + 1; ++j) {
        dp[i][j] = dp[i + 1][j];
        if (j - curr_coin >= 0) {
          dp[i][j] += dp[i][j - curr_coin];
        }
      }
    }

    return dp[0][amount];
  }
};

class optimized_dp_Solution {
  /* The key idea to this problem is realising that this is a decision tree, but
   * slightly different and contrained. So there are paths that you are not
   * allowed to take, otherwise it would result in i.e. if we want to make the
   * amount 3, 1 + 2 is the same as 2 + 1, but dfs on all paths ignores this
   * duplicate. The solution here is if we take the path using coin 1, we are
   * allowed to use coin 1 & 2, but if we take the path using coin 2, we can
   * only use coin 2 from there on. (1 + 2 case will be covered in the "1" path)
   * */
public:
  int change(int amount, std::vector<int> &coins) {

    std::vector<uint> dp_prev(amount + 1, 0);
    dp_prev[0] = 1;

    for (int i = coins.size() - 1; i >= 0; --i) {
      std::vector<uint> dp_curr(amount + 1, 0);
      dp_curr[0] = 1;
      int curr_coin = coins[i];
      for (int j = 1; j < amount + 1; ++j) {
        dp_curr[j] = dp_prev[j];

        if (j - curr_coin >= 0) {
          dp_curr[j] += dp_curr[j - curr_coin];
        }
      }
      dp_prev = std::move(dp_curr);
    }
    return dp_prev[amount];
  }
};
