#include <stdio.h>
#include <string.h>
#include <unordered_map>

#include <vector>

class Solution {
public:
  /* Idea: Greedy approach that uses recursion. For efficiency, we use a hashmap
   * / vector count.
   * Base case: results non empty, we are done. If current path
   * is done, if it is a valid solution, we save it into results, and we are
   * done. By construction, the first valid path we create will be the smallest
   * path that is larger than the target
   *
   * Induction: Iterative through all possible characters that can still be
   * used. if the character has count 0, we skip. If current path is not larger
   * than target and adding a new character will make it smaller, we skip.
   *
   * Otherwise, we push the new character into the path, update the character
   * count, check whether the current path is larger than target. And we run
   * recursion to explore this current path. If this path returns true, we are
   * done.
   *
   * Otherwise, we backtrack by popping the last element in the path and
   * updating the character count. The for loop will go to the next iteration
   *
   * Overall: We iterate over all possible current starting points and use
   * recursion to explore that possible path. If that possible path is valid, we
   * have found the solution and we stop
   * */
  std::string lexGreaterPermutation(std::string s, std::string target) {
    std::vector<int> cnt(26, 0);
    for (const char &c : s) {
      cnt[c - 'a']++;
    }

    std::vector<char> path;
    funct(cnt, path, target, false);

    return res;
  }

private:
  std::string res;

  bool funct(std::vector<int> &cnt, std::vector<char> &path,
             const std::string target, bool big) {
    if (!res.empty()) {
      return true;
    }

    int n = target.size();
    if (path.size() == n) {
      if (big) {
        res = std::string(path.begin(), path.end());
        return true;
      }
      return false;
    }

    int curr_size = path.size();
    for (int c = 0; c < 26; ++c) {
      if (cnt[c] == 0) {
        continue;
      }

      if (!big && (c + 'a' < target[curr_size])) {
        continue;
      }

      path.push_back(c + 'a');
      cnt[c]--;
      bool new_big = big || (c + 'a' > target[curr_size]);

      if (funct(cnt, path, target, new_big)) {
        return true;
      }
      path.pop_back();
      cnt[c]++;
    }

    return false;
  }
};

// Side learning; class to find all permutations
class Practice {
public:
  void findPermutations(std::string s, int index) {
    if (index == s.length())
      res.emplace_back(s);

    for (int start = index; start < s.length(); ++start) {
      // Note that the initial string is also saved, since swap with itself does
      // nothing
      std::swap(s[index], s[start]);
      findPermutations(s, index + 1);
      std::swap(s[index], s[start]);
    }
  }

private:
  std::vector<std::string> res;
};

class efficient_solution {
public:
  std::string lexGreaterPermutation(std::string s, std::string target) {
    std::vector<int> cnt(26, 0);
    for (const char c : s) {
      cnt[c - 'a']++;
    }

    std::vector<char> path;
    greedy(cnt, path, target, false);

    return res;
  }

private:
  std::string res;
  bool greedy(std::vector<int> &cnt, std::vector<char> &path,
              const std::string &target, bool big) {

    int n = target.length();
    if (!res.empty()) {
      return true;
    }

    if (path.size() == n) {
      if (big) {
        res = std::string(path.begin(), path.end());
        return true;
      }
      return false;
    }

    int curr = path.size();
    for (int i = 0; i < 26; ++i) {
      if (cnt[i] == 0) {
        continue;
      }

      if (!big && ('a' + i < target[curr])) {
        continue;
      }

      path.push_back('a' + i);
      cnt[i]--;

      bool new_big = big || ('a' + i) > target[curr];

      if (greedy(cnt, path, target, new_big)) {
        return true;
      }

      path.pop_back();
      cnt[i]++;
    }

    return false;
  }
};
