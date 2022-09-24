#pragma once
#include <Arduino.h>
#include <string>
#include <algorithm>

class WifiManager
{
public:
    WifiManager(const char* ssid, const char* password);
    void setup(void);
    void connect();
    bool isConnected();
    long getWifiForce();
    String getCleanMacAdress();
private:
    const char* ssid;
    const char* password;
    String mac = "";
};