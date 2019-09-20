#include "TransferWindowManager.h"
#include <fstream>

TransferWindowManager::SoccerTeam::SoccerTeam()
{
	//You don't need to edit this function.
}

TransferWindowManager::SoccerTeam::SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk)
{
	this->fw = fw;
	this->mf = mf;
	this->df = df;
	this->gk = gk;

	this->sum_transfer_fee = fw.m_transfer_fee + mf.m_transfer_fee + df.m_transfer_fee + gk.m_transfer_fee;
	this->sum_ability = fw.m_ability + mf.m_ability + df.m_ability + gk.m_ability;
}

std::ostream& operator<<(ostream& os, const TransferWindowManager::SoccerTeam& team)
{
	os << team.fw << std::endl;
	os << team.mf << std::endl;
	os << team.df << std::endl;
	os << team.gk << std::endl;

	os << "sum_transfer_fee " << team.sum_transfer_fee << std::endl;
	os << "sum_ability " << team.sum_ability << std::endl;

	return os;
}


TransferWindowManager::TransferWindowManager(string file_dir, int budget)
{
	this->m_budget = budget;

	ifstream in(file_dir);
	string line;

	while (getline(in, line))
	{
	//Fill in the code to initialize 4 Binary Search Trees(fw, mf, df, gk)
		string player_name;
		string position;
		int fee;
		int ability;

		char line_char[100];
		char * context = NULL;
		strcpy(line_char, line.c_str());
		char * temp = strtok(line_char, ",");

		player_name = temp;

		temp = strtok(NULL, ", ");
		position = temp;

		temp = strtok(NULL, ", ");
		fee = atoi(temp);

		temp = strtok(NULL, ", ");
		ability = atoi(temp);
	
		SoccerPlayerData* spd = new SoccerPlayerData(player_name, position, fee, ability);
		if (position == "Forward") {
			fwBST.insert(*spd);
		}
		else if (position == "Midfielder") {
			mfBST.insert(*spd);
		}
		else if (position == "Defender") {
			dfBST.insert(*spd);
		}
		else {
			gkBST.insert(*spd);
		}
	}
}

ostream& operator<<(ostream& os, const TransferWindowManager& manager)
{
	os << "********Forward List********" << std::endl;
	os << manager.fwBST;
	os << "****************************" << std::endl;

	os << "********Midflder List********" << std::endl;
	os << manager.mfBST;
	os << "*****************************" << std::endl;

	os << "********Defender List********" << std::endl;
	os << manager.dfBST;
	os << "*****************************" << std::endl;

	os << "********Goalkeeper List********" << std::endl;
	os << manager.gkBST;
	os << "*******************************" << std::endl;

	return os;
}

TransferWindowManager::SoccerTeam TransferWindowManager::getBestTeam()
{
	SoccerTeam best_team;
	
	//Fill in the code to search the best_team from 4 BSTs
	//The datas for best team must be stored in the variable best_team.
	//*best team means the most powerful team that is defined in the project introduction file. 
	
	TreeNode *pfwCur, *pmfCur, *pdfCur, *pgkCur;
	TreeNode *pfwNext, *pmfNext, *pdfNext;
	bool flag_fw = true, flag_mf = true, flag_df = true;

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
	// Inorder 역순으로 오른쪽부터 가면됨.
	//
	stack<TreeNode*> sfw;
	stack<TreeNode*> smf;
	stack<TreeNode*> sdf;

	stack<TreeNode*> temp_sfw;
	stack<TreeNode*> temp_smf;
	stack<TreeNode*> temp_sdf;
	// 1. 가장 능력치가 좋은 3 선수부터 시작.
	while (1) {
		if (pfwCur != NULL) {
			sfw.push(pfwCur);
			pfwCur = pfwCur->m_right;
		}
		else {
			break;
		}
	}
	while (1) {
		if (pmfCur != NULL) {
			smf.push(pmfCur);
			pmfCur = pmfCur->m_right;
		}
		else {
			break;
		}
	}
	while (1) {
		if (pdfCur != NULL) {
			sdf.push(pdfCur);
			pdfCur = pdfCur->m_right;
		}
		else {
			break;
		}
	}

	pfwCur = sfw.top();		sfw.pop();
	pmfCur = smf.top();		smf.pop();
	pdfCur = sdf.top();		sdf.pop();

	// 2. 예산 비교
	while (1) {
		//SoccerTeam * team = new SoccerTeam(pfwCur->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data);
		best_team = { pfwCur->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data };

		//스택 깊은 복사 해야됨.
		temp_sfw = sfw;
		temp_smf = smf;
		temp_sdf = sdf;

		if (best_team.sum_transfer_fee <= this->m_budget) {	//가격이 적합하면.
			break;
		}
		else {	// 3. 다음으로 능력치 좋은 팀 선정
			// 3-1. fw 다음 노드 선정
			pfwNext = pfwCur;
			while (1) {
				if (pfwNext->m_left != NULL) {	//fw 왼쪽 child 가 있으면
					pfwNext = pfwNext->m_left;	//왼쪽으로 이동
					while (1) {
						if (pfwNext->m_right != NULL) {	//fw 오른쪽 child 있으면
							sfw.push(pfwNext);	//스택에 넣고
							pfwNext = pfwNext->m_right;	//오른쪽으로 이동
						}
						else {	//fw 오른쪽 child 없으면
							break;
						}
					}
					if (pfwNext->m_data.m_transfer_fee < pfwCur->m_data.m_transfer_fee) {	//하위 노드가 더 싸면
						break;	// pNext 고정
					}
					else { continue; }	//아니면 다시 맨 위로 올라감
				}
				else {	//없으면
					if (sfw.empty()) {
						pfwNext = pfwCur;	//기존 친구로 복귀.
						flag_fw = false;	//끝났다는 표시.
						break;
					}
					pfwNext = sfw.top();
					sfw.pop();
					if (pfwNext->m_data.m_transfer_fee < pfwCur->m_data.m_transfer_fee) {	//하위 노드가 더 싸면
						break;	// pNext 고정
					}
					else { continue; }	//아니면 다시 올라감
				}
			}
			// 3-2. mf 다음 노드 선정
			pmfNext = pmfCur;
			while (1) {
				if (pmfNext->m_left != NULL) {	//fw 왼쪽 child 가 있으면
					pmfNext = pmfNext->m_left;	//왼쪽으로 이동
					while (1) {
						if (pmfNext->m_right != NULL) {	//fw 오른쪽 child 있으면
							smf.push(pmfNext);	//스택에 넣고
							pmfNext = pmfNext->m_right;	//오른쪽으로 이동
						}
						else {	//fw 오른쪽 child 없으면
							break;
						}
					}
					if (pmfNext->m_data.m_transfer_fee < pmfCur->m_data.m_transfer_fee) {	//하위 노드가 더 싸면
						break;	// pNext 고정
					}
					else { continue; }	//아니면 다시 맨 위로 올라감
				}
				else {	//없으면'
					if (smf.empty()) {
						pmfNext = pmfCur;	//기존 친구로 복귀.
						flag_mf = false;	//끝났다는 표시.
						break;
					}
					pmfNext = smf.top();
					smf.pop();
					if (pmfNext->m_data.m_transfer_fee < pmfCur->m_data.m_transfer_fee) {	//하위 노드가 더 싸면
						break;	// pNext 고정
					}
					else { continue; }	//아니면 다시 올라감
				}
			}
			// 3-3. df 다음 노드 선정
			pdfNext = pdfCur;
			while (1) {
				if (pdfNext->m_left != NULL) {	//fw 왼쪽 child 가 있으면
					pdfNext = pdfNext->m_left;	//왼쪽으로 이동
					while (1) {
						if (pdfNext->m_right != NULL) {	//fw 오른쪽 child 있으면
							sdf.push(pdfNext);	//스택에 넣고
							pdfNext = pdfNext->m_right;	//오른쪽으로 이동
						}
						else {	//fw 오른쪽 child 없으면
							break;
						}
					}
					if (pdfNext->m_data.m_transfer_fee < pdfCur->m_data.m_transfer_fee) {	//하위 노드가 더 싸면
						break;	// pNext 고정
					}
					else { continue; }	//아니면 다시 맨 위로 올라감
				}
				else {	//없으면
					//정말로 마지막 (가장 안좋은 놈일때)
					if (sdf.empty()) {
						pdfNext = pdfCur;	//기존 친구로 복귀.
						flag_df = false;	//끝났다는 표시.
						break;
					}
					pdfNext = sdf.top();
					sdf.pop();
					if (pdfNext->m_data.m_transfer_fee < pdfCur->m_data.m_transfer_fee) {	//하위 노드가 더 싸면
						break;	// pNext 고정
					}
					else { continue; }	//아니면 다시 올라감
				}
			}

			//SoccerTeam * fw_team = new SoccerTeam(pfwNext->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data);
			SoccerTeam fw_team, mf_team, df_team;
			fw_team = { pfwNext->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data };
			mf_team = { pfwCur->m_data, pmfNext->m_data, pdfCur->m_data, pgkCur->m_data };
			df_team = { pfwCur->m_data, pmfCur->m_data, pdfNext->m_data, pgkCur->m_data };
			
			// 4. 능력치 및 가격 비교 함수.
			if (getTeamSquad(fw_team, mf_team, df_team, flag_fw, flag_mf, flag_df) == 1) {
				pfwCur = pfwNext;	smf = temp_smf;		sdf = temp_sdf;
			}
			else if (getTeamSquad(fw_team, mf_team, df_team, flag_fw, flag_mf, flag_df) == 2) {
				pmfCur = pmfNext;	sfw = temp_sfw;		sdf = temp_sdf;
			}
			else if (getTeamSquad(fw_team, mf_team, df_team, flag_fw, flag_mf, flag_df) == 3) {
				pdfCur = pdfNext;	sfw = temp_sfw;		smf = temp_smf;
			}
		}
	}


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
	// 만약 끝까지 다 같다면 fw , mf순으로 리턴.
	// 그 다음에도 결판이 안난다면 그다음 mf 나 df가 빼지게 되어있음.

	//아직 한계치에 도달하지 못한경우
	if (fw_flag && mf_flag && df_flag) {
		// 4-1. 3개가 능력치가 다 같은경우
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
		// 4-2. 2개의 능력치가 최대인 경우.
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
		// 4-3. 1개가 높은 경우.
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
	//df 가 이미 한계인 경우
	else if (fw_flag && mf_flag && !df_flag) {
		if (fw.sum_ability == mf.sum_ability) {	// fw = mf
			if (mf.sum_transfer_fee < fw.sum_transfer_fee) {	//mf < fw (가격)
				return 2;
			}
			else { return 1; }	// fw <= mf (가격)
		}
		else if (fw.sum_ability > mf.sum_ability) {	// fw > mf
			return 1;
		}
		else { return 2; }	// mf > fw
	}
	//mf 가 이미 한계인 경우
	else if (fw_flag && !mf_flag && df_flag) {	
		if (fw.sum_ability == df.sum_ability) {	// fw = df
			if (df.sum_transfer_fee < fw.sum_transfer_fee) {	//df < fw (가격)
				return 3;
			}
			else { return 1; }	// fw <= df (가격)
		}
		else if (fw.sum_ability > df.sum_ability) {	// fw > df
			return 1;
		}
		else { return 3; }	// df > fw
	}
	//fw 가 이미 한계인 경우
	else if (!fw_flag && mf_flag && df_flag) {
		if (mf.sum_ability == df.sum_ability) {	// mf = df
			if (df.sum_transfer_fee < mf.sum_transfer_fee) {	//df < mf (가격)
				return 3;
			}
			else { return 2; }	// mf <= df (가격)
		}
		else if (mf.sum_ability > df.sum_ability) {	// mf > df
			return 2;
		}
		else { return 3; }	// df > mf
	}
	//mf, df가 한계인 경우
	else if (fw_flag && !mf_flag && !df_flag) {
		return 1;
	}
	//fw, df가 한계인 경우
	else if (!fw_flag && mf_flag && !df_flag) {
		return 2;
	}
	//fw, mf가 한계인 경우
	else if (!fw_flag && !mf_flag && df_flag) {
		return 3;
	}
	else {	//셋다 한계인 경우 에러.
		return -1;
	}
}


