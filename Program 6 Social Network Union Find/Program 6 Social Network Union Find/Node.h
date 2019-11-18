#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <sstream>

template <typename ItemType>
class Node
{
public:
	ItemType element;  // Data element
	Node *parent;      // Parent

	Node(ItemType e, Node *p = NULL) :
		element(e), parent(p) {}
	//virtual std::string toString() {
	//	std::stringstream out;
	//	out << element.toString();
	//	if (parent != NULL) out << "[p:" << parent->element << "]";
	//	return out.str();

	//}
	//virtual std::string toStringShort() { return element; }
};
#endif