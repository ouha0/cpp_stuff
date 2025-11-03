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
  std::vector<std::string>
  findItinerary(std::vector<std::vector<std::string>> &tickets) {
    std::sort(tickets.begin(), tickets.end());

    std::unordered_map<std::string, std::vector<std::string>> nei_map;
    for (const auto &ticket : tickets) {
      nei_map[ticket[0]].emplace_back(ticket[1]);
    }

    dfs("JFK", nei_map, tickets);

    return res;
  }

private:
  std::vector<std::string> res = {"JFK"};

  bool dfs(std::string &&s,
           std::unordered_map<std::string, std::vector<std::string>> &nei_map,
           std::vector<std::vector<std::string>> &tickets) {
    if (res.size() == tickets.size() + 1) {
      return true;
    }

    if (nei_map.find(s) == nei_map.end()) {
      return false;
    }

    std::vector<std::string> tmp = nei_map[s];
    for (int i = 0; i < tmp.size(); ++i) {
      std::string v = tmp[i];
      nei_map[s].erase(nei_map[s].begin() + i);
      res.emplace_back(v);

      if (dfs(std::move(v), nei_map, tickets)) {
        return true;
      }

      nei_map[s].insert(nei_map[s].begin() + i, v);
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
