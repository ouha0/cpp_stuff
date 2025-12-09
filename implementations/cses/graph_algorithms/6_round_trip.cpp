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

/* graph problem. The are edges between nodes. Desing a round trip that begins
 * somewhere, goes through 2+ cities and returns to the starting city. Idea is
 * dfs along every node, until we find a satisfying path
 * dfs base case = if node already visited, return false. If visiting return
 * true if visiting set is >=
 * */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n + 1);

  for (int i = 0; i < m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;

    adj[v1].push_back(v2);
    adj[v2].push_back(v1);
  }

  std::vector<bool> visited(n + 1, false);
  std::vector<int> parent(n + 1, 0);
  int cycle_start = -1, cycle_end = -1;

  std::function<bool(int, int)> dfs = [&](int u, int p) -> bool {
    // set current node to visited, save its parent
    visited[u] = true;
    parent[u] = p;

    // For each neighbour, if parent, igore case, if nei has been seen before,
    // save the cycle info. Note the cycle start will be the already visited
    // element (from that element to current u element)
    for (const int nei : adj[u]) {
      if (nei == p) {
        continue;
      }

      if (visited[nei]) {
        cycle_start = nei;
        cycle_end = u;
        return true;
      }

      if (!visited[nei]) {
        if (dfs(nei, u)) {
          return true;
        }
      }
    }
    return false;
  };

  for (int i = 1; i <= n; ++i) {
    if (!visited[i] && dfs(i, -1)) {

      std::vector<int> path;
      path.push_back(cycle_start);

      for (int curr = cycle_end; curr != cycle_start; curr = parent[curr]) {
        path.push_back(curr);
      }
      path.push_back(cycle_start);

      std::cout << path.size() << std::endl;
      for (const int city : path) {
        std::cout << city << " ";
      }
      std::cout << std::endl;

      return 0;
    }
  }

  std::cout << "IMPOSSIBLE" << std::endl;

  return 0;
}

/* Key ideas:
 * To find path of a cycle, we often need a parent vector. And dfs requires that
 * we don't visit nodes that are the parent. However, if we ever visit a path
 * that has already been visited, this will become a cycle
 *
 *
 *
 * */
