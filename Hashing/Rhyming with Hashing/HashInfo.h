/* Defines a class made to store a word and what words 
* follow after that word and the normality of that occurance.
*
* Author: Stuart Hopkins
* Last Updated: 03/14/18
*/

#ifndef HASHINFO
#define HASHINFO

#include <iostream>
#include <vector>

class HashInfo {
private:
	std::string word;
	int ct;
	std::vector<std::string> succInfo;
	std::vector<int> succCt;

public:
	HashInfo();
	void setWord(std::string w) { word = w; }; //sets the word
	int getCt() { return ct; }; //returns the count
	void addSuccInfo(std::string s); //Finds successor location and adds it or inserts it if doesn't exist
	std::string findRandSucc(); //Finds and returns a random successor using the pobability of the successors
	std::string toString();
};



#endif