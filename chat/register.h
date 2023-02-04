#pragma once
#include "container.h"
#include "user.h"
#include "message.h"

string name;
string login;
string password;
short usersNum = 0;      //нам точно нужны
int messagesNum = 0;					//эти переменные? есть же getSize  =)
string currentUser;

void readMessage();
void writeMessage();
void userMenu();

Container<User> users(1);
Container<Message> messages(1);

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
		if (users[i].getLogin() == login) throw "login is bussy";   // по хорошему бы вводить логин первым и сразу его проверять 
	}																//чтоб лишний раз не вводить пароль и имя если логин занят
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
		{
			cout << "Login correct! Hello " << users[i].getName() << endl;
			currentUser = login;
			userMenu();
		}
		
	}
	throw "incorrect user or password";
}



void userMenu()
{
	cout << "Press [1] - read message; [2] - write message; [3] - exit" << endl;
	short ch;
	cin >> ch;
	switch (ch)
	{
	case 1:
		readMessage();
		break;
	case 2:
		writeMessage();
		break;
	case 3:
		exit(0);
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
	cout << "enter message: ";
	cin >> sms;
	messages.addItem(Message(currentUser, to, sms));
	messagesNum++;
	userMenu();
}