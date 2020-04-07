#include "Data.h"
// палитра цветов диода
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
    DiodColor(DiodPalette initColor);
    ~DiodColor();
    void setValue(const std::string& value) override;
    std::string getValueString() override;
private:
    // текущий цвет диода
    DiodPalette color;
};
