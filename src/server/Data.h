#pragma once
#include <string>
// интерфейсный класс для работы с данными камеры
class IData
{
public:
    virtual std::string getValueString() const = 0;
};
