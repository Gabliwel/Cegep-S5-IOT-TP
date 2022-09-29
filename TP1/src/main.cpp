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
#include <Averager.h>

int period = 12000;
unsigned long time_now = 0;

#define BuiltIn_Del 2

//Wifi
WifiManager wifiManager = WifiManager(SSID, PASSWORD);
long timerWifi = 0;
long lastConnectionAttempt = 0;
const long CONNECTION_INTERVAL_WIFI = 1000 * 20;
bool wasConnectedLastLoop;

//WebServer
WebServer server(80);
RevolvairWebServer webServer = RevolvairWebServer(server);
float nbLoopSinceWeb;
float totalPMS2; 

//RGBLedManager
RGBLedManager ledManager = RGBLedManager(ledR, ledG, ledB);

//API
RevolvairAPI apiManager = RevolvairAPI();

//Timer API et WebServer
long timerWebAction = 0;
long lastWebAction = 0;
const long WEB_INTERVAL = 1000 * 120;

//PMSReader
PMS firstPms(Serial2);
PMS secondPms(Serial1);
Averager averager = Averager();
PMSReader pmsReader(firstPms, secondPms, averager);
PMS::DATA data1;
PMS::DATA data2;
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

void setChipId()
{
  //Print du chip id
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  Serial.print("Chip ID: "); 
  Serial.println(chipId);
}

void firstConnexion()
{
  wifiManager.printInfo();
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  webServer.setup();
  apiManager.setup();
  temperature = tempReader.getTemperatureValue();
  humidity = tempReader.getHumidityValue();
  pmsValues = pmsReader.getPMSValues();

  webServer.setCaptorsData(pmsValues[1], aqiscale.getPollutionLvl(pmsValues[1]), temperature, humidity);
  webServer.setWifiInfo(SSID, wifiManager.getWifiForce());
  lastWebAction = millis();
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 25, 26); // PMS Serial // tx, rx
  Serial2.begin(9600);
  Serial.println("");

  pinMode(BuiltIn_Del, OUTPUT);
  digitalWrite(BuiltIn_Del, LOW);

  setChipId();
  tempReader.init();

  wifiManager.setup();
  ledManager.setup();
  if(wifiManager.isConnected())
  {
    firstConnexion();
    wasConnectedLastLoop = true;
  }
  else
  {
    lastConnectionAttempt = millis();
    wasConnectedLastLoop = false;
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
  Serial.print(pmsValues[3]);
  Serial.print(",");
  Serial.print(pmsValues[4]);
  Serial.print(",");
  Serial.print(pmsValues[5]);
  Serial.println("");
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
  //Parfois se reconnecte automatiquement sans le connect dans le wifi
  if(wifiManager.isConnected() && !wasConnectedLastLoop)
  {
    firstConnexion();
  }

  if(wifiManager.isConnected())
  {
    wasConnectedLastLoop = true;
    temperature = tempReader.getTemperatureValue();
    humidity = tempReader.getHumidityValue();
    pmsValues = pmsReader.getPMSValues();
    printLoop();
    nbLoopSinceWeb++;
    totalPMS2 += pmsValues[1];

    if(timerWebAction - lastWebAction > WEB_INTERVAL)
    {
      Serial.println("----------ACTION WEB-----------");
      int averagerMeanValue = averager.getAverage();
      apiManager.postData(chipId, wifiManager.getCleanMacAdress(), pmsValues, temperature, humidity);
      webServer.setCaptorsData(totalPMS2 / nbLoopSinceWeb, aqiscale.getPollutionLvl(averagerMeanValue), temperature, humidity);
      webServer.setWifiInfo(SSID, wifiManager.getWifiForce());
      lastWebAction = millis();
      totalPMS2 = 0;
      nbLoopSinceWeb = 0;
    }
    timerWebAction = millis();
    webServer.loop();
    ledManager.changeColorOnPmValue(pmsValues[1]);
  }
  else 
  {
    wasConnectedLastLoop = false;
    if(timerWifi - lastConnectionAttempt > CONNECTION_INTERVAL_WIFI)
    {
      wifiManager.connect();
      lastConnectionAttempt = millis();
      if(!wifiManager.isConnected())
      {
        ledManager.changeColor(Color::blue);
      }
    }
    timerWifi = millis();
  }
  ledManager.loop();
}
