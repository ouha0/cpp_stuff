#include <stdio.h>
#include <vector>

/* Idea: obvious solution is brute force and do a simulation. Another method is
 * greedy approach. We can also consider a diff array that is gas - cost */

class brute_force_solution {
public:
  int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost) {
    for (int start = 0; start < gas.size(); ++start) {
      int total = gas[start] - cost[start];
      if (total < 0) {
        continue;
      }

      int curr = (start + 1) % gas.size();
      while (curr != start) {
        total += gas[curr] - cost[curr];
        if (total < 0) {
          break;
        }
        curr = (curr + 1) % gas.size();
      }
      if (curr == start) {
        return start;
      }
    }
    return -1;
  }
};

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

class solution_copy {
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

    if (total_gas < total_cost) {
      return -1;
    }

    int total = 0;
    int res = 0;
    for (int i = 0; i < gas.size(); ++i) {
      if (total < 0) {
        res = i;
        total = 0;
      }
      total += gas[i] - cost[i];
    }
    return res;
  }
};

/* This questions is quite hard, but kinda intuitive? */
