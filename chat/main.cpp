#include "user.h"
using namespace std;

int main()
{
	User* user = new User[10];
	//int count = 0;
	short usersNum = 0; //кол-во зарегистрированных пользователей
	while (true)
	{
		cout << "Welcome to chat" << endl;
		cout << "Press [1] - login; [2] - registry new user; [3] - exit" << endl;
		short choice;
		cin >> choice;
		string login;
		string password;
		string name;
		
		switch (choice)
		{
		case 1:
			cout << "Enter login: ";
			cin >> login;
			cout << "Enter password: ";
			cin >> password;
			for (int i = 0; i < usersNum; ++i)
			{
				if (user[i].getLogin() == login && user[i].getPassword() == password)
					cout << "Login correct" << endl;
				
			}
			
				
			break;

		case 2:
		
			//cout << "Enter username: ";
			//cin >> name;
			cout << "Enter login: ";
			cin >> login;
			cout << "Enter password: ";
			cin >> password;
			user[usersNum] = User(login, password);	
			++usersNum;
			
			
			break;
		

		case 3:
			delete[] user;
			exit(0);

		default:
			break;
		}
		cout << "============================================\n";
		for (int i = 0; i <= usersNum; ++i)
			{
			
				user[i].show();
		//		cout << user[i]->getLogin() << endl;
			}
		cout << "============================================\n";
		//++count;
	}
	
	return 0;
}