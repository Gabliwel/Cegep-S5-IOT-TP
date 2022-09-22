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
private:
    WebServer *server;
    FlashFileReader flashFileReader;

    String SSID = "N/D";
    String wifiForce = "N/D";
};