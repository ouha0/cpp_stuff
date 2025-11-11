#include <queue>
#include <stdio.h>
#include <vector>

class Solution {
public:
  /* BFS: have a time counter. Each minute, fruit next to rotten fruit becomes
   * rotten. Find all rotten fruit coordinates. push them into the queue
   * together.
   *
   * While queue is non empty, save and pop the rotten fruit. (we need to save
   * the size of the current queue to take note of the time). Infect the
   * surrounding fruits for the fixed size; time counter++;
   *
   * When queue is empty, return time_counter - 1, because no fruits were
   * infected in the current iteration
   *
   * The current solution works more like a simulation.
   * */

  /* Another potential solution may be to treat the fruits on the grid as
   * islands. if any particular island has a rotten fruit, then the whole island
   * will be eventually infected. However, the problem here is it doesn't work
   * out the time it takes for all fruit to become rotten (given there is a
   * solution)*/
  int orangesRotting(std::vector<std::vector<int>> &grid) {
    std::queue<std::pair<int, int>> q;
    int t = 0;
    int fresh_count = 0;
    int rotten_count = 0;

    for (int r = 0; r < grid.size(); ++r) {
      for (int c = 0; c < grid[0].size(); ++c) {
        if (grid[r][c] == ROTTEN) {
          rotten_count++;
          q.push(std::make_pair(r, c));
        } else if (grid[r][c] == FRESH) {
          fresh_count++;
        }
      }
    }

    if (fresh_count == 0 && rotten_count == 0) {
      return 0;
    }

    while (!q.empty()) {
      int curr_it = q.size();

      for (int rott = 0; rott < curr_it; ++rott) {
        auto [x, y] = q.front();
        q.pop();

        for (const auto [dir_x, dir_y] : dirs) {
          if (x + dir_x < 0 || x + dir_x >= grid.size() || y + dir_y < 0 ||
              y + dir_y >= grid[0].size() ||
              grid[x + dir_x][y + dir_y] == ROTTEN) {
            continue;
          }
          if (grid[x + dir_x][y + dir_y] == FRESH) {
            grid[x + dir_x][y + dir_y] = ROTTEN;
            fresh_count--;
            q.push(std::make_pair(x + dir_x, y + dir_y));
          }
        }
      }
      t++;
    }

    return ((fresh_count == 0) ? t - 1 : -1);
  }

private:
  std::vector<std::pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
  const int EMPTY = 0;
  const int FRESH = 1;
  const int ROTTEN = 2;
};
