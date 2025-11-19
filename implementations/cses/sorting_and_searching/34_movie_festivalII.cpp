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

/* Initial idea: Find all overlapping intervals, and subtract the intervals that
 * cannot be watched from the total movie count. Don't need to initial order of
 * the movie start end indices; fine to sort it.
 * Seems intuitive to sort by the start time, and earliest end time. It seems
 * optimal to always choose the early state time. However the duration of the
 * movie is very important, there is no point watchign something with a very
 * long duration, larger future loss. To be independent, there should be no
 * overlap between previous movie end time and current movie start time
 * */

/* Key to this question is noticing that the start and and duration of the movie
 * don't matter, the important thing is knowing the ending time of the movie.
 * For each movie, we need to query "who just finished" a movie, and allocate
 * them to watch this movie, and insert it back into the multiset. Knowing the
 * earliest finish time is easy, since it is at the top. */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, k;
  std::cin >> n >> k;

  std::vector<std::pair<int, int>> nums(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i].first >> nums[i].second;
  }

  std::sort(nums.begin(), nums.end(), [](const auto &a, const auto &b) {
    if (a.second != b.second) {
      return a.second < b.second;
    }
    return a.first > b.first;
  });

  std::multimap<int, int> member_t;
  for (int i = 0; i < k; ++i) {
    member_t.emplace(0, i);
  }

  int res = 0;
  for (const auto &t : nums) {
    int start = t.first;
    int end = t.second;

    int earliest_finish = member_t.begin()->first;
    if (earliest_finish > start) {
      continue;
    }

    auto it = member_t.upper_bound(start);
    it--;
    int member_allocate = it->second;
    member_t.erase(it);
    member_t.emplace(end, member_allocate);

    res++;
  }

  std::cout << res << "\n";

  return 0;
}

/* Important points:
 * Realise that it is important to order time by ending time, and then latest
 * starting time (intuitive); for greedy algorithm
 *
 * We iterate through the earliest ending times, with the shortest movie
 * duration.
 * Each time, we allocate the person that finished closest to the movie start
 * time. We don't want to allocate someone that finished much earlier, since we
 * want to leave that person for a future time interval pair, which a
 * potentially earlier start time. If we can allocate someone, we increment the
 * movie count by 1
 *
 * Note that we need to do a fast query for people who finished a movie as close
 * as possible to the start time of the current movie. We can use upper bound to
 * find the first element larger, and iterate backwards by one.
 * The data structure for this efficient query is using a multiset (since
 * a time interval can have multiple ending times)
 * */
