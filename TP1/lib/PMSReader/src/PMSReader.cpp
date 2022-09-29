#include "PMSReader.h"

PMSReader::PMSReader(PMS &pms1, PMS &pms2, Averager &averager1, Averager &averager2, Averager &averager3)
{
    this->PMS1 = &pms1;
    this->PMS2 = &pms2;
    this->averager1 = &averager1;
    this->averager2 = &averager2;
    this->averager3 = &averager3;
    this->values[0] = -1;
    this->values[1] = -1;
    this->values[2] = -1;
    this->values[3] = -1;
    this->values[4] = -1;
    this->values[5] = -1;
}

int * PMSReader::getPMSValues()
{

  if (this->PMS1->read(pmsData1))
  {
    this->values[0] = pmsData1.PM_AE_UG_1_0;
    this->values[1] = pmsData1.PM_AE_UG_2_5;
    this->values[2] = pmsData1.PM_AE_UG_10_0;
    this->averager1->addValue(values[0]);
    this->averager2->addValue(values[1]);
    this->averager3->addValue(values[2]);
    
  }
  if (this->PMS2->read(pmsData2))
  {
    this->values[3] = pmsData2.PM_AE_UG_1_0;
    this->values[4] = pmsData2.PM_AE_UG_2_5;
    this->values[5] = pmsData2.PM_AE_UG_10_0;
    this->averager1->addValue(values[3]);
    this->averager2->addValue(values[4]);
    this->averager3->addValue(values[5]);
  }


  return this->values;

}