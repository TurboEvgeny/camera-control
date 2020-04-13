#include <boost/asio.hpp>
#include <string>
#define BUFFER_LENGTH 1024
using boost::asio::ip::tcp;
// класс клиент с логикой
class TcpClient
{
 public:
  TcpClient(std::string ip, std::string port);
  ~TcpClient();
  void transmission();
 private:
    boost::asio::io_context io_context;
    tcp::socket s;
    tcp::resolver resolver;
};
