#include "message.h"


Message::Message(std::string from, std::string to, std::string message) :_from(from), _to(to), _message(message) {}

void Message::show()
{
	std::cout << _from << " " << _message;
}

std::string Message::getFrom()
{
	return _from;
}

std::string Message::getTo()
{
	return _to;
}

std::string Message::getMessage()
{
	return _message;
}

std::ostream& operator<<(std::ostream& output, const Message& m)
{
	output << m._from << " " << m._message << std::endl;
	return output;
	}
