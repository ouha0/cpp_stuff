#include <cstdlib>
#include <queue>
#include <stdio.h>
#include <vector>

/* Kahns algorithm; given a list of dependencies, determine the order we execute
 * the tasks. One method is kahns algorithm, finding all 0 degree (dependency)
 * items, doing them first, then updating the dependency to find new items that
 * can be now executed
 *
 * Another way is to do dfs, and get the leaf node towards the root. However, we
 * need to be careful with cycle detection here (use some data structure to
 * store visited);
 *
 * */

/* Key: adjacencty list for DAG. Have q queue of free tasks, do the task, check
 * whether any previously dependent tasks can be scheduled to complete now.
 * We complete all tasks, if size of result is same as numCourses. Return order
 * of tasks if there is a valid solution
 * */
std::vector<int> topologicalsort(int numCourses,
                                 std::vector<std::vector<int>> &prerequisites) {

  // Adjacency list to store the graph
  std::vector<std::vector<int>> adj(numCourses);

  // store incoming edges for every node
  std::vector<int> in_degree(numCourses, 0);

  // e1 ---> e2 means that we complete task e1 before doing e2; cannot do e2
  // before e1
  for (const auto &edge : prerequisites) {
    adj[edge[0]].push_back(edge[1]);
    in_degree[edge[1]]++;
  }

  std::queue<int> free_q;

  for (int i = 0; i < numCourses; ++i) {
    if (in_degree[i] == 0) {
      free_q.push(i);
    }
  }

  std::vector<int> res;
  while (!free_q.empty()) {
    int curr_task = free_q.front();
    free_q.pop();

    res.push_back(curr_task);

    for (const int nei : adj[curr_task]) {
      in_degree[nei]--;
      if (in_degree[nei] == 0) {
        free_q.push(nei);
      }
    }
  }

  return res.size() == numCourses ? res : std::vector<int>();
}
