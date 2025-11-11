#include <stdio.h>
#include <unordered_map>
#include <vector>

class Solution {
public:
  /* Idea: greedy approach. We would like a frequency count, to know whether its
   * ok for the right parenthesis to appear */

  /* This greedy solution is actually quite hard. In this case, we have a
   * leftmin and leftmax count, representing the scoring / balance of the left
   * and right braces. left_min = x means that all possible paths have at least
   * x more left braces than right braces. '*' means that it could be a left
   * or right braces, so we add -1 to left min (right braces), and add to left
   * max(left braces).
   *
   * We look at the range of the left and right braces balance. if left min ever
   * goes negative, we can always set it back to zero (since we can allow '*' to
   * work as a left braces at some point). But if left max becomes negative,
   * this means that even after using as many left braces as we can (each '*'
   * uses a left braces), there are still more right braces than left braces.
   * i.e. **(()))))))
   * */
  bool checkValidString(std::string s) {
    int left_min = 0;
    int left_max = 0;

    for (const char &c : s) {
      if (c == '(') {
        left_min++;
        left_max++;
      } else if (c == ')') {
        left_min--;
        left_max--;
      } else {
        left_min--;
        left_max++;
      }

      if (left_min < 0) {
        left_min = 0;
      }
      if (left_max < 0) {
        return false;
      }
    }
    return left_min == 0;
  }
};

class dp_solution {
public:
  bool checkValidString(std::string s) {
    std::vector<std::vector<int>> dp(s.size() + 1,
                                     std::vector<int>(s.size() + 1, -1));
    return dfs(0, 0, s, dp);
  }

private:
  /* dfs recursive + dp solution. Base case is when index is goes out of bounds,
   * return whether left brackets is zero. Otherwise evaluate the potential
   * paths*/
  bool dfs(int i, int left_b, std::string &s,
           std::vector<std::vector<int>> &dp) {
    bool res;
    if (i >= s.size()) {
      res = left_b == 0;
      dp[i][left_b] = res;
      return res;
    }

    // Forgot about dp caching
    if (dp[i][left_b] != -1) {
      return dp[i][left_b];
    }

    if (s[i] == '(') {
      res = dfs(i + 1, left_b + 1, s, dp);
    } else if (s[i] == ')') {
      // Note that if left_b becomes negative, it is false
      if (left_b - 1 < 0) {
        res = false;
      } else {
        res = dfs(i + 1, left_b - 1, s, dp);
      }
    } else {
      bool as_open = dfs(i + 1, left_b + 1, s, dp);
      bool do_nothing = dfs(i + 1, left_b, s, dp);
      bool as_close = false;
      // Note that we must do the check here too
      if (left_b - 1 >= 0) {
        as_close = dfs(i + 1, left_b - 1, s, dp);
      }
      res = as_open || as_close || do_nothing;
    }

    dp[i][left_b] = res;
    return res;
  }
};

/* Takeaways; this greedy solution is hard to get at. But a dfs / recursive
 * solution is very much still a valid solution. Always go over the base cases
 * first for dp questions. When change indices of an array, always think about
 * whether that entry is actually valid*/
