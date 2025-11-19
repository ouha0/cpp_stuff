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

/* Brainstorm / Initial idea: Save input elements. Then iterate over i, j, where
 * i is start point, j is end point.
 * If some subarray is / is not divisible by n, it doesn' stop future subarrays
 * from satisfying that condition
 * */

/* The brute force idea causes a timeout, not fast enough. Consider using prefix
 * sums instead. What we want is Sum(i,j) = prefix(j) - prefix(i - 1) congruent
 * to 0 mod n. The idea here is we iterate, calculating the prefix sum, do a
 * quick query whether there is a prefix sum that satisfies the previous
 * condition. Increment by the frequency. Now save current prefix sum into the
 * frequency map*/
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::map<int, int> sum_frequency;
  sum_frequency[0] = 1;

  int tmp;
  ll curr_sum = 0;
  ll res = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    curr_sum = (curr_sum + tmp + n) % n;

    if (sum_frequency.count((curr_sum + n) % n)) {
      res += sum_frequency[(curr_sum + n) % n];
    }
    sum_frequency[(curr_sum + n) % n]++;
  }

  std::cout << res << "\n";

  return 0;
}

/* Key / Reflections:
 * For subarrays, a very common O(N) average or (O(NLOGN)) method is to use
 * prefix sums. This would generally require some math and algebra to work out.
 *
 * Be careful of integer overflow. Always consider the contraints and consider
 * the most extreme test cases
 * */
