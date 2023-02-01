#pragma once
#include <string>
#include <iostream>
using namespace std;

class User
{
private:
	//string _name;
	string _login;
	string _password;
public:
	User(string login, string password);
	~User() = default;
	void show();
	string getLogin();
	string getPassword();
	friend ostream& operator<<(ostream& output, const User& u);
};
