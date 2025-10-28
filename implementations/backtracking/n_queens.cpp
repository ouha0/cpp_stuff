#include <stdio.h>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
  /* Idea: Try something, if it works, keep going, if it doesn't, go back to the
   * most recent case that worked. This idea points towards backtracking
   *
   * If all queens have been used (usee index to track this), add current board
   * configuration onto results.
   *
   * General case: if a queen is insertable, insert it on the board, update
   * necessary information, then do dfs, then backtrack
   *
   * Key: Note that the only information we need is the current state of the
   * board, column information, positive diagonal information, and negative
   * diagonal information. (we can't use columns and diagonals that are already
   * occupied)
   * */
public:
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> board(n, std::string(n, '.'));

    backtrack(res, board, 0);

    return res;
  }

private:
  void backtrack(std::vector<std::vector<std::string>> &res,
                 std::vector<std::string> &board, int index) {
    if (index == board.size()) {
      res.push_back(board);
      return;
    }

    for (int c = 0; c < board.size(); ++c) {
      if (columns.count(c) || pos_diag.count(index + c) ||
          neg_diag.count(index - c)) {
        continue;
      }

      columns.insert(c);
      pos_diag.insert(index + c);
      neg_diag.insert(index - c);
      board[index][c] = 'Q';
      backtrack(res, board, index + 1);

      columns.erase(c);
      pos_diag.erase(index + c);
      neg_diag.erase(index - c);
      board[index][c] = '.';
    }
  }
  std::unordered_set<int> columns;
  std::unordered_set<int> pos_diag;
  std::unordered_set<int> neg_diag;
};

class Solution_copy {
public:
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> board(n, std::string(n, '.'));
    backtrack(res, board, 0);

    return res;
  }

private:
  void backtrack(std::vector<std::vector<std::string>> &res,
                 std::vector<std::string> &board, int index) {
    if (index == board.size()) {
      res.push_back(board);
      return;
    }

    for (int c = 0; c < board.size(); ++c) {
      if (cols.count(c) || pos_diag.count(index + c) ||
          neg_diag.count(index - c)) {
        continue;
      }
      cols.insert(c);
      pos_diag.insert(index + c);
      neg_diag.insert(index - c);
      board[index][c] = 'Q';

      backtrack(res, board, index + 1);

      cols.erase(c);
      pos_diag.erase(index + c);
      neg_diag.erase(index - c);
      board[index][c] = '.';
    }
  }
  std::unordered_set<int> cols;
  std::unordered_set<int> pos_diag;
  std::unordered_set<int> neg_diag;
};
