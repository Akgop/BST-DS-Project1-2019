#include "BinarySearchTree.h"
using namespace std;

//Destructor
BinarySearchTree::~BinarySearchTree()
{
	if (this->m_root != NULL) {	//if tree is not empty
		postOrder(this->m_root);	//De-allocate every tree node
		this->m_root = NULL;	//then make root null
	}
}

//BST Insert Function
void BinarySearchTree::insert(SoccerPlayerData & data)
{
	TreeNode * pNew = new TreeNode(data);	//allocate new TreeNode
	TreeNode * pCur;	//set current node pointer
	if (this->m_root == NULL) {	//if root is empty
		this->m_root = pNew;	//set new node as root
		return;
	}
	else {	//tree not empty
		pCur = this->m_root; //initialize with root
		while (1) {
			if (data.m_ability < pCur->m_data.m_ability) {	//if ability is smaller
				if (pCur->m_left == NULL) {	//if no left child
					pCur->m_left = pNew;	//set left as new node
					return;	//stop
				}
				else {	//if left child exists
					pCur = pCur->m_left;	//goto leftchild
				}
			}
			else if (data.m_ability > pCur->m_data.m_ability) {	//if ability is bigger
				if (pCur->m_right == NULL) {	//if no right child
					pCur->m_right = pNew;	//set right as new node
					return;	//stop
				}
				else {	//if right child exists
					pCur = pCur->m_right;	//goto rightchild
				}
			}
			else {
				cout << "Error(NO SAME ABILITY DATA)" << endl;	//error handling
			}
		}
	}
}

//Delete Best Team Memeber Function
void BinarySearchTree::deletion(int ability)
{
	//Find Target Node to delete
	TreeNode * pCur = this->m_root, *pParent = NULL;
	while (pCur && pCur->m_data.m_ability != ability) {	//loop pCur is not null and doesn't find target yet
		pParent = pCur;	//parent <- cur
		if (ability < pCur->m_data.m_ability) pCur = pCur->getLeftNode();	//move left
		else pCur = pCur->getRightNode();	//move right
	}
	//No Matching Target
	if (pCur == NULL) return;
	
	//pCur = Leaf Node
	if (pCur->getLeftNode() == NULL && pCur->getRightNode() == NULL) {
		if (pParent == NULL)	this->m_root = NULL;	//if parent not exist, it means only root node. delete root = set NULL
		else if (pParent->getLeftNode() == pCur)	pParent->m_left = NULL;		//if pCur was left child of parent, set left of parent as NULL
		else if (pParent->getRightNode() == pCur)	pParent->m_right = NULL;	//if pCur was right child of parent, set right of parent as NULL
		delete pCur;
		return;
	}

	//Only Right subtree
	if (pCur->getLeftNode() == NULL) {
		if (pParent == NULL)	this->m_root = pCur->getRightNode();		//if pCur == root, right child is new root
		else if (pParent->getLeftNode() == pCur)	pParent->m_left = pCur->m_right;	//if pCur was left child of parent, set pCur->right as parent->left
		else if (pParent->getRightNode() == pCur)	pParent->m_right = pCur->m_right;	//if pCur was right child of parent, set pCur->right as parent->right
		delete pCur;
		return;
	}

	//Only Left subtree
	if (pCur->getRightNode() == NULL) {
		if (pParent == NULL)	this->m_root = pCur->getLeftNode();			//if pCur == root, left child is new root
		else if (pParent->getLeftNode() == pCur)	pParent->m_left = pCur->m_left;		//if pCur was left child of parent, set pCur->left as parent->left
		else if (pParent->getRightNode() == pCur)	pParent->m_right = pCur->m_left;	//if pCur was right child of parent, set pCur->left as parent->right
		delete pCur;
		return;
	}

	//Two child Node
	TreeNode * pTarget = pCur->getLeftNode(), *pTargetParent = pCur;	//pTarget = biggest node of left subtree
	while (pTarget->getRightNode()) {	//find biggest node & it's parent from left subtree
		pTargetParent = pTarget;		//
		pTarget = pTarget->getRightNode();
	}
	pCur->m_data = pTarget->m_data;	//copy data
	if (pTargetParent == pCur)	pTargetParent->m_left = pTarget->getLeftNode();	//if pTarget->right == NULL, pTargetParent->left = pTarget->left
	else pTargetParent->m_right = pTarget->getLeftNode();	//else pTargetParent->left = pTarget->right
	delete pTarget;

}

//Recursive Postorder function to de-allocate tree
void BinarySearchTree::postOrder(TreeNode * t)
{
	if (t != NULL) {	//if node is not null
		postOrder(t->m_left);	//move to left node
		postOrder(t->m_right);	//move to rigth node
		delete t;	//delete node
	}
	else return;
}

