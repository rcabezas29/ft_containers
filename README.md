# ft_containers

This project is a comprehensive reimplementation of several Standard Template Library (STL) containers in C++, including `stack`, `vector`, `map`, and `set`. Additionally, it reimplements supporting classes and functions such as iterators, the `pair` class, `is_integral` type trait, and the `lexicographical_compare` function. The `map` and `set` containers are internally managed using a Red-Black Tree to ensure efficient data management and access times. This project serves as an educational tool to understand the inner workings of the C++ STL and data structures.

## Containers Overview

- **Vector:** A sequence container representing an array that can change its size dynamically.
- **Stack:** A container adaptor that provides a LIFO (Last In, First Out) data structure.
- **Map:** An associative container that stores elements formed by a combination of a key value and a mapped value, following a specific order. Internally uses a Red-Black Tree.
- **Set:** An associative container that contains a sorted set of unique objects of type Key. Internally uses a Red-Black Tree.

## Additional Implementations

- **Iterators:** Provide a way to access elements of a container sequentially without exposing the underlying representation. Iterators for each container have been implemented, including operations such as increment, decrement, dereference, and comparison.
- **Pair:** A class template providing a way to store two heterogeneous objects as a single unit.
- **is_integral:** A type trait implemented to check at compile-time if a type is an integral type.
- **Lexicographical Compare:** A function template that compares two sequences lexicographically (the way words are sorted in a dictionary).

## Red-Black Tree

A Red-Black Tree is a self-balancing binary search tree where each node contains an extra bit for denoting the color of the node, either red or black. This structure ensures the tree remains balanced, with operations such as insertion, deletion, and lookup being efficient in the worst case.

### Properties of Red-Black Trees:

1. **Red/Black Nodes:** Each node is either red or black.
2. **Root Property:** The root is always black.
3. **Red Node Property:** Red nodes cannot have red children (no two red nodes can be adjacent).
4. **Black Depth Property:** Every path from a node to its descendant NULL nodes has the same number of black nodes.
5. **Leaf Nodes:** All leaves (NIL nodes) are considered black.

These properties ensure that the tree remains approximately balanced, with the path from the root to the farthest leaf being no more than twice as long as the path from the root to the nearest leaf, guaranteeing O(log n) time complexity for basic operations.

![Red/Black Tree](img/rb_tree.png)

## Building and Using the Project

### Compilation with [Make](Makefile)

```bash
make
```

### Test

```bash
./test.sh
```

This will do an overall test to check efficiency on the implementation of all the containers.

## Resources

- https://devdocs.io/cpp/
- https://cplusplus.com/