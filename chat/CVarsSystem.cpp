#include "CVarsSystem.h"


#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include <regex>


CVarSystem::CVarSystem()
{


    this->ListCfg = new std::map<std::string, std::string>;
    this->Init();
}

CVarSystem::~CVarSystem()
{
}

void CVarSystem::Init()
{
    std::cout << "[CVarSystem] InitSystem\n";

    LoadCfg(this->pDataName);


}

#include <Windows.h>
void CVarSystem::LoadCfg(const char* nameFile)
{

    std::string filename; // Путь к файлу

    if (IsDebuggerPresent())
        filename = "../x64/Debug/app.cfg";
    else
        filename = "app.cfg";

    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        // Файл успешно открыт
        std::cout << "File opened successfully." << std::endl;
    }
    else {
        std::cout << "Error opening file is : App.cfg\n";
    }

    std::string line;
    std::regex keyValuePattern("([a-zA-Z0-9]+)\\s*=\\s*\"([a-zA-Z0-9\\s]+)\"");

    while (std::getline(inputFile, line)) {
        size_t separatorPos = line.find('=');
        if (separatorPos != std::string::npos) {
            std::string key = line.substr(0, separatorPos);
            std::string value = line.substr(separatorPos + 1);
            // Удаление начальных и конечных пробелов из ключа и значения
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            key.erase(std::remove(key.begin(), key.end(), '\"'), key.end());
            value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
            this->ListCfg->insert({ key, value });
        }
    }

    inputFile.close();
}

std::map<std::string, std::string>* CVarSystem::getMapList()
{
    return this->ListCfg;
}

std::string CVarSystem::getValue(std::string key)
{
    std::string result = ListCfg->at(key);
    return result.c_str();
}
