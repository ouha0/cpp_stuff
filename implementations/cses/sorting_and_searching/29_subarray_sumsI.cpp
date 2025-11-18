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

/* Idea:
 * Double pointer approach. If current sum too small, increase right pointer,
 * if current sum too large, increase left pointer, if theres a match, add to
 * count. Keep adding elements until the pointers reach the boundary. l < n
 * */

// Note that two pointer approach only works since input are all positive.
// too small guarentees we can add, and too large, means we can reduce
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, x;
  std::cin >> n >> x;

  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }

  int res = 0;

  int l = 0;
  int r = 0;

  ll curr_sum = 0;

  for (int r = 0; r < n; ++r) {
    curr_sum += nums[r];

    while (curr_sum > x) {
      curr_sum -= nums[l];
      l++;
    }

    if (curr_sum == x) {
      res++;
    }
  }

  std::cout << res << "\n";
  return 0;
}

/* Key: Clarity of thought is important. What to do first, what to do next.
 * i.e. we can expand and then shrink if too large. We can always just add
 * first, and then shrink as much as we need to, rather than look at curr sum
 * and shrink if too large, and expand if too small.
 *
 *
 * Be careful with boundary conditions. If your code is messy,
 * it probably means that you logic isn't as clear as it could be...
 * Rather than using a while loop, shrinking l and r based on condition
 * we can use a for loop to iterate, and shrink the left side when our curr sum
 * gets too large...*/
