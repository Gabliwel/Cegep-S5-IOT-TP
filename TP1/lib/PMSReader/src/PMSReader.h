#pragma once
#include "PMS.h"

class PMSReader
{
public:
    PMSReader(PMS &pms1, PMS &pms2);
    int * getPMSValues();
private:
    PMS * PMS1;
    PMS * PMS2;
    PMS::DATA pmsData1; 
    PMS::DATA pmsData2; 
    int values[6]; 
};