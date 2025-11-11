#include <queue>
#include <set>
#include <stdio.h>
#include <vector>

using height_pt = std::pair<int, std::pair<int, int>>;

class Solution {
public:
  /* Seems like a bfs with a pq data structure for lowest height grid. In
   * addition to the while loop, when height isn't sufficient, increase the time
   * counter and try again
   *
   * while pq not empty -> check top -> if top is n-1, n-1, return max of height
   * at that position and t -> if top visited, skip -> if top >= time
   * -> continue and increase time counter -> if not visited, add all neighbours
   * in range and not visited into pq
   *
   * */
  int swimInWater(std::vector<std::vector<int>> &grid) {
    int t = 0;
    int n = grid.size();
    std::priority_queue<height_pt, std::vector<height_pt>,
                        std::greater<height_pt>>
        pq;
    pq.emplace(grid[0][0], std::make_pair(0, 0));
    std::vector<std::vector<int>> visited(n, std::vector<int>(n, false));

    while (!pq.empty()) {
      int h = pq.top().first;
      auto [x1, y1] = pq.top().second;

      if (x1 == n - 1 && y1 == n - 1) {
        return std::max(h, t);
      }

      if (h > t) {
        t = h;
      }

      pq.pop();
      if (visited[x1][y1]) {
        continue;
      }
      visited[x1][y1] = true;

      for (const auto [dir_x, dir_y] : dirs) {
        if (x1 + dir_x >= 0 && x1 + dir_x < n && y1 + dir_y >= 0 &&
            y1 + dir_y < n && !visited[x1 + dir_x][y1 + dir_y]) {
          pq.emplace(grid[x1 + dir_x][y1 + dir_y],
                     std::make_pair(x1 + dir_x, y1 + dir_y));
        }
      }
    }

    return t;
  }

private:
  std::vector<std::pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
};
