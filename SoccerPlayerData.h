#pragma once

#include <string>
#include <iostream>
using namespace std;

class SoccerPlayerData
{
	friend class TreeNode;
	friend class BinarySearchTree;
	friend class TransferWindowManager;
private:
	string m_name;
	string m_position;

	int m_transfer_fee;
	int m_ability;

public:
	SoccerPlayerData() { }
	SoccerPlayerData(string name, string position, int transfer_fee, int ability)	//class struct
		:
		m_name(name),
		m_position(position),
		m_transfer_fee(transfer_fee),
		m_ability(ability)
	{
	}

	//operator overloading to print SoccerPlayereData
	friend ostream& operator<<(ostream& os, const SoccerPlayerData& node) {
		os << "(node.m_name: " << node.m_name << "), "
			<< "(node.m_position: " << node.m_position << "), "
			<< "(node.m_transfer_fee: " << node.m_transfer_fee << "), "
			<< "(node.m_ability: " << node.m_ability << ")";
		cout << endl;
		return os;
	}
};
