#pragma once

#include "TreeNode.h"
#include <iostream>

class BinarySearchTree
{
	friend class TransferWindowManager;
private:
	TreeNode * m_root;

public:
	BinarySearchTree() { m_root = NULL; }
	~BinarySearchTree();

	void insert(SoccerPlayerData& data);
	void deletion(int ability); // ability = key

	friend ostream& operator<<(ostream& os, const BinarySearchTree& tree) {
		if (tree.m_root != NULL) {
			os << tree.m_root;
		}
		return os;
	}
};
