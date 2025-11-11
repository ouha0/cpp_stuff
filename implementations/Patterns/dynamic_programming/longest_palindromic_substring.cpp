#include <stdio.h>
#include <string.h>
#include <vector>

class Solution {
public:
  /* Construct a 2d dp boolean array, where dp[i][j] represents index i - index
   * j is a palindrome. We always need to save the largest index i - index j, to
   * avoid searching through whole dp array at the end.
   * */

  // This is the standard solution that is O(N^2) time and O(N^2 space)
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

class Solution2 {
public:
  /* Alternative method is to use the pointer approach. For each character, we
   * aim to construct the largest palindrome with that character as the
   * midpoint. Note there are two cases; palindromes of odd length and even
   * length For each character of a string, we try to construct the largest
   * palindrome. This is O(N^2) time complexity with O(1) Space
   * */

  std::string longestPalindrome(std::string s) {
    int res_l = 0;
    int res_r = 0;

    for (int i = 0; i < s.length(); ++i) {
      int l = i - 1;
      int r = i + 1;
      while (l >= 0 && r < s.length() && s[l] == s[r]) {
        if (r - l > res_r - res_l) {
          res_r = r;
          res_l = l;
        }

        l--;
        r++;
      }

      l = i;
      r = i + 1;

      while (l >= 0 && r < s.length() && s[l] == s[r]) {
        if (r - l > res_r - res_l) {
          res_r = r;
          res_l = l;
        }

        l--;
        r++;
      }
    }
    return s.substr(res_l, (res_r - res_l) + 1);
  }
};

/* Dynamic programming. Note that a string is a palindrone iff its substrings is
 * a palindrome and the left and right side are the same. We can use this
 * information to do dynamic programming. Note that we keep track of the largest
 * palindrome all the time, otherwise we need to search to whole data structure
 * in the end. */

/* A double pointer approach is also possible here, and another optimal solution
 * with O(1) space is possible*/
