#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Idea is dynamic promming */
  int maxProduct(std::vector<int> &nums) {

    int global_max = nums[0];
    int curr_max = nums[0];
    int curr_min = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
      int prev_max = curr_max;
      curr_max = std::max({curr_max * nums[i], nums[i], curr_min * nums[i]});
      curr_min = std::min({prev_max * nums[i], curr_min * nums[i], nums[i]});

      global_max = std::max(global_max, curr_max);
    }

    return global_max;
  }
};

/* Takeaway; not all dynamic programming questions require memory of all
 * previous states. In this case, knowing just two states is sufficient; the
 * curr_max subarray and curr_min subarray. Think through this question again
 * */
