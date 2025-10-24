#include <stdio.h>
#include <unordered_map>
#include <vector>

// This question was not coded from scratch. It was taken from a forum

namespace std {
class Solution {
public:
  /* Idea is to use a segment tree. Segment trees represent the odd and even
   * balance for some fixed range. Iterate over each number, and update the
   * segment tree using lazy propogation. At the end, if there is a valid left
   * most balance, update the result. Note that segment tree operations are
   * LogN, so the time complexity is NLog(N)*/
  int longestBalanced(vector<int> &nums) {
    SegmentTree seg(nums.size());
    // Hashmap storing the index of the previous instance of the number
    unordered_map<int, int> prev_idx;
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      /* Iterate over each number, generating a segment tree for [l, i] for all
       * l that is smaller than i
       * */

      int val = nums[i] & 1 ? -1 : 1; // 1 if even, -1 if odd

      /* If current number is seen before, subtract value to all ranges that
       * includes the previous index
       * i.e. for all ranges [l, i], where prev_idex, we subtract the balance
       * here by val. We subtract it so we can add it to everything in the range
       * later on
       * */
      if (prev_idx.count(nums[i])) {
        seg.update(0, 0, prev_idx[nums[i]], -val);
      }
      // Add value to balance of all ranges [l, i] for all l < i
      seg.update(0, 0, i, val);

      // Find the left most index for [left_idex, i] s.t. the balance is zer0
      int left_idx = seg.find_left_most_idx(0);
      // We just saw nums[i], save this number and index for future
      prev_idx[nums[i]] = i;
      // If a left most index that forms a balanced range is found, update the
      // max
      if (left_idx != -1) {
        res = max(res, i - left_idx + 1);
      }
    }
    return res;
  }

private:
  class SegmentTree {
  public:
    SegmentTree(uint32_t size)
        : _size(size), _min_tree(size * 4), _max_tree(size * 4),
          _lazy(size * 4) {}
    void update(int node, int left_idx, int right_idx, int val,
                int seg_left = -1, int seg_right = -1) {
      push(node, seg_left, seg_right);
      if (seg_right == -1) {
        seg_left = 0, seg_right = _size - 1;
      }
      if (left_idx > seg_right || right_idx < seg_left) {
        return;
      }
      if (seg_left >= left_idx && seg_right <= right_idx) {
        _lazy[node] += val;
        push(node, seg_left, seg_right);
        return;
      }
      int mid = seg_left + (seg_right - seg_left) / 2;
      update(node * 2 + 1, left_idx, right_idx, val, seg_left, mid);
      update(node * 2 + 2, left_idx, right_idx, val, mid + 1, seg_right);
      _min_tree[node] = min(_min_tree[node * 2 + 1], _min_tree[node * 2 + 2]);
      _max_tree[node] = max(_max_tree[node * 2 + 1], _max_tree[node * 2 + 2]);
    }
    int find_left_most_idx(int node, int seg_left = -1, int seg_right = -1) {
      if (seg_left == -1) {
        seg_left = 0, seg_right = _size - 1;
      }
      push(node, seg_left, seg_right);
      if (_min_tree[node] > 0 || _max_tree[node] < 0) {
        return -1;
      }
      if (seg_left == seg_right) {
        return _max_tree[node] == 0 ? seg_left : -1;
      }
      int mid = seg_left + (seg_right - seg_left) / 2;
      if (int idx = find_left_most_idx(node * 2 + 1, seg_left, mid);
          idx != -1) {
        return idx;
      }
      return find_left_most_idx(node * 2 + 2, mid + 1, seg_right);
    }

  private:
    int _size;
    vector<int> _min_tree, _max_tree, _lazy;
    void push(int node, int seg_left, int seg_right) {
      if (_lazy[node] == 0)
        return;
      _min_tree[node] += _lazy[node];
      _max_tree[node] += _lazy[node];
      if (seg_left != seg_right) {
        _lazy[node * 2 + 1] += _lazy[node];
        _lazy[node * 2 + 2] += _lazy[node];
      }
      _lazy[node] = 0;
    }
  };
};

} // namespace std
