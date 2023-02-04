#pragma once
#include "container.h"
#include "user.h"

string login;
string password;
string name;
short usersNum = 0;
Container<User>* users = new Container<User>[3];
void reg()
{
	cout << "Enter username: ";
	cin >> name;
	cout << "Enter login: ";
	cin >> login;
	cout << "Enter password: ";
	cin >> password;
	users->addItem(User(name, login, password));
	//++usersNum;
}