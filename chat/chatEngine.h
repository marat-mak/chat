#pragma once

#include <stdlib.h>
#include "container.h"
#include "user.h"
#include "message.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>


string currentUser;


void readMessage();
void writeMessage();
void userMenu();
void showUsers();

Container<User> users;
Container<Message> mes;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void reg()
{
    string name;
    string login;
    string password;

    SetConsoleTextAttribute(hConsole, 11);
    cout << "Enter username: ";
    cin >> name;
    for (int i = 0; i < users.getSize(); i++)
    {
        if (users[i].getName() == name) throw "name is busy";
    }
    cout << "Enter login: ";
    cin >> login;
    for (int i = 0; i < users.getSize(); i++)
    {
        if (users[i].getLogin() == login) throw "login is busy";
    }

    cout << "Enter password (min 6 characters): " << endl;
    int ch = 0;
    while (password != "q")
    {
        ch = _getch();
        if (ch == 13)
        {
            if (password.length() <= 5)
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << endl;
                cout << "the password is too short" << endl << endl;
                cout << "please try again" << endl << endl;
                cout << "please enter 'q' to exit the main menu" << endl << endl;
                cout << "Enter password (min 6 characters): " << endl;
                password.clear();
                continue;
            }
            else
            {
                users.addItem(User(name, login, password));
                password.clear();
                break;
            }
        }

        if (ch == 8)
        {

            cout << (char)8 << ' ' << char(8);


            if (!password.empty())

                password.erase(password.length() - 1);

        }
        else
        {
            cout << '*';// Замена символов на *
            password += (char)ch;
            // Преврашение кода из целого числа в символ.
        }

    }
}

bool signUp()
{
    string name;
    string login;
    string password;

    SetConsoleTextAttribute(hConsole, 13);
    cout << "Enter login: ";
    cin >> login;
    cout << "Enter password: ";
    int ch = 0;
    cout << endl;
    while (true)
    {
        ch = _getch();
        if (ch == 13)
        {
            for (int i = 0; i < users.getSize(); ++i)
            {
                if (users[i].getLogin() == login && users[i].getPassword() == password)
                {
                    system("cls");
                    cout << "Login correct! Hello " << users[i].getName() << endl;
                    currentUser = users[i].getName();
                    return true;
                    break;
                }
            }
            cout << endl;
            throw "incorrect login or password";

        }

        if (ch == 8)
        {

            cout << (char)8 << ' ' << char(8);


            if (!password.empty())

                password.erase(password.length() - 1);

        }
        else
        {
            cout << '*';// Замена символов на *
            password += (char)ch;
            // Преврашение кода из целого числа в символ.
        }

    }
}

//bool signUp()
//{
//    string name;
//    string login;
//    string password;

//    SetConsoleTextAttribute(hConsole, 13);
//    cout << "Enter login: ";
//    cin >> login;
//    cout << "Enter password: ";

//    cin >> password;

//    for (int i = 0; i < users.getSize(); ++i)
//    {
//        if (users[i].getLogin() == login && users[i].getPassword() == password)
//        {
//            system("cls");
//            cout << "Login correct! Hello " << users[i].getName() << endl;
//            currentUser = users[i].getName();
//            return true;
//        }
//    }
//    throw "incorrect login or password";
//}

void userMenu()
{
    SetConsoleTextAttribute(hConsole, 14);
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

    for (int i = 0; i < mes.getSize(); i++)
    {
        if (mes[i].getTo() == currentUser || mes[i].getTo() == "all")
            cout << mes[i].getFrom() << ": " << mes[i].getMessage() << endl;
    }
    userMenu();
}

void writeMessage()
{

    string to;
    string sms;
    bool test = false;
    SetConsoleTextAttribute(hConsole, 9);
    cout << "to whom(write 'all' for all): ";
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
    if (test == false) throw "no user in base";
    cout << "enter message: ";
    getline(cin, sms);
    mes.addItem(Message(currentUser, to, sms));
    userMenu();
}

void showUsers()
{
    SetConsoleTextAttribute(hConsole, 11);
    cout << "=============================================" << endl;
    for (int i = 0; i < users.getSize(); i++)
    {
        cout << i + 1 << ". " << users[i].getName() << endl;
    }
    cout << "=============================================" << endl;
    userMenu();
}
