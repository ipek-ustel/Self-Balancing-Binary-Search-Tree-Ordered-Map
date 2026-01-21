This repository contains a fully generic, self-balancing Binary Search Tree (BST) implementation that powers an ordered TreeMap ADT. Developed as part of the CENG 213 Data Structures course at Middle East Technical University (METU).

**Key Features**

Self-Balancing Logic: Unlike standard AVL tree, this implementation uses a unique rebuilding strategy. When a subtree violates its balance condition ($H_{actual} > \lfloor \log_2(N) \rfloor$), it is reconstructed into a minimum-height Complete BST.

Pointer Rewiring Algorithm: The tree restructuring (conversion to Complete BST) is performed in linear time ($O(n)$) using only pointer rewiring. This ensures:No new node allocations or deletions during rebalancing. Elements remain at their original memory addresses, preserving the integrity of external pointers or references.

Structural Metadata: Each node maintains height and subsize (subtree size) metadata, updated during recursion to support fast balance checking and lookup operations.

TreeMap ADT: A map implementation that keeps entries sorted by key, providing efficient navigation methods like ceilingEntry, floorEntry, firstEntry, and lastEntry.



**Technical Implementation**

- Core Components

BinarySearchTree<T, BalanceCondition, Comparator>: The core engine. It is highly flexible, allowing custom ordering through Comparator functors and custom balancing triggers through BalanceCondition functors.

TreeMap<K, V>: A wrapper around the BST that manages KeyValuePair<K, V> objects, providing a high-level dictionary interface.

Contact Management System: A practical application of the TreeMap used to manage a digital contact list with alphabetical traversal and multi-field storage (phones, emails, notes).

- Complexity Analysis

Search / Insertion / Removal: $O(\log n)$ average case.

Rebalancing (Restructuring): $O(n)$ for the affected subtree.

Space Complexity: $O(n)$ for storing $n$ elements, with minimal metadata overhead.



**Skills Demonstrated**

Advanced C++ Templates: Extensive use of template metaprogramming and functors.

Manual Memory Management: Precise handling of dynamic node allocation and recursive deallocation (removeAllNodes) to ensure zero memory leaks.

Algorithm Design: Implementation of iterative traversals (Inorder, Preorder, Postorder) using manual stacks to avoid recursion limits.
