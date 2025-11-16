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

/* The key insight to this question is that the initial ORDERING DOES NOT MATTER
 * and we can only use each number once when creating a subsequence; this hint
 * that sorting may be useful. We can use a combinatorital approach to find all
 * subsequences. For each element, we create a frequency map for it. For each
 * element, we have the choice of using the element {1st ... frequencyth
 * element} or not use it. This is the same for every other element. Using
 * these different elements are independent, so we can multiply them to get the
 * solution. Remember there is 1 case where every number is not used. We need to
 * ignore this case
 *
 * Note that iterating one by one doesn't really work. If a number has not been
 * seen, we know that we can do res = 2 *res + 1, since we can add a new number
 * to every previous element and the number itself alone. However, if a number
 * has been seen previously n times, we need to know how many of the previous
 * sequences uses this number. This is the point where we can stuck. Lets
 * say some number appears lots of times in the start, and doesn't appear in the
 * middle and appears a lot in the end. Lots of sequences in the middle would
 * have used the number we want to ignore. It is hard to identify how many
 * sequences don't use that number (doesn't seem to be a fixed formula)
 *
 * There are two ways we can contruct the frequency map, either using an array
 * and sorting it or using a frequency map and then iterating over it (iterating
 * is slow, especially with lots of collisions; may become O(N^2))
 * */

/* Iterate over sorted array -> if current number is same as previous number, we
 * increment the frequency
 * -> if current number is different, we add the current ccombination into the
 * results count -> and update the frequency back to 0 (frequency will go to 1
 * outside the if statement). When the for loop eneds, the largest number
 * combination is not included yet, so we include that in */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  int tmp;
  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    nums[i] = tmp;
  }

  std::sort(nums.begin(), nums.end());
  ll res = 1;

  int freq = 1;
  for (int i = 1; i < n; ++i) {
    if (nums[i] != nums[i - 1]) {
      res *= (freq + 1);
      res %= MOD;
      freq = 0;
    }
    freq++;
  }
  res *= (freq + 1);
  res = (res - 1 + MOD) % MOD;

  std::cout << res << "\n";
}

/* KEY: Order does not matter. We are either using the element or not.
 * this is a combinatorics problem, where we have frequency choices + 1 for each
 * unique number
 * Also don't forget to subtract 1 from the final result, since the combinations
 * includes the case where every unique number is not used
 * */
