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

/* The idea to this solution is greedy again... The key insight is that
 * realising that the numbers range from 1, ..., n. And picking numbers numbers
 * in whatever order doesn't matter, as long as we pick up as many numbers as we
 * can once we pick the number up (maybe...)
 *
 * We can start from picking up
 * the number one, since we always need one round to pick up the number one
 * anyway. Then, we attempt to pick up the number two. If the index of two is
 * before one, we can't it up in the same round, so we incremenet the total
 * round count. We don't worry about numbers afterwards, because even though we
 * can pick it up in round one, we can very much pick it up in the round where
 * we pick up two. Say the numbers are 2 1 3. We can pick up 3 in the round we
 * pick up one, but we can also pick it up in the round where we pick up 2*/
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::vector<int> numbers(n + 1);
  for (int i = 1; i <= n; ++i) {
    int tmp;
    std::cin >> tmp;
    numbers[tmp] = i;
  }

  int res = 1;
  for (int i = 1; i < n; ++i) {
    if (numbers[i + 1] < numbers[i]) {
      res++;
    }
  }
  std::cout << res << "\n";

  return 0;
}

/* Problem; didn't read the question properly. Note that we must pick the items
 * in  order, this is a fundamental rule of the problem.
 * when reading a question, keep a mental note of all important key points, and
 * run through the key points when you finish reading again...
 * */
