/* Finds the median priority of an input file using priority queues
* 
* Author: Stuart Hopkins, Dr Vicki Allan
* Last Updated: 3/27/18
*/


#include "PQHeap.h"
#include "MinHeap.h"
#include <time.h>

void medianInsert(MinHeap & minPQ, PQ & maxPQ, ItemType*& currMedian, std::ifstream & fin, int limit); //Returns the median of the input
void insertNext(PQ & pq, std::ifstream & fin, int limit); //Version for maximum priority queues
void insertNext(MinHeap & pq, std::ifstream & fin, int limit); // version for minimum priority queues

int main()
{
	clock_t start = clock();
	int const DELETE_CT = 20;
	int const PRINTSIZE = 30;
	int const HOWMANY = 100;

	PQHeap pqMax("MaxHeap", 6000);
	MinHeap pqMin;
	ItemType* currMedian = new ItemType("", -1);

	std::ifstream fin;
	fin.open("Prog5In.txt");
	assert(fin);

	for (int i = 0; i < 60; i++)
	{
		medianInsert(pqMin, pqMax, currMedian, fin, HOWMANY);
		std::cout << currMedian->toString() << std::endl;
	}

	clock_t time = clock() - start;
	std::cout << "Elapsed time = " << ((float)time) / CLOCKS_PER_SEC << std::endl;
	std::cin.ignore();

}



//Insert limit elements of the file fin into min and max heaps and return the median
void medianInsert(MinHeap & minPQ, PQ & maxPQ, ItemType*& currMedian, std::ifstream & fin, int limit = -1) {

	if (limit < 0)
		limit = std::numeric_limits<int>::max();
	std::string word;
	int ct;
	ItemType median("", -1);
	if (currMedian->priority >= 0) {
		median.priority = currMedian->priority;
		median.word = currMedian->word;
	}

	for (int i = 0; i <= limit && !fin.eof(); i++)
	{
		fin >> word >> ct;
		//std::cout << "inserting " << word << ct << std::endl;

		ItemType item(word, ct);
		if (median.priority < 0) {
			median = item;
			currMedian->priority = ct;
			currMedian->word = word;
		}
		else if (ct > median.priority) {
			minPQ.insert(item);
			if (minPQ.getSize() - 1 > maxPQ.getSize()) {
				maxPQ.insert(median);
				median = minPQ.deleteMin()->element;
			}
		}
		else {
			maxPQ.insert(item);
			if (maxPQ.getSize() - 1 > minPQ.getSize()) {
				minPQ.insert(median);
				median = maxPQ.deleteMax()->element;
			}
		}
	}
	currMedian->priority = median.priority;
	currMedian->word = median.word;
	return;
}


//Insert limit elements of the file fin into max heap.
void insertNext(PQ & pq, std::ifstream & fin, int limit = -1)
{
	if (limit < 0)
		limit = std::numeric_limits<int>::max();
	std::string word;
	int ct;
	for (int i = 0; i <= limit && !fin.eof(); i++)
	{
		fin >> word >> ct;
		//std::cout << "inserting " << word << ct << std::endl;
		ItemType item(word, ct);
		pq.insert(item);
	}
}

//Insert limit elements of the file fin into min heap.
void insertNext(MinHeap & pq, std::ifstream & fin, int limit = -1)
{
	if (limit < 0)
		limit = std::numeric_limits<int>::max();
	std::string word;
	int ct;
	for (int i = 0; i <= limit && !fin.eof(); i++)
	{
		fin >> word >> ct;
		//std::cout << "inserting " << word << ct << std::endl;
		ItemType item(word, ct);
		pq.insert(item);
	}
}