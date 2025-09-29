#include <assert.h>
#include <map>
#include <queue>
#include <stdio.h>
#include <utility>
#include <vector>

class Solution {
public:
  int minSplitMerge(std::vector<int> &nums1, std::vector<int> &nums2) {
    /* Idea: BFS, which is not too expensive given the array size constraint
     * of 6. Start with initial array, find direct children states, add to queue
     * if non-existing This means that we need a queue saving current array and
     * current steps, as well as a data structure to quickly check whether the
     * potential state has already been searched
     * */
    q.push(std::make_pair(nums1, 0));

    while (!q.empty()) {
      for (int i = 0; i < q.size(); ++i) {
        auto [curr, d] = q.front();
        q.pop();

        if (same_vector(nums1, nums2)) {
          return d;
        }

        generate_states(curr, d);
      }
    }

    assert(false);
    return -1;
  }
  /* Function that generates all direct children states, adds it to the queue if
   * it isn't a duplicate state*/
  void generate_states(std::vector<int> &nums, int d) {}

  // Function that checks whether both vectors are the same
  int same_vector(std::vector<int> &nums1, std::vector<int> &nums2) {
    for (int i = 0; i < nums1.size(); ++i) {
      if (nums1[i] != nums2[i]) {
        return 0;
      }
    }

    return 1;
  }

private:
  std::queue<std::pair<std::vector<int>, int>> q;
  std::map<std::vector<int>, bool> state_check;
};
