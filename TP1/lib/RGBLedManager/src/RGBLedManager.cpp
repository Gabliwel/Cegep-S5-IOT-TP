#include "RGBLedManager.h"

RGBLedManager::RGBLedManager(uint8_t ledR, uint8_t ledG, uint8_t ledB)
{
    this->ledR = ledR;
    this->ledG = ledG;
    this->ledB = ledB;
}

void RGBLedManager::setup()
{
    ledcAttachPin(ledR, 1);
    ledcAttachPin(ledG, 2);
    ledcAttachPin(ledB, 3);

    ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
    ledcSetup(2, 12000, 8);
    ledcSetup(3, 12000, 8);
}

void RGBLedManager::loop()
{
    if(currentColor == blue)
    {
        if(timer - lastTimerChange > FLASHING_INTERVAL)
        {
            if(!lightIsOn)
            {
                timer = 0;
                B = 255;
            }
            else
            {
                timer = 0;
                B = 0;
            }
            lightIsOn = !lightIsOn;
            lastTimerChange = millis();
        }
        timer = millis();
    }
    else if (currentColor == red)
    {
        if(timer - lastTimerChange > FLASHING_INTERVAL)
        {
            if(!lightIsOn)
            {
                timer = 0;
                R = 255;
            }
            else
            {
                timer = 0;
                R = 0;
            }
            lightIsOn = !lightIsOn;
            lastTimerChange = millis();
        }
        timer = millis();
    }
    updateLight();
}

void RGBLedManager::changeColor(Color color)
{
    this->currentColor = color;
    timer = 0;
    lastTimerChange = 0;
    switch(currentColor) {
        case Color::blue:
            R = 0;
            G = 0;
            B = 255;
            lightIsOn = true;
            lastTimerChange = millis();
        break;
        case Color::green:
            R = 0;
            G = 255;
            B = 0;
        break;
        case Color::yellow:
            R = 255;
            G = 255;
            B = 0;
        break;
        case Color::orange:
            R = 255;
            G = 128;
            B = 0;
        break;
        case Color::red:
            R = 255;
            G = 0;
            B = 0;
            lightIsOn = true;
            lastTimerChange = millis();
        break;
    }
}

Color RGBLedManager::getCurrentColor()
{
    return currentColor;
}

void RGBLedManager::updateLight()
{
    ledcWrite(1, R);
    ledcWrite(2, G);   
    ledcWrite(3, B); 
}