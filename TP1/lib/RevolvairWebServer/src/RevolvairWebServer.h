#include <WebServer.h>
#include <FlashFileReader.h>
#include <string>

class RevolvairWebServer
{
public:
    RevolvairWebServer(WebServer &server);
    static const int led = 13;
    void handleRoot();
    void handleTemp();
    void handleWifi();
    void handleAbout();
    void handleNotFound();
    void sendValues();
    void setup(void);
    void loop(void);
    void setCaptorsData(int PM25, char* desc, float temp, float humidity);
    void setWifiInfo(const char* ssid, long wifiForce);
private:
    WebServer *server;
    FlashFileReader flashFileReader;

    String ssid = "N/D";
    long wifiForce = -1;
    int PM25 = -1;
    String description = "N/D";
    float temp = -1;
    float humidity = -1;
};