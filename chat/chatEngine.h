#pragma once
#include <stdlib.h>
#include "container.h"
#include "user.h"
#include "message.h"

string name;
string login;
string password;
string currentUser;

void readMessage();
void writeMessage();
void userMenu();
void showUsers();

Container<User> users;
Container<Message> messages;

void reg()
{
	bool bussy=false;
	cout << "Enter login: ";
	do
	{
		cin >> login;
		for (int i = 0; i < users.getSize(); i++)
		{
			if (users[i].getLogin() == login)
			{
				cout << "Login is busy, try another login:";
				bussy = true;
				break;
			}
			else bussy = false;
		}
	} while (bussy);
	/*for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getLogin() == login) throw "login is busy";
	}*/
	cout << "Enter username: ";
	cin >> name;
	cout << "Enter password: ";
	cin >> password;											
	users.addItem(User(name, login, password));	
}

bool signUp()
{
	cout << "Enter login: ";
	cin >> login;
	cout << "Enter password: ";
	cin >> password;
	for (int i = 0; i < users.getSize(); ++i)
	{
		if (users[i].getLogin() == login && users[i].getPassword() == password)
		{
			system("cls");
			cout << "Login correct! Hello " << users[i].getName() << endl;
			currentUser = login;
			return true;
		}					
	}
	throw "incorrect user or password";
}



void userMenu()
{
	
	cout << "Press [r] - read message; [w] - write message; [s] - show users; [any] - exit to main menu" << endl;
	char ch = 'null';
	cin >> ch;
	switch (ch)
	{
	case 'r':
		
		readMessage();
		break;
	case 'w':
		try { writeMessage(); }
		catch (const char* ex)
		{
			cout << ex << endl;
			userMenu();
		}
		break;
	case 's':
		showUsers();
		break;
	default:
		break;
	}
}

void readMessage()
{
	 
	for (int i = 0; i < messages.getSize(); i++)
	{
		if (messages[i].getTo() == currentUser || messages[i].getTo() == "all")
			cout << messages[i].getFrom() << ": " << messages[i].getMessage() << endl;
	}
	userMenu();
}

void writeMessage()
{
	
	string to;
	string sms;
	bool test = false;
	cout << "to whom(write 'all' for all): ";
	cin >> to;
  cin.ignore();
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getLogin() == to || to == "all")
		{
			test = true;
			continue;
		}
	}
	if (test == false) throw "no user in base";
	cout << "enter message: ";
	getline(cin, sms);
	messages.addItem(Message(currentUser, to, sms));
	userMenu();
}

void showUsers()
{
	
	cout << "=============================================" << endl;
	for (int i = 0; i < users.getSize();i++)
	{
		cout << "name: " << users[i].getName() << "    login: " << users[i].getLogin() << endl;
	}
	cout << "=============================================" << endl;
	userMenu();
}