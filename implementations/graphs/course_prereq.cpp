#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
  /* Idea: treat this as a graph and edge problem. If a cycle forms, then not
   * all course can be finished. We can do dfs + backtracking to find courses
   * that can be finished. In case of repeated loop, we can have a 'hashset' of
   * current subjects that is already being searched (the current dfs path)
   *
   * More explicitly:
   * Construct an adjacency list, where a course maps to all its prerequisites.
   * For each course, run dfs to determine whether it can be completed; we run
   * on each course to avoid nodes that have no "edges" connecting them
   * if every course can be completed, return true
   * Note the memoization of of the premap; if a course can be completed, we
   * save it there for future use
   * We use visiting set, updated by backtracking, to determine whether a
   * particular path forms a cycle. Remember to backtrack, meaning that
   * we are done doing dfs along that branch, we will do dfs along a different
   * branch
   *
   * */
public:
  bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
    std::unordered_map<int, std::vector<int>> preMap;
    std::unordered_set<int> visiting;

    for (int i = 0; i < numCourses; ++i) {
      preMap[i] = {};
    }

    for (const auto pre : prerequisites) {
      preMap[pre[0]].push_back(pre[1]);
    }

    for (int i = 0; i < numCourses; ++i) {
      if (!dfs(i, preMap, visiting)) {
        return false;
      }
    }

    return true;
  }

private:
  bool dfs(int course, std::unordered_map<int, std::vector<int>> &preMap,
           std::unordered_set<int> &visiting) {
    if (visiting.count(course)) {
      return false;
    }

    if (preMap[course].empty()) {
      return true;
    }

    visiting.insert(course);
    for (const int pre : preMap[course]) {
      if (!dfs(pre, preMap, visiting)) {
        return false;
      }
    }
    visiting.erase(course);
    preMap[course] = {};
    return true;
  }
};

class Solution_copy {
public:
  bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
    std::unordered_map<int, std::vector<int>> preMap;
    std::unordered_set<int> visiting;

    for (int i = 0; i < numCourses; ++i) {
      preMap[i] = {};
    }

    for (const auto prereq : prerequisites) {
      preMap[prereq[0]].push_back(prereq[1]);
    }

    for (int i = 0; i < numCourses; ++i) {
      if (!dfs(i, preMap, visiting)) {
        return false;
      }
    }
    return true;
  }

private:
  bool dfs(int course, std::unordered_map<int, std::vector<int>> &preMap,
           std::unordered_set<int> &visiting) {
    if (visiting.count(course)) {
      return false;
    }

    if (preMap[course].empty()) {
      return true;
    }

    visiting.insert(course);
    for (const int prereq : preMap[course]) {
      if (!dfs(prereq, preMap, visiting)) {
        return false;
      }
    }
    preMap[course] = {};
    visiting.erase(course);

    return true;
  }
};

/* Alternative method is bfs, bottom up. Starting from subjects that have no
 * prerequisites, propogating to other courses, indicating that they can be
 * completed. After doing bfs on this, if there are still courses that have
 * prerequisites left, then it cannot be completed */

/* Key things:
 * Use adjacency lists, to save directed edges i.e. prerequisites of a
 * particular course backtracking in dfs; remember to update visiting set to
 * indicate that a particular path is completed
 * Remember to keep updating adjacency lists. If a subject can be completed,
 * modify the prerequisites of itself to be empty. This speeds the algorithm up,
 * preventing searching an already verified branch
 *
 * */
