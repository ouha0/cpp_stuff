#include <algorithm>
#include <stdio.h>
#include <vector>

class Solution {
public:
  /*
   * Dynamic programming; want two dp arrays, from 0, n - 1 index and 1, n
   * index. For each element, we compare with two elements and three elements
   * before it. So we may need padding. Construct the dp array.
   * Ans should be the max of the last two of each of the two arrays.
   *
   *
   * Alternative implementation; note that we only want the maximum rob amount,
   * which at every state, only requires the two states. So we can discard lots
   * of useless information we previously calculated
   * */
  int rob(std::vector<int> &nums) {
    if (nums.empty()) {
      return 0;
    }

    return std::max({nums[0], max_rob(nums.begin(), nums.end() - 1),
                     max_rob(nums.begin() + 1, nums.end())});
  }

private:
  int max_rob(std::vector<int>::iterator start,
              std::vector<int>::iterator end_exclusive) {
    int rob1 = 0;
    int rob2 = 0;
    int res = 0;

    for (auto it = start; it != end_exclusive; ++it) {
      res = std::max(rob1 + *it, rob2);
      rob1 = rob2;
      rob2 = res;
    }
    return res;
  }
};

/* Key idea; dyanamic programming of states. We notice that the states are
 * dependent on whether the first house is robbed, so we can split the
 * transitions in the very beginning, one path for robbing house 1 and path for
 * not robbing house 1.*/
