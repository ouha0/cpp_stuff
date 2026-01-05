# Core / Infamous Questions

Familiarity: Easy, OK, Hard

## Recursion / DFS (Backtracking)
Summary: Many problems can be elegantly solved recursively

### Top Problems
- 39. Combination Sum (OK)
- 40. Combination Sum II (OK)
- 78. Subsets (Lean Easy)
- 90. Subsets II (OK)
- 46. Permutations (Hard)
- 47. Permutations II (Hard)

## Graph Traversal (DFS, BFS, Topological Sort, Union Find, Dijkstras (A*), Floyd-Warshall, Kahns Algorithm)
Summary: BFS goes layer by layer, using a queue, typically finding shortest path.
DFS goes deep until the leaf node, then backtracks.

### Top Problems (DFS, BFS)
- 133. Clone Graph (OK)
- 127. Word Ladder (Hard)
- 490. The Maze (Hard)

### Top Problems (Dependencies)
- 210. Course Schedule II (Intuition: OK)
- 269. Alien Dictionary (Intuition: Hard)

/* Basic walkthrough for the questions below only */

## Binary Tree
Summary: Types of traversals; preorder, inorder, postorder. Typically Divide & Conquer idea
Idea is to find the middle, and use the middle to determine which reduce the solution set by half

### Top Problems
- 94. Binary Tree Inorder Traversal (Easy)
- 236. Lowest Common Ancestor of a Binary Tree (Hard)
- 297. Serialize and Deserialize Binary Tree (Hard)
- 102. Binary Tree Level Order Traversal (BFS) (Easy)
- 98. Validate Binary Search Tree (Hard)

### Top Problems (Divide and Conquer)
- 34. Find First and Last Position of Element in Sorted Array (Easy)
- 162. Find Peak element (Hard)
- 69. Sqrt(x) (Easy)

## Data Structures
Summary: Hash Table, Queue, Stack, Heap (priority queue)
Hash table is most important here. It uses some space, and allows us to reduce time complexity by a lot

 ### Top Problems (Hashmap)
- 242. Valid Anagram (Easy)
- 133. Clone Graph (Easy)
- 127. Word Ladder (OK)

### Top Problems (Stacks / Queues)
- 155. Min Stack (OK)
- 225. Implement Stack using Queues (Hard)

### Top Problems (Heaps)
- 215. Kth Largest Element in an Array (OK)
- 23. Merge k sorted Lists (OK)

## Linked Lists
Summary: pointers between nodes. Usually we use a dummy node in the start for simplicity. Common
problems we get involve deciding whether to use linked lists, or manipulating linked lists

- 237. Delete Node in a Linked List (OK)
- 92. Reverse Linked List II (OK)
- 876. Middle of the Linked List
- 143. Reorder List

## Pointer Manipulation (2 pointers, sliding windows)
Summary: we use double pointers to efficiently ignore cases we don't need, and
consider the next case that may be important
- 239. Sliding Window Maximum
- 3. Longest Substring without repeating characters
- 76. Minimum Window Substring


## Sorting
- 148. Sort List

## Converting Real Life Problem to Code
Summary: Most questions are not pure algorithmic questions. They will be in the form of a story,
where you need to decide / propose potential solutions that is best for the problem situation

- 146. LRU Cache
- 1066. Campus Bike
- 490. The Maze

## Dynamic Programming
Summary: It is an optimization technique, where we save problems we have already solved
so we don't need to resolve them. There may be multiple ways of storing these partial-solutions
i.e. hashmap, arrays, temporary variables
