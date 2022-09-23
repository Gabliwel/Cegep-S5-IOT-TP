class WifiManager
{
public:
    WifiManager(const char* ssid, const char* password);
    void setup(void);
    void connect();
    bool isConnected();
    long getWifiForce();
private:
    const char* ssid;
    const char* password;
};