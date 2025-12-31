#include <algorithm>
#include <stdio.h>
#include <vector>

/* Standard library ordering:
 * less: a < b
 * greater: a > b
 * where a is the first element, b is the second element
 *
 *
 * For standard sorting; less is ascending, greater is descending order
 *
 * For heaps / priority queues; less is max heap, greater is minheap
 * less means the highest priority is the largest number
 * greater means the highest prriority is the samllest number
 *
 *
 * Note that lamda functions don't work immediately in the third heap argument.
 * You need to use a struct, or decltype
 * */

class MinHeap {
private:
  std::vector<int> heap;

  void siftup(int n) {
    while (n > 0) {
      int parent = (n - 1) / 2;

      // If current element is smaller than parent, swap positions with the
      // parent. Otherwise, the current heap order is correct
      if (heap[n] < heap[parent]) {
        std::swap(heap[parent], heap[n]);
        n = parent;
      } else {
        break;
      }
    }

    return;
  }

  /* We use the left child to check the boundaries of the children. Right child
   * cannot exist without left */
  void siftdown(int n) {

    // We can use left child for the bound, since the right child cannot exist
    // without the left child
    while (2 * n + 1 < heap.size()) {
      // Child nodes
      int left = 2 * n + 1;
      int right = 2 * n + 2;

      int target = left;

      if (right < heap.size() && heap[right] < heap[left]) {
        target = right;
      }

      if (heap[n] > heap[target]) {
        std::swap(heap[n], heap[target]);
        n = target;
      } else {
        break;
      }
    }
  }

public:
  int top(void) {
    if (heap.empty()) {
      return -1;
    }
    return heap[0];
  }

  void push(int val) {
    heap.push_back(val);
    // Fix the order. Last element should go to correct position
    siftup(heap.size() - 1);
  }

  void pop(void) {
    if (heap.empty()) {
      return;
    }
    std::swap(heap[0], heap.back());
    heap.pop_back();

    siftdown(0);
  }

  bool isempty(void) { return heap.empty(); }
};
