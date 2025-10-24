#include <iostream>
#include <stdio.h>
#include <vector>

class Solution {
public:
  int sumDivisibleByK(std::vector<int> &nums, int k) {
    int res = 0;
    std::unordered_map<int, int> freq_count;

    for (const int &num : nums) {
      freq_count[num]++;
    }

    for (const auto &pair : freq_count) {
      if (pair.second % k == 0) {
        res += (pair.first * pair.second);
      }
    }

    return res;
  }
};

int main() {
  Solution s;
  std::vector<int> nums = {1, 2, 2, 3, 3, 3, 3, 4};
  int k1 = 2;
  int test1 = s.sumDivisibleByK(nums, k1);
  std::cout << test1 << std::endl;

  return 0;
}
