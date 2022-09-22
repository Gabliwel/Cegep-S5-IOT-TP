#include "TempReader.h"

TempReader::TempReader(DHT &dht)
{
  this->currentDHT = &dht;
}

void TempReader::init()
{
  this->currentDHT->begin();
}

float TempReader::getHumidityValue()
{
  float humidity = this->currentDHT->readHumidity();
  delay(300);
  return humidity;
}

float TempReader::getTemperatureValue()
{
  float temp = this->currentDHT->readTemperature();
  delay(300);
  return temp;
}