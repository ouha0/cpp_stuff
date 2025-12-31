#include <numeric>
#include <stdio.h>
#include <vector>

class UnionFind {
  std::vector<int> parent;

public:
  UnionFind(int n) {
    parent.resize(n + 1);
    std::iota(parent.begin(), parent.end(), 0);
  }

  int find(int x) {
    if (parent[x] != x) {
      // Make the parent of X its ancestor
      parent[x] = find(parent[x]);
    }

    return parent[x];
  }

  bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return false;
    }

    // Set rootX parent to be rootY
    parent[rootX] = rootY;
    return true;
  }
};
