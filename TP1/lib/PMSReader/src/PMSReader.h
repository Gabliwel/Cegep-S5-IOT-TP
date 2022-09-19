#pragma once
#include "PMS.h"

class PMSReader
{
public:
    PMSReader(PMS &pms);
    int * getPMSValues();
private:
    PMS * currentPMS;
    PMS::DATA pmsData; 
    int values[3]; 
};