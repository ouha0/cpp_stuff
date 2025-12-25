#include <iostream>
#include <optional>
#include <stdexcept>
#include <stdio.h>

template <typename T> class RingBuffer {
private:
  std::vector<T> buffer;
  size_t head = 0;
  size_t tail = 0;
  size_t max_size;
  bool full = false;

public:
  explicit RingBuffer(size_t size) : buffer(size), max_size(size) {};

  void reset() {
    head = tail = 0;
    full = false;
  }

  bool isFull() const { return full; }

  bool isEmpty() const { return !full && (head == tail); }

  void push(T item) {
    buffer[tail] = item;

    // full means we will overwrite it. Move head to next element
    if (full) {
      head = (head + 1) % max_size;
    }

    tail = (tail + 1) % max_size;

    full = (head == tail);
  }

  std::optional<T> pop() {
    if (isEmpty()) {
      return std::nullopt;
    }

    T val = buffer[head];
    head = (head + 1) % max_size;
    // popped, then it definitely isn't fully anymore
    full = false;
    return val;
  }

  size_t capacity() const { return max_size; }
};
