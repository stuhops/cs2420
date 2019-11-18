/* Author: Stuart Hopkins
* Last updated 1/17/2018
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class LinkedList {

private:
	struct Node
	{
		int data;
		Node* next_node;
	};

	int num_of_nodes;
	Node* head;
	Node* tail;


public:
	LinkedList();
	void addData(int new_data);
	void deleteFirst();
	int numberOfNodes();
	int toInt();


}; 
#endif