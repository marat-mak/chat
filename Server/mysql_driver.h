#pragma once
#include "I_SQL_Driver.h"
#include <conncpp.hpp>


class mysql_driver : Isql_Core
{


public:
	//Вызывается для инициализации класса
	mysql_driver();
	~mysql_driver();


	//Isql_Core
	virtual void Init() override;
	virtual bool IsRun() override;
	virtual void ConnectDB(const char* ip, const char* user, const char* pass, const char* dbName) override;
	virtual bool SetDBName(const char* dbName) override;
	virtual void Disconnect() override;
	virtual void ConnectDB(MySQL_user& MysqlContext);

	//~Isql_Core
	virtual int getCountUsers() override;
	virtual bool AutchUser(std::string login, std::string pass, std::string &result) override;
	virtual int RegisterUser(std::string login, std::string username, std::string pass) override;
	virtual int UserList(std::string &result) override;
	virtual std::string  ReadMessageALL(int id = 0) override;


	virtual bool CheckUserName(std::string name);
	virtual bool CheckLogin(std::string login);
	virtual int GetUserID(std::string name);
	virtual bool WriteMessage(std::string client_from, std::string nickname_from,
		std::string client_to, std::string nickname_to, std::string message);


private:
	
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;


	bool statusConnectDB = false;
};

