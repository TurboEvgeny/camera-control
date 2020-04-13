#include "TcpClient.h"
#include <iostream>
TcpClient::TcpClient(std::string ip, std::string port):
  io_context(),
  s(io_context),
  resolver(io_context)
{
    // соединяемся - о результатах сообщаем
    boost::system::error_code error;
    boost::asio::connect(s, resolver.resolve(ip, port), error);
    if (!error)
    {
        this->connected = true;
        // выводим приветствие
        std::cout << "Enter command or type 'exit'" << std::endl;
    }
    // не смогли соединиться, выставляем флаг и пишем сообщение об ошибке
    else
    {
        this->connected = false;
        std::cout << "FAILED" << std::endl;
        std::cout << "server unreachable" << std::endl;
        std::cout << "transmission closed" << std::endl;
    }
}

TcpClient::~TcpClient()
{
}

void TcpClient::transmission()
{
    while(this->connected)
    {
        // просим ввести сообщение для сервера 
        std::cout << "Enter message: ";
        char request[MAX_BUFFER_LENGTH];
        std::cin.getline(request, MAX_BUFFER_LENGTH);
        size_t request_length = std::strlen(request);
        // инициализруем объект обработки ошибок записи
        boost::system::error_code error_write;
        // высылываем его
        boost::asio::write(
                           s,
                           boost::asio::buffer(request, request_length),
                           error_write);
        if (error_write)
        {
            std::cout << "FAILED" << std::endl;
            std::cout << "check server - out message fail " << std::endl;
            std::cout << "transmission closed" << std::endl;
            break;
        }
        // создаем буфер для ответа
        char reply[MAX_BUFFER_LENGTH];
        // инициалируем буфер нулями
        memset(reply, 0, sizeof(reply));
        // объект обработки ошибок чтения
        boost::system::error_code error_read;
        // делаем блокирующее считывание данных
        s.read_some(boost::asio::buffer(reply), error_read);
        // если ошибка - выводим сообщение об ошибке
        if (!error_read)
        {
            std::cout << "Reply is: " << reply << std::endl;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
            std::cout << "input message failure" << std::endl;
            std::cout << "transmission closed" << std::endl;
            // выходим из цикла - прием сообщения поломался
            break;
        }
    }
    // вышли из цикла -соединение завершилось
    this->connected = false;
}
