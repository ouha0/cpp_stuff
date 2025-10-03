#include <iostream>
#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Idea is to use a two pointer approach; one from the left, one from the
   * right. It stops when it reaches a "peak". Two possible types of peaks
   * include same number same index and same number, index differs by 1. All
   * other conditions, the result is - 1. For same number same index, there are
   * two possibilities of lsum and rsum. For index difference by 1, there is
   * only one possibility of lsum and rsum. Note that the midpoint is not added
   * until the end */
  long long splitArray(std::vector<int> &nums) {
    long long res = -1;
    int l = 0;
    int r = nums.size() - 1;

    long long l_sum = 0;
    while (l < nums.size() - 1 && nums[l] < nums[l + 1]) {
      l_sum += nums[l];
      l++;
    }

    long long r_sum = 0;
    while (r > 0 && nums[r - 1] > nums[r]) {
      r_sum += nums[r];
      r--;
    }

    if (l == r) {
      long long option1 = std::abs((l_sum + nums[l]) - r_sum);
      long long option2 = std::abs(l_sum - (r_sum + nums[l]));
      res = std::min(option1, option2);

    } else if (nums[l] == nums[r] && r - l == 1) {
      res = std::abs(r_sum - l_sum);
    }
    return res;
  }
};

int main() {
  Solution s;
  std::vector<int> test = {1, 2, 4, 3};

  long long res = s.splitArray(test);
  std::cout << res << std::endl;

  std::vector<int> test2 = {3, 1, 2};
  std::cout << s.splitArray(test2) << std::endl;

  std::vector<int> test3 = {1, 2, 5};
  std::cout << s.splitArray(test3) << std::endl;

  std::vector<int> test4 = {5, 2, 1};
  std::cout << s.splitArray(test4) << std::endl;

  return 0;
}
