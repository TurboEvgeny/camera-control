#include "CommandsDiodFreq.h"
#include "DiodFrequency.h"

SetDiodFreqCommand::SetDiodFreqCommand(DiodFrequency& freqRef):
  freq(freqRef)
{
}
SetDiodFreqCommand::~SetDiodFreqCommand()
{
}
// назваие команды
std::string SetDiodFreqCommand::getName()
{
    return "set-led-rate";
}

// логика выполнения команды задачи частоты
std::string SetDiodFreqCommand::execute(const std::string& arg)
{
    // проводим преобразование строки в число с плавающей точкой
    // пользуясь функцией stod и at у std::string,
    // выбрасывающими исключения при некорректных аргументах
    try
    {
        // номер последнего символа, которые является частью числа в строке
        // если строка полноценное число - мы получим длину строки
        std::size_t lastNumberSymbolOffset = 0;
        double freqValue = std::stod(arg, &lastNumberSymbolOffset);
        // пользуемся свойством оператора [] у const std::string
        // если аргумент равен длине строки - возвращает символ '\0'
        if (arg[lastNumberSymbolOffset] == '\0')
        {
            // узнаем - установилась ли введенная частота
            bool result = freq.setValue(freqValue);
            if (result)
            {
                return "OK";
            }
          else
            {
                return "FAILED";
            }
        }
        // аргумент - не число, отчитываемся
        else
        {
            return "FAILED";
        }
    }
    // выбросилось исключение - отчитываемся об отказе
    catch (const std::exception& ex)
    {
        return "FAILED";
    }
}

GetDiodFreqCommand::GetDiodFreqCommand(const DiodFrequency& freqRef):
  ICommand(),
  freq(freqRef)
{
}

GetDiodFreqCommand::~GetDiodFreqCommand()
{
}

std::string GetDiodFreqCommand::getName()
{
    return "get-led-rate";
}

std::string GetDiodFreqCommand::execute(const std::string& arg)
{
    return ("OK" + freq.getValueString());
}
