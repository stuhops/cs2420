/* Author: Stuart Hopkins
 * Last updated 1/17/2018
 */

#include "LinkedList.h"
#include <string>

using namespace std;

LinkedList::LinkedList() {
	head = NULL;
	tail = NULL;

	/*
	head->next_node = NULL;
	tail->next_node = NULL;
	*/
	num_of_nodes = 0;
	
}

//Adds the new data onto the tail of the list.
void LinkedList::addData(int new_data) {
	Node* n = NULL;
	n = new Node;
	n->data = new_data;
	n->next_node = NULL;
	if (head == NULL)
		head = n;
	else 
		tail->next_node = n;
	tail = n;
	num_of_nodes++;
}


void LinkedList::deleteFirst() {
	if(head->next_node != NULL)
		head = head->next_node;//Do I need to set head.next_node for the new head or does it auto set?
	num_of_nodes--;

}


int LinkedList::numberOfNodes() {
	return num_of_nodes;
}

int LinkedList::toInt() {
	string myString = "";
	int s = 0;
	Node* temp = new Node;
	temp = head;
	for(int i = 0; i < num_of_nodes; i++){
	//while (temp->next_node != NULL) {
		//cout << "hello" << endl;
		s = s + temp->data;
		temp = temp->next_node;
	}
		return s;

}
