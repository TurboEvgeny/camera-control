#include "AsyncTcpServer.h"
#include "Server.h"
#include <iostream>

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket, Server* pServ) :
  socket_(std::move(socket)),
  pServer(pServ)
{
  
}
// при старте сессии начинаем прослушивать - нет ли входящих пакетов
void Session::start()
{
    do_read();
}
// логика прослушивания входящих данных
void Session::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, MAX_BUFFER_LENGTH),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                // получив запрос, формируем строчку-ответ
                std::string answer;
                pServer->execInputString(std::string(data_), answer);
                // вычищаем маccив для обмена
                memset(data_, 0, sizeof(data_));
                // копируем данные, которые необходимо отправить
                strncpy(data_, answer.c_str(), MAX_BUFFER_LENGTH-1);
                // считаем количество байт, которое необходимо отправить
                size_t sendBytes = strlen(data_) * sizeof(data_[0]);
                // выводим лог
                std::cout << "sending... " << data_ << std::endl;
                std::cout << "bytes=" << sendBytes << std::endl;
                do_write(sendBytes);
            }
        });
}

// логика записи данных
void Session::do_write(std::size_t length)
{
    auto self(shared_from_this());
    // отправляем данные
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            // после отправки при отсутствии ошибок начинаем
            // снова слушать входящие пакеты
            if (!ec)
            {
                do_read();
            }
        });
}
// асинхронный сервер инициализуются с данными про порт 
//  + указатель на серверный обработчик данных
AsyncServer::AsyncServer(
     boost::asio::io_context& io_context,
     short port,
     Server* pServ) :
       acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
       pServer(pServ)
{
    do_accept();
}
// запускаем прослушивание подключений клиентов
void AsyncServer::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          // клиент подключился - стартуем сессию
          if (!ec)
          {
            std::make_shared<Session>(
                std::move(socket), pServer)->start();
          }
          // продолжаем слушать соединения
          do_accept();
        });
}
