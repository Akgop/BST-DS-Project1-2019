#include "TransferWindowManager.h"
#include <fstream>

TransferWindowManager::SoccerTeam::SoccerTeam()
{
	//You don't need to edit this function.
}

//Constructor
TransferWindowManager::SoccerTeam::SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk)
{
	//copy parameter to it's member
	this->fw = fw;
	this->mf = mf;
	this->df = df;
	this->gk = gk;

	//get sum transfer fee and sum ability
	this->sum_transfer_fee = fw.m_transfer_fee + mf.m_transfer_fee + df.m_transfer_fee + gk.m_transfer_fee;
	this->sum_ability = fw.m_ability + mf.m_ability + df.m_ability + gk.m_ability;
}

//Operator Overloaded Function to print best team member
std::ostream& operator<<(ostream& os, const TransferWindowManager::SoccerTeam& team)
{
	//print four best member of each roll
	os << team.fw << std::endl;
	os << team.mf << std::endl;
	os << team.df << std::endl;
	os << team.gk << std::endl;

	//print its fee and ability
	os << "sum_transfer_fee " << team.sum_transfer_fee << std::endl;
	os << "sum_ability " << team.sum_ability << std::endl;

	return os;
}

//Read Textfile and make BST
TransferWindowManager::TransferWindowManager(string file_dir, int budget)
{
	this->m_budget = budget;	//get budget

	ifstream in(file_dir);	//input file stream in. read file
	string line;

	while (getline(in, line))	//read file line by line.
	{
		string player_name;
		string position;
		int fee;
		int ability;

		char line_char[100];
		strcpy(line_char, line.c_str());	//convert string to char
		char * temp = strtok(line_char, ",");	//tokenize with ,

		player_name = temp;	//player_name

		temp = strtok(NULL, ", ");	//tokenize with , and white space
		position = temp;	//position

		temp = strtok(NULL, ", ");	//tokenize with , and white space
		fee = atoi(temp);	//fee

		temp = strtok(NULL, ", ");	//tokenize with , and white space
		ability = atoi(temp);	//ability
	
		//make Soccer player data object
		SoccerPlayerData* spd = new SoccerPlayerData(player_name, position, fee, ability);
		if (position == "Forward") {	//if position is Forward
			fwBST.insert(*spd);	//insert data into fwBST
		}
		else if (position == "Midfielder") {	//if position is Midfielder
			mfBST.insert(*spd);	//insert data into mfBST
		}
		else if (position == "Defender") {	//if position is Defender
			dfBST.insert(*spd);	//insert data indo dfBST
		}
		else {	//else
			gkBST.insert(*spd);	//insert data into gkBST
		}
	}
}

//Operator Overload, print Trees.
ostream& operator<<(ostream& os, const TransferWindowManager& manager)
{
	//forward tree print
	os << "********Forward List********" << std::endl;
	os << manager.fwBST;
	os << "****************************" << std::endl;

	//midfielder tree print
	os << "********Midflder List********" << std::endl;
	os << manager.mfBST;
	os << "*****************************" << std::endl;

	//defenter tree print
	os << "********Defender List********" << std::endl;
	os << manager.dfBST;
	os << "*****************************" << std::endl;

	//goal keeper tree print
	os << "********Goalkeeper List********" << std::endl;
	os << manager.gkBST;
	os << "*******************************" << std::endl;

	return os;
}

//get BestTeam Function
TransferWindowManager::SoccerTeam TransferWindowManager::getBestTeam()
{
	SoccerTeam best_team;	//assign struct
		
	TreeNode *pfwCur, *pmfCur, *pdfCur, *pgkCur;
	TreeNode *pfwNext, *pmfNext, *pdfNext;
	//when no more best offer for tree, set flag false
	bool flag_fw = true, flag_mf = true, flag_df = true;

	//initialize with root of each tree
	if (fwBST.m_root != NULL) {
		pfwCur = fwBST.m_root;
	}
	if (mfBST.m_root != NULL) {
		pmfCur = mfBST.m_root;
	}
	if (dfBST.m_root != NULL) {
		pdfCur = dfBST.m_root;
	}
	if (gkBST.m_root != NULL) {
		pgkCur = gkBST.m_root;
	}

	//
	// # Move Inorder Reversely
	//
	stack<TreeNode*> sfw;	//stack for fwBST
	stack<TreeNode*> smf;	//stack for mfBST
	stack<TreeNode*> sdf;	//stack for dfBST

	stack<TreeNode*> temp_sfw;	//temparory sfw
	stack<TreeNode*> temp_smf;	//temparory smf
	stack<TreeNode*> temp_sdf;	//temparory sdf
	//
	// 1. Start with Best Ability Players
	//
	while (1) {	//move to right node in the tree while there's no more right child
		if (pfwCur != NULL) {	//if node is not NULL
			sfw.push(pfwCur);	//push into stack
			pfwCur = pfwCur->m_right;	//move to right node 
		}
		else {	//when node is null
			break;	//stop
		}
	}
	while (1) { //move to right node in the tree while there's no more right child
		if (pmfCur != NULL) {	//same with fw
			smf.push(pmfCur);
			pmfCur = pmfCur->m_right;
		}
		else {
			break;
		}
	}
	while (1) { //move to right node in the tree while there's no more right child
		if (pdfCur != NULL) {	//same with fw
			sdf.push(pdfCur);
			pdfCur = pdfCur->m_right;
		}
		else {
			break;
		}
	}

	//current pointer = top node of stack. and pop it.
	pfwCur = sfw.top();		sfw.pop();
	pmfCur = smf.top();		smf.pop();
	pdfCur = sdf.top();		sdf.pop();

	//
	// 2. Comparing Budget
	//
	while (1) {
		//set best_team
		best_team = { pfwCur->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data };

		// deep copy of stack.
		temp_sfw = sfw;
		temp_smf = smf;
		temp_sdf = sdf;

		if (best_team.sum_transfer_fee <= this->m_budget) {	//if budget not over
			break;	//stop;
		}
		//
		// 3. Set Next best_team 
		//
		else {	
			// 3-1. set next fw node
			pfwNext = pfwCur;
			while (1) {
				if (pfwNext->m_left != NULL) {	//if fw has left child
					pfwNext = pfwNext->m_left;	//move left
					while (1) {
						if (pfwNext->m_right != NULL) {	//if fw has right child
							sfw.push(pfwNext);	//stack push
							pfwNext = pfwNext->m_right;	//move right
						}
						else {	//if no more right child
							break; //stop
						}
					}
					//if pfwNext node is cheaper
					if (pfwNext->m_data.m_transfer_fee < pfwCur->m_data.m_transfer_fee) {	
						break;	// fix pfwNext and break.
					}
					else { continue; }	//else, loop again
				}
				else {	//no left child
					if (sfw.empty()) {	//if stack is empty
						pfwNext = pfwCur;	//came back to original one.
						flag_fw = false;	//set flag false. it means cannot find any better one.
						break;	//break;
					}
					pfwNext = sfw.top(); //else stack pop.
					sfw.pop();
					//if pfwNext node is cheaper
					if (pfwNext->m_data.m_transfer_fee < pfwCur->m_data.m_transfer_fee) {
						break;	// fix pfwNext and break.
					}
					else { continue; }	//else, loop again
				}
			}
			// 3-2. set next mf node (it works same with fw node)
			pmfNext = pmfCur;
			while (1) {
				if (pmfNext->m_left != NULL) {	//if mf has left child
					pmfNext = pmfNext->m_left;	//move left
					while (1) {
						if (pmfNext->m_right != NULL) {	//if mf has left child
							smf.push(pmfNext);	//stack push
							pmfNext = pmfNext->m_right;	//move right
						}
						else {	//if no more right child
							break;
						}
					}
					//if pmfNext node is cheaper
					if (pmfNext->m_data.m_transfer_fee < pmfCur->m_data.m_transfer_fee) {	
						break;	// fix pmfNext and break.
					}
					else { continue; }	//else, loop again
				}
				else {	//no left child
					if (smf.empty()) {	//if stack is empty
						pmfNext = pmfCur;	//came back to original one.
						flag_mf = false;	//set flag false. it means cannot find any better one.
						break;
					}
					pmfNext = smf.top();	//else stack pop.
					smf.pop();
					//if pfwNext node is cheaper
					if (pmfNext->m_data.m_transfer_fee < pmfCur->m_data.m_transfer_fee) {
						break;	// fix pmfNext and break.
					}
					else { continue; }	//else, loop again
				}
			}
			// 3-3. set next df node (it works same with fw node)
			pdfNext = pdfCur;
			while (1) {
				if (pdfNext->m_left != NULL) {	//if df has left child
					pdfNext = pdfNext->m_left;	//move left
					while (1) {
						if (pdfNext->m_right != NULL) {	//if df has left child
							sdf.push(pdfNext);	//stack push
							pdfNext = pdfNext->m_right;	//move right
						}
						else {	//if no more right child
							break;
						}
					}
					//if pdfNext node is cheaper
					if (pdfNext->m_data.m_transfer_fee < pdfCur->m_data.m_transfer_fee) {	
						break;	// fix pdfNext and break.
					}
					else { continue; }	//else, loop again
				}
				else {	//no left child
					if (sdf.empty()) {		//if stack is empty
						pdfNext = pdfCur;	//came back to original one.
						flag_df = false;	//set flag false. it means cannot find any better one.
						break;
					}
					pdfNext = sdf.top();	//else stack pop.
					sdf.pop();
					//if pdfNext node is cheaper
					if (pdfNext->m_data.m_transfer_fee < pdfCur->m_data.m_transfer_fee) {	
						break;	// fix pdfNext and break.
					}
					else { continue; }	//else, loop again
				}
			}

			//
			// 4. Compare Ability and fee
			//
			SoccerTeam fw_team, mf_team, df_team;
			// 4-1. moved only forward data
			fw_team = { pfwNext->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data };
			// 4-2. moved only midfielder data
			mf_team = { pfwCur->m_data, pmfNext->m_data, pdfCur->m_data, pgkCur->m_data };
			// 4-3. moved only defender data
			df_team = { pfwCur->m_data, pmfCur->m_data, pdfNext->m_data, pgkCur->m_data };
			
			// Call functions to compare squad
			// if pfwNext makes new best team
			if (getTeamSquad(fw_team, mf_team, df_team, flag_fw, flag_mf, flag_df) == 1) {	//pfwCur = pfwNext
				pfwCur = pfwNext;	smf = temp_smf;		sdf = temp_sdf;	//mf, df, return stack to original
			}
			// if pmfNext makes new best team
			else if (getTeamSquad(fw_team, mf_team, df_team, flag_fw, flag_mf, flag_df) == 2) {
				pmfCur = pmfNext;	sfw = temp_sfw;		sdf = temp_sdf;	//fw, df return stack to original
			}
			// if pdfNext makes new best team
			else if (getTeamSquad(fw_team, mf_team, df_team, flag_fw, flag_mf, flag_df) == 3) {
				pdfCur = pdfNext;	sfw = temp_sfw;		smf = temp_smf;	//fw, mf return stack to original
			}
		}
	}

	// Call function to delete best team.
	fwBST.deletion(best_team.fw.m_ability);
	mfBST.deletion(best_team.mf.m_ability);
	dfBST.deletion(best_team.df.m_ability);
	gkBST.deletion(best_team.gk.m_ability);

	return best_team;
}

int TransferWindowManager::getTeamSquad(SoccerTeam fw, SoccerTeam mf, SoccerTeam df, bool fw_flag, bool mf_flag, bool df_flag)
{
	// return 1 -> fw
	// return 2 -> mf
	// return 3 -> df
	// if everything is same then, priority is fw > mf > df

	//if all flags are true
	if (fw_flag && mf_flag && df_flag) {
		// if three player has same ability
		if (fw.sum_ability == mf.sum_ability && mf.sum_ability == df.sum_ability) { // 1) fw = mf = df
			if (df.sum_transfer_fee < mf.sum_transfer_fee && df.sum_transfer_fee < fw.sum_transfer_fee) {	// 1-1) df < mf, fw
				return 3;
			}
			else {
				if (mf.sum_transfer_fee < fw.sum_transfer_fee) {	// 1-2) mf <= df & mf < fw
					return 2;
				}
				else { return 1; }	// 1-3) fw <= mf
			}
		}
		// if two player has same ability and larger then other one
		else if (fw.sum_ability == mf.sum_ability && mf.sum_ability > df.sum_ability) { // 2) fw = mf > df
			if (fw.sum_transfer_fee <= mf.sum_transfer_fee) {	// 2-1) fw <= mf 
				return 1;
			}
			else { return 2; }	// 2-2) mf < fw
		}
		else if (fw.sum_ability == df.sum_ability && df.sum_ability > mf.sum_ability) { // 3) fw = df > mf
			if (fw.sum_transfer_fee <= df.sum_transfer_fee) {	// 2-1) fw <= df 
				return 1;
			}
			else { return 3; }	// 2-2) df < fw
		}
		else if (mf.sum_ability == df.sum_ability && df.sum_ability > fw.sum_ability) {	// 4) mf = df > fw
			if (mf.sum_transfer_fee <= df.sum_transfer_fee) {	// 2-1) mf <= df 
				return 2;
			}
			else { return 3; }	// 2-2) df < mf
		}
		// if one player has biggest ability
		else if (fw.sum_ability > mf.sum_ability && fw.sum_ability > df.sum_ability) {	// 5) fw > mf, df
			return 1;
		}
		else if (mf.sum_ability > fw.sum_ability && mf.sum_ability > df.sum_ability) {	// 6) mf > fw, dw
			return 2;
		}
		else if (df.sum_ability > fw.sum_ability && df.sum_ability > mf.sum_ability) {	// 7) df > fw, mf
			return 3;
		}
	}
	//if df flag is false
	else if (fw_flag && mf_flag && !df_flag) {
		if (fw.sum_ability == mf.sum_ability) {	// fw = mf
			if (mf.sum_transfer_fee < fw.sum_transfer_fee) {	//mf < fw (fee)
				return 2;
			}
			else { return 1; }	// fw <= mf (fee)
		}
		else if (fw.sum_ability > mf.sum_ability) {	// fw > mf
			return 1;
		}
		else { return 2; }	// mf > fw
	}
	//if mf flag is false
	else if (fw_flag && !mf_flag && df_flag) {	
		if (fw.sum_ability == df.sum_ability) {	// fw = df
			if (df.sum_transfer_fee < fw.sum_transfer_fee) {	//df < fw (fee)
				return 3;
			}
			else { return 1; }	// fw <= df (fee)
		}
		else if (fw.sum_ability > df.sum_ability) {	// fw > df
			return 1;
		}
		else { return 3; }	// df > fw
	}
	//if fw flag is false
	else if (!fw_flag && mf_flag && df_flag) {
		if (mf.sum_ability == df.sum_ability) {	// mf = df
			if (df.sum_transfer_fee < mf.sum_transfer_fee) {	//df < mf (fee)
				return 3;
			}
			else { return 2; }	// mf <= df (fee)
		}
		else if (mf.sum_ability > df.sum_ability) {	// mf > df
			return 2;
		}
		else { return 3; }	// df > mf
	}
	//if fw only true
	else if (fw_flag && !mf_flag && !df_flag) {
		return 1;
	}
	// if mf only true
	else if (!fw_flag && mf_flag && !df_flag) {
		return 2;
	}
	//if df only true
	else if (!fw_flag && !mf_flag && df_flag) {
		return 3;
	}
	//if all three false, send error
	else {
		return -1;
	}
}


