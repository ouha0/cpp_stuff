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

/* Idea: want to find the smallest sum you cannot create. First sort the
 * array, then perform a bfs, iterating as we add new coins. If the new coin
 * (smallest) we add + the smallest coin is greater than the missing value, we
 * can stop
 * However, this is too slow, there is probably another greedy method that is
 * faster. We start res = 1, and we iterate through the sorted coins list. Each
 * time, we construct the possible range the previous coins can be. We only need
 * one variable, which is the smallest unreachable sum (due to induction... ).
 * [it was proven that 0...smallest unreachable sum - 1] can be reached
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::vector<int> numbers(n);
  for (int i = 0; i < n; ++i) {
    int tmp;
    std::cin >> tmp;
    numbers[i] = tmp;
  }

  std::sort(numbers.begin(), numbers.end());
  ll res = 1;

  for (const int &coin : numbers) {
    if (coin > res) {
      break;
    }
    res += coin;
  }

  std::cout << res << "\n";

  return 0;
}

/* The idea was right, but working out which steps can be skipped when solving
 * the problem is important. Note that we can keep track of a variable
 * unreachable meaning that [0, ..., unreachable - 1] can all be reached. Adding
 * a single coin inside means that [0, ..., unreachable -1 + coin] can be
 * reached (new unreachable is unreachable + coin). This is like bfs,
 * but skipping the actual work, as by "inducation", we know all previous
 * numbers are reachable*/
