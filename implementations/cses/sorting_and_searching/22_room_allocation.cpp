#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using ll = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9;

/* Idea: Sort the input by start time, and end time. We iterate across the
 * times, allocate a room, and insert into min_heap, which stores the current
 * allocated rooms where the top is the fastest end time (minheap).
 *
 * Sort the start and end time, and store the initial index. Have a minheap
 * storing the end time and the room it has been allocated.
 *
 * Iterate over each time, compare with current top of minheap (fastest end
 * time), if time is strictly larger, pop the top of the minheap and insert
 * curren time into minheap with that time, remember to update the room number
 * with the room allocated
 *
 * */

struct Time {
  int start;
  int end;
  int id;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::vector<Time> time(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> time[i].start >> time[i].end;
    time[i].id = i;
  }

  std::sort(time.begin(), time.end(), [](const Time &a, const Time &b) {
    if (a.start != b.start) {
      return a.start < b.start;
    }

    return a.end < b.end;
  });

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;
  std::vector<int> rooms(n);

  int max_room = 1;
  for (const auto &t : time) {
    int assigned_room;
    if (!pq.empty() && t.start > pq.top().first) {
      assigned_room = pq.top().second;
      pq.pop();
    } else {
      assigned_room = max_room;
      max_room++;
    }
    pq.emplace(t.end, assigned_room);
    rooms[t.id] = assigned_room;
  }

  std::cout << max_room - 1 << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << rooms[i] << " ";
  }
  std::cout << '\n';

  return 0;
}

/* Key idea is to notice that this is an intervals problem. Doing a O(N) sweep
 * isn't sufficient, since we need to allocate room numbers to specific
 * customers (would be sufficient if we only needed to know max customers at
 * once). Hence we need simulate events and use some data structure that
 * efficiently gives us the enxt avaibale room to use. */
