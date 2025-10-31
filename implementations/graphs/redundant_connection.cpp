#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class wrong_solution {
public:
  /* Idea: dfs, and construct a hashset of visited nodes. If we find a node that
   * is is already in the visiting set, the the current path forms a cycle.
   * Stop. Iterate backwards from the edgest vector, and check whether the edge
   * includes a node in the current path set. Return the first edge that has a
   * node in the path set */

  /* This solution fails to identify paths s.t. it contains nodes that aren't in
   * a particular cycle. The solution will may output edges in the final
   * path that isn't in the cycle */
  std::vector<int>
  findRedundantConnection(std::vector<std::vector<int>> &edges) {
    int n = edges.size();
    std::vector<std::vector<int>> neiMap(n + 1);

    for (const auto &edge : edges) {
      neiMap[edge[0]].push_back(edge[1]);
      neiMap[edge[1]].push_back(edge[0]);
    }
    std::vector<bool> visited(n + 1, false);
    std::vector<bool> curr_path(n + 1, false);

    dfs(1, -1, neiMap, visited, curr_path);
    for (int i = edges.size() - 1; i >= 0; --i) {
      if (curr_path[edges[i][0]] && curr_path[edges[i][1]]) {
        return edges[i];
      }
    }

    return {};
  }

private:
  bool dfs(int n, int parent, std::vector<std::vector<int>> &neiMap,
           std::vector<bool> &visited, std::vector<bool> &curr_path) {
    if (visited[n]) {
      return true;
    }

    if (curr_path[n]) {
      return false;
    }

    curr_path[n] = true;
    for (const auto &nei : neiMap[n]) {
      if (nei == parent) {
        continue;
      }
      if (!dfs(nei, n, neiMap, visited, curr_path)) {
        return false;
      }
    }

    curr_path[n] = false;
    visited[n] = true;

    return true;
  }
};
