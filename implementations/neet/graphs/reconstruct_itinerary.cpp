#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
  /* we want to build an adjacency list (hashmap allowing us to easily find
   * neighbours) with neighbours in order. We fix the neighbours in order
   * problem by sorting the tickets before inserting them. Then we can run
   * dfs to find all potential paths. The first valid path will be the solution,
   * since our neighbour map was sorted, so we run dfs in a sorted manner
   * */

  /* Using vectors was too slow so we use multiset */
  std::vector<std::string>
  findItinerary(std::vector<std::vector<std::string>> &tickets) {
    // std::sort(tickets.begin(), tickets.end());

    std::unordered_map<std::string, std::multiset<std::string>> nei_map;
    for (const auto &ticket : tickets) {
      nei_map[ticket[0]].insert(ticket[1]);
    }

    dfs("JFK", nei_map, tickets);

    return res;
  }

private:
  std::vector<std::string> res = {"JFK"};

  bool dfs(std::string s,
           std::unordered_map<std::string, std::multiset<std::string>> &nei_map,
           std::vector<std::vector<std::string>> &tickets) {
    if (res.size() == tickets.size() + 1) {
      return true;
    }

    if (nei_map.find(s) == nei_map.end()) {
      return false;
    }

    std::multiset<std::string> tmp = nei_map[s];

    for (const std::string &curr_s : tmp) {
      std::string copy = curr_s;
      auto it = nei_map[s].find(curr_s);
      if (it == nei_map[s].end()) {
        std::cout << "Somethings wrong" << std::endl;
      } else {
        nei_map[s].erase(it);
      }

      res.emplace_back(curr_s);

      if (dfs(copy, nei_map, tickets)) {
        return true;
      }

      nei_map[s].insert(curr_s);
      res.pop_back();
    }

    return false;
  }
};

class Solution_copy {
public:
  std::vector<std::string>
  findItinerary(std::vector<std::vector<std::string>> &tickets) {
    std::sort(tickets.begin(), tickets.end());

    std::unordered_map<std::string, std::vector<std::string>> nei_map;
    for (const auto &ticket : tickets) {
      nei_map[ticket[0]].emplace_back(ticket[1]);
    }

    dfs("JFK", nei_map, tickets.size() + 1);

    return res;
  }

private:
  std::vector<std::string> res = {"JFK"};

  bool dfs(std::string s,
           std::unordered_map<std::string, std::vector<std::string>> &nei_map,
           int ticket_size) {
    if (res.size() == ticket_size) {
      return true;
    }

    if (nei_map.find(s) == nei_map.end()) {
      return false;
    }

    std::vector<std::string> tmp_nei = nei_map[s];
    for (int i = 0; i < tmp_nei.size(); ++i) {
      std::string v = tmp_nei[i];
      nei_map[s].erase(nei_map[s].begin() + i);
      res.emplace_back(v);

      if (dfs(v, nei_map, ticket_size)) {
        return true;
      }

      nei_map[s].insert(nei_map[s].begin() + i, v);
      res.pop_back();
    }

    return false;
  }
};

class leetcode_solution_faster {
  /* Smart solution, but kinda hard to understand. Basically, the first element
   * to be added on the route is the position with no tickets. By design, the
   * call stack goes in reverse order. So we just need to reverse the route
   * to get the solution...
   * Requires quite a strong understanding of the call stack
   *
   * Key insight; The right path will "deadend" at the final destination.
   * And a location will only be added once it becomes a deadend, by the design of recursion / the call stack
   * */
public:
  std::vector<std::string>
  findItinerary(std::vector<std::vector<std::string>> &tickets) {
    std::map<std::string, std::multiset<std::string>> targets;
    std::vector<std::string> route;

    for (const auto ticket : tickets) {
      targets[ticket[0]].insert(ticket[1]);
    }
    visit("JFK", targets, route);

    return std::vector<std::string>(route.rbegin(), route.rend());
  }

private:
  void visit(std::string s,
             std::map<std::string, std::multiset<std::string>> &targets,
             std::vector<std::string> &route) {
    while (targets[s].size()) {
      std::string next = *targets[s].begin();
      targets[s].erase(targets[s].begin());
      visit(next, targets, route);
    }

    route.push_back(s);
  }
};
