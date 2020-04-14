#pragma once
#include <boost/asio.hpp>
#define MAX_BUFFER_LENGTH 1024
using boost::asio::ip::tcp;

// forward declaration of server class
class Server;
// класс tcp-обмена во время сессии
class Session
  : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, Server* pServ);
    // запуск сессии
    void start();

private:
    // логика прослушивания входящих данных
    void do_read();
    // логика записи данных
    void do_write(std::size_t length);
    // бустовый tcp-сокет
    tcp::socket socket_;
    // данные для обмена (входящие и исходящие)
    char data_[MAX_BUFFER_LENGTH];
    // указатель на экземпляр сервера-обработчика команд
    Server* pServer;
};
// класс асинхронного tcp-сервера
class AsyncServer
{
public:
  AsyncServer(
              boost::asio::io_context& io_context,
              short port,
              Server* pServ);

private:
    // логика прослушивания подключений
    void do_accept();
    // boost-овый tcp-просулшиватель
    tcp::acceptor acceptor_;
    // указатель на экземпляр сервера-обработчика команд
    Server* pServer;
};
