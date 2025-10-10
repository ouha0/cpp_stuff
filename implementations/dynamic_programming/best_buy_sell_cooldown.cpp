#include <limits>
#include <stdio.h>
#include <vector>

class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    int n = prices.size();
    dp.assign(n, std::vector<int>(2, std::numeric_limits<int>::min()));

    return dfs(0, BUY, prices);
  }

private:
  const bool BUY = true;
  const bool SELL = false;
  std::vector<std::vector<int>> dp;

  /* This uses a top down recursive approach; dp reprents max profit starting
   * from a particular day, given we have some buy / sell choice. dfs is the
   * function that recursively solves it */
  int dfs(int state, bool choice, std::vector<int> const &prices) {
    if (state >= prices.size()) {
      return 0;
    }

    if (dp[state][choice] != std::numeric_limits<int>::min()) {
      return dp[state][choice];
    }

    int cooldown = dfs(state + 1, choice, prices);

    if (choice == BUY) {
      int buy = dfs(state + 1, SELL, prices) - prices[state];
      dp[state][BUY] = std::max(cooldown, buy);
    } else {
      int sell = dfs(state + 2, BUY, prices) + prices[state];
      dp[state][SELL] = std::max(sell, cooldown);
    }

    return dp[state][choice];
  }
};

/* It is always nice and intuitive to solve the problem by hand, draw a diagram
 * / decision tree (for all valid decisions) first to get some insight about the
 * code. It's even better if this can be visualised. A dynamic programming
 * method "appears" when you notice that only part of a decision chain matters
 * when solving the problem */
