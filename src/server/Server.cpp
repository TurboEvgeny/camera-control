#include "Server.h"
#include "ICommand.h"
#include "Camera.h"  // CameraDiod
#include "CommandsDiodState.h" // SetDiodStateCommand, GetDiodStateCommand
#include "CommandsDiodColor.h" // SetDiodColorCommand, GetDiodColorCommand
#include "CommandsDiodFreq.h" // SetDiodFreqCommand, GetDiodFreqCommand
#include "AsyncTcpServer.h"
#include <vector>
#include <regex>
#include <iostream>
Server::Server()
{
    pDiod = new CameraDiod();
    // активация команд
    activateCommand(new SetDiodStateCommand(pDiod->state));
    activateCommand(new GetDiodStateCommand(pDiod->state));
    activateCommand(new SetDiodColorCommand(pDiod->color));
    activateCommand(new GetDiodColorCommand(pDiod->color));
    activateCommand(new SetDiodFreqCommand(pDiod->frequency));
    activateCommand(new GetDiodFreqCommand(pDiod->frequency));
}
Server::~Server()
{
    // удаляем всю динамическую память
    delete(pDiod);
    // не забывая про сохраненную память в контейнере команд
    for (auto item : commands)
    {
        delete(item.second);
    }
}
// логика активации команды
void Server::activateCommand(ICommand* command)
{
    commands.emplace(command->getName(), command);
}
// выполнение полученной строки 
void Server::execInputString(const std::string& input, std::string& result)
{
    // логика обработки команда простая - ожидается 2 слова,
    // разделенные пробелом, команда + аргумент
    std::regex regex(R"([\s])"); // split on space and comma
    std::sregex_token_iterator it(input.begin(), input.end(), regex, -1);
    std::vector<std::string> words(it, {});
    if (words.size() > 1)
    {
        result = exec(words[0], words[1]);
    }
    else
    {
        result = exec(words[0], "");
    }
    std::cout << "result=" << result << std::endl;
}
// выполнение команды (возвращает строку)
std::string Server::exec(const std::string& cmd, const std::string& arg)
{
    // ищем контейнере команд введенную
    auto iter = this->commands.find(cmd);
    // что-то нашли - испольняем и возвращаем результат
    if (iter != this->commands.end())
    {
        return iter->second->execute(arg);
    }
    else
    {
        return "FAILED";
    }
}

// логика сервера
void Server::networkLogic()
{
    boost::asio::io_context io_context;
    AsyncServer s(io_context, 11111, this);
    io_context.run();
}
