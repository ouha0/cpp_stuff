#include <stdio.h>
#include <string>
#include <vector>

class caching_Solution {
public:
  /* Note the repetiveness in decision tree paths, hence we can use caching
   * here. Without the dp caching technique, the solution is too slow
   *
   * dfs base case. If t is empty, and s is non empty -> the only way we can
   * construct t with s is by using nothing at all -> so theres only one way
   *
   * if t is non empty and s is empty, there is no way we can construct t from s
   * -> so the count is zero
   *
   * Otherwise, if already in cache, return it. Otherwise, consider the decision
   * trees when we don't use the ith element of s, and move on to i + 1, j. And
   * if s[i] == s[j], also consider the case when we use both i in s, and j in
   * t, so we move on to the i + 1, j + 1 case
   *
   * Before returning, save into dp array so it can be reused in the future
   *
   * */
  int numDistinct(std::string s, std::string t) {
    // This is purely for optimization, not needed
    if (t.length() > s.length()) {
      return 0;
    }

    std::vector<std::vector<int>> dp(s.length() + 1,
                                     std::vector<int>(t.length() + 1, -1));

    return dfs(0, 0, s, t, dp);
  }

private:
  int dfs(int i, int j, std::string &s, std::string &t,
          std::vector<std::vector<int>> &dp) {

    // Think of the leaf node of the decision tree for the base case
    if (j == t.length()) {
      return 1;
    }

    if (i == s.length()) {
      return 0;
    }

    if (dp[i][j] != -1) {
      return dp[i][j];
    }

    int res = dfs(i + 1, j, s, t, dp);
    if (s[i] == t[j]) {
      res += dfs(i + 1, j + 1, s, t, dp);
    }
    dp[i][j] = res;
    return res;
  }
};
