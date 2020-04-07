#include "Data.h"

// состояние диода
class DiodState : public IData
{
public:
    DiodState();
    DiodState(bool initVal);
    ~DiodState();
    void setValue(const std::string& valString) override;
    std::string getValueString() override;
private:
    // состояние диода: true - включен
    bool turnOn;
};
