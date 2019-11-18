#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <array>
using namespace std;

template <class Etype>
class TreeNode
{
public:
	Etype element;  // value in node
	TreeNode *left;  // left child
	TreeNode *right; // right child
	TreeNode *parent; // parent of node
	TreeNode(Etype e = 0, TreeNode *l = NULL, TreeNode *r = NULL, TreeNode *p = NULL) :
		element(e), left(l), right(r), parent(p) { }
};

template <class Etype>
class BinaryTree
{
protected:
	TreeNode<Etype> *root;  // root of tree
	TreeNode<Etype> *currNode; // Current node
	Etype LOW;   // Smallest possible value stored in tree
	Etype HIGH;  // Largest possible value stored in tree
	bool insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype>*  p);

	void printTree(TreeNode<Etype> * t, std::string indent, int currDepth = 0, int maxDepth = numeric_limits<int>::max());
	void printShort(TreeNode<Etype> * curr); //Prints an in order traversal of the tree. O(log n)
	void fall(TreeNode<Etype> *& curr); //Removes all of the leaf nodes of a binary search tree where a leaf node has no children. O(n)
	void successor(TreeNode<Etype>* curr, int type); //Finds the inorder successor of a node. O(log n)
	Etype closestCommon(Etype x, Etype y, TreeNode<Etype> * curr); //Finds the closest ancestor of two input numbers given they both exist within the tree. O(1)
	bool exist(Etype x, TreeNode<Etype> * curr); //Searches through a tree to determine if the value exists or not. O(n)
	void width(TreeNode<Etype> * curr, int & width, int & height); //Finds the width of the tree. O(n)
	void flip(TreeNode<Etype> * curr); //Flips a tree. O(n)
	void makeEmpty(TreeNode<Etype> * curr); //Empty's the current tree O(n)
	TreeNode<Etype>* perfectBalance(Etype arr[], TreeNode<Etype> * parent, int start, int end); //Makes a tree from an array but does not guarentee the array is a bst O(n)
	bool isBST(TreeNode<Etype>* curr, int min, int max); //Determines whether a tree is a bianary search tree O(n)
	void buildFromPreorder(Etype preOdr[], TreeNode<Etype>* node, int & curr, int const SZE); //Creates a tree based off a given array O(n)
	TreeNode<Etype>* getMaxCompleteSubtree(TreeNode<Etype>* t, int & ht, int & my_best); //Determines the largest complete subtree O(n)

	TreeNode<Etype> * findFirst(TreeNode<Etype> * t) const;
	TreeNode<Etype> * find(TreeNode<Etype> * curr, Etype value)const;
	int size(TreeNode<Etype> *t) const;


public:
	Etype getFirst() {
		TreeNode <Etype> *t = findFirst(root);
		currNode = root;
		if (t == NULL) return LOW;
		return t->element;
	}

	BinaryTree(Etype low = 0, Etype high = 0) : root(NULL) {
		LOW = low;
		HIGH = high;
	}

	// Print the tree preceeded by the "msg".
	// Print the tree to depth "depth"
	// Print the whole tree if no depth is specified
	void  printTree(std::string msg, int depth = numeric_limits<int>::max())
	{
		std::cout << std::endl << msg << std::endl;
		printTree(root, "", 0, depth);
	}

	//Insert item x into the tree using BST ordering
	virtual int insert(Etype & x) { return insert(x, root, NULL); }

	void printShort(std::string x); //Prints an in order traversal of the tree. O(log n)
	void fall(); //Removes all of the leaf nodes of a binary search tree where a leaf node has no children. O(n)
	void successor(); //Finds the inorder successor of a node. O(log n)
	Etype getCurrNodeValue(); //Returns the current node's (currNode) value. O(1)
	Etype closestCommon(Etype x, Etype y);//Finds the closest ancestor of two input numbers.
	bool exist(Etype x); //Searches through a tree to determine if the value exists or not. O(n)
	int width(); //Finds the width of the tree. O(n)
	void flip(); //Flips a tree. O(n)
	void buildFromPreorder(Etype preOdr[], int const SZE); //Creates a tree based off a given array O(n)
	void makeEmpty(); //Empty's the current tree O(n)
	void perfectBalance(Etype arr[], int sze); //Makes a tree from an array but does not guarentee the array is a bst O(n)
	bool isBST(); //Determines whether a tree is a bianary search tree O(n)
	void getMaxCompleteSubtree(); //Determines the largest complete subtree O(n)



};


// return the number of nodes in the tree rooted at t
template <class Etype>
int BinaryTree<Etype>::size(TreeNode<Etype> *t) const
{
	if (t == NULL) return 0;
	return (1 + size(t->left) + size(t->right));
}


//Print the contents of tree t
// Indent the tree bby the string "indent"
// Print the tree to a depth of "depth" given "currdepth" is the depth of t
template <class Etype>
void BinaryTree<Etype>::printTree(TreeNode<Etype> *t, std::string indent, int currdepth, int depth)
{
	if (t == NULL || currdepth>depth) return;
	printTree(t->right, indent + "  ", currdepth + 1, depth);
	if (t->parent != NULL)
		cout << indent << t->element << "(" << t->parent->element << ")" << endl;
	else
		cout << indent << t->element << "( no parent)" << endl;
	printTree(t->left, indent + "  ", currdepth + 1, depth);
}

// insert inserts data into the tree rooted at t
// parent is the parent of t
// Returns true if insertion is successful  (duplicates are not allowed)
// Code is O(log n) for a balanced tree as each level is accessed once
// This inserts as if we wanted to created a binary search tree.
template <class Etype>
bool BinaryTree<Etype>::insert(Etype & data, TreeNode<Etype> * & t, TreeNode<Etype> *  parent)
{
	if (t == NULL)
	{  // cout << "inserting " << data << endl;
		t = new TreeNode<Etype>(data, NULL, NULL, parent);
		if (t == NULL) return false;
		return true;
	}
	if (data < t->element) return insert(data, t->left, t);
	return insert(data, t->right, t);
}
// find seaches for data in the tree rooted at curr
// Returns the node if the find is successful, NULL otherwise
// Code is O(log n) for a balanced tree as each level is accessed once


// Find the leftmost node in a tree rooted at t.
template <class Etype>
TreeNode<Etype> * BinaryTree<Etype>::findFirst(TreeNode<Etype> * t) const
{
	TreeNode<Etype>* s = t;
	for (; s->left != NULL; s = s->left)
		;
	return s;
}

//Prints an in order traversal of the tree. O(log n)
template <class Etype>
void BinaryTree<Etype>::printShort(std::string x) {
	cout << x << endl;
	printShort(root);
}
//Prints an in order traversal of the tree given the root. O(log n)
template <class Etype>
void BinaryTree<Etype>::printShort(TreeNode<Etype> * curr) {
	if (curr != NULL) {
		if (curr->left != NULL)
			printShort(curr->left);

		cout << curr->element << endl;

		if (curr->right != NULL)
			printShort(curr->right);
	}
	else
		return;
}

//Removes all of the leaf nodes of a binary search tree where a leaf node has no children. O(n)
template <class Etype>
void BinaryTree<Etype>::fall() {
	fall(root);
}
//Removes all of the leaf nodes of a binary search tree using recursion where a leaf node has no children. O(n)
template <class Etype>
void BinaryTree<Etype>::fall(TreeNode<Etype> *& curr) {
	if (curr == NULL)
		return;
	if (curr->left == NULL && curr->right == NULL) {
		curr = NULL;
		delete curr;
		return;
	}
	fall(curr->left);
	fall(curr->right);
}

//Finds the inorder successor of a node. O(log n)
template <class Etype>
void BinaryTree<Etype>::successor() {

	if (currNode->right != NULL)
		successor(currNode->right, 1);
	else
		successor(currNode, 2);	
}

//Finds the inorder successor of a node. O(log n)
template<class Etype>
void BinaryTree<Etype>::successor(TreeNode<Etype> * curr, int type) {
	if (type == 1) {
		currNode = curr;
		if (curr->left != NULL)
			successor(curr->left, type);
		return;
	}
	if (type == 2) {
		if (curr->parent != NULL) {
			successor(curr->parent, 3);
			return;
		}
	}
	if (type == 3) {
		if (curr->parent != NULL && curr->right == currNode) {
			currNode = curr;
			successor(curr->parent, type);
			return;
		}
	}
	currNode = curr;
	return;
}

//Returns the current node's (currNode) value. O(1)
template <class Etype>
Etype BinaryTree<Etype>::getCurrNodeValue() {
	if (currNode != NULL)
		return currNode->element;
	else
		return NULL;
}

//Finds the closest ancestor of two input numbers.
template <class Etype>
Etype BinaryTree<Etype>::closestCommon(Etype x, Etype y) {
	if (exist(x) == true && exist(y) == true) {
		if (x == y)
			return x;
		return closestCommon(x, y, root);
	}

	return NULL;
}
//Finds the closest ancestor of two input numbers given they both exist within the tree. O(log n)
template <class Etype>
Etype BinaryTree<Etype>::closestCommon(Etype x, Etype y, TreeNode<Etype> * curr) {
	if (x > curr->element && y > curr->element) {
		return closestCommon(x, y, curr->right);
	}
	else if (x < curr->element && y < curr->element) {
		return closestCommon(x, y, curr->left);
	}

	return curr->element;

}

//Searches through a tree to determine if the value exists or not. O(n)
template <class Etype>
bool BinaryTree<Etype>::exist(Etype x) {
	return exist(x, root);
}
//Searches through a tree to determine if the value exists or not. O(n)
template <class Etype>
bool BinaryTree<Etype>::exist(Etype x, TreeNode<Etype> * curr) {
	if (curr == NULL)
		return false;
	if (x == curr->element)
		return true;
	if (exist(x, curr->right) == true || exist(x, curr->left) == true)
		return true;
	return false;
}

//Finds the width of the tree. O(n)
template <class Etype>
int BinaryTree<Etype>::width() {
	int w, h;

	width(root, w, h);
	return w;
}
//Finds the Width of the tree. O(n)
template <class Etype>
void BinaryTree<Etype>::width(TreeNode<Etype> * curr, int & w, int & h) {
	if (curr == NULL) {
		w = -1;
		h = -1;
		return;
	}

	int hl, hr, wl, wr;

	width(curr->left, wl, hl);
	width(curr->right, wr, hr);
	w = max(hr + hl + 2, max(wl, wr));
	h = max(hr, hl) + 1;
	return;
}

//Flips a tree. O(n)
template <class Etype>
void BinaryTree<Etype>::flip() {
	flip(root);
}
//Flips a tree given a temporary tree O(n)
template <class Etype>
void BinaryTree<Etype>::flip(TreeNode<Etype> * curr) {
	if (curr == NULL)
		return;

	flip(curr->left);
	flip(curr->right);

	TreeNode<Etype> * tmp = curr->left;
	curr->left = curr->right;
	curr->right = tmp;
}

//Creates a tree based off a given array O(n)
template <class Etype>
void BinaryTree<Etype>::buildFromPreorder(Etype preOdr[], int const SZE) {
	int curr = 2;
	if (SZE > 0)
		root = new TreeNode<Etype>(preOdr[0], NULL, NULL, NULL);
	buildFromPreorder(preOdr, root, curr, SZE);
	return;
}
//Creates a tree based off a given preorder of a tree. O(n)
template <class Etype>
void BinaryTree<Etype>::buildFromPreorder(Etype preOdr[], TreeNode<Etype> * node, int &curr, int const SZE) {
	int start = curr - 1;

	// If the number of children is zero it is a leaf so return
	if (preOdr[start] == 0)
		return;

	// If the number of children is one or two then at least a left child exists and possibly a right as well.
	if (preOdr[start] == 1 || preOdr[start] == 2) {
		node->left = new TreeNode<Etype>(preOdr[curr], NULL, NULL, node);
		curr += 2;
		buildFromPreorder(preOdr, node->left, curr, SZE);

		// If the number of children is two then a right child exists.
		if (preOdr[start] == 2) {
			node->right = new TreeNode<Etype>(preOdr[curr], NULL, NULL, node);
			curr += 2;
			buildFromPreorder(preOdr, node->right, curr, SZE);
		}
	}

	return;
}

//Empty's the current tree O(n)
template <class Etype>
void BinaryTree<Etype>::makeEmpty() {
	makeEmpty(root);
	root = NULL;
}
//Empty's the current tree O(n)
template <class Etype>
void BinaryTree<Etype>::makeEmpty(TreeNode<Etype> * curr) {
	if (curr == NULL)
		return;
	makeEmpty(curr->left);
	makeEmpty(curr->right);
	delete curr;
}

//Makes a tree from an array but does not guarentee the array is a bst O(n)
template <class Etype>
void BinaryTree<Etype>::perfectBalance(Etype arr[], int sze) {
	if (sze > 0) {
		int mid = (0 + sze) / 2; //Add 1 to round up
		TreeNode<Etype> * t = new TreeNode<Etype>(arr[mid], NULL, NULL, NULL);
		root = t;
		if (sze > 1) {
			root->left = perfectBalance(arr, root, 0, mid - 1);
			if (sze > 2)
				root->right = perfectBalance(arr, root, mid + 1, sze - 1);
		}
	}
	return;
}
//Makes a tree from an array but does not guarentee the array is a bst O(n)
template <class Etype>
TreeNode<Etype>* BinaryTree<Etype>::perfectBalance(Etype arr[], TreeNode<Etype> * parent, int start, int end) {

	int mid = (start + end + 1) / 2; //Add 1 to round up

	TreeNode<Etype> * t = new TreeNode<Etype>(arr[mid], NULL, NULL, parent);

	if (end - start < 3) {
		if (end - start > 0) {
			TreeNode<Etype> * u = new TreeNode<Etype>(arr[mid - 1], NULL, NULL, t);
			t->left = u;
			if (end - start > 1) {
				TreeNode<Etype> * v = new TreeNode<Etype>(arr[mid + 1], NULL, NULL, t);
				t->left = v;
			}
		}
	}
	else {
		t->left = perfectBalance(arr, t, start, mid - 1);
		t->right = perfectBalance(arr, t, mid + 1, end);
	}
	return t;
}

//Determines whether a tree is a bianary search tree O(n)
template <class Etype>
bool BinaryTree<Etype>::isBST() {
	return isBST(root, LOW, HIGH);
}
//Determines whether a tree is a bianary search tree O(n)
template <class Etype>
bool BinaryTree<Etype>::isBST(TreeNode<Etype> * curr, int min, int max) {

	if (curr == NULL)
		return true;

	if (curr->left != NULL)
		if (curr->left->element >= max || curr->left->element <= min)
			return false;

	if (curr->right != NULL)
		if (curr->right->element >= max || curr->right->element <= min)
			return false;

	if (isBST(curr->left, min, curr->element) == true && isBST(curr->right, curr->element, max) == true)
		return true;

	return false;
}

//Determines the largest complete subtree O(n)
template <class Etype>
void BinaryTree<Etype>::getMaxCompleteSubtree() {
	int ht, my_best;
	TreeNode<Etype> * node = getMaxCompleteSubtree(root, ht, my_best);
	std::cout << "The height of the max complete subtree is " << ht << " starting at the root of " << node->element << endl;
}

//Determines the largest complete subtree O(n)
template <class Etype>
TreeNode<Etype>* BinaryTree<Etype>::getMaxCompleteSubtree(TreeNode<Etype> * t, int & ht, int & my_best) {
	if (t == NULL) {
		ht = -1;
		my_best = -1;
		return t;
	}

	int htl, htr, my_bestl, my_bestr;
	TreeNode<Etype> * left_rt = getMaxCompleteSubtree(t->left, htl, my_bestl);
	TreeNode<Etype> * right_rt = getMaxCompleteSubtree(t->right, htr, my_bestr);

	my_best = min(my_bestl, my_bestr) + 1;
	ht = max(my_best, max(htl, htr));

	if (ht == my_best)
		return t;
	else if (ht == htl)
		return left_rt;
	else
		return right_rt;
}