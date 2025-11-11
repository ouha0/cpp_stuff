#include <stdio.h>
#include <vector>

class Interval {
public:
  int start, end;
  Interval(int start, int end) {
    this->start = start;
    this->end = end;
  }
};

class Solution {
public:
  /* Idea, we can sort based the first element of the interval. Then we can
   * iterate keeping track of the previous end time, and comparing with the
   * current time. If there is conflict, we return false, otherwse we keep going
   */
  bool canAttendMeetings(std::vector<Interval> &intervals) {
    if (intervals.empty()) {
      return true;
    }

    std::sort(intervals.begin(), intervals.end(),
              [](const Interval &a, const Interval &b) {
                if (a.start != b.start) {
                  return a.start < b.start;
                }
                return a.end < b.end;
              });

    int n = intervals.size();
    int prev_max = intervals[0].end;
    int i = 1;
    while (i < n) {
      if (prev_max > intervals[i].start) {
        return false;
      }
      prev_max = intervals[i].end;

      i++;
    }
    return true;
  }
};

/* Takeaways here; now how to write a lamda function, and know when to use
 * greater, when to use less...
 *
 * Sorting requires comparator to answer the question. Does a come
 * before b? Yes, a comes before b if a < b (for ascending order)
 *
 * pq requires the comparator to answer the question: Does a have lower priority
 * than b? Yes, a has lower priority / goes after b if a > b so we use greater
 *
 * */
