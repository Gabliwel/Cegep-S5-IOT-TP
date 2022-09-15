#include "PMSReader.h"

PMS currentPMS;
PMS::DATA pmsData;

PMSReader::PMSReader(PMS *pms)
{
    currentPMS = *pms;
}

int * PMSReader::getPMSValues()
{
  static int  values[3];

  if (currentPMS.read(pmsData))
  {
    values[0] = pmsData.PM_AE_UG_1_0;
    values[1] = pmsData.PM_AE_UG_2_5;
    values[2] = pmsData.PM_AE_UG_10_0;
  }

  return values;

}