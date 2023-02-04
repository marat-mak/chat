#pragma once
#include <string>
#include <iostream>

using namespace std;

class Message
{
private:
	string _from;
	string _to;
	string _message;
public:
	Message() = default;
	Message(string from, string to, string message);
	~Message() = default;
	void show();
	string getFrom();
	string getTo();
	string getMessage();
	friend ostream& operator<<(ostream& output, const Message& u);
};

