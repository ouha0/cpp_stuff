#include <queue>
#include <stdio.h>
#include <unordered_set>
#include <vector>

using PII = std::pair<int, int>;
class Solution {
public:
  /* Idea: Want to find minimum cost to connect all points together. Can use
   * some algorithm to find minimum spanning tree, and then sum all distances
   * together.
   * First: construct adjacency list; using manhattan distance. Treat this as a
   * complete graph.
   * Add elements into the pq (min-heap), and start the algorithm
   *
   * Sum the distances of the minimum spanning tree
   *
   * The algorithm to use is Prim's algorithm:
   * Create the adjacency list -> run prims algorithm: while len(visited) <
   * total -> if not visited -> add to result, add to visited -> for each
   * neighbour -> if not visited, add to adjacency list
   *
   * */
  int minCostConnectPoints(std::vector<std::vector<int>> &points) {
    int n = points.size();
    std::vector<std::vector<PII>> nei_map(n);

    for (int i = 0; i < n; ++i) {
      int x1 = points[i][0];
      int y1 = points[i][1];

      for (int j = i + 1; j < n; ++j) {
        int x2 = points[j][0];
        int y2 = points[j][1];

        int d = std::abs(x1 - x2) + std::abs(y1 - y2);
        nei_map[i].push_back(std::make_pair(d, j));
        nei_map[j].push_back(std::make_pair(d, i));
      }
    }

    int res = 0;
    std::unordered_set<int> visited;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;

    pq.emplace(0, 0);

    while (visited.size() < n) {
      auto [d, p] = pq.top();
      pq.pop();

      if (visited.count(p)) {
        continue;
      }

      res += d;
      visited.insert(p);

      for (const auto &[d2, p2] : nei_map[p]) {
        if (!visited.count(p2)) {
          pq.emplace(d2, p2);
        }
      }
    }

    return res;
  }
};
