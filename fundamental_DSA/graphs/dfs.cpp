#include <stdio.h>
#include <vector>

void dfs(int curr, std::vector<std::vector<int>> &adj,
         std::vector<bool> &visited) {
  // Set current node to visited, and process current node
  visited[curr] = true;
  // Code that processes the node

  // Explore neighbours which aren't visited yet
  for (const int nei : adj[curr]) {
    if (!visited[nei]) {
      dfs(nei, adj, visited);
    }
  }

  return;
}

/* Finding number of nodes in its subtree */
void dfs(int s, int e) {
  count[s] = 1;
  for (const auto nei : adj[s]) {
    if (nei == s) {
      continue;
    }
    // Add subtree count to root count
    dfs(nei, s);
    count[s] += count[nei];
  }
  return;
}

/* Max diameter */
int dfs(int u, int p, std::vector<std::vector<int>> &adj) {
  int max1 = 0;
  int max2 = 0;

  for (const int v : adj[u]) {
    if (v == p) {
      continue;
    }

    int child_height = dfs(v, u, adj);
    if (child_height > max1) {
      max2 = max1;
      max1 = child_height;
    } else if (child_height > max2) {
      max2 = child_height;
    }

    global_res = std::max(global_res, max1 + max2);

    return max1 + 1;
  }
}

/* Traversal orderings */
void dfs(Node *node) {
  // Process node here if preorder

  dfs(node->left);
  // Process not here if inorder

  dfs(node->right);

  // process node here if post order
}
