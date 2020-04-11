#include "Server.h"
#include "ICommand.h"
#include "Camera.h"  // CameraDiod
#include "CommandsDiodState.h" // SetDiodStateCommand
#include <vector>
Server::Server()
{
    pDiod = new CameraDiod();
    // активация команд
    activateCommand(new SetDiodStateCommand(pDiod->state));
}
Server::~Server()
{
    // удаляем всю динамическую память
    delete(pDiod);
    // не забывая про сохраненную память в контейнере команд
    for (auto item : commands)
    {
        delete(item.second);
    }
}
// логика активации команды
void Server::activateCommand(ICommand* command)
{
    commands.emplace(command->getName(), command);
}
