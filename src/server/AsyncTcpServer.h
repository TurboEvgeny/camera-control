#pragma once
#include <iostream>
#include "Server.h"
#include <boost/asio.hpp>
#define BUFFER_LENGTH 1024
using boost::asio::ip::tcp;

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket, Server* pServ)
    : socket_(std::move(socket)),
      pServer(pServ)
  {
  }

  void start()
  {
    do_read();
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, BUFFER_LENGTH),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            std::string answer;
            pServer->execInputString(std::string(data_), answer);
            // копируем данные, которые необходимо отправить
            strncpy(data_, answer.c_str(), BUFFER_LENGTH-1);
            // считаем количество байт, которое необходимо отправить
            size_t sendBytes = strlen(data_) * sizeof(data_[0]);
            // выводим лог
            std::cout << "sending... " << data_ << std::endl;
            std::cout << "bytes=" << sendBytes << std::endl;
            do_write(sendBytes);
          }
        });
  }

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
  }

  tcp::socket socket_;
  char data_[BUFFER_LENGTH];
  // указатель на экземпляр сервера-обработчика команд
  Server* pServer;
};

class AsyncServer
{
public:
  AsyncServer(
              boost::asio::io_context& io_context,
              short port,
              Server* pServ)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
      pServer(pServ)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket), pServer)->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  // указатель на экземпляр сервера-обработчика команд
  Server* pServer;
};
