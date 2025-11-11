#include <stdio.h>
#include <string>
#include <vector>

class Solution {
public:
  /* Idea is to use backtracking. Run dfs on every possible element of the
   * board, treating that element as the start. Base case: index == word length
   * -> we have the solution. Otherwise, in the general case. If the row and
   * column is out of bounds or the string is not equal, we return false.
   * Otherwise, the current character. We change the row and column to some temp
   * character and we run dfs on all possible directions */

  bool exist(std::vector<std::vector<char>> &board, std::string word) {
    int rows = board.size();
    int columns = board[0].size();

    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < columns; ++c) {
        if (backtrack(board, word, 0, r, c)) {
          return true;
        }
      }
    }

    return false;
  }

private:
  bool backtrack(std::vector<std::vector<char>> &board, std::string &word,
                 int index, int row, int column) {
    if (index == word.length()) {
      return true;
    }

    if (row >= board.size() || row < 0 || column >= board[0].size() ||
        column < 0 || word[index] != board[row][column]) {
      return false;
    }

    char c_save = board[row][column];
    board[row][column] = '#';
    bool res = backtrack(board, word, index + 1, row + 1, column) ||
               backtrack(board, word, index + 1, row - 1, column) ||
               backtrack(board, word, index + 1, row, column + 1) ||
               backtrack(board, word, index + 1, row, column - 1);

    board[row][column] = c_save;
    return res;
  }
};

/* Key takeaways (other): Remember code runs from left to right. Beware of the
 * ordering of if statements. It is important to check the code for row and
 * column validity before checking for string equality
 * */

class wrong_solution {
  /* This is wrong; this makes the assumption that we can use any combination we
   * wish. However the problem requires that the boxes have to be connected /
   * form a path */
public:
  /* Idea is to iterate through each character, add it to every possible index,
   * check whether string is equal. If equal, return true. Note that we only
   * need to compare newly generated strings, so our starting index is the size
   * of the previous results vector size */
  bool exist(std::vector<std::vector<char>> &board, std::string word) {

    std::vector<std::vector<char>> res = {{}};
    int start_index = 0;
    int curr_size = 0;

    for (int row = 0; row < board.size(); ++row) {
      for (int column = 0; column < board[0].size(); ++column) {

        start_index = curr_size;
        curr_size = res.size();
        for (int i = start_index; i < curr_size; ++i) {

          for (int j = 0; j < res[i].size() + 1; ++j) {
            std::vector<char> cpy = res[i];
            auto it = cpy.begin() + j;
            cpy.insert(it, board[row][column]);

            if (same_string(cpy, word)) {
              return true;
            }

            res.push_back(std::move(cpy));
          }
        }
      }
    }

    return false;
  }

private:
  bool same_string(std::vector<char> &s1, std::string &s2) {
    if (s1.size() != s2.length()) {
      return false;
    }

    int i = 0;
    while (i < s1.size()) {
      if (s1[i] != s2[i]) {
        return false;
      }
      i++;
    }

    return true;
  }
};
