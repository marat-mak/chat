#pragma once
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
	cout << "Enter username: ";
	cin >> name;
	cout << "Enter login: ";
	cin >> login;
	cout << "Enter password: ";
	cin >> password;
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getLogin() == login) throw "login is busy";   // по хорошему бы вводить логин первым и сразу его проверять 
	}																//чтоб лишний раз не вводить пароль и имя если логин занят
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
		writeMessage();
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
	cout << "to whom(write 'all' for all): ";
	cin >> to;
	cin.ignore();
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