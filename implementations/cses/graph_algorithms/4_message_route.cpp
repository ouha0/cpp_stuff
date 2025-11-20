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

/* Initial idea: Seems just like a bfs question, but we have to save the parent
 * node / where a node came from somehow. This can't be saved in the queue,
 * since elements in the queue are popped. We use another data structure,
 * probably vector of nodes, indicating where the node came from. This will
 * work, since each node will only be visited once. If its already visited,
 * we won't search the same place again , since the previous visit was the
 * shortest path from node 1 to n */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n + 1);
  for (int i = 0; i < m; ++i) {
    int n1, n2;
    std::cin >> n1 >> n2;
    adj[n1].emplace_back(n2);
    adj[n2].emplace_back(n1);
  }

  std::vector<bool> visited(n + 1, false);
  std::vector<int> came_from(n + 1, -1);
  std::queue<int> q;

  q.push(1);
  visited[1] = true;

  int path_length = 0;
  bool found = false;
  while (!q.empty() && !found) {
    int level = q.size();

    for (int i = 0; i < level; ++i) {
      int curr_node = q.front();
      q.pop();

      for (int &nei : adj[curr_node]) {
        if (!visited[nei]) {
          q.emplace(nei);
          visited[nei] = true;
          came_from[nei] = curr_node;

          if (nei == n) {
            found = true;
            break;
          }
        }
      }

      if (found) {
        break;
      }
    }
    path_length++;
  }

  if (found) {
    std::cout << path_length + 1 << "\n";

    int curr = n;
    std::vector<int> res(path_length + 1);

    for (int i = path_length; i >= 0; --i) {
      int parent = came_from[curr];
      res[i] = curr;
      curr = parent;
    }

    for (int i = 0; i < path_length + 1; ++i) {
      std::cout << res[i] << " ";
    }
    std::cout << "\n";

  } else {
    std::cout << "IMPOSSIBLE" << "\n";
  }

  return 0;
}

/* Again, be careful with variable naming, and when there's lots of dummy
 * variables */
