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
    // проверяем что начальное значение входит диапазон
    if (this->value < this->minValue)
    {
        this->value = this->minValue;
    }
    else if (this->value > this->maxValue)
    {
        this->value = this->maxValue;
    }
}

DiodFrequency::~DiodFrequency()
{
}
// задача необходимой частоты, возвращает true если прошло успешно
bool DiodFrequency::setValue(double freq)
{
    if ((this->minValue <= freq) && (freq <= this->maxValue))
    {
        this->value = freq;
        return true;
    }
    else
    {
        return false;
    }
}

std::string DiodFrequency::getValueString() const
{
    return std::to_string(this->value);
}
