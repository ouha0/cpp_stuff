#include <limits>
#include <queue>
#include <stdio.h>
#include <vector>

class Solution {
  /* do mult-bfs; start of by finding the zeros and add the treasure chest
   * coordinates into the queue.
   * While q is not empty, get top element and pop. In each direction, find the
   * value, and save the smallest non-zero element into that position. Update it
   * onto the grid and push the coordinate into the queue.
   * */
public:
  int INF = 2147483647;

  void islandsAndTreasure(std::vector<std::vector<int>> &grid) {
    std::queue<std::pair<int, int>> q;

    for (int r = 0; r < grid.size(); ++r) {
      for (int c = 0; c < grid[0].size(); ++c) {
        if (grid[r][c] == 0) {
          q.push(std::make_pair(r, c));
        }
      }
    }

    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();

      int curr_val = grid[x][y];
      for (auto [dir_x, dir_y] : dirs) {
        if (x + dir_x < 0 || x + dir_x >= grid.size() ||
            y + dir_y < grid[0].size() || y + dir_y >= grid[0].size() ||
            grid[x + dir_x][y + dir_y] == -1) {
          continue;
        }

        if (grid[x + dir_x][y + dir_y] == INF) {
          grid[x + dir_x][y + dir_y] = curr_val + 1;
          q.push(std::pair(x + dir_x, y + dir_y));
        }
      }
    }

    return;
  }

private:
  std::vector<std::pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
};
