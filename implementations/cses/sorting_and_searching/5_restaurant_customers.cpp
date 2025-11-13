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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  /*
  int n;
  std::cin >> n;
  std::vector<int> arrival(n);
  std::vector<int> leave(n);

  int a, l;
  for (int i = 0; i < n; ++i) {
    std::cin >> a >> l;
    arrival[i] = a;
    leave[i] = l;
  }

  std::sort(arrival.begin(), arrival.end());
  std::sort(leave.begin(), leave.end());

  int res = 0;
  int count = 0;
  int p_a = 0;
  int p_l = 0;

  while (p_a < n) {
    if (arrival[p_a] < leave[p_l]) {
      count++;
      res = std::max(res, count);
      p_a++;
    } else {
      count--;
      p_l++;
    }
  }
  std::cout << res << "\n";

  return 0;
  */

  // An alternative solution
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> events(n);
  int a, l;
  for (int i = 0; i < n; ++i) {
    std::cin >> a >> l;
    events.emplace_back(a, 1);
    events.emplace_back(l, -1);
  }

  std::sort(events.begin(), events.end(), [](const auto &a, const auto &b) {
    if (a.first != b.first) {
      return a.first < b.first;
    }

    return a.second > b.second;
  });
  int res = 0;
  int count = 0;

  for (const auto &[time, change] : events) {
    count += change;
    res = std::max(res, count);
  }
  std::cout << res << "\n";

  return 0;
}

/* Very much like an intervalas problem. We go through the key times,
 * and figure out whether at the key time, the number of people goes increases
 * or decreases by one.
 *
 * The bug here was that i forgt to initialise the pointer values to zero
 * */

/* The alternative method the same solution idea, but changes the formatting.
 * Store all key events into a vector, sort it, and iterate across. Increment /
 * decrement count depending on whether someone arrived or left  */
