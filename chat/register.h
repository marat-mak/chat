#pragma once
#include "container.h"
#include "user.h"


string name;
string login;
string password;
short usersNum = 0;

Container<User> users(1);

void reg()
{
	cout << "Enter username: ";
	cin >> name;
	cout << "Enter login: ";
	cin >> login;
	cout << "Enter password: ";
	cin >> password;
	users.addItem(User(name, login, password));
	++usersNum;
}

void signUp()
{
	cout << "Enter login: ";
	cin >> login;
	cout << "Enter password: ";
	cin >> password;
	for (int i = 0; i < users.getSize(); ++i)
	{
		if (users.operator[](i).getLogin() == login && users.operator[](i).getPassword() == password)
			cout << "Login correct" << endl;
	}
}