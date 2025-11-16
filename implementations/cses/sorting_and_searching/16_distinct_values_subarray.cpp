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

/* Idea: Iterate through that vector, and use a hashmap to determine whether
 * the current value has been seen in the past.
 * If it hasn't been seen, and the last new value is at l, then we can create
 * curr - l + 1 subarrays. If it has been seen and the previous seen index is at
 * x, then we can create curr - x + 1 subarrays. (+1 is the subset itself)
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  int most_left = 0;
  std::unordered_map<int, int> value_index;
  value_index.reserve(n);

  int tmp;
  ll res = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;

    if (value_index.count(tmp)) {
      most_left = std::max(most_left, value_index[tmp] + 1);
      res += i - most_left + 1;
    } else {
      res += i - most_left + 1;
    }
    value_index[tmp] = i;
  }
  std::cout << res << "\n";

  return 0;
}

/* Bug: two errors, one was the potential overflow for res, another was a
 * logical error with "most left pointer", if there are 2 * 10^5 inputs with
 * everything being distinct. The number of subarrays would be at the maximum,
 * and would be larger than int
 * The other error was the updating of the most left pointer. Left pointer, once
 * it goes right, it should never be allowed to go back left
 * consider the example 1 2 3 2 1. Upon seeing the second 2, the most left will
 * be updated to index 2 (1 + 1). However, when we reach the second one, the
 * most left pointer, shouldn't be allowed to go back to index 1 (0 + 1); this
 * would cause double-counting
 * */
