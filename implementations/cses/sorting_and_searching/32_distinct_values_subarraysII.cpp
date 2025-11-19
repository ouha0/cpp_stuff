#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using ll = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9;

/* Brainstorm / Initial ideas: O(N^2) is probably too slow, we don't want to do
 * this. Using a prefix sum also doesn't work, because we don't know the exact
 * values of two subarrays that are the same. Additionally, having a hashmap to
 * store all indices of a key is very expensive, not the right idea.
 * */

/* Key is using a greedy approach. We try to keep the left pointer as much left
 * as possible, and only move it forward when we have to. Note that if l works
 * for r_large, it will work for r_small (since this is a smaller range)
 * */

/* Fix l = 0. Iterate r from 0 to n. Insert nums[r] into hashmap frequency.
 * while (condition not satisfied), keep moving left pointer, and decrement
 * count from frequency map
 * */

/* if (r - l) range satisfies the condition? How many subarrays can we add?
 * We add all possible subarrays that contain r.
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> nums(n);
  std::map<int, int> freq_map;

  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }

  int l = 0;
  ll res = 0;

  for (int r = 0; r < n; ++r) {
    freq_map[nums[r]]++;

    while (freq_map.size() > k) {
      freq_map[nums[l]]--;

      if (freq_map[nums[l]] == 0) {
        freq_map.erase(nums[l]);
      }

      l++;
    }
    res += r - l + 1;
  }

  std::cout << res << "\n";

  return 0;
}

/* Read the question; This question says at most k distinct values, meaning that
 * the subarray can have 1, ... , k - 1 distinct values. Initially interpreted
 * in the wrong way; does not mean the max frequency count of some key of the
 * subarray < k*/
