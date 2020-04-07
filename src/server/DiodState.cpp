#include "DiodState.h"

DiodState::DiodState() : turnOn(false)
{
}

DiodState::DiodState(bool initVal) :
  turnOn(initVal)
{
}

DiodState::~DiodState()
{
}

void DiodState::setValue(std::string valString)
{
}

std::string DiodState::getValueString()
{
    if (this->turnOn)
    {
        return "on";
    }
    else
    {
        return "off";
    }
}
