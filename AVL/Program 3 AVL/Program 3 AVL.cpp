/* Project 3 ~ Rotation Game
*
* Author: Stuart Hopkins (A02080107)
* Last updated: 2/22/2018
*/

#include "stdafx.h"
#include "RotatePuzzle.h"
#include "Board.h"
#include "Queue.h"
#include "AvlTree.h"
#include "Board.cpp"
#include "Queue.cpp"
#include <iostream>
#include <string>

using namespace std;

void setUpGame(Board & start1, Board & start2, Board & start3, Board & start4);
Board menu(int &method);
bool findSolution(Queue & the_queue, Board primary_board);
bool findSolutionA(AvlTree<Board> tree, Board primary_board);

int main() {

	int method; //The method we will use to solve the puzzle.
	Board primary_board; //The primary board we will start with
	Board perfect_board; //A perfect board to compare to


	while (true) {

		//Display a menu of options for the user to pick from and set primary_board equal to the choice
		primary_board = menu(method);

		//Check to see if they started with a perfect board.
		if (perfect_board.operator==(primary_board))
			std::cout << "You started with a perfect board." << endl;

		//If the input method is zero use the brute force approach
		else if (method == 0) {
			Queue the_queue; //Creates a queue to help us solve the puzzle
			the_queue.addBoard(primary_board, 0);
			if (!findSolution(the_queue, primary_board)) {
				the_queue.clear();

				char c;
				std::cin >> c;
				return 0; //find solution alerts the user if their board was invalid so just quit right after
			}
		}

		//If the input method is not zero use the optimized approach.
		else {
			AvlTree<Board> tree;
			if (!findSolutionA(tree, primary_board)) {
				tree.makeEmpty();

				char c;
				std::cin >> c;
				return 0; //find solution A* alerts the user if their board was invalid so just quit right after
			}
			tree.makeEmpty();
		}



		std::cout << "YOU WIN!!! Original Board:" << endl << primary_board.toString() << endl;

		std::cout << endl << "Please enter a 0 to quit or a 1 to try another board: ";
		int again;
		std::cin >> again;
		if (again == 0)
			break;
	}
	std::cout << "Goodbye" << endl;
	return 0;
}




//Sets up the boards to display on the menu.
void setUpGame(Board & start1, Board & start2, Board & start3, Board & start4) {
	//start1 set up
	start1.rotateWest(0);
	start1.rotateNorth(2);

	//start2 set up
	start2.rotateNorth(0);
	start2.rotateNorth(1);
	start2.rotateWest(1);
	start2.rotateNorth(2);
	start2.rotateWest(0);
	start2.rotateNorth(1);


	//start 3 set up
	start3.rotateNorth(1);
	start3.rotateSouth(2);
	start3.rotateEast(0);
	start3.rotateEast(1);
	start3.rotateWest(2);
	start3.rotateNorth(2);
	start3.rotateSouth(0);

	//start 4 set up
	start4.rotateNorth(0);
	start4.rotateNorth(2);
	start4.rotateSouth(1);
	start4.rotateWest(0);
	start4.rotateEast(1);
	start4.rotateWest(2);
	start4.rotateSouth(1);
	start4.rotateEast(0);
	start4.rotateNorth(1);
	start4.rotateWest(2);
}

//Displays the menu portion of the game and recieves user input. Outputs the starting board and the method to solve it.
Board menu(int &method) {
	Board start1, start2, start3, start4;
	setUpGame(start1, start2, start3, start4);
	int input;

	//Print out the to the terminal to give the user options of boards to start from.
	std::cout << endl << "Option 1: " << endl << start1.toString() << endl;
	std::cout << endl << "Option 2: " << endl << start2.toString() << endl;
	std::cout << endl << "Option 3: " << endl << start3.toString() << endl;
	std::cout << endl << "Option 4: " << endl << start4.toString() << endl;

	std::cout << "Please enter the number of the board you want to start with (selections are shown above): ";
	while (true) {
		std::cin >> input;

		if (input >= 1 && input <= 4)
			break;
		std::cout << "You have entered an incorrect value please enter a valid number of option: ";
	}
	std::cout << "Which method would you like to use?" << std::endl
		<< "For a brute force method enter the number 0." << std::endl
		<< "Or to use an A* solve method enter the number 1." << std::endl;

	std::cin >> method;

	switch (input)
	{
	case 1:  return start1;
	case 2:  return start2;
	case 3:  return start3;
	case 4:  return start4;
	}
}


//Finds the quickest solution to the input board using a brute force technique.
bool findSolution(Queue & the_queue, Board primary_board) {
	int num_of_levels = 0;
	int state1 = 0;
	Board temp1;
	Board perfect_board;
	while (true) {
		num_of_levels++;
		std::cout << "State " << state1 + 1 << " from state " << the_queue.getHeadBoardState() << " History "
			<< the_queue.getHeadBoardHistory() << endl << the_queue.getHeadBoardInfo() << endl;
		for (int i = 0; i < 12; i++) {
			//Create a copy of the head board, move, and check if the user wins.
			state1++;
			temp1 = the_queue.getHeadBoardInfo();
			temp1.move(i);
			the_queue.addBoard(temp1, state1);
			if (temp1.operator==(perfect_board)) {
				std::cout << "State " << state1 << " from state " << the_queue.getHeadBoardState() << " History " << temp1.history() << endl << temp1.toString() << endl;
				return true;
			}
		}
		the_queue.deleteFirst();

		//This program runs using integers. If the state counter is above 32,000 then it might cause overflow in many of the variables.
		//With this overflow, this program becomes useless. Because of this we must quit the program.
		if (state1 < 0) {
			std::cout << "The board entered either impossible to solve, or took to many moves to be solved by this program. Goodbye." << endl;
			the_queue.clear();
			return false;
		}
	}
	the_queue.clear();
}

//Finds the solution using an A* search method.
bool findSolutionA(AvlTree<Board> tree, Board primary_board) {
	tree.insert(primary_board);
	int num_of_levels = 0;
	int state1 = 0;
	Board perfect_board;
	while (true) {
		num_of_levels++;
		//copy best board from avl tree and then delete it.
		Board curr = tree.findMin();
		std::cout << "State: " << state1 << " History" << curr.history() << std::endl
			<< curr.toString() << std::endl;
		Board temp;
		tree.removeMin();

		//make 12 copies and move them acordingly
		for (int i = 0; i < 12; i++) {
			state1++;
			temp = curr;
			temp.move(i);

			if (temp == perfect_board) {
				std::cout << "State: " << state1 << " History" << temp.history() << std::endl
					<< temp.toString() << std::endl;
				return true;
			}

			tree.insert(temp);

		}

		//This program runs using integers. If the state counter is above 32,000 then it might cause overflow in many of the variables.
		//With this overflow, this program becomes useless. Because of this we must quit the program.
		if (state1 < 0) {
			std::cout << "The board entered either impossible to solve, or took to many moves to be solved by this program. Goodbye." << endl;
			return false;
		}
	}
}

