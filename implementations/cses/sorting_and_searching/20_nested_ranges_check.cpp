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

struct Range {
  int l, r;
  int id;
};

/* This question can be solved via sorting, and then "sweeping across". This
 * means that it will be O(LOGN) + O(2N) + O(2N) The way we sort is sort by the
 * left boundary ascending order, and if the left boundary is the same, we sort
 * the right boundary by descending order (we need a lambda function to define
 * the ordering)
 *
 * Iterating left to right will allow us to solve the contained by problem. We
 * know every previous element has a smaller or equal left boundary, so we know
 * the left boundary of elements automatically satisfy the contained by
 * condition. We only need to focus on the right boundary. We keep a max_end,
 * storing the max right boundary. If there was a greater right boundary that
 * has already been seen. it means it has a smaller left boundary and a larger
 * right boundary -> this means that the current element can be contained
 *
 * Iterating right to left will allow us to solve the contains problem. We know
 * that the left boundary of all previous (right hand elements) are greater than
 * or equal to the current left boundary. This satisfies the left boundary
 * condition for containing some other element. All we need to figure out is
 * that the current element right boundary is larger than some / amy right
 * element of an element we have seen before (on the right hand side). We can
 * use a min_end variable to save the smallest right hand boundary we have seen
 * to figure this out. if the current element right boundary is larger (right
 * boundary contains some other element), the left element is automatically
 * satisfied, since all right hand elements have larger left boundaries
 *
 * */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::vector<Range> ranges(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> ranges[i].l >> ranges[i].r;
    ranges[i].id = i;
  }
  std::sort(ranges.begin(), ranges.end(), [](const Range &a, const Range &b) {
    if (a.l != b.l) {
      return a.l < b.l;
    }

    return b.r < a.r;
  });

  std::vector<int> contains(n, 0);
  std::vector<int> contained_by(n, 0);

  int min_end = std::numeric_limits<int>::max();
  for (int i = n - 1; i >= 0; --i) {
    if (ranges[i].r >= min_end) {
      contains[ranges[i].id] = 1;
    }
    min_end = std::min(min_end, ranges[i].r);
  }

  int max_end = 0;
  for (int i = 0; i < n; ++i) {
    if (ranges[i].r <= max_end) {
      contained_by[ranges[i].id] = 1;
    }
    max_end = std::max(max_end, ranges[i].r);
  }

  for (int i = 0; i < n; ++i) {
    std::cout << contains[i] << " ";
  }
  std::cout << "\n";

  for (int i = 0; i < n; ++i) {
    std::cout << contained_by[i] << " ";
  }
  std::cout << "\n";

  return 0;
}

/* Key: Sorting ascending by first element, and descending by second element,
 * gives us a useful property to determine whether a range contains some
 * other element, or is contained by some element. This is due to one side of
 * the range is automatically satisfied as we do a linear scan, we only need
 * to focus on one condition.
 * We must store the indices somewhere, either boolean array, or a hashset of
 * all valid indices. Hashset is most inefficient in the worst case, due
 * to pointers to the next element for collision handling and buckets (pointing
 * to start of lists) requiring more space. Boolean array is 1 bit, and is most
 * efficient
 * */
