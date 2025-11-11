#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Use a pointer type of method. For each character, find and count all its
   * palindromes. Note that each character has two possibilities; even and odd
   * length of palindromes. */
  int countSubstrings(std::string s) {
    int res = 0;

    for (int i = 0; i < s.length(); ++i) {
      int l = i;
      int r = i;
      while (l >= 0 && r < s.length() && s[l] == s[r]) {
        res++;

        l--;
        r++;
      }

      l = i;
      r = i + 1;

      while (l >= 0 && r < s.length() && s[l] == s[r]) {
        res++;

        l--;
        r++;
      }
    }
    return res;
  }
};
