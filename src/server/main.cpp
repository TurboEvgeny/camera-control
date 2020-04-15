#include <iostream>
#include <boost/asio.hpp> // tcp connectuib
#include <boost/property_tree/ptree.hpp>       // parse ini file
#include <boost/property_tree/ini_parser.hpp>
#include "Server.h"
int main()
{
    // считываем из ini-файла порт для прослушивания
    std::string portStr;
    try
    {
        boost::property_tree::ptree tree;
        boost::property_tree::ini_parser::read_ini("server.ini", tree);
        portStr = tree.get<std::string>("network.port");
    }
    // при ошибке выводим описание проблемы
    catch(std::exception& e)
    {
      std::cout << e.what() << std::endl;
      return 1;
    }
    Server server(portStr);
    server.networkLogic();
    return 0;
}
