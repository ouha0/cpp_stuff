#include <iostream>
#include <stdio.h>

const int MAX_N = 10000;
const int LOG = 17;
int a[MAX_N];
int m[MAX_N][LOG];

int query(int L, int R) {
  int length = R - L + 1;
  int k = 0;

  /* Finding largest power of 2 s.t. it is less than the length*/
  while ((1 << (k + 1)) < length) {
    k++;
  }

  return std::min(m[L][k], m[R - (1 << k)][k]);
}

int main() {
  int n;
  std::cin >> n;

  // Reading input
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    m[i][0] = a[i];
  }

  // preprocessing
  for (int k = 0; k < LOG; ++k) {
    for (int i = 0; i + (1 << k) - 1 < n; ++i) {
      m[i][k] = std::min(m[i][k - 1], m[i + (1 << (k - 1))][k - 1]);
    }
  }

  /* Answering range queries */
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int L, R;
    std::cin >> L >> R;
    std::cout << query(L, R) << "\n";
  }
}

/* Features of sparse tables
 *
 * O(1) efficient range queries.
 * m[i][j] is typically asking from ith index until ith index + 2^j, what is the
 * minimum element (m represents the minimum in this case) We can work this out
 * via dynamica programming; using m[i][j] = m[i][j - 1], m[i + 2 ^ (j - 1)][j -
 * 1]
 * This is efficiently computed, iterating over i, and then j. j is efficiently
 * computed, because j computation requires j - 1 computations, which was
 * already computed
 *
 *
 * Note that 1 << k is 2 ^ k
 * */
