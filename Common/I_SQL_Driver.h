#pragma once

//Интерфейс реализует основные функции которые нужны для работы класса, 
//То есть открывает возможность создавать классы которые работают не только с Mysql
#include <string>
#include <list>

struct MySQL_user
{
	std::string ip;
	std::string user;
	std::string pass;
	std::string dbName;
};


struct Message
{
	std::string snickname;
	std::string smessage;

	Message(std::string nickname, std::string message)
	{
		snickname = nickname;
		smessage = message;
	}

};


struct Isql_Core
{
	//Вызывается для инициализации класса
	virtual void Init() = 0;
	virtual bool IsRun() = 0;
	virtual void ConnectDB(MySQL_user &MysqlContext) = 0;
	virtual void ConnectDB(const char* ip, const char* user, const char* pass, const char* dbName) = 0;
	virtual bool SetDBName(const char* dbName) = 0;
	virtual void Disconnect() = 0;


	//Типизация запросов, то есть конкретный запрос и конкретный ответ (к сожалению это не php)
	virtual int getCountUsers() = 0;
	virtual bool AutchUser(std::string login, std::string pass, std::string& result) = 0;
	virtual int RegisterUser(std::string login, std::string username, std::string pass) = 0;
	virtual int UserList(std::string &result) = 0;
	virtual std::string ReadMessageALL(int id = 0) = 0;


	virtual bool CheckUserName(std::string name) = 0;
	virtual bool CheckLogin(std::string login) = 0;
	virtual int GetUserID(std::string name) = 0;
	virtual bool WriteMessage(std::string client_from, std::string nickname_from, 
		std::string client_to, std::string nickname_to, std::string message) = 0;


};


