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
#include <boost/property_tree/ptree.hpp>       // ini parse
#include <boost/property_tree/ini_parser.hpp>  // ini parse
Server::Server(std::string port, bool log):
  listenPort(std::stoi(port)),
  logging(log)
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
    // по стандарту должно быть всего 2 слова, иначе аргумент некорректен
    if (words.size() == 2)
    {
        result = exec(words[0], words[1]);
    }
    else
    {
        result = exec(words[0], "");
    }
    // выводим строку результата (в случае флага логирования)
    if (this->logging)
    {
        std::cout << "result=" << result << std::endl;
    }
}
// выполнение команды (возвращает строку)
std::string Server::exec(const std::string& cmd, const std::string& arg)
{
    // ищем контейнере команд введенную
    auto iter = this->commands.find(cmd);
    // что-то нашли - испольняем и возвращаем результат
    if (iter != this->commands.end())
    {
        if (this->logging)
        {
            std::cout << "command=" << cmd << std::endl;
            std::cout << "arg=" << arg << std::endl;
        }
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
     if ((0 < listenPort) &&
         (listenPort < std::numeric_limits<short>::max()))
    {
        std::cout << "opening port " << listenPort;
        std::cout << " for connections" << std::endl;
        boost::asio::io_context io_context;
        AsyncServer s(io_context, listenPort, this);
        io_context.run();
    }
    else
    {
      std::cout << "port number " << listenPort << " is incorrect";
      std::cout << "check 0-65535 range" << std::endl;
    }
}
