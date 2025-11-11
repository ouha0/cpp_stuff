#include <queue>
#include <stdio.h>
#include <unordered_map>
#include <vector>

using PII = std::pair<int, int>;

class Solution {
public:
  /* Idea: want to find the minimum time to reach every node; the slowest {set
   * of times it takes to reach every node}. This points to some variation of
   * dijstras algorithm, which gives us a spanning tree of the shortest path to
   * every node from a particular node. From there, we just need the longest
   * distance node. Refresher: dijkstras is essentially bfs + a heap priority
   * queue + data structure to save minimum distances to a particular node */

  /* Create adjacency list -> set up priority queue -> while not empty, top
   * element and pop
   * -> if in visited, skip -> otherwise update current max time -> for each of
   * the neighbours -> push time, and node into the priority queue */

  int networkDelayTime(std::vector<std::vector<int>> &times, int n, int k) {
    std::unordered_map<int, std::vector<PII>> nei_map;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
    pq.push({0, k});

    for (const auto &time : times) {
      nei_map[time[0]].push_back({time[1], time[2]});
    }

    std::vector<bool> visited(n + 1, false);

    int t = 0;
    while (!pq.empty()) {
      auto [w, curr] = pq.top();
      pq.pop();

      if (visited[curr]) {
        continue;
      }

      visited[curr] = true;
      t = std::max(t, w);

      for (const auto &[n2, w2] : nei_map[curr]) {
        if (!visited[n2]) {
          pq.push({w + w2, n2});
        }
      }
    }

    for (int i = 1; i < n + 1; ++i) {
      if (visited[i] == false) {
        return -1;
      }
    }

    return t;
  }
};

class optimised_solution {
public:
  int networkDelayTime(std::vector<std::vector<int>> &times, int n, int k) {
    std::vector<std::vector<PII>> nei_map(n + 1);
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
    std::vector<bool> visited(n + 1, false);

    for (const auto &time : times) {
      nei_map[time[0]].emplace_back(time[1], time[2]);
    }

    int t = 0;
    pq.emplace(0, k);
    while (!pq.empty()) {
      auto [w1, n1] = pq.top();
      pq.pop();

      if (visited[n1]) {
        continue;
      }

      visited[n1] = true;
      t = std::max(w1, t);

      for (const auto &[n2, w2] : nei_map[n1]) {
        if (!visited[n2]) {
          pq.emplace(w2 + w1, n2);
        }
      }
    }

    for (int i = 1; i < n + 1; ++i) {
      if (visited[i] == false) {
        return -1;
      }
    }
    return t;
  }
};

/* Graphs with node weightings and finding the "shortest" often point to using
 * some variation of the dijstras algorithm.*/

// This is just a basic dijkstras implementation
class dijstras_solution {
public:
  int networkDelayTime(std::vector<std::vector<int>> &times, int n, int k) {
    std::vector<int> min_time(n + 1, INT_MAX);
    std::vector<std::vector<PII>> nei_map(n + 1);
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;

    for (const auto &time : times) {
      nei_map[time[0]].emplace_back(time[1], time[2]);
    }

    int t = 0;
    pq.emplace(0, k);
    min_time[k] = 0;

    while (!pq.empty()) {
      auto [w1, n1] = pq.top();
      pq.pop();
      if (w1 > min_time[n1]) {
        continue;
      }

      min_time[n1] = w1;
      t = std::max(t, w1);

      for (const auto [n2, w2] : nei_map[n1]) {
        if (w2 + w1 < min_time[n2]) {
          pq.emplace(w1 + w2, n2);
        }
      }
    }

    for (int i = 0; i < min_time.size(); ++i) {
      if (min_time[i] == INT_MAX) {
        return -1;
      }
    }

    return t;
  }
};
