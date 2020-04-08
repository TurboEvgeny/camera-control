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

void DiodColor::setValue(DiodPalette val)
{
    this->color = val;
}

std::string DiodColor::getValueString() const
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
