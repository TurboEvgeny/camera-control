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
    activateCommand(std::make_unique<SetDiodStateCommand>(pDiod->state));
    activateCommand(std::make_unique<GetDiodStateCommand>(pDiod->state));
    activateCommand(std::make_unique<SetDiodColorCommand>(pDiod->color));
    activateCommand(std::make_unique<GetDiodColorCommand>(pDiod->color));
    activateCommand(std::make_unique<SetDiodFreqCommand>(pDiod->frequency));
    activateCommand(std::make_unique<GetDiodFreqCommand>(pDiod->frequency));
}
Server::~Server()
{
    // удаляем всю динамическую память
    delete(pDiod);
}
// логика активации команды
void Server::activateCommand(std::unique_ptr<ICommand>&& command)
{
    commands.emplace(command->getName(), std::move(command));
}
// выполнение полученной строки 
void Server::execInputString(const std::string& input, std::string& result)
{
    // логика обработки команда простая - ожидается 2 слова,
    // разделенные пробелом: команда + аргумент
  
    // запускам регулярное выражение, которое создаст список слов,
    // разделенных пробелами
    std::regex regex(R"([\s])");
    std::sregex_token_iterator it(input.begin(), input.end(), regex, -1);
    std::vector<std::string> words(it, {});
    // если в векторе 2 слова - значит у нас есть и команда и аргумент
    // (считаем, что в аргументе пробелов нет!)
    if (words.size() == 2)
    {
        result = exec(words[0], words[1]);
    }
    // в любом другом случае выполняем команду без аргументов
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
