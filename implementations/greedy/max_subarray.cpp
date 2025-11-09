#include <stdio.h>
#include <vector>

class basic_solution {
  /* This is a basic non-optimal O(N^2) solution, where we find every possible
   * sum, saving some time using a "prefix sum" approach*/
public:
  int maxSubArray(std::vector<int> &nums) {
    int res = nums[0];

    for (int i = 0; i < nums.size(); ++i) {
      int tmp_sum = 0;
      for (int j = i; j < nums.size(); ++j) {
        tmp_sum += nums[j];
        res = std::max(tmp_sum, res);
      }
    }

    return res;
  }
};

class greedy_solution_optimal {
public:
  /* Idea: Greedy / intuitive approach. We keep adding a number. If a new number
   * causes our curr_sum to become negative, it makes sense to not use the
   * negative sum and start new. As we add new numbers, we make sure to keep
   * track of the largest global sum */
  int maxSubArray(std::vector<int> &nums) {
    int res = nums[0];
    int curr_sum = 0;

    for (int i = 0; i < nums.size(); ++i) {
      if (curr_sum < 0) {
        curr_sum = 0;
      }
      curr_sum += nums[i];
      res = std::max(res, curr_sum);
    }

    return res;
  }
};

/* If a problem seems quite hard, try an intuitive / greedy approach and see if
 * it works. Be sure to verify your intuition with logic / proof techniques /
 * test cases tho! */
