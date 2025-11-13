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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  ll res = std::numeric_limits<int>::min();
  ll curr = 0;

  for (int i = 0; i < n; ++i) {
    int tmp;
    std::cin >> tmp;

    curr += tmp;
    res = std::max(res, curr);

    if (curr < 0) {
      curr = 0;
    }
  }

  std::cout << res << "\n";

  return 0;
}
