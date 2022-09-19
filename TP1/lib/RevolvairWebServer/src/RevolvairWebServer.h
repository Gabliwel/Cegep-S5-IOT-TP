#include <WebServer.h>
#include <FlashFileReader.h>
#include <string>

class RevolvairWebServer
{
public:
    RevolvairWebServer(WebServer &server);
    static const int led = 13;
    void handleRoot();
    void handleNotFound();
    void sendValues();
    void setup(void);
    void loop(void);
private:
    WebServer *server;
    FlashFileReader flashFileReader;
};