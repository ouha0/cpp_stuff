#include <stdio.h>
#include <vector>

class Solution {
public:
  /* This is the standard approach, but it is not necessarily the most efficient
   * Use backtracking method; each stage, we can include the number and move on
   * to next number, use the current number, and reuse it in the next iteration,
   * or not use the number */
  std::vector<std::vector<int>> combinationSum(std::vector<int> &nums,
                                               int target) {
    std::vector<std::vector<int>> res;
    std::vector<int> subset;

    dfs(nums, res, subset, 0, target, 0);

    return res;
  }

private:
  void dfs(std::vector<int> &nums, std::vector<std::vector<int>> &res,
           std::vector<int> &subset, int index, int target, int curr) {
    if (curr > target || index >= nums.size()) {
      return;
    } else if (curr == target) {
      res.push_back(subset);
      return;
    } else {
      subset.push_back(nums[index]);
      dfs(nums, res, subset, index, target, curr + nums[index]);
      // dfs(nums, res, subset, index + 1, target, curr + nums[index]);
      // Realise that this is redundant, since the previous code already
      // discovers that path of using a new index

      subset.pop_back();
      dfs(nums, res, subset, index + 1, target, curr);
    }
  }
};

class Efficient_Solution {
public:
  /* The idea to first sort the numbers array. This means that if a numbers
   * index is too large, we don't need to check the rest of the array in the
   * current iteration. If target, we push and we stop. If < target, for each
   * number until end of array, we can either include it or exclude it. Note
   * that it is from the current index to the end, not the start to the end of
   * the array. If we can do this, it would cause duplicates to occur */
  std::vector<std::vector<int>> combinationSum(std::vector<int> &nums,
                                               int target) {
    std::vector<std::vector<int>> res;
    std::vector<int> subset;
    std::sort(nums.begin(), nums.end()); // O(N LogN)

    dfs(nums, res, subset, 0, target); // O(2^(target - smallest value in nums))

    return res;
  }

private:
  void dfs(std::vector<int> &nums, std::vector<std::vector<int>> &res,
           std::vector<int> &subset, int index, int target) {
    if (target == 0) {
      res.push_back(subset);
      return;
    }

    for (int i = index; i < nums.size(); ++i) {
      /* Slightly optimised before if nums[i] is too large, then nums[j] for all
       * j larger than i will be ignored */
      if (nums[i] > target) {
        return;
      }

      subset.push_back(nums[i]);
      dfs(nums, res, subset, i, target - nums[i]);

      subset.pop_back();
    }
  }
};

/* This is for combination sum II question on neetcode */
class Solution_2 {
public:
  /* Idea: Backtracking. At each tree branch, we either include the current
   * number and explore the resulting branch or we exclude it. However, when we
   * exclude it, it is important to exclude all its duplicates. Then we stop at
   * the last duplicate (because our code runs on index + 1). This will
   * guarentee uniqueness of our solution. The next branch we explore will not
   * include the index we currently have and its duplicates */
  std::vector<std::vector<int>> combinationSum2(std::vector<int> &nums,
                                                int target) {
    std::vector<std::vector<int>> res;
    std::vector<int> subset;
    std::sort(nums.begin(), nums.end());

    backtrack(nums, res, subset, 0, target);

    return res;
  }

private:
  void backtrack(std::vector<int> &nums, std::vector<std::vector<int>> &res,
                 std::vector<int> &subset, int start_index, int target) {
    if (target == 0) {
      res.push_back(subset);
      return;
    }

    if (target < 0 || start_index == nums.size()) {
      return;
    }

    subset.push_back(nums[start_index]);
    backtrack(nums, res, subset, start_index + 1, target - nums[start_index]);

    subset.pop_back();
    int i = start_index;
    while (i < nums.size() - 1 && nums[i] == nums[i + 1]) {
      i++;
    }
    backtrack(nums, res, subset, i + 1, target);
  }
};

class Efficient_Solution_2 {
public:
  std::vector<std::vector<int>> combinationSum2(std::vector<int> &nums,
                                                int target) {
    std::vector<std::vector<int>> res;
    std::vector<int> subset;

    std::sort(nums.begin(), nums.end());
    dfs(nums, res, subset, 0, target);

    return res;
  }

private:
  void dfs(std::vector<int> &nums, std::vector<std::vector<int>> &res,
           std::vector<int> &subset, int index, int target) {
    if (target == 0) {
      res.push_back(subset);
      return;
    }

    for (int i = index; i < nums.size(); ++i) {
      if (nums[i] > target) {
        return;
      }

      if (i > index && nums[i] == nums[i - 1]) { // this is the key here
        continue;
      }

      subset.push_back(nums[i]);
      dfs(nums, res, subset, i + 1, target - nums[i]);
      subset.pop_back();
    }
  }
};
