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

  std::vector<int> val(n + 1);

  int tmp;
  for (int i = 1; i <= n; ++i) {
    std::cin >> tmp;
    val[i] = tmp;
  }

  std::vector<int> pos(n + 1);
  for (int i = 1; i <= n; ++i) {
    pos[val[i]] = i;
  }

  int rounds = 1;
  for (int i = 2; i <= n; ++i) {
    if (pos[i - 1] > pos[i]) {
      rounds++;
    }
  }

  int a, b;
  int val_a, val_b;

  auto is_broken = [&](const int x) {
    if (x <= 1 || x > n) {
      return 0;
    }

    if (pos[x - 1] > pos[x]) {
      return 1;
    }

    return 0;
  };

  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    val_a = val[a];
    val_b = val[b];

    std::set<int> neighbours = {val_a, val_a + 1, val_b, val_b + 1};

    for (const int &nei : neighbours) {
      rounds -= is_broken(nei);
    }

    std::swap(val[a], val[b]);
    pos[val_a] = b;
    pos[val_b] = a;

    for (const int &nei : neighbours) {
      rounds += is_broken(nei);
    }

    std::cout << rounds << "\n";
  }

  return 0;
}

/* This question is quite hard. The idea is to use two arrays, one that stores
 * the initial values of the array in order, and another array that stores the
 * indices of the values array (positions vector). The idea for the solution
 * involes comparing the neighbouring values with the neighbouring indices.
 * The key insight for this problem is that we invert the affects of the
 * neighbouring values of the two values to be stopped, so that their breakpoint
 * / ordering temporarily has no affect. Since they now have no affect, we can
 * comforable swap them and update our two vectors. Once we do this, we
 * recalculate the effect of the neighbours (calculate the brekapoints and add
 * the effect back in)
 * */

/* Previous bugs:
 * don't swap temporary variables... a swap basically swaps the address
 * elements... Note that set stores unique elements in order. An array stores
 * elements contiguously on stack, but it is not unique.
 * Iterating over a hashset is slower than iterating over a set, since a hashset
 * is basically lots of buckets, where most are empty Iterating over this means
 * also iterating over lots of empty buckets
 * */
