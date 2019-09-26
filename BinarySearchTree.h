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

	//function for de-allocate Trees
	void postOrder(TreeNode * t);

	//function for print player data, operator overloading.
	friend ostream& operator<<(ostream& os, const BinarySearchTree& tree) {
		//used stack to make in-order search
		if (tree.m_root != NULL) {	//if tree is not null
			TreeNode * pCur = tree.m_root;	//current node as root
			stack<TreeNode*> s;	//stack s.
			while (1) {
				while (1) { //goto smallest ability node
					if (pCur->getLeftNode() == NULL) { //if left node empty
						break;	//break
					}
					else {
						s.push(pCur);	//stack push
						pCur = pCur->getLeftNode();	//move left
					}
				}
				while (1) {
					os << pCur;	//print player data
					if (pCur->getRightNode() != NULL) {	//if right child exist
						pCur = pCur->getRightNode();	//move right
						break;	//break;
					}
					else {	//no right child
						if (s.empty()) {	//if stack empty
							return os;	//return os.
						}
						else {	//not empty
							pCur = s.top();	//current not = stack top node
							s.pop();	//stack pop
						}
					}
				}
			}
		}
	}
};
