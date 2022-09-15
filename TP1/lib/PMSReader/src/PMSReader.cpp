#include "PMSReader.h"

PMSReader::PMSReader(PMS &pms)
{
    this->currentPMS = &pms;
}

int * PMSReader::getPMSValues()
{
  static int  values[3];

  if (this->currentPMS->read(pmsData))
  {
    values[0] = pmsData.PM_AE_UG_1_0;
    values[1] = pmsData.PM_AE_UG_2_5;
    values[2] = pmsData.PM_AE_UG_10_0;
  }
  else{
    values[0] = 1000000;
    values[1] = 1000000;
    values[2] = 1000000;
  }

  return values;

}