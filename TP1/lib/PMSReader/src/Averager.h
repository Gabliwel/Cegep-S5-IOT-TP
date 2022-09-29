#pragma once

class Averager
{
public:
    Averager();
    float getAverage(int nbLoop);
    void addValue(int value);
private:
    void resetValues();
    int values1[24];
    int values2[24]; 
    int currentPMS1ArrayValue;
    int currentPMS2ArrayValue;
    int sum = 0;
    int entries = 0;
};