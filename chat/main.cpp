#include "register.h"


using namespace std;

int main()
{

	while (true)
	{
		cout << "Welcome to chat" << endl;
		cout << "Press [1] - login; [2] - registry new user; [3] - exit" << endl;
		short choice;
		cin >> choice;		
		switch (choice)
		{
		case 1:			
			signUp();				
			break;
		case 2:		
			reg();					
			break;
		case 3:
			exit(0);
		default:
			break;
		}
		cout << "============================================\n";
		for (int i = 0; i <= usersNum; ++i)
			{
			cout << users.operator[](i).getName() << endl;
			users.operator[](i).show();
			}
		cout << "============================================\n";
		//++count;
	}
	
	return 0;
}