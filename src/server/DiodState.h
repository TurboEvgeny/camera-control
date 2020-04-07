#include "Data.h"

// состояние диода
class DiodState : public IData
{
public:
    DiodState();
    DiodState(bool initVal);
    ~DiodState();
    void setValue(std::string valString);
    std::string getValueString();
private:
    // состояние диода: true - включен
    bool turnOn;
};

enum class DiodPalette
{
    RED,
    GREEN,
    BLUE
};
// Цвет диода
class DiodColor : public IData
{
public:
    DiodColor();
    DiodColor(DiodPalette init);
    ~DiodColor();
    void setValue(std::string value);
    std::string getValueString();
private:
    // текущий цвет диода
    DiodPalette color;
};
// частота диода
class DiodFrequency : public IData
{
public:
    DiodFrequency();
    // initVal - начальное значение, Гц
    // min - минимальное ограничение, Гц
    // max - максимальное ограничение, Гц
    DiodFrequency(double initVal, double min, double max);
    ~DiodFrequency();
    void setValue(std::string value);
    std::string getStringValue();
private:
    // частота в Гц
    double value;
    // минимально допустимая частота, Гц
    double minValue;
    // максимально допустимая частота, Гц
    double maxValue;
};
