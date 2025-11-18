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

/* Random ideas:
 * Doing something very early has a very large reward. But doing something late
 * will always cause a loss. What if we do a task based on how long the task
 * will take. Given tasks that same the same duration, the order we to tasks
 * don't matter. It seems optimal to always do the fastests task; maximizing
 * reward, and minimizing loss */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> tasks(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> tasks[i].first;
    std::cin >> tasks[i].second;
  }

  std::sort(tasks.begin(), tasks.end());
  ll rew = 0;
  ll t = 0;

  for (int i = 0; i < n; ++i) {
    rew += tasks[i].second - (t + tasks[i].first);
    t += tasks[i].first;
  }

  std::cout << rew << "\n";

  return 0;
}

/* Key:
 * Noticing the greediness / main idea. Each time, we choose the action that
 * maximizes gain / minimizes loss; doing the target that requires the least
 * time is this. Doing this provides most gain for future tasks
 *
 * This problem is a mathematical problem, and is more clear when you write the
 * algebra out
 * */
