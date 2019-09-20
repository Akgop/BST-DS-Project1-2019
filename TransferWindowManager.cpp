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
	// Inorder �������� �����ʺ��� �����.
	//
	stack<TreeNode*> sfw;
	stack<TreeNode*> smf;
	stack<TreeNode*> sdf;

	stack<TreeNode*> temp_sfw;
	stack<TreeNode*> temp_smf;
	stack<TreeNode*> temp_sdf;
	// 1. ���� �ɷ�ġ�� ���� 3 �������� ����.
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

	// 2. ���� ��
	while (1) {
		//SoccerTeam * team = new SoccerTeam(pfwCur->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data);
		best_team = { pfwCur->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data };

		//���� ���� ���� �ؾߵ�.
		temp_sfw = sfw;
		temp_smf = smf;
		temp_sdf = sdf;

		if (best_team.sum_transfer_fee <= this->m_budget) {	//������ �����ϸ�.
			break;
		}
		else {	// 3. �������� �ɷ�ġ ���� �� ����
			// 3-1. fw ���� ��� ����
			pfwNext = pfwCur;
			while (1) {
				if (pfwNext->m_left != NULL) {	//fw ���� child �� ������
					pfwNext = pfwNext->m_left;	//�������� �̵�
					while (1) {
						if (pfwNext->m_right != NULL) {	//fw ������ child ������
							sfw.push(pfwNext);	//���ÿ� �ְ�
							pfwNext = pfwNext->m_right;	//���������� �̵�
						}
						else {	//fw ������ child ������
							break;
						}
					}
					if (pfwNext->m_data.m_transfer_fee < pfwCur->m_data.m_transfer_fee) {	//���� ��尡 �� �θ�
						break;	// pNext ����
					}
					else { continue; }	//�ƴϸ� �ٽ� �� ���� �ö�
				}
				else {	//������
					if (sfw.empty()) {
						pfwNext = pfwCur;	//���� ģ���� ����.
						flag_fw = false;	//�����ٴ� ǥ��.
						break;
					}
					pfwNext = sfw.top();
					sfw.pop();
					if (pfwNext->m_data.m_transfer_fee < pfwCur->m_data.m_transfer_fee) {	//���� ��尡 �� �θ�
						break;	// pNext ����
					}
					else { continue; }	//�ƴϸ� �ٽ� �ö�
				}
			}
			// 3-2. mf ���� ��� ����
			pmfNext = pmfCur;
			while (1) {
				if (pmfNext->m_left != NULL) {	//fw ���� child �� ������
					pmfNext = pmfNext->m_left;	//�������� �̵�
					while (1) {
						if (pmfNext->m_right != NULL) {	//fw ������ child ������
							smf.push(pmfNext);	//���ÿ� �ְ�
							pmfNext = pmfNext->m_right;	//���������� �̵�
						}
						else {	//fw ������ child ������
							break;
						}
					}
					if (pmfNext->m_data.m_transfer_fee < pmfCur->m_data.m_transfer_fee) {	//���� ��尡 �� �θ�
						break;	// pNext ����
					}
					else { continue; }	//�ƴϸ� �ٽ� �� ���� �ö�
				}
				else {	//������'
					if (smf.empty()) {
						pmfNext = pmfCur;	//���� ģ���� ����.
						flag_mf = false;	//�����ٴ� ǥ��.
						break;
					}
					pmfNext = smf.top();
					smf.pop();
					if (pmfNext->m_data.m_transfer_fee < pmfCur->m_data.m_transfer_fee) {	//���� ��尡 �� �θ�
						break;	// pNext ����
					}
					else { continue; }	//�ƴϸ� �ٽ� �ö�
				}
			}
			// 3-3. df ���� ��� ����
			pdfNext = pdfCur;
			while (1) {
				if (pdfNext->m_left != NULL) {	//fw ���� child �� ������
					pdfNext = pdfNext->m_left;	//�������� �̵�
					while (1) {
						if (pdfNext->m_right != NULL) {	//fw ������ child ������
							sdf.push(pdfNext);	//���ÿ� �ְ�
							pdfNext = pdfNext->m_right;	//���������� �̵�
						}
						else {	//fw ������ child ������
							break;
						}
					}
					if (pdfNext->m_data.m_transfer_fee < pdfCur->m_data.m_transfer_fee) {	//���� ��尡 �� �θ�
						break;	// pNext ����
					}
					else { continue; }	//�ƴϸ� �ٽ� �� ���� �ö�
				}
				else {	//������
					//������ ������ (���� ������ ���϶�)
					if (sdf.empty()) {
						pdfNext = pdfCur;	//���� ģ���� ����.
						flag_df = false;	//�����ٴ� ǥ��.
						break;
					}
					pdfNext = sdf.top();
					sdf.pop();
					if (pdfNext->m_data.m_transfer_fee < pdfCur->m_data.m_transfer_fee) {	//���� ��尡 �� �θ�
						break;	// pNext ����
					}
					else { continue; }	//�ƴϸ� �ٽ� �ö�
				}
			}

			//SoccerTeam * fw_team = new SoccerTeam(pfwNext->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data);
			SoccerTeam fw_team, mf_team, df_team;
			fw_team = { pfwNext->m_data, pmfCur->m_data, pdfCur->m_data, pgkCur->m_data };
			mf_team = { pfwCur->m_data, pmfNext->m_data, pdfCur->m_data, pgkCur->m_data };
			df_team = { pfwCur->m_data, pmfCur->m_data, pdfNext->m_data, pgkCur->m_data };
			
			// 4. �ɷ�ġ �� ���� �� �Լ�.
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
	// ���� ������ �� ���ٸ� fw , mf������ ����.
	// �� �������� ������ �ȳ��ٸ� �״��� mf �� df�� ������ �Ǿ�����.

	//���� �Ѱ�ġ�� �������� ���Ѱ��
	if (fw_flag && mf_flag && df_flag) {
		// 4-1. 3���� �ɷ�ġ�� �� �������
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
		// 4-2. 2���� �ɷ�ġ�� �ִ��� ���.
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
		// 4-3. 1���� ���� ���.
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
	//df �� �̹� �Ѱ��� ���
	else if (fw_flag && mf_flag && !df_flag) {
		if (fw.sum_ability == mf.sum_ability) {	// fw = mf
			if (mf.sum_transfer_fee < fw.sum_transfer_fee) {	//mf < fw (����)
				return 2;
			}
			else { return 1; }	// fw <= mf (����)
		}
		else if (fw.sum_ability > mf.sum_ability) {	// fw > mf
			return 1;
		}
		else { return 2; }	// mf > fw
	}
	//mf �� �̹� �Ѱ��� ���
	else if (fw_flag && !mf_flag && df_flag) {	
		if (fw.sum_ability == df.sum_ability) {	// fw = df
			if (df.sum_transfer_fee < fw.sum_transfer_fee) {	//df < fw (����)
				return 3;
			}
			else { return 1; }	// fw <= df (����)
		}
		else if (fw.sum_ability > df.sum_ability) {	// fw > df
			return 1;
		}
		else { return 3; }	// df > fw
	}
	//fw �� �̹� �Ѱ��� ���
	else if (!fw_flag && mf_flag && df_flag) {
		if (mf.sum_ability == df.sum_ability) {	// mf = df
			if (df.sum_transfer_fee < mf.sum_transfer_fee) {	//df < mf (����)
				return 3;
			}
			else { return 2; }	// mf <= df (����)
		}
		else if (mf.sum_ability > df.sum_ability) {	// mf > df
			return 2;
		}
		else { return 3; }	// df > mf
	}
	//mf, df�� �Ѱ��� ���
	else if (fw_flag && !mf_flag && !df_flag) {
		return 1;
	}
	//fw, df�� �Ѱ��� ���
	else if (!fw_flag && mf_flag && !df_flag) {
		return 2;
	}
	//fw, mf�� �Ѱ��� ���
	else if (!fw_flag && !mf_flag && df_flag) {
		return 3;
	}
	else {	//�´� �Ѱ��� ��� ����.
		return -1;
	}
}


