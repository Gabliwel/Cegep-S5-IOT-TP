#include <Arduino.h>
#include <string.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <FS.h>

#include <SPIFFS.h>
#include <Adafruit_Sensor.h>

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

int period = 12000;
unsigned long time_now = 0;

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

//PMSReader
PMS firstPms(Serial2);
PMSReader pmsReader(firstPms);
int * pmsValues;

//DHT
#define DHT_PIN 18 // ESP32 IO18
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);
TempReader tempReader(dht);
float temperature = 0;
float humidity = 0;

//AQIScale
AqiScale aqiscale = AqiScale();

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial.println("");

  pinMode(BuiltIn_Del, OUTPUT);
  digitalWrite(BuiltIn_Del, LOW);

  tempReader.init();

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
  time_now = millis();      
  temperature = tempReader.getTemperatureValue();
  humidity = tempReader.getHumidityValue();
  
  while(millis() < time_now + period){ 
    pmsValues = pmsReader.getPMSValues();
    
  }        
  Serial.print(pmsValues[0]);
  Serial.print(",");
  Serial.print(pmsValues[1]);
  Serial.print(",");
  Serial.print(pmsValues[2]);
  Serial.println("");
  Serial.print(temperature);
  Serial.println("");
  Serial.print(humidity);
  Serial.println("");
  Serial.print(aqiscale.getAQI(pmsValues[1]));
}