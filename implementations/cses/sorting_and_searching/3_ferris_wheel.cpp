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

/* We want use minimum gondolas as possible for all children.
 * Initial idea was to to use hashmaps, to find the weight we want for the
 * remaining spae of the gondola, but this doesn't work, since if the exact
 * weight can't be found, we need to iterate through all weights.
 *
 * Probably better to sort the weights, and use a double pointer, and try to
 * keep adding children in until we can't. The problem is how to guarentee we
 * are using as much space as possible
 *
 * */

/* Some test cases:
 * 10
 * 1, 1, 1, 3, 7, 8, 9, 10, 100, 105
 *
  10 15
  9 8 8 9 10 8 5 8 7 10
  3, 5, 7, 8, 8, 8, 8, 9, 9, 10
 *
 *
 * */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, x;
  std::cin >> n >> x;
  std::vector<int> weights(n);

  for (auto &w : weights) {
    std::cin >> w;
  }

  std::sort(weights.begin(), weights.end());

  int res = 0;
  int l = 0;
  int r = n - 1;
  while (l < r) {
    if (weights[r] > x) {
      continue;
    }

    if (weights[r] + weights[l] <= x) {
      res++;
      r--;
      l++;
    } else {
      res++;
      r--;
    }
  }

  if (l == r && weights[l] <= x) {
    res++;
  }

  std::cout << res << "\n";

  return 0;
}

/* Key takeaway, make sure to read the question properly and take note of
 * key information */
