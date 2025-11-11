#include <queue>
#include <stdio.h>
#include <vector>

class Solution {
  /* Initial Idea: run bfs on all '0's. If a '0' can "escape" / reach the
   * boundary of a board, then it isn't surrounded. We iterate through each
   * coordinate of a board, and try to "sink" the zeros, by running bfs to see
   * if it can reach the boundary. If it can't, we leave it alone. If we can, we
   * sink it by changing it to X's THIS METHOD IS QUITE INEFFICIENT, IT IS
   * BETTER TO SEARCH FROM THE BOUNDARY, USING DFS OR BFS
   *
   * The alternative method: do dfs of the boundary. if out of bounds, cell has
   * already been searched  or cell is 'X', we skip. Otherwise, current cell
   * can't be surrounded (true), and we run dfs on its neighbours. Finally, if a
   * cell is X, and it can be surrounded (false), we change the board cell '0'
   * to 'X'
   * */
public:
  void solve(std::vector<std::vector<char>> &board) {
    R = board.size();
    C = board[0].size();
    std::vector<std::vector<bool>> alone(R, std::vector<bool>(C, false));

    for (int r = 0; r < R; ++r) {
      dfs(r, 0, alone, board);
      dfs(r, C - 1, alone, board);
    }

    for (int c = 0; c < C; ++c) {
      dfs(0, c, alone, board);
      dfs(R - 1, c, alone, board);
    }

    for (int x = 0; x < R; ++x) {
      for (int y = 0; y < C; ++y) {
        if (board[x][y] == 'O' && alone[x][y] == false) {
          board[x][y] = 'X';
        }
      }
    }
  }

private:
  int R;
  int C;
  const std::vector<std::pair<int, int>> dirs = {
      {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  void dfs(int x, int y, std::vector<std::vector<bool>> &alone,
           const std::vector<std::vector<char>> &board) {
    if (x < 0 || x >= R || y < 0 || y >= C || alone[x][y] ||
        board[x][y] == 'X') {
      return;
    }

    alone[x][y] = true;

    for (const auto [dir_x, dir_y] : dirs) {
      dfs(x + dir_x, y + dir_y, alone, board);
    }
  }
};

class Solution_bfs {
public:
  /* Idea do bfs of the boundaries that is 'O'. Mark itself, and all its
   * surrounding 'O's are independent. Keep a 'hashset' of 0's that have already
   * verified (otherwise infinite loop). At the end, iterate through whole
   * board. Change all non-independent 'O's into 'X', and we are done  */
  void solve(std::vector<std::vector<char>> &board) {
    const int R = board.size();
    const int C = board[0].size();

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> independent(R, std::vector<bool>(C, false));

    for (int r = 0; r < R; ++r) {
      if (board[r][0] == 'O') {
        independent[r][0] = true;
        q.push(std::make_pair(r, 0));
      }

      if (board[r][C - 1] == 'O') {
        independent[r][C - 1] = true;
        q.push(std::make_pair(r, C - 1));
      }
    }

    for (int c = 0; c < C; ++c) {
      if (board[0][c] == 'O') {
        independent[0][c] = true;
        q.push(std::make_pair(0, c));
      }

      if (board[R - 1][c] == 'O') {
        independent[R - 1][c] = true;
        q.push(std::make_pair(R - 1, c));
      }
    }

    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();

      for (const auto [dir_x, dir_y] : dirs) {
        if (x + dir_x < 0 || x + dir_x >= R || y + dir_y < 0 ||
            y + dir_y >= C || board[x + dir_x][y + dir_y] == 'X' ||
            independent[x + dir_x][y + dir_y]) {
          continue;
        }
        independent[x + dir_x][y + dir_y] = true;
        q.push(std::make_pair(x + dir_x, y + dir_y));
      }
    }

    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        if (board[r][c] == 'O' && independent[r][c] == false) {
          board[r][c] = 'X';
        }
      }
    }
  }

private:
  const std::vector<std::pair<int, int>> dirs = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
};

/* As before, a bfs solution + memoization characteristic that goes from the
 * boundary should also work. Backtracking too */
