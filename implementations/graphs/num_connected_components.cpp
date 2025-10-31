#include <stdio.h>
#include <unordered_map>
#include <vector>
class Solution {
public:
  /* Key idea: run dfs on a particular node and keep going. When dfs is done, +1
   * to count. Start dfs on another node that has not been visited yet.
   *
   * dfs: base case. If node has been visited, end. Otherwise, set node to be
   * visited, and run dfs to visit its neighbouring nodes
   *
   * */
  int countComponents(int n, std::vector<std::vector<int>> &edges) {

    std::unordered_map<int, std::vector<int>> neiMap;
    std::vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
      neiMap[i] = {};
    }

    for (const auto edge : edges) {
      neiMap[edge[0]].push_back(edge[1]);
      neiMap[edge[1]].push_back(edge[0]);
    }
    int count = 0;

    for (int i = 0; i < n; ++i) {
      if (visited[i]) {
        continue;
      }
      count++;
      dfs(i, neiMap, visited);
    }

    return count;
  }

private:
  void dfs(int n, std::unordered_map<int, std::vector<int>> &neiMap,
           std::vector<bool> &visited) {
    if (visited[n]) {
      return;
    }
    visited[n] = true;
    for (const auto nei : neiMap[n]) {
      dfs(nei, neiMap, visited);
    }
  }
};

/* Other optimizations: avoid using hashmaps when they can be replaced by using
 * vectors. i.e. the hashset and hashmap in this case can be changed to
 * vectors. This changes O(1) average to O(1) guarenteed */
