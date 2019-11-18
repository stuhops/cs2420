/*Implaments a union find class and performs operations on it.
* Unions are performed by height with path compression.
*
* Author: Stuart Hopkins
* Last Updated: 04/06/2018
*/

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <iostream>
#include <string>

class UnionFind 
{
private:
	static const int SIZE = 1000; 
	int arr[SIZE]; 
	int unionsPerformed;
	int successfulUnions;
	int findsPerformed;
	

public:
	UnionFind(); //Constructor
	bool _union(int posA, int posB); //Unions two references
	int find(int pos); //Finds the root of the input union.
	int getUnions() { return unionsPerformed; }
	int getSuccessfulUnions() { return successfulUnions; }
	int getFinds() { return findsPerformed; }
	int getSize() { return SIZE; }
	void printUnion(); //Prints out a readable version of the array


};
#endif
