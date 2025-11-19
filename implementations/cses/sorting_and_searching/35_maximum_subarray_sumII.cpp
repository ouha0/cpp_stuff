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

/* Initial idea: seems we can use prefix sums, and look for values in between
 * length of a and b. However, this is O(N * (b - a) )*/

/* Key: Prefix sum is the right idea, but we use a deque to store useful
 * previous prefix sums... We want sum(i, j) = p[j] - p[i - 1] for valid i - 1
 * ranges. This means that we need to minimise p[i - 1]. Where i is from j - a
 * to j - b. Note we use a deque because we can discard elements old elements by
 * popping front, and pop back. We pop the back if we have found a more more
 * recent prefix sum that is smaller than the previosu recent one. The front
 * will always have the smallest prefix sum, but we also need to check whether
 * the index is currently still in range
 *
 * i must be in range from j - b to j - a -> i - 1 must be in range from j - b -
 * 1 to j - a - 1. |i - j| <= b
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, a, b;
  std::cin >> n >> a >> b;

  ll res = 0;
  ll curr_sum = 0;
  std::deque<std::pair<ll, int>> dq;

  ll tmp;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    curr_sum += tmp;

    if (!dq.empty() && i > dq.front().second + b) {
      dq.pop_front();
    }

    while (!dq.empty() && dq.back().first >= curr_sum) {
      dq.pop_back();
    }
    dq.emplace_back(curr_sum, i);

    if (!dq.empty() && i >= dq.front().second + a) {
      res = std::max(res, curr_sum - dq.front().first);
    }
  }

  std::cout << res << "\n";

  return 0;
}

// This code doesn't work yet. note we can't add in undefined ranges before they
// are defined... The error was caused by, we only add valid elements into the
// deque i.e, prefix sums with size a...

/* Key insights:
 * Note the negative input -> may need to use prefix sum
 * We need previous arrays, within a specific distance away, that are useful.
 * i.e. if we have a recent prefix array that is very small, we don't need
 * something from more earlier on, since mathematically, our goal was to
 * minimize the P[i - 1]. Keeping useful prefix arrays in order can be done
 * using a deque (fifo)
 *
 * */
