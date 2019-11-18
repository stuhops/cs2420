/* Creates poems based on the probablility of one word coming after another.
 * The probability is determined based on reading in a poem and recording
 * what words come after another.
 *
 * Author: Stuart Hopkins
 * Last Updated: 03/14/18
 */

#include "stdafx.h"
#include "HashTable.h"
#include "HashInfo.h"
#include "HashTable.cpp"
#include "HashInfo.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

// Reads in values from a file and records them in a hash table
void readIn(std::string file, HashTable<std::string, HashInfo> & table); 
// Initializes the values based on an input switch number
void setup(int switch_num, std::string &file, std::string &start, int &words, bool &print_hash); 
// Gets rid of punctuation and changes all letters to lower case
void clean(std::string &nextToken); 


int main()
{
	std::srand(time(NULL));
	int words;
	const int POEMS = 5;
	bool print_hash;
	std::string start;
	std::string file;
	std::string curr;
	std::string prev = "";
	int count = 0;

	// Repeat process for the number of POEM files there are.
	for (int i = 0; i < POEMS; i++) {
		setup(i, file, start, words, print_hash);
		HashTable<std::string, HashInfo> table;
		
		// Read in and record the data in a hash table
		readIn(file, table); 

		if(print_hash == true)
			std::cout << table.toString(50) << std::endl;

		// Write poetry using a premade hashtable
		prev = start;
		for (int i = 0; i < words; i++) {
			HashInfo * h_info = table.find(prev);
			curr = h_info->findRandSucc();
			std::cout << curr << " ";
			prev = curr;
		}

		//Reset for next poem
		table.makeEmpty();
		std::cout << std::endl << std::endl << std::endl;
	}

	char w;
	std::cin >> w;
    return 0;
}

// Reads in values from a file and records them in a hash table
void readIn(std::string file, HashTable<std::string, HashInfo> & table) {
	int count = 0;
	std::string prev;
	std::string curr;
	std::ifstream inFile(file);
	inFile >> curr;
	while (inFile.good()) {
		clean(curr);

		if (table.find(curr) == NULL) {
			HashInfo * info = new HashInfo();
			info->setWord(curr);
			table.insert(curr, info);
		}
		//Don't record information on the previous node for the first item read in
		if (count > 0) {
			HashInfo * h_info = table.find(prev);
			h_info->addSuccInfo(curr);
		}
		count++;
		prev = curr;
		inFile >> curr;
	}
	return;
}

// Initializes the values based on an input switch number
void setup(int switch_num, std::string &file, std::string &start, int &words, bool &print_hash) {
	switch (switch_num) {
	case 0: file = "green.txt";
		start = "sam";
		words = 20;
		print_hash = true;
		break;
	case 1: file = "clown.txt";
		start = "go";
		words = 20;
		print_hash = true;
		break;
	case 2: file = "inch.txt";
		start = "computer";
		words = 50;
		print_hash = false;
		break;
	case 3: file = "poe.txt";
		start = "nevermore";
		words = 50;
		print_hash = false;
		break;
	case 4: file = "seuss.txt";
		start = "mordecai";
		words = 50;
		print_hash = false;
		break;
	}
}

// Gets rid of punctuation and changes all letters to lower case
void clean(std::string &nextToken) {
	for(int	i = 0; i < nextToken.length();)	{
		if (nextToken[i] > 255 || nextToken[i] < 0 || ispunct(nextToken[i]))
			nextToken.erase(i, 1);
		else {
			nextToken[i]= tolower(nextToken[i]);
			i++;
		}
	}
}