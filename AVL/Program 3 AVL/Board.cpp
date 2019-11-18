/* Implaments the Board class.
*
* Authors: Dr. Vicki Allan, and Stuart Hopkins (A02080107)
* Last updated: 1/24/2018
*/

#include "Board.h"

Board::Board() {
	cost_rn = 0;
	state = 0;
	makeBoard();
	board_score = score();
}
//Copy constructor
Board::Board(const Board & b) {
	assert(SIZE > 0);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = b.board[i][j];
	cost_rn = b.cost_rn;
	board_score = b.board_score;
	move_history = b.move_history;
	setPerfScores();
}

// Make one move.  m indicates which move is wanted. Return string describing the move
std::string Board::move(int m) {
	std::stringstream ss;
	ss << ":";
	int sub = m / 4;
	switch (m % 4)
	{
	case 0:  rotateNorth(sub); ss << "^" << sub; break;
	case 1:  rotateSouth(sub); ss << "v" << sub; break;
	case 2:  rotateEast(sub); ss << ">" << sub; break;
	case 3:  rotateWest(sub); ss << "<" << sub; break;
	}
	cost_rn++;
	addHistory(ss.str());
	score();
	return ss.str();
}

std::string Board::history() {
	return move_history;
}

// Create a printable representation of the Board class
std::string Board::toString() const {
	std::stringstream ss;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			ss << board[i][j] << " ";
		ss << std::endl;
	}
	return ss.str();
};

int Board::getState() {
	return state;
}

// return true if board is identical to b
bool Board::operator==(Board &b) {

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] != b.board[i][j]) return false;
	return true;
}

// return true if board a is less than board b
bool operator<(Board a, Board b) {
	return a.board_score + a.cost_rn < b.board_score + b.cost_rn;
}

// return true if board a is less than or equal to board b
bool operator<=(Board a, Board b) {
	return a.score() + a.cost_rn <= b.score() + b.cost_rn;
}

/* Create a board by performing legal moves on a board
 * jumbleCt indicates the number of moves that may be required
 * if jumbleCt ==0, return the winning board                */
void Board::makeBoard(int jumbleCt) {
	int val = 1;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = val++;
	score();
	jumble(jumbleCt);
}

// Randomly apply ct moves to the board
void Board::jumble(int ct) {
	for (int i = 0; i < ct; i++)
		move(rand() % (SIZE * 4));
}

//Rotate East using row specified
void Board::rotateEast(int row) {
	if (row < 0 || row >= SIZE) return;
	int wrap = board[row][SIZE - 1];
	for (int i = SIZE - 2; i >= 0; i--)
		board[row][i + 1] = board[row][i];
	board[row][0] = wrap;
}

//Rotate West using row specified
void Board::rotateWest(int row) {
	if (row < 0 || row >= SIZE) return;
	int wrap = board[row][0];
	for (int i = 0; i < SIZE - 1; i++)
		board[row][i] = board[row][i + 1];
	board[row][SIZE - 1] = wrap;
}

//Rotate South using column specified
void Board::rotateSouth(int col) {
	if (col < 0 || col >= SIZE) return;
	int wrap = board[SIZE - 1][col];
	for (int i = SIZE - 2; i >= 0; i--)
		board[i + 1][col] = board[i][col];
	board[0][col] = wrap;
}

//Rotate North using column specified
void Board::rotateNorth(int col) {
	if (col < 0 || col >= SIZE) return;
	int wrap = board[0][col];
	for (int i = 0; i < SIZE - 1; i++)
		board[i][col] = board[i + 1][col];
	board[SIZE - 1][col] = wrap;
}

void Board::addHistory(std::string new_history) {
	std::stringstream ss;
	ss << move_history << new_history;
	move_history = ss.str();
}

void Board::changeState(int new_state) {
	state = new_state;
}

void Board::setPerfScores() {

	for (int i = 0; i < 9; i++) {
		xy tmp;
		tmp.x_pos = i / 3;
		tmp.y_pos = i % 3;
		tmp.val = i + 1;
		perf_scores[i] = tmp;
	}
}

int Board::score() {
	int sum = 0;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (x != perf_scores[board[x][y] - 1].x_pos)
				sum++;
			if (y != perf_scores[board[x][y] - 1].y_pos)
				sum++;
		}
	}
	board_score = sum / 3;
	return board_score;
}

std::ostream&  operator<<(std::ostream& os, const Board& brd) {
	os << brd.toString() << endl;
	return os;
}

void Board::changeCost(int new_cost) {
	cost_rn = new_cost;
}