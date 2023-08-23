#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>


class MessageManager {
public:
    // Функция для обработки строки и получения всех пар ключ-значение
    static std::map<std::string, std::string> parseKeyValueString(const std::string& input) {
        std::map<std::string, std::string> keyValueMap;

        std::istringstream iss(input);
        std::string segment;

        while (std::getline(iss, segment, ';')) {
            size_t equalsPos = segment.find('=');
            if (equalsPos != std::string::npos) {
                std::string key = segment.substr(0, equalsPos);
                std::string value = segment.substr(equalsPos + 1);
                keyValueMap[key] = value;  // Сохраняем значение
            }
        }

        return keyValueMap;
    }
};
