#include <stdio.h>
#include <string>
#include <vector>

class Solution {
public:
  /* Idea: At each point, we can either partition and start a new string, or we
   * can continue without partitioning. This hints towards backtracking. We can
   * use an index i, to use as a base case to stop the recursion.
   *
   * if index is larger / equal to string length, we are done
   *
   * for i from index to the end of string, if (index, i) forms a palindrome,
   * insert into subset, and do recursion (explore all possibilities) of that
   * path. Now we backtrack.
   *
   * (This code explores when i = index, which is when a single element is
   * considered a palindrome). After exploring a specific dfs path, it will
   * backtrack, and perform dfs on a different branch, and then backtrack (and
   * repeat )
   *
   * */
  std::vector<std::vector<std::string>> partition(std::string s) {
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> partition;

    backtrack(res, s, 0, partition);

    return res;
  }

private:
  void backtrack(std::vector<std::vector<std::string>> &res, std::string &s,
                 int index, std::vector<std::string> &subset) {
    if (index >= s.length()) {
      res.push_back(subset);
      return;
    }

    for (int i = index; i < s.length(); ++i) {
      if (is_palindrome(s, index, i)) {
        subset.push_back(s.substr(index, i - index + 1));
        backtrack(res, s, i + 1, subset);
        subset.pop_back();
      }
    }
  }

  bool is_palindrome(std::string &s, int i, int j) {
    while (i <= j) {
      if (s[i] != s[j]) {
        return false;
      }
      i++;
      j--;
    }
    return true;
  }
};

class Solution_copy {
public:
  std::vector<std::vector<std::string>> partition(std::string s) {
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> part;

    backtrack(res, part, s, 0);
    return res;
  }

private:
  void backtrack(std::vector<std::vector<std::string>> &res,
                 std::vector<std::string> &part, const std::string &s,
                 int index) {
    if (index == s.length()) { // >= is not necessary
      res.push_back(part);
      return;
    }

    for (int i = index; i < s.length(); ++i) {
      if (is_palindrome(s, index, i)) {
        part.emplace_back(s.substr(index, i - index + 1));
        backtrack(res, part, s, i + 1);
        part.pop_back();
      }
    }
  }

  bool is_palindrome(const std::string &s, int i, int j) {
    // i <= j not necessary; if i == j, then it is guarenteed to be equal
    while (i < j) {
      if (s[i] != s[j]) {
        return false;
      }
      i++;
      j--;
    }

    return true;
  }
};
