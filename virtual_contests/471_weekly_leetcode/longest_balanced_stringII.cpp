#include <stdio.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// Same as previous question but stronger memory constraints

struct triple {
  int a;
  int b;
  int c;
};

class Solution {
public:
  /* Build a prefix sum of a, b, c of frequency counts. P[i] will represent the
   * S[0, ..., i- 1] count.
   * The key to this problem is a mathematical trick. By algebra and
   * rearranging, we can simplify the O(N^2) to an O(N) condition check, using a
   * hashmap. For example One possible case is a solution involving only a's and
   * b's. If a particular range [i, j-1] is a solution. It would mean the a's
   * and b's in this range are equal i.e. S[j] - S[i] meaning that a_j - a_i ==
   * b_j - b_i. c_j - c_i == 0 since this case has no c's -> c_j = c_i
   * Rearranging this gives us a_j - b_j == a_i - b_i. We know that i < j. So if
   * we calculate a_j - b_j, and we find a previous index, say i, part of a's
   * and b's has a_i - b_i is equal to the jth calculation, then we know that we
   * have found a balanced pair (mathematically). Finding a previous instance
   * that gives the same value can be achieved using a hashmap.
   *
   * Now, we note that this was only on one particular case, "a's and b's". In
   * total there are 8 cases, for each of the 3 letters, we either choose to
   * include it or not. We need to calculate the algebra for each of these
   * different cases
   *
   * */
  int longestBalanced(std::string s) {
    std::vector<triple> prefix_sum = {triple{0, 0, 0}};

    // Create the prefix sum
    for (int i = 0; i < s.length(); ++i) {
      prefix_sum.push_back(prefix_sum.back());

      if (s[i] == 'a') {
        prefix_sum.back().a++;

      } else if (s[i] == 'b') {
        prefix_sum.back().b++;

      } else if (s[i] == 'c') {
        prefix_sum.back().c++;
      }
    }

    int res = 0;
    std::unordered_map<std::tuple<std::string, int, int>, int> first;

    // Iterate over the prefix sum. Should be size N + 1
    for (int i = 0; i < prefix_sum.size(); ++i) {
      int a = prefix_sum[i].a;
      int b = prefix_sum[i].b;
      int c = prefix_sum[i].c;

      std::vector<std::tuple<std::string, int, int>> keys = {
          {"ab", a - b, c}, {"abc", a - b, a - c}, {"ca", c - a, b},
          {"bc", b - c, a}, {"a", b, c},           {"b", a, c},
          {"c", a, b}};

      for (const auto &key : keys) {
        // Update default to value (first time key was found) if exists
        auto it = first.find(key);
        int def = (it != first.end()) ? (it->second) : i;

        res = std::max(res, i - def);
        first.try_emplace(key, i); // insert if previously no value
      }
    }

    return res;
  }

private:
  std::vector<std::string> cases = {"abc", "ab", "bc", "ac", "a", "b", "c"};
};
