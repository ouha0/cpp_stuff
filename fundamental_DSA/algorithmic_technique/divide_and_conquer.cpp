#include <stdio.h>
#include <vector>

struct Problem {};

/* General notion:
 * Divide a large problem into smaller problems (same problem, but "smaller").
 * One we solve the "smaller" / partial problems, we need to have a method to
 * combine the subsolutions.
 *
 * Divide and conquer is splitting problems into their smallest unit, solving
 * it, and then combining the smallest solution unit into a more complete
 * solution
 *
 * */

/* General divide and conquer technique */
void solve(Problem p) {
  // Base case logic
  if (p.size() <= 1) {
    return base_logic(p);
  }

  // Divide the problem
  auto [sub1, sub2] = split(p);

  // Conquer / solve the subproblem
  auto res1 = solve(sub1);
  auto res2 = solve(sub2);

  // combine the partial solution
  return merge(res1, res2);
}

/* Merge sort algorithm */
class sort {
  std::vector<int> arr;

  // Combinting partiall solved solutions; Merging two partially subproblems
  void merge(std::vector<int> &arr, int l, int m, int r) {
    std::vector<int> tmp;

    int i = l;
    int j = m + 1;

    // combine to sorted vectors into one
    while (i <= m && j <= r) {
      if (arr[i] <= arr[j]) {
        tmp.push_back(arr[i]);
        i++;
      } else {
        tmp.push_back(arr[j]);
        j++;
      }
    }

    // Push leftover elements into the array
    while (i <= m) {
      tmp.push_back(arr[i]);
      i++;
    }

    while (j <= r) {
      tmp.push_back(arr[j]);
      j++;
    }

    // Copy tmporary vector elements into array
    for (int k = 0; k < tmp.size(); ++k) {
      arr[l + k] = tmp[k];
    }
  }

  // merge sort recursive logic
  void merge_sort(std::vector<int> &arr, int l, int r) {
    if (l >= r) {
      return;
    }

    int m = l + (r - l) / 2;
    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, r);

    merge(arr, l, m, r);
  }

  void sort_vector(std::vector<int> &arr) {
    if (arr.empty()) {
      return;
    }

    merge_sort(arr, 0, arr.size() - 1);
  }
};
