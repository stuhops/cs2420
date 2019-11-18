#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream> 
#include <cassert>
#include "Board.h"


// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( new_val )       --> Insert new_val
// void remove( val )       --> Remove val (unimplemented)
// bool contains( val )     --> Return true if val is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
	//Constructor
	AvlTree() : root{ nullptr }
	{ }

	AvlTree(const AvlTree & right_side) : root{ nullptr }
	{
		root = clone(right_side.root);
	}

	AvlTree(AvlTree && right_side) : root{ right_side.root }
	{
		right_side.root = nullptr;
	}

	~AvlTree()
	{
		makeEmpty();
	}

	/**
	* Deep copy.
	*/
	AvlTree & operator=(const AvlTree & right_side)
	{
		AvlTree copy = right_side;
		std::swap(*this, copy);
		return *this;
	}

	/**
	* Move.
	*/
	AvlTree & operator=(AvlTree && right_side)
	{
		std::swap(root, right_side.root);

		return *this;
	}

	/**
	* Find the smallest item in the tree.
	* Abort if empty.
	*/
	const Comparable & findMin() const
	{
		assert(!isEmpty());
		return findMin(root)->element;
	}

	/**
	* Find the largest item in the tree.
	* Abortif empty.
	*/
	const Comparable & findMax() const
	{
		assert(!isEmpty());;
		return findMax(root)->element;
	}

	/**
	* Returns true if val is found in the tree.
	*/
	bool contains(const Comparable & val) const
	{
		return contains(val, root);
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const
	{
		return root == nullptr;
	}

	/**
	* Print the tree contents in sorted order.
	*/
	void printTree() const
	{
		if (isEmpty())
			std::cout << "Empty tree" << std::endl;
		else
			printTree(root);
	}

	/**
	* Make the tree logically empty.
	*/
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	* Insert new_val into the tree; duplicates are allowed
	*/
	void insert(const Comparable & new_val)
	{
		insert(new_val, root);
	}

	/**
	* Insert new_val into the tree; duplicates are allowed
	*/
	void insert(Comparable && new_val)
	{
		insert(std::move(new_val), root);
	}

	/**
	* Remove val from the tree. Nothing is done if val is not found.
	*/
	void remove(const Comparable & val)
	{
		remove(val, root);
	}

	// Print the tree preceeded by the "msg".
	// Print the tree to depth "depth"
	// Print the whole tree if no depth is specified
	void  toString()
	{
		if (root == NULL) return;
		toString(root->left, "  ", root->element);
		std::cout << root->element << "(no parent)" << std::endl;
		toString(root->right, "  ", root->element);
	}

	//Removes the minimum value from the tree and rebalances
	void removeMin()
	{
		removeMin(root);
	}

private:
	struct AvlNode
	{
		Comparable element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;

		AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0)
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
			: element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h } { }
	};

	AvlNode *root;

	/**
	* Internal method to insert into a subtree.
	* val is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(const Comparable & val, AvlNode * & t)
	{
		if (t == nullptr) {
			//std::cout << "+";
			t = new AvlNode{ val, nullptr, nullptr };
		}
		else if (val <= t->element) {
			//std::cout << "<";
			insert(val, t->left);
		}
		else if (t->element < val) {
			//std::cout << ">";
			insert(val, t->right);
		}
		//std::cout << std::endl;
		balance(t);
	}

	/**
	* Internal method to insert into a subtree.
	* val is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(Comparable && val, AvlNode * & t)
	{
		std::cout << 1;
		if (t == nullptr)
			t = new AvlNode{ std::move(val), nullptr, nullptr };
		else if (val <= t->element)
			insert(std::move(val), t->left);
		else if (t->element < val)
			insert(std::move(val), t->right);

		balance(t);
	}

	/**
	* Internal method to remove from a subtree.
	* val is the item to remove.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void remove(const Comparable & val, AvlNode * & t)
	{
		if (t == nullptr)
			return;   // Item not found; do nothing

		if (val < t->element)
			remove(val, t->left);
		else if (t->element < val)
			remove(val, t->right);
		else if (t->left != nullptr && t->right != nullptr) // Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			AvlNode *oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}

		balance(t);
	}

	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance(AvlNode * & t)
	{
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		else
			if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
				if (height(t->right->right) >= height(t->right->left))
					rotateWithRightChild(t);
				else
					doubleWithRightChild(t);

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	/**
	* Internal method to find the smallest item in a subtree t.
	* Return node containing the smallest item.
	*/
	AvlNode * findMin(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	/**
	* Internal method to find the largest item in a subtree t.
	* Return node containing the largest item.
	*/
	AvlNode * findMax(AvlNode *t) const
	{
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}


	/**
	* Internal method to test if an item is in a subtree.
	* val is item to search for.
	* t is the node that roots the tree.
	*/
	bool contains(const Comparable & val, AvlNode *t) const
	{
		if (t == nullptr)
			return false;
		else if (val < t->element)
			return contains(val, t->left);
		else if (t->element < val)
			return contains(val, t->right);
		else
			return true;    // Match
	}

	/**
	* Internal method to make subtree empty.
	*/
	void makeEmpty(AvlNode * & t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	/**
	* Internal method to print a subtree rooted at t in sorted order.
	*/
	void printTree(AvlNode *t) const
	{
		if (t != nullptr)
		{
			printTree(t->left);
			std::cout << t->element << " ";
			printTree(t->right);
		}
	}

	/**
	* Internal method to clone subtree.
	*/
	AvlNode * clone(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode{ t->element, clone(t->left), clone(t->right), t->height };
	}
	// Avl manipulations
	/**
	* Return the height of node t or -1 if nullptr.
	*/
	int height(AvlNode *t) const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max(int left_side, int right_side) const
	{
		return left_side > right_side ? left_side : right_side;
	}

	/**
	* Rotate binary tree node with left child.
	* For AVL trees, this is a single rotation for case 1.
	* Update heights, then set new root.
	*/
	void rotateWithLeftChild(AvlNode * & k2)
	{
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	/**
	* Rotate binary tree node with right child.
	* For AVL trees, this is a single rotation for case 4.
	* Update heights, then set new root.
	*/
	void rotateWithRightChild(AvlNode * & k1)
	{
		AvlNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}

	/**
	* Double rotate binary tree node: first left child.
	* with its right child; then node k3 with new left child.
	* For AVL trees, this is a double rotation for case 2.
	* Update heights, then set new root.
	*/
	void doubleWithLeftChild(AvlNode * & k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	/**
	* Double rotate binary tree node: first right child.
	* with its left child; then node k1 with new right child.
	* For AVL trees, this is a double rotation for case 3.
	* Update heights, then set new root.
	*/
	void doubleWithRightChild(AvlNode * & k1)
	{
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}

	//Prints the whole tree with the parent value following the current
	//Requires a node to print, a string to know how far to indent, and the parent to print as well.
	void toString(AvlNode *t, std::string indent, Comparable parent)
	{
		if (t == NULL) return;
		toString(t->left, indent + "  ", t->element);
		std::cout << indent << t->element << "(" << parent << ")" << std::endl;
		toString(t->right, indent + "  ", t->element);
	}

	//Removes the minimum value
	//We pass in the current node to see if that is the minimum and if so remove it.
	void removeMin(AvlNode *&curr)
	{
		if (curr->left == NULL)
			remove(curr->element, curr);
		else
			removeMin(curr->left);
	}

};

#endif
