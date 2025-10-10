#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Start with empty array; each element can be used or not used. Loop through
   * the current elements vector of subsets, and add a new element which
   * contains the element */
  std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
    std::vector<std::vector<int>> res = {{}};

    for (const int &num : nums) {
      int n = res.size();
      for (int i = 0; i < n; ++i) {
        std::vector<int> tmp = res[i];
        tmp.push_back(num);
        res.push_back(tmp);
      }
    }

    return res;
  }
};

/* Remember: don't iterate over a variable that is being modified within the
 * iteration */
