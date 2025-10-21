#include <iostream>
#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Continuously take the last digit of the number, store the number * power of
   * 10 each time. Note that we need to delete the last digit, divide the number
   * by 10 and increment the10 power each time*/
  std::vector<int> decimalRepresentation(int n) {
    long long power_ten = 1;
    std::vector<int> res;

    while (n > 0) {
      int digit = n % 10;

      if (digit > 0) {
        res.emplace_back(digit * power_ten);
      }

      n /= 10;
      power_ten *= 10;
    }
    std::reverse(res.begin(), res.end());
    return res;
  }
};

int main() {
  int test = 6;
  Solution s;
  std::vector<int> res = s.decimalRepresentation(test);

  for (int i = 0; i < res.size(); ++i) {
    std::cout << res[i] << std::endl;
  }

  return 0;
}

/* Takeaways; do one digit by one digit. Can use log 10, or string conversion.
 * However log10 is a difficult math calculation we ideally want to avoid and
 * string conversion is a heap memory allocation (this is a system call). Better
 * to do small digits to large digits and do a reverse of an array, which is
 * reasonably fast for an array */

/* Other; have an idea for every part of the code, and test some simple test
 * cases quickly before actually writing out the code */
