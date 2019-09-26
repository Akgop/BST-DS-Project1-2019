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
	if (this->m_root == NULL) {	//if tree is empty
		return;	//return
	}
	else {	//tree is not empty
		TreeNode * target_parent = this->m_root;	//delete target's parent node pointer
		TreeNode * delete_target = this->m_root;	//delete target node pointer
		TreeNode * change_target = this->m_root;	//change spot node pointer
		TreeNode * change_target_parent = this->m_root;	//change spot parent node
		if (delete_target->m_data.m_ability == ability) {	//if target is root
			if (delete_target->m_left == NULL) {	//if no left child
				if (delete_target->m_right == NULL) {	//if no right child
					this->m_root = NULL;	//root <- null
					delete delete_target;	//delete target
				}
				else {	//no left child, exists right child
					this->m_root = delete_target->m_right;	//set right child as root
					delete target_parent;	//delete target
				}
			}
			else {	//if left child exists
				change_target_parent = change_target;	//change spot parent node <- change spot node
				change_target = delete_target->m_left;	//change spot move left
				if (change_target->m_right == NULL) {	//if no right node
					change_target->m_right = delete_target->m_right;	//change spot's right child <- target's right child
					this->m_root = change_target;	//set root as change spot node
					delete delete_target;	//delete target
				}
				else {	//if right child exists
					while (1) {
						change_target_parent = change_target;	//target parent = current node
						change_target = change_target->m_right; //goto right child (change target)
						if (change_target->m_right == NULL) {	//if no more right child
							break;
						}
					}
					if (change_target->m_left != NULL) {	//if left child exist
						change_target_parent->m_right = change_target->m_left;	//set change spot parent's right child as change target's left child
					}
					else { //if no left child
						change_target_parent->m_right = NULL;	//no child, so set null at right child
					}
					change_target->m_left = delete_target->m_left;	//change node
					change_target->m_right = delete_target->m_right;
					this->m_root = change_target;	//set root as changed node
					delete delete_target;	//delete target
				}
			}
		}
		else {	//if target is not root node
			// 1. find delete target and delete target's parent
			while (1) {
				if (delete_target->m_data.m_ability < ability) {	//if current node ability < target ability
					target_parent = delete_target;
					delete_target = delete_target->m_right;	//goto right child
				}
				else if (delete_target->m_data.m_ability > ability) {	//cur node ability > target ability
					target_parent = delete_target;
					delete_target = delete_target->m_left;	//goto left child
				}
				else {	//if ability is same
					break;	//break
				}
			}
			// 2. find the change target and it's parent node & 3. delete node
			change_target = delete_target;	change_target_parent = delete_target;
			if (change_target->m_left == NULL) {	//if change target's left child is null
				if (change_target->m_right == NULL) {	//same at right child
					//if right child
					if (change_target->m_data.m_ability > target_parent->m_data.m_ability) {
						target_parent->m_right = NULL;	//set parent's right child as null
					}
					else {	//if left child
						target_parent->m_left = NULL;	//set parent's left child as null
					}
					delete delete_target;	//delete target
				}
				else {	//if right child exist
					change_target = change_target->m_right;	//goto right child
					//if change target ability > delete target parent's ability
					if (change_target->m_data.m_ability > target_parent->m_data.m_ability) {
						target_parent->m_right = change_target;	//set change target as right child of target parents 
					}
					else {
						target_parent->m_left = change_target;	//set change target as left child of target parents
					}
					delete delete_target;	//delete node
				}
			}
			else {	//if left child exists
				change_target_parent = change_target;
				change_target = change_target->m_left;	//move left
				while (1) {	//move right as far as it can
					if (change_target->m_right == NULL) {	//if change target has no right child
						break;	//stop
					}
					else {
						change_target_parent = change_target;	//else 
						change_target = change_target->m_right;	//move right
					}
				}
				if (delete_target->m_left == change_target) {	//if target's left == change target
					//if delete target parent's ability > delete_target's ability
					if (target_parent->m_data.m_ability > delete_target->m_data.m_ability) {
						target_parent->m_left = change_target;	//set change target as parent's left child
						delete delete_target;	//delete target
					}
					else { //parent's ability < target's ability
						target_parent->m_right = change_target;	//set change target as parent's right child
						delete delete_target;	//delete target
					}
				}
				else {	//target's left != change target
					if (change_target->m_left != NULL) {	//if change target's left is not null
						change_target_parent->m_right = change_target->m_left;	//set change target's left as it's parent's right
					}
					change_target->m_left = delete_target->m_left;	//move change target node to delete target node
					change_target->m_right = delete_target->m_right;
					target_parent->m_left = change_target;
					delete delete_target;	//delete target
				}
			}
		}
	}
}

//Recursive Postorder function to de-allocate tree
void BinarySearchTree::postOrder(TreeNode * t)
{
	if (t != NULL) {	//if node is not null
		postOrder(t->m_left);	//move to left node
		postOrder(t->m_right);	//move to rigth node
		cout << t->m_data.m_name << ":" << t->m_data.m_ability << endl;
		delete t;	//delete node
	}
	else return;
}

