#pragma once
#include <string>
#include <iostream>


class Message
{
private:
	std::string _from;
	std::string _to;
	std::string _message;
public:
	Message() = default;
	Message(std::string from, std::string to, std::string message);
	~Message() = default;
	void show();
	std::string getFrom();
	std::string getTo();
	std::string getMessage();
	friend std::ostream& operator<<(std::ostream& output, const Message& u);
};

