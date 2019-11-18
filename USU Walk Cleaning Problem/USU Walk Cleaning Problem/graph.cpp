/*Implaments Graph.h
*
* Author: Stuart Hopkins
* Last Updated: 04/23/2018
*/

#include "graph.h"

//Constructor
Graph::Graph(std::string f, std::ostream &fout) {
	std::ifstream fin(f);
	fileName = f;
	char ch1, ch2;
	int i1, i2;
	//Set up the arrays to input the data into
	fin >> i1 >> i2;
	const int nodeNum = i1;
	const int edgeNum = i2;
	nodeCt = nodeNum;
	edgeCt = edgeNum;

	edgeArr = new Edge[edgeNum];

	graphArr = new int*[nodeNum];
	for (int i = 0; i < nodeNum; i++) {
		graphArr[i] = new int[nodeNum];
		for (int j = 0; j < nodeNum; j++) {
			graphArr[i][j] = -1;
		}
	}

	//Read in the edges and place them in their appropriate places
	for (int i = 0; i < edgeNum; i++) {
		fin >> ch1 >> ch2;
		//Set Edge
		Edge edg;
		edg.fromNode = ch1 - 'A';
		edg.toNode = ch2 - 'A';
		edg.cycleID = -1;
		edg.used = false;
		//Set in the Edge array
		edgeArr[i] = edg;
		//Set in the 2D array
		graphArr[edg.fromNode][edg.toNode] = i;
		graphArr[edg.toNode][edg.fromNode] = i;
	}

	//Check if a Euler tour is possible
	for (int i = 0; i < nodeNum; i++) {
		int degree = 0;
		for (int j = 0; j < nodeNum; j++) {
			if (graphArr[i][j] != -1)
				degree++;
		}
		if (degree % 2 != 0)
			fout << "No Euler Tour Available" << std::endl;
	}
}

//Computes an Eularian tour. Presumes that a perfect tour is possible.
void Graph::computeTour(std::ostream &fout) {
	int numOfCycles = markEdges(fout);

	fout << std::endl;
	printEdgeMatrix(fout);
	fout << std::endl;
	printGraphMatrix(fout);

	int currEdge = 0;
	int nextNode = edgeArr[currEdge].fromNode;
	vector<int> cycleStack;

	fout << std::endl;
	fout << "Euler Tour for " << fileName << " " << std::endl;

	int start = edgeArr[currEdge].fromNode;
	for (int i = 0; i < edgeCt; i++) {
		printNodes(fout, nextNode, currEdge);
		//Update the cycleStack vector
		if (cycleStack.size() > 0) {
			if (cycleStack[cycleStack.size() - 1] == edgeArr[currEdge].cycleID);
			else if (cycleStack.size() > 1 && cycleStack[cycleStack.size() - 2] == edgeArr[currEdge].cycleID)
				cycleStack.pop_back();
			else
				cycleStack.push_back(edgeArr[currEdge].cycleID);
		}
		else
			cycleStack.push_back(edgeArr[currEdge].cycleID);

		//Update the edge
		edgeArr[currEdge].cycleID = -1;
		edgeArr[currEdge].used = true;

		//Get the next node
		if (nextNode != edgeArr[currEdge].toNode)
			nextNode = edgeArr[currEdge].toNode;
		else
			nextNode = edgeArr[currEdge].fromNode;


		//Get the next edge
		currEdge = getNextEdge(cycleStack, nextNode);
	}
	fout << (char)(start + 'A') << std::endl;
}

//Places all edges of a graph into cycles.
int Graph::markEdges(std::ostream &fout) {
	int currEdge = 0;
	int cycleID = 0;

	fout << "Cycles for the graph of file " << fileName << std::endl;

	for (int inGroups = 0; inGroups < edgeCt; cycleID++) {
		//find the edge
		while (true) {
			if (edgeArr[currEdge].cycleID == -1)
				break;
			currEdge = (currEdge + 1) % edgeCt;
		}

		//set start
		int start = edgeArr[currEdge].fromNode;
		int nextNode = start;

		fout << "Cycle " << cycleID << ": ";

		while (true) {
			//Update the node
			edgeArr[currEdge].cycleID = cycleID;
			printNodes(fout, nextNode, currEdge);
			inGroups++;

			//Find the next Node
			if (nextNode != edgeArr[currEdge].toNode) {
				nextNode = edgeArr[currEdge].toNode;
			}
			else {
				nextNode = edgeArr[currEdge].fromNode;
			}

			//Check if nextNode is equal to start to see if we have completed the cycle
			if (nextNode == start)
				break;

			//Find the next edge and return the FIRST edge without a cycle
			for (int i = 0; i < nodeCt; i++) {
				int tmpEdge = graphArr[nextNode][i];
				if (tmpEdge != -1 && edgeArr[tmpEdge].cycleID == -1) {
					currEdge = tmpEdge;
					break;
				}
			}
		}
		fout << (char)(start + 'A') << std::endl;
	}
	return cycleID + 1; //Returns the number of cycles made
}

//Returns the next edge that should be followed in finding an Euler tour
int Graph::getNextEdge(vector<int> stack, int nextNode) {
	int currC = -1;
	int prevC = -1;
	int tmpEdge = -1;
	bool inGroup = false;

	for (int i = 0; i < nodeCt; i++) {
		//find the next edge tht hasn't been gouped 
		inGroup = false;
		tmpEdge = graphArr[nextNode][i];
		if (tmpEdge != -1 && edgeArr[tmpEdge].used == false) {
			//Checks if it is equal to the current cycle
			if (edgeArr[tmpEdge].cycleID == stack[stack.size() - 1]) {
				if (currC == -1)
					currC = tmpEdge;
				inGroup = true;
			}
			//Checks if it is equal to the previous cycle
			for (int j = stack.size() - 2; j >= 0; j--) {
				if (edgeArr[tmpEdge].cycleID == stack[j]) {
					if (prevC == -1)
						prevC = tmpEdge;
					inGroup = true;
				}
			}
			//InGroup states whether it was included in the current or previous groups
			if (inGroup == false)
				return tmpEdge;
		}
	}
	if (currC != -1)
		return currC;
	else
		return prevC;
}

//Prints an edge in a readable format
void Graph::printNodes(std::ostream &fout, int fromNode, int currEdge) {
	fout << (char)(fromNode + 'A') << " ";
}

//Prints a readable version of the edge matrix
void Graph::printEdgeMatrix(std::ostream &fout) {
	fout << "The edge matrix for " << fileName << std::endl;
	fout << "Edge:  ";
	for (int i = 0; i < edgeCt; i++) {
		fout << setw(3) << i;
	}
	fout << std::endl;
	fout << "Cycle: ";
	for (int j = 0; j < edgeCt; j++) {
		fout << setw(3) << edgeArr[j].cycleID;
	}
	fout << std::endl;
}

//Prints a readable version of the edge matrix
void Graph::printGraphMatrix(std::ostream &fout) {

	fout << "The edge matrix for " << fileName << std::endl;

	fout << "   ";
	for (int i = 0; i < nodeCt; i++) {
		fout << setw(3) << (char)(i + 'A');
	}
	fout << endl;

	for (int i = 0; i < nodeCt; i++) {
		for (int j = -1; j < nodeCt; j++) {
			if (j == -1)
				fout << setw(3) << (char)(i + 'A');
			else if (graphArr[i][j] != -1)
				fout << setw(3) << graphArr[i][j];
			else
				fout << setw(3) << "-";
		}
		fout << std::endl;
	}
}

//Prints a readable version of the cycle matrix
void Graph::printCycleMatrix(std::ostream &fout) {
	fout << "The cycle matrix for " << fileName << std::endl;

	fout << "   ";
	for (int i = 0; i < nodeCt; i++) {
		fout << setw(3) << (char)(i + 'A');
	}
	fout << std::endl;
	for (int i = 0; i < nodeCt; i++) {
		for (int j = -1; j < nodeCt; j++) {
			if (j == -1)
				fout << setw(3) << (char)(i + 'A');
			else if (graphArr[i][j] != -1) 
				fout << setw(3) << edgeArr[ graphArr[i][j] ].cycleID;
			else
				fout << setw(3) << "-";
		}
		fout << std::endl;
	}
}