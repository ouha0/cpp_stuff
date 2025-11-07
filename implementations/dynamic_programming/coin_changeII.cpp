#include <stdio.h>
#include <vector>

class Solution {
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
