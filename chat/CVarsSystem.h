#pragma once

#include "I_CVarSystem.h"



class CVarSystem : ICvarSystem
{
public:
	CVarSystem();
	~CVarSystem();

public:
	virtual void Init();
	virtual void LoadCfg(const char* nameFile);
	virtual std::map<std::string, std::string>* getMapList();
	virtual std::string getValue(std::string key);

private:
	const char* pDataName = "app.cfg";
	std::map<std::string, std::string>* ListCfg;


};