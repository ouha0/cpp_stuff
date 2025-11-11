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

class Solution_leaf_up {
  /* Idea: recogise this as a decision tree (graph). At each state, we have a
   * set of decisions. we can do dfs on the decisions, and some decisions repeat
   * each other. Since there is repetition, we can do caching to speed up the
   * algorithm. This caching property is the key in dynamic programming
   *
   * We first need a 2d dp array, storing the state + the buying / selling state
   *
   * the dfs goes like this. We start from ith state, and buying/selling state.
   * if ith state >= size, we return 0.
   * Otherwise if we are in buying state, it means the profit of the current
   * state is the cost it takes to purchase the stock, and maximum profit of the
   * selling state at state + 1.
   *
   * If we are in the selling state, it means the max profit of the current
   * state is price we sell for + maximum profit we can be in state + 2, buying
   * state
   *
   *
   * Note that this is a top down approach. i.e. it is dp from the leaf node of
   * the decision tree towards the root
   * */
public:
  int maxProfit(std::vector<int> &prices) {
    std::vector<std::vector<int>> dp(
        prices.size() + 2,
        std::vector<int>(2, std::numeric_limits<int>::max()));
    /* Note the use of vectors for the hashmap. This is because C++ can't hash
     * pairs by default, it would require a manual hash function. The problem
     * will arise if the price is ever at integer max, which is highly unlikely
     * An alternative will involve using std::map
     */

    return dfs(0, true, prices, dp);
  }

private:
  int dfs(int state, bool buying, std::vector<int> &prices,
          std::vector<std::vector<int>> &dp) {
    if (state >= prices.size()) {
      return 0;
    }

    // Setting default to -1 is also perfectly fine here, since -1 will never be
    // stored (0 / doing nothing is always a better option)
    if (dp[state][buying] != std::numeric_limits<int>::max()) {
      return dp[state][buying];
    }

    if (buying) {
      int do_nothing = dfs(state + 1, buying, prices, dp);
      int buy = dfs(state + 1, !buying, prices, dp) - prices[state];
      dp[state][buying] = std::max(do_nothing, buy);

    } else {
      int do_nothing = dfs(state + 1, buying, prices, dp);
      int sell = dfs(state + 2, !buying, prices, dp) + prices[state];
      dp[state][buying] = std::max(do_nothing, sell);
    }

    return dp[state][buying];
  }
};

class Solution_space_optimize {
  /* Idea: Use dynamic programming bottom up, saving only the required states.
   * There are 3 of them. max profit at buy_state + 1, max profit at buy_state +
   * 2, max profit at sell_state + 1
   * These need to be used to calculate the max profit from buying and selling
   * at the current state
   * */
public:
  int maxProfit(std::vector<int> &prices) {
    int n = prices.size();
    int dp1_buy = 0;
    int dp2_buy = 0;
    int dp1_sell = 0;

    for (int i = n - 1; i >= 0; --i) {
      int dp_buy = std::max(dp1_sell - prices[i], dp1_buy);
      int dp_sell = std::max(dp2_buy + prices[i], dp1_sell);

      dp2_buy = dp1_buy;
      dp1_buy = dp_buy;
      dp1_sell = dp_sell;
    }

    return dp1_buy;
  }
};

/* The key to this problem is realising it is a decision tree, hence
 * can be solved via recursion / dfs. In addition to this, note
 * the repetivieness in dfs call stacks; this can be improved via
 * caching, which is the key of dynamic programming
 *
 * */
