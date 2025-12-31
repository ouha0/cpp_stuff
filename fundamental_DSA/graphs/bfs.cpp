#include <queue>
#include <stdio.h>
#include <unordered_set>
#include <vector>

/* bfs, typically a tree search layer by layer i.e. search all nodes at a
 * particular depth before moving to the next depth. Can be used to find the
 * shortest path for equally weighted graph. For weighted graphs, we can use
 * dijkstras. We use a queue for bfs. Depending on the problem, we either count
 * the number of items in the queue before proceeding the layer, or we can use
 * some property of the graph (if applicable, for example an integer that saved
 * the distance from the source to the current point )*/

/* Key things:
 * Need a data structure to store the graph, a queue, visited array to avoid
 * iterating over already searched Need to get the front, remember to pop,
 * remember the case when start is equal to the end
 * */

/* Simple bfs to find distance from source to destination */
int bfs(std::vector<std::vector<int>> &adj, int src, int dest) {
  if (src == dest) {
    return 0;
  }

  std::queue<int> q;
  std::vector<bool> visited(adj.size() + 1, false);

  q.push(src);
  visited[src] = true;

  int dist = 0;
  while (!q.empty()) {
    int curr_depth = q.size();

    for (int i = 0; i < curr_depth; ++i) {
      int curr = q.front();
      q.pop();

      for (int nei : adj[curr]) {
        // Skip if new node has already been visited
        if (visited[nei]) {
          continue;
        }

        if (nei == dest) {
          return dist + 1;
        }
        visited[nei] = true;
        q.push(nei);
      }
    }
    dist++;
  }

  return -1;
}
