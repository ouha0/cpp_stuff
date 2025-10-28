#include <cstdint>
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
    // Cannot use tuples here; tuples aren't hashable
    std::unordered_map<std::string, int> first;

    // Iterate over the prefix sum. Should be size N + 1
    for (int i = 0; i < prefix_sum.size(); ++i) {
      int a = prefix_sum[i].a;
      int b = prefix_sum[i].b;
      int c = prefix_sum[i].c;

      // This is too slow
      std::vector<std::string> keys = {
          "ab_" + std::to_string(a - b) + "_" + std::to_string(c),
          "abc_" + std::to_string(a - b) + "_" + std::to_string(a - c),
          "ca_" + std::to_string(c - a) + "_" + std::to_string(b),
          "bc_" + std::to_string(b - c) + "_" + std::to_string(a),
          "a_" + std::to_string(b) + "_" + std::to_string(c),
          "b_" + std::to_string(a) + "_" + std::to_string(c),
          "c_" + std::to_string(a) + "_" + std::to_string(b)};

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
};

class solution {
private:
  static constexpr uint64_t OFFSET = 100000;

  uint64_t hash(const std::tuple<int, int, int> &k) {
    auto [type, val1, val2] = k;
    uint64_t u_type = static_cast<uint64_t>(type);
    uint64_t u_val1 = static_cast<uint64_t>(val1);
    uint64_t uval2 = static_cast<uint64_t>(val2);

    return (u_type << 36) | (u_val1 << 18) | (uval2);
  }

public:
  int longestBalanced(std::string s) {
    std::vector<std::array<int, 3>> P;
    P.push_back({0, 0, 0});

    for (char c : s) {
      P.push_back(P.back());
      if (c == 'a') {
        P.back()[0]++;
      } else if (c == 'b') {
        P.back()[1]++;
      } else if (c == 'c') {
        P.back()[2]++;
      }
    }
    int ans = 0;
    std::unordered_map<uint64_t, int> first;

    for (int i = 0; i < P.size(); ++i) {
      int a = P[i][0];
      int b = P[i][1];
      int c = P[i][2];

      std::vector<std::tuple<int, int, int>> keys = {
          {7, a - b, c}, {6, a - b, a - c}, {5, b - c, a}, {4, c - a, b},
          {3, b, c},     {2, c, a},         {1, a, b}};

      for (const auto &key : keys) {
        auto it = first.find(hash(key));
        if (it != first.end()) {
          ans = std::max(ans, i - it->second);
        } else {
          first[hash(key)] = i;
        }
      }
    }

    return ans;
  }
};
