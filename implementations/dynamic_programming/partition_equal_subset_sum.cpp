#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Key idea: we want to use each element once, and find all reachable states.
   * We return true if the state we want to reach is reachable */
  bool canPartition(std::vector<int> &nums) {
    int half_sum = 0;
    for (const int &n : nums) {
      half_sum += n;
    }
    if (half_sum & 1) {
      return false;
    } else {
      half_sum /= 2;
    }

    std::vector<int> dp(half_sum + 1, 0);
    dp[0] = 1;

    for (const int &n : nums) {
      for (int i = half_sum; i >= n; --i) {
        dp[i] = dp[i] || dp[i - n];
      }
    }

    return static_cast<bool>(dp[half_sum]);
  }
};

/* Note that the state we want is half the total sum of all numbers. Knowing
 * this, we can ignore all odd numbers. Then we can construct a dp array, to
 * find all possible numbers we are able to reach. As usual, be careful of
 * boundary conditions. Note that we need to iterate backwards, otherwise we use
 * variables that we just modified in the current iteration which is wrong
 *
 * As usual: Try solving the problem by hand first. Find information that can be
 * reused (think in terms of state transitions). Compress the problem and only
 * keep the relevant information. Be careful of boundary conditions. Consider
 * whether a continuously updated temporary variable is sufficient, or we need a
 * dp table
 * */
