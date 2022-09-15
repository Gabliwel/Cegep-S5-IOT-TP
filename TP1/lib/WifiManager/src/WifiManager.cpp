#include "WifiManager.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#define LED_BUILTIN 2

WiFiServer server(80);

WifiManager::WifiManager(char *STA_SSID, char *STA_PW, char *AP_SSID, char *AP_PW)
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(AP_SSID, AP_PW);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}