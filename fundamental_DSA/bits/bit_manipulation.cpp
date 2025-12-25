#include <bitset>
#include <iostream>
#include <stdio.h>

class Register {
private:
  uint32_t value;

public:
  Register(uint32_t initial_val = 0) : value(initial_val) {};

  // set a bit (make it one)
  void setBit(int pos) { value |= (1U << pos); }

  // clear bit
  void clearBit(int pos) { value &= ~(1U << pos); }

  // toggle bit; make 0 -> 1, 1 -> 0
  void togglebit(int pos) { value ^= (1U << pos); }

  // check a bit
  bool checkBit(int pos) const { return (value & (1U << pos)) == 1; }

  // Extract a raneg of bits
  uint32_t extract(int start, int length) const {
    // get 1000.. -> 011111 and then use & to extract the bits we want
    uint32_t mask = (1U << length) - 1;
    return (value >> start) & mask;
  }

  void print() const {
    std::cout << "Value: " << value << " (Binary: )" << std::bitset<32>(value)
              << ")" << std::endl;
  }
};
