#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using ll = long long;

const int MOD = 1e9 + 7;
const int INF = 1e9;

/* Idea: construct a vector of numbers and its index pair. Sort them.
 * Iterate through each number, and do double pointer approach, to
 * find the other two numbers that can form the number. If number too large,
 * reduce right pointer, if too small, increase left pointer */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, x;
  std::cin >> n >> x;

  std::vector<std::pair<int, int>> numbers(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> numbers[i].first;
    numbers[i].second = i;
  }

  std::sort(numbers.begin(), numbers.end());
  for (int i = 0; i < n; ++i) {
    int start = numbers[i].first;
    int target = x - start;

    int l = i + 1;
    int r = n - 1;
    while (l < r) {
      int sum = numbers[l].first + numbers[r].first;
      if (sum < target) {
        l++;
      } else if (sum > target) {
        r--;
      } else {
        std::cout << numbers[i].second + 1 << " " << numbers[l].second + 1
                  << " " << numbers[r].second + 1 << "\n";
        return 0;
      }
    }
  }

  std::cout << "IMPOSSIBLE" << "\n";

  return 0;
}

/* Key: Use a double pointer approach. This double pointer approach is
 * more efficient that using a hashmap... and its hard to deal with the hashmap
 * indices when they are duplicate keys, and whether an indice has been seen
 * before (depends the order we iterate)*/
