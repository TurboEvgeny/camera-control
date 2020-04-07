#include "DiodColor.h"

DiodColor::DiodColor() :
  IData(),
  color(DiodPalette::RED)
{
}

DiodColor::DiodColor(DiodPalette initColor):
  IData(),
  color(initColor)
{
}

DiodColor::~DiodColor()
{
}

void DiodColor::setValue(const std::string value)
{
    if (value.compare("red") == 0)
    {
        this->color = DiodPalette::RED;
    }
    else if (value.compare("green") == 0)
    {
        this->color = DiodPalette::GREEN;
    }
    else if (value.compare("blue") == 0)
    {
        this->color = DiodPalette::BLUE;
    }
}

std::string DiodColor::getValueString()
{
    switch(this->color)
    {
      case DiodPalette::RED:
          return "red";
      case DiodPalette::GREEN:
          return "green";
      case DiodPalette::BLUE:
          return "blue";
      default:
          return "";
    }
}
