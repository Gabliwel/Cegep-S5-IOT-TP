#include "AqiScale.h"

AqiScale::AqiScale(RGBLedManager &ledManager)
{
    this->ledmanager = &ledManager;
}

char* AqiScale::getAQI(int pm25)
{
  int iqaValue = pm25/meanIQA*50;
  
  if(iqaValue < goodpm25Limit){
    ledmanager->changeColor(red);
    return iqa1;
  }
  if(iqaValue < okpm25Limit){
    ledmanager->changeColor(yellow);
    return iqa2;
  }
  if(iqaValue < badpm25Limit){
    ledmanager->changeColor(orange);
    return iqa3;
  }
  ledmanager->changeColor(red);
  return iqa4;
}