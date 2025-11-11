#include <stdio.h>
#include <vector>

class Solution {
  /* Idea: dfs on the boarders of the island. We build a two sets of
   * coordinates, one set all coordinates that is able to flow into the pacific,
   * the other set being the set of all coordinates that can flow into the
   * atlantic. In the end, we find coordinates that are in both sets / the
   * intersection */
public:
  std::vector<std::vector<int>>
  pacificAtlantic(std::vector<std::vector<int>> &heights) {
    R = heights.size();
    C = heights[0].size();

    std::vector<std::vector<bool>> pac(R, std::vector<bool>(C, false));
    std::vector<std::vector<bool>> atl(R, std::vector<bool>(C, false));

    for (int r = 0; r < R; ++r) {
      dfs(r, 0, pac, heights, heights[r][0]);
      dfs(r, C - 1, atl, heights, heights[r][C - 1]);
    }

    for (int c = 0; c < C; ++c) {
      dfs(0, c, pac, heights, heights[0][c]);
      dfs(R - 1, c, atl, heights, heights[R - 1][c]);
    }

    std::vector<std::vector<int>> res;
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        if (pac[r][c] && atl[r][c]) {
          res.push_back({r, c});
        }
      }
    }

    return res;
  }

private:
  int R;
  int C;

  const std::vector<std::pair<int, int>> dirs = {
      {-1, 0}, {1, 0}, {0, 1}, {0, -1}};

  void dfs(int x, int y, std::vector<std::vector<bool>> &visit,
           std::vector<std::vector<int>> &heights, int prev_height) {
    if (x < 0 || x >= R || y < 0 || y >= C || visit[x][y] ||
        heights[x][y] < prev_height) {
      return;
    }

    visit[x][y] = true;
    for (const auto [dir_x, dir_y] : dirs) {
      dfs(x + dir_x, y + dir_y, visit, heights, heights[x][y]);
    }
  }
};

/* Note that only the common types are hashable in C++ (integral values). To
 * hash pairs of integers, or other containers, you need to implement your own
 * hash. An alternative for these types of questions is to just go with a 2d
 * vector boolean array */

/* Other potential solutions: bfs from the boundary with a visits "hash" for
 * both pacific and atlantic above
 *
 * Can also do dfs from every cell and use backtracking. For better efficiency,
 * should use memoization so that coordinates aren't traversed multiple times
 * */
