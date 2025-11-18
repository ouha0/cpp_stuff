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

/* Idea: Saving a current minimum of everything already seen is too slow.
 * O(N^2) worst case. Need to think of an alternative. Use a monotonic stack...
 * By using a monotonic stack, we can get rid of useless elements (numbers
 * that are too large), allowing future elements to repeatedly consider them?
 * If i currently already have a reasonably small element, i don't need elements
 * that were larger than what i currently am from the past. Using the current
 * element is better than using the past element which was even larger (current
 * element is smaller and closer)
 *
 */

/* Idea using a stack: While stack is non empty, check top element, if smaller,
 * output it, push current element onto the stack, continue */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::stack<std::pair<int, int>> s;

  for (int i = 0; i < n; ++i) {
    int tmp;
    std::cin >> tmp;
    while (!s.empty() && s.top().first >= tmp) {
      s.pop();
    }

    if (s.empty()) {
      std::cout << 0 << " ";
    } else {
      std::cout << s.top().second + 1 << " ";
    }
    s.emplace(tmp, i);
  }
  std::cout << "\n";

  return 0;
}

/* Key:
 * Notice that this problem requires a stack for the optimal solution;
 * problems that habe keywords, nearest, first, next, greater, smaller, to the
 * left, to the right.
 * A stack generally keeps track of the most recent useful
 * element, and gets rid of useless elements along the way
 *
 * If as we iterate, using the current element means some other element
 * becomse useless, we can usually use a stack. If a new element breaks
 * the sort order, we can pop elements because they are "shadowed" or become
 * useless
 *
 * Maintain a monotonically (strictly) increasing stack. It always has the
 * closest largest element on the top. If an element is larger than current, it
 * will be popped. If it is smaller, it will remain, and be used in the output.
 * After this, the current element will be pushed into the stack
 * */
