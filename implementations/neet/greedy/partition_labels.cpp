#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
  /* Idea: greedy. Construct a hashmap frequency count. We iterate through the
   * string, and reduce the count each time. We add the elements into a
   * temporary hashset. Once we are sure that every element in the hashset has
   * frequency count 0, we can create a new hashset / start a new substring */
  std::vector<int> partitionLabels(std::string s) {
    std::vector<int> res;
    std::unordered_map<char, int> count;

    for (const char c : s) {
      count[c]++;
    }

    std::vector<char> substr;
    for (int c = 0; c < s.length(); ++c) {
      substr.push_back(s[c]);
      count[s[c]]--;

      if (count[s[c]] == 0) {
        if (substr_empty(substr, count)) {
          res.push_back(substr.size());
          substr = {};
        }
      }
    }

    return res;
  }

private:
  bool substr_empty(std::vector<char> &substr,
                    std::unordered_map<char, int> &count) {
    for (const char &c : substr) {
      if (count[c] != 0) {
        return false;
      }
    }
    return true;
  }
};
