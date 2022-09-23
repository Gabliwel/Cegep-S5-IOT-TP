#include "RGBLedManager.h"

class AqiScale
{
public:
    AqiScale(RGBLedManager &ledManager);
    char* getAQI(int pm25);
private:
    RGBLedManager * ledmanager;
    char iqa1[4] = "Bon";
    char iqa2[11] = "Acceptable";
    char iqa3[8] = "Mauvais";
    char iqa4[14] = "Très Mauvais";
    int meanIQA = 35;
    int goodpm25Limit = 12;
    int okpm25Limit = 35;
    int badpm25Limit = 55;
};