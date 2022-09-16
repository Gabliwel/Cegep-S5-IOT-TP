#include "WifiManager.h"

#include <Arduino.h>
#include <WiFi.h>

WifiManager::WifiManager(const char* ssid, const char* password)
{
    this->ssid = ssid;
    this->password = password;
}

void WifiManager::setup()
{
    connect();
}

void WifiManager::loop()
{
    // Serial.println("1");
}

void WifiManager::connect()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    int counter = 0;
    while (WiFi.status() != WL_CONNECTED && counter < 20) { // 10 sec, et *2 comme à chaque demi sec
        delay(500); // donc 0.5 sec
        Serial.print(".");
        counter += 1;
    }

    if(isConnected())
    {
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.print("Connexion impossible...");
    }
}

bool WifiManager::isConnected()
{
    if(WiFi.status() == WL_CONNECTED)
    {
        return true;
    }
    else 
    {
        return false;
    }
}