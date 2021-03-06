#pragma once
#include <string>
#include <unordered_map>
#include <memory>
// forward declaration
struct CameraDiod;
class ICommand;
// класс отвечающий за работу сервера
class Server
{
public:
    Server(std::string port, bool log = false);
    ~Server();
    // логика сервера
    void networkLogic();
    // выполнение полученной строки 
    void execInputString(const std::string& input, std::string& result);
private:
    // активация команды
    void activateCommand(std::unique_ptr<ICommand>&& command);
    // выполнение команды (возвращает строку)
    std::string exec(const std::string& cmd, const std::string& arg);
    // данные о диоде
    //(храним не в стеке, чтобы не было зависимостей от заголовков)
    CameraDiod* pDiod;
    // хранилище активных команд
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands;
    // порт для tcp подключения
    int listenPort;
    // флаг вывода команда
    bool logging;
};
