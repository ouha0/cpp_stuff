#include <algorithm> // for std::sort, std::min/max
#include <cmath>     // for math functions
#include <iostream>
#include <numeric> // for std::iota, std::accumulate
#include <string>
#include <vector>

// Data Structures
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using ll = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9;

/* After reading the inputs, sort both the apartment size preference, and actual
 * apaprtment size. Try to match the customer apartment size preference with the
 * actualy apartment. And increment pointers accordingly. If an apartment is too
 * small for the customer with the smallest preference, we can ignore this
 * apartment for all future customers, since customer preferences are already
 * sorted. If an apartment is too large for a customer, we can ignore this
 * customer as it can no longer be matched with any apartments, since the
 * current apartment being matched is the smallest apartment there is. If we
 * match an apartment with a customer, it doesn't negatively reduce the number
 * of potential matches we can match in the future, since k is fixed. Leaving
 * the current apartment for the future customer doesm't do any good in
 * increasing the number of total matches */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<int> desired_size(n);
  std::vector<int> apart_size(m);

  for (auto &size : desired_size) {
    std::cin >> size;
  }

  for (auto &size : apart_size) {
    std::cin >> size;
  }

  std::sort(desired_size.begin(), desired_size.end());
  std::sort(apart_size.begin(), apart_size.end());

  int i = 0;
  int j = 0;
  int res = 0;

  while (i < desired_size.size() && j < apart_size.size()) {
    int apart = apart_size[j];
    int desired = desired_size[i];

    if (abs(apart - desired) <= k) {
      res++;
      i++;
      j++;
    } else if (apart < desired) {
      j++;
    } else {
      i++;
    }
  }

  std::cout << res << "\n";
  return 0;
}

/* takeaway: be careful with variable names, otherwise it is easy to mess things
 * up. */
