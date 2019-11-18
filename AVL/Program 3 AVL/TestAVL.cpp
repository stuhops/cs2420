#include "AvlTree.h"
#include <iostream>
#include <iomanip>
#include <string>

int main()
{
	AvlTree<int> t;
	for (int i = 1; i < 30; i += 3)
		t.insert(i);
	t.insert(7);

	t.printTree();
	t.toString();

	std::cout << std::endl << t.findMin() << std::endl;
	std::cout << t.findMax() << std::endl;
	int check = 23;
	if (!t.contains(check))
		std::cout << check << " ITEM_NOT_FOUND failed!" << std::endl;

	std::string name = "this";

	AvlTree<std::string> words;
	words.insert("help");
	words.insert("me");
	words.insert("please");
	words.insert("I");
	words.insert("said");
	words.insert("help");
	words.insert("me");
	words.insert("please");
	words.printTree();

	//Add: 1 3 5 7 9 11 2 4 8  (now print tree)
	AvlTree<int> tree;
	const int SIZE = 9;
	int nums_to_add[SIZE] = { 1,3,5,7,9,11,2,4,8 };
	for (int i = 0; i < SIZE; i++) {
		tree.insert(nums_to_add[i]);
	}

	//	Remove 7 9(now print tree)
	tree.remove(7);
	tree.remove(9);
	tree.printTree();

	//	Add 50 30 15 18 (now print tree)
	tree.insert(50);
	tree.insert(30);
	tree.insert(15);
	tree.insert(18);

	//	Remove Min(now print tree)
	tree.removeMin();
	tree.printTree();

	//	Remove Min(now print tree)
	tree.removeMin();
	tree.printTree();

	//	Remove Min(now print tree)
	tree.removeMin();
	tree.printTree();

	//	Add 17(now print tree
	tree.insert(17);

	char p;
	std::cin >> p;

	return 0;
}
