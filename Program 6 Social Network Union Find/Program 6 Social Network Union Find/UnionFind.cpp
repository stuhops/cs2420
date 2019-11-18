/* Implaments the UnionFind class.
*
* Author: Stuart Hopkins
* Last Uptdated: 04/06/2018
*/

#include "UnionFind.h"

//Constructor
UnionFind::UnionFind()
{
	for (int i = 0; i < SIZE; i++) {
		arr[i] = -1;
	}
	unionsPerformed = 0;
	successfulUnions = 0;
	findsPerformed = 0;
}

//Unions two references
bool UnionFind::_union(int posA, int posB)
{
	unionsPerformed++;
	//perform find on both nodeA and nodeB. 
	int rootA = find(posA);
	int rootB = find(posB);
	//if they have the same root then return
	if (rootA == rootB)
		return false;

	if (arr[rootA] < arr[rootB])
		arr[rootB] = rootA;
	else if (arr[rootA] == arr[rootB]) {
		arr[rootB] = rootA;
		arr[rootA]--; //increase the height
	}
	else
		arr[rootA] = rootB;

	successfulUnions++;
	return true;

}


//Finds the root of the input union.
int UnionFind::find(int pos)
{
	int root = pos;
	if (arr[pos] >= 0) {
		root = find(arr[pos]);
		arr[pos] = root; //For path compression
	}
	findsPerformed++;
	return root;
}

//Prints the array out
void UnionFind::printUnion() {
	for (int i = 0; i < SIZE; i++)
		std::cout << "[" << i << "] " << arr[i] << std::endl;
	return;
}