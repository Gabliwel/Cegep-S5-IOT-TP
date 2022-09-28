#include "PMSReader.h"

PMSReader::PMSReader(PMS &pms1, PMS &pms2)
{
    this->PMS1 = &pms1;
    this->PMS2 = &pms2;
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
  }
  if (this->PMS2->read(pmsData2))
  {
    this->values[3] = pmsData2.PM_AE_UG_1_0;
    this->values[4] = pmsData2.PM_AE_UG_2_5;
    this->values[5] = pmsData2.PM_AE_UG_10_0;
  }


  return this->values;

}