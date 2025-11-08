#include <stdio.h>
#include <vector>

/* Feeling: either dfs with backtracking on every cell; or dfs via bfs */
class dfs_solution {
  /* Idea; use a dfs solution, but avoid doing repeated work by caching / dp
   * Realise since we want strictly increasing path, we don't need to save
   * whether a position was visited or not, since if it was visited, it means
   * the value was smaller than the current one, so we can't visit it again
   *
   * */
public:
  int longestIncreasingPath(std::vector<std::vector<int>> &matrix) {
    const int r = matrix.size();
    const int c = matrix[0].size();

    std::vector<std::vector<int>> dp(r, std::vector<int>(c, -1));
    int res = 1;
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        res = std::max(res, dfs(i, j, -1, dp, matrix));
      }
    }
    return res;
  }

private:
  const std::vector<std::pair<int, int>> dirs = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  int dfs(int i, int j, int prev_val, std::vector<std::vector<int>> &dp,
          std::vector<std::vector<int>> &matrix) {
    if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() ||
        matrix[i][j] <= prev_val) {
      return 0;
    }
    if (dp[i][j] != -1) {
      return dp[i][j];
    }

    int res = 1;
    for (const auto &[x, y] : dirs) {
      res = std::max(res, 1 + dfs(i + x, j + y, matrix[i][j], dp, matrix));
    }
    dp[i][j] = res;
    return res;
  }
};

/* Reflection: bugs; unclear variable names -> forgot one if comparison
 * condition. defined column to be matrix.size(), which is actually the number
 * of rows...
 * */
