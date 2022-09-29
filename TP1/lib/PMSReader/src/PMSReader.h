#pragma once
#include "PMS.h"
#include "Averager.h"

class PMSReader
{
public:
    PMSReader(PMS &pms1, PMS &pms2, Averager &averager1, Averager &averager2, Averager &averager3);
    int * getPMSValues();
private:
    PMS * PMS1;
    PMS * PMS2;
    PMS::DATA pmsData1; 
    PMS::DATA pmsData2; 
    int values[6]; 
    //PMS 1
    Averager * averager1;
    //PMS 2.5
    Averager * averager2;
    //PMS 10
    Averager * averager3;
};