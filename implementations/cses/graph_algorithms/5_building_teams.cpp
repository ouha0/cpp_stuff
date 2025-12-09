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

/* Idea; build an adjacency list. For each node, if not visited, start bfs
 * search. If no colour, use red. Otherwise always use colour that is different
 * to parent. return impossible, if a colour dismatch.
 * Set red to 1.
 *
 * for each node, find children nodes. If children node colour already set same
 * as parent node return imppssible, set colour to different to parent node,
 * update new parent node colour, repeat.
 *
 * */

bool bfs(int n, std::vector<std::vector<int>> &adj, std::vector<int> &team) {
  std::queue<int> depth_q;

  depth_q.push(n);
  team[n] = 1;

  while (!depth_q.empty()) {

    int u = depth_q.front();
    depth_q.pop();

    int curr_colour = team[u];
    int next_colour = (curr_colour == 1) ? 2 : 1;

    for (const int nei : adj[u]) {
      if (team[nei] == curr_colour) {
        return false;
      }

      // Ignore if correct colour already
      if (team[nei] == -1) {
        depth_q.push(nei);
        team[nei] = next_colour;
      }
    }
  }

  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  const int UNVISITED = -1;
  const int TEAM_1 = 1;
  const int TEAM_2 = 2;

  int n, m;
  std::cin >> n >> m;

  // Construct adjacency list
  std::vector<std::vector<int>> adj(n + 1);
  for (int i = 0; i < m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;

    adj[v1].push_back(v2);
    adj[v2].push_back(v1);
  }

  std::vector<int> team(n + 1, UNVISITED);
  for (int i = 1; i <= n; ++i) {
    if (team[i] == UNVISITED) {
      if (!bfs(i, adj, team)) {
        std::cout << "IMPOSSIBLE" << "\n";
        return 0;
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    std::cout << team[i] << " ";
  }

  std::cout << std::endl;

  return 0;
}

/*
 * Note for graphs, sometimes we want directed edges (single way), sometimes we
 * require undirected edges (both ways) Vector is often more efficient that
 * using hashmaps obviously
 * Note for bfs, sometimes we require current layer, sometimes we don't.
 * Remember that we need to get the top, pop the top, explore the neighbours.
 * Mark visited either during insert of during pop. (depends on circumstance)
 * finding least weighted path requires during pop, and only insert when path is
 * less than existing For non-weighted graphs, we can mark visited during pop,
 * since the first node we find is the best...
 *
 * */
