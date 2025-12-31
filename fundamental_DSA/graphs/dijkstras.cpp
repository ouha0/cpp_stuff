#include <climits>
#include <queue>
#include <stdio.h>
#include <vector>

/* Implementation*:
 * need a pq, distance vector, require elements of pq to be weight, then node
 * for ordering. (unless we explicitly define a lamda function that deals with
 * this
 *
 * pop the top element, if it is outdates i.e. distance larger (CAN BE EQUAL.
 * EQUAL MEANS IT IS THE CURRENT BEST) than current best, we ignore it.
 * Otherwise we explore its neighbours, if the neighbours potential distance may
 * be fruitful (better than current best). We update the distance vector and
 * push the distance, node pair into the pq.
 *
 *
 *
 * */
std::vector<int>
dijkstras(int V, std::vector<std::vector<std::pair<int, int>>> &adj, int src) {
  std::vector<int> dist(V, INT_MAX);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;

  // Initialisation
  dist[src] = 0;
  pq.push({0, src});

  while (!pq.empty()) {
    int d = pq.top().first;
    int u = pq.top().second;

    pq.pop();
    if (d > dist[u]) {
      continue;
    }

    for (const auto &[length, node] : adj[u]) {
      if (d + length >= dist[node]) {
        continue;
      }

      dist[node] = d + length;
      pq.push({d + length, node});
    }
  }

  return dist;
}
