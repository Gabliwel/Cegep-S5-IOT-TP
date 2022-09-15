#include <WebServer.h>
#include <FlashFileReader.h>

class RevolvairWebServer
{
public:
    RevolvairWebServer(WebServer &server);
    static const int led = 13;
    void handleRoot();
    void handleNotFound();
    bool loadFromSpiffs(String path);
    void setup(void);
    void loop(void);
private:
    WebServer *server;
    FlashFileReader flashFileReader;
};