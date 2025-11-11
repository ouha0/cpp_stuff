#include <stdio.h>
#include <vector>

class Solution {
public:
  /* First we must find the position to insert the intervals. Then we must
   * determine whether to insert it or merge it */
  std::vector<std::vector<int>> insert(std::vector<std::vector<int>> &intervals,
                                       std::vector<int> &newInterval) {
    int i = 0;
    int n = intervals.size();
    std::vector<std::vector<int>> res;

    while (i < n && intervals[i][1] < newInterval[0]) {
      res.emplace_back(intervals[i]);
      ++i;
    }

    while (i < n && newInterval[1] >= intervals[i][0]) {
      newInterval[0] = std::min(newInterval[0], intervals[i][0]);
      newInterval[1] = std::max(newInterval[1], intervals[i][1]);
      i++;
    }
    res.emplace_back(newInterval);

    while (i < n) {
      res.emplace_back(intervals[i]);
      i++;
    }
    return res;
  }
};

class solution_copy {
public:
  /* Idea: keep inserting intervals into results vector, until we are required
   * to merge new interval, some interval in the vector keep inserting as long
   * as largest in interval is smaller than smallest in new interval
   *
   * Now we have to merge intervals, perhaps 1, perhaps multiple
   * the new interval will min of smallest and max of largest of current
   * interval. we have to do so as long there is an overlap.
   * The condition of the overlap is when the larger element of the new interval
   * is larger than the smallest element of the smaller interval
   *
   * then we insert the reset of the intervals into the results vector
   *
   * */
  // test cases. 1,3  5,6; insert 4, 100
  std::vector<std::vector<int>> insert(std::vector<std::vector<int>> &intervals,
                                       std::vector<int> &newInterval) {
    std::vector<std::vector<int>> res;
    res.reserve(intervals.size());
    int i = 0;
    int n = intervals.size();

    while (i < n && intervals[i][1] < newInterval[0]) {
      res.emplace_back(intervals[i]);
    }

    // Only 1 conditional check is required here since, the previous while loop
    // implies this condition
    while (i < n && intervals[i][0] <= newInterval[1]) {
      newInterval[0] = std::min(newInterval[0], intervals[i][0]);
      newInterval[1] = std::max(newInterval[1], intervals[i][1]);
      i++;
    }

    while (i < n) {
      res.emplace_back(intervals[i]);
      i++;
    }

    return res;
  }
};

class binary_solution {
public:
  /* idea here is to use binary search to find the insertion position (ignore
   * merging for now). After this, iterate over the intervals one by one, and
   * merge when required. Note that the zero indexes of the ranges is guarenteed
   * to be smaller than 0 indexes of future ranges (by constrution) */
  std::vector<std::vector<int>> insert(std::vector<std::vector<int>> &intervals,
                                       std::vector<int> &newInterval) {
    if (intervals.empty()) {
      return {newInterval};
    }

    int n = intervals.size();
    int l = 0;
    int r = n - 1;

    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (newInterval[0] <= intervals[mid][0]) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    intervals.insert(intervals.begin() + l, newInterval);

    std::vector<std::vector<int>> res;
    for (const auto &range : intervals) {
      if (res.empty() || res.back()[1] < range[0]) {
        res.emplace_back(range);
      } else {
        res.back()[1] = std::max(res.back()[1], range[1]);
      }
    }

    return res;
  }
};

/* Key takeaways: It is often beneficial to write all the algebra out. Doing
 * explicit test cases and also showing a more general version of the problem */

/* let intervals be [xi, yi], and target be [a, b].
 * intervals are sorted. So long as yi < a, we keep inserting intervals into the
 * result.
 * When we stop, it means yi >= a. we know this is true now
 * We merge if x_i <= b because it means that both a <= yi and b >= xi, which is
 * an overlap. We keep merging so long as there is an overlap
 *
 *
 * */
