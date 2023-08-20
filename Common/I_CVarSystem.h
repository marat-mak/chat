#pragma once
//система предназначена для хранения, загрузки контейнера по типу ключ => значение

#include <map>
#include <string>

struct sCvar
{
	const char* name;
	const char* value;
};

struct ICvarSystem
{
	virtual void Init() = 0;
	virtual void LoadCfg(const char* nameFile) = 0;
	virtual std::map<std::string, std::string> *getMapList() = 0;
	virtual std::string getValue(std::string key) = 0;
};