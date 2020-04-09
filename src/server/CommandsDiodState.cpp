#include "CommandsDiodState.h"
#include "DiodState.h"
// класс команды включения-выключения диода
SetDiodStateCommand::SetDiodStateCommand(DiodState& diodState):
  ICommand(),
  state(diodState)
{
}

SetDiodStateCommand::~SetDiodStateCommand()
{
}

std::string SetDiodStateCommand::getName()
{
    return "set-led-state";
}

std::string SetDiodStateCommand::execute(const std::string& arg)
{
    if (arg.compare("on") == 0)
    {
        state.setValue(true);
        return "OK";
    }
    else if (arg.compare("off") == 0)
    {
        state.setValue(false);
        return "OK";
    }
    else
    {
        return "FAILED";
    }
}

// класс команды включения-выключения диода
GetDiodStateCommand::GetDiodStateCommand(const DiodState& diodState):
  ICommand(),
  state(diodState)
{
}

GetDiodStateCommand::~GetDiodStateCommand()
{
}

std::string GetDiodStateCommand::getName()
{
    return "get-led-state";
}

std::string GetDiodStateCommand::execute(const std::string& arg)
{
    return ("OK" + this->state.getValueString());
}
