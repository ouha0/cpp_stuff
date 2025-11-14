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

/* Similar to previous collecting numbers problem. First we store the input of n
 * + 1 size to easily identify index with value. Then we create a copy of this
 * array where the indices represent the number, and the value of the array
 * represents the inital index of the number. We count the number of rounds
 * for this initial array, then we figure out how "swap" operations affect
 * the number of rounds required.
 *
 * the total rounds is calculated via summing all the breakpoints, when the
 * number is larger but the indices of the smaller number is larger. To
 * calculate the breakpoints, we can remove the effect / rounds of the
 * breakpoints we are about to swap, and then do the swap, updating the
 * positions array, and the current number state, then add the affect of the
 * breakpoints back in.
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> initial_numbers(n + 1);
  int tmp;
  for (int i = 1; i <= n; ++i) {
    std::cin >> tmp;
    initial_numbers[i] = tmp;
  }

  std::vector<int> sorted_numbers(n + 1);
  for (int i = 1; i <= n; ++i) {
    sorted_numbers[initial_numbers[i]] = i;
  }

  int rounds = 1;
  for (int i = 1; i < n; ++i) {
    if (sorted_numbers[i] > sorted_numbers[i + 1]) {
      rounds++;
    }
  }

  int a, b;
  int val_a, val_b;

  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    val_a = initial_numbers[a];
    val_b = initial_numbers[b];

    std::cout << rounds << '\n';
  }

  return 0;
}
