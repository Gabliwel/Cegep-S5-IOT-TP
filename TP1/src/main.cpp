#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <FS.h>
#include <SPIFFS.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

#include "config.h"
#include <AqiScale.h>
#include <FlashFileReader.h>
#include <PMSReader.h>
#include <RevolvairAPI.h>
#include <RevolvairWebServer.h>
#include <RGBLedManager.h>
#include <TempReader.h>
#include <WifiManager.h>

#include <PMS.h>

int period = 2000;
unsigned long time_now = 0;

#define BuiltIn_Del 2

//Wifi
WifiManager wifiManager = WifiManager(SSID, PASSWORD);

//WebServer
WebServer server(80);
RevolvairWebServer webServer = RevolvairWebServer(server);

//PMSReader
PMS firstPms(Serial2);
PMSReader pmsReader(firstPms);
int * pmsValues;

//DHT
#define DHT_PIN 18 // ESP32 IO18
#define DHT_TYPE DHT22


void setup() {
  pinMode(BuiltIn_Del, OUTPUT);
  digitalWrite(BuiltIn_Del, LOW);
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial.println("");

  wifiManager.setup();
  if(wifiManager.isConnected())
  {
    if (MDNS.begin("esp32")) {
      Serial.println("MDNS responder started");
    }

    SPIFFS.begin();
    if (SPIFFS.begin()) {
      Serial.println("SPIFFS begin");
    }
    
    webServer.setup();
  }

}
void loop() {
  time_now = millis();      
 
  
  while(millis() < time_now + period){ 
    pmsValues = pmsReader.getPMSValues();
  }        
  Serial.print(pmsValues[0]);
  Serial.print(",");
  Serial.print(pmsValues[1]);
  Serial.print(",");
  Serial.print(pmsValues[2]);
  Serial.println("");
}