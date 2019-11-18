/*Implaments a min skew heap.
*
* Author: Stuart Hopkins
* Last Updated: 3/27/18
*/

#ifndef MINHEAP
#define MINHEAP
#include "Node.h"

class MinHeap {

private:
	int size;
	Node *root;
	Node *SkewHeapMerge(Node * t1, Node * t2);
	void makeEmpty(Node *curr);
	void toString(Node *t, std::string indent, Node *parent);

public:
	MinHeap() { root = NULL; size = 0; }
	void insert(ItemType val); // Inserts "val" into the heap
	Node* deleteMin(); // Returns and removes the min and merges the remaining trees.
	void toString();
	int getSize() { return size; }


};
#endif