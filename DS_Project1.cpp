#include <iostream>
#include "TransferWindowManager.h"

using namespace std;

//int main(int argc, char** argv)
int main()
{
	string file_dir = "C:\\Users\\nyc09\\source\\repos\\DS_Project1\\DS_Project1\\ShootForLog.txt";
	int budget = 2790;
	//TransferWindowManager transfer_window_manager(argv[1], atoi(argv[2]));
	TransferWindowManager transfer_window_manager(file_dir, budget);
	cout << transfer_window_manager << endl;	//print bst using operator overloading
	TransferWindowManager::SoccerTeam team = transfer_window_manager.getBestTeam();
	cout << "Best Players" << endl;
	cout << team << endl;
	cout << "-----" << endl;
	cout << "The Transfer window close" << endl;
	cout << transfer_window_manager << endl;
    return 0;
}

