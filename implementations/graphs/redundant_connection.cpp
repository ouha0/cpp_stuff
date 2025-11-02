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

class Solution_gt_approach {
public:
  /* Idea is to generate a graph using the edges given from scratch. Return the
   * first edge that causes the graph to stop being a tree */
  // This solution does not work the single component structure isn't maintained
  // as we iterate through the edges. We only know that before adding a new
  // edge, the graph was a tree
  std::vector<int>
  findRedundantConnection(std::vector<std::vector<int>> &edges) {
    std::unordered_set<int> nodes;

    for (int i = 0; i < edges.size(); ++i) {
      int n1 = edges[i][0];
      int n2 = edges[i][1];

      if (!nodes.count(n1)) {
        nodes.insert(n1);
      }

      if (!nodes.count(n2)) {
        nodes.insert(n2);
      }

      if (nodes.size() - 1 != i + 1) {
        return edges[i];
      }
    }

    return {};
  }
};

class Solution_union_find {
public:
  /* Idea: when we add a new edge, it should be connecting nodes from two
   * different components; otherwise the edge will cause a cycle. This idea
   * points to union find. We can use union to combine two different components,
   * and use find to determine a nodes "ancestor". If two nodes have the same
   * ancestor, they are from the same component */
  std::vector<int>
  findRedundantConnection(std::vector<std::vector<int>> &edges) {
    std::vector<int> par(edges.size() + 1);
    std::vector<int> rank(edges.size() + 1, 1);

    for (int i = 0; i < edges.size() + 1; ++i) {
      par[i] = i;
    }

    for (int i = 0; i < edges.size(); ++i) {
      int n1 = edges[i][0];
      int n2 = edges[i][1];
      if (!union_find(n1, n2, par, rank)) {
        return edges[i];
      }
    }
    return {};
  }

private:
  // Flattening effect
  int find(int n, std::vector<int> par) {
    int p = par[n];

    while (p != par[p]) {
      par[p] = par[par[p]];
      p = par[p];
    }

    return p;
  }

  bool union_find(int n1, int n2, std::vector<int> &par,
                  std::vector<int> &rank) {
    int p1 = find(n1, par);
    int p2 = find(n2, par);

    if (p1 == p2) {
      return false;
    }

    if (rank[p1] > rank[p2]) {
      par[p2] = p1;
      rank[p1] += rank[p2];
    } else {
      par[p1] = p2;
      rank[p2] += rank[p1];
    }

    return true;
  }
};
