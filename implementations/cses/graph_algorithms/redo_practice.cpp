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

/* This problem is essentially cycle detection. If a node neighbour is not its
 * parent, and the neighbour has been visited before, this will form a cycle.
 * something that has been visited -> ... -> parent -> node -> something that
 * has been visited in the past*/
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  // Construct adjacency list / graph
  std::vector<std::vector<int>> graph(n + 1);
  std::vector<bool> visited(n + 1, false);
  std::vector<int> parent(n + 1);

  for (int i = 0; i < m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;
    graph[v1].push_back(v2);
    graph[v2].push_back(v1);
  }

  int cycle_start = -1, cycle_end = -1;

  // Dfs that returns true (propogates result if cycle has been found)
  std::function<bool(int, int)> dfs = [&](int u, int p) -> bool {
    visited[u] = true;
    parent[u] = p;

    for (const int v : graph[u]) {
      if (v == p) {
        continue;
      }

      if (visited[v]) {
        cycle_start = v;
        cycle_end = u;
        return true;
      }

      if (!visited[v]) {
        if (dfs(v, u)) {
          return true;
        }
      }
    }

    return false;
  };

  for (int i = 1; i <= n; ++i) {
    // cycle found
    if (!visited[i] && dfs(i, -1)) {
      std::vector<int> path;
      path.push_back(cycle_start);

      for (int curr = cycle_end; curr != cycle_start; curr = parent[curr]) {
        path.push_back(curr);
      }

      path.push_back(cycle_start);

      std::cout << path.size() << std::endl;
      for (const int v : path) {
        std::cout << v << " ";
      }
      std::cout << std::endl;

      return 0;
    }
  }

  std::cout << "IMPOSSIBLE" << std::endl;

  return 0;
}
