#include <stdio.h>
#include <vector>

/*
 * Algorithm that constructs a matrix that finds shortest paths
 * between any two nodes. Construction is O(V^3), and queries
 * after construction is O(1).
 *
 * Idea is to initialize matrix, and for all possible subpaths,
 * is subpath is shorter distance than current best path, update
 * the path
 *
 * */

using ll = long long;
const ll INF = 1e18;

// Initilize max distance for distance, and set path to itself to be 0;
std::vector<std::vector<ll>> dist(n, std::vector<ll>(n, INF));
for (int i = 0; i < n; ++i) {
  dist[i][i] = 0;
}

// Update distance matrix to include direct neighbours
for (int source = 0; source < n; ++source) {
  for (const auto &[cost, dest] : graphs[source]) {
    dist[source][dest] = cost;
  }
}

for (int k = 0; k < n; ++k) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      // Check if sub-paths exist, to avoid adding infinities. Write consistent
      // logic, don't try to add paths that don't even exist
      if (dist[i][k] != INF && dist[k][j] != INF) {
        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}
