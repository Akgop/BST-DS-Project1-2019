#include "BinarySearchTree.h"
using namespace std;

//�Ҹ���.
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
		if (delete_target->m_data.m_ability == ability) {	//ã���� �ϴ� ���� ��Ʈ�ΰ��
			if (delete_target->m_left == NULL) {	//���� child��� ������.
				if (delete_target->m_right == NULL) {	//������ child��嵵 ������
					this->m_root = NULL; 
					delete delete_target;	//�׳� ��Ʈ ����.
				}
				else {	//������ ���� ������
					this->m_root = delete_target->m_right;	//��Ʈ��带 �������� ������ ���� ����
					delete target_parent;	//���� ��� ��������.
				}
			}
			else {	//���� child ��� ������.
				change_target_parent = change_target;
				change_target = delete_target->m_left;
				if (change_target->m_right == NULL) {	//������ ��尡 ������
					change_target->m_right = delete_target->m_right;
					this->m_root = change_target;
					delete delete_target;
				}
				else {	//������ ��尡 ������
					while (1) {
						change_target_parent = change_target;	//�θ��� = ������
						change_target = change_target->m_right; //���������� ��ĭ �̵�.
						if (change_target->m_right == NULL) {	//�ű� ���� �������� ���̻� ���ٸ� 
							break;	//����.
						}
					}
					if (change_target->m_left != NULL) {	//�ٲ� ���� ������ �־��ٸ�
						change_target_parent->m_right = change_target->m_left;	//�� �θ��� �������� ����
					}
					else {
						change_target_parent->m_right = NULL;	//�����ٸ� �׳� NULL ��.
					}
					change_target->m_left = delete_target->m_left;
					change_target->m_right = delete_target->m_right;
					this->m_root = change_target;
					delete delete_target;
				}
			}
		}
		else {	//��Ʈ�� �ƴѰ��
			// 1. Ÿ�ٰ� Ÿ���� �θ��带 ã����.
			while (1) {
				if (delete_target->m_data.m_ability < ability) {	//���� ��尪�� ������� ������ ������.
					target_parent = delete_target;
					delete_target = delete_target->m_right;	//���������� �̵�.
				}
				else if (delete_target->m_data.m_ability > ability) {
					target_parent = delete_target;
					delete_target = delete_target->m_left;	//�������� �̵�.
				}
				else {
					break;
				}
			}
			// 2. �ٲٷ��� �ϴ� ���� �� �θ��带 ã����.
			change_target = delete_target;	change_target_parent = delete_target;
			if (change_target->m_left == NULL) {	//�ٲٷ��� ���� ������ null�̶��.
				if (change_target->m_right == NULL) {	//�����ʵ� null �̶�� (�� �ڽ��� ������)
					if (change_target->m_data.m_ability > target_parent->m_data.m_ability) {
						target_parent->m_right = NULL;
					}
					else {
						target_parent->m_left = NULL;
					}
					delete delete_target;
				}
				else {	//�������� �ִٸ�.
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
			else {	//������ �ִٸ�.
				change_target_parent = change_target;
				change_target = change_target->m_left;	//�������� ���ְ�
				while (1) {	//���������� �Ǵ¸�ŭ �̵�
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
						change_target_parent->m_right = change_target->m_left;	//�ٲٷ��� �θ����
					}
					change_target->m_left = delete_target->m_left;	//�Ʒ����� ���� ����÷��ְ�
					change_target->m_right = delete_target->m_right;	//null �̾ �������
					target_parent->m_left = change_target;
					delete delete_target;
				}
			}
		}
	}
}

