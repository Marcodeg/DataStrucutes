# DataStrucutes
![Cocoapods platforms](https://badgen.net/badge/language/C/blue?icon=)

This repo contains the following C libraries:

- Binary Search Trees: both iterative and recoursive
- Heap trees
- Graphs

## Binary Search Trees
The library manage BST of generic type and has the following funcitionality (both iterative and recoursive):

1. insertion of a node in a BST;
2. printing of all the elements present in a BST;
3. deletion of all elements of in a BST;
4. deletion from a BST given an input item;
5. deletion from a given ABR of all items containing an item that meets the following property:
"has a v key such that a ≤ v ≤ b, with a and b input elements, and is at depth p with p1 ≤ p ≤ p2, where p1 and p2 are input integers';
6. duplication of an input BST as the only parameter of the function;
7. verifies if two BST data are identical, i.e. if they have the same keys and the same shape;
8. filling an ordered array containing all the elements of a given BST;
9. construction of a perfectly balanced BST from a given BST.

__N.B.: the two libraries exhibit the same level of efficiency.__

## Heap Trees
The library provides the representation of weighted and unweighted graphs, by  __tree__ and __array.__

1. display / extract the minimum value
2. display / extract the maximum value
3. decreases a key
4. increase a key
5. insert key
6. clear key
7. delete whole heap

## Graphs
The library provides the representation of weighted and unweighted graphs, by  __adjacency matrices__ and __adjacency lists.__

1. Inserting/deleting a new vertex;
2. Inserting/deleting a new arc;
3. Visit in width of a graph;
4. Visit in depth of a graph;
5. Calculation and printing of routes between two vertices (any route, minimum length route, minimum weight route);
6. Calculation of the maximum subgraph that can be reached from a given vertex;
7. Calculation of the transposed graph;
8. Verification of acyclicity of a graph;
9. Calculation and printing of a topological order of the vertices of the graph;
10. Conversion of three graph representations (e.g.: adjacency lists ↔ adjacency matrix);


## Linux
All the libraries, were developed on Linux (latest gcc version)

## Valgrind
Valgrind is a powerfull tool! It was mainly used to find memory leaks. Read more [here](http://www.valgrind.org)
