#include <stdio.h>
#include <string>
#include <vector>

/* Trie is a tree data structure, where every edge represents a letter of the
 * alphabet. There is also another variable that states whether the current
 * depth of the tree represents the end of some word */

/* Key: We use a TrieNode within a Trie structure. Trie requires a root
 * TrieNode. Each TrieNode requires a vector of possible edges, and a boolean to
 * represent whether the current word represents the end of some word.
 * Remember to do character - 'a' to get the children array offset.
 * */

class Trie {
private:
  struct TrieNode {
    TrieNode *children[26];
    bool end;

    TrieNode() {
      end = false;
      for (int i = 0; i < 26; ++i) {
        children[i] = nullptr;
      }
    }
  };

  TrieNode *root;

public:
  Trie() { root = new TrieNode(); }

  void insert(std::string word) {
    TrieNode *curr = root;

    for (const char c : word) {
      int index = c - 'a';

      // If path doesn't exist, create new trie node
      if (curr->children[index] == nullptr) {
        curr->children[index] = new TrieNode();
      }

      // Update curr to curr trie node
      curr = curr->children[index];
    }

    // set end node = true; indicates current node can represent the end of the
    // word
    curr->end = true;
  }

  // Go through nodes of trie node. If any path is nullptr, then word can't be
  // found. If at end, the word exists if the node is an ending node
  bool search(std::string word) {
    TrieNode *curr = root;
    for (const char c : word) {
      int index = c - 'a';

      if (curr->children[index] == nullptr) {
        return false;
      }

      curr = curr->children[index];
    }

    return curr->end;
  }

  bool startswith(std::string word) {
    TrieNode *curr = root;

    for (const char c : word) {
      int index = c - 'a';
      if (curr->children[index] == nullptr) {
        return false;
      }
      curr = curr->children[index];
    }

    return true;
  }
};
