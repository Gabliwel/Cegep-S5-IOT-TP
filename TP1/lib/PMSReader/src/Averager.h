#pragma once

class Averager
{
public:
    Averager();
    float getAverage();
    void setValue(int pmsNumber, int value);
    void resetValues();
private:
    int values1[24];
    int values2[24]; 
    int currentPMS1ArrayValue;
    int currentPMS2ArrayValue;
};