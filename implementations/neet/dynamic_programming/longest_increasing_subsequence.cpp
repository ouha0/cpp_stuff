#include <stdio.h>
#include <vector>

class Solution {
public:
  /* dynamic programming method; construct dp array, where dp[i] is the longest
   * subsequence using num[i] in the susbequence. Finally, do a linear search of
   * the dp array */
  int lengthOfLIS(std::vector<int> &nums) {
    std::vector<int> dp(nums.size(), 1); //

    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          dp[i] = std::max(dp[j] + 1, dp[i]);
        }
      }
    }

    int ans = 0;
    for (int i = 0; i < dp.size(); ++i) {
      ans = std::max(ans, dp[i]);
    }
    return ans;
  }
};
// There is a more optimal solution for this involving binary and dynamic
// programming

class Solution2 {
public:
  /* Iterate through each string, filling out dp array */
  int longestCommonSubsequence(std::string text1, std::string text2) {
    std::vector<std::vector<int>> dp(text1.size() + 1,
                                     std::vector<int>(text2.size() + 1, 0));
    for (int i = 1; i < text1.size() + 1; ++i) {
      for (int j = 1; j < text2.size() + 1; ++j) {
        if (text1[i - 1] == text2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[text1.size()][text2.size()];
  }
};
/* Note that it is common to make the vector size dp size + 1 to avoid off by
 * one errors. Can instead initialize to zero to avoid logical errors */

/*In this context, notice the dynamic programming. Became hesitant because the
 * best solution I thought of was O(N^2). Sometimes, even if you think your
 * solution is slow, think it through anyways; it may help you gain insight into
 * more efficient solutions
 *
 * The key for dynamic programming questions is determining what the optimal
 * substructure is
 *
 * */
