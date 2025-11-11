#include <stdio.h>
#include <vector>

/* Idea: brute foce, dp solution going backwards, or greedy solution to find out
 * how far we can go each time */
class Solution {
  /* Greedy solution idea: Each time, we find the set of destinations one jump
   * can get us. We stop when we are able to jump to / past the last index */
public:
  int jump(std::vector<int> &nums) {
    int l = 0;
    int r = 0;
    int res = 0;

    while (l <= r && r < nums.size() - 1) {
      int farthest = 0;
      for (int i = l; i < r + 1; ++i) {
        farthest = std::max(farthest, i + nums[i]);
      }
      l = r + 1;
      r = farthest;
      res++;
    }

    return (r >= nums.size() - 1) ? res : -1;
  }
};

/* Be careful not to iterate over variables that you are changing while u
 * iterate... */
