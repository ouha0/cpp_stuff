#include <stdio.h>
#include <string.h>
#include <vector>

class Solution {
public:
  /* Construct a 2d dp boolean array, where dp[i][j] represents index i - index
   * j is a palindrome. We always need to save the largest index i - index j, to
   * avoid searching at the end Best solution is O(1), haven't thought of that
   * yet.
   * */
  std::string longestPalindrome(std::string s) {
    int n = s.length();
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));

    int l = 0;
    int r = 0;

    for (int i = n - 1; i >= 0; --i) {
      for (int j = i; j < n; ++j) {
        if (i == j) {
          dp[i][j] = true;
          if (j - i > r - l) {
            l = i;
            r = j;
          }
        } else if (j - i == 1 && s[i] == s[j]) {
          dp[i][j] = true;
          if (j - i > r - l) {
            l = i;
            r = j;
          }
        } else {
          if (s[i] == s[j] && dp[i + 1][j - 1]) {
            dp[i][j] = true;
            if (j - i > r - l) {
              l = i;
              r = j;
            }
          }
        }
      }
    }
    return s.substr(l, r - l + 1);
  }
};

/* Dynamic programming. Note that a string is a palindrone iff its substrings is
 * a palindrome and the left and right side are the same. We can use this
 * information to do dynamic programming. Note that we keep track of the largest
 * palindrome all the time, otherwise we need to search to whole data structure
 * in the end. */

/* A double pointer approach is also possible here, and another optimal solution
 * with O(1) space is possible*/
