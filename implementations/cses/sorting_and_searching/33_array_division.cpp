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

/* Doing binary search on the max sum seems the most intuitive solution; may
 * time out and be slow howerver. It would be O(numbers range) * LOG(N), which
 * actually seems OK ?*/

/* Binary search logic:
 * find mid point, get current arrays left (= k) temporary variable, set count =
 * 0, keep adding elements until we go past mid; if we go past mid, set count =
 * current element and decrement arrays remaining
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }

  ll l = 0;
  ll r = 1e18l;

  while (l <= r) {
    ll mid = l + (r - l) / 2;

    int arr_remaining = k;
    ll count = 0;

    for (int i = 0; i < n; ++i) {
      count += nums[i];

      if (count > mid) {
        count = nums[i];
        arr_remaining--;

        if (nums[i] > mid || arr_remaining == 0) {
          arr_remaining = 0;
          break;
        }
      }
    }

    if (arr_remaining == 0) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  std::cout << l << "\n";

  return 0;
}
