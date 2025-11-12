
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

/* Idea: Use a set to store prices. This is a binary search tree (sorted).
 * For each person, we want to find the last price that is smaller than the
 * customer price
 * For each customer, we want to find the largest price that is less than
 * customer max price.
 * we can use prices.upper_bound which returns the iterator to the first
 * element that is larger.
 * this iterator could be valid, or go out of bounds.
 * if valid iterator; either first element or some other element. If first
 * element which is smallest is the first larger element, we return -1.
 * Otherwise, we can return *(it--)
 *
 * if invalid iterator which means the first larger element was not found.
 * if the size of the prices set is non empty, that means all elements are
 * smaller, we can return *(it--), the largest element
 * if size of the array set is empty, return -1
 *
 *
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::multiset<int> prices;
  int tmp;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    prices.insert(tmp);
  }

  int c_max_price;
  for (int i = 0; i < m; ++i) {
    std::cin >> c_max_price;

    auto it = prices.upper_bound(c_max_price);

    // First element is larger or prices mutliset is empty
    if (it == prices.begin()) {
      std::cout << -1 << "\n";
    } else {
      --it;
      std::cout << *it << "\n";
      prices.erase(it);
    }
  }

  return 0;
}

/* Key takeaways: Note that set is basically a binary search tree, but the keys
 * stored must be unique. To use non-unique keys, we need to use a multiset.
 *
 * Also, take note of the available functions that comes with using set and
 * multiset data structure.
 * Note that erase(key) removes all instances of the key for multiset
 * lowerbound finds the first element greater than or equal to x - O(LOGN)
 * upperbound finds the first element strictly greater than x - O(LOGN)
 *
 * */
