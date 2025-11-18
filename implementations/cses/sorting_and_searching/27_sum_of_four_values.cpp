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

/* If we follow the previous method, doing O(N^2) loop with a double pointer
 * approach, it would make time complexity O(N^3); we should consider something
 * faster. An idea is to use a hashmap storing previous sums, and there indices.
 * However, the probelm, is our previous sum must not interfere with the current
 * sum i.e. they must not use the same indices. This would depend on the order
 * of our iteration. We can iterate i from 0 to n, j from i + 1 to n, and each
 * time, look at a hashmap, for sums which include elements k and l of sums of
 * 0... i, and 0 ...i.
 * For each fixed i and j, after we finish the jth loop, we can add all the sums
 * arr[i] + arr[k] for k from 0 ... i. (we cannot go past i, otherwise,
 * k may interfere with future values of i and j)
 *
 *
 * */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, x;
  std::cin >> n >> x;

  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }

  std::unordered_map<int, std::pair<int, int>> sum_indices;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {

      int sum = nums[i] + nums[j];
      int target = x - sum;
      if (sum_indices.count(target)) {
        std::cout << i + 1 << " " << j + 1 << " "
                  << sum_indices[target].first + 1 << " "
                  << sum_indices[target].second + 1 << "\n";
        return 0;
      }
    }
    for (int k = 0; k < i; ++k) {
      sum_indices[nums[i] + nums[k]] = std::make_pair(i, k);
    }
  }

  std::cout << "IMPOSSIBLE" << "\n";

  return 0;
}

/* Key insight:
 * The previous method using double pointer doesn't work. We need to somehow
 * have quick access to previous sums we calculated. We can do this using a
 * hashmap. The key is in which order to we interate, and how do we store values
 * into the hashmap, so that the current iteration to find (target - sum[i] +
 * sum[j]) doesn't give us two numbers that involve the index i and j.
 *
 * Also, note that hashmap keys are unique. If we find a sum that already exists
 * in the hashmap, we just replace the indices. This doesn't matter, since we
 * only need one instance where the sum works. We don't need all instances where
 * we can create the sum.
 *
 * imagine we want to create 4 and we have 11111111. It doesn't matter which
 * pairs of one we use from the past; they will all be fine in this problem
 * */
