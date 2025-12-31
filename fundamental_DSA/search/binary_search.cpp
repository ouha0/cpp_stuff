#include <stdio.h>
#include <vector>

/* Basic binary search. Have a left and right pointer, where target will lie in
 * between, due to sorted property of the vector. Find the middle point. If
 * target is less than the mid point, look to the left. If target is larger than
 * mid point, then look to the right */

int binary_search(int l, int r, std::vector<int> &nums, int target) {

  while (l <= r) {
    int m = l + (r - l) / 2;
    if (nums[m] == target) {
      return m;

      // The number found was less than what I wanted to find
    } else if (nums[m] < target) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }

  return -1;
}
