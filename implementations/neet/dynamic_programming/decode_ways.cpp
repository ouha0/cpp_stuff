#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Idea is to use dynamic programming. Every state requires the information of
   * the previous two states. For each character, construct the dp array. */
  int numDecodings(std::string s) {
    int res = 0;

    if (s[0] == '0') {
      return 0;
    }

    std::vector<int> dp(s.length() + 1, 1);

    for (int i = 2; i < s.length() + 1; ++i) {
      int tmp = 0;

      if (s[i - 1] - '0' != 0) {
        tmp += dp[i - 1];
      }
      int two_num = std::stoi(s.substr(i - 2, 2));
      if (10 <= two_num && two_num <= 26) {
        tmp += dp[i - 2];
      }

      dp[i] = tmp;
    }

    return dp[s.length()];
  }
};

/* Key takewayws; find the optimal substructure. For each state, what other
 * states are required. This information should be saved / easily accessed.
 * Also, be very careful with off by one errors, especially if you define a
 * non-standard dp array for padding. The ith term may not correspond to the ith
 * term of the original string
 * */
