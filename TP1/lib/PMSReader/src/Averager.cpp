#include "Averager.h"

Averager::Averager()
{
  resetValues();
}

float Averager::getAverage(int nbLoop)
{
  float average = 0;
  if(entries != 0){
    average = sum/entries; 
  }
  resetValues();
  return average;
}

void Averager::resetValues()
{
  sum = 0;
  entries = 0;
}

void Averager::addValue(int value)
{
  if(value >= 0){
    sum += value;
    entries++;
  }
}
