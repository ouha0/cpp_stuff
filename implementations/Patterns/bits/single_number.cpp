#include <stdio.h>
#include <vector>

class Solution {
public:
  int singleNumber(std::vector<int> &nums) {
    int start = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
      start = start ^ nums[i];
    }
    return start;
  }
};
/* Note that the order of bitwiseor doesn't matter; commutative
 * the bitwise or symbol is ^
 * */
