#include "PQHeap.h"

//Create a heap with maximum size "physicalSize" 
PQHeap::PQHeap(std::string name, int physicalSize)
{
	this->name = name;
	size = 0;
	heap = new ItemType[physicalSize];
	this->physicalSize = physicalSize;
	count = 0;
}



// insert element and re-heapify
void PQHeap::insert(ItemType &newVal)
{
	int curr = size;
	assert(size < physicalSize);
	int parent = (curr - 1) / KIDS; // round down
	while (curr>0 && newVal.priority >heap[parent].priority) {
		heap[curr] = heap[parent];
		curr = parent;
		parent = (curr - 1) / KIDS;
	}
	heap[curr] = newVal;
	size++;
	count++;
}


// Delete maximum value, re-heapify, and return max element
Node* PQHeap::deleteMax()
{
	if (size == 0)
		return new Node(ItemType("error", -1));
	ItemType toReturn = heap[0];
	size--;
	ItemType currVal = heap[size];
	int curr = 0;
	int c1 = 1;
	int c2 = c1 + 1;
	int c3 = c1 + 2;
	int c4 = c1 + 3;
	while ((c1 < size && currVal.priority < heap[c1].priority) ||
		(c2 < size && currVal.priority < heap[c2].priority) ||
		(c3 < size && currVal.priority < heap[c3].priority) ||
		(c4 < size && currVal.priority < heap[c4].priority)) {
		int bestChild = c1;
		if (c2 < size && heap[c2].priority > heap[bestChild].priority)
			bestChild = c2;
		if (c3 < size && heap[c3].priority > heap[bestChild].priority)
			bestChild = c3;
		if (c4 < size && heap[c4].priority > heap[bestChild].priority)
			bestChild = c4;

		heap[curr] = heap[bestChild];
		curr = bestChild;
		c1 = KIDS * bestChild + 1;
		c2 = c1 + 1;
		c3 = c1 + 2;
		c4 = c1 + 3;
	} // endwhile

	count--;
	heap[curr] = currVal;
	return new Node(toReturn);

}


// merge second into current  heap
void PQHeap::merge(PQ * second)
{
	for (int i = 0; i < second->getSize(); i++)
		insert(dynamic_cast<PQHeap*>(second)->heap[i]);
	second->makeEmpty();
}

// Convert first "size: elements of PQ to a string.
std::string PQHeap::toString(int maxSize) const
{
	const int PERLINE = 5;
	std::stringstream out;
	out << name << "  current size=" << size;
	if (maxSize > size)
		maxSize = size;

	for (int i = 0; i <maxSize; i++)
	{
		if (i%PERLINE == 0) out << std::endl;
		out << heap[i].toString() << "\t";
	}
	out << std::endl;
	return out.str();
}


