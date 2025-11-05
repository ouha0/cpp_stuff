#include <algorithm>
#include <stdio.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {

  // The key for this is recognising this as a graph theory problem and using
  // post order dfs. More description at the end
public:
  std::string foreignDictionary(std::vector<std::string> &words) {
    std::unordered_map<char, std::unordered_set<char>> adj;

    for (const std::string &w : words) {
      for (const char c : w) {
        adj[c] = {};
      }
    }

    for (int i = 0; i < words.size() - 1; ++i) {
      std::string &w1 = words[i];
      std::string &w2 = words[i + 1];

      std::string_view w1_view(w1);
      std::string_view w2_view(w2);
      int min_length = std::min(w1.length(), w2.length());
      if (w1.length() > w2.length() &&
          w1_view.substr(0, min_length) == w2_view.substr(0, min_length)) {
        return {};
      }

      for (int j = 0; j < min_length; ++j) {
        if (w1[j] != w2[j]) {
          adj[w1[j]].insert(w2[j]);
          break;
        }
      }
    }
    std::vector<char> res;
    std::unordered_map<char, bool> visited;

    for (const auto &[key, _] : adj) {
      if (dfs(key, res, visited, adj)) {
        return {};
      }
    }

    std::reverse(res.begin(), res.end());
    return std::string(res.begin(), res.end());
  }

private:
  bool dfs(char c, std::vector<char> &res,
           std::unordered_map<char, bool> &visited,
           std::unordered_map<char, std::unordered_set<char>> &adj) {
    auto it = visited.find(c);
    if (it != visited.end()) {
      return it->second;
    }

    visited[c] = true;

    for (const char &n : adj[c]) {
      if (dfs(n, res, visited, adj)) {
        return true;
      }
    }
    visited[c] = false;
    res.emplace_back(c);
    return false;
  }
};

class Solution_copy {
public:
  std::string foreignDictionary(std::vector<std::string> &words) {
    std::unordered_map<char, std::unordered_set<char>> adj;
    for (const std::string &w : words) {
      for (const char c : w) {
        adj[c] = {};
      }
    }

    for (int i = 0; i < words.size() - 1; ++i) {
      std::string &w1 = words[i];
      std::string &w2 = words[i + 1];

      std::string_view w1_view(w1);
      std::string_view w2_view(w2);

      int min_length = std::min(w1.length(), w2.length());
      if (w1.length() > w2.length() &&
          w1_view.substr(0, min_length) == w2_view.substr(0, min_length)) {
        return {};
      }

      for (int j = 0; j < min_length; ++j) {
        if (w1[j] != w2[j]) {
          adj[w1[j]].insert(w2[j]);
          break;
        }
      }
    }

    std::string res;
    std::unordered_map<char, bool> visited;

    for (const auto &[key, _] : adj) {
      // Slight optimisation to avoid calling dfs for already called keys
      if (visited.find(key) == visited.end()) {
        if (dfs(key, res, visited, adj)) {
          return {};
        }
      }
    }

    reverse(res.begin(), res.end());
    return res;
  }

private:
  bool dfs(char c, std::string &res, std::unordered_map<char, bool> &visited,
           std::unordered_map<char, std::unordered_set<char>> &adj) {
    if (visited.find(c) != visited.end()) {
      return visited[c];
    }

    visited[c] = true;
    for (const char n : adj[c]) {
      if (dfs(n, res, visited, adj)) {
        return true;
      }
    }
    visited[c] = false;
    res.push_back(c);

    return false;
  }
};

/* dfs is a personal weak area; should practice more dfs logic, and have better
 * understanding of recursion and the call stack
 *
 * There are many key areas to this problem. A directed edge a -> b indicating b
 * comes after a. We can create a directed graph from the information given.
 * Note that the graph may have disconnected components / lone characters
 * (meaning that this character can go anywhere). Hence we need to remember to
 * initialise every character that appears in a word. We must also remember the
 * edge case where if a word has the same prefix as another word and is longer,
 * it must lexigraphically go after the other word
 *
 * Once we have constructed the graph. We can run dfs, adding elements in post
 * order (elements with words that are lexigraphically the largest in the
 * current set). We use res to keep track of the post order traversal, and use
 * visited hashmap to identify whether a word has been visited (in / not in the
 * current path). We use this hashmap to identify whether a new node is already
 * on the current path, indicating there is a cycle, meaning that the
 * lexigraphical ordering is not well defined, so we can just end the function
 * call
 *
 * */
