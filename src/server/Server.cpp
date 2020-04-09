#include "Server.h"
#include "ICommand.h"
#include "Camera.h"
Server::Server()
{
    pDiod = new CameraDiod();
    // активация команд
    //xactivateCommand();
}
Server::~Server()
{
    delete(pDiod);
}
// логика активации команды
void Server::activateCommand(std::unique_ptr<ICommand>& command)
{
    commands.emplace(command->getName(), command);
}
