/*Binary heaps should be the last structure that is gone through in the course and it is like a binary tree but not one
Binary heaps work on the concept of priority queue where the most important is the easiest to access and remove
Binary heaps are able to compromise between arrays (which use selection sort) and sorted arrays (using insertion sort)
It is able to insert and remove at a decent time of log(n) and is in-place
The way it differs from the tree is that is implicit, meaning that no pointers are used, only an array which in theory could be drawn as a tree*
Instead of using the usual traversal, the nodes are simply inserted without sorting from left to right.
This relation between parent and children is that the parent is equal or more than both children though the children have no distinction between each others
There is a lot more to say and I will try to explain in-code */

#include <iostream>
#include <vector>

using namespace std;

