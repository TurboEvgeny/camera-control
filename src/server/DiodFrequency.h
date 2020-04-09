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
    // задача необходимой частоты, возвращает true если прошло успешно
    bool setValue(double freq);
    std::string getValueString() const override;
private:
    // частота в Гц
    double value;
    // минимально допустимая частота, Гц
    double minValue;
    // максимально допустимая частота, Гц
    double maxValue;
};
