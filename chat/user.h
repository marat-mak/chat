#pragma once
#include <string>
#include <iostream>
//using namespace std;


class User
{
private:
	string _name;
	string _login;
	string _password;
public:
	User() = default;
	User(string name, string login, string password);
	~User() = default;
	void show();                                           //видимо уже не нужно
	string getName();
	string getLogin();
	string getPassword();
	friend ostream& operator<<(ostream& output, const User& u);
};
