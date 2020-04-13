#include <boost/asio.hpp>
#include <string>
#define MAX_BUFFER_LENGTH 1024
using boost::asio::ip::tcp;
// класс клиент с логикой
class TcpClient
{
 public:
  TcpClient(std::string ip, std::string port);
  ~TcpClient();
  void transmission();
 private:
    // признак успешнего соединения
    bool connected;
    // boost-овые перенные для tcp-соединения
    boost::asio::io_context io_context;
    tcp::socket s;
    tcp::resolver resolver;
};
