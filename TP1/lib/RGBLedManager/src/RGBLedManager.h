#pragma once
#include <Arduino.h>

enum Color {blue, green, yellow, orange, red};

class RGBLedManager
{
public:
    RGBLedManager(uint8_t ledR, uint8_t ledG, uint8_t ledB);
    void setup(void);
    void loop(void);
    void changeColorOnPmValue(float pm25);
    void changeColor(Color color);
    Color getColorFromPM25(float pm25);
private:
    Color currentColor = Color::blue;
    uint32_t R, G, B;
    bool lightIsOn = false;

    uint8_t ledR;  
    uint8_t ledG;
    uint8_t ledB;

    long timer = 0;
    long lastTimerChange = 0;
    const long FLASHING_INTERVAL = 500;
    
    const float GOOD_PM_LIMIT = 12;
    const float OK_PM_LIMIT = 35;
    const float BAD_PM_LIMIT = 55;

    void updateLight();
};