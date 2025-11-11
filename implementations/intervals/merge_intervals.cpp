#include <stdio.h>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>>
  merge(std::vector<std::vector<int>> &intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::vector<int>> res;

    for (const auto &range : intervals) {
      if (res.empty() || res.back()[1] < range[0]) {
        res.emplace_back(range);
      } else {
        res.back()[1] = std::max(res.back()[1], range[1]);
      }
    }

    return res;
  }
};
