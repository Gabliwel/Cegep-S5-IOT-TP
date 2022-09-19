#include <Arduino.h>

enum Color {blue, green, yellow, orange, red};

class RGBLedManager
{
public:
    RGBLedManager();
    void setup(void);
    void loop(void);
    void changeColor(Color color);
    Color getCurrentColor();
private:
    Color currentColor = Color::blue;
    uint32_t R, G, B;
    bool lightIsOn = false;

    const uint8_t ledR = 12;  
    const uint8_t ledG = 13;
    const uint8_t ledB = 14;

    long timer = 0;
    long lastTimerChange = 0;
    const long FLASHING_INTERVAL = 500;

    void updateLight();
};