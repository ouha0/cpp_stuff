#include <stdio.h>
#include <vector>

/*
You are given an integer array nums.
Return the bitwise OR of all even numbers in the array.
If there are no even numbers in nums, return 0.

1 <= nums.length <= 100
1 <= nums[i] <= 100
 * */

class Solution {
public:
  int evenNumberBitwiseORs(std::vector<int> nums) {
    /* For each bit, check if number is even, check bitwiseor, modify respective
     * bit
     *
     * Key idea: by iterating through each  bit, we can skip bits all numbers
     * for the current bit that are already set to 1.
     *
     * May not be cache friendly though, because we iterate through one bit of
     * each number one at a time, rather going through all bits of one number
     * all at once.
     * */
    int res = 0;
    for (int i = 0; i <= 6; ++i) {
      for (const int &num : nums) {
        if ((~num & 1) & ((num >> i) & 1)) {
          res |= (1 << i);
          break;
        }
      }
    }
    return res;
  }
};

class Solution2 {
public:
  int evenNumberBitwiseORs(std::vector<int> nums) {
    /* For each number, if even, apply bitwiseor to 0(the identity)*/
    int res = 0;

    for (const int &num : nums) {
      if ((num % 2 == 0)) {
        res |= num;
      }
    }
    return res;
  }
};
