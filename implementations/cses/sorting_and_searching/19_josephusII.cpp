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

void build(std::vector<int> &tree, int v, int tl, int tr);
void update(std::vector<int> &tree, int v, int tl, int tr, int pos,
            int new_val);
int find_kth(std::vector<int> &tree, int v, int tl, int tr, int k);

/* Don't really undertand this qs...
 *
 * This problem requires using segment trees to achieve O(LOGN), and efficiently
 * find the kth remaining element each time. */

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, k;
  std::cin >> n >> k;
  std::vector<int> tree(4 * n);

  build(tree, 1, 1, n);

  int start_pos = 0;
  for (int i = 0; i < n; ++i) {
    int remaining_size = tree[1];

    int pos_rem = (start_pos + k) % remaining_size;
    int kth = pos_rem + 1;
    int actual_child = find_kth(tree, 1, 1, n, kth);
    std::cout << actual_child << " ";
    update(tree, 1, 1, n, actual_child, 0);
    start_pos = pos_rem;
  }

  std::cout << "\n";

  return 0;
}

/* Segment tree build: v is index of current node in tree
 * tl, tr = "tree left" and "tree right" bounds.
 * tree[v] stores the count of children still in the circle within its range
 * [i, i] = 1 if child i is inside, or 0 (child i removed)
 * */
void build(std::vector<int> &tree, int v, int tl, int tr) {
  if (tl == tr) {
    tree[v] = 1;
  } else {
    int tm = tl + (tr - tl) / 2;

    build(tree, 2 * v, tl, tm);
    build(tree, 2 * v + 1, tm + 1, tr);

    tree[v] = tree[2 * v] + tree[2 * v + 1];
  }
}

void update(std::vector<int> &tree, int v, int tl, int tr, int pos,
            int new_val) {
  if (tl == tr) {
    tree[v] = new_val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      update(tree, 2 * v, tl, tm, pos, new_val);
    } else {
      update(tree, 2 * v + 1, tm + 1, tr, pos, new_val);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
  }
}

int find_kth(std::vector<int> &tree, int v, int tl, int tr, int k) {
  if (tl == tr) {
    return tl;
  }

  int tm = tl + (tr - tl) / 2;
  int left_count = tree[2 * v];

  if (k <= left_count) {
    return find_kth(tree, 2 * v, tl, tm, k);
  } else {
    return find_kth(tree, 2 * v + 1, tm + 1, tr, k - left_count);
  }
}
