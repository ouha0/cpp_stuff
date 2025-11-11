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
    } else {
      /* The key is to realise that we don't actually need to modify the string,
       * we can "simulate" modifications by changing the indexes*/
      int cost_replace = 1 + dfs(i + 1, j + 1, s1, s2, dp);
      int cost_delete = 1 + dfs(i + 1, j, s1, s2, dp);
      int cost_insert = 1 + dfs(i, j + 1, s1, s2, dp);
      res = std::min({cost_replace, cost_delete, cost_insert});
    }

    dp[i][j] = res;
    return res;
  }
};

/* It is useful to imagine the values of the 2d cache array of dimensions
 * s1.size() + 1 and s2.size() + 1 */

class pure_dp_solution {
public:
  /* This is a pure dp solution, where we construct the dp 2d array, we slowly
   * built it. if w1[i] == w2[j], then solving (i, j) is same as solving (i + 1,
   * j + 1). if w1[i] != w2[j], we have to determine the minimum distance of the
   * 3 possible states (replace, delete and insert operations). hence state (i,
   * j) is 1 + minimum of other 3 states. If we delete i, it means we move onto
   * (i + 1, j). If we replace the same value as j , it means we can move onto
   * (i + 1, j + 1). If we insert the same value as j, it means we can move onto
   * the (i,  j + 1) state
   * */
  int minDistance(std::string word1, std::string word2) {
    const int n = word1.length();
    const int m = word2.length();

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, -1));

    for (int i = 0; i < n + 1; ++i) {
      dp[i][m] = n - i;
    }

    for (int j = 0; j < m + 1; ++j) {
      dp[n][j] = m - j;
    }

    for (int i = n - 1; i >= 0; --i) {
      for (int j = m - 1; j >= 0; --j) {
        if (word1[i] == word2[j]) {
          dp[i][j] = dp[i + 1][j + 1];
        } else {
          dp[i][j] =
              1 + std::min({dp[i + 1][j + 1], dp[i][j + 1], dp[i + 1][j]});
        }
      }
    }

    return dp[0][0];
  }
};
