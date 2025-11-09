#include <stdio.h>
#include <vector>

class dp_solution {
  /* Idea, we can do a dp solution by iterating backwards, or we can do a dfs of
   * every possible path and caching it */
public:
  bool canJump(std::vector<int> &nums) {
    std::vector<bool> dp(nums.size(), false);
    dp[nums.size() - 1] = true;

    for (int i = nums.size() - 2; i >= 0; --i) {
      int jump = nums[i];
      for (int j = 1; j <= jump; ++j) {
        if (i + j < nums.size() && dp[i + j]) {
          dp[i] = true;
          break;
        }
      }
    }
    return dp[0];
  }
};

class greedy_solution {
  /* The reason this greedy solution works, is because the jump length can be
   * length 1 to the max length */
public:
  bool canJump(std::vector<int> &nums) {
    int goal = nums.size() - 1;

    for (int i = nums.size() - 2; i >= 0; --i) {
      if (i + nums[i] >= goal) {
        goal = i;
      }
    }
    return (goal == 0);
  }
};
