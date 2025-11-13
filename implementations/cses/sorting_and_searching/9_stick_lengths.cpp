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
 * of the absolute differences */
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
