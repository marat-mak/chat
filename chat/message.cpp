#include "message.h"


Message::Message(string from, string to, string message) :_from(from), _to(to), _message(message) {}

void Message::show()
{
	std::cout << _from << " " << _message;
}

string Message::getFrom()
{
	return _from;
}

string Message::getTo()
{
	return _to;
}

string Message::getMessage()
{
	return _message;
}

ostream& operator<<(ostream& output, const Message& m)
{
	output << m._from << " " << m._message << std::endl;
	return output;
	}
