#pragma once
#include <Arduino.h>

enum Color {blue, green, yellow, orange, red};

class RGBLedManager
{
public:
    RGBLedManager(uint8_t ledR, uint8_t ledG, uint8_t ledB);
    void setup(void);
    void loop(void);
    void changeColor(Color color);
    Color getCurrentColor();
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

    void updateLight();
};