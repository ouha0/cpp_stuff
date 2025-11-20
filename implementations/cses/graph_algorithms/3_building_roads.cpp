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

/* Initial idea: Distances don't matter. It seems we want to join all
 * disconnected components on the graph. First we need to build the graph
 * and the adjacency list. Then we need to add edges to join disconnected
 * components. It seems we can just count the number of disconnected components,
 * and ad an edge between each disconnected component. This will be a sufficient
 * solution */

/* Some math: If a graph has k components, you need k - 1 edges to connect them
 */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n + 1);

  for (int i = 0; i < m; ++i) {
    int r1, r2;
    std::cin >> r1 >> r2;
    adj[r1].emplace_back(r2);
    adj[r2].emplace_back(r1);
  }

  std::vector<bool> visited(n + 1, false);
  std::vector<int> connect;
  connect.reserve(n);

  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      connect.push_back(i);

      std::queue<int> q;

      visited[i] = true;
      q.push(i);

      while (!q.empty()) {
        int curr_node = q.front();
        q.pop();
        for (int neighbour : adj[curr_node]) {
          if (!visited[neighbour]) {
            q.push(neighbour);
            visited[neighbour] = true;
          }
        }
      }
    }
  }
  std::cout << connect.size() - 1 << "\n";

  if (connect.size() != 1) {
    for (int i = 0; i < connect.size() - 1; ++i) {
      std::cout << connect[i] << " " << connect[i + 1] << "\n";
    }
  }

  return 0;
}

/* Read the question...
 * Think in terms of edge cases, what when the graph is not disconnected... we
 * don't print any edges...
 * */
