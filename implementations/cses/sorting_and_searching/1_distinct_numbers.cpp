#include <iostream>
#include <set>
#include <stdio.h>
#include <unordered_set>

int main() {
  std::ios_base::sync_with_stdio(false);

  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::set<int> set;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    set.insert(x);
  }
  std::cout << set.size() << std::endl;

  return 0;
}
