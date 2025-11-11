#include <stdio.h>
#include <vector>

class Solution {
public:
  /* Idea is backtracking. Each decision tree, add new element, explore that
   * path, backtrack and then explore the path without the element. The index
   * and the used vector is used to keep track of everything */
  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    std::vector<std::vector<int>> res;
    std::vector<int> used(nums.size(), 0);
    std::vector<int> curr_permutation;

    backtrack(nums, res, curr_permutation, used);

    return res;
  }

private:
  void backtrack(std::vector<int> &nums, std::vector<std::vector<int>> &res,
                 std::vector<int> &curr_permutation, std::vector<int> &used) {

    if (curr_permutation.size() == nums.size()) {
      res.push_back(curr_permutation);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (used[i] == 0) {
        curr_permutation.push_back(nums[i]);
        used[i] = 1;
        backtrack(nums, res, curr_permutation, used);

        curr_permutation.pop_back();
        used[i] = 0;
      }
    }
  }
};

class Solution2 {
public:
  /* This is a iterative approach to building all permutations. The idea is
   * you start with some vector. For each possible vector, you add the new
   * number at every possible position it could be added. Do this for every
   * number until you finish */
  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    std::vector<std::vector<int>> res = {{}};

    for (int i = 0; i < nums.size(); ++i) {
      std::vector<std::vector<int>> curr_iteration;

      for (int j = 0; j < res.size(); ++j) {
        std::vector<int> perm = res[j];

        for (int k = 0; k < perm.size() + 1; ++k) {
          std::vector<int> cpy = perm;
          auto it = cpy.begin() + k;
          cpy.insert(it, nums[i]);
          curr_iteration.push_back(std::move(cpy));
        }
      }
      res = curr_iteration;
    }

    return res;
  }
};

class Solution_recursive {
public:
  /* The key to recursion is figuring out the sub-problem structure. Base case
   * is the empty vector. For the general case, find the permutation of the
   * elements excluding index 0, and then add index 0 number to every possible
   * position of the permutation sub-problem
   *
   * */
  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    if (nums.size() == 0) {
      return {{}};
    }
    std::vector<int> slice(nums.begin() + 1, nums.end());
    std::vector<std::vector<int>> perms = permute(slice);

    std::vector<std::vector<int>> res;
    for (const std::vector<int> &perm : perms) {
      for (int i = 0; i < perm.size() + 1; ++i) {
        std::vector<int> cpy = perm;
        cpy.insert(cpy.begin() + i, nums[0]);
        res.push_back(std::move(cpy));
      }
    }

    return res;
  }
};

/* Always work out the decision tree first. This is very useful for backtracking
 * problems. If you can't solve it by hand, you can't code it... As usual, its
 * important to run test cases after implementation */

/* For recursive solutions, always try work out the base case and the general
 * case. Figure out the "mini" step and the sub-problem. In this case, the base
 * case was when the numbers to permutate are empty, return {}. In the general
 * case, the subproblem is the permutations of all numbers from index 1 to the
 * end. The mini-step would be, for every possible permutation, add the element
 * at index 0 to every possible index for that permutation. */

/* Recursion steps example

nums = [1, 2, 3]:

permute([1, 2, 3]) is called:

It saves the first element, 1.

It recursively calls permute([2, 3]).

permute([2, 3]) is called:

It saves the first element, 2.

It recursively calls permute([3]).

permute([3]) is called:

It saves the first element, 3.

It recursively calls permute([]).

permute([]) is called:

This is the base case. It hits nums.size() == 0 and returns {{}} (a list
containing one empty permutation).

Back in permute([3]):

It receives {{}} from the call below it.

It takes its saved number, 3, and inserts it into every possible position of the
empty permutation []. This produces {[3]}.

It returns {{3}}.

Back in permute([2, 3]):

It receives {{3}} from the call below it.

It takes its saved number, 2, and inserts it into every possible position of
[3].

Inserting at index 0 gives [2, 3].

Inserting at index 1 gives [3, 2].

It returns {{2, 3}, {3, 2}}.

Back in permute([1, 2, 3]):

It receives {{2, 3}, {3, 2}}.

It takes its saved number, 1, and inserts it into every possible position of
both permutations, producing the final six results.

It returns the final complete list.

 * */
