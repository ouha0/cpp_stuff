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

/* Idea is to find the median. Then iterate through the array and take the sum
 * of the absolute differences. What we want to find is a value d, s.t.
 * the sum of the absolute values is negative. We want to find d s.t. the
 * derivative goes from negative to positive. Since this is a sum of absolute
 * values, we can order the sticks first, and suppose d >= p_i or something. We
 * will find that d = the median of the sticks will give us the minimum we
 * want*/
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;
  std::vector<int> numbers(n);

  int tmp;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    numbers[i] = tmp;
  }

  std::sort(numbers.begin(), numbers.end());
  ll median = numbers[n / 2];
  ll res = 0;

  for (const int &n : numbers) {
    res += std::abs(static_cast<ll>(n) - median);
  }

  std::cout << res << "\n";

  return 0;
}
