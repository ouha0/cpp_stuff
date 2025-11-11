#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
  /* Want to find whether the current configuration is valid i.e. whether there
   * are duplicates in 3 regions. Construct a hashset for each region. Iterate
   * through the board, when we reach non-empty character, if not in hashset,
   * insert it. If already in hashset, return false. Return true at the end,
   * since no violiations */
public:
  bool isValidSudoku(std::vector<std::vector<char>> &board) {
    std::vector<std::unordered_set<char>> rows(9);
    std::vector<std::unordered_set<char>> columns(9);
    std::vector<std::unordered_set<char>> square(9);

    // row and colums should be 9
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[0].size(); ++j) {
        if (board[i][j] != '.') {
          char curr_char = board[i][j];
          if (rows[i].count(curr_char) || columns[j].count(curr_char)) {
            return false;
          }
          rows[i].insert(curr_char);
          columns[j].insert(curr_char);

          // The alternative method is to notice that taking the floor of the
          // indices will give the correct square. i.e. for i = j = 8, we can
          // take i / 3 and j / 3 giving 2, 2. If the square hashset was defined
          // as 2d hashset, this would give the correct square
          int sq_count = 0;
          if (i >= 3 && i <= 5) {
            sq_count += 3;
          } else if (i >= 6 && i < 9) {
            sq_count += 6;
          }
          if (j >= 3 && j <= 5) {
            sq_count += 1;
          } else if (j >= 6 && j < 9) {
            sq_count += 2;
          }

          if (square[sq_count].count(curr_char)) {
            return false;
          }
          square[sq_count].insert(curr_char);
        }
      }
    }

    return true;
  }
};
