#include "TcpClient.h"
#include <iostream>
TcpClient::TcpClient(std::string ip, std::string port):
  io_context(),
  s(io_context),
  resolver(io_context)
{
  boost::asio::connect(s, resolver.resolve(ip, port));
}

TcpClient::~TcpClient()
{
}

void TcpClient::transmission()
{
    while(true)
    {
        std::cout << "Enter message: ";
        char request[BUFFER_LENGTH];
        std::cin.getline(request, BUFFER_LENGTH);
        size_t request_length = std::strlen(request);
        boost::asio::write(
                           s,
                           boost::asio::buffer(request, request_length));
        char reply[BUFFER_LENGTH];
        boost::system::error_code error;
        memset(reply, 0, sizeof(reply));
        // делаем блокирующее считывание данных
        s.read_some(boost::asio::buffer(reply), error);
        if (error)
        {
            std::cout << "error!";
        }
        else
        {
            std::cout << "Reply is: " << reply << std::endl;
        }
    }
}
