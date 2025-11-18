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

/* Idea: both people can always try to choose books so that they don't interfere
 * with each other. They only interfere with each other, when there is a single
 * book, that takes longer to read than all other books combined. In this case,
 * where there is a dominant book, one person reads the dominant book, while the
 * other personr reads all other books. Then the other person reads the dominant
 * book so the time is 2 * dominant book.
 *
 * In the case where there is no dominant book, both people can read all books
 * without interferance
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;
  ll total_time = 0;
  ll max_single = 0;

  ll tmp;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    max_single = std::max(max_single, tmp);
    total_time += tmp;
  }

  if (2 * max_single > total_time) {
    std::cout << 2 * max_single << "\n";
  } else {
    std::cout << total_time << "\n";
  }

  return 0;
}

/* Greedy idea; there are two cases, one where one person has to wait
 * for the other person to finish. This happens when there is a dominant
 * book that takes more time all other books combined. This is a mathematical
 * problem rather than a simulation problem */
