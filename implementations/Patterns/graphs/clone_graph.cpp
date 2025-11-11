#include <list>
#include <map>
#include <queue>
#include <stdio.h>
#include <unordered_map>
#include <vector>

class Solution {
  /* We require some type of tree traversal to go through every single node; use
   * dfs Base case: if we have already cloned that node and saved its
   * neighbours, return the clone.
   *
   * Otherwise, we create a clone of the current node. For each neighbour of the
   * original node, we clone the neighbour node nei, and push_back it to the end
   * of the initial node clone
   *
   * After this, we are done, and we return the clone of the initial node
   *
   *
   * */

public:
  Node *cloneGraph(Node *node) {
    std::unordered_map<Node *, Node *> oldtonew;
    return clone(node, oldtonew);
  }

private:
  Node *clone(Node *node, std::unordered_map<Node *, Node *> &oldtonew) {
    if (node == nullptr) {
      return nullptr;
    }

    if (oldtonew.count(node)) {
      return oldtonew[node];
    }

    Node *copy = new Node(node->val);
    oldtonew[node] = copy;

    for (Node *nei : node->neighbors) {
      copy->neighbors.push_back(clone(nei, oldtonew));
    }

    return copy;
  }
};

class Solution {
public:
  /* This is the BFS + queue solution
   * if node is null, we do nothing. Otherwise create a clone, update oldtonew
   * map, and add node to queue.
   *
   * while queue is not empty, save it, and pop it. For each neighbour, either
   * the neighbour clone exists or doesn't exist. if it already exists, add the
   * neighbour clone to the end of the initial node clones neighbours. If it
   * does not exist, create the clone for the neighbour node, push it into the
   * queue (to clone later), and link the neighbour clone to the initial clone;
   * repeat
   *
   * finally, output the initial node clone
   * */
  Node *cloneGraph(Node *node) {
    if (node == nullptr) {
      return;
    }

    std::unordered_map<Node *, Node *> old_new;
    std::queue<Node *> q;
    old_new[node] = new Node(node->val);
    q.push(node);

    while (!q.empty()) {
      Node *curr = q.front();
      q.pop();

      for (const Node *nei : curr->neighbors) {
        if (old_new.find(nei) == old_new.end()) {
          old_new[nei] = new Node(nei->val);
          q.push(nei);
        }
        curr->neighbors.push_back(old_new[nei]);
      }
    }

    return old_new[node];
  }
};
