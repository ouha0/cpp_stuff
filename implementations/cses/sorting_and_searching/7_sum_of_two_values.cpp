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

/* Idea: So our goal is to find the target sum given an array
 * We could construct a hashmap mapping its value to its index
 * which is O(N) and then iterating through the integers, and trying to find its
 * target value. Note that this hashmap approach becomes very messy when there
 * are muliple indices for the same value. This would mean that we need to
 * manually update the hashmap as we go. And the hashmap would be <int,
 * vector<int>>. The greedy approach is better
 *
 * Another method is perhaps sorting the array and doing a double pointer
 * approach
 *
 * */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  // Sorting the array, using double pointer, and vector of pairs to preserve
  // initial index

  int n, target;
  std::cin >> n >> target;

  std::vector<std::pair<int, int>> numbers(n);
  for (int i = 0; i < n; ++i) {
    int tmp;
    std::cin >> tmp;
    numbers[i] = std::make_pair(tmp, i);
  }

  std::sort(numbers.begin(), numbers.end());
  int l = 0;
  int r = n - 1;
  while (l < r) {
    int sum = numbers[l].first + numbers[r].first;
    if (sum == target) {
      std::cout << numbers[l].second + 1 << " " << numbers[r].second + 1
                << "\n";
      return 0;
    } else if (sum < target) {
      l++;
    } else {
      r--;
    }
  }
  std::cout << "IMPOSSIBLE" << "\n";

  /*
  int n, target;
  std::cin >> n >> target;
  std::vector<int> numbers(n);
  int tmp;

  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    numbers[i] = tmp;
  }

  std::unordered_map<int, std::vector<int>> value_index_map;
  for (int i = 0; i < n; ++i) {
    value_index_map[numbers[i]].push_back(i);
  }

// Logic is wrong here. Need to temporary erase a index here first, before
searching for the
// target value
  for (const int &n : numbers) {
    if (value_index_map.count(target - n) > 0) {
      std::cout << value_index_map[n] + 1 << " "
                << value_index_map[target - n] + 1 << "\n";
      return 0;
    }
  }
  std::cout << "IMPOSSIBLE" << "\n";
  */

  return 0;
}

/* Bug here: we want the original index, no the index after the array was
 * sorted. So we either need a hashmap to store the original indices (we lose
 * some information when values are non-unique). Another way is to store the
 * values with its initial index as a pair, and sort based on the first value*/
