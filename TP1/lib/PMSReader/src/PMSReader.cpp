#include "PMSReader.h"

PMSReader::PMSReader(PMS &pms)
{
    this->currentPMS = &pms;
    this->values[0] = 0;
    this->values[1] = 0;
    this->values[2] = 0;
}

int * PMSReader::getPMSValues()
{

  if (this->currentPMS->read(pmsData))
  {
    this->values[0] = pmsData.PM_AE_UG_1_0;
    this->values[1] = pmsData.PM_AE_UG_2_5;
    this->values[2] = pmsData.PM_AE_UG_10_0;
  }


  return this->values;

}