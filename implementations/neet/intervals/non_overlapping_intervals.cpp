#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Sort the intervals. Iterate through the intervals, if something problematic
   * happens (overlapping interval: )
   * remove the one with the larger max value
   *
   * */
  int eraseOverlapIntervals(std::vector<std::vector<int>> &intervals) {
    int n = intervals.size();
    int res = 0;
    // O(NLOGN)
    std::sort(intervals.begin(), intervals.end());

    int prev_max = intervals[0][1];

    int curr = 1;
    // O(N)
    while (curr < n) {
      if (intervals[curr][0] >= prev_max) {
        prev_max = intervals[curr][1];
      } else {
        prev_max = std::min(prev_max, intervals[curr][1]);
        res++;
      }
      curr++;
    }
    return res;
  }
};

/*
 *
 * [1, 2], [1, 4], [2, 4].
 * probably better and more efficient to keep it sorted, otherwise hard to find
 * the minimum
 * if same starting point, it makes sense to remove the one with the larger max
 * value. Since it will be sorted, it next first value is compared, we can just
 * remove the next element automatically
 *
 * [1, 5], [2, 4], [7, 8]; here we want to remove the element with the smaller
 * max value
 *
 * [1, 1000] [2, 5], [3, 8]
 *
 * */


/* Key takeaways; it seems that most interval questions can be done with some sorting method */
