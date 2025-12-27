#include <algorithm>
#include <climits>
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
const ll INF = 1e18;

/* Since n < 500 and there are lots of queries, we can use floyd-warshall
 * Construct the grid, then build the distance matrix. Finally, iterate over the
 * queries
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m, q;
  std::cin >> n >> m >> q;

  // Initialise distance to inf, but use inf to avoid overflow
  std::vector<std::vector<ll>> dist(n + 1, std::vector<ll>(n + 1, INF));

  // Initilize diagonals
  for (int i = 1; i <= n; ++i) {
    dist[i][i] = 0;
  }

  // include direct paths into the distance matrix
  for (int i = 0; i < m; ++i) {
    int src, dest;
    ll cost;
    std::cin >> src >> dest >> cost;

    // get most efficient distances with path lengths 1
    dist[src][dest] = std::min(cost, dist[src][dest]);
    dist[dest][src] = std::min(cost, dist[dest][src]);
  }

  // Construct distance matrix; O(V^3)
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  for (int i = 0; i < q; ++i) {
    int src, dest;
    std::cin >> src >> dest;

    if (dist[src][dest] == INF) {
      std::cout << -1 << std::endl;
    } else {
      std::cout << dist[src][dest] << std::endl;
    }
  }

  return 0;
}

/* Reflections:
 * Don't forget to read input.
 * Recognize that not all grapsh are nice, non-simple path, lots of cycles
 * etc... Note floyd-warshall is essentially dynamic programming; we consider
 * altnerative paths using k = 1...n, always updating to the shortest path
 *
 * Note that some data structures aren't needed here. For exmaple, we only need
 * the distance matrix here, but we don't need the adjacency list for this
 * problem... We can construct the dist matrix solely from the input
 * */
