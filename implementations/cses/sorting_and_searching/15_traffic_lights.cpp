#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include <assert.h>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using ll = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9;

// Review this question...

/* Idea, we use two containers; one to store the current path lengths in
 * descending order, one to store the current posts. We iterate through the
 * posts, insert it a range (either between posts, or posts or end point),
 * determine the initial distance, delete it from the current path lengths, and
 * add the two new path lengths to the container.
 *
 * For each post, try to find upper and lower limit, calcuate this distance,
 * delete from distance set
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int x, n;
  std::cin >> x >> n;

  std::multiset<int, std::greater<int>> dist = {x};
  std::set<int> pos = {0, x};

  int tmp;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;

    auto it_right = pos.upper_bound(tmp);
    auto it_left = std::prev(it_right);

    // auto it_left = it_right;
    // it_left--;

    int l = *it_left;
    int r = *it_right;

    auto it_dist = dist.find(r - l);
    assert(it_dist != dist.end());
    dist.erase(it_dist);

    dist.insert(r - tmp);
    dist.insert(tmp - l);

    pos.insert(tmp);

    std::cout << *dist.begin() << "\n";
  }

  return 0;
}

/* Bug: doing operations on the wrong array. Keep track of what different arrays
 * mean, and what the variable / code is actually doing. Cannot do set::iterator
 * it_left = it_right - 1, since elements in a set aren't stored contiguously.
 * This will cause a run time error. it-- and it++ will work tho
 * Note that std::lowerbound does not do what u expect it to do. It finds the
 * first element greater than or equal to the given input std::upper_bound finds
 * the first element that is greater than the given input std::prev gets the
 * iterator directly before what the input it was pointing to
 *
 * */
