#include <iostream>
#include <stdio.h>
#include <unordered_set>
#include <vector>

class Solution {
public:
  /* Count number of distinct odd and even numbers.
   * resize is nums.size() - absolute difference
   * */

  int longestBalanced(std::vector<int> &nums) {
    int max = 0;
    for (int start = 0; start < nums.size(); ++start) {
      std::unordered_set<int> s;
      int distinct_odds;
      int distinct_evens;

      if (nums[start] & 1) {
        distinct_odds = 1;
        distinct_evens = 0;
      } else {
        distinct_odds = 0;
        distinct_evens = 1;
      }
      s.insert(nums[start]);

      for (int end = start + 1; end < nums.size(); ++end) {
        if (s.count(nums[end])) {
        } else {
          s.insert(nums[end]);
          (nums[end] & 1) ? (distinct_odds++) : (distinct_evens++);
        }

        if (distinct_evens == distinct_odds) {
          max = std::max(max, end - start + 1);
        }
      }
    }

    return max;
  }
};

int main() {
  Solution s;
  std::vector<int> test1 = {3, 2, 2, 5, 4};
  int res1 = s.longestBalanced(test1);

  std::vector<int> test2 = {2, 5, 4, 3};
  int res2 = s.longestBalanced(test2);

  std::cout << res1 << std::endl;
  std::cout << res2 << std::endl;

  return 0;
}
