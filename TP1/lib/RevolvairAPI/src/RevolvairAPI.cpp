#include "RevolvairAPI.h"

RevolvairAPI::RevolvairAPI()
{

}

void RevolvairAPI::postData(uint32_t chipId, String macId, int * pmsValues, float temp, float humidity)
{
    String jsonPm25Package = "";
    StaticJsonDocument<200> doc;

    //doc["esp8266id"] = chipId;
    doc["esp8266id"] = "12224532";
    doc["software_version"] = "Revo-2022-777";
    JsonArray array2 = doc.createNestedArray("sensordatavalues");
    JsonObject nested = array2.createNestedObject();
        nested["value_type"] = "PMS_P0";
        nested["value"] = pmsValues[0];
    JsonObject nested2 = array2.createNestedObject();
        nested2["value_type"] = "PMS2";
        nested2["value"] = pmsValues[1];
    JsonObject nested3 = array2.createNestedObject();
        nested3["value_type"] = "PMS_P1";
        nested3["value"] = pmsValues[2];
    JsonObject nested4 = array2.createNestedObject();
        nested4["value_type"] = "BME280_temperature";
        nested4["value"] = temp;
    JsonObject nested5 = array2.createNestedObject();
        nested5["value_type"] = "BME280_humidity";
        nested5["value"] = humidity;

    serializeJson(doc, jsonPm25Package);
    postJSON(jsonPm25Package, macId);
}

void RevolvairAPI::postJSON(String& encodedJSON, String macId)
{
    WiFiClientSecure *client = new WiFiClientSecure;
    if(client) {
      client -> setCACert(staging_revolvair_cert_R3);
    }
  
    HTTPClient http;
    http.begin(*client, API_POST_URL); 
    http.addHeader("x-mac-id", "esp32-"+macId);
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(encodedJSON);
    String payload = http.getString();
    Serial.println("---------POST--------");
    Serial.println(API_POST_URL);
    Serial.println(httpCode);
    Serial.println(payload);
    Serial.println("---------------------");
    http.end();
}
