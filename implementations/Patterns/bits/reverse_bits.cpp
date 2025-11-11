#include <cstdint>
#include <stdio.h>

class Solution {
public:
  /* Idea here is for each bit, determine whether it is 1 or 0, using the bit
   * wise and. To save the result, we use bit wise or the result (to not change
   * previous bits) and shift the 1 bit 32 - i positions */
  uint32_t reverseBits(int n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; ++i) {
      uint32_t bit = (n >> i) & 1;
      res = res | (bit << (31 - i));
    }
    return res;
  }
};
