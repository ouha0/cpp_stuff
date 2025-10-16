#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Key idea to the solution is backtracking. First sort the nums array to
   * easily prune the tree in future recursions. Base case is when at max depth,
   * save the subset into the result. Otherwise, consider the branch where we
   * include the number, and the branch we don't include the number. To avoid
   * duplicates, we skip until the next unique number (this avoids looking) at
   * the same branch */
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

class Solution_copy {
public:
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
    std::vector<std::vector<int>> res;
    std::vector<int> subset;

    std::sort(nums.begin(), nums.end());

    backtrack(nums, res, subset, 0);

    return res;
  }

private:
  void backtrack(std::vector<int> &nums, std::vector<std::vector<int>> &res,
                 std::vector<int> &subset, int index) {

    if (index == nums.size()) {
      res.push_back(subset);
      return;
    }

    subset.push_back(nums[index]);
    backtrack(nums, res, subset, index + 1);

    subset.pop_back();
    int i = index;
    while (i < nums.size() - 1 && nums[i] == nums[i + 1]) {
      i++;
    }
    backtrack(nums, res, subset, i + 1);
  }
};

class Solution_iterative {
public:
  /* This is an iterative solution. Try it out by hand. The idea is for each
   * number, add it to every element of the results vector. To avoid duplicates,
   * the idea here is to only add to the previous size of results. Note that
   * after we add elements to the results, the results vector = prev results +
   * new results. If we add the same element to the previous result, we will get
   * elements that are the same as the new result (since the element we add is
   * the same) */
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
    std::sort(nums.begin(), nums.end());

    std::vector<std::vector<int>> res = {{}};
    int start_index = 0;
    int curr_size = 0;

    for (int i = 0; i < nums.size(); ++i) {
      if (i > 0 && nums[i] == nums[i - 1]) {
        start_index = curr_size;
      } else {
        start_index = 0;
      }

      curr_size = res.size();

      for (int j = start_index; j < curr_size; ++j) {
        std::vector<int> cpy = res[j];
        cpy.push_back(nums[i]);
        res.push_back(std::move(cpy));
      }
    }

    return res;
  }
};

/* The important step is determining which part of the decision tree should be
 * pruned / ignored. In this case, the key is skipping over duplicates right
 * before we run recursion on subsets without the number */

/* Define variables properly so you don't pass in parameters you don't intend to
 * pass... When you use a variable, be careful whether u modified it or not. If
 * you need a variable, use it ASAP. If you don't need some variable, delete it
 * ASAP */
