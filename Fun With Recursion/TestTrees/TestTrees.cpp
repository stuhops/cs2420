#include "stdafx.h"
#include "binarytree.h"
#include "iostream"
#include <array>
#include <ctime>
using namespace std;

int main()
{
	const int COUNT = 10;  // size of tree
	const int MAXELE = 100;
	BinaryTree<int> tree1(0, MAXELE);
	BinaryTree<int> tree2(0, MAXELE);
	BinaryTree<int> tree3(0, MAXELE);
	BinaryTree<int> tree4(0, MAXELE);
	BinaryTree<int> tree5(0, MAXELE);


	int values[] = { 10,25,5,8,6,1,30,50,22,11,19,42,3,12,13,36,37,38 };
	int size = sizeof values / sizeof(int);

	for (int i = 0; i < size; i++) {
		tree1.insert(values[i]);
	}
	tree1.printTree("Tree 1");
	std::cout << tree1.getFirst();
	
	int x;
	srand((int)time(0));
	for (int i = 0; i < COUNT; i++) {
	  tree2.insert(x=rand() % MAXELE);
	}
	tree2.printTree("Random tree");
	
	tree2.printShort("\nList of Keys: ");

	tree2.fall();
	tree2.printTree("\n Tree with Leaves Removed");

	/* You can solve this however you want.  The problem is I really don't want my main program to see pointers, but I need to have a current pointer that keeps 
	moving throug the tree.  This code assumes a "current Node" is saved inside the tree.  getFirst sets it.  successor also sets it.  */
	
	tree1.getFirst();
	std::cout << "starting at " << tree1.getCurrNodeValue()<< std::endl;
	for (int i = 0; i < 10; i++)
	{   tree1.successor();  //Successor sets a class variable which is the successor node
	    std::cout <<  "The next sucessor is " << tree1.getCurrNodeValue() << std::endl;
	}
	
	tree1.printTree("Tree 3");

	std::cout << "\nclosest common between 1 and 50 " << tree1.closestCommon(1,50);
	std::cout << "\nclosest common between 19 and 22 " << tree1.closestCommon(19, 22);
	std::cout << "\nclosest common between 11 and 30 " << tree1.closestCommon(11, 30);
	std::cout << "\nclosest common between 15 and 30 " << tree1.closestCommon(15, 30);
	
	tree1.fall();
	tree1.printTree("tree1");
	std::cout << "The width of the tree1 is " << tree1.width() << std::endl;
	tree2.printTree("tree2");
	std::cout << "The width of the tree2 is " << tree2.width() << std::endl;
	
	tree2.printTree("Tree 2");
	tree2.flip();
	tree2.printTree("Flipped Tree 2");
	
	// The preOrder definition is the node value, the number of childen it has, followed by the preOrder definition of each child.
	// Thus, this tree is rooted at 8 and has two children.
	int preOrderI[] = {8, 2, 10, 1, 14, 1, 13, 0, 3, 2, 6, 2, 7, 0, 4, 0, 1, 0 };
	tree4.buildFromPreorder(preOrderI, sizeof(preOrderI) / sizeof(int) - 1);
	tree4.printTree("tree from Preorder");
	tree4.makeEmpty();
	
	std::cout << "**********\n\n\n";
	int perfectBalanceI[] = { 2,5,7,9,12,14,15,16,21,56,69,80,82,83,84,74,90,95,99 };
	tree4.perfectBalance(perfectBalanceI, sizeof(perfectBalanceI) / sizeof(int));
	tree4.printTree("Perfect Balance");
	
	if (tree4.isBST())
	std::cout << "Tree is a BST\n";
	else
	std::cout << "Tree is NOT a BST\n";
	
	tree4.fall();
	tree4.printTree("Curr Tree");
	
	if (tree4.isBST())
	std::cout << "Tree is a BST\n";
	else
	std::cout << "Tree is NOT a BST\n";
	
	tree2.printTree("Tree 2");
	if (tree2.isBST())
	std::cout << "Tree is a BST\n";
	else
	std::cout << "Tree is NOT a BST\n";
	
	int nodesI[] = { 10,16,31,5,2,88 };
	tree3.perfectBalance(nodesI, sizeof(nodesI)/sizeof(int));
	tree3.printTree("PerfectBalance from keys");
	
	for (int i = 0; i <COUNT; i++){
	int t = rand()%MAXELE;
	tree5.insert(t);
	}
	tree5.printTree("FindMaxComplete");
	tree5.getMaxCompleteSubtree();
	
	tree4.printTree("FindMaxComplete");
	tree4.getMaxCompleteSubtree();
	tree3.printTree("FindMaxComplete");
	tree3.getMaxCompleteSubtree();
	
	char c;
	std::cin >> c;  //Pause 

}





