#include <string>
#include <iostream>
#include "container.h"
#include "register.h"
#include "user.h"
#include "message.h"


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
			try { signUp(); }
			catch (const char* ex) 
			{
				cout << ex << endl;
			}
			break;
		case 2:		
			try { reg(); }
			catch (const char* ex)
			{
				cout << ex << endl;
			}
			break;
		case 3:
			exit(0);
		default:
			break;
		}
		cout << "============================================\n";
	//	for (int i = 0; i <= usersNum; ++i)
	//		{
	//		cout << users.operator[](i).getName() << " " << users.operator[](i).getLogin() << endl;
			//users.operator[](i).show();
		//	}
	//	cout << "============================================\n";
		//++count;
	}
	
	return 0;
}