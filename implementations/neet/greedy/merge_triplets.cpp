#include <stdio.h>
#include <unordered_set>
#include <vector>

/* Idea: for each triplet, we can either merge it or do nothing. For problematic
 * triplets, we can't merge it so we ignore it. Suppose all other triplets are
 * not problematic. Note that any triplets we merge will always be greater than
 * the current and less than the target. Each time we merge, we will either be
 * the same, or be closer to the target */

// Or we can filter all valid triplets, and iterate through all valid triplets,
// and the numbers they hold and determine whether we find all targets
class Solution {
public:
  bool mergeTriplets(std::vector<std::vector<int>> &triplets,
                     std::vector<int> &target) {
    std::vector<int> start = {0, 0, 0};
    for (const auto &trip : triplets) {
      if (trip[0] <= target[0] && trip[1] <= target[1] &&
          trip[2] <= target[2]) {
        start[0] = std::max(start[0], trip[0]);
        start[1] = std::max(start[1], trip[1]);
        start[2] = std::max(start[2], trip[2]);
      }
    }

    return (start == target);
  }
};

class optimal_solution {
public:
  bool mergeTriplets(std::vector<std::vector<int>> &triplets,
                     std::vector<int> &target) {
    std::unordered_set<int> good;
    for (const auto &t : triplets) {
      if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2]) {
        continue;
      }
      for (int i = 0; i < t.size(); ++i) {
        if (t[i] == target[i]) {
          // Inserts the index of the target that can be satisfied
          good.insert(i);
        }
      }
    }

    return (good.size() == 3);
  }
};
