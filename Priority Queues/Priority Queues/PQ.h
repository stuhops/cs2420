#ifndef PQ_H
#define PQ_H
#include "Node.h"
#include  <limits>

class PQ
{
protected:
	std::string name;  //Name of queue (for documentation purposes)
public:
	int size;     // Number of actual items in queue.
	PQ(std::string name = "No Name") { this->name = name; size = 0; }
	virtual Node* deleteMax() = 0;
	virtual std::string toString(int size) const = 0;
	int getSize() { return size; }
	bool isEmpty() { return size == 0; }
	virtual void insert(ItemType & x) = 0;
	virtual void merge(PQ * second) = 0;
	virtual void makeEmpty() { size = 0; }
};
#endif
