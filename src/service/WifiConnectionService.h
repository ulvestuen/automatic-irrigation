#ifndef WifiConnectionService_h
#define WifiConnectionService_h

#include <secrets.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Create a file named secrets.h at the same level in the folder structure as "main.cpp".
// Add the following contents to the file and substitute with a desired ssid and pwd:
// #ifndef secrets_h
// #define secrets_h

// #ifndef STASSID
// #define STASSID "your wlan ssid here"
// #define STAPSK "your wlan pwd here"
// #endif

// #endif
class WifiConnectionService
{

private:
    const char *ssid = STASSID;
    const char *password = STAPSK;

public:
    WifiConnectionService();
    void connect();
};

#endif
