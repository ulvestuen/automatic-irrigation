#include <service/WifiConnectionService.h>

WifiConnectionService::WifiConnectionService() {}

void WifiConnectionService::connect()
{
    Serial.begin(115200);
    WiFi.disconnect(true);
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
