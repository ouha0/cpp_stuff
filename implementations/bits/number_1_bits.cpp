#include <stdio.h>

class Solution {
public:
  int hammingWeight(int n) {
    int count = 0;
    while (n > 0) {
      if (n & 1) {
        count++;
      }
      n = n >> 1;
    }
    return count;
  }
};

class altnerative_Solution {
public:
  int hammingWeight(int n) {

    int count = 0;
    while (n > 0) {
      // This operation borrows the rightmost 1 bit, and then makes all bits
      // after that become zero by design
      // i.e. 111000 & 110111 -> 110000. Each iteration gets rid of a single 1
      n = n & (n - 1);

      count++;
    }
    return count;
  }
};
