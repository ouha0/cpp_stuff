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

/* Idea: We want the length of the shortest path between two points. We can do
 * this with bfs
 * While queue not empty, get first element, explore all possibnle directions,
 * push new coordinate into the queue, and change the grid element to hash. Stop
 * when the element we push is B (end point)
 *
 * hmmmm need to figure out a way to backtrack the initial path. Storing in the
 * queue does not work since it isn't persistent (popped) as we go.
 * Storing the directions into a 2d array is sufficient for this...
 * */

// Redo this, and write cleaner code...
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<char>> grid(n, std::vector<char>(m));

  std::pair<int, int> start;
  std::pair<int, int> end;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> grid[i][j];
      if (grid[i][j] == 'A') {
        start.first = i;
        start.second = j;
      }

      if (grid[i][j] == 'B') {
        end.first = i;
        end.second = j;
      }
    }
  }

  int res = 0;
  std::queue<std::pair<int, int>> q;
  q.emplace(start);
  grid[start.first][start.second] = '#';

  const int dir_x[4] = {1, 0, -1, 0};
  const int dir_y[4] = {0, 1, 0, -1};
  const char stepDir[4] = {'D', 'R', 'U', 'L'};

  std::vector<std::vector<char>> history(n, std::vector<char>(m));

  while (!q.empty()) {
    int levels = q.size();

    for (int i = 0; i < levels; ++i) {
      int x = q.front().first;
      int y = q.front().second;
      q.pop();

      for (int j = 0; j < 4; ++j) {
        int new_x = x + dir_x[j];
        int new_y = y + dir_y[j];

        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m) {
          if (grid[new_x][new_y] == 'B') {
            history[new_x][new_y] = stepDir[j];
            std::cout << "YES" << "\n" << res + 1 << "\n";

            int back_x = new_x;
            int back_y = new_y;
            std::vector<char> backtrack(res + 1);
            for (int k = res; k >= 0; --k) {
              backtrack[k] = history[back_x][back_y];
              auto it = std::find(std::begin(stepDir), std::end(stepDir),
                                  backtrack[k]);
              int index = std::distance(std::begin(stepDir), it);
              back_x = back_x - dir_x[index];
              back_y = back_y - dir_y[index];
            }
            for (int k = 0; k < res + 1; ++k) {
              std::cout << backtrack[k];
            }
            std::cout << "\n";

            return 0;
          } else if (grid[new_x][new_y] == '.') {
            history[new_x][new_y] = stepDir[j];
            q.emplace(new_x, new_y);
            grid[new_x][new_y] = '#';
          }
        }
      }
    }
    res++;
  }

  std::cout << "NO" << "\n";

  return 0;
}

/* Key: The logic was overall correct. Note that backtracking can't be done by
 * changing structure of queue element, since elements are lost the moment they
 * are popped. We need to store the previous information, which can be
 * represented in 4 characters (directions). Also realise that as soon as a
 * direction is assigned to some coordinate, it can't be changed by design,
 * since there was no repeating for neighbours finding neighbours
 *
 * Also, be very careful with dummy variables, knowing which one to use... In
 * this case, messed up i, j, and k multiple times...
 *
 * */
