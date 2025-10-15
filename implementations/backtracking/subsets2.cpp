#include <stdio.h>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
    std::vector<std::vector<int>> res;
    std::vector<int> subset;

    std::sort(nums.begin(), nums.end());
    dfs(nums, res, subset, 0);

    return res;
  }

private:
  void dfs(std::vector<int> &nums, std::vector<std::vector<int>> &res,
           std::vector<int> &subset, int index) {
    if (index == nums.size()) {
      res.push_back(subset);
      return;
    }

    subset.push_back(nums[index]);
    dfs(nums, res, subset, index + 1);

    subset.pop_back();
    int i = index;
    while (i < nums.size() - 1 && nums[i] == nums[i + 1]) {
      i++;
    }

    dfs(nums, res, subset, i + 1);
  }
};

/* The important step is determining which part of the decision tree should be
 * pruned / ignored. In this case, the key is skipping over duplicates right
 * before we run recursion on subsets without the number */


/* Define variables properly so you don't pass in parameters you don't intend to pass... */
