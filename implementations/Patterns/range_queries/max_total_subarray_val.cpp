#include <set>
#include <stdio.h>
#include <vector>

/* Spare table template */
struct SparseTable {
private:
  int n;
  std::vector<std::vector<int>> mn;
  std::vector<std::vector<int>> mx;
  std::vector<int> logVal;

public:
  SparseTable(const std::vector<int> &a) {
    n = a.size();
    int maxLog = 32 - __builtin_clz(n);

    mn.assign(n, std::vector<int>(maxLog));
    mx.assign(n, std::vector<int>(maxLog));
    logVal.assign(n + 1, 0);

    for (int i = 2; i <= n; i++)
      logVal[i] = logVal[i / 2] + 1;

    for (int i = 0; i < n; i++) {
      mx[i][0] = a[i];
      mn[i][0] = a[i];
    }

    // O(2 * NLogN) sparse table construction
    for (int j = 1; (1 << j) <= n; j++) {
      for (int i = 0; i + (1 << j) <= n; i++) {
        mn[i][j] = std::min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
      }
    }

    for (int j = 1; (1 << j) <= n; j++) {
      for (int i = 0; i + (1 << j) <= n; i++) {
        mx[i][j] = std::max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  // O(1) range queries
  int queryMin(int l, int r) {
    int j = logVal[r - l + 1];
    return std::min(mn[l][j], mn[r - (1 << j) + 1][j]);
  }

  int queryMax(int l, int r) {
    int j = logVal[r - l + 1];
    return std::max(mx[l][j], mx[r - (1 << j) + 1][j]);
  }
};

class Solution {
public:
  long long maxTotalValue(std::vector<int> &nums, int k) {
    long long ans = 0;
    SparseTable st(nums); // O(N * Log(N))

    int n = (int)nums.size();
    std::multiset<std::pair<int, std::pair<int, int>>> s;
    // O(N)
    for (int i = 0; i < n; ++i) {
      s.insert({st.queryMax(0, i) - st.queryMin(0, i), {0, i}});
    }

    // O(k * LogN)
    while (k--) {
      int curr = s.rbegin()->first;
      int l = s.rbegin()->second.first;
      int r = s.rbegin()->second.second;
      // O(LogN)
      s.erase(s.find({curr, {l, r}}));

      // O(LogN)
      if (l + 1 <= r) {
        s.insert({st.queryMax(l + 1, r) - st.queryMin(l + 1, r), {l + 1, r}});
      }
      ans += curr;
    }
    return ans;
  }
};

/*
 * Construct a min and max sparse table
 * Take the largest element, add it to the solution and insert its subarray into
 * the multiset. Note that the structure makes sure that all subarrays are
 * uniquely generated The initial set of subarrays all have different right
 * ending points. All subsequent subarrays have different left end points. Note
 * that arrays that are a subset of some other array always has a smaller value
 * than its superset
 *
 *
 *
 * */
