/* Creates an D-Ary priority queue. Inherates definitions from "PQ.h".
 * 
 * Author: Stuart Hopkins, Dr Vicki Allan
 * Last Updated: 3/27/2018
 */
#ifndef PQHeap_H
#define PQHeap_H

#include "PQ.h"

class PQHeap : public PQ
{
public:
	static const int KIDS = 4;
	ItemType currentNode;
	PQHeap(std::string name, int size);
	void insert(ItemType &);  //    virtual void insert(ItemType & x )=0 ;
	Node* deleteMax();
	int getCount() { return count; }
	void merge(PQ *h);  // merges h into current heap  
	std::string toString(int size) const;
private:
	int count;
	ItemType * heap;   // Heap Array
	int physicalSize;  // Physical size of heap
};


#endif


