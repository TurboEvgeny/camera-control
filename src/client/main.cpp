#include <iostream>
#include <boost/asio.hpp>
#define BUFFER_LENGTH 1024
using boost::asio::ip::tcp;

int main()
{
    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(s, resolver.resolve("127.0.0.1", "11111"));
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
        memset(reply, 0, sizeof(reply));
        size_t reply_length =
          boost::asio::read(s, boost::asio::buffer(reply, s.available()));
        std::cout << "Reply is: " << reply << std::endl;
    }
    return 0;
}
