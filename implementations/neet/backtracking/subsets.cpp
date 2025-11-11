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
        res.push_back(
            std::move(tmp)); // rvalue reference for tmp; can be deleted / used
      }
    }

    return res;
  }
};

/* Remember: don't iterate over a variable that is being modified within the
 * iteration */

class Solution_backtracking {
public:
  /* Key idea is to explore part of a decision tree, "backtrack" to previous
   * breakpoint, and explore a new part of the decision tree
   * This is like a dfs, which saves all leaf nodes
   * */
  std::vector<std::vector<int>> subsets(std::vector<int> &nums) {

    std::vector<std::vector<int>> res = {};
    std::vector<int> subset = {};

    dfs(0, nums, subset, res);

    return res;
  }

private:
  void dfs(int i, const std::vector<int> &nums, std::vector<int> &subset,
           std::vector<std::vector<int>> &res) {
    if (i >= nums.size()) {
      res.push_back(subset);
      return;
    }

    subset.push_back(nums[i]);
    dfs(i + 1, nums, subset, res);

    subset.pop_back();
    dfs(i + 1, nums, subset, res);
  }
};
