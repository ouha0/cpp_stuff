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

/* Idea: Try to use as least towers as we can. When a new cube comes, if its
 * larger than everything, start a new tower, otherwise add the cube to the one
 * that has the smallest absolute difference?
 * If you could place a cube on another cube, you would never start a new tower.
 * If you do, all pieces you can put on the new tower, you could have stacked on
 * the older tower. It's either equal or worse off.
 * Where do u choose to stack the cube? The one with the closest absolute
 * difference? You would always choose the smaller tower to put it on. Putting
 * it on the larger tower puts the tower at a disadvantage
 * */

// Cache friendly implementation
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::vector<int> towers;
  towers.reserve(n);

  int tmp;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;

    auto it = std::upper_bound(towers.begin(), towers.end(), tmp);
    if (it == towers.end()) {
      towers.push_back(tmp);
    } else {
      *it = tmp;
    }
  }

  std::cout << towers.size() << "\n";

  return 0;
}

/* Because of the way we insert elements into the array. The array is always
 * sorted. If the input is too large, we add to the end. If the input is within
 * the range, we find the first element that is larger than the input, and we
 * replace the the element with the input. The element before and after smaller
 * and larger respectively. And all non-neighbours maintain the order */

/* Note that a keys in a set are unique. If u want non-unique keys, you must use
 * multiset
 * Note that we don't need to iterate over a set / multiset to find an element
 * (O(N)) There are in-built methods like upper_bound and lowerbound which is
 * essentially binary search (O(LOGN)) since set/multiset are balanced binary
 * search trees
 * */

/*
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::multiset<int> towers;
  int tmp;
  for (int c = 0; c < n; ++c) {
    std::cin >> tmp;

    int max_height = towers.empty() ? -1 : *towers.rbegin();

    if (tmp >= max_height) {
      towers.insert(tmp);
    } else {
      auto it = towers.upper_bound(tmp);
      towers.erase(it);
      towers.insert(tmp);
    }
  }
  std::cout << towers.size() << "\n";

  return 0;
}
*/
