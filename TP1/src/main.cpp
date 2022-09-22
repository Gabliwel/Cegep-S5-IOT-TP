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
long timerWifi = 0;
long lastConnectionAttempt = 0;
const long CONNECTION_INTERVAL_WIFI = 1000 * 20;

//WebServer
WebServer server(80);
RevolvairWebServer webServer = RevolvairWebServer(server);

//RGBLedManager
RGBLedManager ledManager = RGBLedManager(ledR, ledG, ledB);

//API
RevolvairAPI apiManager = RevolvairAPI(MAC_ID);
long timerApi = 0;
long lastApiCall = 0;
const long API_INTERVAL = 1000 * 120;

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
    // Aller chercher du data avant
    apiManager.postData();
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
    if(timerApi - lastApiCall > API_INTERVAL)
    {
      //Aller chercher du data
      apiManager.postData();
      lastApiCall = millis();
    }
    timerApi = millis();
  }
  else
  {
    if(timerWifi - lastConnectionAttempt > CONNECTION_INTERVAL_WIFI)
    {
      wifiManager.connect();
      lastConnectionAttempt = millis();
    }
    timerWifi = millis();
  }

  //changer la couleur avant au besoin, pis check avant le if du wifi
  ledManager.loop();
  delay(2);
}