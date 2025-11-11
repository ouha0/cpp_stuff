#include <map>
#include <stdio.h>
#include <vector>

/* Again, there are many different solutions to this problem; general
 * recursive decision tree, recursive tree with caching, and pure
 * dynamic programming approach*/
class basic_dfs_solution {
public:
  int findTargetSumWays(std::vector<int> &nums, int target) {
    int index = 0;
    return dfs(nums, target, index, target);
  }

private:
  int dfs(std::vector<int> &nums, int curr_sum, int index, int target) {
    if (index == nums.size()) {
      return (curr_sum == target);
    }

    int res = 0;
    res += dfs(nums, curr_sum + nums[index], index + 1, target);
    res += dfs(nums, curr_sum - nums[index], index + 1, target);
    return res;
  }
};

class dfs_memoization {
public:
  int findTargetSumWays(std::vector<int> &nums, int target) {
    std::map<std::pair<int, int>, int> cache;

    return dfs(nums, 0, 0, target, cache);
  }

private:
  int dfs(std::vector<int> &nums, int curr_sum, int index, int target,
          std::map<std::pair<int, int>, int> &cache) {
    if (cache.count(std::make_pair(curr_sum, index))) {
      return cache[std::make_pair(curr_sum, index)];
    }

    if (index == nums.size()) {
      return target == curr_sum;
    }

    int res = dfs(nums, curr_sum + nums[index], index + 1, target, cache);
    res += dfs(nums, curr_sum - nums[index], index + 1, target, cache);

    cache[std::make_pair(curr_sum, index)] = res;
    return res;
  }
};

class optimized_dp_solution {
public:
  /* Optmized dp approach, where where the current state only depends on the
   * previous state. For every key, value in dp_prev, find if key + number
   * exists in dp_curr. if exists, add value count to it. Otherwise, create new
   * key + number, value pair using dp_prev value. */
  int findTargetSumWays(std::vector<int> &nums, int target) {
    std::unordered_map<int, int> dp_prev;
    dp_prev[0] = 1;

    for (const int &num : nums) {
      std::unordered_map<int, int> dp_curr;
      for (const auto &[key, value] : dp_prev) {
        // Not check is required, since if a key doesn't exists, the [] sets
        // them to 0 first before adding value
        dp_curr[key + num] += value;
        dp_curr[key - num] += value;
      }
      dp_prev = std::move(dp_curr);
    }

    // if target doesn't exist, it would create target, 0 key value pair and
    // return 0
    return dp_prev[target];
  }
};
