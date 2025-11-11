#include <stdio.h>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
  bool validTree(int n, std::vector<std::vector<int>> &edges) {
    std::unordered_set<int> visited;
    std::unordered_map<int, std::vector<int>> neiMap;
    std::vector<bool> curr_path(n + 1, false);

    for (int i = 0; i < n; ++i) {
      neiMap[i] = {};
    }

    for (const auto edge : edges) {
      neiMap[edge[0]].push_back(edge[1]);
      neiMap[edge[1]].push_back(edge[0]);
    }

    if (!dfs(0, -1, visited, curr_path, neiMap)) {
      return false;
    }

    if (visited.size() != n) {
      return false;
    }

    return true;
  }

private:
  bool dfs(int n, int parent, std::unordered_set<int> &visited,
           std::vector<bool> &curr_path,
           std::unordered_map<int, std::vector<int>> &neiMap) {
    if (curr_path[n] == true) {
      return false;
    }

    if (visited.count(n)) {
      return true;
    }

    curr_path[n] = true;
    for (const int nei : neiMap[n]) {
      if (nei == parent) {
        continue;
      } else if (!dfs(nei, n, visited, curr_path, neiMap)) {
        return false;
      }
    }
    curr_path[n] = false;
    visited.insert(n);
    return true;
  }
};

class Solution_GT {
public:
  bool validTree(int n, std::vector<std::vector<int>> &edges) {
    if (edges.size() != n - 1) {
      return false;
    }

    std::unordered_map<int, std::vector<int>> neiMap;

    for (int i = 0; i < n; ++i) {
      neiMap[i] = {};
    }

    for (const auto edge : edges) {
      neiMap[edge[0]].push_back(edge[1]);
      neiMap[edge[1]].push_back(edge[0]);
    }

    std::unordered_set<int> visited;
    dfs(0, neiMap, visited);

    return (visited.size() == n) ? true : false;
  }

private:
  void dfs(int n, std::unordered_map<int, std::vector<int>> &neiMap,
           std::unordered_set<int> &visited) {
    if (visited.count(n)) {
      return;
    }

    visited.insert(n);

    for (const auto nei : neiMap[n]) {
      dfs(nei, neiMap, visited);
    }
  }
};

/* Random ideas: valid tree is if there are no cycles and the graph is
 * connected. We can probably use adjacency list and dfs to determine whether a
 * graph has no cycles. To determine whether connected, we can run through one
 * node and have a visited hashset. If hashset size is n, it means that the
 * graph is connected */

/* Another method is a graph theory approach. A graph is connected if the graph
 * is connected and the total number of nodes is equal to total edges - 1.
 * We can verifiy the total number of edges in the start, and then run dfs on a
 * single node. if every other node is reached, then we know the graph is a tree
 */
