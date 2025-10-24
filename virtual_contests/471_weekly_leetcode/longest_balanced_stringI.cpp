#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class Solution {
public:
  /* O(N^2) solution: Outer loop reprenting starting point, inner loop
   * representing ending index. Each time, make sure that non-zero keys have the
   * same count */
  int longestBalanced(std::string s) {
    if (s.length() == 1) {
      return 1;
    }

    int res = 0;

    for (int i = 0; i < s.length(); ++i) {
      std::vector<int> freq_count(26, 0);
      freq_count[s[i] - 'a']++;
      int base_count = 1;
      for (int j = i + 1; j < s.length(); ++j) {
        int allowed = 1;

        freq_count[s[j] - 'a']++;
        if (s[j] == s[i]) {
          base_count++;
        }

        for (int count = 0; count < 26; ++count) {
          if (freq_count[count] == 0) {
            continue;
          } else {
            if (freq_count[count] != base_count) {
              allowed = 0;
              break;
            }
          }
        }

        if (allowed) {
          res = std::max(res, j - i + 1);
        }
      }
    }

    return res;
  }
};

int main() {
  Solution s;
  std::string test1 = "zzabccy";

  std::cout << s.longestBalanced(test1) << std::endl;

  return 0;
}
