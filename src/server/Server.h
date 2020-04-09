#include <string>
#include <unordered_map>
#include <memory>
// forward declaration
struct CameraDiod;
class ICommand;
// класс отвечающий за работу сервера
class Server
{
public:
    Server();
    ~Server();
private:
    // данные о диоде
    //(храним не в стеке, чтобы не было зависимостей от заголовков)
    CameraDiod* pDiod;
    // активация команды
    void activateCommand(std::unique_ptr<ICommand>& command);
    // хранилище активных команд
    std::unordered_map<std::string, std::unique_ptr<ICommand>&> commands;
};
