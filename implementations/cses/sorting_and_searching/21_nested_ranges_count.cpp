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

/* Skipping this question for now, since this is a more advanced data
 * structure*/

/* This question is quite hard, seems to require segment trees / advanced data
 * structures for an optimal solution. Since inputs are quite large, may need to
 * do compression (mapping elements) first.
 * High level approach (ignoring compresssion) is sorting the ranges first.
 * Iterate across the sorted list, build the tree as we go and query the tree
 * for number of instances that satisfy the current dimension. We only need to
 * compare about one dimension of the range, since previously added ranges have
 * a smaller left boundary (so we can ignore the left boundary condition for
 * "contains me". All elements in the existing tree have a left boundary
 * condition that is satisfying "contains me", we only need to work out the
 * frequency of the right boundary)
 *
 * We can iterate the sorting array backwards to work out whether I "contain
 * someone else"
 * */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  return 0;
}
