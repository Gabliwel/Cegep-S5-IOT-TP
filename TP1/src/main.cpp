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
RevolvairAPI apiManager = RevolvairAPI();
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

//Arduino
uint32_t chipId = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial.println("");

  pinMode(BuiltIn_Del, OUTPUT);
  digitalWrite(BuiltIn_Del, LOW);

  //Print du chip id
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  Serial.print("Chip ID: "); 
  Serial.println(chipId);
  Serial.print("Chip model: "); 
  Serial.println(ESP.getChipModel());

  tempReader.init();

  wifiManager.setup();
  ledManager.setup();
  if(wifiManager.isConnected())
  {
    if (MDNS.begin("esp32")) {
      Serial.println("MDNS responder started");
    }
    webServer.setup();
    //Premier post API
    temperature = tempReader.getTemperatureValue();
    humidity = tempReader.getHumidityValue();
    pmsValues = pmsReader.getPMSValues();
    apiManager.postData(chipId, wifiManager.getCleanMacAdress(), pmsValues, temperature, humidity);
  }
  else
  {
    lastConnectionAttempt = millis();
  }
}

void printLoop(){
  Serial.println("---------------------");
  Serial.print("PM: ");
  Serial.print(pmsValues[0]);
  Serial.print(",");
  Serial.print(pmsValues[1]);
  Serial.print(",");
  Serial.print(pmsValues[2]);
  Serial.println("");
  //--------------- print le DCL 2.5, mais jsp c'est quoi------------
  //Serial.print("DCL 2.5: ");
  //Serial.print("DCL2.5");
  //Serial.println("");
  Serial.print("IQA de l’air: ");
  Serial.print(aqiscale.getAQI(pmsValues[1]));
  Serial.println("");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("");
  Serial.print("Humidite: ");
  Serial.print(humidity);
  Serial.println("");
  Serial.println(aqiscale.getPollutionLvl(pmsValues[1]));
  Serial.println("---------------------");
}

void loop() {
  if(wifiManager.isConnected())
  {
    // on pourait aussi obtenir les donnés sans le wifi...
    // ...mais inutile et non précisé dans l'énoncé

    // l'énoncé dit aussi:
    // lire les valeurs des capteurs...  ...aux 2 minutes, mais aussi pas clair comme il faut aussi print a chaque refresh
    temperature = tempReader.getTemperatureValue();
    humidity = tempReader.getHumidityValue();
    pmsValues = pmsReader.getPMSValues();
    //printLoop();

    if(timerApi - lastApiCall > API_INTERVAL)
    {
      apiManager.postData(chipId, wifiManager.getCleanMacAdress(), pmsValues, temperature, humidity);
      lastApiCall = millis();
    }
    timerApi = millis();

    webServer.setCaptorsData(pmsValues[1], aqiscale.getPollutionLvl(pmsValues[1]), temperature, humidity);
    webServer.setWifiInfo(SSID, wifiManager.getWifiForce());
    webServer.loop();
    ledManager.changeColorOnPmValue(pmsValues[1]);
  }
  else
  {
    if(timerWifi - lastConnectionAttempt > CONNECTION_INTERVAL_WIFI)
    {
      wifiManager.connect();
      lastConnectionAttempt = millis();
      if(!wifiManager.isConnected())
      {
        ledManager.changeColor(Color::blue);
      }
      else
      {
        webServer.setup();
      }
    }
    timerWifi = millis();
  }
  ledManager.loop();
  delay(2);
}
