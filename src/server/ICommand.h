#pragma once
#include <string>
// интерфейсный класс для описания команд
class ICommand
{
    // выдача имени команды
    virtual std::string getName() = 0;
    // логика команды -
    // возвращает строку - ответ для клиента о результате выполнения
    virtual std::string execute(std::string arg) = 0;
};
