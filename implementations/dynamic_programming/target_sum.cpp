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
