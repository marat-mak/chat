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
    cout << "Enter username:" << endl;
    cin >> name;
    for (int i = 0; i < users.getSize(); i++)
    {
        if (users[i].getName() == name) throw "name is busy";
    }
    cout << "Enter login:" << endl;
    cin >> login;
    for (int i = 0; i < users.getSize(); i++)
    {
        if (users[i].getLogin() == login) throw "login is busy";
    }
    cout << "Enter password (min 6 characters): " << endl;
    int ch = 0;
    while (true)
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
                cout << "press ESC to cancel" << endl << endl;
                cout << "Enter password (min 6 characters): " << endl;
                password.clear();
                continue;
            }
            else
            {
                users.addItem(User(name, login, password));
                cout << "\nUser " << name << " registered" << endl;
                password.clear();
                break;
            }
        }

        if (ch == 8)
        {
            cout << (char)8 << ' ' << char(8);

            if (!password.empty())
            {
                password.erase(password.length() - 1);
            }
        }
        else
        {
            cout << '*';// Замена символов на *
            password += (char)ch;
            // Преврашение кода из целого числа в символ.
        }
        if (ch == 27)
        {
            break;
        }
    }
}

bool signUp()
{
    string name;
    string login;
    string password;

    SetConsoleTextAttribute(hConsole, 13);
    cout << "Enter login:" << endl;
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

void userMenu()
{
    SetConsoleTextAttribute(hConsole, 14);
    cout << "Press [r] - read message; [w] - write message; [s] - show users; [any] - exit to main menu" << endl;
    int ch = 0;
    ch = _getche();
    cout << endl;
    if (ch == 114)
    {
        readMessage();
    }
    if (ch == 119)
    {
        try { writeMessage(); }
        catch (const char* ex)
        {
            cout << ex << endl;
            userMenu();
        }
    }
    if (ch == 115)
    {
        showUsers();
    }
    else
    {
        return;
    }
}

void readMessage()
{
    cout << "=============================================" << endl;
    for (int i = 0; i < mes.getSize(); i++)
    {
        if (mes[i].getTo() == currentUser || mes[i].getTo() == "all" || mes[i].getFrom() == currentUser)
        {
            if(mes[i].getFrom() == currentUser)  cout << "You: -> " << mes[i].getMessage() << endl;
        
            else cout << mes[i].getFrom() << ": " << mes[i].getMessage() << endl;
        }
    }
    cout << "=============================================" << endl;
    userMenu();
}

void writeMessage()
{
    string to;
    string sms;
    bool test = false;
    SetConsoleTextAttribute(hConsole, 7);
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
