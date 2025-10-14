#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Idea is backtracking. Each decision tree, add new element, explore that
   * path, backtrack and then explore the path without the element. The index
   * and the used vector is used to keep track of everything */
  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    std::vector<std::vector<int>> res;
    std::vector<int> used(nums.size(), 0);
    std::vector<int> curr_permutation;

    backtrack(nums, res, curr_permutation, used);

    return res;
  }

private:
  void backtrack(std::vector<int> &nums, std::vector<std::vector<int>> &res,
                 std::vector<int> &curr_permutation, std::vector<int> &used) {

    if (curr_permutation.size() == nums.size()) {
      res.push_back(curr_permutation);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (used[i] == 0) {
        curr_permutation.push_back(nums[i]);
        used[i] = 1;
        backtrack(nums, res, curr_permutation, used);

        curr_permutation.pop_back();
        used[i] = 0;
      }
    }
  }
};

/* Always work out the decision tree first. If you can't solve it by hand, you
 * can't code it... As usual, its important to run test cases after implementation */
