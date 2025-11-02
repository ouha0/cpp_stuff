#include <queue>
#include <stdio.h>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
public:
  /* Idea: generate a hashmap of "patterns" mapping to words that are distance
   * one from the pattern. Then for do bfs until we find the end word. For each
   * word generate the patterns, and hash the pattern to find potential matches,
   * add them into queue until we find a word that matches with endWord
   * */
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string> &wordList) {

    std::unordered_map<std::string, std::vector<std::string>> pattern_match;
    std::unordered_set<std::string> word_set;

    for (const std::string &word : wordList) {
      word_set.insert(word);
    }

    if (!word_set.count(endWord)) {
      return 0;
    }

    for (const std::string &word : word_set) {
      std::vector<std::string> patterns = generate_patterns(word);

      for (const std::string &pattern : patterns) {
        pattern_match[pattern].push_back(word);
      }
    }

    std::queue<std::string> q;
    int d = 1;
    std::unordered_set<std::string> visited;
    q.push(beginWord);
    visited.insert(beginWord);

    while (!q.empty()) {
      int n = q.size();
      d++;

      for (int i = 0; i < n; ++i) {
        std::string &curr = q.front();
        std::vector<std::string> patterns = generate_patterns(curr);

        for (const std::string &pattern : patterns) {
          for (const std::string &word : pattern_match[pattern]) {
            if (visited.count(word)) {
              continue;
            }
            if (word == endWord) {
              return d;
            }
            q.push(word);
            visited.insert(word);
          }
        }
        q.pop();
      }
    }

    return 0;
  }

private:
  std::vector<std::string> generate_patterns(std::string s) {
    std::vector<std::string> patterns;
    for (int i = 0; i < s.size(); ++i) {
      char save = s[i];
      s[i] = '*';
      patterns.push_back(s);
      s[i] = save;
    }
    return patterns;
  }
};

class Solution_cleanup {
  /* Slightly more cleaner version of the above. same idea
   * Generate pattern map data structure to get O(N)
   *
   * do bfs level by level. Start with d = 1.
   * pop the front of the queue, d++, generate words of distance 1.
   * if word is a match, return d. If a word has already been visited, skip,
   * otherwise push word into queue and insert into hash set as visited
   *
   * return 0 if there are no matches
   *
   * */
public:
  int ladderLength(std::string beginWord, std::string endWord,
                   std::vector<std::string> &wordList) {
    auto it = std::find(wordList.begin(), wordList.end(), endWord);
    if (it == wordList.end()) {
      return 0;
    }

    std::unordered_map<std::string, std::vector<std::string>> pattern_map;

    for (const std::string &word : wordList) {
      std::string copy = word;
      for (int i = 0; i < word.length(); ++i) {
        char save = word[i];
        copy[i] = '*';
        pattern_map[copy].push_back(word);
        copy[i] = save;
      }
    }

    std::unordered_set<std::string> visited;
    std::queue<std::string> q;
    int d = 1;

    q.push(beginWord);
    visited.insert(beginWord);

    while (!q.empty()) {
      int n = q.size();
      d++;

      for (int i = 0; i < n; ++i) {
        std::string curr = q.front();
        q.pop();
        visited.insert(curr);

        for (int i = 0; i < curr.size(); ++i) {
          char tmp = curr[i];
          curr[i] = '*';

          for (const std::string &word : pattern_map[curr]) {
            if (visited.count(word)) {
              continue;
            }

            if (word == endWord) {
              return d;
            }

            q.push(word);
          }
          curr[i] = tmp;
        }
      }
    }

    return 0;
  }
};
