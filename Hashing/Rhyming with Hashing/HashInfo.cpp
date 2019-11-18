/* Defines HashInfo.h
*
* Author: Stuart Hopkins
* Last Updated: 03/14/18
*/

#include "HashInfo.h"
#include <vector>
#include <iostream>
#include <string>

HashInfo::HashInfo() { 
	word = ""; 
	ct = 0; 
}

//Finds successor location and adds it or inserts it if doesn't exist
void HashInfo::addSuccInfo(std::string s) {
	for(int i = 0; i < succInfo.size(); i++) {
		if (s == succInfo[i]) {
			succCt[i]++;
			//std::cout << succCt[i] << succInfo[i] << std::endl;
			ct++;
			return;
		}
	}

	succInfo.push_back(s);
	succCt.push_back(1);
	ct++;
	return;
}

//Finds and returns a random successor using the pobability of the successors
std::string HashInfo::findRandSucc() {
	int rnd = rand() % ct;
	int prob_ctr = 0;
	int i = 0;
	while(true) {
		prob_ctr += succCt[i];

		if (prob_ctr >= rnd)
			return succInfo[i];
		else
			i++;
	}
}

std::string HashInfo::toString() {
	int count = 0;
	stringstream ss;
		for (int i = 0; i < succInfo.size(); i++) {
			ss << succCt[i] 
				<< " " 
				<< succInfo[i] 
				<< " - ";
		}
	return ss.str();
}