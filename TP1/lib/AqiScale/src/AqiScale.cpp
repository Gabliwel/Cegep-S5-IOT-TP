#include "AqiScale.h"

AqiScale::AqiScale()
{
    
}

char* AqiScale::getAQI(int pm25)
{
  int iqaValue = pm25/meanIQA*50;
  
  if(iqaValue < goodpm25Limit){
    return iqa1;
  }
  if(iqaValue < okpm25Limit){
    return iqa2;
  }
  return iqa3;
}