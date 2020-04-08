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

void DiodState::setValue(bool val)
{
    this->turnOn = val;
}

std::string DiodState::getValueString() const
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
