#include <algorithm>
#include <queue>
#include <stdio.h>
#include <unordered_map>
#include <vector>

/* Idea: brute force, just doing O(N^2). Iterate through each query, for all
 * intervals */
/* This question is quite hard / unexpected... */

class Solution {
  /* Idea to this solution: This question has a natural ordering related to it,
   * so its nice to sort the intervals by the first element first. We also sort
   * throw the queries, but we use a hashtable to remember the value -> initial
   * index of the queries. We want the query because having a sorted query may
   * go well with a sorted interval.
   *
   * Now we also need a pq data strucutre, storing the interval length, followed
   * by the right limit. We iterate through the query.
   * For each query, we keep pushing intervals into the pq until the left
   * element of the interval is out of bounds. At this point, we know that every
   * interval in the pq has a left value that is less that the query. (All
   * following queries are larger than this left value, so it is also fine. We
   * just need to worry about the right value). The top of the heap, if valid,
   * is the interval length we want. If we pushed everything we can, and the top
   * value is invalid, we pop the top value.
   *
   * */

public:
  std::vector<int> minInterval(std::vector<std::vector<int>> &intervals,
                               std::vector<int> &queries) {

    std::sort(intervals.begin(), intervals.end()); // O(NLOGN)

    // O(N); using value, initial index pair, to insert range correctly later
    // Using a hashmap instead doesn't work due to duplicate queries
    std::vector<std::pair<int, int>> indexed_queries;
    for (int i = 0; i < queries.size(); ++i) {
      indexed_queries.emplace_back(queries[i], i);
    }
    // O(NLOGN)
    std::sort(indexed_queries.begin(), indexed_queries.end());

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    // Initialise to avoid out of bounds indexing
    std::vector<int> res(queries.size(), -1);

    int i = 0;
    for (const auto &q : indexed_queries) {
      while (i < intervals.size() && q.first >= intervals[i][0]) {
        pq.emplace(intervals[i][1] - intervals[i][0] + 1, intervals[i][1]);
        ++i;
      }

      while (!pq.empty() && q.first > pq.top().second) {
        pq.pop();
      }
      res[q.second] = pq.empty() ? -1 : pq.top().first;
    }
    return res;
  }
};

/* Key takeaways... Quite hard. Intervals are easier when sorted. Note that keys
 * of hashtables are unique; if u require non-uniqueness, use a different data
 * structures. Heap structures are useful for keeping the "next best value" we
 * want at the very top */

// This problem is just quite hard; don't know how one would code it without
// hints...
