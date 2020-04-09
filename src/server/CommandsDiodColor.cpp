#include "CommandsDiodColor.h"
#include "DiodColor.h"
// класс команды включения-выключения диода
SetDiodColorCommand::SetDiodColorCommand(DiodColor& colorRef):
  ICommand(),
  color(colorRef)
{
}

SetDiodColorCommand::~SetDiodColorCommand()
{
}

std::string SetDiodColorCommand::getName()
{
    return "set-led-color";
}

std::string SetDiodColorCommand::execute(const std::string& arg)
{
    if (arg.compare("red") == 0)
    {
        color.setValue(DiodPalette::RED);
        return "OK";
    }
    else if (arg.compare("green") == 0)
    {
        color.setValue(DiodPalette::GREEN);
        return "OK";
    }
    else if (arg.compare("blue") == 0)
    {
        color.setValue(DiodPalette::BLUE);
        return "OK";
    }
    else
    {
        return "FAILED";
    }
}

// класс команды включения-выключения диода
GetDiodColorCommand::GetDiodColorCommand(const DiodColor& colorRef):
  ICommand(),
  color(colorRef)
{
}

GetDiodColorCommand::~GetDiodColorCommand()
{
}

std::string GetDiodColorCommand::getName()
{
    return "get-led-color";
}

std::string GetDiodColorCommand::execute(const std::string& arg)
{
    return ("OK " + this->color.getValueString());
}
