#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <sstream>
#include "ItemType.h"

class Node
{
public:
	ItemType element;  // Data element
	Node *left;        // Left child
	Node *right;       // Right Child
	Node(ItemType e, Node *l = NULL, Node *r = NULL) :
		element(e), left(l), right(r) {}
	virtual std::string toString() {
		std::stringstream out;
		out << element.toString();
		if (left != NULL) out << "[l:" << left->element.priority << "]";
		if (right != NULL) out << "[r:" << right->element.priority << "]";
		return out.str();

	}
	virtual std::string toStringShort() { return element.word; }
};
#endif