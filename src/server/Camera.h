#pragma once
#include "DiodState.h"
#include "DiodColor.h"
#include "DiodFrequency.h"

struct CameraDiod
{
    // инициализация параметров диода камеры
    CameraDiod()
    {
        // начальные данные о состоянии вкл-выкл
        const bool initTurnOn = false;
        state = DiodState(initTurnOn);
        // начальный цвет
        const DiodPalette initColor = DiodPalette::RED;
        color = DiodColor(initColor);
        // начальные параметры частоты
        const double initFreq = 0.0;
        const double minFreq = 0.0;
        const double maxFreq = 5.0;
        frequency = DiodFrequency(initFreq, minFreq, maxFreq);
    }
    // состояние диода, включен-выключен
    DiodState state;
    // цвет диода
    DiodColor color;
    // частота мигания диода
    DiodFrequency frequency;
};
