/* Implaments MinHeap.h
*
* Author: Stuart Hopkins
* Last Updated: 03/27/18
*/

#include "MinHeap.h"

Node* MinHeap::SkewHeapMerge(Node * t1, Node * t2)   // t1 and t2 are merged, a new tree
{
	Node * small;
	if (t1 == NULL)  return t2;
	if (t2 == NULL) return t1;
	if (t1->element.priority < t2->element.priority) {
		t1->right = SkewHeapMerge(t1->right, t2);
		small = t1;
	}
	else {
		t2->right = SkewHeapMerge(t2->right, t1);
		small = t2;
	}
	Node * tmp = small->left;
	small->left = small->right;
	small->right = tmp;
	return small;
}

// Makes the heap empty starting at the input node
void MinHeap::makeEmpty(Node *curr) {
	if (curr == NULL) {
		return;
	}
	makeEmpty(curr->left);
	makeEmpty(curr->right);
	size = 0;
	delete curr;
}

// Inserts a value into the heap
void MinHeap::insert(ItemType val) {
	Node *valNode = new Node(val);
	root = SkewHeapMerge(root, valNode);
	size++;
}

// Returns and removes the min and merges the remaining heaps
Node* MinHeap::deleteMin() {
	Node *tmp = root;
	if (root != NULL)
		root = SkewHeapMerge(root->left, root->right);
	size--;
	return tmp;
}

// Print the tree preceeded by the "msg".
// Print the tree to depth "depth"
// Print the whole tree if no depth is specified
void  MinHeap::toString() {
	if (root == NULL) return;
	toString(root->left, "  ", root);
	std::cout << root->toString() << "(no parent)" << std::endl;
	toString(root->right, "  ", root);
}


void MinHeap::toString(Node *t, std::string indent, Node *parent) {
	if (t == NULL) return;
	toString(t->left, indent + "  ", t);
	std::cout << indent << t->toString() << "(" << parent->toString() << ")" << std::endl;
	toString(t->right, indent + "  ", t);
}
