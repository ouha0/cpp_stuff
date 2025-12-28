#include <stdio.h>

struct Problem {};

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
