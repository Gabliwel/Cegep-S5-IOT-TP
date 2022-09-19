class WifiManager
{
public:
    WifiManager(const char* ssid, const char* password);
    void setup(void);
    void loop(void);
    void connect();
    bool isConnected();
private:
    const char* ssid;
    const char* password;
};