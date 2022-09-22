#include "RevolvairAPI.h"

RevolvairAPI::RevolvairAPI(const char* mac_id)
{
    this->MAC_ID = mac_id;
}

void RevolvairAPI::postData()
{
    String jsonPm25Package = "";
    StaticJsonDocument<200> doc;

    doc["esp8266id"] = "12224532";
    doc["software_version"]   = "Revo-2022-777";
    JsonArray array2 = doc.createNestedArray("sensordatavalues");
    JsonObject nested = array2.createNestedObject();
        nested["value_type"] = "PMS_P0";
        nested["value"] = "2.3";
    JsonObject nested2 = array2.createNestedObject();
        nested2["value_type"] = "PMS_P1";
        nested2["value"] = "1.3";

    serializeJson(doc, jsonPm25Package);
    postJSON(jsonPm25Package);
}

void RevolvairAPI::postJSON(String& encodedJSON)
{
    WiFiClientSecure *client = new WiFiClientSecure;
    if(client) {
      client -> setCACert(staging_revolvair_cert_R3);
    }
  
    HTTPClient http;
    http.begin(*client, API_POST_URL); 
    http.addHeader("x-mac-id", "esp32-083AF2BA8814"); // @TODO remplacer par votre mac. Ex : ESP32-A0WDQ6
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(encodedJSON);
    String payload = http.getString();
    Serial.println("POST");
    Serial.println(API_POST_URL);
    Serial.println(httpCode);
    Serial.println(payload);
    http.end();
}
