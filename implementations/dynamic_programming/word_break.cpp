#include <stdio.h>
#include <unordered_map>
#include <vector>

class Solution {
public:
  /* Two ideas; recursive dfs or dynamic programming, to save time. The
   * repeating susbtructure, is whether the string from index i until the end of
   * the string, can be solved
   *
   * Construct a hashmap to efficiently find whether a substring exists in the
   * dictionary Iterate the string backwards, check whether the string by
   * consulting the cache, until the start is reached.
   *
   * */

  bool wordBreak(std::string s, std::vector<std::string> &wordDict) {
    std::vector<bool> dp_mem(s.size() + 1, false);
    dp_mem[s.size()] = true;
    std::unordered_map<std::string, bool> word_map;

    for (const std::string &tmp_s : wordDict) {
      word_map[tmp_s] = true;
    }

    for (int i = s.size() - 1; i >= 0; --i) {
      for (int j = i + 1; j < s.size() + 1; ++j) {

        if (dp_mem[j] == true) {

          std::string tmp_substring = s.substr(i, j - i);
          if (word_map.count(tmp_substring)) {
            dp_mem[i] = true;
            break;
          }
        }
      }
    }

    return dp_mem[0];
  }
};

/*
 * Key takeaways:
 * Again identifying the optimal substructure is very important in dynamic
 * programming; decide whether to go top down or bottom up method. When you
 * notice time complexities are a bit high, think about hash tables, and whether
 * there is a repetitive action happening inside the code
 * */

/* C++ takeaways:
 * Note that when you query a hashtable with a key that previously didn't exist,
 * it automatically inserts a new element with the key. Hence to check key,
 * value existence, you should always use hash_table.count("key")
 * */
