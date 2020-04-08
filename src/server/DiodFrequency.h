#include "Data.h"

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
    void setValue(double freq);
    std::string getValueString() const override;
private:
    // частота в Гц
    double value;
    // минимально допустимая частота, Гц
    const double minValue;
    // максимально допустимая частота, Гц
    const double maxValue;
};
