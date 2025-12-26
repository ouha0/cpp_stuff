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
const int INF = 1e9;

/* Need shortest distance from a particular city to every other city.
 * We can run dijkstras until every city is the shortest distance it could be
 * we need a grid, with weights (weights are positive in this case), priority
 * queue that includes current city and current distance. if we pop something,
 * its new / better, we update the distance vector, and add its adjacent paths .
 * Otherwise, we pop it and do nothing (don't add adjacent paths here)
 * */

/* Dijkstras: pop the city out. Check if better than current alternatives, if
 * so, update the distance list. For each neighbour, if better than current
 * altnerative, add it into the pq*/

/* Update dist when push cost, distance pair inside. When pop, ignore flights
 * that are worse than the current best flight, in particular don't explore the
 * neighbours of bad flights*/

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  // adjacency list; index n is the reachable points from city n to some other
  // destination and the cost
  std::vector<std::vector<std::pair<ll, int>>> grid(n + 1);
  std::vector<ll> dist(n + 1, LLONG_MAX);

  for (int i = 0; i < m; ++i) {
    int source, dest;
    ll cost;
    std::cin >> source >> dest >> cost;
    grid[source].emplace_back(cost, dest);
  }

  std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>,
                      std::greater<std::pair<ll, int>>>
      dist_pq;

  // Start dijkstras algorithm, never forget the initialization stage...
  dist_pq.emplace(0, 1);
  dist[1] = 0;

  while (!dist_pq.empty()) {
    auto [cost, dest] = dist_pq.top();
    dist_pq.pop();

    if (cost > dist[dest]) {
      continue;
    }

    for (const auto &[flight_cost, flight_dest] : grid[dest]) {
      if (cost + flight_cost >= dist[flight_dest]) {
        continue;
      }

      dist[flight_dest] = cost + flight_cost;
      dist_pq.emplace(cost + flight_cost, flight_dest);
    }
  }

  for (int city = 1; city <= n; ++city) {
    std::cout << dist[city] << " ";
  }

  std::cout << std::endl;

  return 0;
}

/* Key takeaways; Dijkstras will work for shortest paths from a single
 * non-unique source. To avoid TLE, if some information can avoid redundant
 * searching, include it. This means updating "current best distance" on push
 * rather than pop. It also means that we only explore neighbours of popped
 * items if the cost is less than or equals to the current best. If it is
 * equals, it means it was the flight that resulted in the shortest distance, so
 * we must explore its neighbours
 *
 * Don't forget the initialization stage of dijkstras algorithms, remember what
 * your elements / pair represents. Its cost first, then destination
 * */

/* Other: review priority queues and dijkstras algorithm. Whether to use greater
 * or less, how to write the lambda function. Understand how to avoid TLE,
 * modify on push or on pop (it is push to speed up algorithm)*/
