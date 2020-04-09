#include "ICommand.h"
// forward declaration DiodState
class DiodState;
// класс команды включения-выключения диода
class SetDiodStateCommand : public ICommand
{
public:
    SetDiodStateCommand(DiodState& diodState);
    ~SetDiodStateCommand();
    // имя команды
    std::string getName() override;
    // выполнить команду с аргументами
    std::string execute(const std::string& arg) override;
private:
    // ссылка на данные о состоянии диода
    DiodState& state;
};
// класс команды получения состояния диода
class GetDiodStateCommand : public ICommand
{
 public:
    GetDiodStateCommand(const DiodState& state);
    ~GetDiodStateCommand();
    // имя команды
    std::string getName() override;
    // выполнить команду с аргументами
    std::string execute(const std::string& arg) override;
 private:
    // ссылка на данные о состоянии диода
    const DiodState& state;
};
