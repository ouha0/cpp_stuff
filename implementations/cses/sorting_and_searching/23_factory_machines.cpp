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

/* Do binary search on the time interval, to see the lowest time required to
 * make t products. Note the very large numbers which may cause integer
 * overflow; important to use long long.
 *
 * Sometimes, using an answers variable inside the binary search makes the logic
 * easier to understand
 * */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, t;
  std::cin >> n >> t;

  std::vector<ll> machine_time(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> machine_time[i];
  }

  ll l = 0;
  ll r = 1e18;

  while (l <= r) {
    ll time = l + (r - l) / 2;

    ll products = 0;
    for (int i = 0; i < n; ++i) {
      products += (time / machine_time[i]);
      if (products >= t) {
        break;
      }
    }

    if (products < t) {
      l = time + 1;
    } else {
      r = time - 1;
    }
  }

  std::cout << l << "\n";

  return 0;
}

/* Key ideas:
 * Be careful with the overflowing; use long long. Note that it can be it takes
 * 10^9 time to get one product and we need 10^9 products -> overflow
 *
 * Realise that if we already make >= products than required, we know that we
 * are overestimating, and we can end the sum earlier
 *
 * Be careful with the edge casees. Consider l == r == 8 and our target is 8. r
 * is updated to 7, and we end the while loop. we output l which is the answer
 *
 * we are shrinking the solution space of "minimum time" by half each time
 *
 * */
