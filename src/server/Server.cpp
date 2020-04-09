#include "Server.h"
#include "ICommand.h"
#include "Camera.h"  // CameraDiod
#include "CommandsDiodState.h" // SetDiodStateCommand
#include <vector>
Server::Server()
{
    pDiod = new CameraDiod();
    // активация команд
    std::unique_ptr<ICommand> command =
      std::make_unique<SetDiodStateCommand>(pDiod->state);
    activateCommand(command);
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
