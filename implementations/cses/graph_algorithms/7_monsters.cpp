#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include <climits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using ll = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9;

/*
 * Goal: Want to reach boundary, if possible, before any monster catches you.
 * return NO if impossible, YES + the path if possible; this means that we
 * have to save the valid path
 *
 * We assume the monster moves optimally, so we can do bfs on the monsters first
 * and prepopulate the number of steps required by the monster to reach that
 * point (given they walk optimally). A can only reach a particular position, if
 * the steps it takes to get their is less than the monster steps. A path
 * exists, if A is able to get to the boundary.
 *
 * */

/* Specific implementations:
 * Construct the grid: iterate and save the char into the grid. If A, save that
 * as the start position. if M, add that coordinate into a queue, which we use
 * to the minimum steps required for the monster to reach every point
 *
 * When doing bfs; for the monster, only reach a point if in range and not a
 * wall (we can replace A with a number because we already saved the starting
 * point of A). Update only if we can reach the point faster than some other
 * monster
 *
 * bfs for the person, save the current number of steps, if a point is reachable
 * (in range, reach faster than a monaster, not a wall), add to queue. Increase
 * current steps count at each level. To reconstruct the successful path, we may
 * need a grid that saves the information of the direction the person took
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

  std::queue<std::pair<int, int>> monster_q;
  std::queue<std::pair<int, int>> player_q;

  // Construct the grid, save into monster_q, save start
  std::vector<std::vector<char>> grid(n, std::vector<char>(m));
  std::vector<std::vector<int>> monster_grid(n, std::vector<int>(m, INT_MAX));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char tmp;
      std::cin >> tmp;
      grid[i][j] = tmp;

      if (tmp == 'M') {
        monster_q.emplace(i, j);
        monster_grid[i][j] = 0;

      } else if (tmp == 'A') {
        player_q.emplace(i, j);

        // If we start at boundary, we are done
        if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
          std::cout << "YES" << std::endl;
          return 0;
        }
      }
    }
  }

  /* Construct monster grid; fill with shortest paths */
  std::vector<std::vector<char>> parent_dir;
  while (!monster_q.empty()) {
    auto [curr_x, curr_y] = monster_q.front();
    monster_q.pop();

    for (const auto &dir : dirs) {
      int nx = curr_x + dir[0];
      int ny = curr_y + dir[1];

      if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
        continue;
      }

      if (monster_grid[nx][ny] == INT_MAX) {
        monster_grid[nx][ny] = monster_grid[curr_x][curr_y] + 1;
        monster_q.emplace(nx, ny);
      }
    }
  }

  /* Construct player grid */
  int player_step = 1;
  while (!player_q.empty()) {

    int curr_layer = player_q.size();
    for (int i = 0; i < curr_layer; ++i) {

      auto [curr_x, curr_y] = player_q.front();
      player_q.pop();

      for (const auto &dir : dirs) {
        int nx = curr_x + dir[0];
        int ny = curr_y + dir[1];

        // out of range move
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
          continue;
        }

        if (grid[nx][ny] == '.' && player_step < monster_grid[nx][ny]) {
          player_q.emplace(nx, ny);

          // Save the direction to the parent direction
        }
      }
    }
    player_step++;
  }

  return 0;
}

// Hard problem...
/* Takeaways: use the pattern where current length depends on previous
 * coordinate length rather than using a stack variable which counts the layers
 * / steps */
