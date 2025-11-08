#include <stdio.h>
#include <vector>

/* Feeling: either dfs with backtracking on every cell; or dfs via bfs */
class dfs_solution {
  // If we travel past a cell, we can never go back to it, due to
  // the strictly increasing rule

  /* Idea: We iterate through each starting point and do dfs.
   * Base case: if surrounding cells has been visited, or smaller than current
   * cell, we return the current distance travelled
   *
   *
   * Base case: travel the maximum distance in every possible direction,
   * return the maximum distane of the directions
   * */
public:
  int longestIncreasingPath(std::vector<std::vector<int>> &matrix) {}

private:
};
