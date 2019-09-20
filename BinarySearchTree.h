#pragma once

#include "TreeNode.h"
#include <iostream>
#include <stack>

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
			TreeNode * pCur = tree.m_root;
			stack<TreeNode*> s;
			while (1) {
				while (1) {
					if (pCur->getLeftNode() == NULL) {
						break;
					}
					else {
						s.push(pCur);
						pCur = pCur->getLeftNode();
					}
				}
				while (1) {
					os << pCur;
					if (pCur->getRightNode() != NULL) {
						pCur = pCur->getRightNode();
						break;
					}
					else {
						if (s.empty()) {
							return os;
						}
						else {
							pCur = s.top();
							s.pop();
						}
					}
				}
			}
		}
	}
};
