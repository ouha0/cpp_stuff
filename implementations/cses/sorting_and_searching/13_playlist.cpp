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

/* Idea; we iterate through the vector, and we always want to be able to
 * calculate the max length quickly. This means saving the last valid left index
 * we can. We can do this by maintaining a hashmap mapping its value to its last
 * seen index. We iterate through the array, if the new value is not seen, we
 * add it to the hashmap, and save the current longest length. If it has been
 * seen, we update the left value to the last seen index + 1 (this is the
 * furthest we can extend to the left)*/
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::unordered_map<int, int> last_seen_index;
  last_seen_index.reserve(n);

  int tmp;
  int res = 0;
  int l = 0;
  for (int r = 0; r < n; ++r) {
    std::cin >> tmp;

    if (last_seen_index.count(tmp) && last_seen_index[tmp] >= l) {
      l = last_seen_index[tmp] + 1;
    }

    last_seen_index[tmp] = r;
    res = std::max(res, r - l + 1);
  }

  std::cout << res << "\n";

  return 0;
}

/* Bugs: Using a hashset was the wrong logical idea. Just consider 1213456. It
 * misses the 2. In addition, a value only becomes problematic if it has been
 * seen before AND it is in the current window we are constructing
 * */
