/* Uses Union Find to determine how many days it
* takes to link every user in a network with one 
* connection being made every day.
*
* Author: Stuart Hopkins
* Last Updated: 04/06/2018
*/

#include <iostream>
#include <ctime>
#include "UnionFind.h"

int main() {
	UnionFind network;
	const int MEMBERS = network.getSize();
	int days = 0;
	
	srand(std::time(0));
	
	for (int i = 0; network.getSuccessfulUnions() < MEMBERS - 1; days++) {

		//Random numbers to find a new member to union with another
		int toUnion1 = rand() % MEMBERS;
		int toUnion2 = rand() % MEMBERS;
		//Union the two together
		network._union(toUnion1, toUnion2);
	}

	std::cout << "Days: " << days << std::endl;
	std::cout << "Unions: " << network.getUnions() << std::endl;
	std::cout << "Finds: " << network.getFinds() << std::endl;

	//Print out the number of unions performed
	char c;
	std::cin >> c;
	return 0;
}