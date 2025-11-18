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

/* Initial ideas / brainstorming: Sum(i, j) = prefix sum[j] - prefix sum [i - 1]
 * for j >= i. We want the sum = X. We can iterate through the array, calculate
 * prefix_sum [j], and query the number of occurances of prefix_sum[j] has
 * occured */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, x;
  std::cin >> n >> x;

  std::map<ll, int> sum_count;
  // sum_count.reserve(n);
  sum_count[0] = 1;

  ll curr_sum = 0;
  int tmp;
  ll res = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    curr_sum += tmp;

    if (sum_count.count(curr_sum - x) > 0) {
      res += sum_count[curr_sum - x];
    }
    sum_count[curr_sum]++;
  }

  std::cout << res << "\n";

  return 0;
}

/* Key insight: Think in terms of prefix sums, and explore the math and algebra
 * of this problem. It will make it more clear. Realise that subarrays can be
 * solved using subtraction of two prefix sums and using hashmaps / maps to
 * identify previous occurences of some sum. Note that the general hash function
 * may cause too many collisions for problems with a large N. Usually sufficient
 * going with std::map taking a O(NLogN) time */
