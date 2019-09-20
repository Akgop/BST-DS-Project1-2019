#pragma once

#include "BinarySearchTree.h"

#include <iostream>
#include <string>
#include <stack>
#include <cstring>

class TransferWindowManager
{
private:
	int m_budget;

	BinarySearchTree fwBST;
	BinarySearchTree mfBST;
	BinarySearchTree dfBST;
	BinarySearchTree gkBST;

public:

	struct SoccerTeam
	{
		SoccerPlayerData fw;
		SoccerPlayerData mf;
		SoccerPlayerData df;
		SoccerPlayerData gk;

		int sum_transfer_fee;
		int sum_ability;

		SoccerTeam();
		SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk);
		friend ostream& operator<<(ostream& os, const SoccerTeam& team);
	};

	TransferWindowManager(string file_dir, int budget);
	

	friend ostream& operator<<(ostream& os, const TransferWindowManager& manager);

	SoccerTeam getBestTeam();

	int getTeamSquad(SoccerTeam fw, SoccerTeam mf, SoccerTeam df, bool fw_flag, bool mf_flag, bool df_flag);
};

