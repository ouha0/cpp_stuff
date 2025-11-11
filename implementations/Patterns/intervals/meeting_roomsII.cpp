#include <stdio.h>
#include <vector>

class Interval {
public:
  int start, end;
  Interval(int start, int end) {
    this->start = start;
    this->end = end;
    ;
  }
};
class Solution {
public:
  /* Idea: We save all key times. Each time we reach a key time, we either
   * increment or decrement the current number of meetings going on. The maximum
   * number of meetings happening at once is the required days we need to
   * schedule. i.e. If at 1pm, there will be 5 meetings going on (and this is
   * the peak for the day), it means that we need to schedule 5 days for all
   * meetings*/
  int minMeetingRooms(std::vector<Interval> &intervals) {
    std::vector<int> start;
    start.reserve(intervals.size());
    std::vector<int> end;
    end.reserve(intervals.size());

    for (const auto &range : intervals) {
      start.emplace_back(range.start);
      end.emplace_back(range.end);
    }
    std::sort(start.begin(), start.end());
    std::sort(end.begin(), end.end());

    int res = 0;

    int curr_count = 0;
    int s_p = 0;
    int e_p = 0;
    while (s_p < start.size() && e_p < end.size()) {
      if (start[s_p] < end[e_p]) {
        curr_count++;
        res = std::max(curr_count, res);
        s_p++;
      } else {
        curr_count--;
        e_p++;
      }
    }

    return res;
  }
};

/* Takeaways: Try to transform the problem slightly, especially when the output
 * doesn't require "history". In this case, the peak number of meetings
 * happening at a specific time is the answer. Also, don't forget to do sorting.
 *
 * If u start a while loop, before writing the whole argument, incremenet this
 * count... This habbit just prevents lots of bugs
 * */
