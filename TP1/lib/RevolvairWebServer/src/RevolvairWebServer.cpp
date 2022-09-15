#include "RevolvairWebServer.h"

RevolvairWebServer::RevolvairWebServer(WebServer &server)
{
  this->server = &server;
}

void RevolvairWebServer::setup()
{
  //server.on("/", handleRoot);
  this->server->send(302, "text/plain", "");
}

void RevolvairWebServer::handleRoot()
{
  this->server->sendHeader("Location", "/index.htm", true);
  this->server->send(302, "text/plain", "");
}