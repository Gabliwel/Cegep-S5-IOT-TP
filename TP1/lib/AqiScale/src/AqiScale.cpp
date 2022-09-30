#include "AqiScale.h"

AqiScale::AqiScale()
{

}

char* AqiScale::getPollutionLvl(int pm25)
{
  // https://revolvair.org/indice-de-qualite-de-lair-iqa/
  // Échelle pour les données brutes PM 2.5 en microgrammes par mètre cube (μg/m3)
  if(pm25 == -1)
    return nd;
  if(pm25 < goodpm25Limit){
    return lvl1;
  }
  if(pm25 < okpm25Limit){
    return lvl2;
  }
  if(pm25 < badpm25Limit){
    return lvl3;
  }
  return lvl4;
}

float AqiScale::getAQI(int pm25)
{
  return (pm25 * AQI_NORM) / 50;
}