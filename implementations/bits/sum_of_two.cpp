#include <cstdint>
#include <stdio.h>

class Solution {
public:
  /* This question works similarly to how we add integers, we add bits, and if
   * both are ones, we perform a carry.
   * While a or b non zero, we calculate the last bit, save a carry if
   * necessary, and perform bitwise OR left shift operation with the res */
  // Intuition here, is transforming a and b into a' + b' until their sum
  // doesn't result in carries
  int getSum(int a, int b) {
    while (b != 0) {
      int tmp_carry = (a & b) << 1;
      a = a ^ b;
      b = tmp_carry;
    }

    return a;
  }
};
