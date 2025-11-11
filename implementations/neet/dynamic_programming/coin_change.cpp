#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Dynamic programming type of method. To get the a particular amount, it
   * would be the minimum required to get the amount - (each element of the
   * coins array). This would be recursion, however, for dp, we want a "memory"
   * of our already solved values */
  int coinChange(std::vector<int> &coins, int amount) {
    std::vector<int> dp(amount + 1, amount + 1);

    dp[0] = 0;

    for (int num = 1; num < amount + 1; ++num) {
      for (int coin : coins) {
        if (num - coin >= 0) {
          dp[num] = std::min(dp[num], dp[num - coin] + 1);
        }
      }
    }
    return dp[amount] > amount ? -1 : dp[amount];
  }
};

/* When you have intuition / an idea, always test it out with some simple test
 * cases. i.e. greedy method of largest -> smallest doesn't work for this case.
 * Designing the solution was important here like choosing how to deal with the
 * base case i.e. dp[0] = 0 in the very start
 */
