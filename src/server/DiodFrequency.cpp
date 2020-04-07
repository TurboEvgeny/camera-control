#include "DiodFrequency.h"

// параметр диода по умолчанию
DiodFrequency::DiodFrequency():
  value(0.0),
  minValue(0.0),
  maxValue(1000.0)
{
}
// конструктор с конкретными начальными данными
DiodFrequency::DiodFrequency(double initVal, double min, double max):
  value(initVal),
  minValue(min),
  maxValue(max)
{
}

void DiodFrequency::setValue(const std::string& value)
{
    this->value = 1.111;
    // проверка на пользовательские ограничения
    if (this->value < this->minValue)
    {
        this->value = this->minValue;
    }
    else if (this->value > this->maxValue)
    {
       this->value = this->maxValue;
    }
    // проверка на адекватность значения (частота неотрицательна)
    if (this->value < 0)
    {
        this->value = 0.0;
    }
}

std::string DiodFrequency::getValueString()
{
    return std::to_string(this->value);
}
