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

/* Idea: Iterate across the grid, when we encounter a room, explore how large
 * the room is and convert it to a wall when done so future explorations don't
 * interfere with it. BFS in every direction within boundary should work */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<char>> grid(n, std::vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> grid[i][j];
    }
  }

  const int dir_x[4] = {-1, 0, 1, 0};
  const int dir_y[4] = {0, 1, 0, -1};

  int res = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == '.') {
        std::queue<std::pair<int, int>> q;
        q.emplace(i, j);
        grid[i][j] = '#';

        while (!q.empty()) {
          int x = q.front().first;
          int y = q.front().second;
          q.pop();

          for (int i = 0; i < 4; ++i) {
            int new_x = dir_x[i] + x;
            int new_y = dir_y[i] + y;

            if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m &&
                grid[new_x][new_y] == '.') {
              q.emplace(new_x, new_y);
              grid[new_x][new_y] = '#';
            }
          }
        }
        res++;
      }
    }
  }

  std::cout << res << "\n";

  return 0;
}

/* Idea was right but implementation was wrong... Messed up indices
 * The logic is important. We should change the grid the moment we pop into the
 * queue, otherwise some other coordinate in the queue may push the same
 * neighbour into the queue. This is wasted work, and may cause it to exceed the
 * time limit
 * */
