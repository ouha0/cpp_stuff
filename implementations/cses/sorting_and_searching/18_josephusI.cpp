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

  int n;
  std::cin >> n;
  std::queue<int> q;

  for (int i = 1; i <= n; ++i) {
    q.push(i);
  }

  bool flag = false;
  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    if (!flag) {
      q.push(curr);
    } else {
      std::cout << curr << " ";
    }
    flag = !flag;
  }
  std::cout << "\n";

  return 0;
}
