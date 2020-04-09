#include "ICommand.h"
// forward declaration of references
class DiodColor;
// класс команды смены цвета диода
class SetDiodColorCommand : public ICommand
{
public:
    SetDiodColorCommand(DiodColor& colorRef);
    ~SetDiodColorCommand();
    // имя команды
    std::string getName() override;
    // выполнить команду с аргументами
    std::string execute(const std::string& arg) override;
private:
    // ссылка на данные о цвете диода
    DiodColor& color;
};
// класс команды получения текущего цвета диода
class GetDiodColorCommand : public ICommand
{
 public:
    GetDiodColorCommand(const DiodColor& colorRef);
    ~GetDiodColorCommand();
    // имя команды
    std::string getName() override;
    // выполнить команду с аргументами
    std::string execute(const std::string& arg) override;
 private:
    // ссылка на данные о состоянии диода
    const DiodColor& color;
};
