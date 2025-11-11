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
    state_check[nums1] = true;

    while (!q.empty()) {
      auto [curr, d] = q.front();
      q.pop();

      if (same_vector(curr, nums2)) {
        return d;
      }

      generate_states(curr, d);
    }

    assert(false);
    return -1;
  }
  /* Function that generates all direct children states, adds it to the queue if
   * it isn't a duplicate state*/
  void generate_states(std::vector<int> &nums, int d) {
    for (int l = 0; l < nums.size(); ++l) {
      for (int r = l; r < nums.size(); ++r) {
        std::vector<int> sub_arr(nums.begin() + l, nums.begin() + r + 1);
        std::vector<int> remaining;
        remaining.insert(remaining.end(), nums.begin(), nums.begin() + l);
        remaining.insert(remaining.end(), nums.begin() + r + 1, nums.end());

        for (int i = 0; i < remaining.size() + 1; ++i) {
          std::vector<int> tmp = remaining;
          tmp.insert(tmp.begin() + i, sub_arr.begin(), sub_arr.end());

          if (state_check[tmp] == true) {
            continue;
          } else {
            state_check[tmp] = true;
            q.push(std::pair(std::move(tmp), d + 1));
          }
        }
      }
    }
  }

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

/* Reflections:
 * General bfs usually doesn't require you to iterate through each level. The
 * queue data structure naturally does all the work Be careful not to iterate
 * through a variable that is changing states. If you have to do this, save the
 * variable temporarily before iterating.
 *
 * when constructing subarrays, note that () represents [), where its inclusive,
 * exclusive; so remember the + 1 for exclusive When you insert into an array at
 * an iterator, it inserts right before the iterator. This means you can insert
 * at vector.end()
 *
 * */
