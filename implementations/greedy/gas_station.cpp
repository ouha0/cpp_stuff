#include <stdio.h>
#include <vector>

/* Idea: obvious solution is brute force and do a simulation. Another method is
 * greedy approach. */
class greedy_solution {
public:
  int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost) {
    int total_gas = 0;
    int total_cost = 0;

    for (const int g : gas) {
      total_gas += g;
    }
    for (const int c : cost) {
      total_cost += c;
    }

    if (total_cost > total_gas) {
      return -1;
    }

    int total = 0;
    int res = 0;
    for (int i = 0; i < gas.size(); ++i) {
      if (total < 0) {
        total = 0;
        res = i;
      }
      total += gas[i] - cost[i];
    }
    return res;
  }
};
