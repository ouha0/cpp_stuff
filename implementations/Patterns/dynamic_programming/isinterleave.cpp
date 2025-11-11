#include <stdio.h>
#include <string>
#include <vector>

/* Key idea: This is a decision tree type of problem; which can be a a
 * combination of recursion / backtracking + caching. The most optimal way
 * however, is to use a pure dynamic programming approach.
 *
 * To start, if using dfs: base case is when s1, and s2 indices go out of bounds
 * */

class dfs_solution {
public:
  bool isInterleave(std::string s1, std::string s2, std::string s3) {

    return dfs(s1, s2, s3, 0, 0, 0);
  }

private:
  bool dfs(std::string &s1, std::string &s2, std::string &s3, int i, int j,
           int k) {
    if (k == s3.length()) {
      return (i == s1.length() && j == s2.length());
    }

    if (i < s1.length() && s1[i] == s3[k]) {
      // Note that this if statement is important, and we can end the whole
      // function the moment we find a true path
      if (dfs(s1, s2, s3, i + 1, j, k + 1)) {
        return true;
      }
    }

    if (j < s2.length() && s2[j] == s3[k]) {
      if (dfs(s1, s2, s3, i, j + 1, k + 1)) {
        return true;
      }
    }

    return false;
  }
};

class dfs_caching_solution {
public:
  bool isInterleave(std::string &s1, std::string &s2, std::string &s3) {
    std::vector<std::vector<int>> dp(s1.length() + 1,
                                     std::vector<int>(s2.length() + 1, -1));
    return dfs(0, 0, s1, s2, s3, dp);
  }

private:
  bool dfs(int i, int j, const std::string &s1, const std::string &s2,
           const std::string &s3, std::vector<std::vector<int>> &dp) {
    if (i + j == s3.length()) {
      return (i == s1.length() && j == s2.length());
    }

    if (dp[i][j] != -1) {
      return dp[i][j];
    }

    bool res = false;
    if (i < s1.length() && s1[i] == s3[i + j]) {
      res = dfs(i + 1, j, s1, s2, s3, dp);
    }

    if (!res && j < s2.length() && s2[j] == s3[i + j]) {
      res = dfs(i, j + 1, s1, s2, s3, dp);
    }

    dp[i][j] = res;
    return res;
  }
};

class solution_copy {
  /* Idea: we do recursion with memoization. Base case: if we have finished
   * comparing all letters of s3, and used up all letters of s1 and s2, return
   * true
   *
   * Otherwise look at dp cache and see if current (i, j, i + j) indices for
   * s1, s2, s3 respectively have been computed previously. If it has been
   * computed in the past return the value in the dp array.
   *
   * Otherwise, set result to 0 (false). if there are still characters in s1,
   * and current character forms a match with s3, search the path of (i + 1, j,
   * i + j + 1) using dfs. Save this result.
   *
   * if result is true, we do nothing. Otherwise we check if current (i, j, i +
   * j) configuration for s2. if next character of s2 is same as next char of
   * s3, we can search the path of (i, j+ 1, i + j + 1).
   *
   * save this into dp array, and return the result. if res was true, this means
   * that from (i, j) configuration onwards, theres a potential match for s3 can
   * be constructed with s1, and s2
   * */

public:
  bool isInterleave(std::string &s1, std::string &s2, std::string &s3) {
    std::vector<std::vector<int>> dp(s1.length() + 1,
                                     std::vector<int>(s2.length() + 1, -1));
    return dfs(0, 0, s1, s2, s3, dp);
  }

private:
  bool dfs(int i, int j, std::string &s1, std::string &s2, std::string &s3,
           std::vector<std::vector<int>> &dp) {
    if (i + j == s3.length()) {
      return (i == s1.length() && j == s2.length());
    }
    if (dp[i][j] != -1) {
      return dp[i][j];
    }

    int res = 0;
    if (i < s1.length() && s1[i] == s3[i + j]) {
      res = dfs(i + 1, j, s1, s2, s3, dp);
    }

    if (!res && j < s2.length() && s2[j] == s3[i + j]) {
      res = dfs(i, j + 1, s1, s2, s3, dp);
    }

    dp[i][j] = res;

    return res;
  }
};

class pure_dp_solution {
  /* This is a pure dp solution. We start from (n, m) -> (0, 0) going left and
   * up dp[i][j] = false means that from s1[i] and s2[j], we cannot make the
   * rest of the s3[i + j] string. dp[i][j] is true if s1[i] == s3[i + j] and
   * dp[i + 1][j]; current ith string of s1 is same as s3. and that i + 1
   * onwards from s1, and j can be used to construct s3. This is the same idea
   * for s2[j] == s3[i + j] and dp[i][j + 1] being true
   * */
public:
  bool isInterleave(std::string &s1, std::string &s2, std::string &s3) {
    if (s1.length() + s2.length() != s3.length()) {
      return false;
    }

    int n = s1.length();
    int m = s2.length();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
    dp[n][m] = true;

    for (int i = n; i >= 0; --i) {
      for (int j = m; j >= 0; --j) {
        if (i < n && s1[i] == s3[i + j] && dp[i + 1][j]) {
          dp[i][j] = true;
        }

        if (j < m && s2[j] == s3[i + j] && dp[i][j + 1]) {
          dp[i][j] = true;
        }
      }
    }

    return dp[0][0];
  }
};
