#pragma once

#include <stdlib.h>
#include "container.h"
#include "user.h"
#include "message.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>


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
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void reg()
{
	SetConsoleTextAttribute(hConsole, 11);
	cout << "Введите имя пользователя: ";
	cin >> name;
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getName() == name) throw "пользователь с таким именем уже существует";
	}
	cout << "Enter login: ";
	cin >> login;
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getLogin() == login) throw "данный логин занят";
	}
	while (true)
	{
		cout << "EВведите пароль (минимум 6 символов): " << endl;
		cin >> password;

		if (password.length() <= 5)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "пароль слишком короткий" << endl << endl;
			cout << "нажмите q для возврата в меню" << endl << endl;

			if (password == "q")
			{
				break;
				//exit(0);
			}
		}
		else
			break;
	}

	users.addItem(User(name, login, password));
}

bool signUp()
{
	SetConsoleTextAttribute(hConsole, 13);
	cout << "Введите логин: ";
	cin >> login;
	cout << "Введите пароль: ";
	cin >> password;
	for (int i = 0; i < users.getSize(); ++i)
	{
		if (users[i].getLogin() == login && users[i].getPassword() == password)
		{
			system("cls");
			cout << "Привет " << users[i].getName() << "!" << endl;
			currentUser = users[i].getName();
			return true;
		}					
	}
	throw "неверный логин или пароль";
}



void userMenu()
{
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Введите [r] - прочитать сообщения; [w] - написать сообщение; [s] - вывести список пользователей; любой другой символ для возврата в главное меню" << endl;
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
	SetConsoleTextAttribute(hConsole, 9);
	cout << "введите имя адресата(или введите all чтобы отправить сообщение всем пользователям)\n: ";
	cin >> to;
  cin.ignore();
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getName() == to || to == "all")
		{
			test = true;
			continue;
		}
	}
	if (test == false) throw "пользователя с таким именем нет в базе чата, проверьте список пользователей";
	cout << "введите сообщение: ";
	getline(cin, sms);
	messages.addItem(Message(currentUser, to, sms));
	userMenu();
}

void showUsers()
{
	SetConsoleTextAttribute(hConsole, 11);
	cout << "=============================================" << endl;
	for (int i = 0; i < users.getSize();i++)
	{
		cout << i + 1 << ". " << users[i].getName() << endl;
	}
	cout << "=============================================" << endl;
	userMenu();
}