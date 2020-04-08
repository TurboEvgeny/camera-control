#include "Data.h"

// состояние диода
class DiodState : public IData
{
public:
    DiodState();
    DiodState(bool initVal);
    ~DiodState();
    void setValue(bool val);
    std::string getValueString() const override;
private:
    // состояние диода: true - включен
    bool turnOn;
};
