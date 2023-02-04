#include "register.h"

using namespace std;

int main()
{
	//User* user = new User[3];
	//int count = 0;
 //кол-во зарегистрированных пользователей
	while (true)
	{
		cout << "Welcome to chat" << endl;
		cout << "Press [1] - login; [2] - registry new user; [3] - exit" << endl;
		short choice;
		cin >> choice;

		
		switch (choice)
		{
		case 1:
			cout << "Enter login: ";
			cin >> login;
			cout << "Enter password: ";
			cin >> password;
			for (int i = 0; i < users->getSize(); ++i)
			{
				if (users->operator[](i).getLogin() == login && users->operator[](i).getPassword() == password)
					cout << "Login correct" << endl;
				
			}
			
				
			break;

		case 2:
		
			reg();
			
			
			break;
		

		case 3:
			//delete[] users;
			exit(0);

		default:
			break;
		}
		cout << "============================================\n";
		for (int i = 0; i <= usersNum; ++i)
			{
			
				users->operator[](i).show();
		//		cout << user[i]->getLogin() << endl;
			}
		cout << "============================================\n";
		//++count;
	}
	
	return 0;
}