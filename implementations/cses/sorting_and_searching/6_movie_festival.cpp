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

/* Idea: thinking of this as intervals, we want to find the longest number of
 * non overlapping intervals. But how do we know which interval to choose to
 * watch. We can explore the paths, of potentially occupying / not occuping
 * intervals. This whill become a dfs, which is probably very slow for large
 * output. Another way may be a dynamic programming approach, being the max
 * number of moves we are able to watch at each end /  maybe a greedy approach
 *
 *
 * Greedy approach: For every pair of movies, we choose to watch the movie with
 * earliest end time
 */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  // This solution is less intuitive, a better solution is to sort by the end
  // time
  /*
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> movie_time(n);

  int s, e;
  for (int i = 0; i < n; ++i) {
    std::cin >> s >> e;
    movie_time[i] = std::make_pair(s, e);
  }

  std::sort(movie_time.begin(), movie_time.end());

  int res = 0;
  int curr_end = movie_time[0].second;
  int curr = 1;
  while (curr < n) {
    int next_start, next_end;
    next_start = movie_time[curr].first;
    next_end = movie_time[curr].second;

    if (next_start >= curr_end) {
      res++;
      curr_end = next_end;
    } else {
      curr_end = std::min(curr_end, next_end);
    }
    curr++;
  }
  res++;

  std::cout << res << "\n";
  */

  int n;
  std::cin >> n;
  int s, e;

  std::vector<std::pair<int, int>> movie_times(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s >> e;
    movie_times[i] = std::make_pair(s, e);
  }

  std::sort(movie_times.begin(), movie_times.end(),
            [](const auto &a, const auto &b) {
              if (a.second != b.second) {
                return a.second < b.second;
              }
              return a.first < b.first;
            });

  int movie_count = 0;
  int prev_end_time = 0;

  for (const auto &[start, end] : movie_times) {
    if (start >= prev_end_time) {
      movie_count++;
      prev_end_time = end;
    }
  }

  std::cout << movie_count << "\n";

  return 0;
}
/* Alternative solution is to sort by the end time, and then start time. This
 * makes it natural to iterate through the movies array. This greedy method
 * will ensure that we watch as many movies as we can (nothing missed) */

/* This question is more intuitive if we draw all the intervals out, and
 * then tried to identify the order we should iterate through the movie times */

/* Other small bugs: Don't use emplace_back / push_back when the vector size is
 * already predefined. Note that sort lamda ordering function was defined wrong.
 * Always run through the logic of the code. */
