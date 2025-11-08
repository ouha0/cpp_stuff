#include <stdio.h>
#include <string>
#include <vector>

class Solution {
public:
  /* Idea: dfs / recursive solution / decision tree.
   * Broad idea. If the comparison index is the same we do nothing. If they are
   * different, we have to make 3 different choices. We do recursion here and
   * return the count that gives the minimum number of "moves". We save into a
   * dp array for caching
   *
   * base case:
   * if w1 non empty and w2 is done, we return w1.length(), because we have to
   * delete the rest
   *
   * if w1 is empty and w2 non empty, we return w2.length, because we have to
   * add new elements
   * */
  int minDistance(std::string word1, std::string word2) {

    std::vector<std::vector<int>> dp(word1.length() + 1,
                                     std::vector<int>(word2.length() + 1, -1));
    return dfs(0, 0, word1, word2, dp);
  }

private:
  int dfs(int i, int j, std::string &s1, std::string &s2,
          std::vector<std::vector<int>> &dp) {
    if (i >= s1.length() || j >= s2.length()) {
      return std::max(s1.length() - i, s2.length() - j);
    }

    if (dp[i][j] != -1) {
      return dp[i][j];
    }

    int res = std::numeric_limits<int>::max();
    if (s1[i] == s2[j]) {
      res = dfs(i + 1, j + 1, s1, s2, dp);
      dp[i][j] = res;
    } else {
      // save the 3 actions into results here
    }

    return res;
  }
};
