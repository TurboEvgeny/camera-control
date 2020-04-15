#include "TcpClient.h"
#include <boost/property_tree/ptree.hpp>       // parse ini file
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>
int main()
{
    // считываем из ini-файла настройки сервера (ip сервера и порт)
    std::string ipStr, portStr;
    try
    {
        boost::property_tree::ptree tree;
        boost::property_tree::ini_parser::read_ini("client.ini", tree);
        ipStr = tree.get<std::string>("network.ip");
        portStr = tree.get<std::string>("network.port");
    }
    // при ошибке выводим описание проблемы
    catch(std::exception& e)
    {
      std::cout << e.what() << std::endl;
      return 1;
    }
    // создаем экземпляр сетевого клиента
    TcpClient client(ipStr, portStr);
    // и запускаем логику сетего взаимодействия
    client.transmission();
    return 0;
}
