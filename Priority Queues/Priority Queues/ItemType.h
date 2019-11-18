#ifndef ITEMTYPE_H
#define ITEMTYPE_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <assert.h>


class ItemType
{
public:
	std::string word;            // word
	int priority;           // Priority of ItemType   
	ItemType(std::string aword = "", int p = 0) { word = aword;  priority = p; }
	std::string toString() {
		std::stringstream out;
		out << word << ":" << priority;
		return out.str();
	}
};
#endif