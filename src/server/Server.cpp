#include "Server.h"
#include "ICommand.h"
#include "Camera.h"  // CameraDiod
#include "CommandsDiodState.h" // SetDiodStateCommand, GetDiodStateCommand
#include "CommandsDiodColor.h" // SetDiodColorCommand, GetDiodColorCommand
#include "CommandsDiodFreq.h" // SetDiodFreqCommand, GetDiodFreqCommand
#include <vector>
Server::Server()
{
    pDiod = new CameraDiod();
    // активация команд
    activateCommand(new SetDiodStateCommand(pDiod->state));
    activateCommand(new GetDiodStateCommand(pDiod->state));
    activateCommand(new SetDiodColorCommand(pDiod->color));
    activateCommand(new GetDiodColorCommand(pDiod->color));
    activateCommand(new SetDiodFreqCommand(pDiod->frequency));
    activateCommand(new GetDiodFreqCommand(pDiod->frequency));

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
