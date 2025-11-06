#include <cstdint>
#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Seems like using a hashset with O(N) space would be easiest. However,
   * bitwise xor is more efficient? Note that XOR is commutative. Suppose all
   * but one number exists. We can iterate through int i = 0 to n inclusive, and
   * do xor on this, and then iterate through each number of nums and do xor.
   * Since commutative, same numbers xor should be 0. And 0 xor with the missing
   * number is the missing number. (0 is the identity)*/
  int missingNumber(std::vector<int> &nums) {
    int n = nums.size() + 1;
    int res = 0;
    for (const int &num : nums) {
      res = num ^ res;
    }

    for (int i = 1; i < n; ++i) {
      res = res ^ i;
    }

    return res;
  }
};
