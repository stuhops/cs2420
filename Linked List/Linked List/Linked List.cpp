/* Author: Stuart Hopkins
* Last updated 1/17/2018
*/

#include "stdafx.h"
#include "LinkedList.h"
#include "LinkedList.cpp"

int main()
{
	int c = 0;
	LinkedList my_list;

	cout << "Please enter 3 integers to make a list: ";
	for (int i = 0; i < 3; i++) {
		cin >> c;
		my_list.addData(c);
	}

	cout << "You entered the numbers";
	cout << my_list.toInt();




	cin >> c;
    return 0;
}

