/* The Priority Queue class is designed to work in conjunction with the Board class. It implaments a priority queue
* of structures that contain information for a 3x3 puzzle game using avl trees.
*
* Author: Stuart Hopkins (A02080107)
* Last updated 2/21/2018
*/
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "Board.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class PriorityQueue {

private:
	struct Node
	{
		Board my_board;
		int state;
		Node* left;
		Node* right;
	};

	Node* head;
	Node* tail;


public:
	Queue();
	Board getHeadBoardInfo();						//Returns the head Board.
	std::string getHeadBoardHistory();				//Returns the history of the head Board.
	int getHeadBoardState();						//Returns the state of the head Board.
	void changeHeadBoardState(int s);				//Changes the state of the head Board.
	void addBoard(Board new_board, int the_state);  //Adds a new board onto the tail of the queue.
	void deleteFirst();								//Deletes the first node and places the head pointer onto the next in line.
	void clear();									//Clears the queue.
};
#endif