#include <functional>
#include <queue>
#include <stdio.h>
#include <unordered_map>
#include <vector>

class Solution {
public:
  bool isNStraightHand(std::vector<int> &hand, int groupSize) {
    if (hand.size() % groupSize != 0) {
      return false;
    }

    std::sort(hand.begin(), hand.end());

    std::unordered_map<int, int> freq_count;
    for (const int h : hand) {
      freq_count[h]++;
    }

    for (const int count : hand) {
      if (freq_count[count] > 0) {
        for (int i = count; i < count + groupSize; ++i) {
          if (freq_count.count(i) > 0 && freq_count[i] == 0) {
            return false;
          } else {
            freq_count[i]--;
          }
        }
      }
    }
    return true;
  }
};

class solution_make_heap {
public:
  bool isNStraightHand(std::vector<int> &hand, int groupSize) {
    if (hand.size() % groupSize != 0) {
      return false;
    }
    std::unordered_map<int, int> count;
    for (const int h : hand) {
      count[h]++;
    }

    // This does not work, since we need to make a heap out of the unordered_map
    // keys
    std::vector<int> heap;
    heap.reserve(count.size());
    for (const auto &[key, _] : count) {
      heap.push_back(key);
    }

    std::make_heap(heap.begin(), heap.end(), std::greater<int>{});
    while (!heap.empty()) {
      int first = heap[0];
      for (int i = first; i < first + groupSize; ++i) {
        if (count.find(i) == count.end()) {
          return false;
        }
        count[i]--;
        if (count[i] == 0) {
          if (i != heap[0]) {
            return false;
          }
          std::pop_heap(heap.begin(), heap.end(), std::greater<int>{});
          heap.pop_back();
        }
      }
    }

    return true;
  }
};

class solution_heap {
public:
  bool isNStraightHand(std::vector<int> &hand, int groupSize) {
    if (hand.size() % groupSize != 0) {
      return false;
    }

    std::unordered_map<int, int> count;
    for (const int &h : hand) {
      count[h]++;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (const auto &[key, _] : count) {
      pq.push(key);
    }

    while (!pq.empty()) {
      int start = pq.top();

      for (int i = start; i < start + groupSize; ++i) {
        if (count.count(i) == 0) {
          return false;
        }
        count[i]--;
        if (count[i] == 0) {
          if (pq.top() != i) {
            return false;
          }
          pq.pop();
        }
      }
    }
    return true;
  }
};

/* Important to name variables nicely, otherwise it is easy to mess up the logic
 */
