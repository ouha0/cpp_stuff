#include <queue>
#include <stdio.h>
#include <tuple>
#include <vector>

using PIII = std::tuple<int, int, int>;
using PAIR = std::pair<int, int>;

class Solution {
public:
  /* Idea: we want to find the shortest path between two points; this points to
   * dijkstras algorithm. However, the is a maximum number of stops we can't go
   * over, so there must be a variation to dijkstras.
   * First we can create an adjacency list and run dijkstras, but the stopping
   * condition being that the number of stops is less than the threshold k. This
   * means the pq will store the distance, neighboring node, and the number of
   * stops. If the pq becomes empty without finding the desination, we return -1
   *
   * */
  int findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src,
                        int dst, int k) {
    std::vector<std::vector<PAIR>> adj(n);
    for (const std::vector<int> &flight : flights) {
      adj[flight[0]].emplace_back(flight[1], flight[2]);
    }

    std::vector<std::vector<int>> min_cost(n, std::vector<int>(k + 2, INT_MAX));
    std::priority_queue<PIII, std::vector<PIII>, std::greater<PIII>> pq;
    pq.emplace(0, src, -1);
    while (!pq.empty()) {
      const auto [w, n, stops] = pq.top();
      pq.pop();

      if (n == dst) {
        if (stops <= k) {
          return w;
        }
        continue;
      }

      if (w > min_cost[n][stops + 1]) {
        continue;
      }
      min_cost[n][stops + 1] = w;

      for (const auto [nei, w2] : adj[n]) {
        if (stops + 1 <= k && w + w2 < min_cost[nei][stops + 2]) {
          min_cost[nei][stops + 2] = w + w2;
          pq.emplace(w + w2, nei, stops + 1);
        }
      }
    }

    return -1;
  }
};

/* Remember: When we access vector indices, they must be predefined, otherwise
 * it becomes segfault. Its fine for hashmaps, since if undefined, it will
 * define it for you before u access it. Note some paths with lots of stops may
 * be shorter, but it may be more than the k threshold, so we must not use a
 * visited vector, since it will ignore smaller stops, but longer distance
 * paths... */

/* This problem has stronger resource constraints than other similar problems;
 * it requires you not to push nodes where we know the weight is worse than what
 * we already currently have. We should also not push new nodes, that already
 * surpass the k stop threshold
 */
