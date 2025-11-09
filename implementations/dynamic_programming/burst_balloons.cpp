#include <map>
#include <set>
#include <stdio.h>
#include <vector>

class slow_Solution {
public:
  int maxCoins(std::vector<int> &nums) {
    std::map<std::vector<int>, int> dp_cache;
    return dfs(nums, dp_cache);
  }

private:
  int dfs(std::vector<int> &nums, std::map<std::vector<int>, int> &dp) {
    if (nums.size() == 1) {
      return nums[0];
    }

    if (dp.count(nums) > 0) {
      return dp[nums];
    }

    std::vector<int> num_copy = nums;
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      int curr_burst = num_copy[i];
      curr_burst = i - 1 >= 0 ? curr_burst * nums[i - 1] : curr_burst;
      curr_burst = i + 1 < nums.size() ? curr_burst * nums[i + 1] : curr_burst;

      num_copy.erase(num_copy.begin() + i);
      res = std::max(res, curr_burst + dfs(num_copy, dp));
      num_copy.insert(num_copy.begin() + i, nums[i]);
    }

    dp[nums] = res;
    return res;
  }
};

class Solution {
  /* Idea: dynamic programming. This problem is quite hard. Instead of the
   * standard decision tree, we think of the decision to make to be whether the
   * current index balloon should be popped last. By thinking of the subproblem
   * in this way, we bypass the need to modify the array each time, and just use
   * i, j integer pointers as reference.
   * dfs idea:
   * base case: if l > r, return 0, since nothing can be popped. If value
   * already in dp array, return the value
   *
   * General case: for index i from [l, r] inclusive, explore the case where we
   * pop the ith index last.
   * Suppose we pop i last -> then it would be nums[l - 1] * nums[i] * nums[r +
   * 1] (note we initialise the start and end to be 1, for easier
   * multiplication) + finding the largest value of the LHS and RHS subproblem.
   * this is dfs(l, i - 1) + dfs(i + 1, r), which is the maximum we can get for
   * popping [l, i - 1] and [i + 1, r]. The left and right subproblem / states
   * don't affect each other, because ith index is popped last (always creating
   * a wall). the ith index is never popped before all of the balloons in the
   * left and right subproblem are popped.
   *
   * Think about the structure of the sub-problem and this would make sense
   * */
public:
  int maxCoins(std::vector<int> &nums) {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    std::vector<std::vector<int>> dp(nums.size(),
                                     std::vector<int>(nums.size(), -1));

    return dfs(1, nums.size() - 2, nums, dp);
  }

private:
  int dfs(int l, int r, std::vector<int> &nums,
          std::vector<std::vector<int>> &dp) {
    if (l > r) {
      return 0;
    }
    if (dp[l][r] != -1) {
      return dp[l][r];
    }

    dp[l][r] = 0;
    int coins;
    for (int i = l; i < r + 1; ++i) {
      coins = nums[i] * nums[l - 1] * nums[r + 1];
      coins += dfs(l, i - 1, nums, dp) + dfs(i + 1, r, nums, dp);
      dp[l][r] = std::max(dp[l][r], coins);
    }
    return dp[l][r];
  }
};

/* Reflections:
 * Sometimes subproblems are easy to calculate, sometimes the subproblem is hard
 * to caculate. If you recognize a dp method, and a specific subproblem is
 * difficult to handle, it may be possible to consider a different subproblem /
 * different perspective Be careful of the operations on vectors which are O(N)
 */
