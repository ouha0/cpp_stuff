#include <stdio.h>
#include <string>
#include <vector>

/* This problem is quite hard. Before starting questions like this, it is
 * important to consider lots of test cases, and edge cases before starting to
 * code...
 * Note that a* means that a can be used [0, infinity] times. a* doesn't refer
 * to ab, ac, ad, adddd, etc...
 * */
class Solution {
public:
  bool isMatch(std::string s, std::string p) {
    std::vector<std::vector<int>> dp(s.length() + 1,
                                     std::vector<int>(p.length() + 2, -1));
    return dfs(0, 0, s, p, dp);
  }

private:
  bool dfs(int i, int j, std::string &s, std::string &p,
           std::vector<std::vector<int>> &dp) {
    // If already in cache, return
    if (dp[i][j] != -1) {
      return dp[i][j];
    }

    // if both subproblems are empty, we are done
    if (i >= s.length() && j >= p.length()) {
      dp[i][j] = true;
      return dp[i][j];
    }

    // if no patterns left, but string still not matched, return false;
    if (j >= p.length()) {
      dp[i][j] = false;
      return dp[i][j];
    }

    // Boolean to check whether current indices has a match
    bool match = i < s.length() && (s[i] == p[j] || p[j] == '.');

    // if in bound and 2 indices forward is *, consider using * and not using
    // it
    if (j + 1 < p.length() && p[j + 1] == '*') {
      dp[i][j] = dfs(i, j + 2, s, p, dp) || (match && dfs(i + 1, j, s, p, dp));
      return dp[i][j];
    }

    // 2 indices forward is not *, and there is a match. Move both i, j by 1
    if (match) {
      dp[i][j] = dfs(i + 1, j + 1, s, p, dp);
      return dp[i][j];
    }

    // The patterns cannot be made, so we save false, and return
    dp[i][j] = false;
    return false;
  }
};

class Solution_copy {
public:
  bool isMatch(std::string s, std::string p) {
    std::vector<std::vector<int>> dp(s.length() + 1,
                                     std::vector<int>(p.length() + 2, -1));

    return dfs(0, 0, s, p, dp);
  }

private:
  bool dfs(int i, int j, std::string &s, std::string &p,
           std::vector<std::vector<int>> &dp) {
    if (dp[i][j] != -1) {
      return dp[i][j];
    }

    if (i >= s.length() && j >= p.length()) {
      dp[i][j] = true;
      return true;
    }

    if (j >= p.length()) {
      dp[i][j] = false;
      return false;
    }

    bool match = i < s.length() && (s[i] == p[j] || p[j] == '.');
    if (j + 1 < p.length() && p[j + 1] == '*') {
      dp[i][j] = dfs(i, j + 2, s, p, dp) || (match && dfs(i + 1, j, s, p, dp));
      return dp[i][j];
    }

    if (match) {
      dp[i][j] = dfs(i + 1, j + 1, s, p, dp);
      return dp[i][j];
    }

    dp[i][j] = false;
    return false;
  }
};

/* This problem is quite hard. A key insight to this problem is to knowing how
 * to deal with *, and also noticing that if s = "" and p = "a*", this is
 * perfectly valid, as we can choose to ignore p. This is also why s is empty,
 * and p not empty doesn't automatically evaluate to false, since p can be '*'
 * which means that it can be skipped, which is in fact true!
 *
 * if s is non empty and p is empty, it automatically evaluates to false though!
 * */
