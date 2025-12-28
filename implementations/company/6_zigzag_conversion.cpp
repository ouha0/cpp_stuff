#include <stdio.h>
#include <string>

/* Plan
 * Seems like a mathematical question. If we can work out the pattern, we can
 * construct the string rowwise. This would make it O(N)
 *
 * row 3 -> 3 + 1
 * row 4 -> 4 + 2
 * row 5 -> 5 + 3
 *
 * row + row - 2 = 2 * row  - 2 for the first row.
 * last row is the same. The more interesting case
 * is the middle rows
 * middle rows will be the same, but with extra i.e.
 * x + 1, x + 2 ... x + row - 3
 * */

class Solution {
public:
  std::string convert(std::string s, int numRows) {
    std::string res;

    for (int i = 0; i < numRows; ++i) {
    }

    return res;
  }
};
