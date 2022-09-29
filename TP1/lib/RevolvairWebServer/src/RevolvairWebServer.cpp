#include "RevolvairWebServer.h"

#include <ArduinoJson.h>
#include <FS.h>

#include <WebServer.h>
#include <FlashFileReader.h>

RevolvairWebServer::RevolvairWebServer(WebServer &server)
{
  this->server = &server;
  this->flashFileReader = FlashFileReader();
}

void RevolvairWebServer::handleRoot()
{
  this->server->sendHeader("Location", "/index.html", true);
  this->server->send(302, "text/plain", "");
}

void RevolvairWebServer::handleTemp()
{
  this->server->sendHeader("Location", "/temp.html", true);
  this->server->send(302, "text/plain", "");
}

void RevolvairWebServer::handleWifi()
{
  this->server->sendHeader("Location", "/wifi.html", true);
  this->server->send(302, "text/plain", "");
}

void RevolvairWebServer::handleAbout()
{
  this->server->sendHeader("Location", "/about.html", true);
  this->server->send(302, "text/plain", "");
}

void RevolvairWebServer::sendValues()
{
  String jsonPm25Package = "";
  StaticJsonDocument<200> doc;

  doc["PM"] = this->PM25;
  doc["Description"] = this->description;
  doc["Temp"] = this->temp;
  doc["Humidity"] = this->humidity;
  doc["SSID"] = this->ssid;
  doc["WifiForce"] = this->wifiForce;

  serializeJson(doc, jsonPm25Package);
  this->server->send(200, "application/json", jsonPm25Package);
}

void RevolvairWebServer::handleNotFound()
{
  Serial.println("Not found");
  Serial.println(this->server->uri());
  if(flashFileReader.loadFromSpiffs(this->server->uri(), this->server)) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += this->server->uri();
  message += "\nMethod: ";
  message += (this->server->method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += this->server->args();
  message += "\n";
  for (uint8_t i=0; i<this->server->args(); i++){
    message += " NAME:"+this->server->argName(i) + "\n VALUE:" + this->server->arg(i) + "\n";
  }
  this->server->send(404, "text/plain", message);
  Serial.println(message);
}

void RevolvairWebServer::setup()
{
  this->server->on("/", HTTP_GET, std::bind(&RevolvairWebServer::handleRoot, this));
  this->server->on("/temp", HTTP_GET, std::bind(&RevolvairWebServer::handleTemp, this));
  this->server->on("/wifi", HTTP_GET, std::bind(&RevolvairWebServer::handleWifi, this));
  this->server->on("/about", HTTP_GET, std::bind(&RevolvairWebServer::handleAbout, this));
  this->server->on("/readPMS", HTTP_GET, std::bind(&RevolvairWebServer::sendValues, this));
  this->server->onNotFound(std::bind(&RevolvairWebServer::handleNotFound, this));
  
  this->server->begin();
  Serial.println("HTTP server started");
}

void RevolvairWebServer::loop()
{
  this->server->handleClient();
  delay(2);
}

void RevolvairWebServer::setCaptorsData(int PM25, char* desc, float temp, float humidity)
{
  this->PM25 = PM25;
  this->description = desc;
  this->temp = temp;
  this->humidity = humidity;
}

void RevolvairWebServer::setWifiInfo(const char* ssid, long wifiForce)
{
  this->ssid = ssid;
  this->wifiForce = wifiForce;
}