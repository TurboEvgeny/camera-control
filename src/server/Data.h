#pragma once
#include <string>
// интерфейсный класс для работы с данными камеры
class IData
{
public:
    virtual void setValue(std::string valString) = 0;
    virtual std::string getValueString() = 0;
};
