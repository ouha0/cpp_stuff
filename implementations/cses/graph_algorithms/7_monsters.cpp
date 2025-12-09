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

/* Key idea: get all the input, save positions of monsters, and starting point.
 * Then calculate a monsters bfs distance -> then do bfs on the person running
 * away. If any coordinate will be caught by some monster, it isn't valid*/

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  const char moves[4] = {'D', 'U', 'R', 'L'};
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<char>> graph(n, std::vector<char>(m));
  std::pair<int, int> start;
  std::pair<int, int> end = {-1, -1};
  std::vector<std::pair<int, int>> monster_positions;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      // save into graph
      char c;
      std::cin >> c;
      graph[i][j] = c;

      // save monster and survivor start position
      if (c == 'M') {
        monster_positions.emplace_back(i, j);
      } else if (c == 'A') {
        start.first = i;
        start.second = j;

        if (i == n - 1 || j == m - 1) {
          return 0;
        }
      }
    }
  }

  // precalculate monster graph distances by doing bfs
  // This would be O(NM) to populate and build
  std::vector<std::vector<int>> monster_distances(n,
                                                  std::vector<int>(m, INT_MAX));
  std::queue<std::pair<int, int>> monster_q;

  for (const auto [x, y] : monster_positions) {
    monster_q.emplace(x, y);
    monster_distances[x][y] = 0;
  }

  while (!monster_q.empty()) {
    auto [x, y] = monster_q.front();
    monster_q.pop();
    int monster_reach = monster_distances[x][y];

    for (const auto [dirx, diry] : dirs) {
      int newx = x + dirx;
      int newy = y + diry;

      // If new coordinate not wall, and monster can reach coordinate faster
      // than previous, update it
      if (newx >= 0 && newx < n && newy >= 0 && newy < m &&
          graph[newx][newy] != '#' &&
          monster_distances[newx][newy] > monster_reach + 1) {
        monster_distances[newx][newy] = monster_reach + 1;
        monster_q.emplace(newx, newy);
      }
    }
  }

  std::vector<std::vector<char>> parent(n, std::vector<char>(m));
  std::queue<std::pair<int, int>> survivor_q;

  survivor_q.emplace(start);
  int depth = 0;

  while (!survivor_q.empty()) {
    int q_size = survivor_q.size();

    for (int i = 0; i < q_size; ++i) {
      auto [x, y] = survivor_q.front();
      survivor_q.pop();

      for (int d = 0; d < 4; ++d) {
        int newx = x + dirs[d][0];
        int newy = y + dirs[d][1];

        if (newx >= 0 && newx < n && newy >= 0 && newy < m &&
            graph[newx][newy] == '.' &&
            depth + 1 < monster_distances[newx][newy]) {

          if (newx == n - 1 || newy == m - 1) {
            end = {newx, newy};
            parent[newx][newy] = moves[d];

            // wrong at the moment
            // print the solution here
            //

            return 0;
          }

          survivor_q.emplace(newx, newy);
          parent[newx][newy] = moves[d];
          // update relative direction into parent
          graph[newx][newy] = '#'; // mark as visited
        }
      }
    }

    depth++;
  }

  return 0;
}

/*
 *
 * (x,y) -> (x, y + 1) -> (0, 1) -> R
 * (x,y) -> (x, y - 1) -> (0, -1) -> L
 * (x,y) -> (x + 1, y) -> (1, 0) -> D
 * (x,y) -> (x - 1, y) -> (-1, 0) -> UP
 * */
