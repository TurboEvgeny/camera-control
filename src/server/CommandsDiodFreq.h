#include "ICommand.h"
// forward declaration of reference
class DiodFrequency;
// класс команды смены частоты мигания диода
class SetDiodFreqCommand : public ICommand
{
public:
    SetDiodFreqCommand(DiodFrequency& freqRef);
    ~SetDiodFreqCommand();
    // имя команды
    std::string getName() override;
    // выполнить команду с аргументами
    std::string execute(const std::string& arg) override;
private:
    // ссылка на данные о состоянии диода
    DiodFrequency& freq;
};
// класс команды получения частоты мигания диода
class GetDiodFreqCommand : public ICommand
{
 public:
    GetDiodFreqCommand(const DiodFrequency& freqRef);
    ~GetDiodFreqCommand();
    // имя команды
    std::string getName() override;
    // выполнить команду с аргументами
    std::string execute(const std::string& arg) override;
 private:
    // ссылка на данные о состоянии диода
    const DiodFrequency& freq;
};
