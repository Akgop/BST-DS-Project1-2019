#include "BinarySearchTree.h"
using namespace std;

//소멸자.
BinarySearchTree::~BinarySearchTree()
{
	//while (1) {
	//	if (this->m_root == NULL) {
	//		break;
	//	}
	//	else {
	//		deletion(this->m_root->m_data.m_ability);
	//	}
	//}
}

void BinarySearchTree::insert(SoccerPlayerData & data)
{
	TreeNode * pNew = new TreeNode(data);
	TreeNode * pCur;
	if (this->m_root == NULL) {	//if root is empty
		this->m_root = pNew;	//set new node as root
		return;
	}
	else {
		pCur = this->m_root; //initialize with root
		while (1) {
			if (data.m_ability < pCur->m_data.m_ability) {	//if ability is smaller
				//if no left child
				if (pCur->m_left == NULL) {
					pCur->m_left = pNew;	//set left as new node
					return;
				}
				else {	//if left child exists
					pCur = pCur->m_left;	//goto leftchild
				}
			}
			else if (data.m_ability > pCur->m_data.m_ability) {	//if ability is larger
				//if no right child
				if (pCur->m_right == NULL) {
					pCur->m_right = pNew;	//set right as new node
					return;
				}
				else {	//if right child exists
					pCur = pCur->m_right;
				}
			}
			else {
				cout << "Error(NO SAME ABILITY DATA)" << endl;
			}
		}
	}
}

void BinarySearchTree::deletion(int ability)
{
	if (this->m_root == NULL) {
		return;
	}
	else {
		TreeNode * target_parent = this->m_root;
		TreeNode * delete_target = this->m_root;
		TreeNode * change_target = this->m_root;
		TreeNode * change_target_parent = this->m_root;
		if (delete_target->m_data.m_ability == ability) {	//찾고자 하는 값이 루트인경우
			if (delete_target->m_left == NULL) {	//왼쪽 child노드 없을때.
				if (delete_target->m_right == NULL) {	//오른쪽 child노드도 없을때
					this->m_root = NULL; 
					delete delete_target;	//그냥 루트 삭제.
				}
				else {	//오른쪽 노드는 있을때
					this->m_root = delete_target->m_right;	//루트노드를 지울대상의 오른쪽 노드로 지정
					delete target_parent;	//현재 노드 지워버림.
				}
			}
			else {	//왼쪽 child 노드 있을때.
				change_target_parent = change_target;
				change_target = delete_target->m_left;
				if (change_target->m_right == NULL) {	//오른쪽 노드가 없으면
					change_target->m_right = delete_target->m_right;
					this->m_root = change_target;
					delete delete_target;
				}
				else {	//오른쪽 노드가 있으면
					while (1) {
						change_target_parent = change_target;	//부모노드 = 현재노드
						change_target = change_target->m_right; //오른쪽으로 한칸 이동.
						if (change_target->m_right == NULL) {	//옮긴 다음 오른쪽이 더이상 없다면 
							break;	//멈춤.
						}
					}
					if (change_target->m_left != NULL) {	//바꿀 놈의 왼쪽이 있었다면
						change_target_parent->m_right = change_target->m_left;	//그 부모의 왼쪽으로 설정
					}
					else {
						change_target_parent->m_right = NULL;	//없었다면 그냥 NULL 값.
					}
					change_target->m_left = delete_target->m_left;
					change_target->m_right = delete_target->m_right;
					this->m_root = change_target;
					delete delete_target;
				}
			}
		}
		else {	//루트는 아닌경우
			// 1. 타겟과 타겟의 부모노드를 찾아줌.
			while (1) {
				if (delete_target->m_data.m_ability < ability) {	//현재 노드값이 지우려는 값보다 작으면.
					target_parent = delete_target;
					delete_target = delete_target->m_right;	//오른쪽으로 이동.
				}
				else if (delete_target->m_data.m_ability > ability) {
					target_parent = delete_target;
					delete_target = delete_target->m_left;	//왼쪽으로 이동.
				}
				else {
					break;
				}
			}
			// 2. 바꾸려고 하는 노드와 그 부모노드를 찾아줌.
			change_target = delete_target;	change_target_parent = delete_target;
			if (change_target->m_left == NULL) {	//바꾸려는 값의 왼쪽이 null이라면.
				if (change_target->m_right == NULL) {	//오른쪽도 null 이라면 (즉 자식이 없으면)
					if (change_target->m_data.m_ability > target_parent->m_data.m_ability) {
						target_parent->m_right = NULL;
					}
					else {
						target_parent->m_left = NULL;
					}
					delete delete_target;
				}
				else {	//오른쪽은 있다면.
					change_target = change_target->m_right;
					if (change_target->m_data.m_ability > target_parent->m_data.m_ability) {
						target_parent->m_right = change_target;
					}
					else {
						target_parent->m_left = change_target;
					}
					delete delete_target;
				}
			}
			else {	//왼쪽이 있다면.
				change_target_parent = change_target;
				change_target = change_target->m_left;	//왼쪽으로 가주고
				while (1) {	//오른쪽으로 되는만큼 이동
					if (change_target->m_right == NULL) {
						break;
					}
					else {
						change_target_parent = change_target;
						change_target = change_target->m_right;
					}
				}
				if (delete_target->m_left == change_target) {
					if (target_parent->m_data.m_ability > delete_target->m_data.m_ability) {
						target_parent->m_left = change_target;
						delete delete_target;
					}
					else {
						target_parent->m_right = change_target;
						delete delete_target;
					}
				}
				else {
					if (change_target->m_left != NULL) {
						change_target_parent->m_right = change_target->m_left;	//바꾸려는 부모먼저
					}
					change_target->m_left = delete_target->m_left;	//아래에서 위로 끌어올려주고
					change_target->m_right = delete_target->m_right;	//null 이어도 상관없음
					target_parent->m_left = change_target;
					delete delete_target;
				}
			}
		}
	}
}

