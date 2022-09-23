#include "RGBLedManager.h"

class AqiScale
{
public:
    AqiScale();
    char* getPollutionLvl(int pm25);
    float getAQI(int pm25);
private:
    RGBLedManager * ledmanager;
    char lvl1[4] = "Bon";
    char lvl2[11] = "Acceptable";
    char lvl3[8] = "Mauvais";
    char lvl4[14] = "Très Mauvais";
    const int goodpm25Limit = 12;
    const int okpm25Limit = 35;
    const int badpm25Limit = 55;
    const float AQI_NORM = 25;
};