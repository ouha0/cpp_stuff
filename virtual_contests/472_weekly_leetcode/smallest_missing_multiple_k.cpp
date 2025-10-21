#include <iostream>
#include <stdio.h>
#include <vector>

class Solution {
public:
  int missingMultiple(std::vector<int> &nums, int k) {
    std::sort(nums.begin(), nums.end());

    int curr_lowest = k;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] < curr_lowest) {
        continue;
      } else if (nums[i] == curr_lowest) {
        curr_lowest += k;
      } else {
        return curr_lowest;
      }
    }

    return curr_lowest;
  }
};

int main() {
  std::vector<int> test1 = {8, 2, 3, 4, 6};
  int k1 = 2;
  Solution x;

  int res1 = x.missingMultiple(test1, k1);
  std::cout << res1 << std::endl;

  std::vector<int> test2 = {1, 4, 7, 10, 15};
  int k2 = 5;
  int res2 = x.missingMultiple(test2, k2);
  std::cout << res2 << std::endl;

  return 0;
}
