/*This graph class creates a graph using a 2D array. It can perform a variety
* of operations including finding a Euler tour.
*
* Author: Stuart Hopkins
* Last Updated: 04/23/2018
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include "assert.h"
#include "edge1.h"
#include <vector>
#include <iomanip>

class Graph
{
private:
	int convChar(char ch) { return ch - 65;	} //Converts a character to a number
	int edgeCt; //How many edges are in the graph
	int nodeCt; //How many nodes are in the graph
	int** graphArr; //Stores the graph with the subscripts of the edges
	std::string fileName;
	Edge* edgeArr; //Stores the edges of the graph
	int markEdges(std::ostream &fout); //Places all edges of a graph into cycles.
	int getNextEdge(vector<int> stack, int nextNode); //Returns the next edge that should be followed in finding an Euler tour
	void printNodes(std::ostream &fout, int fromNode, int currEdge); //Prints an edge in a readable format

public:
	Graph(std::string f, std::ostream &fout); //Constructor
	void computeTour(std::ostream &fout); //Computes an Eularian tour. Presumes that a perfect tour is possible.
	void printEdgeMatrix(std::ostream &fout); //Prints a readable version of the edge matrix
	void printGraphMatrix(std::ostream &fout); //Prints a readable version of the graph matrix
	void printCycleMatrix(std::ostream &fout); //Prints a readable version of the cycle matrix
};

#endif
