#include "TcpClient.h"

int main()
{
    // создаем экземпляр сетевого клиента
    TcpClient client("127.0.0.1", "11111");
    // и запускаем логику сетего взаимодействия
    client.transmission();
    return 0;
}
