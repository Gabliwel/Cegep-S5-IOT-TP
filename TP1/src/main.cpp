#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <FS.h>

#include "config.h"
#include <AqiScale.h>
#include <FlashFileReader.h>
#include <PMSReader.h>
#include <RevolvairAPI.h>
#include <RevolvairWebServer.h>
#include <RGBLedManager.h>
#include <TempReader.h>
#include <WifiManager.h>

#define BuiltIn_Del 2

//Wifi
WifiManager wifiManager = WifiManager(SSID, PASSWORD);
long timer = 0;
long lastConnectionAttempt = 0;
const long CONNECTION_INTERVAL = 1000 * 20;

//WebServer
WebServer server(80);
RevolvairWebServer webServer = RevolvairWebServer(server);

//RGBLedManager
RGBLedManager ledManager = RGBLedManager();

void setup() {
  Serial.begin(115200);
  Serial.println("");
  
  pinMode(BuiltIn_Del, OUTPUT);
  digitalWrite(BuiltIn_Del, LOW);

  wifiManager.setup();
  ledManager.setup();
  if(wifiManager.isConnected())
  {
    if (MDNS.begin("esp32")) {
      Serial.println("MDNS responder started");
    }
    webServer.setup();
  }
  else
  {
    lastConnectionAttempt = millis();
  }
}

void loop() {
  if(wifiManager.isConnected())
  {
    webServer.loop();
  }
  else
  {
    if(timer - lastConnectionAttempt > CONNECTION_INTERVAL)
    {
      wifiManager.connect();
      lastConnectionAttempt = millis();
    }
    timer = millis();
  }

  //changer la couleur avant
  ledManager.loop();
  delay(2);
}