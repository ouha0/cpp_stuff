#include <stdio.h>
#include <unordered_set>
#include <vector>

class Solution {
public:
  /* Idea: treat this question as a graph problem with directed edges. First
   * build an adjacency list. Have a visited, and current path hash set. For
   * each course, we run dfs on it.
   *
   * dfs: if current numCourses already searched, return true. If it is on the
   * current path, return false, since this forms a cycle.
   *
   * Otherwise, add the current course to current path, and run dfs on its
   * prerequisites. If any if any of prerequisites dfs fails, return false.
   * Otherwise, add current course to visited, get rid of it on current path,
   * and append it to results vector. Note that prerequisites will be added onto
   * results vector before the course, due to recursion.
   *
   * */
  std::vector<int> findOrder(int numCourses,
                             std::vector<std::vector<int>> &prerequisites) {
    std::unordered_set<int> visited;
    std::unordered_set<int> current_path;
    std::vector<int> res;
    std::unordered_map<int, std::vector<int>> preMap;

    for (int i = 0; i < numCourses; ++i) {
      preMap[i] = {};
    }

    for (const auto prereq : prerequisites) {
      preMap[prereq[0]].push_back(prereq[1]);
    }

    for (int i = 0; i < numCourses; ++i) {
      if (!dfs(i, visited, current_path, res, preMap)) {
        return {};
      }
    }
    return res;
  }

private:
  bool dfs(int course, std::unordered_set<int> &visited,
           std::unordered_set<int> &current_path, std::vector<int> &res,
           std::unordered_map<int, std::vector<int>> &preMap) {
    if (current_path.count(course)) {
      return false;
    }

    if (visited.count(course)) {
      return true;
    }

    current_path.insert(course);
    for (const auto prereq : preMap[course]) {
      if (!dfs(prereq, visited, current_path, res, preMap)) {
        return false;
      }
    }
    current_path.erase(course);
    visited.insert(course);
    res.push_back(course);
    return true;
  }
};

/* This algorithm is essentially topological sort; doing some action that
 * requires another task to be completed first before doing it */
