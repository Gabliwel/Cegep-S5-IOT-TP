#include "Averager.h"

Averager::Averager()
{
  resetValues();
}

float Averager::getAverage()
{
  int sum = 0;
  int entries = 0;
  for(int i = 0; i < 24; i++){
    if(values1[i] >= 0){
      sum+=values1[i];
      entries++;
    }
    if(values2[i] >= 0){
      sum+=values2[i];
      entries++;
    }
  }
  resetValues();
  float average = 0;
  if(entries != 0){
     average = sum/entries; 
  }
  return average;
}

void Averager::resetValues()
{
  for(int i = 0; i < 24; i++){
    values1[i] = -1;
    values2[i] = -1;  
  }
  this->currentPMS1ArrayValue = 0;
  this->currentPMS2ArrayValue = 0;
}

void Averager::setValue(int pmsNumber, int value)
{
  if(pmsNumber == 1){
    this->values1[currentPMS1ArrayValue] = value;
    currentPMS1ArrayValue++;
    if(currentPMS1ArrayValue == sizeof(values1)){
      currentPMS1ArrayValue = 0;
    }
  }
  else if(pmsNumber == 2){
    this->values2[currentPMS2ArrayValue] = value;
    currentPMS2ArrayValue++;
    if(currentPMS2ArrayValue == sizeof(values2)){
      currentPMS2ArrayValue = 0;
    }
  }
}
