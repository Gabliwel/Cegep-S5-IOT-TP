#include "RevolvairWebServer.h"

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

void RevolvairWebServer::sendValues()
{
  this->server->send(200, "text/plain", "test");
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
  this->server->on("/readPMS", HTTP_GET, std::bind(&RevolvairWebServer::sendValues, this));
  this->server->onNotFound(std::bind(&RevolvairWebServer::handleNotFound, this));
  
  this->server->begin();
  Serial.println("HTTP server started");
}

void RevolvairWebServer::loop()
{
  this->server->handleClient();
}