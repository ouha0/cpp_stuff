#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
  /* Idea: Recursion / backtracking. If index is at the end, we are done, and we
   * push the partition into the result. Otherwise, find the index -> string
   * hashmap. Then for each character in the string, add it to the partition,
   * explore that "branch" (dfs), then backtrack.
   *
   * Note that if digits is emtpy, it wants empty vector, not a vector with ""
   * */
public:
  std::vector<std::string> letterCombinations(std::string digits) {
    if (digits.length() == 0) {
      return {};
    }

    std::vector<std::string> res;
    std::string part;
    backtrack(res, part, digits, 0);

    return res;
  }

private:
  void backtrack(std::vector<std::string> &res, std::string &part,
                 std::string &digits, int index) {
    if (index == digits.length()) {
      res.push_back(part);
      return;
    }

    auto it = digit_map.find(digits[index]);
    if (it != digit_map.end()) {
      std::string &s = it->second;
      for (int i = 0; i < s.length(); ++i) {
        part.push_back(s[i]);
        backtrack(res, part, digits, index + 1);
        part.pop_back();
      }
    } else {
      backtrack(res, part, digits, index + 1);
    }
  }
  std::unordered_map<char, std::string> digit_map = {
      {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
      {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
};
