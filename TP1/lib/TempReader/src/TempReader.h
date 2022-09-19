#pragma once
#include "DHT.h"

class TempReader
{
public:
    TempReader(DHT &dht);
    void init();
    float getHumidityValue();
    float getTemperatureValue();
private:
    DHT * currentDHT;
};